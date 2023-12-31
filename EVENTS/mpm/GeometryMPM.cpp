/* *****************************************************************************
Copyright (c) 2016-2023, The Regents of the University of California (Regents).
All rights reserved.

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of the FreeBSD Project.

REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED HEREUNDER IS 
PROVIDED "AS IS". REGENTS HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, 
UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

*************************************************************************** */

#include "GeometryMPM.h"
#include <QLabel>
#include <QComboBox>
#include <QGroupBox>
#include <QGridLayout>
#include <QTabWidget>
#include <QStackedWidget>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

#include <SC_ComboBox.h>
#include <SC_DoubleLineEdit.h>
#include <SC_IntLineEdit.h>
#include <SC_StringLineEdit.h>
#include <SC_TableEdit.h>
#include <SC_FileEdit.h>
#include <SC_CheckBox.h>


GeometryMPM::GeometryMPM(QWidget *parent)
  :SimCenterWidget(parent)
{
  int numRow = 0;

  QGridLayout *layout = new QGridLayout();
  this->setLayout(layout);
  
  QStringList bodyList; bodyList << "Fluid" << "Debris" << "Structure" << "Custom";
  bodyPreset = new SC_ComboBox("body_preset",bodyList);
  layout->addWidget(new QLabel("Body Preset"),numRow,0);
  layout->itemAt(layout->count()-1)->setAlignment(Qt::AlignRight);
  layout->addWidget(bodyPreset,numRow++,1);
  // numRow = 0;

  // -----------------------------------------------------------------------------------
  QList <QString> objectList; objectList << "Box" << "Sphere" << "Cylinder" << "Cone" << "Ring" << "File" << "Checkpoint" << "OSU LWF" << "OSU DWB" << "UW WASIRF" << "WU TWB" << "USGS DFF" << "NICHE" << "Custom";
  objectType = new SC_ComboBox("object_type", objectList);
  layout->addWidget(new QLabel("Object Type"), numRow,0);
  layout->itemAt(layout->count()-1)->setAlignment(Qt::AlignRight);
  layout->addWidget(objectType,numRow++, 1);

  QList <QString> operationList;  operationList << "Add (OR)" << "Subtract (NOT)" << "Intersect (AND)" << "Difference (XOR)";
  operationType = new SC_ComboBox("operation_type", operationList);
  layout->addWidget(new QLabel("Operation With Prior Geometry"), numRow,0);
  layout->itemAt(layout->count()-1)->setAlignment(Qt::AlignRight);
  layout->addWidget(operationType,numRow++, 1);

  length = new SC_DoubleLineEdit("span_x",104.0);  
  height = new SC_DoubleLineEdit("span_y",4.6);  
  width = new SC_DoubleLineEdit("span_z",3.658);
  layout->addWidget(new QLabel("Dimensions (X,Y,Z)"), numRow, 0);
  layout->itemAt(layout->count()-1)->setAlignment(Qt::AlignRight);
  layout->addWidget(length, numRow, 1);  
  layout->addWidget(height, numRow, 2);  
  layout->addWidget(width, numRow, 3);  
  layout->addWidget(new QLabel("m"), numRow++, 4);

  originX = new SC_DoubleLineEdit("origin_x",0.0);
  originY = new SC_DoubleLineEdit("origin_y",0.0);
  originZ = new SC_DoubleLineEdit("origin_z",0.0);
  layout->addWidget(new QLabel("Origin (X,Y,Z)"), numRow, 0);  
  layout->itemAt(layout->count()-1)->setAlignment(Qt::AlignRight);
  layout->addWidget(originX, numRow,1);
  layout->addWidget(originY, numRow,2);
  layout->addWidget(originZ, numRow,3);
  layout->addWidget(new QLabel("m"), numRow++, 4);  

  // -----------------------------------------------------------------------------------
  applyArray = new SC_CheckBox("apply_array");
  layout->addWidget(new QLabel("Array of Geometries?"),numRow, 0);
  layout->itemAt(layout->count()-1)->setAlignment(Qt::AlignRight);
  layout->addWidget(applyArray,numRow++, 1);

  QGroupBox *arrayBox = new QGroupBox("Array Operation");
  QGridLayout *arrayBoxLayout = new QGridLayout();
  arrayBox->setLayout(arrayBoxLayout);

  arrayBox->hide();
  arrayBox->setVisible(false);
  int numArrayRow = 0;
  arrayX = new SC_IntLineEdit("array_x",1);
  arrayY = new SC_IntLineEdit("array_y",1);
  arrayZ = new SC_IntLineEdit("array_z",1);
  arrayBoxLayout->addWidget(new QLabel("Array Elements (nX,nY,nZ)"), numArrayRow, 0);
  arrayBoxLayout->itemAt(arrayBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  arrayBoxLayout->addWidget(arrayX, numArrayRow, 1);
  arrayBoxLayout->addWidget(arrayY, numArrayRow, 2);
  arrayBoxLayout->addWidget(arrayZ, numArrayRow, 3);
  arrayBoxLayout->addWidget(new QLabel("#"), numArrayRow++, 4);

  spacingX = new SC_DoubleLineEdit("spacing_x",0.60);  
  spacingY = new SC_DoubleLineEdit("spacing_y",0.20);  
  spacingZ = new SC_DoubleLineEdit("spacing_z",0.15);
  arrayBoxLayout->addWidget(new QLabel("Array Spacing (X,Y,Z)"), numArrayRow, 0);
  arrayBoxLayout->itemAt(arrayBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  arrayBoxLayout->addWidget(spacingX, numArrayRow, 1);  
  arrayBoxLayout->addWidget(spacingY, numArrayRow, 2);  
  arrayBoxLayout->addWidget(spacingZ, numArrayRow, 3);  
  arrayBoxLayout->addWidget(new QLabel("m"), numArrayRow++, 4);

  arrayBoxLayout->setRowStretch(numArrayRow,1);

  layout->addWidget(arrayBox, (numRow+numArrayRow), 0, numArrayRow, 5);
  numRow = numRow+numArrayRow+1;
  connect(applyArray, &QCheckBox::stateChanged, [=](int state) {
    if (state == 2) {
      arrayBox->show();
      arrayBox->setVisible(true);
    } else {
      arrayBox->hide();
      arrayBox->setVisible(false);
    }
  });

  // -----------------------------------------------------------------------------------
  numRow = numRow+1;
  applyRotation = new SC_CheckBox("apply_rotation");
  layout->addWidget(new QLabel("Rotate Geometry?"),numRow, 0);
  layout->itemAt(layout->count()-1)->setAlignment(Qt::AlignRight);
  layout->addWidget(applyRotation,numRow++, 1);

  QGroupBox *rotateBox = new QGroupBox("Rotation Operation");
  QGridLayout *rotateBoxLayout = new QGridLayout();
  rotateBox->setLayout(rotateBoxLayout);

  rotateBox->hide();
  rotateBox->setVisible(false);
  int numRotateRow = 0;
  rotateAngleX = new SC_DoubleLineEdit("rotate_x",0.0);
  rotateAngleY = new SC_DoubleLineEdit("rotate_y",0.0);
  rotateAngleZ = new SC_DoubleLineEdit("rotate_z",0.0);
  rotateBoxLayout->addWidget(new QLabel("Rotation Angles (rX,rY,rZ)"), numRotateRow, 0);
  rotateBoxLayout->itemAt(rotateBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  rotateBoxLayout->addWidget(rotateAngleX, numRotateRow, 1);
  rotateBoxLayout->addWidget(rotateAngleY, numRotateRow, 2);
  rotateBoxLayout->addWidget(rotateAngleZ, numRotateRow, 3);
  rotateBoxLayout->addWidget(new QLabel("deg."), numRotateRow++, 4);

  rotateFulcrumX = new SC_DoubleLineEdit("fulcrum_x",104.0);  
  rotateFulcrumY = new SC_DoubleLineEdit("fulcrum_y",4.6);  
  rotateFulcrumZ = new SC_DoubleLineEdit("fulcrum_z",3.658);
  rotateBoxLayout->addWidget(new QLabel("Rotation Center (X,Y,Z)"), numRotateRow, 0);
  rotateBoxLayout->itemAt(rotateBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  rotateBoxLayout->addWidget(rotateFulcrumX, numRotateRow, 1);  
  rotateBoxLayout->addWidget(rotateFulcrumY, numRotateRow, 2);  
  rotateBoxLayout->addWidget(rotateFulcrumZ, numRotateRow, 3);  
  rotateBoxLayout->addWidget(new QLabel("m"), numRotateRow++, 4);

  rotateBoxLayout->setRowStretch(numRotateRow,1);

  layout->addWidget(rotateBox, (numRow+numRotateRow+1), 0, numRotateRow, 5);
  numRow = numRow+numRotateRow+1+1;


  connect(applyRotation, &QCheckBox::stateChanged, [=](int state) {
    if (state == 2) {
      rotateBox->show();
      rotateBox->setVisible(true);
    } else {
      rotateBox->hide();
      rotateBox->setVisible(false);
    }
  });


  // -----------------------------------------------------------------------------------
  numRow = numRow+1;

  int numDimRow = 0;
  QGroupBox *dimensionsBox = new QGroupBox("Digital Twin Geometry");
  QGridLayout *dimensionsBoxLayout = new QGridLayout();
  dimensionsBox->setLayout(dimensionsBoxLayout);

  QStringList facilityList; facilityList << "Hinsdale Large Wave Flume (OSU LWF)" << "Hinsdale Directional Wave Basin (OSU DWB)" <<  "Wind-Air-Sea Interaction Facility (UW WASIRF)" << "Waseda University's Tsunami Wave Basin (WU TWB)" << "U.S. Geo. Survey's Debris Flow Flume (USGS DFF)" << "NICHE Full-Scale Wind-Wave Flume" << "Custom";
  facility = new SC_ComboBox("domainSubType",facilityList);
  dimensionsBoxLayout->addWidget(new QLabel("Digital Twin Facility"),numDimRow,0);
  dimensionsBoxLayout->itemAt(dimensionsBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  dimensionsBoxLayout->addWidget(facility,numDimRow++,1, 1, 4);

  facilityLength = new SC_DoubleLineEdit("facility_span_x",104.0);  
  facilityHeight = new SC_DoubleLineEdit("facility_span_y",4.6);  
  facilityWidth = new SC_DoubleLineEdit("facility_span_z",3.658);
  dimensionsBoxLayout->addWidget(new QLabel("Facility Dimensions (X,Y,Z)"), numDimRow, 0);
  dimensionsBoxLayout->itemAt(dimensionsBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  dimensionsBoxLayout->addWidget(facilityLength, numDimRow, 1);  
  dimensionsBoxLayout->addWidget(facilityHeight, numDimRow, 2);  
  dimensionsBoxLayout->addWidget(facilityWidth, numDimRow, 3);  
  dimensionsBoxLayout->addWidget(new QLabel("m"), numDimRow++, 4);

  standingWaterLevel = new SC_DoubleLineEdit("standingWaterLevel",2.0);
  dimensionsBoxLayout->addWidget(new QLabel("Standing Water Level (SWL)"), numDimRow, 0);
  dimensionsBoxLayout->itemAt(dimensionsBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  dimensionsBoxLayout->addWidget(standingWaterLevel, numDimRow, 1);  
  dimensionsBoxLayout->addWidget(new QLabel("m"), numDimRow++, 2);

  fillFlumeUptoSWL = new SC_CheckBox("fillFlumeUptoSWL");
  dimensionsBoxLayout->addWidget(new QLabel("Fill flume to SWL with fluid?"),numDimRow, 0);  
  dimensionsBoxLayout->itemAt(dimensionsBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  dimensionsBoxLayout->addWidget(fillFlumeUptoSWL,numDimRow++, 1);
  

  // numDimRow+=1; // Vertical spacer
  int numBathRow = 0;
  dimensionsBoxLayout->addWidget(new QLabel("Flume Bathymetry Type"),numDimRow,0);
  dimensionsBoxLayout->itemAt(dimensionsBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  // dimensionsBoxLayout->addWidget(bathXZData,numDimRow++,0,4,4);  

  // QStackedWidget *bathStack = new QStackedWidget();
  // bathStack->addWidget(ptWidget);
  // bathStack->addWidget(stlWidget);
  // Stack for bathymetry
  // QStringList bathOptions; bathOptions << "Point List" << "STL File";
  // bathymetryComboBox = new SC_ComboBox("bathType",bathOptions);
  
  QStringList bathOptions; bathOptions << "Point List" << "STL File";
  bathymetryComboBox = new SC_ComboBox("bathymetryComboBox", bathOptions);
  dimensionsBoxLayout->addWidget(bathymetryComboBox, numDimRow++, 1);
  QStringList bathXZHeadings; bathXZHeadings << "Bathymetry Joint Position (X) [m]" << "Bathymetry Joint  Height (Y) [m]";
  QStringList dataBathXZ; dataBathXZ << "35" << "0" << "42" << "1.75" << "56" << "2.5" << "105" << "2.5";
  bathXZData = new SC_TableEdit("bathXZData", bathXZHeadings, 4, dataBathXZ);
  bathSTL = new SC_FileEdit("bathSTL");

  QWidget *ptWidget = new QWidget(); 
  QGridLayout *ptLayout = new QGridLayout();
  ptLayout->addWidget(bathXZData, 0, 0, 2, 2);
  ptLayout->setRowStretch(1,1);
  ptWidget->setLayout(ptLayout);

  QWidget *stlWidget = new QWidget();
  QGridLayout *stlLayout = new QGridLayout();
  stlLayout->addWidget(new QLabel("Surface File (*.stl)"),0,0);
  stlLayout->itemAt(stlLayout->count()-1)->setAlignment(Qt::AlignRight);
  stlLayout->addWidget(bathSTL,0, 1, 1, 1);
  stlLayout->setRowStretch(1,1);  
  stlWidget->setLayout(stlLayout);

  QStackedWidget *bathStack = new QStackedWidget();
  bathStack->addWidget(ptWidget);
  bathStack->addWidget(stlWidget);
  
  // numBathRow=4;
  dimensionsBoxLayout->addWidget(bathStack,numDimRow++,0, 1, numBathRow);
  dimensionsBoxLayout->setRowStretch(numDimRow,1);
  layout->addWidget(dimensionsBox,numRow++,0,numDimRow,5);
  // numRow = numRow+numDimRow;
  numRow = numRow+numDimRow;

  layout->setRowStretch(numRow, 1);
  // int thisWidth = (*this).sizeHint().width(); // Probably 200
  // layout->addItem(new QSpacerItem(thisWidth, 25, QSizePolicy::Fixed, QSizePolicy::Expanding), numRow, 0);


  // connext bathymetry to show correct widget
  // connect(bathymetryComboBox, QOverload<int>::of(&QComboBox::activated),
	//   bathStack, &QStackedWidget::setCurrentIndex);


  connect(bathymetryComboBox, &QComboBox::currentTextChanged, [=](QString val) {
    if (val == "Point List") {
      bathStack->setCurrentIndex(0);
      bathXZData->show();
      bathXZData->setVisible(true);
      bathXZData->setEnabled(true);
      ptWidget->show();
      ptWidget->setEnabled(true);
      ptWidget->setVisible(true);

      // bathXZData->setTableData(4, dataBathXZ);
      stlWidget->hide();
      stlWidget->setEnabled(false);
      stlWidget->setVisible(false);
      // numBathRow = 4;
    } else if (val == "STL File") {
      //
      bathStack->setCurrentIndex(1);
      bathXZData->hide();
      bathXZData->setVisible(false);
      bathXZData->setEnabled(false);
      ptWidget->hide();
      ptWidget->setEnabled(false);
      ptWidget->setVisible(false);

      stlWidget->show();
      stlWidget->setEnabled(true);
      stlWidget->setVisible(true);
    }
  }
  );
  // Connect the facility QComboBox to change entries to default values if selected
  // If fluid, set default object type to match fluid object that fills flume digital twin
  connect(facility, &QComboBox::currentTextChanged, [=](QString val) {
    if (val == "Hinsdale Large Wave Flume (OSU LWF)") {
      facilityLength->setText("104.0");
      facilityHeight->setText("4.6");
      facilityWidth->setText("3.658");
      if (bodyPreset->currentText() == "Fluid") {
        objectType->setCurrentText("OSU LWF");
      }
    } else if (val == "Hinsdale Directional Wave Basin (OSU DWB)") {
      facilityLength->setText("48.8");
      facilityHeight->setText("2.1");
      facilityWidth->setText("26.5");
      if (bodyPreset->currentText() == "Fluid") {
        objectType->setCurrentText("OSU DWB");
      }
    } else if (val == "Wind-Air-Sea Interaction Facility (UW WASIRF)") {
      facilityLength->setText("12.19");
      facilityHeight->setText("1.22");
      facilityWidth->setText("0.914");
      objectType->setCurrentText("UW WASIRF");
    } else if (val == "Waseda University's Tsunami Wave Basin (WU TWB)") {
      facilityLength->setText("9.0");
      facilityHeight->setText("1.0");
      facilityWidth->setText("4.0");
      if (bodyPreset->currentText() == "Fluid") {
        objectType->setCurrentText("WU TWB");
      }
    } else if (val == "U.S. Geo. Survey's Debris Flow Flume (USGS DFF)") {
      facilityLength->setText("90.0");
      facilityHeight->setText("2.0");
      facilityWidth->setText("2.0");
      if (bodyPreset->currentText() == "Fluid") {
        objectType->setCurrentText("USGS DFF");
      }
    } else if (val == "NICHE Full-Scale Wind-Wave Flume") {
      facilityLength->setText("300.0");
      facilityHeight->setText("10.0");
      facilityWidth->setText("100.0");
      if (bodyPreset->currentText() == "Fluid") {
        objectType->setCurrentText("NICHE");
      }
    } else if (val == "Custom") {
      facilityLength->setText("0.0");
      facilityHeight->setText("0.0");
      facilityWidth->setText("0.0");
      objectType->setCurrentText("Box");
    }
  });

  connect(bodyPreset, &QComboBox::currentTextChanged, [=](QString val) {
    if (val == "Fluid") {
      facility->setCurrentText("Hinsdale Large Wave Flume (OSU LWF)");

      standingWaterLevel->setEnabled(true);
      standingWaterLevel->show();
      standingWaterLevel->setText("2.0");
      fillFlumeUptoSWL->setEnabled(true);
      fillFlumeUptoSWL->show();
      fillFlumeUptoSWL->setChecked(true);

      length->setText("104.0");
      height->setText("4.6");
      width->setText("3.658");
      originX->setText("0.0");
      originY->setText("0.0");
      originZ->setText("0.0");
      applyArray->setChecked(false);
      // bathymetryComboBox->setCurrentText("Point List");
      bathStack->setCurrentIndex(0);
      bathStack->show();
      bathStack->setEnabled(true);
      bathymetryComboBox->setEnabled(true);
      bathymetryComboBox->show();
      bathSTL->setEnabled(true);
      // bathXZData->setEnabled(true);
      // bathXZData->show();
      // bathXZData->setTableData(4, dataBathXZ);
      dimensionsBox->show();
    } else if (val == "Debris") {
      facility->setCurrentText("Hinsdale Large Wave Flume (OSU LWF)");
      standingWaterLevel->setDisabled(true);
      standingWaterLevel->hide();
      fillFlumeUptoSWL->setChecked(false);
      fillFlumeUptoSWL->setDisabled(true);
      fillFlumeUptoSWL->hide();
      length->setText("0.5");
      height->setText("0.05");
      width->setText("0.1");
      originX->setText("43.8");
      originY->setText("2.0");
      originZ->setText("1.825");
      applyArray->setChecked(true);
      // bathymetryComboBox->setCurrentText("Point List");
      bathymetryComboBox->setDisabled(true);
      bathymetryComboBox->hide();
      bathSTL->setDisabled(true);
      bathStack->setCurrentIndex(1);
      bathStack->hide();
      bathStack->setDisabled(true);
      // bathXZData->setTableData(4, dataBathXZ);
      // bathXZData->setDisabled(true);
      // bathXZData->hide();
      dimensionsBox->hide();
    } else if (val == "Structure") {
      facility->setCurrentText("Hinsdale Large Wave Flume (OSU LWF)");
      standingWaterLevel->setDisabled(true);
      standingWaterLevel->hide();
      fillFlumeUptoSWL->setChecked(false);
      fillFlumeUptoSWL->setDisabled(true);
      fillFlumeUptoSWL->hide();
      length->setText("1.0");
      height->setText("0.625");
      width->setText("1.0");
      originX->setText("45.8");
      originY->setText("2.0");
      originZ->setText("1.325");
      applyArray->setChecked(true);
      bathStack->setCurrentIndex(1);
      bathStack->hide();
      bathStack->setDisabled(true);
      bathymetryComboBox->setDisabled(true);
      bathymetryComboBox->hide();
      bathSTL->setDisabled(true);
      // bathXZData->setTableData(4, dataBathXZ);
      // bathXZData->setDisabled(true);
      // bathXZData->hide();
      dimensionsBox->hide();
    } else if (val == "Custom") {
      facility->setCurrentText("Custom");
      standingWaterLevel->setDisabled(true);
      standingWaterLevel->hide();
      fillFlumeUptoSWL->setChecked(false);
      fillFlumeUptoSWL->setDisabled(true);
      fillFlumeUptoSWL->hide();
      length->setText("1.0");
      height->setText("1.0");
      width->setText("1.0");
      originX->setText("0.0");
      originY->setText("0.0");
      originZ->setText("0.0");

      bathStack->setCurrentIndex(1);
      bathStack->hide();
      bathStack->setDisabled(true);
      bathymetryComboBox->setDisabled(true);
      bathymetryComboBox->hide();
      bathSTL->setDisabled(true);
      // bathXZData->setDisabled(true);
      // bathXZData->hide();
      dimensionsBox->hide();
    }
  });

    
  // -----------------------------------------------------------------------------------

  // layout->addWidget(tabWidget);

  // int numDefaultTabs = 3;

  // QVector<QGridLayout*> theAddedLayout(numReserveTabs);
  // QVector<QTabWidget*> modelAddedTabWidget(numReserveTabs); 

  // for (int i = 0; i < numReserveTabs; i++) {
  //   theAdded[i] = new QWidget();
  //   addedGeometry[i] = new geometryBodiesMPM();
  //   modelAddedTabWidget[i] = new QTabWidget();
  // }

  // connect(addB, &QPushButton::released, this, [=]() {
  //   // if (curTab != -1)  // insert below selected
  //   // Concatenate string to say "Custom Body 1", "Custom Body 2", etc.
  //   if (numAddedTabs >= numReserveTabs) 
  //     return;
    
  //   tabWidget->addTab(theAdded[numAddedTabs], QIcon(QString(":/icons/user-black.svg")), "Custom " + QString::number(numAddedTabs + 1));

  //   theAdded[numAddedTabs]->setLayout(theAddedLayout[numAddedTabs]);
  //   modelAddedTabWidget[numAddedTabs]->addTab(addedMaterial[numAddedTabs], QIcon(QString(":/icons/squares-filled-black.svg")),"Material");
  //   modelAddedTabWidget[numAddedTabs]->addTab(addedGeometry[numAddedTabs], QIcon(QString(":/icons/triangle-square-circle-black.svg")),"Geometry");
  //   modelAddedTabWidget[numAddedTabs]->addTab(addedAlgorithm[numAddedTabs], QIcon(QString(":/icons/engine-black.svg")),"Algorithm");
  //   modelAddedTabWidget[numAddedTabs]->addTab(addedPartition[numAddedTabs], QIcon(QString(":/icons/cpu-black.svg")),"Partition");
  //   modelAddedTabWidget[numAddedTabs]->setIconSize(QSize(sizeBodyTabs, sizeBodyTabs));
  //   theAddedLayout[numAddedTabs]->addWidget(modelAddedTabWidget[numAddedTabs]);
  //   numAddedTabs += 1;
  // });

  // connect(delB, &QPushButton::released, this, [=]() {
  //   if (( tabWidget->currentIndex() == -1) || (tabWidget->count() <= numDefaultTabs) || (tabWidget->currentIndex() < numDefaultTabs)) 
  //     return;
  //   auto widget = tabWidget->widget(tabWidget->currentIndex());
  //   if (widget) {
  //         // Delete the widget itself
  //         // widget.deleteLater()
  //   }
  //   tabWidget->setCurrentIndex(tabWidget->currentIndex()-1);
  //   tabWidget->removeTab(tabWidget->currentIndex()+1);
  //   // clean up 
  //   numAddedTabs -= 1;
  // }); 

  // connect(tabWidget, &QTabWidget::tabCloseRequested, this, [=](int index) {
  //   if (( index == -1) || (tabWidget->count() <= numDefaultTabs) || (index < numDefaultTabs)) 
  //     return; 
  //   // tabWidget->setCurrentIndex(index-1);
  //   auto widget = tabWidget->widget(index);
  //   if (widget) {
  //         // removes the widget
  //         // widget.deleteLater()
  //   }
  //   if (index > 0 && index < tabWidget->count()-1 && tabWidget->currentIndex() == index) {
  //     tabWidget->setCurrentIndex(index-1);
  //   } 
  //   tabWidget->removeTab(index);
  //   // clean up
  //   numAddedTabs -= 1;
  // });


  // Debris Geometry File = new SC_FileEdit("file");
  // debrisGeometryLayout->addWidget(new QLabel("Debris Geometry File"),numRow, 0);
  // debrisGeometryLayout->addWidget(Debris Geometry File,numRow++, 1);  


  // // connext bathymetry to show correct widget
  // connect(waveGenComboBox, QOverload<int>::of(&QComboBox::activated),
	//   waveGenStack, &QStackedWidget::setCurrentIndex);
  // */

}


GeometryMPM::~GeometryMPM()
{

}

bool
GeometryMPM::setBodyPreset(int index)
{
  // Way to set the body preset from higher levels, 
  // e.g. to set the geometry body preset to "Debris" if the user adds a debris template in bodies
  if (index < 0 || index > bodyPreset->count()) {
    // QDebug() << "Error: Invalid body preset index";
    return false;
  }
  bodyPreset->setCurrentIndex(index);
  // Default Fluid template to OSU LWF water object
  // Everything else starts as rectangular prism boxes for ease of use
  if (bodyPreset->currentText() == "Fluid") {
    objectType->setCurrentText("OSU LWF");
    applyArray->setChecked(false);
    applyRotation->setChecked(false);
  } else if (bodyPreset->currentText() == "Debris") {
    objectType->setCurrentText("Box");
    applyArray->setChecked(true);
    applyRotation->setChecked(true);
  } else if (bodyPreset->currentText() == "Structure") {
    objectType->setCurrentText("Box");
    applyArray->setChecked(true);
    applyRotation->setChecked(false);
  } else if (bodyPreset->currentText() == "Custom") {
    objectType->setCurrentText("Box");
    applyArray->setChecked(true);
    applyRotation->setChecked(true);
  }
  // Should probably make this a function, it checks array spacing vs dimensions
  if (applyArray->isChecked()) {
    // May prefer terniary operator here
    if (spacingX->text().toDouble() < length->text().toDouble()) 
      spacingX->setText(QString::number(1.0*length->text().toDouble()));
    if (spacingY->text().toDouble() < height->text().toDouble()) 
      spacingY->setText(QString::number(1.0*height->text().toDouble()));
    if (spacingZ->text().toDouble() < width->text().toDouble()) 
      spacingZ->setText(QString::number(1.0*width->text().toDouble()));
  }
  return true;
}

bool
GeometryMPM::outputToJSON(QJsonObject &jsonObject)
{
  QJsonArray geometriesArray;


  {
    QJsonObject geometryObject;


    geometryObject["body_preset"] = bodyPreset->currentText();
    geometryObject["object"] = objectType->currentText();

    if (operationType->currentText() == "Add (OR)") {
      geometryObject["operation"] = "add";
    } else if (operationType->currentText() == "Subtract (NOT)") {
      geometryObject["operation"] = "subtract";
    } else if (operationType->currentText() == "Intersect (AND)") {
      geometryObject["operation"] = "intersect";
    } else if (operationType->currentText() == "Difference (XOR)") {
      geometryObject["operation"] = "difference";
    } else {
      geometryObject["operation"] = "add";
    }

    geometryObject["facility"] = facility->currentText();
    QJsonArray facilityDims;
    facilityDims.append(facilityLength->text().toDouble());
    facilityDims.append(facilityHeight->text().toDouble());
    facilityDims.append(facilityWidth->text().toDouble());
    // Only show facility dimensions if they are non-zero, i.e. if the user has selected a 3D digital twin
    if (facilityDims[0] != 0.0 && facilityDims[1] != 0.0 && facilityDims[2] != 0.0) {
      geometryObject["facility_dimensions"] = facilityDims;
      // facilityDims.append(length->text().toDouble());
      // facilityDims.append(height->text().toDouble());
      // facilityDims.append(width->text().toDouble());
    }

    QJsonArray spanArray;
    QJsonArray originArray;
    if (bodyPreset->currentText() == "Fluid") {
      // Crop fluid geometry to SWL and facility size if selected to fill flume up to SWL
      geometryObject["standing_water_level"] = standingWaterLevel->text().toDouble();
      geometryObject["fill_flume_upto_SWL"] = fillFlumeUptoSWL->isChecked();
      if (fillFlumeUptoSWL->isChecked()) {
        spanArray.append(length->text().toDouble() < facilityLength->text().toDouble() ? length->text().toDouble() : facilityLength->text().toDouble());
        spanArray.append(standingWaterLevel->text().toDouble() < facilityHeight->text().toDouble() ? standingWaterLevel->text().toDouble() : facilityHeight->text().toDouble());
        spanArray.append(width->text().toDouble() < facilityWidth->text().toDouble() ? width->text().toDouble() : facilityWidth->text().toDouble());
      } else {
        spanArray.append(length->text().toDouble());
        spanArray.append(height->text().toDouble());
        spanArray.append(width->text().toDouble());
      }
      if (0) geometryObject["dimensions"] = spanArray; // Future schema
      else   geometryObject["span"] = spanArray; // ClayoreUW artifact, to be deprecated

      originArray.append(originX->text().toDouble());
      originArray.append(originY->text().toDouble());
      originArray.append(originZ->text().toDouble());
      if (0) geometryObject["origin"] = originArray; // Future schema
      else   geometryObject["offset"] = originArray; // ClayoreUW artifact, to be deprecated

      // User point-list input bathymetry
      if (bathXZData->isEnabled()) {
        QJsonObject tableBath;
        bathXZData->outputToJSON(tableBath);
        QJsonArray bathXZArray;
        
        for (int i = 0; i < tableBath["bathXZData"].toArray().size(); i++) {
          bathXZArray.append(tableBath["bathXZData"].toArray()[i].toArray());
        }
        geometryObject["bathymetryXZ"] = bathXZArray;
      }
      // TODO: Add user file-input bathymetry to JSON 
    } else {
      spanArray.append(length->text().toDouble());
      spanArray.append(height->text().toDouble());
      spanArray.append(width->text().toDouble());
      if (0) geometryObject["dimensions"] = spanArray; // Future schema
      else   geometryObject["span"] = spanArray; // ClayoreUW artifact, to be deprecated

      originArray.append(originX->text().toDouble());
      originArray.append(originY->text().toDouble());
      originArray.append(originZ->text().toDouble());
      if (0) geometryObject["origin"] = originArray; // Future schema
      else   geometryObject["offset"] = originArray; // ClayoreUW artifact, to be deprecated
    }
    
    geometryObject["apply_array"] = applyArray->isChecked();
    if (applyArray->isChecked()) {
      QJsonArray arrayDims;
      arrayDims.append(arrayX->text().toInt());
      arrayDims.append(arrayY->text().toInt());
      arrayDims.append(arrayZ->text().toInt());
      geometryObject["array"] = arrayDims;

      QJsonArray spacingArray;
      spacingArray.append(spacingX->text().toDouble());
      spacingArray.append(spacingY->text().toDouble());
      spacingArray.append(spacingZ->text().toDouble());
      geometryObject["spacing"] = spacingArray;
    }

    geometryObject["apply_rotation"] = applyRotation->isChecked();
    if (applyRotation->isChecked()) {
      QJsonArray rotateAngles;
      rotateAngles.append(rotateAngleX->text().toDouble());
      rotateAngles.append(rotateAngleY->text().toDouble());
      rotateAngles.append(rotateAngleZ->text().toDouble());
      geometryObject["rotate"] = rotateAngles;

      QJsonArray rotateFulcrum;
      rotateFulcrum.append(rotateFulcrumX->text().toDouble());
      rotateFulcrum.append(rotateFulcrumY->text().toDouble());
      rotateFulcrum.append(rotateFulcrumZ->text().toDouble());
      geometryObject["fulcrum"] = rotateFulcrum;
    }
    
    // geometriesArray.append(geometryObject);
    QJsonArray tempGeometryArray = jsonObject["geometry"].toArray();
    tempGeometryArray.append(geometryObject);
    jsonObject["geometry"] = tempGeometryArray;
  }

  return true;
}

bool
GeometryMPM::inputFromJSON(QJsonObject &jsonObject)
{
  // theOpenSeesPyScript->inputFromJSON(jsonObject);
  // theSurfaceFile->inputFromJSON(jsonObject);    
  return true;
}

bool
GeometryMPM::copyFiles(QString &destDir)
{
  // if (theOpenSeesPyScript->copyFile(destDir) != true)
  //   return false;
  // return theSurfaceFile->copyFile(destDir);    
  return true;
}


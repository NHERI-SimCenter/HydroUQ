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
#include <QSvgWidget>
#include <QString>
#include <QIcon>

#include <SC_ComboBox.h>
#include <SC_DoubleLineEdit.h>
#include <SC_IntLineEdit.h>
#include <SC_StringLineEdit.h>
#include <SC_TableEdit.h>
#include <SC_FileEdit.h>
#include <SC_CheckBox.h>

#include "GeometryAI.h"

GeometryMPM::GeometryMPM(QWidget *parent)
  :SimCenterWidget(parent)
{
  int maxWidth = 1280;
  int numRow = 0;

  QGridLayout *layout = new QGridLayout();
  
  QStringList bodyList; bodyList << "Fluid" << "Debris" << "Structure" << "Custom" << "Generative AI";
  bodyPreset = new SC_ComboBox("body_preset", bodyList);
  layout->addWidget(new QLabel("Body Preset"), numRow, 0, 1, 1, Qt::AlignRight);
  layout->addWidget(bodyPreset,numRow++,1, 1, 3);
  layout->itemAt(layout->count()-1)->widget()->setMaximumWidth(maxWidth);
  // numRow = 0;

  // -----------------------------------------------------------------------------------
  QList <QString> objectList; objectList << "Box" << "Sphere" << "Cylinder" << "Cone" << "Ring" << "File" << "Checkpoint" << "OSU LWF" << "OSU DWB" << "UW WASIRF" << "WU TWB" << "USGS DFF" << "NICHE" << "Custom" << "Generative AI";
  objectType = new SC_ComboBox("object_type", objectList);
  layout->addWidget(new QLabel("Object Type"), numRow, 0, 1, 1, Qt::AlignRight);
  layout->addWidget(objectType,numRow++, 1, 1, 3);
  layout->itemAt(layout->count()-1)->widget()->setMaximumWidth(maxWidth);


  // -----------------------------------------------------------------------------------
  theGenAI = new GeometryAI();
  layout->addWidget(theGenAI, numRow++, 0, 1, 5);  
  theGenAI->hide(); // Hide the AI widget until object type is "Generative AI"
  // -----------------------------------------------------------------------------------


  QList <QString> operationList;  operationList << "Add (OR)" << "Subtract (NOT)" << "Intersect (AND)" << "Difference (XOR)";
  operationType = new SC_ComboBox("operation_type", operationList);
  layout->addWidget(new QLabel("Operation On Prior Geometry"), numRow, 0, 1, 1, Qt::AlignRight);
  layout->addWidget(operationType, numRow++, 1, 1, 3);
  layout->itemAt(layout->count()-1)->widget()->setMaximumWidth(maxWidth);

  operationType->setItemIcon(0, QIcon(QString(":/icons/union-black.svg")));
  operationType->setItemIcon(1, QIcon(QString(":/icons/subtract-black.svg")));
  operationType->setItemIcon(2, QIcon(QString(":/icons/intersect-black.svg")));
  operationType->setItemIcon(3, QIcon(QString(":/icons/difference-black.svg")));


  originX = new SC_DoubleLineEdit("origin_x", 0.0);
  originY = new SC_DoubleLineEdit("origin_y", 0.0);
  originZ = new SC_DoubleLineEdit("origin_z", 0.0);
  layout->addWidget(new QLabel("Origin (X,Y,Z)"), numRow, 0, 1, 1, Qt::AlignRight);  
  layout->addWidget(originX, numRow, 1, 1, 1);
  layout->addWidget(originY, numRow, 2, 1, 1);
  layout->addWidget(originZ, numRow, 3, 1, 1);
  layout->addWidget(new QLabel("m"), numRow++, 4, 1, 1);  

  length = new SC_DoubleLineEdit("span_x", 84.0);  
  height = new SC_DoubleLineEdit("span_y", 4.6);  
  width = new SC_DoubleLineEdit("span_z", 3.65);
  layout->addWidget(new QLabel("Dimensions (X,Y,Z)"), numRow, 0, 1, 1, Qt::AlignRight);
  layout->addWidget(length, numRow, 1, 1, 1);  
  layout->addWidget(height, numRow, 2, 1, 1);  
  layout->addWidget(width, numRow, 3, 1, 1);  
  layout->addWidget(new QLabel("m"), numRow++, 4, 1, 1);

  radius = new SC_DoubleLineEdit("radius", 0.0);
  radius->setEnabled(false);
  layout->addWidget(new QLabel("Radius"), numRow, 0, 1, 1, Qt::AlignRight);
  layout->addWidget(radius, numRow, 1, 1, 3);
  layout->itemAt(layout->count()-1)->widget()->setMaximumWidth(maxWidth);
  layout->addWidget(new QLabel("m"), numRow++, 4, 1, 1);

  QStringList longAxisList; longAxisList << "" << "X" << "Y" << "Z";
  longAxis = new SC_ComboBox("long_axis", longAxisList);
  longAxis->setEnabled(false);
  layout->addWidget(new QLabel("Long Axis"), numRow, 0, 1, 1, Qt::AlignRight);  
  layout->addWidget(longAxis, numRow++, 1, 1, 3);
  layout->itemAt(layout->count()-1)->widget()->setMaximumWidth(maxWidth);




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
  arrayBoxLayout->addWidget(new QLabel("Array Elements (X,Y,Z)"), numArrayRow, 0);
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
  rotateBoxLayout->addWidget(new QLabel("Rotation Angles (X,Y,Z)"), numRotateRow, 0);
  rotateBoxLayout->itemAt(rotateBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  rotateBoxLayout->addWidget(rotateAngleX, numRotateRow, 1);
  rotateBoxLayout->addWidget(rotateAngleY, numRotateRow, 2);
  rotateBoxLayout->addWidget(rotateAngleZ, numRotateRow, 3);
  rotateBoxLayout->addWidget(new QLabel("deg."), numRotateRow++, 4);

  rotateFulcrumX = new SC_DoubleLineEdit("fulcrum_x",0.0);  
  rotateFulcrumY = new SC_DoubleLineEdit("fulcrum_y",0.0);  
  rotateFulcrumZ = new SC_DoubleLineEdit("fulcrum_z",0.0);
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
  dimensionsBoxLayout->addWidget(new QLabel("Still Water Level (SWL)"), numDimRow, 0);
  dimensionsBoxLayout->itemAt(dimensionsBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  dimensionsBoxLayout->addWidget(standingWaterLevel, numDimRow, 1);  
  dimensionsBoxLayout->addWidget(new QLabel("m"), numDimRow++, 2);

  fillFlumeUptoSWL = new SC_CheckBox("fillFlumeUptoSWL");
  dimensionsBoxLayout->addWidget(new QLabel("Fill flume to SWL with fluid?"),numDimRow, 0);  
  dimensionsBoxLayout->itemAt(dimensionsBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  dimensionsBoxLayout->addWidget(fillFlumeUptoSWL,numDimRow++, 1);
  
  int numBathRow = 0;
  dimensionsBoxLayout->addWidget(new QLabel("Flume Bathymetry Type"),numDimRow,0);
  dimensionsBoxLayout->itemAt(dimensionsBoxLayout->count()-1)->setAlignment(Qt::AlignRight);

  QStringList bathOptions; bathOptions << "Point List" << "STL File";
  bathymetryComboBox = new SC_ComboBox("bathymetryComboBox", bathOptions);
  dimensionsBoxLayout->addWidget(bathymetryComboBox, numDimRow++, 1);
  QStringList bathXZHeadings; bathXZHeadings << "Joint Position (X)" << "Joint Position (Y)";
  QStringList dataBathXZ; dataBathXZ<< "0.0" << "0.0" 
                 << "16.275" << "0.226" 
                 << "19.933" << "0.226" 
                 << "30.906" << "1.140" 
                 << "45.536" << "1.750" 
                 << "82.106" << "1.750" 
                 << "89.46"  << "2.363";
  bathXZData = new SC_TableEdit("bathXZData", bathXZHeadings, 7, dataBathXZ);
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
  
  dimensionsBoxLayout->addWidget(bathStack,numDimRow++,0, 1, numBathRow);
  dimensionsBoxLayout->setRowStretch(numDimRow,1);
  layout->addWidget(dimensionsBox,numRow++,0,numDimRow,5);
  numRow = numRow+numDimRow;

  QStringList trackerHeadings; trackerHeadings << "1st" << "2nd" << "3rd" << "4th" << "5th";
  QStringList trackerData; trackerData << "0" << "" << "" << "" << "";
  trackerTable = new SC_TableEdit("trackerTable", trackerHeadings, 1, trackerData);
  layout->addWidget(new QLabel("Identify Particle IDs to Place Trackers On"), numRow++, 1, 1, 3);
  layout->addWidget(trackerTable, numRow++, 0, 1, 5);
  
  // numRow = numRow+1; // check


  layout->setRowStretch(numRow, 1);

  this->setLayout(layout);


  connect(bathymetryComboBox, &QComboBox::currentTextChanged, [=](QString val) {
    if (val == "Point List") {
      bathStack->setCurrentIndex(0);
      bathXZData->show();
      bathXZData->setVisible(true);
      bathXZData->setEnabled(true);
      ptWidget->show();
      ptWidget->setEnabled(true);
      ptWidget->setVisible(true);
      stlWidget->hide();
      stlWidget->setEnabled(false);
      stlWidget->setVisible(false);
    } else if (val == "STL File") {
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
      facilityLength->setText("84.0");
      facilityHeight->setText("4.6");
      facilityWidth->setText("3.65");
      if (bodyPreset->currentText() == "Fluid") {
        objectType->setCurrentText("OSU LWF");
      }
      QStringList newDataBathXZ; newDataBathXZ << "0.0" << "0.0" 
                 << "16.275" << "0.226" 
                 << "19.933" << "0.226" 
                 << "30.906" << "1.140" 
                 << "45.536" << "1.750" 
                 << "82.106" << "1.750" 
                 << "89.46"  << "2.363";
      delete bathXZData; bathXZData = new SC_TableEdit("bathXZData",bathXZHeadings, 7, newDataBathXZ);
      ptLayout->addWidget(bathXZData, 0, 0);
    } else if (val == "Hinsdale Directional Wave Basin (OSU DWB)") {
      facilityLength->setText("48.8");
      facilityHeight->setText("2.1");
      facilityWidth->setText("26.5");
      if (bodyPreset->currentText() == "Fluid") {
        objectType->setCurrentText("OSU DWB");
      }
      QStringList newDataBathXZ; newDataBathXZ << "0.00" << "0.0" 
                 << "11.0" << "0.0" 
                 << "31.0" << "1.0" 
                 << "45.0" << "1.0"
                 << "45.0" << "0.0" 
                 << "48.8" << "0.0";
      delete bathXZData; bathXZData = new SC_TableEdit("bathXZData",bathXZHeadings, 6, newDataBathXZ);
      ptLayout->addWidget(bathXZData, 0, 0);
    } else if (val == "Wind-Air-Sea Interaction Facility (UW WASIRF)") {
      facilityLength->setText("12.19");
      facilityHeight->setText("1.22");
      facilityWidth->setText("0.914");
      if (bodyPreset->currentText() == "Fluid") {
        objectType->setCurrentText("UW WASIRF");
      }
      QStringList newDataBathXZ; newDataBathXZ << "0.00" << "0.0" 
                 << "12.0" << "0.0";
      delete bathXZData; bathXZData = new SC_TableEdit("bathXZData",bathXZHeadings, 2, newDataBathXZ);
      ptLayout->addWidget(bathXZData, 0, 0);
    } else if (val == "Waseda University's Tsunami Wave Basin (WU TWB)") {
      facilityLength->setText("9.0");
      facilityHeight->setText("1.0");
      facilityWidth->setText("4.0");
      if (bodyPreset->currentText() == "Fluid") {
        objectType->setCurrentText("WU TWB");
      }
      QStringList newDataBathXZ; newDataBathXZ << "0.00" << "0" 
                 << "4.45" << "0" 
                 << "4.45" << "0.255" 
                 << "9.00" << "0.255";
      delete bathXZData; bathXZData = new SC_TableEdit("bathXZData",bathXZHeadings, 4, newDataBathXZ);
      ptLayout->addWidget(bathXZData, 0, 0);
    } else if (val == "U.S. Geo. Survey's Debris Flow Flume (USGS DFF)") {
      facilityLength->setText("90.0");
      facilityHeight->setText("2.0");
      facilityWidth->setText("2.0");
      if (bodyPreset->currentText() == "Fluid") {
        objectType->setCurrentText("USGS DFF");
      }
      QStringList newDataBathXZ; newDataBathXZ << "0.00"  << "0.0" // Top of flume, or soil mass ?
                 << "7.00"  << "0.0" // Gate ?
                 << "80.00" << "0.0" // Bottom of initial flume slope, prior to catanary
                 << "81.00" << "0.176" // 10 deg, 1:0.176 (ASSUME CATANARY JOINT AS LINEAR SEGMENTS TO FLATTEN 30DEG SLOPE REL TO ROTATED GRAVITY VECTOR)
                 << "82.00" << "0.540" // 20 deg, 1:0.364
                 << "100.0" << "10.926"; // 30deg, 1:0.577 
      delete bathXZData; bathXZData = new SC_TableEdit("bathXZData",bathXZHeadings, 6, newDataBathXZ);
      ptLayout->addWidget(bathXZData, 0, 0);
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

  connect(objectType, &QComboBox::currentTextChanged, [=](QString val) {
    if (val == "Box") {
      length->setEnabled(true);
      length->show();
      height->setEnabled(true);
      height->show();
      width->setEnabled(true);
      width->show();
      radius->setDisabled(true);
      radius->clear();
      longAxis->setDisabled(true);
      longAxis->setCurrentText("");
      // radius->hide();
      // longAxis->hide();
      length->setText("1.0");
      height->setText("1.0");
      width->setText("1.0");
    } else if (val == "Sphere") {
      length->setDisabled(true);
      // length->hide();
      height->setDisabled(true);
      // height->hide();
      width->setDisabled(true);
      // width->hide();
      radius->setEnabled(true);
      radius->show();
      longAxis->setDisabled(true);
      longAxis->setCurrentText("");
      // longAxis->hide();
      radius->setText("0.5");
    } else if (val == "Cylinder") {
      length->setEnabled(true);
      length->show();
      height->setDisabled(true);
      // height->hide();
      width->setDisabled(true);
      // width->hide();
      radius->setEnabled(true);
      radius->show();
      longAxis->setEnabled(true);
      longAxis->show();
      length->setText("1.0");
      radius->setText("0.5");
      longAxis->setCurrentText("X");
    } else if (val == "Cone") {
      length->setEnabled(true);
      length->show();
      height->setDisabled(true);
      // height->hide();
      width->setDisabled(true);
      // width->hide();
      radius->setEnabled(true);
      radius->show();
      longAxis->setEnabled(true);
      longAxis->show();
      length->setText("1.0");
      radius->setText("0.5");
      longAxis->setCurrentText("X");
    } else if (val == "Ring") {
      length->setEnabled(true);
      length->show();
      height->setDisabled(true);
      // height->hide();
      width->setDisabled(true);
      // width->hide();
      radius->setEnabled(true);
      radius->show();
      longAxis->setEnabled(true);
      longAxis->show();
      width->setText("0.25");
      radius->setText("0.5");
      longAxis->setCurrentText("X");
    } else if (val == "File") {
      length->setEnabled(true);
      length->show();
      height->setEnabled(true);
      height->show();
      width->setEnabled(true);
      width->show();
      length->setText("1.0");
      height->setText("1.0");
      width->setText("1.0");
      radius->setDisabled(true);
      radius->clear();
      longAxis->setDisabled(true);
      longAxis->setCurrentText("");
      // radius->hide();
      // longAxis->hide();
    } else if (val == "Checkpoint") {
      length->setDisabled(true);
      // length->hide();
      height->setDisabled(true);
      // height->hide();
      width->setDisabled(true);
      // width->hide();
      radius->setDisabled(true);
      longAxis->setDisabled(true);
      // radius->hide();
      // longAxis->hide();
    } else if (val == "OSU LWF") {
      facility->setCurrentText("Hinsdale Large Wave Flume (OSU LWF)");
      length->setEnabled(true);
      length->show();
      height->setEnabled(true);
      height->show();
      width->setEnabled(true);
      width->show();
      radius->setDisabled(true);
      radius->clear();
      longAxis->setDisabled(true);
      longAxis->setCurrentText("");
      // radius->hide();
      // longAxis->hide();
      if (bodyPreset->currentText() == "Fluid") {
        length->setText("84.0");
        height->setText("2.0");
        width->setText("3.65");
        originX->setText("1.9");
        originY->setText("0.0");
        originZ->setText("0.0");
      }
    } else if (val == "OSU DWB") {
      facility->setCurrentText("Hinsdale Directional Wave Basin (OSU DWB)");
      length->setEnabled(true);
      length->show();
      height->setEnabled(true);
      height->show();
      width->setEnabled(true);
      width->show();
      radius->setDisabled(true);
      radius->clear();
      longAxis->setDisabled(true);
      longAxis->setCurrentText("");
      // radius->hide();
      // longAxis->hide();
      if (bodyPreset->currentText() == "Fluid") {
        length->setText("48.8");
        height->setText("0.87");
        width->setText("26.5");
        originX->setText("0.0");
        originY->setText("0.0");
        originZ->setText("0.0");
      }
    } else if (val == "UW WASIRF") {
      facility->setCurrentText("Wind-Air-Sea Interaction Facility (UW WASIRF)");
      length->setEnabled(true);
      length->show();
      height->setEnabled(true);
      height->show();
      width->setEnabled(true);
      width->show();
      radius->setDisabled(true);
      radius->clear();
      longAxis->setDisabled(true);
      longAxis->setCurrentText("");
      // radius->hide();
      // longAxis->hide();
      if (bodyPreset->currentText() == "Fluid") {
        length->setText("12.19");
        height->setText("0.2");
        width->setText("0.914");
        originX->setText("0.0");
        originY->setText("0.0");
        originZ->setText("0.0");
      }
    } else if (val == "WU TWB") {
      facility->setCurrentText("Waseda University's Tsunami Wave Basin (WU TWB)");
      length->setEnabled(true);
      length->show();
      height->setEnabled(true);
      height->show();
      width->setEnabled(true);
      width->show();
      radius->setDisabled(true);
      radius->clear();
      longAxis->setDisabled(true);
      longAxis->setCurrentText("");
      // radius->hide();
      // longAxis->hide();
      if (bodyPreset->currentText() == "Fluid") {
        length->setText("9.0");
        height->setText("0.23");
        width->setText("4.0");
        originX->setText("0.0");
        originY->setText("0.0");
        originZ->setText("0.0");
      }
    } else if (val == "USGS DFF") {
      facility->setCurrentText("U.S. Geo. Survey's Debris Flow Flume (USGS DFF)");
      length->setEnabled(true);
      length->show();
      height->setEnabled(true);
      height->show();
      width->setEnabled(true);
      width->show();
      radius->setDisabled(true);
      radius->clear();
      longAxis->setDisabled(true);
      longAxis->setCurrentText("");
      // radius->hide();
      // longAxis->hide();
      if (bodyPreset->currentText() == "Fluid") {
        length->setText("90.0");
        height->setText("2.0");
        width->setText("2.0");
        originX->setText("0.0");
        originY->setText("0.0");
        originZ->setText("0.0");
      }
    } else if (val == "NICHE") {
      facility->setCurrentText("NICHE Full-Scale Wind-Wave Flume");
      length->setEnabled(true);
      length->show();
      height->setEnabled(true);
      height->show();
      width->setEnabled(true);
      width->show();
      radius->setDisabled(true);
      radius->clear();
      longAxis->setDisabled(true);
      longAxis->setCurrentText("");
      // radius->hide();
      // longAxis->hide();
      if (bodyPreset->currentText() == "Fluid") {
        length->setText("300.0");
        height->setText("10.0");
        width->setText("100.0");
        originX->setText("0.0");
        originY->setText("0.0");
        originZ->setText("0.0");
      }
    } else if (val == "Custom") {
      length->setEnabled(true);
      length->show();
      height->setEnabled(true);
      height->show();
      width->setEnabled(true);
      width->show();
      radius->setDisabled(true);
      radius->clear();
      longAxis->setDisabled(true);
      longAxis->setCurrentText("");
      // radius->hide();
      // longAxis->hide();
    } else if (val == "Generative AI") {
      length->setEnabled(true);
      length->show();
      height->setEnabled(true);
      height->show();
      width->setEnabled(true);
      width->show();
      radius->setDisabled(true);
      radius->clear();
      longAxis->setDisabled(true);
      longAxis->setCurrentText("");
    }


    // if else specifically for generative AI
    if (val == "Generative AI") {
      theGenAI->show();
      theGenAI->setVisible(true);
    } else {
      theGenAI->hide();
      theGenAI->setVisible(false);
    }

  });

  connect(bodyPreset, &QComboBox::currentTextChanged, [=](QString val) {
    if (val == "Fluid") {
      length->setText("84.0");
      height->setText("2.0");
      width->setText("3.65");
      originX->setText("1.9"); // wave-maker paddle neutral at OSU LWF
      originY->setText("0.0");
      originZ->setText("0.0");
      applyArray->setChecked(false);

      facility->setCurrentText("Hinsdale Large Wave Flume (OSU LWF)");
      facilityLength->setText("104.0");
      facilityHeight->setText("4.6");
      facilityWidth->setText("3.658");
      standingWaterLevel->setEnabled(true);
      standingWaterLevel->show();
      standingWaterLevel->setText("2.0");
      fillFlumeUptoSWL->setEnabled(true);
      fillFlumeUptoSWL->setChecked(true);
      fillFlumeUptoSWL->show();
      bathStack->setCurrentIndex(0);
      bathStack->show();
      bathStack->setEnabled(true);
      bathymetryComboBox->setEnabled(true);
      bathymetryComboBox->show();
      bathSTL->setEnabled(true);
      dimensionsBox->show();
    } else if (val == "Debris") {
      facility->setCurrentText("Hinsdale Large Wave Flume (OSU LWF)");
      standingWaterLevel->setDisabled(true);
      // standingWaterLevel->hide();
      fillFlumeUptoSWL->setChecked(false);
      fillFlumeUptoSWL->setDisabled(true);
      // fillFlumeUptoSWL->hide();
      length->setText("0.5");
      height->setText("0.05");
      width->setText("0.1");
      originX->setText("43.8");
      originY->setText("2.0");
      originZ->setText("1.325");
      applyArray->setChecked(true);
      bathStack->setCurrentIndex(1);
      bathStack->hide();
      bathStack->setDisabled(true);
      bathymetryComboBox->setDisabled(true);
      bathymetryComboBox->hide();
      bathSTL->setDisabled(true);
      dimensionsBox->hide();
    } else if (val == "Structure") {
      facility->setCurrentText("Hinsdale Large Wave Flume (OSU LWF)");
      standingWaterLevel->setDisabled(true);
      // standingWaterLevel->hide();
      fillFlumeUptoSWL->setChecked(false);
      fillFlumeUptoSWL->setDisabled(true);
      // fillFlumeUptoSWL->hide();
      length->setText("1.0");
      height->setText("0.625");
      width->setText("1.0");
      originX->setText("45.8");
      originY->setText("2.10"); // 2.0 + buffer
      originZ->setText("1.325");
      applyArray->setChecked(true);
      bathStack->setCurrentIndex(1);
      bathStack->hide();
      bathStack->setDisabled(true);
      bathymetryComboBox->setDisabled(true);
      bathymetryComboBox->hide();
      bathSTL->setDisabled(true);
      dimensionsBox->hide();
    } else if (val == "Custom") {
      facility->setCurrentText("Custom");
      standingWaterLevel->setDisabled(true);
      // standingWaterLevel->hide();
      fillFlumeUptoSWL->setChecked(false);
      fillFlumeUptoSWL->setDisabled(true);
      // fillFlumeUptoSWL->hide();
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
      dimensionsBox->hide();
    }
  });
  // Refresh SWL and geometry height when checkbox is toggled
  connect(fillFlumeUptoSWL, &QCheckBox::stateChanged, [=](int state) {
    if (state == 2) {
      standingWaterLevel->setEnabled(true);
      if (standingWaterLevel->text().toDouble() > facilityHeight->text().toDouble()) {
        standingWaterLevel->setText(facilityHeight->text());
      } else if (standingWaterLevel->text().toDouble() < 0.0) {
        standingWaterLevel->setText("0.0");
      }
      double bounded_swl = (standingWaterLevel->text().toDouble() - originY->text().toDouble()) > 0.0 
                                  ? (standingWaterLevel->text().toDouble() - originY->text().toDouble()) 
                                  : 0.0;
      height->setText(QString::number(bounded_swl));
    } else {
      standingWaterLevel->setDisabled(true);
    }
  });
  // Refresh geometry height when SWL is changed and fill flume up to SWL is checked
  connect(standingWaterLevel, &QLineEdit::textChanged, [=](QString val) {
    if (fillFlumeUptoSWL->isChecked() && fillFlumeUptoSWL->isEnabled()) {
      if (val.toDouble() > facilityHeight->text().toDouble()) {
        standingWaterLevel->setText(facilityHeight->text());
      } else if (val.toDouble() < 0.0) {
        standingWaterLevel->setText("0.0");
      }
      double bounded_swl = (standingWaterLevel->text().toDouble() - originY->text().toDouble()) > 0.0 
                                  ? (standingWaterLevel->text().toDouble() - originY->text().toDouble()) 
                                  : 0.0;
      height->setText(QString::number(bounded_swl));
    }
  });
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
  } else if (bodyPreset->currentText() == "Generative AI") {
    objectType->setCurrentText("Generative AI");
    applyArray->setChecked(false);
    applyRotation->setChecked(false);
  }
  // Should probably make this a function, it checks array spacing vs dimensions
  if (applyArray->isChecked()) {
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
  
  if (trackerTable->isEnabled()) {
    QJsonObject trackerObject;
    trackerTable->outputToJSON(trackerObject);
    QJsonArray trackerArray;
    for (int i = 0; i < trackerObject["trackerTable"].toArray().size(); i++) {
      QJsonArray temp_array = trackerObject["trackerTable"].toArray()[i].toArray();
      for (int j = 0; j < temp_array.size(); j++) {
        if (temp_array[j].toString().isEmpty() == false) continue; 
        temp_array.removeAt(j);
        j--;
      }
      if (temp_array.size() == 0) temp_array.append("0");
      trackerArray.append(temp_array);
    }
    // TODO : Merge all internal arrays into single array
    geometryObject["track_particle_id"] = trackerArray[0].toArray();
  } else {
    geometryObject["track_particle_id"] = QJsonArray() << "0";
  }


  if (geometryObject["track_particle_id"].toArray().size() <= 0 ) {
    geometryObject["track_particle_id"] = QJsonArray() << "0";
  }
  
  jsonObject["geometry"] = geometryObject;
  if (jsonObject.find("track_particle_id") == jsonObject.end()) 
    jsonObject["track_particle_id"] = QJsonArray() << "0";
  else if (jsonObject.find("track_particle_id") != jsonObject.end() && jsonObject["track_particle_id"].toArray().size() < 1)
    jsonObject["track_particle_id"] =  QJsonArray() << "0";
  

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

bool
GeometryMPM::setDigitalTwin(int twinIdx) 
{
  // Way to set the digital twin from higher levels,
  // e.g. to set the geometry digital twin to "Hinsdale Large Wave Flume (OSU LWF)" if the user selects the OSU LWF digital twin
  if (twinIdx < 0 || twinIdx > facility->count()) {
    // QDebug() << "Error: Invalid digital twin index";
    return false;
  }
  facility->setCurrentIndex(twinIdx);
  // Default Fluid template to OSU LWF water object

  if (bodyPreset->currentText() == "Fluid") {
    if (twinIdx == 0) { // OSU LWF
      fillFlumeUptoSWL->setChecked(true);
      standingWaterLevel->setText("2.0");
    } else if (twinIdx == 1) { // OSU DWB
      fillFlumeUptoSWL->setChecked(true);
      standingWaterLevel->setText("0.87");
    } else if (twinIdx == 2) { // UW WASIRF
      fillFlumeUptoSWL->setChecked(true);
      standingWaterLevel->setText("0.2"); // Recheck Nikki's SWLs
    } else if (twinIdx == 3) { // WU TWB
      fillFlumeUptoSWL->setChecked(true);
      standingWaterLevel->setText("0.23");
    } else if (twinIdx == 4) { // USGS DFF
      fillFlumeUptoSWL->setChecked(false);
      standingWaterLevel->setText("0.0");
    } 
  } else if (bodyPreset->currentText() == "Debris") {
    if (twinIdx == 0) { // OSU LWF
      objectType->setCurrentIndex(0); // Just boxes for now, don't swap yet
      length->setText(QString::number(0.5));
      height->setText(QString::number(0.05));
      width->setText(QString::number(0.1));
      originX->setText(QString::number(42.8));
      originY->setText(QString::number(2.0));
      originZ->setText(QString::number(1.475));
      applyArray->setChecked(true);
      spacingX->setText(QString::number(0.6));
      spacingY->setText(QString::number(0.05));
      spacingZ->setText(QString::number(0.2));
      arrayX->setText(QString::number(2));
      arrayY->setText(QString::number(1));
      arrayZ->setText(QString::number(4));
    }
    else if (twinIdx == 1) { // OSU DWB
      objectType->setCurrentIndex(0); 
      length->setText(QString::number(0.10));
      height->setText(QString::number(0.05));
      width->setText(QString::number(0.10));
      originX->setText(QString::number(31.29));
      originY->setText(QString::number(1.0));
      originZ->setText(QString::number(0.4));
      applyArray->setChecked(true);
      spacingX->setText(QString::number(0.15));
      spacingY->setText(QString::number(0.0));
      spacingZ->setText(QString::number(0.15));
      arrayX->setText(QString::number(4));
      arrayY->setText(QString::number(1));
      arrayZ->setText(QString::number(5));
    }
    else if (twinIdx == 2) { // UW WASIRF
      objectType->setCurrentIndex(0); 
      length->setText(QString::number(0.1016));
      height->setText(QString::number(0.0254));
      width->setText(QString::number(0.0254));
      // TODO: Recheck specs of the debris from Nikkis work (4x1x1"?)
      originX->setText(QString::number(4.0)); 
      originY->setText(QString::number(0.2)); // Recheck the height
      originZ->setText(QString::number(0.5873));
      applyArray->setChecked(false);
      spacingX->setText(QString::number(0.1016));
      spacingY->setText(QString::number(0.0254));
      spacingZ->setText(QString::number(0.0254));
      arrayX->setText(QString::number(1));
      arrayY->setText(QString::number(1));
      arrayZ->setText(QString::number(1));
    }
    else if (twinIdx == 3) { // WU TWB
      objectType->setCurrentIndex(0); 
      length->setText(QString::number(0.06));
      height->setText(QString::number(0.06));
      width->setText(QString::number(0.15));
      originX->setText(QString::number(5.05)); //Recheck
      originY->setText(QString::number(0.255)); // Recheck the height
      originZ->setText(QString::number(1.725));
      applyArray->setChecked(true);
      spacingX->setText(QString::number(0.09));
      spacingY->setText(QString::number(0.09));
      spacingZ->setText(QString::number(0.18));
      arrayX->setText(QString::number(1));
      arrayY->setText(QString::number(2));
      arrayZ->setText(QString::number(3));
    }
    else if (twinIdx == 4) { // USGS DFF
      // Placeholder structure 
      objectType->setCurrentIndex(0); // Box?
      length->setText(QString::number(0.5));
      height->setText(QString::number(0.05));
      width->setText(QString::number(0.1));
      originX->setText(QString::number(2.0));
      originY->setText(QString::number(2.0));
      originZ->setText(QString::number(0.65));
      applyArray->setChecked(true);
      spacingX->setText(QString::number(0.6));
      spacingY->setText(QString::number(0.0));
      spacingZ->setText(QString::number(0.2));
      arrayX->setText(QString::number(2));
      arrayY->setText(QString::number(1));
      arrayZ->setText(QString::number(4));
      //Need to rotate these as well due to grav vector and sloped soil mass

    }

  } else if (bodyPreset->currentText() == "Structure") {
    // objectType->setCurrentText("Box");
    //TODO: Add structure presets
    // TODO: Force constency for rigid/non-rigid selection of structure
  } else if (bodyPreset->currentText() == "Custom") {
    // Do nothing
  } else if (bodyPreset->currentText() == "Generative AI") {
      objectType->setCurrentText("Generative AI");
      length->setText(QString::number(1.0));
      height->setText(QString::number(1.0));
      width->setText(QString::number(1.0));
      originX->setText(QString::number(0.5));
      originY->setText(QString::number(0.5));
      originZ->setText(QString::number(0.5));
      applyArray->setChecked(false);
      spacingX->setText(QString::number(1.5));
      spacingY->setText(QString::number(1.5));
      spacingZ->setText(QString::number(1.5));
      arrayX->setText(QString::number(1));
      arrayY->setText(QString::number(1));
      arrayZ->setText(QString::number(1));
      applyRotation->setChecked(false);
      rotateAngleX->setText(QString::number(0.0));
      rotateAngleY->setText(QString::number(0.0));
      rotateAngleZ->setText(QString::number(0.0));
      rotateFulcrumX->setText(QString::number(1.0));
      rotateFulcrumY->setText(QString::number(1.0));
      rotateFulcrumZ->setText(QString::number(1.0));
      operationType->setCurrentText("Add (OR)");
      radius->setText(QString::number(0.0));
      longAxis->setCurrentText("");
  }
  return true;
}

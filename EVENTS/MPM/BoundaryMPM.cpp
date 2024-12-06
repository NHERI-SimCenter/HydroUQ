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

#include "BoundaryMPM.h"
#include <QLabel>
#include <QComboBox>
#include <QGroupBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QStackedWidget>
#include <QDebug>
#include <QIcon>
#include <QSvgWidget>
#include <QString> 
#include <QJsonObject>
#include <QJsonArray>
#include <QLineEdit>
#include <SC_ComboBox.h>
#include <SC_DoubleLineEdit.h>
#include <SC_IntLineEdit.h>
#include <SC_TableEdit.h>
#include <SC_FileEdit.h>
#include <SC_CheckBox.h>

#include <stdexcept>
#include <QPixmap>



// For 2d graphing like in RV distributions 
#include <QLineEdit>
#include <QDoubleValidator>
#include <SimCenterGraphPlot.h>
#include <math.h>
#include <QPushButton>
#include <QFileDialog>

BoundaryMPM::BoundaryMPM(QWidget *parent)
  :SimCenterWidget(parent)
{

  QGridLayout *layout = new QGridLayout();
  this->setLayout(layout);

  // QPushButton *showPlotButton = NULL;
  QString inpType = QString("Preset Paddle - OSU LWF"); // Default wave generation method
  this->inpty=inpType;

  stackedWidget = new QStackedWidget();
  theCustom = new QWidget();
  theWaveFlume = new QWidget();
  theWaveGeneration = new QWidget();
  theStructures = new QWidget();
  theWalls = new QWidget();

  boundaryType = new SC_ComboBox("boundaryPreset", QStringList() << "Custom" << "Flume Facility" << "Wave Generator" << "Rigid Structures" << "Rigid Walls");
  layout->addWidget(new QLabel("Boundary Preset"));
  layout->addWidget(boundaryType);
  layout->addWidget(stackedWidget);

  stackedWidget->addWidget(theCustom);
  stackedWidget->addWidget(theWaveFlume);
  stackedWidget->addWidget(theWaveGeneration);
  stackedWidget->addWidget(theStructures);
  stackedWidget->addWidget(theWalls);

  connect(boundaryType, QOverload<int>::of(&QComboBox::activated),
    stackedWidget, &QStackedWidget::setCurrentIndex);


  QGridLayout *customLayout = new QGridLayout();
  QGridLayout *waveFlumeLayout = new QGridLayout();
  QGridLayout *theWaveGenLayout = new QGridLayout();
  QGridLayout *structLayout = new QGridLayout();
  QGridLayout *wallsLayout = new QGridLayout();
  theCustom->setLayout(customLayout);
  theWaveFlume->setLayout(waveFlumeLayout);  
  theWaveGeneration->setLayout(theWaveGenLayout);
  theStructures->setLayout(structLayout);
  theWalls->setLayout(wallsLayout);

  QGroupBox *dimensionsBox = new QGroupBox("Flume Facility Dimensions");
  QGridLayout *dimensionsBoxLayout = new QGridLayout();

  int numRow = 0;  
  flumeLength = new SC_DoubleLineEdit("flumeLength",104.0);  
  flumeHeight = new SC_DoubleLineEdit("flumeHeight",4.6);  
  flumeWidth = new SC_DoubleLineEdit("flumeWidth",3.658);
  dimensionsBoxLayout->addWidget(new QLabel("Dimensions (X,Y,Z)"), numRow, 0);
  dimensionsBoxLayout->itemAt(dimensionsBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  dimensionsBoxLayout->addWidget(flumeLength, numRow, 1);    
  dimensionsBoxLayout->addWidget(flumeHeight, numRow, 2);  
  dimensionsBoxLayout->addWidget(flumeWidth, numRow, 3);  
  dimensionsBoxLayout->addWidget(new QLabel("m"), numRow++, 4);

  flumeOriginX = new SC_DoubleLineEdit("flumeOriginX",0.0);
  flumeOriginY = new SC_DoubleLineEdit("flumeOriginY",0.0);
  flumeOriginZ = new SC_DoubleLineEdit("flumeOriginZ",0.0);
  dimensionsBoxLayout->addWidget(new QLabel("Origin (X,Y,Z)"), numRow, 0);  
  dimensionsBoxLayout->itemAt(dimensionsBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  dimensionsBoxLayout->addWidget(flumeOriginX, numRow, 1);
  dimensionsBoxLayout->addWidget(flumeOriginY, numRow, 2);
  dimensionsBoxLayout->addWidget(flumeOriginZ, numRow, 3);
  dimensionsBoxLayout->addWidget(new QLabel("m"), numRow++, 4);  
  dimensionsBoxLayout->setRowStretch(numRow,1);
  dimensionsBox->setLayout(dimensionsBoxLayout);


  numRow = 0;
  // QGroupBox *bathBox = new QGroupBox("");
  // QGridLayout *bathBoxLayout = new QGridLayout();
  // bathBox->setLayout(bathBoxLayout);
  // QStringList bathXZHeadings; bathXZHeadings << "Position in Flume (X)" << "Elevation (Y)";
  // QStringList dataBathXZ; dataBathXZ << "35" << "0" << "42" << "1.75" << "56" << "2.5" << "105" << "2.5";
  // bathXZData = new SC_TableEdit("bathXZData",bathXZHeadings, 4, dataBathXZ);

  // bathBoxLayout->addWidget(new QLabel("Bathymetry Segments"),numRow++,0,1,4);    
  // bathBoxLayout->addWidget(bathXZData,numRow++,0,1,4);  
  // bathBoxLayout->setRowStretch(2,1);


  // Stack for bathymetry
  QStringList bathOptions; bathOptions << "Point List" << "STL File";
  bathymetryComboBox = new SC_ComboBox("bathType",bathOptions);
  
  QStringList bathXZHeadings; bathXZHeadings << "Joint Position (X)" << "Joint Position (Y)";
  QStringList dataBathXZ; dataBathXZ << "0" << "0" << "16.275" << "0.226" << "19.933" << "0.226" << "30.906" << "1.140" << "45.536" << "1.750" << "82.106" << "1.750" << "89.46" << "2.363";
  // wmn = 2 or 1.91 something for OSU LWF
  int bathXZPairs = 7;
  bathXZData = new SC_TableEdit("bathXZData",bathXZHeadings, bathXZPairs, dataBathXZ);
  bathSTL = new SC_FileEdit("bathSTL");
  QString bathFilename = QString("Examples/hdro-0001/src/flumeFloor.stl");
  bathSTL->setFilename(bathFilename);
  // bathSTL->setFilter("STL Files (*.stl)");

  QWidget *ptWidget = new QWidget(); // going to add figure which is why the layout
  QGridLayout *ptLayout = new QGridLayout();
  ptLayout->addWidget(bathXZData, 0, 0);
  ptLayout->setRowStretch(1,1);
  ptWidget->setLayout(ptLayout);

  QWidget *stlWidget = new QWidget();
  QGridLayout *stlLayout = new QGridLayout();
  stlLayout->addWidget(new QLabel("Surface File (stl)"),0,0);
  stlLayout->itemAt(stlLayout->count()-1)->setAlignment(Qt::AlignRight);
  stlLayout->addWidget(bathSTL,0,1);
  stlLayout->setRowStretch(1,1);  
  stlWidget->setLayout(stlLayout);

  QStackedWidget *bathStack = new QStackedWidget();
  bathStack->addWidget(ptWidget);
  bathStack->addWidget(stlWidget);
  //


  numRow = 0;
  // QStringList facilityList; facilityList << "Hinsdale Large Wave Flume - Oregon State University (OSU LWF)" << "Hinsdale Directional Wave Basin (OSU DWB)" <<  "Wind-Air-Sea Interaction Facility (UW WASIRF)" << "Waseda University's Tsunami Wave Basin (WU TWB)" << "U.S. Geo. Survey's Debris Flow Flume (USGS DFF)" << "CLOSED" << "INLETOUTLET";
  QStringList facilityList; facilityList << "Hinsdale Large Wave Flume (OSU LWF)" << "Hinsdale Directional Wave Basin (OSU DWB)" <<  "Wind-Air-Sea Interaction Facility (UW WASIRF)" << "Waseda University's Tsunami Wave Basin (WU TWB)" << "U.S. Geo. Survey's Debris Flow Flume (USGS DFF)";
  facility = new SC_ComboBox("domainSubType",facilityList);
  facility->setEnabled(false);
  waveFlumeLayout->addWidget(new QLabel("Digital Twin Facility"),numRow,0);
  waveFlumeLayout->itemAt(waveFlumeLayout->count()-1)->setAlignment(Qt::AlignRight);
  waveFlumeLayout->addWidget(facility,numRow++,1);

  waveFlumeLayout->addWidget(dimensionsBox,numRow++,0,2,5);
  numRow++; // Adjust for groupbox title
  waveFlumeLayout->addWidget(new QLabel("Source Bathymetry"),numRow,0);
  waveFlumeLayout->itemAt(waveFlumeLayout->count()-1)->setAlignment(Qt::AlignRight);
  waveFlumeLayout->addWidget(bathymetryComboBox,numRow++,1);
  waveFlumeLayout->addWidget(bathStack,numRow++,0,1,2);
  waveFlumeLayout->setRowStretch(numRow,1);

  // connext bathymetry to show correct widget
  connect(bathymetryComboBox, QOverload<int>::of(&QComboBox::activated),
	  bathStack, &QStackedWidget::setCurrentIndex);
  //
  // connect the facility QComboBox to change entries to default values if selected
  //
  
  connect(facility, &QComboBox::currentTextChanged, [=](QString val) {
    if (val == "Hinsdale Large Wave Flume (OSU LWF)") {
      flumeLength->setText("104.0");
      flumeHeight->setText("4.6");
      flumeWidth->setText("3.658");
      QStringList newDataBathXZ; newDataBathXZ << "0.0" << "0.0" 
                 << "16.275" << "0.226" 
                 << "19.933" << "0.226" 
                 << "30.906" << "1.140" 
                 << "45.536" << "1.750" 
                 << "82.106" << "1.750" 
                 << "89.46"  << "2.363";
      delete bathXZData;
      bathXZData = new SC_TableEdit("bathXZData",bathXZHeadings, 7, newDataBathXZ);
      ptLayout->addWidget(bathXZData, 0, 0);
    } else if (val == "Hinsdale Directional Wave Basin (OSU DWB)") {
      flumeLength->setText("48.8");
      flumeHeight->setText("2.1");
      flumeWidth->setText("26.5");      
      QStringList newDataBathXZ; newDataBathXZ << "0.00" << "0.0" 
                 << "11.0" << "0.0" 
                 << "31.0" << "1.0" 
                 << "45.0" << "1.0"
                 << "45.0" << "0.0" 
                 << "48.8" << "0.0";
      delete bathXZData;
      bathXZData = new SC_TableEdit("bathXZData",bathXZHeadings, 6, newDataBathXZ);
      ptLayout->addWidget(bathXZData, 0, 0);
    } else if (val == "Wind-Air-Sea Interaction Facility (UW WASIRF)") {
      flumeLength->setText("12.19");
      flumeHeight->setText("1.22");
      flumeWidth->setText("0.914");
      QStringList newDataBathXZ; newDataBathXZ << "0.00" << "0.0" 
                 << "12.0" << "0.0";
      delete bathXZData;
      bathXZData = new SC_TableEdit("bathXZData",bathXZHeadings, 2, newDataBathXZ);
      ptLayout->addWidget(bathXZData, 0, 0);
    } else if (val == "Waseda University's Tsunami Wave Basin (WU TWB)") {
      flumeLength->setText("9.0");
      flumeHeight->setText("1.0");
      flumeWidth->setText("4.0");
      QStringList newDataBathXZ; newDataBathXZ << "0.00" << "0" 
                 << "4.45" << "0" 
                 << "4.45" << "0.255" 
                 << "9.00" << "0.255";
      delete bathXZData;
      bathXZData = new SC_TableEdit("bathXZData",bathXZHeadings, 4, newDataBathXZ);
      ptLayout->addWidget(bathXZData, 0, 0);
    } else if (val == "U.S. Geo. Survey's Debris Flow Flume (USGS DFF)") {
      flumeLength->setText("90.0");
      flumeHeight->setText("2.0");
      flumeWidth->setText("2.0");
      QStringList newDataBathXZ; newDataBathXZ << "0.00"  << "0.0" // Top of flume, or soil mass ?
                 << "7.00"  << "0.0" // Gate ?
                 << "80.00" << "0.0" // Bottom of initial flume slope, prior to catanary
                 << "81.00" << "0.176" // 10 deg, 1:0.176 (ASSUME CATANARY JOINT AS LINEAR SEGMENTS TO FLATTEN 30DEG SLOPE REL TO ROTATED GRAVITY VECTOR)
                 << "82.00" << "0.540" // 20 deg, 1:0.364
                 << "100.0" << "10.926"; // 30deg, 1:0.577 
      delete bathXZData;
      bathXZData = new SC_TableEdit("bathXZData",bathXZHeadings, 6, newDataBathXZ);
      ptLayout->addWidget(bathXZData, 0, 0);
    } 
  });


  //
  // instead of more classes lets just do simple tabbed widgets
  //


  // wave generator
  numRow = 0;
  QStringList listWaveGeneration; listWaveGeneration << "Preset Paddle - OSU LWF" << "Periodic Waves" << "Preset Paddle - OSU DWB" ;
  generationMethod = new SC_ComboBox("generationMethod",listWaveGeneration);
  generationMethod->setEnabled(false);


  QStringList paddleContactTypeList; paddleContactTypeList <<  "Separable" << "Slip" << "Sticky";  
  paddleContactType = new SC_ComboBox("paddleContactType", paddleContactTypeList);

  QWidget *paddleWidget = new QWidget();
  QGridLayout *paddleLayout = new QGridLayout();
  paddleLayout->addWidget(new QLabel("Contact Type"),numRow, 0);
  paddleLayout->itemAt(paddleLayout->count()-1)->setAlignment(Qt::AlignRight);
  paddleLayout->addWidget(paddleContactType, numRow++, 1);  
  
  paddleLength = new SC_DoubleLineEdit("paddleLength", 0.2);
  paddleHeight = new SC_DoubleLineEdit("paddleHeight", 4.8);
  paddleWidth  = new SC_DoubleLineEdit("paddleWidth", 3.85);
  paddleLayout->addWidget(new QLabel("Dimensions (X,Y,Z)"),numRow, 0);
  paddleLayout->itemAt(paddleLayout->count()-1)->setAlignment(Qt::AlignRight);
  paddleLayout->addWidget(paddleLength,numRow,1);
  paddleLayout->addWidget(paddleHeight,numRow,2);
  paddleLayout->addWidget(paddleWidth,numRow, 3);
  paddleLayout->addWidget(new QLabel("m"),numRow++, 4);


  paddleOriginX = new SC_DoubleLineEdit("paddleOriginX", 1.7);
  paddleOriginY = new SC_DoubleLineEdit("paddleOriginY", -0.1);
  paddleOriginZ = new SC_DoubleLineEdit("paddleOriginZ", -0.1);
  paddleLayout->addWidget(new QLabel("Origin (X,Y,Z)"),numRow, 0);
  paddleLayout->itemAt(paddleLayout->count()-1)->setAlignment(Qt::AlignRight);
  paddleLayout->addWidget(paddleOriginX,numRow,1);
  paddleLayout->addWidget(paddleOriginY,numRow,2);
  paddleLayout->addWidget(paddleOriginZ,numRow,3);
  paddleLayout->addWidget(new QLabel("m"),numRow++, 4);
  
  paddleDisplacementFile = new SC_FileEdit("paddleDisplacementFile");
  QString paddleName = QString("Examples/WaveMaker/wmdisp_LWF_Unbroken_Amp4_SF500_twm10sec_1200hz_14032023.csv");
  paddleDisplacementFile->setFilename(paddleName);
  // paddleDisplacementFile->setFilter("CSV Files (*.csv)");
  

  // QString paddleDisplacementFilename = QString::fromAscii"WaveMaker/wmdisp_LWF_Unbroken_Amp4_SF500_twm10sec_1200hz_14032023.csv";
  paddleLayout->addWidget(new QLabel("Paddle Motion File"), numRow, 0);
  paddleLayout->itemAt(paddleLayout->count()-1)->setAlignment(Qt::AlignRight);
  char str[] = "wmdisp_LWF_Unbroken_Amp4_SF500_twm10sec_1200hz_14032023.csv"; // 4m amplitude, scale-factor 500, from Mascarenas 2022
  // paddleName(str);
  QString renderPaddleName = QString(str);
  paddleDisplacementFile->setFilename(renderPaddleName);
  paddleLayout->addWidget(paddleDisplacementFile, numRow++, 1, 1, 4);
  paddleDisplacementFile->setEnabled(false);
  paddleDisplacementFile->setToolTip("This file is not editable, it is a default file for the OSU LWF");
  paddleDisplacementFile->show();
  
  int paddleNumRow = numRow;
  numRow++;
  paddleLayout->setRowStretch(numRow,1);  

  paddleWidget = new QWidget();
  paddleWidget->setLayout(paddleLayout);
  // /**
  QHBoxLayout * plotLayout = new QHBoxLayout();
  QWidget *plotWidget = new QWidget();
  plotWidget->setLayout(plotLayout);
  // **/

  // Periodic Waves
  waveMag = new SC_DoubleLineEdit("waveMag",0.5);
  waveCelerity = new SC_DoubleLineEdit("waveCelerity",4.0);
  waveRepeatSpeed = new SC_DoubleLineEdit("waveRepeatSpeed",10.0);
  QWidget *periodicWidget = new QWidget();
  QGridLayout *periodicLayout = new QGridLayout();  
  periodicWidget->setLayout(periodicLayout);
  periodicLayout->addWidget(new QLabel("Wave Height"),0,0);
  periodicLayout->itemAt(periodicLayout->count()-1)->setAlignment(Qt::AlignRight);
  periodicLayout->addWidget(new QLabel("Wave Celerity"),1,0);
  periodicLayout->itemAt(periodicLayout->count()-1)->setAlignment(Qt::AlignRight);
  periodicLayout->addWidget(new QLabel("Wave Period"),2,0);
  periodicLayout->itemAt(periodicLayout->count()-1)->setAlignment(Qt::AlignRight);
  periodicLayout->addWidget(waveMag,0,1);
  periodicLayout->addWidget(waveCelerity,1,1);
  periodicLayout->addWidget(waveRepeatSpeed,2,1);
  periodicLayout->addWidget(new QLabel("m"),0,2);
  periodicLayout->addWidget(new QLabel("m/s"),1,2);
  periodicLayout->addWidget(new QLabel("s"),2,2);
  periodicLayout->setRowStretch(3,1);

  QStackedWidget *waveGenStack = new QStackedWidget();
  waveGenStack->addWidget(paddleWidget);
  waveGenStack->addWidget(periodicWidget); 


  // /**
  thePlot = new SimCenterGraphPlot(QString("Time [s]"),QString("Displacement [m]"), 500, 500);
  if (inpty==QString("Periodic Waves")) {
      alpha = this->createTextEntry(tr("Height"), periodicLayout, 0);
      beta  = this->createTextEntry(tr("Celerity"), periodicLayout, 1);
      a = this->createTextEntry(tr("Period"), periodicLayout, 2);
      b  = this->createTextEntry(tr("Duration"), periodicLayout, 3);
      showPlotButton = new QPushButton("Show Plot");
      periodicLayout->addWidget(showPlotButton, 1,4);

      periodicLayout->setColumnStretch(5,1);

  } else  {
    dataDir = this->createTextEntry(tr("Paddle Motion (*.csv)"), plotLayout, 0);
    dataDir->setText(paddleName);
    dataDir->setMinimumWidth(200);
    dataDir->setMaximumWidth(700);

    QPushButton *chooseFileButton = new QPushButton("Choose");
    plotLayout->addWidget(chooseFileButton, 1);
    a = this->createTextEntry(tr("Min(t)"), plotLayout, 2);
    b = this->createTextEntry(tr("Max(t)"), plotLayout, 3);
    showPlotButton = new QPushButton("Show Plot");
    plotLayout->addWidget(showPlotButton, 4);

    plotLayout->setStretch(5,1);

    paddleLayout->addWidget(plotWidget, paddleNumRow++, 0, 1, 5);

    paddleLayout->addWidget(thePlot, paddleNumRow++, 0, 1, 5);
    thePlot->hide();
    // mainLayout->setColumnStretch(4,1);

    connect(chooseFileButton, &QPushButton::clicked, this, [=](){
          QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"),"", "CSV File (*.csv)");
          if (!fileName.isEmpty()) {
              dataDir->setText(fileName);
          }
      });
  }
  // **/


  // Place the plot in the layout


  // /**
  if (inpty==QString("Periodic Waves"))
  {
      connect(alpha,SIGNAL(textEdited(QString)), this, SLOT(updateDistributionPlot()));
      connect(beta,SIGNAL(textEdited(QString)), this, SLOT(updateDistributionPlot()));
      connect(a,SIGNAL(textEdited(QString)), this, SLOT(updateDistributionPlot()));
      connect(b,SIGNAL(textEdited(QString)), this, SLOT(updateDistributionPlot()));
      connect(showPlotButton, &QPushButton::clicked, this, [=](){ thePlot->hide(); thePlot->show();});
  } else {
      connect(dataDir,SIGNAL(textEdited(QString)), this, SLOT(updateDistributionPlot()));
      connect(a,SIGNAL(textEdited(QString)), this, SLOT(updateDistributionPlot()));
      connect(b,SIGNAL(textEdited(QString)), this, SLOT(updateDistributionPlot()));
      connect(showPlotButton, &QPushButton::clicked, this, [=](){ thePlot->hide(); thePlot->show();});
      // connect (paddleDisplacementFile, &SC_FileEdit::fileChanged, this, [=](){
      //     QString fileName = paddleDisplacementFile->getFilename();
      //     dataDir->setText(fileName);
      // });
      // Show the plot when the
      connect(dataDir, &QLineEdit::editingFinished, this, [=](){
          thePlot->hide();
          thePlot->show();
      });
  }
  // **/

  connect(generationMethod, QOverload<int>::of(&QComboBox::activated),
    waveGenStack, &QStackedWidget::setCurrentIndex);

  // update value of inpty when generationMethod is changed
  connect(generationMethod, QOverload<int>::of(&QComboBox::activated),
    this, [=](int index) {
      inpty = generationMethod->currentText();
    });

  numRow = 0;
  theWaveGenLayout->addWidget(new QLabel("Wave Generation Method"),numRow,0);
  theWaveGenLayout->itemAt(theWaveGenLayout->count()-1)->setAlignment(Qt::AlignRight);
  theWaveGenLayout->addWidget(generationMethod,numRow++,1);
  theWaveGenLayout->addWidget(waveGenStack,numRow++,0,1,2);
  theWaveGenLayout->setRowStretch(numRow,1);


  // Rigid Structures

  numRow = 0;

  QStringList listObject; listObject << "Orange Box - OSU LWF" << "Square Columns - OSU DWB"<< "Grey Box - UW WASIRF" << "Square Columns - WU TWB" << "Box" << "Cylinder" << "Wedge" << "Sphere" << "Custom";  
  structObjectType = new SC_ComboBox("structObjectType",listObject);
  structLayout->addWidget(new QLabel("Object Type"),numRow,0);
  structLayout->itemAt(structLayout->count()-1)->setAlignment(Qt::AlignRight);
  structLayout->addWidget(structObjectType,numRow++,1);

  QStringList listContact; listContact << "Separable" << "Slip" << "Sticky";  
  structContactType = new SC_ComboBox("structContactType",listContact);
  structLayout->addWidget(new QLabel("Contact Type"),numRow,0);
  structLayout->itemAt(structLayout->count()-1)->setAlignment(Qt::AlignRight);
  structLayout->addWidget(structContactType,numRow++,1);

  QStringList faceList; faceList << "X-" << "X+" << "Y-" << "Y+" << "Z-" << "Z+";
  loadCellFace = new SC_ComboBox("loadCellFace", faceList);
  structLayout->addWidget(new QLabel("Load-Cell on Face"),numRow,0);
  structLayout->itemAt(structLayout->count()-1)->setAlignment(Qt::AlignRight);
  structLayout->addWidget(loadCellFace,numRow++,1);

  // numRow = 2;
  structLength = new SC_DoubleLineEdit("structLength",1.0);
  structHeight = new SC_DoubleLineEdit("structHeight",0.625);
  structWidth = new SC_DoubleLineEdit("structWidth",1.0);
  structLayout->addWidget(new QLabel("Dimensions (X,Y,Z)"),numRow, 0);
  structLayout->itemAt(structLayout->count()-1)->setAlignment(Qt::AlignRight);
  structLayout->addWidget(structLength,numRow,1);
  structLayout->addWidget(structHeight,numRow,2);
  structLayout->addWidget(structWidth,numRow,3);
  structLayout->addWidget(new QLabel("m"),numRow++, 4);

  structOriginLength = new SC_DoubleLineEdit("structOriginX",45.8);
  structOriginHeight = new SC_DoubleLineEdit("structOriginY",2.0);
  structOriginWidth = new SC_DoubleLineEdit("structOriginZ",1.325);
  structLayout->addWidget(new QLabel("Origin (X,Y,Z)"),numRow, 0);
  structLayout->itemAt(structLayout->count()-1)->setAlignment(Qt::AlignRight);
  structLayout->addWidget(structOriginLength,numRow,1);
  structLayout->addWidget(structOriginHeight,numRow,2);
  structLayout->addWidget(structOriginWidth,numRow,3);
  structLayout->addWidget(new QLabel("m"),numRow++, 4);


  structApplyCoulombFriction = new SC_CheckBox("structApplyCoulombFriction");
  structApplyCoulombFriction->setChecked(false);
  structApplyCoulombFriction->setEnabled(false);
  structLayout->addWidget(new QLabel("Apply Coulomb Friction?"),numRow, 0);  
  structLayout->itemAt(structLayout->count()-1)->setAlignment(Qt::AlignRight);
  structLayout->addWidget(structApplyCoulombFriction,numRow++, 1);
  
  QGroupBox *structFrictionBox = new QGroupBox("");
  QGridLayout *structFrictionBoxLayout = new QGridLayout();
  structFrictionBox->setLayout(structFrictionBoxLayout);
  numRow = 0;
  
  
  structStaticFrictionWallX = new SC_DoubleLineEdit("structStaticFrictionWallX",0.0);
  structStaticFrictionWallY = new SC_DoubleLineEdit("structStaticFrictionWallY",0.0);
  structStaticFrictionWallZ = new SC_DoubleLineEdit("structStaticFrictionWallZ",0.0);
  structFrictionBoxLayout->addWidget(new QLabel("Static Friction on Faces (X,Y,Z)"),numRow, 0);
  structFrictionBoxLayout->itemAt(structFrictionBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  structFrictionBoxLayout->addWidget(structStaticFrictionWallX,numRow,1);
  structFrictionBoxLayout->addWidget(structStaticFrictionWallY,numRow,2);
  structFrictionBoxLayout->addWidget(structStaticFrictionWallZ,numRow,3);
  structFrictionBoxLayout->addWidget(new QLabel("Coef."),numRow++, 4);

  structDynamicFrictionWallX = new SC_DoubleLineEdit("structDynamicFrictionWallX",0.0);
  structDynamicFrictionWallY = new SC_DoubleLineEdit("structDynamicFrictionWallY",0.0);
  structDynamicFrictionWallZ = new SC_DoubleLineEdit("structDynamicFrictionWallZ",0.0);
  structFrictionBoxLayout->addWidget(new QLabel("Dynamic Friction on Faces (X,Y,Z)"),numRow, 0);
  structFrictionBoxLayout->itemAt(structFrictionBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  structFrictionBoxLayout->addWidget(structDynamicFrictionWallX,numRow,1);  
  structFrictionBoxLayout->addWidget(structDynamicFrictionWallY,numRow,2);  
  structFrictionBoxLayout->addWidget(structDynamicFrictionWallZ,numRow,3);  
  structFrictionBoxLayout->addWidget(new QLabel("Coef."),numRow++, 4);
  structFrictionBoxLayout->setRowStretch(numRow,1);

  numRow = 7+1;
  structLayout->addWidget(structFrictionBox, numRow++, 0, 2, 5);

  numRow += 1; // Adjust for groupbox

  applyArray = new SC_CheckBox("applyArray");
  applyArray->setChecked(true);
  structLayout->addWidget(new QLabel("Make an Array?"),numRow, 0);
  structLayout->itemAt(structLayout->count()-1)->setAlignment(Qt::AlignRight);
  structLayout->addWidget(applyArray,numRow++, 1);

  // numRow = 0;
  QGroupBox *structArrayBox = new QGroupBox("");
  QGridLayout *structArrayBoxLayout = new QGridLayout();
  structArrayBox->setLayout(structArrayBoxLayout);
  int numStructArrayRow = 0;
  structArrayX  = new SC_IntLineEdit("structArrayX",1);
  structArrayY  = new SC_IntLineEdit("structArrayY",1);
  structArrayZ  = new SC_IntLineEdit("structArrayZ",1);
  structSpacingX = new SC_DoubleLineEdit("structSpacingX",0.0);
  structSpacingY = new SC_DoubleLineEdit("structSpacingY",0.0);
  structSpacingZ = new SC_DoubleLineEdit("structSpacingZ",0.0);
  structArrayBoxLayout->addWidget(new QLabel("Array of Objects (X, Y, Z)"),numStructArrayRow, 0);
  structArrayBoxLayout->itemAt(structArrayBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  structArrayBoxLayout->addWidget(structArrayX,numStructArrayRow,1);
  structArrayBoxLayout->addWidget(structArrayY,numStructArrayRow,2);
  structArrayBoxLayout->addWidget(structArrayZ,numStructArrayRow,3);
  structArrayBoxLayout->addWidget(new QLabel("#"),numStructArrayRow++, 4);
  structArrayBoxLayout->addWidget(new QLabel("Spacing of Objects (X,Y,Z)"),numStructArrayRow, 0);
  structArrayBoxLayout->itemAt(structArrayBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  structArrayBoxLayout->addWidget(structSpacingX,numStructArrayRow,1);
  structArrayBoxLayout->addWidget(structSpacingY,numStructArrayRow,2);
  structArrayBoxLayout->addWidget(structSpacingZ,numStructArrayRow,3);
  structArrayBoxLayout->addWidget(new QLabel("m"),numStructArrayRow++, 4);
  structArrayBoxLayout->setRowStretch(numStructArrayRow,1);

  // numRow = 10;
  structLayout->addWidget(structArrayBox, numRow++, 0, 2, 5);
  numRow += 1; // Adjust for groupbox

  autoCreateLoadCells = new SC_CheckBox("autoCreateLoadCells");
  autoCreateLoadCells->setChecked(true);
  structLayout->addWidget(new QLabel("Auto-Create Load-Cells (Force Sensors)?"),numRow, 0);
  structLayout->itemAt(structLayout->count()-1)->setAlignment(Qt::AlignRight);
  structLayout->addWidget(autoCreateLoadCells,numRow++, 1);

  structLayout->setRowStretch(numRow+1,1);

  // structLayout->setRowStretch(numRow,1);

  connect(structApplyCoulombFriction, &QCheckBox::stateChanged, [=](int state) {
    if (state == Qt::Checked) {
      structFrictionBox->setVisible(true);
    } else {
      structFrictionBox->setVisible(false);
    }
  });

  connect(applyArray, &QCheckBox::stateChanged, [=](int state) {
    if (state == Qt::Checked) {
      structArrayBox->setVisible(true);
    } else {
      structArrayBox->setVisible(false);
    }
  });



  // connect(structLength, &QLineEdit::textChanged, [=](QString val) {
  //   emit structDimensionsChanged(val);
  // });

  // connect(structHeight, &QLineEdit::textChanged, [=](QString val) {
  //   emit structDimensionsChanged(val);
  // });

  // connect(structWidth, &QLineEdit::textChanged, [=](QString val) {
  //   emit structDimensionsChanged(val);
  // });

  // connect(structOriginLength, &QLineEdit::textChanged, [=](QString val) {
  //   emit structOriginChanged(val);
  // });

  // connect(structOriginHeight, &QLineEdit::textChanged, [=](QString val) {
  //   emit structOriginChanged(val);
  // });

  // connect(structOriginWidth, &QLineEdit::textChanged, [=](QString val) {
  //   emit structOriginChanged(val);
  // });

  // connect(structLength, SIGNAL(textChanged(QString)), this, SIGNAL(structDimensionsChanged(QString)));
  // connect(structHeight, SIGNAL(textChanged(QString)), this, SIGNAL(structDimensionsChanged(QString)));
  // connect(structWidth, SIGNAL(textChanged(QString)), this, SIGNAL(structDimensionsChanged(QString)));
  // connect(structOriginLength, SIGNAL(textChanged(QString)), this, SIGNAL(structOriginChanged(QString)));
  // connect(structOriginHeight, SIGNAL(textChanged(QString)), this, SIGNAL(structOriginChanged(QString)));
  // connect(structOriginWidth, SIGNAL(textChanged(QString)), this, SIGNAL(structOriginChanged(QString)));
  

  // connect(structLength, &QLineEdit::textChanged, this, &BoundaryMPM::structDimensionsChanged);
  // connect(structHeight, &QLineEdit::textChanged, this, &BoundaryMPM::structDimensionsChanged);
  // connect(structWidth, &QLineEdit::textChanged, this, &BoundaryMPM::structDimensionsChanged);
  // connect(structOriginLength, &QLineEdit::textChanged, this, &BoundaryMPM::structOriginChanged);
  // connect(structOriginHeight, &QLineEdit::textChanged, this, &BoundaryMPM::structOriginChanged);
  // connect(structOriginWidth, &QLineEdit::textChanged, this, &BoundaryMPM::structOriginChanged);


//Signal for dimensions change or origin change to be used in higher class


  // If any change happens to any of the variables, the signal will be emitted and the slot will be called
  // What do slots do? They emit signals to the higher class
  // What do signals do? They call the slots in the higher class
  // What do the higher class do? They emit signals to the main class
  // What do the main class do? They call the slots in the main class
  // connect(this, &BoundaryMPM::structDimensionsChanged, this, &BoundaryMPM::structDimensionsChangedSlot);
  // connect(this, &BoundaryMPM::structOriginChanged, this, &BoundaryMPM::structOriginChangedSlot);


  



  // -----
  // Walls

  numRow = 0;
  QStringList wallListContact; wallListContact << "Separable" << "Slip" << "Sticky";  
  
  wallsContactType = new SC_ComboBox("wallContactType",listContact);
  wallsLayout->addWidget(new QLabel("Contact Type"),numRow,0);
  wallsLayout->itemAt(wallsLayout->count()-1)->setAlignment(Qt::AlignRight);
  wallsLayout->addWidget(wallsContactType,numRow++,1);

  wallsLength = new SC_DoubleLineEdit("wallsLength",90.0);
  wallsHeight = new SC_DoubleLineEdit("wallsHeight",4.5);
  wallsWidth = new SC_DoubleLineEdit("wallsWidth",3.6);
  wallsLayout->addWidget(new QLabel("Dimensions (X,Y,Z)"),numRow, 0);
  wallsLayout->itemAt(wallsLayout->count()-1)->setAlignment(Qt::AlignRight);
  wallsLayout->addWidget(wallsLength,numRow,1);
  wallsLayout->addWidget(wallsHeight,numRow,2);
  wallsLayout->addWidget(wallsWidth,numRow,3);
  wallsLayout->addWidget(new QLabel("m"),numRow++, 4);

  originLength = new SC_DoubleLineEdit("wallsOriginX",0.0);
  originHeight = new SC_DoubleLineEdit("wallsOriginY",0.0);
  originWidth = new SC_DoubleLineEdit("wallsOriginZ",0.0);
  wallsLayout->addWidget(new QLabel("Origin (X,Y,Z)"),numRow, 0);
  wallsLayout->itemAt(wallsLayout->count()-1)->setAlignment(Qt::AlignRight);
  wallsLayout->addWidget(originLength,numRow,1);
  wallsLayout->addWidget(originHeight,numRow,2);
  wallsLayout->addWidget(originWidth,numRow,3);
  wallsLayout->addWidget(new QLabel("m"),numRow++, 4);

  applyCoulombFriction = new SC_CheckBox("applyCoulombFriction");
  applyCoulombFriction->setChecked(false);
  applyCoulombFriction->setEnabled(false);
  wallsLayout->addWidget(new QLabel("Apply Coulomb Friction?"),numRow, 0);  
  wallsLayout->itemAt(wallsLayout->count()-1)->setAlignment(Qt::AlignRight);
  wallsLayout->addWidget(applyCoulombFriction,numRow++, 1);
  

  
  QGroupBox *frictionBox = new QGroupBox("");
  QGridLayout *frictionBoxLayout = new QGridLayout();
  frictionBox->setLayout(frictionBoxLayout);
  int numFrictionRow = 0;
  staticFrictionWallX = new SC_DoubleLineEdit("staticFrictionWallX",0.0);
  staticFrictionWallY = new SC_DoubleLineEdit("staticFrictionWallY",0.0);
  staticFrictionWallZ = new SC_DoubleLineEdit("staticFrictionWallZ",0.0);
  frictionBoxLayout->addWidget(new QLabel("Static Friction on Walls (X,Y,Z)"),numFrictionRow, 0);
  frictionBoxLayout->itemAt(frictionBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  frictionBoxLayout->addWidget(staticFrictionWallX,numFrictionRow,1);
  frictionBoxLayout->addWidget(staticFrictionWallY,numFrictionRow,2);
  frictionBoxLayout->addWidget(staticFrictionWallZ,numFrictionRow,3);
  frictionBoxLayout->addWidget(new QLabel("Coef."),numFrictionRow++, 4);

  dynamicFrictionWallX = new SC_DoubleLineEdit("dynamicFrictionWallX",0.0);
  dynamicFrictionWallY = new SC_DoubleLineEdit("dynamicFrictionWallY",0.0);
  dynamicFrictionWallZ = new SC_DoubleLineEdit("dynamicFrictionWallZ",0.0);
  frictionBoxLayout->addWidget(new QLabel("Dynamic Friction on Walls (X,Y,Z)"),numFrictionRow, 0);
  frictionBoxLayout->itemAt(frictionBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  frictionBoxLayout->addWidget(dynamicFrictionWallX,numFrictionRow,1);  
  frictionBoxLayout->addWidget(dynamicFrictionWallY,numFrictionRow,2);  
  frictionBoxLayout->addWidget(dynamicFrictionWallZ,numFrictionRow,3);  
  frictionBoxLayout->addWidget(new QLabel("Coef."),numFrictionRow++, 4);
  frictionBoxLayout->setRowStretch(numFrictionRow,1);
  wallsLayout->addWidget(frictionBox, numRow, 0, numFrictionRow, 5);
  numRow += numFrictionRow;

  // Inlet/Outlet
  applyInletOutlet = new SC_CheckBox("applyInletOutlet");
  applyInletOutlet->setChecked(false);
  applyInletOutlet->setEnabled(false); // TODO: Wall inlet/outlet not implemented yet 
  wallsLayout->addWidget(new QLabel("Apply Inlet/Outlet?"),numRow, 0);
  wallsLayout->itemAt(wallsLayout->count()-1)->setAlignment(Qt::AlignRight);
  wallsLayout->addWidget(applyInletOutlet,numRow++, 1);


  QGroupBox *inletOutletBox = new QGroupBox("");
  QGridLayout *inletOutletBoxLayout = new QGridLayout();
  inletOutletBox->setLayout(inletOutletBoxLayout);
  int numInOutRow = 0;
  QStringList inletOutletList; inletOutletList << "None" 
                                               << "Inlet - Steady"  << "Inlet - OpenFOAM"  << "Inlet - GeoClaw"  << "Inlet - SWE File" 
                                               << "Outlet - Steady" << "Outlet - OpenFOAM" << "Outlet - GeoClaw" << "Outlet - SWE File";
  inletOutletTypeSubX = new SC_ComboBox("inletOutletTypeSubX",inletOutletList);
  inletOutletTypeSubY = new SC_ComboBox("inletOutletTypeSubY",inletOutletList);
  inletOutletTypeSubZ = new SC_ComboBox("inletOutletTypeSubZ",inletOutletList);
  inletOutletTypePlusX = new SC_ComboBox("inletOutletTypePlusX",inletOutletList);
  inletOutletTypePlusY = new SC_ComboBox("inletOutletTypePlusY",inletOutletList);
  inletOutletTypePlusZ = new SC_ComboBox("inletOutletTypePlusZ",inletOutletList);
  inletOutletBoxLayout->addWidget(new QLabel("Inlet-Outlet at (X-,Y-,Z-) Walls"),numInOutRow, 0);
  inletOutletBoxLayout->itemAt(inletOutletBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  inletOutletBoxLayout->addWidget(inletOutletTypeSubX,numInOutRow,1);
  inletOutletBoxLayout->addWidget(inletOutletTypeSubY,numInOutRow,2);
  inletOutletBoxLayout->addWidget(inletOutletTypeSubZ,numInOutRow++,3);
  inletOutletBoxLayout->addWidget(new QLabel("Inlet-Outlet at (X+,Y+,Z+) Walls"),numInOutRow, 0);
  inletOutletBoxLayout->itemAt(inletOutletBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  inletOutletBoxLayout->addWidget(inletOutletTypePlusX,numInOutRow,1);
  inletOutletBoxLayout->addWidget(inletOutletTypePlusY,numInOutRow,2);
  inletOutletBoxLayout->addWidget(inletOutletTypePlusZ,numInOutRow++,3);
  inletOutletBoxLayout->setRowStretch(numInOutRow,1);
  inletOutletBox->setVisible(false); // TODO: Wall inlet/outlet not implemented yet
  // numRow = numRow+1;  
  wallsLayout->addWidget(inletOutletBox, numRow+numInOutRow, 0, 2, 4);
  numRow += numInOutRow;
  // numRow += 4;
  wallsLayout->setRowStretch(numRow+2, 1);

  connect(applyCoulombFriction, &QCheckBox::stateChanged, [=](int state) {
    if (state == Qt::Checked) {
      staticFrictionWallX->setEnabled(true);
      staticFrictionWallY->setEnabled(true);
      staticFrictionWallZ->setEnabled(true);
      dynamicFrictionWallX->setEnabled(true);
      dynamicFrictionWallY->setEnabled(true);
      dynamicFrictionWallZ->setEnabled(true);
      staticFrictionWallX->setVisible(true);
      staticFrictionWallY->setVisible(true);
      staticFrictionWallZ->setVisible(true);
      dynamicFrictionWallX->setVisible(true);
      dynamicFrictionWallY->setVisible(true);
      dynamicFrictionWallZ->setVisible(true);
      frictionBox->setVisible(true);
    } else {
      staticFrictionWallX->setEnabled(false);
      staticFrictionWallY->setEnabled(false);
      staticFrictionWallZ->setEnabled(false);
      dynamicFrictionWallX->setEnabled(false);
      dynamicFrictionWallY->setEnabled(false);
      dynamicFrictionWallZ->setEnabled(false);
      staticFrictionWallX->setVisible(false);
      staticFrictionWallY->setVisible(false);
      staticFrictionWallZ->setVisible(false);
      dynamicFrictionWallX->setVisible(false);
      dynamicFrictionWallY->setVisible(false);
      dynamicFrictionWallZ->setVisible(false);
      frictionBox->setVisible(false);
    }
  });


  connect(applyInletOutlet, &QCheckBox::stateChanged, [=](int state) {
    if (state == Qt::Checked) {
      inletOutletTypeSubX->setEnabled(true);
      inletOutletTypeSubY->setEnabled(true);
      inletOutletTypeSubZ->setEnabled(true);
      inletOutletTypePlusX->setEnabled(true);
      inletOutletTypePlusY->setEnabled(true);
      inletOutletTypePlusZ->setEnabled(true);
      inletOutletTypeSubX->setVisible(true);
      inletOutletTypeSubY->setVisible(true);
      inletOutletTypeSubZ->setVisible(true);
      inletOutletTypePlusX->setVisible(true);
      inletOutletTypePlusY->setVisible(true);
      inletOutletTypePlusZ->setVisible(true);
      inletOutletBox->setVisible(true);
    } else {
      inletOutletTypeSubX->setEnabled(false);
      inletOutletTypeSubY->setEnabled(false);
      inletOutletTypeSubZ->setEnabled(false);
      inletOutletTypePlusX->setEnabled(false);
      inletOutletTypePlusY->setEnabled(false);
      inletOutletTypePlusZ->setEnabled(false);
      inletOutletTypeSubX->setVisible(false);
      inletOutletTypeSubY->setVisible(false);
      inletOutletTypeSubZ->setVisible(false);
      inletOutletTypePlusX->setVisible(false);
      inletOutletTypePlusY->setVisible(false);
      inletOutletTypePlusZ->setVisible(false);
      inletOutletBox->setVisible(false);
    }
  });


}

BoundaryMPM::~BoundaryMPM()
{
  delete thePlot;
}

void BoundaryMPM::clear(void)
{
  // clear all widgets
  // theCustom->clear();
  // theWaveFlume->clear();
  // theWaveGeneration->clear();
  // theStructures->clear();
  // theWalls->clear();
}

bool
BoundaryMPM::setBoundaryType(int type)
{
  enum BoundaryTypeEnum {CUSTOM, WAVE_FLUME, WAVE_GENERATOR, RIGID_STRUCTURE, RIGID_WALLS};
  if (type == BoundaryTypeEnum::CUSTOM) {
    theCustom->setVisible(true);
    theWaveFlume->setVisible(false);
    theWaveGeneration->setVisible(false);
    theStructures->setVisible(false);
    theWalls->setVisible(false);
    stackedWidget->setCurrentIndex(0);
    boundaryType->setCurrentIndex(0);
    return true;
  } else if (type == BoundaryTypeEnum::WAVE_FLUME) {
    theCustom->setVisible(false);
    theWaveFlume->setVisible(true);
    theWaveGeneration->setVisible(false);
    theStructures->setVisible(false);
    theWalls->setVisible(false);
    stackedWidget->setCurrentIndex(1);
    boundaryType->setCurrentIndex(1);
    return true;
  } else if (type == BoundaryTypeEnum::WAVE_GENERATOR) {
    theCustom->setVisible(false);
    theWaveFlume->setVisible(false);
    theWaveGeneration->setVisible(true);
    theStructures->setVisible(false);
    theWalls->setVisible(false);
    stackedWidget->setCurrentIndex(2);
    boundaryType->setCurrentIndex(2);
    return true;
  } else if (type == BoundaryTypeEnum::RIGID_STRUCTURE) {
    theCustom->setVisible(false);
    theWaveFlume->setVisible(false);
    theWaveGeneration->setVisible(false);
    theStructures->setVisible(true);
    theWalls->setVisible(false);
    stackedWidget->setCurrentIndex(3);
    boundaryType->setCurrentIndex(3);
    return true;
  } else if (type == BoundaryTypeEnum::RIGID_WALLS) {
    theCustom->setVisible(false);
    theWaveFlume->setVisible(false);
    theWaveGeneration->setVisible(false);
    theStructures->setVisible(false);
    theWalls->setVisible(true);
    stackedWidget->setCurrentIndex(4);
    boundaryType->setCurrentIndex(4);
    return true;
  } else {
    return false; 
  }
}

// Refactor these to not have specific length vars, etc per stacked widget
double BoundaryMPM::getDimensionX() {
  if (stackedWidget->currentIndex() == 0) return 0;
  else if (stackedWidget->currentIndex() == 1) return flumeLength->text().toDouble();
  else if (stackedWidget->currentIndex() == 2) return paddleLength->text().toDouble();
  else if (stackedWidget->currentIndex() == 3) return structLength->text().toDouble();
  else if (stackedWidget->currentIndex() == 4) return wallsLength->text().toDouble();
  else
  return 1.f;
}

double BoundaryMPM::getDimensionY() {
  if (stackedWidget->currentIndex() == 0) return 0;
  else if (stackedWidget->currentIndex() == 1) return flumeHeight->text().toDouble();
  else if (stackedWidget->currentIndex() == 2) return paddleHeight->text().toDouble();
  else if (stackedWidget->currentIndex() == 3) return structHeight->text().toDouble();
  else if (stackedWidget->currentIndex() == 4) return wallsHeight->text().toDouble();
  else
  return 1.f;
}

double BoundaryMPM::getDimensionZ() {
  if (stackedWidget->currentIndex() == 0) return 0;
  else if (stackedWidget->currentIndex() == 1) return flumeWidth->text().toDouble();
  else if (stackedWidget->currentIndex() == 2) return paddleWidth->text().toDouble();
  else if (stackedWidget->currentIndex() == 3) return structWidth->text().toDouble();
  else if (stackedWidget->currentIndex() == 4) return wallsWidth->text().toDouble();
  else
  return 1.f;
}

SC_DoubleLineEdit* BoundaryMPM::getDimensionXWidget() {
  if (stackedWidget->currentIndex() == 0) return nullptr;
  else if (stackedWidget->currentIndex() == 1) return flumeLength;
  else if (stackedWidget->currentIndex() == 2) return paddleLength;
  else if (stackedWidget->currentIndex() == 3) return structLength;
  else if (stackedWidget->currentIndex() == 4) return wallsLength;
  else
  return nullptr;
}

SC_DoubleLineEdit* BoundaryMPM::getDimensionYWidget() {
  if (stackedWidget->currentIndex() == 0) return nullptr;
  else if (stackedWidget->currentIndex() == 1) return flumeHeight;
  else if (stackedWidget->currentIndex() == 2) return paddleHeight;
  else if (stackedWidget->currentIndex() == 3) return structHeight;
  else if (stackedWidget->currentIndex() == 4) return wallsHeight;
  else
  return nullptr;
}

SC_DoubleLineEdit* BoundaryMPM::getDimensionZWidget() {
  if (stackedWidget->currentIndex() == 0) return nullptr;
  else if (stackedWidget->currentIndex() == 1) return flumeWidth;
  else if (stackedWidget->currentIndex() == 2) return paddleWidth;
  else if (stackedWidget->currentIndex() == 3) return structWidth;
  else if (stackedWidget->currentIndex() == 4) return wallsWidth;
  else
  return nullptr;
}

double BoundaryMPM::getOriginX() {
  if (stackedWidget->currentIndex() == 0) return 0;
  else if (stackedWidget->currentIndex() == 1) return flumeOriginX->text().toDouble();
  else if (stackedWidget->currentIndex() == 2) return paddleOriginX->text().toDouble();
  else if (stackedWidget->currentIndex() == 3) return structOriginLength->text().toDouble();
  else if (stackedWidget->currentIndex() == 4) return originLength->text().toDouble();
  else
  return 0.f;
}

double BoundaryMPM::getOriginY() {
  if (stackedWidget->currentIndex() == 0) return 0;
  else if (stackedWidget->currentIndex() == 1) return flumeOriginY->text().toDouble();
  else if (stackedWidget->currentIndex() == 2) return paddleOriginY->text().toDouble();
  else if (stackedWidget->currentIndex() == 3) return structOriginHeight->text().toDouble();
  else if (stackedWidget->currentIndex() == 4) return originHeight->text().toDouble();
  else
  return 0.f;
}

double BoundaryMPM::getOriginZ() {
  if (stackedWidget->currentIndex() == 0) return 0;
  else if (stackedWidget->currentIndex() == 1) return flumeOriginZ->text().toDouble();
  else if (stackedWidget->currentIndex() == 2) return paddleOriginZ->text().toDouble();
  else if (stackedWidget->currentIndex() == 3) return structOriginWidth->text().toDouble();
  else if (stackedWidget->currentIndex() == 4) return originWidth->text().toDouble();
  else
  return 0.f;
}

SC_DoubleLineEdit* BoundaryMPM::getOriginXWidget() {
  if (stackedWidget->currentIndex() == 0) return nullptr;
  else if (stackedWidget->currentIndex() == 1) return flumeOriginX;
  else if (stackedWidget->currentIndex() == 2) return paddleOriginX;
  else if (stackedWidget->currentIndex() == 3) return structOriginLength;
  else if (stackedWidget->currentIndex() == 4) return originLength;
  else
  return nullptr;
}

SC_DoubleLineEdit* BoundaryMPM::getOriginYWidget() {
  if (stackedWidget->currentIndex() == 0) return nullptr;
  else if (stackedWidget->currentIndex() == 1) return flumeOriginY;
  else if (stackedWidget->currentIndex() == 2) return paddleOriginY;
  else if (stackedWidget->currentIndex() == 3) return structOriginHeight;
  else if (stackedWidget->currentIndex() == 4) return originHeight;
  else
  return nullptr;
}

SC_DoubleLineEdit* BoundaryMPM::getOriginZWidget() {
  if (stackedWidget->currentIndex() == 0) return nullptr;
  else if (stackedWidget->currentIndex() == 1) return flumeOriginZ;
  else if (stackedWidget->currentIndex() == 2) return paddleOriginZ;
  else if (stackedWidget->currentIndex() == 3) return structOriginWidth;
  else if (stackedWidget->currentIndex() == 4) return originWidth;
  else
  return nullptr;
}


int BoundaryMPM::getArrayX() {
  if (stackedWidget->currentIndex() == 0) return 0;
  else if (stackedWidget->currentIndex() == 1) return 0;
  else if (stackedWidget->currentIndex() == 2) return 0;
  else if (stackedWidget->currentIndex() == 3) return structArrayX->text().toInt();
  else if (stackedWidget->currentIndex() == 4) return 0;
  else
  return 1;
}

int BoundaryMPM::getArrayY() {
  if (stackedWidget->currentIndex() == 0) return 0;
  else if (stackedWidget->currentIndex() == 1) return 0;
  else if (stackedWidget->currentIndex() == 2) return 0;
  else if (stackedWidget->currentIndex() == 3) return structArrayY->text().toInt();
  else if (stackedWidget->currentIndex() == 4) return 0;
  else
  return 1;
}

int BoundaryMPM::getArrayZ() {
  if (stackedWidget->currentIndex() == 0) return 0;
  else if (stackedWidget->currentIndex() == 1) return 0;
  else if (stackedWidget->currentIndex() == 2) return 0;
  else if (stackedWidget->currentIndex() == 3) return structArrayZ->text().toInt();
  else if (stackedWidget->currentIndex() == 4) return 0;
  else
  return 1;
}

SC_IntLineEdit* BoundaryMPM::getArrayXWidget() {
  if (stackedWidget->currentIndex() == 0) return nullptr;
  else if (stackedWidget->currentIndex() == 1) return nullptr;
  else if (stackedWidget->currentIndex() == 2) return nullptr;
  else if (stackedWidget->currentIndex() == 3) return structArrayX;
  else if (stackedWidget->currentIndex() == 4) return nullptr;
  else
  return nullptr;
}

SC_IntLineEdit* BoundaryMPM::getArrayYWidget() {
  if (stackedWidget->currentIndex() == 0) return nullptr;
  else if (stackedWidget->currentIndex() == 1) return nullptr;
  else if (stackedWidget->currentIndex() == 2) return nullptr;
  else if (stackedWidget->currentIndex() == 3) return structArrayY;
  else if (stackedWidget->currentIndex() == 4) return nullptr;
  else
  return nullptr;
}

SC_IntLineEdit* BoundaryMPM::getArrayZWidget() {
  if (stackedWidget->currentIndex() == 0) return nullptr;
  else if (stackedWidget->currentIndex() == 1) return nullptr;
  else if (stackedWidget->currentIndex() == 2) return nullptr;
  else if (stackedWidget->currentIndex() == 3) return structArrayZ;
  else if (stackedWidget->currentIndex() == 4) return nullptr;
  else
  return nullptr;
}

double BoundaryMPM::getSpacingX() {
  if (stackedWidget->currentIndex() == 0) return 0;
  else if (stackedWidget->currentIndex() == 1) return 0;
  else if (stackedWidget->currentIndex() == 2) return 0;
  else if (stackedWidget->currentIndex() == 3) return structSpacingX->text().toDouble();
  else if (stackedWidget->currentIndex() == 4) return 0;
  else
  return 0.f;
}

double BoundaryMPM::getSpacingY() {
  if (stackedWidget->currentIndex() == 0) return 0;
  else if (stackedWidget->currentIndex() == 1) return 0;
  else if (stackedWidget->currentIndex() == 2) return 0;
  else if (stackedWidget->currentIndex() == 3) return structSpacingY->text().toDouble();
  else if (stackedWidget->currentIndex() == 4) return 0;
  else
  return 0.f;
}

double BoundaryMPM::getSpacingZ() {
  if (stackedWidget->currentIndex() == 0) return 0;
  else if (stackedWidget->currentIndex() == 1) return 0;
  else if (stackedWidget->currentIndex() == 2) return 0;
  else if (stackedWidget->currentIndex() == 3) return structSpacingZ->text().toDouble();
  else if (stackedWidget->currentIndex() == 4) return 0;
  else
  return 0.f;
}


SC_DoubleLineEdit* BoundaryMPM::getSpacingXWidget() {
  if (stackedWidget->currentIndex() == 0) return nullptr;
  else if (stackedWidget->currentIndex() == 1) return nullptr;
  else if (stackedWidget->currentIndex() == 2) return nullptr;
  else if (stackedWidget->currentIndex() == 3) return structSpacingX;
  else if (stackedWidget->currentIndex() == 4) return nullptr;
  else
  return nullptr;
}

SC_DoubleLineEdit* BoundaryMPM::getSpacingYWidget() {
  if (stackedWidget->currentIndex() == 0) return nullptr;
  else if (stackedWidget->currentIndex() == 1) return nullptr;
  else if (stackedWidget->currentIndex() == 2) return nullptr;
  else if (stackedWidget->currentIndex() == 3) return structSpacingY;
  else if (stackedWidget->currentIndex() == 4) return nullptr;
  else
  return nullptr;
}

SC_DoubleLineEdit* BoundaryMPM::getSpacingZWidget() {
  if (stackedWidget->currentIndex() == 0) return nullptr;
  else if (stackedWidget->currentIndex() == 1) return nullptr;
  else if (stackedWidget->currentIndex() == 2) return nullptr;
  else if (stackedWidget->currentIndex() == 3) return structSpacingZ;
  else if (stackedWidget->currentIndex() == 4) return nullptr;
  else
  return nullptr;
}


QLineEdit *
BoundaryMPM::createTextEntry(QString text,
                                            QHBoxLayout *theLayout,
                                            int minL,
                                            int maxL)
{
    QVBoxLayout *entryLayout = new QVBoxLayout();
    //QHBoxLayout *entryLayout = new QHBoxLayout();
    QLabel *entryLabel = new QLabel(text);

    QLineEdit *res = new QLineEdit();
    res->setMinimumWidth(minL);
    res->setMaximumWidth(maxL);
    res->setValidator(new QDoubleValidator);

    entryLayout->addWidget(entryLabel);
    entryLayout->addWidget(res);

    entryLayout->setSpacing(0);
    //    entryLayout->setMargin(0);

    theLayout->addLayout(entryLayout);

    return res;
}

QLineEdit *
BoundaryMPM::createTextEntry(QString text,
                                            QGridLayout *theLayout,
                                            int col,
                                            int minL,
                                            int maxL)
{
    //QVBoxLayout *entryLayout = new QVBoxLayout();
    // //QHBoxLayout *entryLayout = new QHBoxLayout();
    QLabel *entryLabel = new QLabel(text);

    QLineEdit *res = new QLineEdit();
    res->setMinimumWidth(minL);
    res->setMaximumWidth(maxL);
    res->setValidator(new QDoubleValidator);
    //entryLayout->addWidget(entryLabel);
    //entryLayout->addWidget(res);

    //entryLayout->setSpacing(0);
    //entryLayout->setMargin(0);

    //theLayout->addLayout(entryLayout,0,col,2,1);

    theLayout->addWidget(entryLabel,0,col);
    theLayout->addWidget(res,1,col);

    return res;
}


bool
BoundaryMPM::outputToJSON(QJsonObject &jsonObject)
{
  QJsonArray boundariesArray;
  boundariesArray = jsonObject["boundaries"].toArray();

  enum BoundaryTypeEnum : int {CUSTOM, WAVE_FLUME, WAVE_GENERATOR, RIGID_STRUCTURE, RIGID_WALLS};
  // Wave Flume Facility
  if (stackedWidget->currentIndex() == BoundaryTypeEnum::CUSTOM) {
    return true;
  }
  else if (stackedWidget->currentIndex() == BoundaryTypeEnum::WAVE_FLUME) {
    QJsonObject boundariesObject;

    // TODO: Add wave flume facility names to JSON to link to the name in ClaymoreUW enumerators
    boundariesObject["object"] = QString("OSU LWF");
    boundariesObject["contact"] = QString("Separable");
    // boundariesObject["contact"] = QJsonValue(waveFlumeContactType->currentText()).toString();

    QJsonArray originArray;
    originArray.append(flumeOriginX->text().toDouble());
    originArray.append(flumeOriginY->text().toDouble());
    originArray.append(flumeOriginZ->text().toDouble());
    if (0) boundariesObject["origin"] = originArray;
    else boundariesObject["domain_start"] = originArray;

    QJsonArray dimensionsArray;
    QJsonArray dimensionsEndArray;
    dimensionsArray.append(flumeLength->text().toDouble());
    dimensionsArray.append(flumeHeight->text().toDouble());
    dimensionsArray.append(flumeWidth->text().toDouble());
    dimensionsEndArray.append(flumeLength->text().toDouble() + flumeOriginX->text().toDouble());
    dimensionsEndArray.append(flumeHeight->text().toDouble() + flumeOriginY->text().toDouble());
    dimensionsEndArray.append(flumeWidth->text().toDouble() + flumeOriginZ->text().toDouble());
    if (0) boundariesObject["dimensions"] = dimensionsArray; // future schema
    else boundariesObject["domain_end"] = dimensionsEndArray; // ClaymoreUW artifact, TODO: deprecate

    boundariesObject["friction_static"] = 0.0;
    boundariesObject["friction_dynamic"] = 0.0;


    // Maybe add SWL, bools, wave-maker neutral, etc. here
    boundariesArray.append(boundariesObject);
  }

  // Wave Generation
  else if (stackedWidget->currentIndex() == BoundaryTypeEnum::WAVE_GENERATOR) {
    QJsonObject boundariesObject;

    // TODO: Add wave generator names to JSON to link to the name in ClaymoreUW enumerators
    boundariesObject["contact"] = QJsonValue(paddleContactType->currentText()).toString();

    QJsonArray originArray;

    originArray.append(paddleOriginX->text().toDouble());
    originArray.append(paddleOriginY->text().toDouble());
    originArray.append(paddleOriginZ->text().toDouble());
    if (0) boundariesObject["origin"] = originArray;
    else boundariesObject["domain_start"] = originArray;

    QJsonArray dimensionsArray;
    QJsonArray dimensionsEndArray;
    dimensionsArray.append(paddleLength->text().toDouble());
    dimensionsArray.append(paddleHeight->text().toDouble());
    dimensionsArray.append(paddleWidth->text().toDouble());
    dimensionsEndArray.append(paddleLength->text().toDouble() + paddleOriginX->text().toDouble());
    dimensionsEndArray.append(paddleHeight->text().toDouble() + paddleOriginY->text().toDouble());
    dimensionsEndArray.append(paddleWidth->text().toDouble() + paddleOriginZ->text().toDouble());
    if (0) boundariesObject["dimensions"] = dimensionsArray; // future schema
    else boundariesObject["domain_end"] = dimensionsEndArray; // ClaymoreUW artifact, TODO: deprecate

    
    boundariesObject["friction_static"] = 0.0;
    boundariesObject["friction_dynamic"] = 0.0;

    boundariesObject["object"] = QString("OSU Paddle");  
    
    if (generationMethod->currentIndex() == 0) 
    {
      // TODOL: Custom file input
      boundariesObject["object"] = QString("OSU Paddle");

      // QFileInfo paddleDisplacementFileInfo(paddleDisplacementFile->getFilename());
      QString paddleDisplacementFilename = paddleDisplacementFile->getFilename();
      QString paddleFile = paddleDisplacementFilename.mid(paddleDisplacementFilename.lastIndexOf("/"));
      // if (!paddleDisplacementFileInfo.exists()) {
      //   this->errorMessage("ERROR: Paddle Motion - file does not exist");
      //   return false;
      // }

      // boundariesObject["file"] = paddleDisplacementFile->getFilename() ; // Paddle motion file
      // QString("WaveMaker/") + paddleFile; // Paddle motion file assuming use of Data directory for claymore (TODO: relative paths)
      boundariesObject["file"] = QString("../") + QString("wmdisp_LWF_Unbroken_Amp4_SF500_twm10sec_1200hz_14032023.csv"); 
      boundariesObject["output_frequency"] = 1200.0; // TODO: Either be user set or read-in from motion_file
      boundariesObject["friction_static"] = 0.0;
      boundariesObject["friction_dynamic"] = 0.0;
    } 

    if (inpty==QString("Periodic Waves")) {
        // check for error condition, an entry had no value
        if ((alpha->text().isEmpty())||(beta->text().isEmpty())||(a->text().isEmpty())||(b->text().isEmpty())) {
            this->errorMessage("ERROR: Periodic Waves - data has not been set");
            return false;
        }
        boundariesObject["wave_height"]=alpha->text().toDouble();
        boundariesObject["wave_celerity"]=beta->text().toDouble();
        boundariesObject["wave_period"]=a->text().toDouble();
        boundariesObject["wave_duration"]=b->text().toDouble();
        boundariesObject["object"] = QString("Periodic Waves");
    } else if (inpty==QString("Preset Paddle - OSU LWF")) {
        if (dataDir->text().isEmpty()) {
            this->errorMessage("ERROR: Paddle Motion - data has not been set");
            return false;
        }

        QJsonArray paddleTimeArray;
        paddleTimeArray.append(a->text().toDouble());
        paddleTimeArray.append(b->text().toDouble());
        // boundariesObject["time"] = paddleTimeArray;
        // boundariesObject["file"] = QString(dataDir->text());
        boundariesObject["file"] = QString("../") + QString("wmdisp_LWF_Unbroken_Amp4_SF500_twm10sec_1200hz_14032023.csv");
        boundariesObject["output_frequency"] = 1200.0; // TODO: Either be user set or read-in from motion_file
        boundariesObject["object"] = QString("OSU Paddle");
    }

    boundariesArray.append(boundariesObject);
  }


  // Rigid Structures
  else if (stackedWidget->currentIndex() == BoundaryTypeEnum::RIGID_STRUCTURE) {
    QJsonObject boundariesObject;

    boundariesObject["object"] = "Box";
    boundariesObject["contact"] = QJsonValue(structContactType->currentText()).toString();
    
    QJsonArray originArray;
    originArray.append(structOriginLength->text().toDouble());
    originArray.append(structOriginHeight->text().toDouble());
    originArray.append(structOriginWidth->text().toDouble());
    if (0) boundariesObject["origin"] = originArray;
    else boundariesObject["domain_start"] = originArray;

    QJsonArray dimensionsArray;
    QJsonArray dimensionsEndArray;
    dimensionsArray.append(structLength->text().toDouble());
    dimensionsArray.append(structHeight->text().toDouble());
    dimensionsArray.append(structWidth->text().toDouble());
    dimensionsEndArray.append(structLength->text().toDouble() + structOriginLength->text().toDouble());
    dimensionsEndArray.append(structHeight->text().toDouble() + structOriginHeight->text().toDouble());
    dimensionsEndArray.append(structWidth->text().toDouble() + structOriginWidth->text().toDouble());
    if (0) boundariesObject["dimensions"] = dimensionsArray; // future schema
    else boundariesObject["domain_end"] = dimensionsEndArray; // ClaymoreUW artifact, TODO: deprecate

    boundariesObject["friction_static"] = 0.0;
    boundariesObject["friction_dynamic"] = 0.0;

    if (applyCoulombFriction->isChecked()) {
      QJsonObject frictionObject;
      QJsonArray staticFrictionArray;
      QJsonArray dynamicFrictionArray;
      frictionObject["type"] = "Coulomb";
      staticFrictionArray.append(staticFrictionWallX->text().toDouble());
      staticFrictionArray.append(staticFrictionWallY->text().toDouble());
      staticFrictionArray.append(staticFrictionWallZ->text().toDouble());
      frictionObject["static"] = staticFrictionArray;
      dynamicFrictionArray.append(dynamicFrictionWallX->text().toDouble());
      dynamicFrictionArray.append(dynamicFrictionWallY->text().toDouble());
      dynamicFrictionArray.append(dynamicFrictionWallZ->text().toDouble());
      frictionObject["dynamic"] = dynamicFrictionArray;
      // boundariesObject["friction"] = frictionObject;
      boundariesObject["friction_static"] = staticFrictionArray[0];
      boundariesObject["friction_dynamic"] = dynamicFrictionArray[0];
    }

    if (applyArray->isChecked()) {
      QJsonObject arrayObject;
      QJsonArray arrayDimensionsArray;
      QJsonArray arraySpacingArray;
      arrayDimensionsArray.append(structArrayX->text().toInt());
      arrayDimensionsArray.append(structArrayY->text().toInt());
      arrayDimensionsArray.append(structArrayZ->text().toInt());
      arraySpacingArray.append(structSpacingX->text().toDouble());
      arraySpacingArray.append(structSpacingY->text().toDouble());
      arraySpacingArray.append(structSpacingZ->text().toDouble());
      boundariesObject["array"] = arrayDimensionsArray;
      boundariesObject["spacing"] = arraySpacingArray;
    }

    // TODO: Add auto-load-cell portion of JSON to link to the name of created sensor

    boundariesArray.append(boundariesObject);
  }


  // Walls
  else if (stackedWidget->currentIndex() == BoundaryTypeEnum::RIGID_WALLS) {
    QJsonObject boundariesObject;
    boundariesObject["object"] = "Walls";
    boundariesObject["contact"] = QJsonValue(wallsContactType->currentText()).toString();

    QJsonArray originArray;
    originArray.append(originLength->text().toDouble());
    originArray.append(originHeight->text().toDouble());
    originArray.append(originWidth->text().toDouble());
    if (0) boundariesObject["origin"] = originArray;
    else boundariesObject["domain_start"] = originArray;

    QJsonArray dimensionsArray;
    QJsonArray dimensionsEndArray;
    dimensionsArray.append(wallsLength->text().toDouble());
    dimensionsArray.append(wallsHeight->text().toDouble());
    dimensionsArray.append(wallsWidth->text().toDouble());
    dimensionsEndArray.append(wallsLength->text().toDouble() + originLength->text().toDouble());
    dimensionsEndArray.append(wallsHeight->text().toDouble() + originHeight->text().toDouble());
    dimensionsEndArray.append(wallsWidth->text().toDouble() + originWidth->text().toDouble());
    if (0) boundariesObject["dimensions"] = dimensionsArray; // future schema
    else boundariesObject["domain_end"] = dimensionsEndArray; // ClaymoreUW artifact, TODO: deprecate

    boundariesObject["friction_static"] = 0.0;
    boundariesObject["friction_dynamic"] = 0.0;

    if (applyCoulombFriction->isChecked()) {
      QJsonObject frictionObject;
      QJsonArray staticFrictionArray;
      QJsonArray dynamicFrictionArray;
      frictionObject["type"] = "Coulomb";
      staticFrictionArray.append(staticFrictionWallX->text().toDouble());
      staticFrictionArray.append(staticFrictionWallY->text().toDouble());
      staticFrictionArray.append(staticFrictionWallZ->text().toDouble());
      frictionObject["static"] = staticFrictionArray;
      dynamicFrictionArray.append(dynamicFrictionWallX->text().toDouble());
      dynamicFrictionArray.append(dynamicFrictionWallY->text().toDouble());
      dynamicFrictionArray.append(dynamicFrictionWallZ->text().toDouble());
      frictionObject["dynamic"] = dynamicFrictionArray;
      // boundariesObject["friction"] = frictionObject;
      boundariesObject["friction_static"] = staticFrictionArray[0];
      boundariesObject["friction_dynamic"] = dynamicFrictionArray[0];
    }

    // if (applyInletOutlet->isChecked()) {
    //   QJsonObject inletOutletObject;
    //   QJsonObject subXObject;
    //   QJsonObject subYObject;
    //   QJsonObject subZObject;
    //   QJsonObject plusXObject;
    //   QJsonObject plusYObject;
    //   QJsonObject plusZObject;
    //   subXObject["type"] = QJsonValue(inletOutletTypeSubX->currentText()).toString();
    //   subYObject["type"] = QJsonValue(inletOutletTypeSubY->currentText()).toString();
    //   subZObject["type"] = QJsonValue(inletOutletTypeSubZ->currentText()).toString();
    //   plusXObject["type"] = QJsonValue(inletOutletTypePlusX->currentText()).toString();
    //   plusYObject["type"] = QJsonValue(inletOutletTypePlusY->currentText()).toString();
    //   plusZObject["type"] = QJsonValue(inletOutletTypePlusZ->currentText()).toString();
    //   inletOutletObject["X-"] = subXObject;
    //   inletOutletObject["Y-"] = subYObject;
    //   inletOutletObject["Z-"] = subZObject;
    //   inletOutletObject["X+"] = plusXObject;
    //   inletOutletObject["Y+"] = plusYObject;
    //   inletOutletObject["Z+"] = plusZObject;
    //   boundariesObject["inlet-outlet"] = inletOutletObject;
    // }

    boundariesArray.append(boundariesObject);
  }
  else {
    qDebug() << "Boundary type not recognized";
    return false;
  }

  jsonObject["boundaries"] = boundariesArray; // future schema

  //  jsonObject["domainSubType"]=facility->currentText();
  bathSTL->outputToJSON(jsonObject);
  paddleDisplacementFile->outputToJSON(jsonObject);

  return true;
}

bool
BoundaryMPM::inputFromJSON(QJsonObject &jsonObject)
{
  bathSTL->inputFromJSON(jsonObject);
  paddleDisplacementFile->inputFromJSON(jsonObject);


    //
    // for all entries, make sure i exists and if it does get it, otherwise return error
    //

    if (jsonObject.contains("object")) {
        inpty=jsonObject["object"].toString();
    } else {
        inpty = "Parameters";
    }

    if (inpty==QString("Periodic Waves")) {
      if (jsonObject.contains("wave_height")) {
          double theAlphaValue = jsonObject["wave_height"].toDouble();
          alpha->setText(QString::number(theAlphaValue));
      } else {
          this->errorMessage("ERROR: Periodic Waves - no \"alpha\" entry");
          return false;
      }
      if (jsonObject.contains("wave_celerity")) {
          double theBetaValue = jsonObject["wave_celerity"].toDouble();
          beta->setText(QString::number(theBetaValue));
      } else {
          this->errorMessage("ERROR: Periodic Waves  - no \"beta\" entry");
          return false;
      }
      if (jsonObject.contains("wave_period")) {
          double theAValue = jsonObject["wave_period"].toDouble();
          a->setText(QString::number(theAValue));
      } else {
          this->errorMessage("ERROR: Periodic Waves  - no \"a\" entry");
          return false;
      }
      if (jsonObject.contains("wave_duration")) {
          double theBValue = jsonObject["wave_duration"].toDouble();
          b->setText(QString::number(theBValue));
      } else {
          this->errorMessage("ERROR: Periodic Waves - no \"b\" entry");
          return false;
      }

    } else if (inpty==QString("Preset Paddle - OSU LWF")) {
      if (jsonObject.contains("time")) {
          QJsonArray theTimeArray = jsonObject["time"].toArray();
          a->setText(QString::number(theTimeArray[0].toDouble()));
          b->setText(QString::number(theTimeArray[1].toDouble()));
      } else {
          this->errorMessage("ERROR: Paddle Motion - no \"time\" entry");
          return false;
      }
      if (jsonObject.contains("file")) {
          QString theDataDir = jsonObject["file"].toString();
          dataDir->setText(theDataDir);
      } else {
          this->errorMessage("ERROR: Paddle Motion - no \"file\" entry");
          return false;
      }
    } else if (inpty==QString("Preset Paddle - OSU DWB")) {
      if (jsonObject.contains("time")) {
          QJsonArray theTimeArray = jsonObject["time"].toArray();
          a->setText(QString::number(theTimeArray[0].toDouble()));
          b->setText(QString::number(theTimeArray[1].toDouble()));
      } else {
          this->errorMessage("ERROR: Paddle Motion - no \"time\" entry");
          return false;
      }
      if (jsonObject.contains("file")) {
          QString theDataDir = jsonObject["file"].toString();
          dataDir->setText(theDataDir);
      } else {
          this->errorMessage("ERROR: Paddle Motion - no \"file\" entry");
          return false;
      }
    }
  
    //this->updateDistributionPlot();
    return true;
}

bool
BoundaryMPM::copyFiles(QString &destDir)
{
    if (inpty==QString("Preset Paddle - OSU LWF") || inpty==QString("Preset Paddle - OSU DWB") || inpty==QString("Paddle")) {
        return QFile::copy(dataDir->text(), destDir);
    } else {
        return true;
    }
  if (bathSTL) {
    if (!bathSTL->copyFile(destDir))
      qDebug() << "Error copying bathymetry file: " << bathSTL->getFilename();
  }
  if (paddleDisplacementFile) {
    if (!paddleDisplacementFile->copyFile(destDir))
      qDebug() << "Error copying paddle displacement file: " << paddleDisplacementFile->getFilename();
  }


  return true;    
}

QString
BoundaryMPM::getAbbreviatedName(void) {
  return QString("WM");
}

bool readCSVRow (QTextStream &in, QStringList *row) {

    static const int delta[][5] = {
        //  ,    "   \n    ?  eof
        {   1,   2,  -1,   0,  -1  }, // 0: parsing (store char)
        {   1,   2,  -1,   0,  -1  }, // 1: parsing (store column)
        {   3,   4,   3,   3,  -2  }, // 2: quote entered (no-op)
        {   3,   4,   3,   3,  -2  }, // 3: parsing inside quotes (store char)
        {   1,   3,  -1,   0,  -1  }, // 4: quote exited (no-op)
        // -1: end of row, store column, success
        // -2: eof inside quotes
    };

    row->clear();

    if (in.atEnd())
        return false;

    int state = 0, t;
    char ch;
    QString cell;

    while (state >= 0) {

        if (in.atEnd())
            t = 4;
        else {
            in >> ch;
            if (ch == ',') t = 0;
            else if (ch == '\"') t = 1;
            else if (ch == '\n') t = 2;
            else t = 3;
        }

        state = delta[state][t];

        if (state == 0 || state == 3) {
            cell += ch;
        } else if (state == -1 || state == 1) {
            row->append(cell);
            cell = "";
        }

    }

    if (state == -2)
        throw std::runtime_error("End-of-file found while inside quotes.");

    return true;

}

void
BoundaryMPM::updateDistributionPlot() {
    double alp=0, bet=0, aa=0, bb=0, me=0, st=0;
    int numSteps = 100;
    if ((this->inpty)==QString("Periodic Waves")) {
        alp=alpha->text().toDouble();
        bet=beta->text().toDouble();
        aa=a->text().toDouble();
        bb=b->text().toDouble();
        me = (aa*bet+bb*alp)/(alp+bet);
        st = sqrt( alp*bet*(bb-aa)/pow(alp+bet,2)/(alp+bet+1)  );
     } 
     else if (((this->inpty)==QString("Preset Paddle - OSU LWF")) || (this->inpty==QString("Preset Paddle - OSU DWB")) || (this->inpty==QString("Paddle"))) {
        if (dataDir->text().isEmpty()) {
            this->errorMessage("ERROR: Paddle Motion - data has not been set");
            return;
        }
        QString csvFileName = dataDir->text();
        QFile csv(csvFileName);
        csv.open(QFile::ReadOnly | QFile::Text);

        QTextStream in(&csv);
        QStringList row;
        QStringList firstColumn;
        QStringList secondColumn;
        QStringList thirdColumn;
        
        numSteps = 0; // reset

        // Assume no header lines
        while (readCSVRow(in, &row)) {
            firstColumn.append(row[0]);
            secondColumn.append(row[1]);
            thirdColumn.append(row[2]);
            numSteps++;
        }

        csv.close();

        QVector<double> x(numSteps); // time
        QVector<double> y(numSteps); // displacement
        for (int i=0; i<numSteps; i++) {
            x[i] = firstColumn[i].toDouble();
            y[i] = secondColumn[i].toDouble();
        }

        me = 2.0;
        alp = 1.0;
        bet = 1.0;

        aa = 0.0;
        bb=b->text().toDouble();

        // plot
        thePlot->clear();
        thePlot->drawPDF(x,y);
        return;

    }


    if (aa>bb) {
        thePlot->clear();
        return;
    }

    if (this->inpty==QString("Periodic Waves")) {
      if (alp >= 0.0 && bet > 0.0 && me != aa) {
          double min = aa; // defined in x>0
          double max = bb;
          QVector<double> x(100);
          QVector<double> y(100);
          for (int i=0; i<100; i++) {
              double xi = min + i*(max-min)/99;
              x[i] = xi;
              double betai=tgamma(alp)*tgamma(bet)/tgamma(alp+bet);
              y[i] = pow(xi-aa,alp-1)*pow(bb-xi,bet-1)/betai/pow(bb-aa,alp+bet-1);
          }
          thePlot->clear();
          thePlot->drawPDF(x,y);
      } else {
          thePlot->clear();
      }
    }


//        else {
//            QVector<double> x(100);
//            QVector<double> y(100);
//            QVector<double> x1(100);
//            QVector<double> y1(100);
//            for (int i=0; i<100; i++) {
//                x[i] =  aa+1;
//                y[i] =  bb+10;
//                x1[i] =  me+1;
//                y1[i] =  st+10;
//            }
//            thePlot->clear();
//            thePlot->drawPDF(x,y);
//            thePlot->drawPDF(x1,y1);
//        }
}

bool
BoundaryMPM::setDigitalTwin(int twinIdx)
{
  // TODO: Refactor to rely more on "facility" for consistency, rather than hard-coding
  int numTwins = 5; // Currently have 5 twins in prototype
  if (twinIdx >= numTwins) return false;


  if (boundaryType->currentIndex() == 1) {
    facility->setCurrentIndex(twinIdx); // Change the digital twin facility 
  }
  else if (boundaryType->currentIndex() == 2) {
    if (twinIdx == 0) {
      paddleOriginX->setText(QString::number(1.7));
      paddleOriginY->setText(QString::number(-0.1));
      paddleOriginZ->setText(QString::number(-0.1));
      paddleLength->setText(QString::number(0.2));
      paddleHeight->setText(QString::number(4.6));
      paddleWidth->setText(QString::number(3.85));
    } else if (twinIdx == 1) {
      paddleOriginX->setText(QString::number(-0.1));
      paddleOriginY->setText(QString::number(-0.1));
      paddleOriginZ->setText(QString::number(-0.1));
      paddleLength->setText(QString::number(0.2));
      paddleHeight->setText(QString::number(2.7));
      paddleWidth->setText(QString::number(26.7));
    } else if (twinIdx == 2) {
      paddleOriginX->setText(QString::number(0));
      paddleOriginY->setText(QString::number(0));
      paddleOriginZ->setText(QString::number(0));
      paddleLength->setText(QString::number(0.2));
      paddleHeight->setText(QString::number(1.2));
      paddleWidth->setText(QString::number(0.9));
    } else if (twinIdx == 3) {
      paddleOriginX->setText(QString::number(0.5));
      paddleOriginY->setText(QString::number(0.1));
      paddleOriginZ->setText(QString::number(0.0));
      paddleLength->setText(QString::number(0.05));
      paddleHeight->setText(QString::number(0.9));
      paddleWidth->setText(QString::number(4.0));
    } else if (twinIdx == 4) {
      paddleOriginX->setText(QString::number(7.0));
      paddleOriginY->setText(QString::number(0.0));
      paddleOriginZ->setText(QString::number(0.0));
      paddleLength->setText(QString::number(0.2));
      paddleHeight->setText(QString::number(2.0));
      paddleWidth->setText(QString::number(2.0));
    }

  }
  else if (boundaryType->currentIndex() == 3) {
    // Rigid structures
    // Preset rigid structures for the digital twin experiments
    if (twinIdx == 0) { // OSU LWF
      structContactType->setCurrentIndex(0); // Separable
      structObjectType->setCurrentIndex(twinIdx); // Orange Box - OSU LWF
      structLength->setText(QString::number(1.0));
      structHeight->setText(QString::number(0.625));
      structWidth->setText(QString::number(1.0));
      structOriginLength->setText(QString::number(45.8));
      structOriginHeight->setText(QString::number(2.0));
      structOriginWidth->setText(QString::number(1.325));
      applyArray->setChecked(false);
      structSpacingX->setText(QString::number(1.1));
      structSpacingY->setText(QString::number(0.625));
      structSpacingZ->setText(QString::number(1.1));
      structArrayX->setText(QString::number(1));
      structArrayY->setText(QString::number(1));
      structArrayZ->setText(QString::number(1));
    }
    else if (twinIdx == 1) { // OSU DWB
      structContactType->setCurrentIndex(0); // Separable
      structObjectType->setCurrentIndex(twinIdx); // Square Columns - OSU DWB
      structLength->setText(QString::number(0.4));
      structHeight->setText(QString::number(0.3));
      structWidth->setText(QString::number(0.4));
      structOriginLength->setText(QString::number(35.29));
      structOriginHeight->setText(QString::number(1.0));
      structOriginWidth->setText(QString::number(8.2));
      applyArray->setChecked(true);
      structSpacingX->setText(QString::number(0.8));
      structSpacingY->setText(QString::number(0.8));
      structSpacingZ->setText(QString::number(0.8));
      structArrayX->setText(QString::number(1));
      structArrayY->setText(QString::number(1));
      structArrayZ->setText(QString::number(12));
    }
    else if (twinIdx == 2) { // UW WASIRF
      structContactType->setCurrentIndex(0); // Separable
      structObjectType->setCurrentIndex(twinIdx); // Grey Box?
      structLength->setText(QString::number(0.254));
      structHeight->setText(QString::number(0.1524));
      structWidth->setText(QString::number(0.254));
      // TODO: Recheck specs of the grey box from Nikkis work (10x6x10"?, 1:4 Froude of OSU-LWF)
      structOriginLength->setText(QString::number(8.0));
      structOriginHeight->setText(QString::number(0.1)); // Recheck the height
      structOriginWidth->setText(QString::number(0.473));
      applyArray->setChecked(false);
      structSpacingX->setText(QString::number(0.3));
      structSpacingY->setText(QString::number(0.2));
      structSpacingZ->setText(QString::number(0.3));
      structArrayX->setText(QString::number(1));
      structArrayY->setText(QString::number(1));
      structArrayZ->setText(QString::number(1));
    }
    else if (twinIdx == 3) { // WU TWB
      structContactType->setCurrentIndex(0); // Separable
      structObjectType->setCurrentIndex(twinIdx); // Box?
      structLength->setText(QString::number(0.1));
      structHeight->setText(QString::number(0.3));
      structWidth->setText(QString::number(0.1));
      structOriginLength->setText(QString::number(5.11)); // 0.71 from quay, 0.66 rel to dim
      structOriginHeight->setText(QString::number(0.255));
      structOriginWidth->setText(QString::number(1.3));
      applyArray->setChecked(true);
      structSpacingX->setText(QString::number(0.45));
      structSpacingY->setText(QString::number(0.4));
      structSpacingZ->setText(QString::number(0.325));
      structArrayX->setText(QString::number(2));
      structArrayY->setText(QString::number(1));
      structArrayZ->setText(QString::number(5));
      // 0.325 centerline spacing transverse, 0.225 gap
      // 0.45 centerline longitudinal, 0.35 gap
    }
    else if (twinIdx == 4) { // USGS DFF
      structContactType->setCurrentIndex(0); // Separable
      // Placeholder structure 
      structLength->setText(QString::number(0.25));
      structHeight->setText(QString::number(0.25));
      structWidth->setText(QString::number(0.25));
      structOriginLength->setText(QString::number(80.0));
      structOriginHeight->setText(QString::number(0.0));
      structOriginWidth->setText(QString::number(0.75));
      applyArray->setChecked(false);
      structSpacingX->setText(QString::number(0.3));
      structSpacingY->setText(QString::number(0.3));
      structSpacingZ->setText(QString::number(0.3));
      structArrayX->setText(QString::number(1));
      structArrayY->setText(QString::number(1));
      structArrayZ->setText(QString::number(1));

    }
  }
  else if (boundaryType->currentIndex() == 4) {
    // Rigid walls
    // Make sure the walls fit the wave flume's dimensions
    applyCoulombFriction->setChecked(false);
    applyCoulombFriction->setEnabled(false);
    applyInletOutlet->setChecked(false);
    applyInletOutlet->setEnabled(false);
    if (twinIdx == 0) { // OSU LWF
      wallsContactType->setCurrentIndex(0); // Separable
      wallsLength->setText(QString::number(90.0));
      wallsHeight->setText(QString::number(4.5));
      wallsWidth->setText(QString::number(3.65));
    }
    else if (twinIdx == 1) { // OSU DWB
      wallsContactType->setCurrentIndex(0); // Separable
      wallsLength->setText(QString::number(48.8));
      wallsHeight->setText(QString::number(2.7));
      wallsWidth->setText(QString::number(26.5));
    }
    else if (twinIdx == 2) { // UW WASIRF
      wallsContactType->setCurrentIndex(0); // Separable
      wallsLength->setText(QString::number(12));
      wallsHeight->setText(QString::number(1.2));
      wallsWidth->setText(QString::number(0.9));
    }
    else if (twinIdx == 3) { // WU TWB
      wallsContactType->setCurrentIndex(0); // Separable
      wallsLength->setText(QString::number(9.0));
      wallsHeight->setText(QString::number(1.0));
      wallsWidth->setText(QString::number(4.0));
      applyCoulombFriction->setEnabled(true);
      // applyCoulombFriction->setChecked(false);
    }
    else if (twinIdx == 4) { // USGS DFF
      wallsContactType->setCurrentIndex(0); // Separable
      wallsLength->setText(QString::number(100.0));
      wallsHeight->setText(QString::number(2.0));
      wallsWidth->setText(QString::number(2.0));
      applyCoulombFriction->setEnabled(true);
      // applyCoulombFriction->setChecked(false);
    }
    originLength->setText(QString::number(0.0));
    originHeight->setText(QString::number(0.0));
    originWidth->setText(QString::number(0.0));
  }
  else if (boundaryType->currentIndex() == 0) {
    // Custom, so probably don't do anything
  }
  else {
    qDebug() << "Boundary type not recognized";
    return false;
  }
  return true;

  // TODO: Change parameters for things other than wave flume boundary (e.g. rigid structure)
}

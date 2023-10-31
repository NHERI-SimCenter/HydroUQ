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

#include <BoundariesMPM.h>
#include <QLabel>
#include <QComboBox>
#include <QGroupBox>
#include <QGridLayout>
#include <QTabWidget>
#include <QStackedWidget>
#include <QDebug>

#include <SC_ComboBox.h>
#include <SC_DoubleLineEdit.h>
#include <SC_IntLineEdit.h>
#include <SC_TableEdit.h>
#include <SC_FileEdit.h>


BoundariesMPM::BoundariesMPM(QWidget *parent)
  :SimCenterWidget(parent)
{
  QGroupBox *domainSettings = new QGroupBox("Domain");
  QGridLayout *domainSettingsLayout = new QGridLayout();  
  domainSettings->setLayout(domainSettingsLayout);  

  QStringList facilityList; facilityList << "OSU LWF" << "UW WASIRF" << "CLOSED" << "INLETOUTLET";
  facility = new SC_ComboBox("domainSubType",facilityList);
  domainSettingsLayout->addWidget(new QLabel("Facility"),0,0);
  domainSettingsLayout->addWidget(facility,0,1);

  QGroupBox *dimensionsBox = new QGroupBox("");
  QGridLayout *dimensionsBoxLayout = new QGridLayout();
  dimensionsBox->setLayout(dimensionsBoxLayout);

  dimensionsBoxLayout->addWidget(new QLabel("Flume Length"), 0, 0);
  dimensionsBoxLayout->addWidget(new QLabel("m"), 0, 2);
  dimensionsBoxLayout->addWidget(new QLabel("Flume Height"), 1, 0);
  dimensionsBoxLayout->addWidget(new QLabel("m"), 1, 2);
  dimensionsBoxLayout->addWidget(new QLabel("Flume Width"), 2, 0);
  dimensionsBoxLayout->addWidget(new QLabel("m"), 2, 2);
  dimensionsBoxLayout->addWidget(new QLabel("Cell Size"), 3, 0);
  dimensionsBoxLayout->addWidget(new QLabel("m"), 3, 2);      
  
  flumeLength = new SC_DoubleLineEdit("flumeLength",104.0);
  flumeHeight = new SC_DoubleLineEdit("flumeHeight",4.6);
  flumeWidth = new SC_DoubleLineEdit("flumeWidth",3.658);
  cellSize = new SC_DoubleLineEdit("cellSize",0.1);    

  dimensionsBoxLayout->addWidget(flumeLength, 0, 1);
  dimensionsBoxLayout->addWidget(flumeHeight, 1, 1);
  dimensionsBoxLayout->addWidget(flumeWidth, 2, 1);
  dimensionsBoxLayout->addWidget(cellSize, 3, 1);

  domainSettingsLayout->addWidget(dimensionsBox,0,2,2,5);  

  QTabWidget *tabWidget = new QTabWidget();
  QWidget *theBathymetry = new QWidget();
  QWidget *theInitialConditions = new QWidget();
  QWidget *theWaveGeneration = new QWidget();
  QWidget *theTurbulenceSettings = new QWidget();
  
  tabWidget->addTab(theBathymetry,"Bathymetry");
  tabWidget->addTab(theInitialConditions,"Initial Conditions");
  tabWidget->addTab(theWaveGeneration,"Wave Generation");
  tabWidget->addTab(theTurbulenceSettings,"Turbulance");  
  
  QGridLayout *layout = new QGridLayout();
  this->setLayout(layout);

  layout->addWidget(domainSettings,0,0);
  layout->addWidget(tabWidget,1,0);  

  //
  // connect the facility QComboBox to change entries to default values if selected
  //
  
  connect(facility, &QComboBox::currentTextChanged, [=](QString val) {
    if (val == "OSU LWF") {
      flumeLength->setText("104.0");
      flumeHeight->setText("4.6");
      flumeWidth->setText("3.658");
      cellSize->setText("0.1");    
    } else if (val == "UW WASIRF") {
      flumeLength->setText("12.19");
      flumeHeight->setText("1.22");
      flumeWidth->setText("0.914");
      cellSize->setText("0.038");    
    } 
  });

  //
  // instead of more classes lets just do simple tabbed widgets
  //

  // 1. initial condotions
  stillWaterLevel = new SC_DoubleLineEdit("stillWaterLevel",2.0);
  initVel = new SC_DoubleLineEdit("initVelocity",0.0);
  velFile = new SC_FileEdit("velocityFile");
  refPressure = new SC_DoubleLineEdit("refPressure",0.0);
  
  QGridLayout *initLayout = new QGridLayout();
  theInitialConditions->setLayout(initLayout);
  
  initLayout->addWidget(new QLabel("Still Water Level"),0,0);
  initLayout->addWidget(new QLabel("Initial Velocity"),1,0);
  initLayout->addWidget(new QLabel("Reference Pressure"),2,0);
  initLayout->addWidget(new QLabel("Velocity Time History File"),3,0);  
  initLayout->addWidget(new QLabel("meters"),0,2);
  initLayout->addWidget(new QLabel("meters/second"),1,2);
  initLayout->addWidget(new QLabel("Pascals"),2,2);
  

  

  initLayout->addWidget(stillWaterLevel,0,1);
  initLayout->addWidget(initVel,1,1);
  initLayout->addWidget(refPressure,2,1);
  initLayout->addWidget(velFile,3,1);
  initLayout->setRowStretch(4,1);


  // 2. turbulance conditions
  referenceLength = new SC_DoubleLineEdit("turbRefLength",0.125);
  turbulanceIntensity = new SC_DoubleLineEdit("turbIntensity",0.25);
  referenceVel = new SC_DoubleLineEdit("turbReferenceVel",5);
  
  QGridLayout *turbLayout = new QGridLayout();
  theTurbulenceSettings->setLayout(turbLayout);
  
  turbLayout->addWidget(new QLabel("Reference Length"),0,0);
  turbLayout->addWidget(new QLabel("Turbulence Intensity"),1,0);
  turbLayout->addWidget(new QLabel("Reference (Mean) Velocity"),2,0);
  turbLayout->addWidget(new QLabel("m"),0,2);
  turbLayout->addWidget(new QLabel("unitless"),1,2);
  turbLayout->addWidget(new QLabel("m/s"),2,2);  

  turbLayout->addWidget(referenceLength,0,1);
  turbLayout->addWidget(turbulanceIntensity,1,1);
  turbLayout->addWidget(referenceVel,2,1);
  turbLayout->setRowStretch(3,1);

  // 3. Bathymetry .. getting a little more complicated!
  //    need to use ComboBox and StackedWidget
  QGridLayout *theBathymetryLayout = new QGridLayout();
  theBathymetry->setLayout(theBathymetryLayout);
  
  QStringList bathOptions; bathOptions << "Point List" << "STL File";
  bathymetryComboBox = new SC_ComboBox("bathType",bathOptions);
  
  QStringList bathXZHeadings; bathXZHeadings << "Position Along Flume (m)" << "Height (m)";
  QStringList dataBathXZ; dataBathXZ << "35" << "0" << "42" << "1.75" << "56" << "2.5" << "105" << "2.5";
  bathXZData = new SC_TableEdit("bathXZData",bathXZHeadings, 4, dataBathXZ);
  bathSTL = new SC_FileEdit("bathSTL");

  QWidget *ptWidget = new QWidget(); // going to add figure which is why the layout
  QGridLayout *ptLayout = new QGridLayout();
  ptLayout->addWidget(bathXZData, 0, 0);
  ptWidget->setLayout(ptLayout);

  QWidget *stlWidget = new QWidget();
  QGridLayout *stlLayout = new QGridLayout();
  stlLayout->addWidget(new QLabel("Surface File (stl)"),0,0);
  stlLayout->addWidget(bathSTL,0,1);
  stlLayout->setRowStretch(1,1);  
  stlWidget->setLayout(stlLayout);
  
  QStackedWidget *bathStack = new QStackedWidget();
  bathStack->addWidget(ptWidget);
  bathStack->addWidget(stlWidget);

  theBathymetryLayout->addWidget(new QLabel("Source Bathymetry"), 0,0);
  theBathymetryLayout->addWidget(bathymetryComboBox,0,1);
  theBathymetryLayout->addWidget(bathStack,1,0,1,2);

  // connext bathymetry to show correct widget
  connect(bathymetryComboBox, QOverload<int>::of(&QComboBox::activated),
	  bathStack, &QStackedWidget::setCurrentIndex);


  // 4. Wave Generation .. as complicated as previous!
  //    need to use ComboBox and StackedWidget
  QGridLayout *theWaveGenLayout = new QGridLayout();
  theWaveGeneration->setLayout(theWaveGenLayout);
  
  QStringList genOptions; genOptions << "Paddle Generated Waves" << "Periodic Waves" << "No Waves";
  waveGenComboBox = new SC_ComboBox("waveType",genOptions);
  
  paddleDisplacementFile = new SC_FileEdit("paddleDispFile");
  waveMag = new SC_DoubleLineEdit("periodicWaveMagnitude",1.0);
  waveCelerity = new SC_DoubleLineEdit("periodicWaveCelerity",1.0);
  waveRepeatSpeed = new SC_DoubleLineEdit("periodicWaveRepeatPeriod",1.0);

  QWidget *paddleWidget = new QWidget();
  QGridLayout *paddleLayout = new QGridLayout();
  paddleLayout->addWidget(new QLabel("Paddle Displacement File"),0,0);
  paddleLayout->addWidget(paddleDisplacementFile,0,1);
  paddleLayout->setRowStretch(1,1);  
  paddleWidget->setLayout(paddleLayout);

  QWidget *periodicWidget = new QWidget();
  QGridLayout *periodicLayout = new QGridLayout();  
  periodicLayout->addWidget(waveMag,0,1);
  periodicLayout->addWidget(waveCelerity,1,1);
  periodicLayout->addWidget(waveRepeatSpeed,2,1);
  
  periodicLayout->addWidget(new QLabel("Height"),0,0);
  periodicLayout->addWidget(new QLabel("meter"),0,2);
  periodicLayout->addWidget(new QLabel("Celerity"),1,0);
  periodicLayout->addWidget(new QLabel("meters/sec"),1,2);
  periodicLayout->addWidget(new QLabel("Repeat Period"),2,0);
  periodicLayout->addWidget(new QLabel("sec."),2,2);
  periodicLayout->setRowStretch(4,1);
  periodicWidget->setLayout(periodicLayout);

  
  QStackedWidget *waveGenStack = new QStackedWidget();
  waveGenStack->addWidget(paddleWidget);
  waveGenStack->addWidget(periodicWidget);  

  theWaveGenLayout->addWidget(new QLabel("Generation Method"),0,0);
  theWaveGenLayout->addWidget(waveGenComboBox,0,1);
  theWaveGenLayout->addWidget(waveGenStack,1,0,1,2);
  
  // connext bathymetry to show correct widget
  connect(waveGenComboBox, QOverload<int>::of(&QComboBox::activated),
	  waveGenStack, &QStackedWidget::setCurrentIndex);

}

BoundariesMPM::~BoundariesMPM()
{

}

bool
BoundariesMPM::outputToJSON(QJsonObject &jsonObject)
{
  facility->outputToJSON(jsonObject);
  flumeLength->outputToJSON(jsonObject);
  flumeHeight->outputToJSON(jsonObject);
  flumeWidth->outputToJSON(jsonObject);
  cellSize->outputToJSON(jsonObject);
  
  // init Conditions
  stillWaterLevel->outputToJSON(jsonObject);
  initVel->outputToJSON(jsonObject);
  velFile->outputToJSON(jsonObject);  
  refPressure->outputToJSON(jsonObject);
  
  // turbilence settings
  referenceLength->outputToJSON(jsonObject);
  turbulanceIntensity->outputToJSON(jsonObject);
  referenceVel->outputToJSON(jsonObject);
  
  // bathymetry
  bathymetryComboBox->outputToJSON(jsonObject);
  bathXZData->outputToJSON(jsonObject);
  bathSTL->outputToJSON(jsonObject);
  
  // wave generation
  waveGenComboBox->outputToJSON(jsonObject);
  paddleDisplacementFile->outputToJSON(jsonObject);    
  waveMag->outputToJSON(jsonObject);
  waveCelerity->outputToJSON(jsonObject);
  waveRepeatSpeed->outputToJSON(jsonObject);
  
  return true;
}

bool
BoundariesMPM::inputFromJSON(QJsonObject &jsonObject)
{
  facility->inputFromJSON(jsonObject);
  flumeLength->inputFromJSON(jsonObject);
  flumeHeight->inputFromJSON(jsonObject);
  flumeWidth->inputFromJSON(jsonObject);
  cellSize->inputFromJSON(jsonObject);
  
  // init Conditions
  stillWaterLevel->inputFromJSON(jsonObject);
  initVel->inputFromJSON(jsonObject);
  velFile->inputFromJSON(jsonObject);  
  refPressure->inputFromJSON(jsonObject);
  
  // turbilence settings
  referenceLength->inputFromJSON(jsonObject);
  turbulanceIntensity->inputFromJSON(jsonObject);
  referenceVel->inputFromJSON(jsonObject);
  
  // bathymetry
  bathymetryComboBox->inputFromJSON(jsonObject);
  bathXZData->inputFromJSON(jsonObject);
  bathSTL->inputFromJSON(jsonObject);
  
  // wave generation
  waveGenComboBox->inputFromJSON(jsonObject);
  paddleDisplacementFile->inputFromJSON(jsonObject);    
  waveMag->inputFromJSON(jsonObject);
  waveCelerity->inputFromJSON(jsonObject);
  waveRepeatSpeed->inputFromJSON(jsonObject);
  
  return true;
}


bool
BoundariesMPM::copyFiles(QString &destDir)
{
  velFile->copyFile(destDir);  
  bathSTL->copyFile(destDir);
  paddleDisplacementFile->copyFile(destDir);    
  
  return true;
}


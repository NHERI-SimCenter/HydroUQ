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
#include <SC_CheckBox.h>


BoundariesMPM::BoundariesMPM(QWidget *parent)
  :SimCenterWidget(parent)
{

  QGridLayout *layout = new QGridLayout();
  this->setLayout(layout);

  QTabWidget *tabWidget = new QTabWidget();
  QWidget *theWaveFlume = new QWidget();
  QWidget *theWaveGeneration = new QWidget();
  QWidget *theStructures = new QWidget();
  QWidget *theWalls = new QWidget();
  
  tabWidget->addTab(theWaveFlume,"Flume Facility");
  tabWidget->addTab(theWaveGeneration,"Wave Generation");  
  tabWidget->addTab(theStructures,"Rigid Structures");
  tabWidget->addTab(theWalls,"Walls");

  layout->addWidget(tabWidget);

  QGridLayout *waveFlumeLayout = new QGridLayout();
  theWaveFlume->setLayout(waveFlumeLayout);

  QStringList facilityList; facilityList << "Hinsdale Large Wave Flume (OSU LWF)" << "Hinsdale Directional Wave Basin (OSU DWB)" <<  "Wind-Air-Sea Interaction Facility (UW WASIRF)" << "Waseda University's Tsunami Wave Basin (WU TWB)" << "U.S. Geo. Survey's Debris Flow Flume (USGS DFF)" << "CLOSED" << "INLETOUTLET";
  facility = new SC_ComboBox("domainSubType",facilityList);
  waveFlumeLayout->addWidget(new QLabel("Facility"),0,0);
  waveFlumeLayout->addWidget(facility,0,1);

  QGroupBox *dimensionsBox = new QGroupBox("");
  QGridLayout *dimensionsBoxLayout = new QGridLayout();
  dimensionsBox->setLayout(dimensionsBoxLayout);


  int numRow = 0;  
  flumeLength = new SC_DoubleLineEdit("flumeLength",104.0);  
  dimensionsBoxLayout->addWidget(new QLabel("Flume Length"), numRow, 0);
  dimensionsBoxLayout->addWidget(flumeLength, numRow, 1);  
  dimensionsBoxLayout->addWidget(new QLabel("m"), numRow++, 2);
  
  flumeHeight = new SC_DoubleLineEdit("flumeHeight",4.6);  
  dimensionsBoxLayout->addWidget(new QLabel("Flume Height"), numRow, 0);
  dimensionsBoxLayout->addWidget(flumeHeight, numRow, 1);  
  dimensionsBoxLayout->addWidget(new QLabel("m"), numRow++, 2);

  flumeWidth = new SC_DoubleLineEdit("flumeWidth",3.658);
  dimensionsBoxLayout->addWidget(new QLabel("Flume Width"), numRow, 0);
  dimensionsBoxLayout->addWidget(flumeWidth, numRow, 1);  
  dimensionsBoxLayout->addWidget(new QLabel("m"), numRow++, 2);

  numRow = 0;
  flumeOriginX = new SC_DoubleLineEdit("flumeOriginX",0.0);
  dimensionsBoxLayout->addWidget(new QLabel("Origin (X)"), numRow, 3);  
  dimensionsBoxLayout->addWidget(flumeOriginX, numRow,4);
  dimensionsBoxLayout->addWidget(new QLabel("m"), numRow++, 5);

  flumeOriginY = new SC_DoubleLineEdit("flumeOriginY",0.0);
  dimensionsBoxLayout->addWidget(new QLabel("Origin (Y)"), numRow, 3);    
  dimensionsBoxLayout->addWidget(flumeOriginY, numRow,4);
  dimensionsBoxLayout->addWidget(new QLabel("m"), numRow++, 5);

  flumeOriginZ = new SC_DoubleLineEdit("flumeOriginZ",0.0);
  dimensionsBoxLayout->addWidget(new QLabel("Origin (Z)"), numRow, 3);      
  dimensionsBoxLayout->addWidget(flumeOriginZ, numRow,4);
  dimensionsBoxLayout->addWidget(new QLabel("m"), numRow++, 5);  

  waveFlumeLayout->addWidget(dimensionsBox,1,0,3,4);

  QStringList bathXZHeadings; bathXZHeadings << "Position Along Flume (m)" << "Height (m)";
  QStringList dataBathXZ; dataBathXZ << "35" << "0" << "42" << "1.75" << "56" << "2.5" << "105" << "2.5";
  bathXZData = new SC_TableEdit("bathXZData",bathXZHeadings, 4, dataBathXZ);

  waveFlumeLayout->addWidget(new QLabel("Bathymetry"),5,0,1,4);    
  waveFlumeLayout->addWidget(bathXZData,6,0,1,4);  
  
  

  //
  // connect the facility QComboBox to change entries to default values if selected
  //
  
  connect(facility, &QComboBox::currentTextChanged, [=](QString val) {
    if (val == "Hinsdale Large Wave Flume (OSU LWF)") {
      flumeLength->setText("104.0");
      flumeHeight->setText("4.6");
      flumeWidth->setText("3.658");
    } else if (val == "Hinsdale Directional Wave Basin (OSU DWB)") {
      flumeLength->setText("48.8");
      flumeHeight->setText("26.5");
      flumeWidth->setText("2.1");
    } else if (val == "Wind-Air-Sea Interaction Facility (UW WASIRF)") {
      flumeLength->setText("12.19");
      flumeHeight->setText("1.22");
      flumeWidth->setText("0.914");
    } else if (val == "Waseda University's Tsunami Wave Basin (WU TWB)") {
      flumeLength->setText("9.0");
      flumeHeight->setText("1.0");
      flumeWidth->setText("4.0");
    } else if (val == "U.S. Geo. Survey's Debris Flow Flume (USGS DFF)") {
      flumeLength->setText("90.0");
      flumeHeight->setText("2.0");
      flumeWidth->setText("2.0");
    } 
  });

  //
  // instead of more classes lets just do simple tabbed widgets
  //

  /*
  // 1. initial conditions
  stillWaterLevel = new SC_DoubleLineEdit("stillWaterLevel",2.0);
  initVel = new SC_DoubleLineEdit("initVelocity",0.0);
  velFile = new SC_FileEdit("velocityFile");
  refPressure = new SC_DoubleLineEdit("refPressure",0.0);
  
  QGridLayout *initLayout = new QGridLayout();
  theObstacles->setLayout(initLayout);
  
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
  */

  // wave generator
  
  QGridLayout *paddleLayout = new QGridLayout();
  theWaveGeneration->setLayout(paddleLayout);

  numRow = 0;
  QStringList listWaveGeneration; listWaveGeneration << "Preset Paddle Motion";
  
  generationMethod = new SC_ComboBox("generationMethod",listWaveGeneration);
  paddleLayout->addWidget(new QLabel("Generation Method"),numRow,0);
  paddleLayout->addWidget(generationMethod,numRow++,1);

  numRow = 1;
  paddleLength = new SC_DoubleLineEdit("paddleLength",0.2);
  paddleLayout->addWidget(new QLabel("Paddle Length (X)"),numRow, 0);
  paddleLayout->addWidget(paddleLength,numRow,1);
  paddleLayout->addWidget(new QLabel("m"),numRow++, 2);  

  paddleHeight = new SC_DoubleLineEdit("paddleHeight",4.0);
  paddleLayout->addWidget(new QLabel("Paddle Height (Y)"),numRow, 0);
  paddleLayout->addWidget(paddleHeight,numRow,1);
  paddleLayout->addWidget(new QLabel("m"),numRow++, 2);

  paddleWidth = new SC_DoubleLineEdit("paddleWidth",4.0);
  paddleLayout->addWidget(new QLabel("Paddle Width (Z)"),numRow, 0);
  paddleLayout->addWidget(paddleWidth,numRow,1);
  paddleLayout->addWidget(new QLabel("m"),numRow++, 2);

  numRow = 1;
  paddleLength = new SC_DoubleLineEdit("paddleOriginX",0.0);
  paddleLayout->addWidget(new QLabel("Origin (X)"),numRow, 3);
  paddleLayout->addWidget(paddleLength,numRow,4);
  paddleLayout->addWidget(new QLabel("m"),numRow++, 5);  

  paddleHeight = new SC_DoubleLineEdit("paddleOriginY",0.0);
  paddleLayout->addWidget(new QLabel("Origin (Y)"),numRow, 3);
  paddleLayout->addWidget(paddleHeight,numRow,4);
  paddleLayout->addWidget(new QLabel("m"),numRow++, 5);    

  paddleWidth = new SC_DoubleLineEdit("paddleOriginZ",0.0);
  paddleLayout->addWidget(new QLabel("Origin (Z)"),numRow, 3);
  paddleLayout->addWidget(paddleWidth,numRow,4);
  paddleLayout->addWidget(new QLabel("m"),numRow++, 5);


  QStringList paddleContactTypeList; paddleContactTypeList << "Sticky" << "Slip" << "Separable";  
  paddleContactType = new SC_ComboBox("paddleContactType", paddleContactTypeList);
  paddleLayout->addWidget(new QLabel("ContactType"),numRow, 0);
  paddleLayout->addWidget(paddleContactType, numRow++, 1);  
  
  paddleDisplacementFile = new SC_FileEdit("paddleDisplacementFile");
  paddleLayout->addWidget(new QLabel("Paddle Displacmenet File"),numRow, 0);
  paddleLayout->addWidget(paddleDisplacementFile,numRow++, 1, 1, 5);  
  

  // Rigid Structures
  QGridLayout *structLayout = new QGridLayout();
  theStructures->setLayout(structLayout);

  numRow = 0;
  QStringList listContact; listContact << "Sticky" << "Slip" << "Separable";  
  
  structContactType = new SC_ComboBox("structContactType",listContact);
  structLayout->addWidget(new QLabel("Contact Type"),numRow,0);
  structLayout->addWidget(structContactType,numRow++,1);

  numRow = 1;
  structLength = new SC_DoubleLineEdit("structLength",1.016);
  structLayout->addWidget(new QLabel("Structure Length (X)"),numRow, 0);
  structLayout->addWidget(structLength,numRow,1);
  structLayout->addWidget(new QLabel("m"),numRow++, 2);  

  structHeight = new SC_DoubleLineEdit("structHeight",0.625);
  structLayout->addWidget(new QLabel("Structure Height (Y)"),numRow, 0);
  structLayout->addWidget(structHeight,numRow,1);
  structLayout->addWidget(new QLabel("m"),numRow++, 2);

  structWidth = new SC_DoubleLineEdit("structWidth",1.016);
  structLayout->addWidget(new QLabel("Structure Width (Z)"),numRow, 0);
  structLayout->addWidget(structWidth,numRow,1);
  structLayout->addWidget(new QLabel("m"),numRow++, 2);

  numRow = 1;
  structOriginLength = new SC_DoubleLineEdit("structOriginX",45.8);
  structLayout->addWidget(new QLabel("Structure Origin (X)"),numRow, 3);
  structLayout->addWidget(structOriginLength,numRow,4);
  structLayout->addWidget(new QLabel("m"),numRow++, 5);  

  structOriginHeight = new SC_DoubleLineEdit("structOriginY",2.0);
  structLayout->addWidget(new QLabel("Structure Origin (Y)"),numRow, 3);
  structLayout->addWidget(structOriginHeight,numRow,4);
  structLayout->addWidget(new QLabel("m"),numRow++, 5);    

  structOriginWidth = new SC_DoubleLineEdit("structOriginZ",1.325);
  structLayout->addWidget(new QLabel("Structure Origin (Z)"),numRow, 3);
  structLayout->addWidget(structOriginWidth,numRow,4);
  structLayout->addWidget(new QLabel("m"),numRow++, 5);

  structApplyCoulombFriction = new SC_CheckBox("structApplyCoulombFriction");
  structLayout->addWidget(new QLabel("Apply Coulomb Fruction?"),numRow, 0);  
  structLayout->addWidget(structApplyCoulombFriction,numRow++, 1);
  
  QGroupBox *structFrictionBox = new QGroupBox("");
  QGridLayout *structFrictionBoxLayout = new QGridLayout();
  structFrictionBox->setLayout(structFrictionBoxLayout);
  numRow = 0;
  
  structStaticFrictionWallX = new SC_DoubleLineEdit("structStaticFrictionWallX",0.0);
  structFrictionBoxLayout->addWidget(new QLabel("Static Friction on Structure (X)"),numRow, 0);
  structFrictionBoxLayout->addWidget(structStaticFrictionWallX,numRow,1);

  structDynamicFrictionWallX = new SC_DoubleLineEdit("structDynamicFrictionWallX",0.0);
  structFrictionBoxLayout->addWidget(new QLabel("Dynamic Friction on Structure (X)"),numRow, 3);
  structFrictionBoxLayout->addWidget(structDynamicFrictionWallX,numRow++,4);  

  structStaticFrictionFloor = new SC_DoubleLineEdit("structStaticFrictionFloor",0.0);
  structFrictionBoxLayout->addWidget(new QLabel("Static Friction on Structure (Y)"),numRow, 0);
  structFrictionBoxLayout->addWidget(structStaticFrictionFloor,numRow,1);

  structDynamicFrictionFloor = new SC_DoubleLineEdit("structDynamicFrictionFloor",0.0);
  structFrictionBoxLayout->addWidget(new QLabel("Dynamic Friction on Structure (Y)"),numRow, 3);
  structFrictionBoxLayout->addWidget(structDynamicFrictionFloor,numRow++,4);  
  
  structStaticFrictionWallZ = new SC_DoubleLineEdit("structStaticFrictionWallZ",0.0);
  structFrictionBoxLayout->addWidget(new QLabel("Static Friction on Structure (Z)"),numRow, 0);
  structFrictionBoxLayout->addWidget(staticFrictionWallZ,numRow,1);

  structDynamicFrictionWallZ = new SC_DoubleLineEdit("structDynamicFrictionWallZ",0.0);
  structFrictionBoxLayout->addWidget(new QLabel("Dynamic Friction on Structure (Z)"),numRow, 3);
  structFrictionBoxLayout->addWidget(structDynamicFrictionWallZ,numRow++,4);  

  numRow = 5;
  structLayout->addWidget(structFrictionBox, numRow, 0, 3, 4);
  
  // -----
  // Walls
  QGridLayout *wallsLayout = new QGridLayout();
  theWalls->setLayout(wallsLayout);

  numRow = 0;
  // QStringList listContact; listContact << "Sticky" << "Slip" << "Separable";  
  
  wallsContactType = new SC_ComboBox("wallContactType",listContact);
  wallsLayout->addWidget(new QLabel("Contact Type"),numRow,0);
  wallsLayout->addWidget(wallsContactType,numRow++,1);

  numRow = 1;
  wallsLength = new SC_DoubleLineEdit("wallsLength",89.0);
  wallsLayout->addWidget(new QLabel("Length (X)"),numRow, 0);
  wallsLayout->addWidget(wallsLength,numRow,1);
  wallsLayout->addWidget(new QLabel("m"),numRow++, 2);  

  wallsHeight = new SC_DoubleLineEdit("wallsHeight",89.0);
  wallsLayout->addWidget(new QLabel("Height (Y)"),numRow, 0);
  wallsLayout->addWidget(wallsHeight,numRow,1);
  wallsLayout->addWidget(new QLabel("m"),numRow++, 2);

  wallsWidth = new SC_DoubleLineEdit("wallsWidth",89.0);
  wallsLayout->addWidget(new QLabel("Width (Z)"),numRow, 0);
  wallsLayout->addWidget(wallsWidth,numRow,1);
  wallsLayout->addWidget(new QLabel("m"),numRow++, 2);

  numRow = 1;
  originLength = new SC_DoubleLineEdit("wallsOriginX",0.0);
  wallsLayout->addWidget(new QLabel("Origin (X)"),numRow, 3);
  wallsLayout->addWidget(originLength,numRow,4);
  wallsLayout->addWidget(new QLabel("m"),numRow++, 5);  

  originHeight = new SC_DoubleLineEdit("wallsOriginY",0.0);
  wallsLayout->addWidget(new QLabel("Origin (Y)"),numRow, 3);
  wallsLayout->addWidget(originHeight,numRow,4);
  wallsLayout->addWidget(new QLabel("m"),numRow++, 5);    

  originWidth = new SC_DoubleLineEdit("wallsOriginZ",0.0);
  wallsLayout->addWidget(new QLabel("Origin (Z)"),numRow, 3);
  wallsLayout->addWidget(originWidth,numRow,4);
  wallsLayout->addWidget(new QLabel("m"),numRow++, 5);

  applyCoulombFriction = new SC_CheckBox("applyCoulombFriction");
  wallsLayout->addWidget(new QLabel("Apply Coulomb Fruction?"),numRow, 0);  
  wallsLayout->addWidget(applyCoulombFriction,numRow++, 1);
  
  QGroupBox *frictionBox = new QGroupBox("");
  QGridLayout *frictionBoxLayout = new QGridLayout();
  frictionBox->setLayout(frictionBoxLayout);
  numRow = 0;
  
  staticFrictionWallX = new SC_DoubleLineEdit("staticFrictionWallX",0.0);
  frictionBoxLayout->addWidget(new QLabel("Static Friction on Wall (X)"),numRow, 0);
  frictionBoxLayout->addWidget(staticFrictionWallX,numRow,1);

  dynamicFrictionWallX = new SC_DoubleLineEdit("dynamicFrictionWallX",0.0);
  frictionBoxLayout->addWidget(new QLabel("Dynamic Friction on Wall (X)"),numRow, 3);
  frictionBoxLayout->addWidget(dynamicFrictionWallX,numRow++,4);  

  staticFrictionFloor = new SC_DoubleLineEdit("staticFrictionFloor",0.0);
  frictionBoxLayout->addWidget(new QLabel("Static Friction on Floor (Y)"),numRow, 0);
  frictionBoxLayout->addWidget(staticFrictionFloor,numRow,1);

  dynamicFrictionFloor = new SC_DoubleLineEdit("dynamicFrictionFloor",0.0);
  frictionBoxLayout->addWidget(new QLabel("Dynamic Friction on Floor (Y)"),numRow, 3);
  frictionBoxLayout->addWidget(dynamicFrictionFloor,numRow++,4);  
  
  staticFrictionWallZ = new SC_DoubleLineEdit("staticFrictionWallZ",0.0);
  frictionBoxLayout->addWidget(new QLabel("Static Friction on Wall (Z)"),numRow, 0);
  frictionBoxLayout->addWidget(staticFrictionWallZ,numRow,1);

  dynamicFrictionWallZ = new SC_DoubleLineEdit("dynamicFrictionWallZ",0.0);
  frictionBoxLayout->addWidget(new QLabel("Dynamic Friction on Wall (Z)"),numRow, 3);
  frictionBoxLayout->addWidget(dynamicFrictionWallZ,numRow++,4);  

  numRow = 5;
  wallsLayout->addWidget(frictionBox, numRow, 0, 3, 4);
  
  // wallsLayout->setRowStretch(numRow,1);

  /*
  // 3. Bathymetry .. getting a little more complicated!
  //    need to use ComboBox and StackedWidget
  QGridLayout *theWaveFlumeLayout = new QGridLayout();
  theWaveFlume->setLayout(theWaveFlumeLayout);
  
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

  theWaveFlumeLayout->addWidget(new QLabel("Source Bathymetry"), 0,0);
  theWaveFlumeLayout->addWidget(bathymetryComboBox,0,1);
  theWaveFlumeLayout->addWidget(bathStack,1,0,1,2);

  // connext bathymetry to show correct widget
  connect(bathymetryComboBox, QOverload<int>::of(&QComboBox::activated),
	  bathStack, &QStackedWidget::setCurrentIndex);

  
  // 4. Wave Generation .. as complicated as previous!
  //    need to use ComboBox and StackedWidget
  QGridLayout *theWaveGenLayout = new QGridLayout();
  theWaveGeneration->setLayout(theWaveGenLayout);
  
  QStringList genOptions; genOptions << "Preset Paddle Motion" << "Paddle Generated Waves" << "Periodic Waves" << "No Waves";
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
  */
}

BoundariesMPM::~BoundariesMPM()
{

}

bool
BoundariesMPM::outputToJSON(QJsonObject &jsonObject)
{
  return true;
}

bool
BoundariesMPM::inputFromJSON(QJsonObject &jsonObject)
{
  return true;
}


bool
BoundariesMPM::copyFiles(QString &destDir)
{
  //  velFile->copyFile(destDir);  
  //  bathSTL->copyFile(destDir);
  //  paddleDisplacementFile->copyFile(destDir);    
  
  return true;
}


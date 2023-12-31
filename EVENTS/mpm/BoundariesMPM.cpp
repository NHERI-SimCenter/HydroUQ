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
#include <QIcon>
#include <QSvgWidget>
#include <QString> 
#include <QJsonObject>
#include <QJsonArray>

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
  
  tabWidget->addTab(theWaveFlume,QIcon(QString(":/icons/wash-black.svg")), "Flume Facility");
  tabWidget->addTab(theWaveGeneration,QIcon(QString(":/icons/wave-break-black.svg")), "Wave Generator");  
  tabWidget->addTab(theStructures,QIcon(QString(":/icons/home-black.svg")), "Rigid Structures");
  tabWidget->addTab(theWalls,QIcon(QString(":/icons/wall-black.svg")), "Walls");
  int sizeTabIcon = 20;
  tabWidget->setIconSize(QSize(sizeTabIcon,sizeTabIcon));
  layout->addWidget(tabWidget);
  layout->setRowStretch(1,1);

  QGridLayout *waveFlumeLayout = new QGridLayout();
  theWaveFlume->setLayout(waveFlumeLayout);



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
  
  QStringList bathXZHeadings; bathXZHeadings << "Position Along Flume (m)" << "Height (m)";
  QStringList dataBathXZ; dataBathXZ << "35" << "0" << "42" << "1.75" << "56" << "2.5" << "105" << "2.5";
  bathXZData = new SC_TableEdit("bathXZData",bathXZHeadings, 4, dataBathXZ);
  bathSTL = new SC_FileEdit("bathSTL");

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
  QStringList facilityList; facilityList << "Hinsdale Large Wave Flume (OSU LWF)" << "Hinsdale Directional Wave Basin (OSU DWB)" <<  "Wind-Air-Sea Interaction Facility (UW WASIRF)" << "Waseda University's Tsunami Wave Basin (WU TWB)" << "U.S. Geo. Survey's Debris Flow Flume (USGS DFF)" << "CLOSED" << "INLETOUTLET";
  facility = new SC_ComboBox("domainSubType",facilityList);
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
    if (val == "Hinsdale Large Wave Flume - Oregon State University (OSU LWF)") {
      flumeLength->setText("104.0");
      flumeHeight->setText("4.6");
      flumeWidth->setText("3.658");
      // dataBathXZ << "0" << "0" << "35" << "0" << "42" << "1.75" << "56" << "2.5" << "105" << "2.5";
    } else if (val == "Hinsdale Directional Wave Basin - Oregon State University (OSU DWB)") {
      flumeLength->setText("48.8");
      flumeHeight->setText("26.5");
      flumeWidth->setText("2.1");
      // dataBathXZ << "0" << "0" << "11" << "0" << "31" << "2.0" << "45" << "2.0" << "45" << "0" << "48.8" << "0";
    } else if (val == "Wind-Air-Sea Interaction Facility - University of Washington (UW WASIRF)") {
      flumeLength->setText("12.19");
      flumeHeight->setText("1.22");
      flumeWidth->setText("0.914");
      // dataBathXZ << "0" << "0" << "12" << "0";
    } else if (val == "Tsunami Wave Basin - Waseda University (WU TWB)") {
      flumeLength->setText("9.0");
      flumeHeight->setText("1.0");
      flumeWidth->setText("4.0");
      // dataBathXZ << "0" << "0" << "3.95" << "0" << "3.95" << "0.255" << "9.0" << "0.255";
    } else if (val == "Debris Flow Flume - U.S. Geological Survey (USGS DFF)") {
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
  
  QGridLayout *theWaveGenLayout = new QGridLayout();
  theWaveGeneration->setLayout(theWaveGenLayout);

  numRow = 0;
  QStringList listWaveGeneration; listWaveGeneration << "Preset Paddle - OSU LWF" << "Periodic Waves - Custom" << "Preset Paddle - OSU DWB" << "Paddle - Custom" << "Preset Wave Pump - UW WASIRF"  <<  "Pump - Custom" << "Preset Vanishing Gate - WU TWB" << "Preset Swinging Gates - USGS DFF" << "Gate - Custom";
  generationMethod = new SC_ComboBox("generationMethod",listWaveGeneration);

  QStringList paddleContactTypeList; paddleContactTypeList <<  "Separable" << "Slip" << "Sticky";  
  paddleContactType = new SC_ComboBox("paddleContactType", paddleContactTypeList);

  QWidget *paddleWidget = new QWidget();
  QGridLayout *paddleLayout = new QGridLayout();
  paddleLayout->addWidget(new QLabel("Contact Type"),numRow, 0);
  paddleLayout->itemAt(paddleLayout->count()-1)->setAlignment(Qt::AlignRight);
  paddleLayout->addWidget(paddleContactType, numRow++, 1);  
  
  paddleLength = new SC_DoubleLineEdit("paddleLength",0.2);
  paddleHeight = new SC_DoubleLineEdit("paddleHeight",4.0);
  paddleWidth  = new SC_DoubleLineEdit("paddleWidth",4.0);
  paddleLayout->addWidget(new QLabel("Paddle Dimensions (X,Y,Z)"),numRow, 0);
  paddleLayout->itemAt(paddleLayout->count()-1)->setAlignment(Qt::AlignRight);
  paddleLayout->addWidget(paddleLength,numRow,1);
  paddleLayout->addWidget(paddleHeight,numRow,2);
  paddleLayout->addWidget(paddleWidth,numRow, 3);
  paddleLayout->addWidget(new QLabel("m"),numRow++, 4);


  paddleOriginX = new SC_DoubleLineEdit("paddleOriginX",0.0);
  paddleOriginY = new SC_DoubleLineEdit("paddleOriginY",0.0);
  paddleOriginZ = new SC_DoubleLineEdit("paddleOriginZ",0.0);
  paddleLayout->addWidget(new QLabel("Paddle Origin (X,Y,Z)"),numRow, 0);
  paddleLayout->itemAt(paddleLayout->count()-1)->setAlignment(Qt::AlignRight);
  paddleLayout->addWidget(paddleOriginX,numRow,1);
  paddleLayout->addWidget(paddleOriginY,numRow,2);
  paddleLayout->addWidget(paddleOriginZ,numRow,3);
  paddleLayout->addWidget(new QLabel("m"),numRow++, 4);



  paddleDisplacementFile = new SC_FileEdit("paddleDisplacementFile");
  paddleLayout->addWidget(new QLabel("Paddle Displacement File"), numRow, 0);
  paddleLayout->itemAt(paddleLayout->count()-1)->setAlignment(Qt::AlignRight);
  paddleLayout->addWidget(paddleDisplacementFile, numRow++, 1, 1, 4);  
  paddleLayout->setRowStretch(numRow,1);  
  
  paddleWidget = new QWidget();
  paddleWidget->setLayout(paddleLayout);
 
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
  periodicLayout->addWidget(new QLabel("meters"),0,2);
  periodicLayout->addWidget(new QLabel("meters/sec"),1,2);
  periodicLayout->addWidget(new QLabel("sec."),2,2);
  periodicLayout->setRowStretch(3,1);

  QStackedWidget *waveGenStack = new QStackedWidget();
  waveGenStack->addWidget(paddleWidget);
  waveGenStack->addWidget(periodicWidget); 


  connect(generationMethod, QOverload<int>::of(&QComboBox::activated),
    waveGenStack, &QStackedWidget::setCurrentIndex);

  numRow = 0;
  theWaveGenLayout->addWidget(new QLabel("Wave Generation Method"),numRow,0);
  theWaveGenLayout->itemAt(theWaveGenLayout->count()-1)->setAlignment(Qt::AlignRight);
  theWaveGenLayout->addWidget(generationMethod,numRow++,1);
  theWaveGenLayout->addWidget(waveGenStack,numRow++,0,1,2);
  theWaveGenLayout->setRowStretch(numRow,1);


  // Rigid Structures
  QGridLayout *structLayout = new QGridLayout();
  theStructures->setLayout(structLayout);

  numRow = 0;

  QStringList listObject; listObject << "Orange Box - OSU LWF" << "Grey Box - UW WASIRF" << "Square Columns - WU TWB" << "Box" << "Cylinder" << "Wedge" << "Sphere" << "Custom";  
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
  structLength = new SC_DoubleLineEdit("structLength",1.016);
  structHeight = new SC_DoubleLineEdit("structHeight",0.625);
  structWidth = new SC_DoubleLineEdit("structWidth",1.016);
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
  structApplyCoulombFriction->setChecked(true);
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
  structArrayBoxLayout->addWidget(new QLabel("Array of Objects (nX, nY, nZ)"),numStructArrayRow, 0);
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
  structLayout->addWidget(new QLabel("Auto-Create Load-Cells (Sensors)?"),numRow, 0);
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


  // -----
  // Walls
  QGridLayout *wallsLayout = new QGridLayout();
  theWalls->setLayout(wallsLayout);

  numRow = 0;
  QStringList wallListContact; wallListContact << "Separable" << "Slip" << "Sticky";  
  
  wallsContactType = new SC_ComboBox("wallContactType",listContact);
  wallsLayout->addWidget(new QLabel("Contact Type"),numRow,0);
  wallsLayout->itemAt(wallsLayout->count()-1)->setAlignment(Qt::AlignRight);
  wallsLayout->addWidget(wallsContactType,numRow++,1);

  wallsLength = new SC_DoubleLineEdit("wallsLength",90.0);
  wallsHeight = new SC_DoubleLineEdit("wallsHeight",4.5);
  wallsWidth = new SC_DoubleLineEdit("wallsWidth",3.65);
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
  applyCoulombFriction->setChecked(true);
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
  applyInletOutlet->setChecked(true);
  wallsLayout->addWidget(new QLabel("Apply Inlet/Outlet?"),numRow, 0);
  wallsLayout->itemAt(wallsLayout->count()-1)->setAlignment(Qt::AlignRight);
  wallsLayout->addWidget(applyInletOutlet,numRow++, 1);


  QGroupBox *inletOutletBox = new QGroupBox("");
  QGridLayout *inletOutletBoxLayout = new QGridLayout();
  inletOutletBox->setLayout(inletOutletBoxLayout);
  int numInOutRow = 0;
  QStringList inletOutletList; inletOutletList << "None" << "Inlet - Laminar" << "Inlet - Turbulent" << "Inlet - OpenFOAM" << "Inlet - Boussinesq" << "Inlet - GeoClaw" << "Inlet - SWE File" << "Outlet - Laminar" << "Outlet - Turbulent" << "Outlet - OpenFOAM" << "Outlet - Boussinesq" << "Outlet - GeoClaw" << "Outlet - SWE File";
  inletOutletTypeSubX = new SC_ComboBox("inletOutletTypeSubX",inletOutletList);
  inletOutletTypeSubY = new SC_ComboBox("inletOutletTypeSubY",inletOutletList);
  inletOutletTypeSubZ = new SC_ComboBox("inletOutletTypeSubZ",inletOutletList);
  inletOutletTypePlusX = new SC_ComboBox("inletOutletTypePlusX",inletOutletList);
  inletOutletTypePlusY = new SC_ComboBox("inletOutletTypePlusY",inletOutletList);
  inletOutletTypePlusZ = new SC_ComboBox("inletOutletTypePlusZ",inletOutletList);
  inletOutletBoxLayout->addWidget(new QLabel("Inlet-Outlet at (-X,-Y,-Z) Walls"),numInOutRow, 0);
  inletOutletBoxLayout->itemAt(inletOutletBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  inletOutletBoxLayout->addWidget(inletOutletTypeSubX,numInOutRow,1);
  inletOutletBoxLayout->addWidget(inletOutletTypeSubY,numInOutRow,2);
  inletOutletBoxLayout->addWidget(inletOutletTypeSubZ,numInOutRow++,3);
  inletOutletBoxLayout->addWidget(new QLabel("Inlet-Outlet at (+X,+Y,+Z) Walls"),numInOutRow, 0);
  inletOutletBoxLayout->itemAt(inletOutletBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  inletOutletBoxLayout->addWidget(inletOutletTypePlusX,numInOutRow,1);
  inletOutletBoxLayout->addWidget(inletOutletTypePlusY,numInOutRow,2);
  inletOutletBoxLayout->addWidget(inletOutletTypePlusZ,numInOutRow++,3);
  inletOutletBoxLayout->setRowStretch(numInOutRow,1);
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
  QJsonArray boundariesArray;
  boundariesArray = jsonObject["boundaries"].toArray();
  
  // Wave Flume Facility
  {
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

    // Maybe add SWL, bools, wave-maker neutral, etc. here
    boundariesArray.append(boundariesObject);
  }

  // Wave Generation
  {
    QJsonObject boundariesObject;

    // TODO: Add wave generator names to JSON to link to the name in ClaymoreUW enumerators
    boundariesObject["object"] = QString("OSU Paddle");  
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

    boundariesObject["file"] = QString("WaveMaker/wmdisp_LWF_Unbroken_Amp4_SF500_twm10sec_1200hz_14032023.csv");
    // TODOL: Custom file input
    // paddleDisplacementFile->text(); // Paddle motion file
    boundariesObject["output_freq"] = 1200.0; // TODO: Either be user set or read-in from motion_file

    boundariesArray.append(boundariesObject);
  }


  // Rigid Structures
  {
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
      boundariesObject["friction"] = frictionObject;
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
  {
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
      boundariesObject["friction"] = frictionObject;
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
    //   inletOutletObject["-X"] = subXObject;
    //   inletOutletObject["-Y"] = subYObject;
    //   inletOutletObject["-Z"] = subZObject;
    //   inletOutletObject["+X"] = plusXObject;
    //   inletOutletObject["+Y"] = plusYObject;
    //   inletOutletObject["+Z"] = plusZObject;
    //   boundariesObject["inlet-outlet"] = inletOutletObject;
    // }

    boundariesArray.append(boundariesObject);
  }


  if (0) jsonObject["boundaries"] = boundariesArray; // future schema
  else jsonObject["grid-boundaries"] = boundariesArray; // ClaymoreUW artifact, TODO: Deprecate


  //  jsonObject["domainSubType"]=facility->currentText();
  bathSTL->outputToJSON(jsonObject);
  paddleDisplacementFile->outputToJSON(jsonObject);



  return true;
}

bool
BoundariesMPM::inputFromJSON(QJsonObject &jsonObject)
{
  // if (jsonObject.contains("domainSubType")) {
  //   QJsonValue theValue = jsonObject["domainSubType"];
  //   QString valueString = theValue.toString();
  //   facility->setCurrentText(valueString);
  // }
  bathSTL->inputFromJSON(jsonObject);
  paddleDisplacementFile->inputFromJSON(jsonObject);
  return true;
}


bool
BoundariesMPM::copyFiles(QString &destDir)
{
  //  velFile->copyFile(destDir);  
  bathSTL->copyFile(destDir);
  // return true;
  if (paddleDisplacementFile->copyFile(destDir) != true)
    return false;
  return paddleDisplacementFile->copyFile(destDir);    
}


/* *****************************************************************************
Copyright (c) 2016-2023, The Regents Sensor the University Sensor California (Regents).
All rights reserved.

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:

1. Redistributions Sensor source code must retain the above copyright notice, this
   list Sensor conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list Sensor conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SSensorTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES Sensor MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT Sensor SUBSTITUTE GOODS OR SERVICES;
LOSS Sensor USE, DATA, OR PRSensorITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY Sensor LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT Sensor THE USE Sensor THIS
SSensorTWARE, EVEN IF ADVISED Sensor THE POSSIBILITY Sensor SUCH DAMAGE.

The views and conclusions contained in the sSensortware and documentation are those
Sensor the authors and should not be interpreted as representing Sensorficial policies,
either expressed or implied, Sensor the FreeBSD Project.

REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
THE IMPLIED WARRANTIES Sensor MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
THE SSensorTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED HEREUNDER IS 
PROVIDED "AS IS". REGENTS HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, 
UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

*************************************************************************** */

#include "SensorMPM.h"
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


SensorMPM::SensorMPM(QWidget *parent)
  : SimCenterWidget(parent)
{
  //
  // This file creates the widgets used to define the sensors for the MPM application
  // Sensors are instruments that measure some quantity, e.g. free-surface elevation, velocity, force, etc.
  // These are meant to be digital twins of real sensors. Hence, they posses the same variables as their real-world counterparts.
  // The user can specify the type of sensor, attribute to measure, operation to perform, sampling frequency, name, location.
  // The user can also specify the direction in which to measure the attribute. This 
  // Each tab on this page is a different type of sensor
  // A general template for creating custom sensors is provided for users. 
  // Also provide a few template specializations
  // These are common, pre-made instruments.
  // They include wave gauges, velocity meters, and load cells
  //
  QGridLayout *layout = new QGridLayout();
  this->setLayout(layout);


  // 
  // create stacked widgets for sensor presets
  //
  stackedWidget = new QStackedWidget();
  theCustom = new QWidget();
  theWaveGauges = new QWidget();
  theVelocityMeters = new QWidget();
  theLoadCells = new QWidget();
  thePiezoMeters = new QWidget();
  QGridLayout *customLayout = new QGridLayout();
  QGridLayout *wgLayout = new QGridLayout();
  QGridLayout *vmLayout = new QGridLayout();
  QGridLayout *lcLayout = new QGridLayout();
  QGridLayout *pmLayout = new QGridLayout();
  theCustom->setLayout(customLayout);
  theWaveGauges->setLayout(wgLayout);
  theVelocityMeters->setLayout(vmLayout);
  theLoadCells->setLayout(lcLayout);
  thePiezoMeters->setLayout(pmLayout);
  
  // ===========================================================================
  sensorType = new SC_ComboBox("preset", QStringList() << "Custom" << "Wave-Gauges" << "Velocimeters" << "Load-Cells" << "Piezometers");
  layout->addWidget(new QLabel("Sensor Preset"));
  layout->addWidget(sensorType);
  layout->addWidget(stackedWidget);

  // ===========================================================================
  stackedWidget->addWidget(theCustom);
  stackedWidget->addWidget(theWaveGauges);
  stackedWidget->addWidget(theVelocityMeters);
  stackedWidget->addWidget(theLoadCells);
  stackedWidget->addWidget(thePiezoMeters);

  // ===========================================================================  
  QStringList yesNo; yesNo <<  "Yes" << "No";
  QStringList noYes; noYes <<  "No" << "Yes";
  QStringList typeList; typeList <<  "particles" << "grid"; // << "nodes" << "elements" << "surface" << "edge";
  QStringList typeGridParticleList; typeGridParticleList <<  "grid" << "particles" ; // << "nodes" << "elements" << "surface" << "edge";
  QStringList typeGridList; typeGridList << "grid";
  QStringList typeParticleList; typeParticleList << "particles";

  // ===========================================================================
  QStringList  list; list << "Name" << "Origin X" << "Origin Y" << "Origin Z" << "Dimension X" << "Dimension Y" << "Dimension Z" ;
  QStringList  data; data << "CustomSensor1" << "0.0" << "0.0" << "0.0" << "0.0" << "0.0" << "0.0" ;
  customTable = new SC_TableEdit("customLocs", list, 1, data);


  QStringList  listWG; listWG << "Name" << "Origin X" << "Origin Y" << "Origin Z" << "Dimension X" << "Dimension Y" << "Dimension Z" ;
  QStringList  dataWG; dataWG << "WaveGauge1" << "16.0" << "1.5" << "0.4" << "0.1" << "2.50" << "0.1" 
				                      << "WaveGauge2" << "34.269" << "1.5" << "0.4" << "0.1" << "2.50" << "0.1" 
				                      << "WaveGauge3" << "38.114" << "1.5" << "0.4" << "0.1" << "2.50" << "0.1" ;
  waveGaugesTable = new SC_TableEdit("waveGaugeLocs",  listWG, 3, dataWG);
  
  QStringList  listVM; listVM << "Name" << "Origin X" << "Origin Y" << "Origin Z" << "Dimension X" << "Dimension Y" << "Dimension Z" ;
  QStringList  dataVM; dataVM << "VelocityMeter1" << "16.0" << "0.00" << "0.4" << "0.05" << "2.75" << "0.05" 
				                      << "VelocityMeter2" << "43.8" << "1.75" << "0.4" << "0.05" << "1.00" << "0.05" ;
  velociMetersTable  = new SC_TableEdit("velociMeterLocs", listVM, 2, dataVM);
  
  QStringList  listLC; listLC << "Name" << "Origin X" << "Origin Y" << "Origin Z" << "Dimension X" << "Dimension Y" << "Dimension Z" ;
  QStringList  dataLC; dataLC << "LoadCell1" << "45.799" << "2.0" << "1.35" << "0.025" << "0.3" << "1.0" 
                              << "LoadCell2" << "45.799" << "2.3" << "1.35" << "0.025" << "0.3" << "1.0" ;    
  loadCellsTable  = new SC_TableEdit("loadCellLocs", listLC, 2, dataLC);

  QStringList  listPM; listPM << "Name" << "Origin X" << "Origin Y" << "Origin Z" << "Dimension X" << "Dimension Y" << "Dimension Z" ;
  QStringList  dataPM; dataPM << "PiezoMeter1" << "16.0" << "1.00" << "0.4" << "0.05" << "0.05" << "0.05" 
				                      << "PiezoMeter2" << "43.8" << "1.80" << "0.4" << "0.05" << "0.05" << "0.05" ;
  piezoMetersTable  = new SC_TableEdit("piezoMeterLocs", listPM, 2, dataPM);



  QStringList attributesOnParticlesList; 
  attributesOnParticlesList << "ID" << "Mass" << "Volume"
                            << "Position_X" << "Position_Y" << "Position_Z" 
                            << "Velocity_X" << "Velocity_Y" << "Velocity_Z" << "Velocity_Magnitude"
                            << "DefGrad_XX" << "DefGrad_XY" << "DefGrad_XZ"
                            << "DefGrad_YX" << "DefGrad_YY" << "DefGrad_YZ"
                            << "DefGrad_ZX" << "DefGrad_ZY" << "DefGrad_ZZ"
                            << "J" << "DefGrad_Determinant" << "JBar" << "DefGrad_Determinant_FBAR" 
                            << "StressCauchy_XX" << "StressCauchy_XY" << "StressCauchy_XZ"
                            << "StressCauchy_YX" << "StressCauchy_YY" << "StressCauchy_YZ"
                            << "StressCauchy_ZX" << "StressCauchy_ZY" << "StressCauchy_ZZ"
                            << "Pressure" << "VonMisesStress"
                            << "DefGrad_Invariant1" << "DefGrad_Invariant2" << "DefGrad_Invariant3"
                            << "DefGrad_1" << "DefGrad_2" << "DefGrad_3"
                            << "StressCauchy_Invariant1" << "StressCauchy_Invariant2" << "StressCauchy_Invariant3"
                            << "StressCauchy_1" << "StressCauchy_2" << "StressCauchy_3"
                            << "StressPK1_XX" << "StressPK1_XY" << "StressPK1_XZ"
                            << "StressPK1_YX" << "StressPK1_YY" << "StressPK1_YZ"
                            << "StressPK1_ZX" << "StressPK1_ZY" << "StressPK1_ZZ"
                            << "StressPK1_Invariant1" << "StressPK1_Invariant2" << "StressPK1_Invariant3"
                            << "StressPK1_1" << "StressPK1_2" << "StressPK1_3"
                            << "StressPK2_XX" << "StressPK2_XY" << "StressPK2_XZ"
                            << "StressPK2_YX" << "StressPK2_YY" << "StressPK2_YZ"
                            << "StressPK2_ZX" << "StressPK2_ZY" << "StressPK2_ZZ"
                            << "StressPK2_Invariant1" << "StressPK2_Invariant2" << "StressPK2_Invariant3"
                            << "StressPK2_1" << "StressPK2_2" << "StressPK2_3"
                            << "StrainSmall_XX" << "StrainSmall_XY" << "StrainSmall_XZ"
                            << "StrainSmall_YX" << "StrainSmall_YY" << "StrainSmall_YZ"
                            << "StrainSmall_ZX" << "StrainSmall_ZY" << "StrainSmall_ZZ"
                            << "StrainSmall_Invariant1" << "StrainSmall_Invariant2" << "StrainSmall_Invariant3"
                            << "Dilation" << "StrainSmall_Determinant" 
                            << "StrainSmall_1" << "StrainSmall_2" << "StrainSmall_3"
                            << "VonMisesStrain"
                            << "logJp";

  QStringList attributesOnGridList;
  attributesOnGridList << "Mass" << "Force" << "Momentum" << "Velocity"; // Acceleration, Pressure
  QStringList operationList; operationList << "Sum" << "Max" << "Min" << "Count" << "Average";

  toggle = new SC_ComboBox("toggle", yesNo); // wave gauge (elevation rel. to grav. vec. Sensor particle free surface)
  type = new SC_ComboBox("type", typeParticleList); // wave gauge (elevation rel. to grav. vec. Sensor particle free surface)
  attribute = new SC_ComboBox("attribute", attributesOnParticlesList);
  operation = new SC_ComboBox("operation", operationList);
  direction = new SC_ComboBox("direction", QStringList() << "X" << "Y" << "Z" << "X+" << "Y+" << "Z+" << "X-" << "Y-" << "Z-" << "N/A");
  direction->setCurrentIndex(9); // N/A, non vector
  output_frequency = new SC_DoubleLineEdit("output_frequency", 30.0);

  toggleWG = new SC_ComboBox("toggle", yesNo); // wave gauge (elevation rel. to grav. vec. Sensor particle free surface)
  typeWG = new SC_ComboBox("type", typeParticleList); // wave gauge (elevation rel. to grav. vec. Sensor particle free surface)
  attributeWG = new SC_ComboBox("attribute", QStringList() << "Elevation" << "Position_Y");
  operationWG = new SC_ComboBox("operation", QStringList() << "Max");
  directionWG = new SC_ComboBox("direction", QStringList() << "N/A");
  // directionWG->setCurrentIndex(0); // N/A, non vector
  output_frequencyWG = new SC_DoubleLineEdit("output_frequency", 30.0);

  toggleVM  = new SC_ComboBox("toggle", yesNo); // velocity meter (velocity on grid)
  typeVM  = new SC_ComboBox("type", typeGridParticleList); // velocity meter (velocity on grid)
  attributeVM = new SC_ComboBox("attribute", QStringList() << "Velocity" << "Velocity_X" << "Velocity_Y" << "Velocity_Z" << "Velocity_Magnitude");
  operationVM = new SC_ComboBox("operation", QStringList() << "Max" << "Average");
  directionVM = new SC_ComboBox("direction", QStringList() << "X" << "Y" << "Z" << "X+" << "Y+" << "Z+" << "X-" << "Y-" << "Z-" << "N/A");
  directionVM->setCurrentIndex(0); // X
  output_frequencyVM = new SC_DoubleLineEdit("output_frequency", 30.0);

  toggleLC  = new SC_ComboBox("toggle", yesNo); // load cell (force on grid)
  typeLC  = new SC_ComboBox("type", typeGridList); // load cell (force on grid)
  attributeLC = new SC_ComboBox("attribute", QStringList() << "Force" << "Force_X" << "Force_Y" << "Force_Z" << "Force_Magnitude");
  operationLC = new SC_ComboBox("operation", QStringList() << "Sum" << "Max" << "Average");
  directionLC = new SC_ComboBox("direction", QStringList() << "X" << "Y" << "Z" << "X+" << "Y+" << "Z+" << "X-" << "Y-" << "Z-" << "N/A");
  directionLC->setCurrentIndex(3); // X+
  output_frequencyLC = new SC_DoubleLineEdit("output_frequency", 120.0);

  togglePM = new SC_ComboBox("toggle", yesNo); // wave gauge (elevation rel. to grav. vec. Sensor particle free surface)
  typePM = new SC_ComboBox("type", typeParticleList); // wave gauge (elevation rel. to grav. vec. Sensor particle free surface)
  attributePM = new SC_ComboBox("attribute", QStringList() << "Pressure");
  operationPM = new SC_ComboBox("operation", QStringList() << "Max" << "Average");
  directionPM = new SC_ComboBox("direction", QStringList() << "N/A");
  // directionPM->setCurrentIndex(0); // N/A, non vector
  output_frequencyPM = new SC_DoubleLineEdit("output_frequency", 30.0);

  // ===========================================================================
  customLayout->addWidget(new QLabel("Use These Sensors?"),0,0, Qt::AlignRight);
  customLayout->addWidget(toggle,0,1);
  customLayout->addWidget(new QLabel(""),0,2);
  customLayout->addWidget(new QLabel("Apply On"),1,0, Qt::AlignRight);
  customLayout->addWidget(type,1,1);
  customLayout->addWidget(new QLabel(""),1,2);
  customLayout->addWidget(new QLabel("Measure Attribute"),2,0, Qt::AlignRight);
  customLayout->addWidget(attribute,2,1);
  customLayout->addWidget(new QLabel(""),2,2);
  customLayout->addWidget(new QLabel("Perform Operation"),3,0, Qt::AlignRight);
  customLayout->addWidget(operation,3,1);
  customLayout->addWidget(new QLabel(""),3,2);
  customLayout->addWidget(new QLabel("Sampling Frequency"),4,0, Qt::AlignRight);
  customLayout->addWidget(output_frequency,4,1);
  customLayout->addWidget(new QLabel("Hz"),4,2);
  customLayout->addWidget(new QLabel("In Direction"),5,0, Qt::AlignRight);
  customLayout->addWidget(direction,5,1);
  customLayout->addWidget(new QLabel(""),5,2);
  customLayout->addWidget(customTable,7,0,1,4);
  customLayout->setRowStretch(7,1);

  // ===========================================================================
  wgLayout->addWidget(new QLabel("Use These Sensors?"),0,0, Qt::AlignRight);
  wgLayout->addWidget(toggleWG,0,1);
  wgLayout->addWidget(new QLabel(""),0,2);
  wgLayout->addWidget(new QLabel("Apply On"),1,0, Qt::AlignRight);
  wgLayout->addWidget(typeWG,1,1);
  wgLayout->addWidget(new QLabel(""),1,2);
  wgLayout->addWidget(new QLabel("Measure Attribute"),2,0, Qt::AlignRight);
  wgLayout->addWidget(attributeWG,2,1);
  wgLayout->addWidget(new QLabel(""),2,2);
  wgLayout->addWidget(new QLabel("Perform Operation"),3,0, Qt::AlignRight);
  wgLayout->addWidget(operationWG,3,1);
  wgLayout->addWidget(new QLabel(""),3,2);
  wgLayout->addWidget(new QLabel("Sampling Frequency"),4,0, Qt::AlignRight);
  wgLayout->addWidget(output_frequencyWG,4,1);
  wgLayout->addWidget(new QLabel("Hz"),4,2);
  wgLayout->addWidget(new QLabel("In Direction"),5,0, Qt::AlignRight);
  wgLayout->addWidget(directionWG,5,1);
  wgLayout->addWidget(waveGaugesTable,7,0,1,4);
  wgLayout->setRowStretch(7,1);
  // ===========================================================================
  vmLayout->addWidget(new QLabel("Use These Sensors?"),0,0, Qt::AlignRight);
  vmLayout->addWidget(toggleVM,0,1);
  vmLayout->addWidget(new QLabel(""),0,2);
  vmLayout->addWidget(new QLabel("Apply On"),1,0, Qt::AlignRight);
  vmLayout->addWidget(typeVM,1,1);
  vmLayout->addWidget(new QLabel(""),1,2);
  vmLayout->addWidget(new QLabel("Measure Attribute"),2,0, Qt::AlignRight);
  vmLayout->addWidget(attributeVM,2,1);
  vmLayout->addWidget(new QLabel(""),2,2);
  vmLayout->addWidget(new QLabel("Perform Operation"),3,0, Qt::AlignRight);
  vmLayout->addWidget(operationVM,3,1);
  vmLayout->addWidget(new QLabel(""),3,2);
  vmLayout->addWidget(new QLabel("Sampling Frequency"),4,0, Qt::AlignRight);
  vmLayout->addWidget(output_frequencyVM,4,1);
  vmLayout->addWidget(new QLabel("Hz"),4,2);
  vmLayout->addWidget(new QLabel("In Direction"),5,0, Qt::AlignRight);
  vmLayout->addWidget(directionVM,5,1);
  vmLayout->addWidget(velociMetersTable,7,0,1,4);
  vmLayout->setRowStretch(7,1);
  // ===========================================================================
  lcLayout->addWidget(new QLabel("Use These Sensors?"),0,0, Qt::AlignRight);
  lcLayout->addWidget(toggleLC,0,1);
  lcLayout->addWidget(new QLabel(""),0,2);
  lcLayout->addWidget(new QLabel("Apply On"),1,0, Qt::AlignRight);
  lcLayout->addWidget(typeLC,1,1);
  lcLayout->addWidget(new QLabel(""),1,2);
  lcLayout->addWidget(new QLabel("Measure Attribute"),2,0, Qt::AlignRight);
  lcLayout->addWidget(attributeLC,2,1);
  lcLayout->addWidget(new QLabel(""),2,2);
  lcLayout->addWidget(new QLabel("Perform Operation"),3,0, Qt::AlignRight);
  lcLayout->addWidget(operationLC,3,1);
  lcLayout->addWidget(new QLabel(""),3,2);
  lcLayout->addWidget(new QLabel("Sampling Frequency"),4,0, Qt::AlignRight);
  lcLayout->addWidget(output_frequencyLC,4,1);
  lcLayout->addWidget(new QLabel("Hz"),4,2);
  lcLayout->addWidget(new QLabel("In Direction"),5,0, Qt::AlignRight);
  lcLayout->addWidget(directionLC,5,1);
  lcLayout->addWidget(loadCellsTable,7,0,1,4);    
  lcLayout->setRowStretch(7,1);
  // ===========================================================================
  pmLayout->addWidget(new QLabel("Use These Sensors?"),0,0, Qt::AlignRight);
  pmLayout->addWidget(togglePM,0,1);
  pmLayout->addWidget(new QLabel(""),0,2);
  pmLayout->addWidget(new QLabel("Apply On"),1,0, Qt::AlignRight);
  pmLayout->addWidget(typePM,1,1);
  pmLayout->addWidget(new QLabel(""),1,2);
  pmLayout->addWidget(new QLabel("Measure Attribute"),2,0, Qt::AlignRight);
  pmLayout->addWidget(attributePM,2,1);
  pmLayout->addWidget(new QLabel(""),2,2);
  pmLayout->addWidget(new QLabel("Perform Operation"),3,0, Qt::AlignRight);
  pmLayout->addWidget(operationPM,3,1);
  pmLayout->addWidget(new QLabel(""),3,2);
  pmLayout->addWidget(new QLabel("Sampling Frequency"),4,0, Qt::AlignRight);
  pmLayout->addWidget(output_frequencyPM,4,1);
  pmLayout->addWidget(new QLabel("Hz"),4,2);
  pmLayout->addWidget(new QLabel("In Direction"),5,0, Qt::AlignRight);
  pmLayout->addWidget(directionPM,5,1);
  pmLayout->addWidget(piezoMetersTable,7,0,1,4);    
  pmLayout->setRowStretch(7,1);
  // ===========================================================================



  connect(sensorType, &QComboBox::currentTextChanged, [=](QString val) {
    enum SensorTypeEnum : int {CUSTOM = 0, WAVE_GAUGE, VELOCITY_METER, LOAD_CELL, PIEZO_METER, TOTAL};
    if (val == "Custom") {
      setSensorType(SensorTypeEnum::CUSTOM);
    } else if (val == "Wave-Gauges") {
      setSensorType(SensorTypeEnum::WAVE_GAUGE);

      toggleWG->setCurrentText("Yes");
      typeWG->setCurrentIndex(0);
      attributeWG->setCurrentText("Elevation");
      operationWG->setCurrentText("Max");
      directionWG->setCurrentText("N/A");
      output_frequencyWG->setText("30.0");
    } else if (val == "Velocimeters") {
      setSensorType(SensorTypeEnum::VELOCITY_METER);
      toggleVM->setCurrentText("No");
      typeVM->setCurrentIndex(0);
      attributeVM->setCurrentText("Velocity");
      operationVM->setCurrentText("Average");
      directionVM->setCurrentText("X+");
      output_frequencyVM->setText("30.0");
    } else if (val == "Load-Cells") {
      setSensorType(SensorTypeEnum::LOAD_CELL);
      toggleLC->setCurrentText("Yes");
      typeLC->setCurrentIndex(0);
      attributeLC->setCurrentText("Force");
      operationLC->setCurrentText("Sum");
      directionLC->setCurrentText("X+");
      output_frequencyLC->setText("120.0");
    } else if (val == "Piezometers") {
      setSensorType(SensorTypeEnum::PIEZO_METER);
      togglePM->setCurrentText("No");
      typePM->setCurrentIndex(0);
      attributePM->setCurrentText("Pressure");
      operationPM->setCurrentText("Average");
      directionPM->setCurrentText("N/A");
      output_frequencyPM->setText("30.0");
    }
  });
  
}

SensorMPM::~SensorMPM()
{

}

void SensorMPM::clear(void)
{
  // customTable->clear();
  // waveGaugesTable->clear();
  // velociMetersTable->clear();
  // loadCellsTable->clear();
  // piezoMetersTable->clear();

  toggle->setCurrentText("No");
  type->setCurrentText("particles");
  attribute->setCurrentText("Position_Y");
  operation->setCurrentText("Max");
  direction->setCurrentText("N/A");
  output_frequency->setText("30.0");

  toggleWG->setCurrentText("Yes");
  typeWG->setCurrentText("particles");
  attributeWG->setCurrentText("Elevation");
  operationWG->setCurrentText("Max");
  directionWG->setCurrentText("N/A");
  output_frequencyWG->setText("30.0");

  toggleVM->setCurrentText("No");
  typeVM->setCurrentText("grid");
  attributeVM->setCurrentText("Velocity");
  operationVM->setCurrentText("Max");
  directionVM->setCurrentText("X+");
  output_frequencyVM->setText("30.0");

  toggleLC->setCurrentText("Yes");
  typeLC->setCurrentText("grid");
  attributeLC->setCurrentText("Force");
  operationLC->setCurrentText("Sum");
  directionLC->setCurrentText("X+");
  output_frequencyLC->setText("30.0");

  togglePM->setCurrentText("No");
  typePM->setCurrentText("particles");
  attributePM->setCurrentText("Pressure");
  operationPM->setCurrentText("Max");
  directionPM->setCurrentText("N/A");
  output_frequencyPM->setText("30.0");
}

bool
SensorMPM::setSensorType(int type)
{
  // Enum to set icons, titles, init values, etc.
  enum SensorTypeEnum : int {CUSTOM = 0, WAVE_GAUGE, VELOCITY_METER, LOAD_CELL, PIEZO_METER, TOTAL};

  if (type < SensorTypeEnum::TOTAL) {
    if (sensorType->currentIndex() != type) {
      sensorType->setCurrentIndex(type);
    }
    if (stackedWidget->currentIndex() != type) {
      stackedWidget->setCurrentIndex(type);
    }
  }
  if (type == SensorTypeEnum::CUSTOM) {
    theCustom->setVisible(true);
    theWaveGauges->setVisible(false);
    theVelocityMeters->setVisible(false);
    theLoadCells->setVisible(false);
    thePiezoMeters->setVisible(false);
    // stackedWidget->setCurrentIndex(0);
  } else if (type == SensorTypeEnum::WAVE_GAUGE) {
    // sensorType->setCurrentIndex(1);
    theCustom->setVisible(false);
    theWaveGauges->setVisible(true);
    theVelocityMeters->setVisible(false);
    theLoadCells->setVisible(false);
    thePiezoMeters->setVisible(false);
    // stackedWidget->setCurrentIndex(1);
  } else if (type == SensorTypeEnum::VELOCITY_METER) {
    // sensorType->setCurrentIndex(2);
    theCustom->setVisible(false);
    theWaveGauges->setVisible(false);
    theVelocityMeters->setVisible(true);
    theLoadCells->setVisible(false);
    thePiezoMeters->setVisible(false);
    // stackedWidget->setCurrentIndex(2);
  } else if (type == SensorTypeEnum::LOAD_CELL) {
    // sensorType->setCurrentIndex(3);
    theCustom->setVisible(false);
    theWaveGauges->setVisible(false);
    theVelocityMeters->setVisible(false);
    theLoadCells->setVisible(true);
    thePiezoMeters->setVisible(false);
    // stackedWidget->setCurrentIndex(3);
  } else if (type == SensorTypeEnum::PIEZO_METER) {
    // sensorType->setCurrentIndex(4);
    theCustom->setVisible(false);
    theWaveGauges->setVisible(false);
    theVelocityMeters->setVisible(false);
    theLoadCells->setVisible(false);
    thePiezoMeters->setVisible(true);
    // stackedWidget->setCurrentIndex(4);
  } else {
    return false; 
  }
  return true;
}

bool
SensorMPM::outputToJSON(QJsonObject &jsonObject)
{
  QJsonArray sensorsArray = jsonObject["sensors"].toArray();
  QJsonArray particleSensorsArray = jsonObject["particle-sensors"].toArray();
  QJsonArray gridSensorsArray = jsonObject["grid-sensors"].toArray();

  // create a json object per sensor default
  QJsonObject tableArraysCustom;
  QJsonObject tableArraysWG;
  QJsonObject tableArraysVM;
  QJsonObject tableArraysLC;
  QJsonObject tableArraysPM;
  customTable->outputToJSON(tableArraysCustom);
  waveGaugesTable->outputToJSON(tableArraysWG);
  velociMetersTable->outputToJSON(tableArraysVM);
  loadCellsTable->outputToJSON(tableArraysLC);
  piezoMetersTable->outputToJSON(tableArraysPM);

  enum sensorEnum : int {CUSTOM = 0, WAVE_GAUGE, VELOCITY_METER, LOAD_CELL, PIEZO_METER, TOTAL};

  int stackIndexToEnum = static_cast<sensorEnum>(stackedWidget->currentIndex());

  // Wave-gauges (WG), Velocimeters (VM), and Load-cells (LC)
  if (stackIndexToEnum == sensorEnum::CUSTOM) {
    for (int i = 0; i < tableArraysCustom["customLocs"].toArray().size(); ++i) {
      QJsonObject customObject;
      QJsonArray customArray = tableArraysCustom["customLocs"].toArray()[i].toArray();
      // customObject["toggle"] = QJsonValue(toggle->currentText()).toString();
      customObject["preset"] = QJsonValue(sensorType->currentText()).toString();
      customObject["toggle"] = (QJsonValue(toggle->currentText()).toString() == "Yes") ? QJsonValue(true) : QJsonValue(false);
      customObject["type"] = QJsonValue(type->currentText()).toString();
      customObject["attribute"] = QJsonValue(attribute->currentText()).toString();
      customObject["operation"] = operation->itemText(operation->currentIndex());
      customObject["output_frequency"] = output_frequency->text().toDouble();
      customObject["direction"] = direction->itemText(direction->currentIndex());
      customObject["name"] = customArray[0].toString();

      // Future schema
      QJsonArray origin;
      for (int j=1; j<4; ++j) origin.append(customArray[j].toDouble());

      QJsonArray dimensions;
      for (int j=4; j<7; ++j) dimensions.append(customArray[j].toDouble());

      // ClaymoreUW artifacts
      QJsonArray domain_start;
      domain_start.append(customArray[1].toDouble());
      domain_start.append(customArray[2].toDouble());
      domain_start.append(customArray[3].toDouble());

      QJsonArray domain_end;
      domain_end.append(customArray[1].toDouble() + customArray[4].toDouble());
      domain_end.append(customArray[2].toDouble() + customArray[5].toDouble());
      domain_end.append(customArray[3].toDouble() + customArray[6].toDouble());

      if (0) { // Future schema
        customObject["origin"] = origin;
        customObject["dimensions"] = dimensions;
      } else { // ClaymoreUW artifacts, to be deprecated
        customObject["domain_start"] = domain_start;
        customObject["domain_end"] = domain_end;
      }

      sensorsArray.append(customObject);
      if (type->currentText() == "grid") {
        gridSensorsArray.append(customObject);
        jsonObject["grid-sensors"] = gridSensorsArray; // ClaymoreUW, to be deprecated (use "sensors" instead)
      } else {
        particleSensorsArray.append(customObject);
        jsonObject["particle-sensors"] = particleSensorsArray; // ClaymoreUW, to be deprecated (use "sensors" instead)
      }
    }
    return true;
  } else if (stackIndexToEnum == sensorEnum::WAVE_GAUGE) {
    for (int i = 0; i < tableArraysWG["waveGaugeLocs"].toArray().size(); ++i) {
      QJsonObject waveGaugesObject;
      QJsonArray waveGaugeArray = tableArraysWG["waveGaugeLocs"].toArray()[i].toArray();
      // waveGaugesObject["toggle"] = QJsonValue(toggleWG->currentText()).toString();
      waveGaugesObject["preset"] = QJsonValue(sensorType->currentText()).toString();
      waveGaugesObject["toggle"] = (QJsonValue(toggleWG->currentText()).toString() == "Yes") ? QJsonValue(true) : QJsonValue(false);
      waveGaugesObject["type"] = QJsonValue(typeWG->currentText()).toString();
      waveGaugesObject["attribute"] = QJsonValue(attributeWG->currentText()).toString();
      waveGaugesObject["operation"] = operationWG->itemText(operationWG->currentIndex());
      waveGaugesObject["output_frequency"] = output_frequencyWG->text().toDouble();
      waveGaugesObject["direction"] = directionWG->itemText(directionWG->currentIndex());
      waveGaugesObject["name"] = waveGaugeArray[0].toString();

      // Future schema
      QJsonArray origin;
      for (int j=1; j<4; ++j) origin.append(waveGaugeArray[j].toDouble());

      QJsonArray dimensions;
      for (int j=4; j<7; ++j) dimensions.append(waveGaugeArray[j].toDouble());

      // ClaymoreUW artifacts
      QJsonArray domain_start;
      domain_start.append(waveGaugeArray[1].toDouble());
      domain_start.append(waveGaugeArray[2].toDouble());
      domain_start.append(waveGaugeArray[3].toDouble());

      QJsonArray domain_end;
      domain_end.append(waveGaugeArray[1].toDouble() + waveGaugeArray[4].toDouble());
      domain_end.append(waveGaugeArray[2].toDouble() + waveGaugeArray[5].toDouble());
      domain_end.append(waveGaugeArray[3].toDouble() + waveGaugeArray[6].toDouble());
      if (0) { // Future schema
        waveGaugesObject["origin"] = origin;
        waveGaugesObject["dimensions"] = dimensions;
      } else { // ClaymoreUW artifacts, to be deprecated
        waveGaugesObject["domain_start"] = domain_start;
        waveGaugesObject["domain_end"] = domain_end;
      }
      if (toggleWG->currentText() == "Yes") {
      sensorsArray.append(waveGaugesObject);
      if (typeWG->currentText() == "grid") {
        gridSensorsArray.append(waveGaugesObject);
        jsonObject["grid-sensors"] = gridSensorsArray; // ClaymoreUW, to be deprecated (use "sensors" instead)
      } else {
        particleSensorsArray.append(waveGaugesObject);
        jsonObject["particle-sensors"] = particleSensorsArray; // ClaymoreUW, to be deprecated (use "sensors" instead)
      }
      }
    }
    return true;
  } else if (stackIndexToEnum == sensorEnum::VELOCITY_METER) {
    for (int i = 0; i < tableArraysVM["velociMeterLocs"].toArray().size(); ++i) {
      QJsonObject velociMetersObject;
      QJsonArray velociMeterArray = tableArraysVM["velociMeterLocs"].toArray()[i].toArray();
      // velociMetersObject["toggle"] = QJsonValue(toggleVM->currentText()).toString();
      velociMetersObject["preset"] = QJsonValue(sensorType->currentText()).toString();
      velociMetersObject["toggle"] = (QJsonValue(toggleVM->currentText()).toString() == "Yes") ? QJsonValue(true) : QJsonValue(false);
      velociMetersObject["type"] = QJsonValue(typeVM->currentText()).toString();
      velociMetersObject["attribute"] = QJsonValue(attributeVM->currentText()).toString();
      velociMetersObject["operation"] = operationVM->itemText(operationVM->currentIndex());
      velociMetersObject["output_frequency"] = output_frequencyVM->text().toDouble();
      velociMetersObject["direction"] = directionVM->itemText(directionVM->currentIndex());
      velociMetersObject["name"] = velociMeterArray[0].toString();

      // Future schema
      QJsonArray origin;
      for (int j=1; j<4; ++j) origin.append(velociMeterArray[j].toDouble());

      QJsonArray dimensions;
      for (int j=4; j<7; ++j) dimensions.append(velociMeterArray[j].toDouble());
      
      // ClaymoreUW artifacts
      QJsonArray domain_start;
      domain_start.append(velociMeterArray[1].toDouble());
      domain_start.append(velociMeterArray[2].toDouble());
      domain_start.append(velociMeterArray[3].toDouble());

      QJsonArray domain_end;
      domain_end.append(velociMeterArray[1].toDouble() + velociMeterArray[4].toDouble());
      domain_end.append(velociMeterArray[2].toDouble() + velociMeterArray[5].toDouble());
      domain_end.append(velociMeterArray[3].toDouble() + velociMeterArray[6].toDouble());

      if (0) { // Future schema
        velociMetersObject["origin"] = origin;
        velociMetersObject["dimensions"] = dimensions;
      } else { // ClaymoreUW artifacts, to be deprecated
        velociMetersObject["domain_start"] = domain_start;
        velociMetersObject["domain_end"] = domain_end;
      }

      if (toggleVM->currentText() == "Yes") {
        sensorsArray.append(velociMetersObject);
        if (typeVM->currentText() == "grid") {
          gridSensorsArray.append(velociMetersObject);
          jsonObject["grid-sensors"] = gridSensorsArray; // ClaymoreUW, to be deprecated (use "sensors" instead)
        } else {
          particleSensorsArray.append(velociMetersObject);
          jsonObject["particle-sensors"] = particleSensorsArray; // ClaymoreUW, to be deprecated (use "sensors" instead)
        }
      }
    }
    return true;
  } else if (stackIndexToEnum == sensorEnum::LOAD_CELL) {
    for (int i = 0; i < tableArraysLC["loadCellLocs"].toArray().size(); ++i) {
      QJsonObject loadCellsObject;
      QJsonArray loadCellArray = tableArraysLC["loadCellLocs"].toArray()[i].toArray();
      // loadCellsObject["toggle"] = QJsonValue(toggleLC->currentText()).toString();
      loadCellsObject["preset"] = QJsonValue(sensorType->currentText()).toString();
      loadCellsObject["toggle"] = (QJsonValue(toggleLC->currentText()).toString() == "Yes") ? QJsonValue(true) : QJsonValue(false);
      loadCellsObject["type"] = QJsonValue(typeLC->currentText()).toString();
      loadCellsObject["attribute"] = QJsonValue(attributeLC->currentText()).toString();
      loadCellsObject["operation"] = operationLC->itemText(operationLC->currentIndex());
      loadCellsObject["output_frequency"] = output_frequencyLC->text().toDouble();
      loadCellsObject["direction"] = directionLC->itemText(directionLC->currentIndex());
      loadCellsObject["name"] = loadCellArray[0].toString();

      // Future schema
      QJsonArray origin;
      for (int j=1; j<4; ++j) origin.append(loadCellArray[j].toDouble());

      QJsonArray dimensions;
      for (int j=4; j<7; ++j) dimensions.append(loadCellArray[j].toDouble());
      
      // ClaymoreUW artifacts
      QJsonArray domain_start;
      domain_start.append(loadCellArray[1].toDouble());
      domain_start.append(loadCellArray[2].toDouble());
      domain_start.append(loadCellArray[3].toDouble());

      QJsonArray domain_end;
      domain_end.append(loadCellArray[1].toDouble() + loadCellArray[4].toDouble());
      domain_end.append(loadCellArray[2].toDouble() + loadCellArray[5].toDouble());
      domain_end.append(loadCellArray[3].toDouble() + loadCellArray[6].toDouble());

      if (0) { // Future schema
        loadCellsObject["origin"] = origin;
        loadCellsObject["dimensions"] = dimensions;
      } else { // ClaymoreUW artifacts, to be deprecated
        loadCellsObject["domain_start"] = domain_start;
        loadCellsObject["domain_end"] = domain_end;
      }
      if (toggleLC->currentText() == "Yes") {
      sensorsArray.append(loadCellsObject);
      if (typeLC->currentText() == "grid") { 
        gridSensorsArray.append(loadCellsObject);
        jsonObject["grid-sensors"] = gridSensorsArray; // ClaymoreUW, to be deprecated (use "sensors" instead)
      } else {
        particleSensorsArray.append(loadCellsObject);
        jsonObject["particle-sensors"] = particleSensorsArray; // ClaymoreUW, to be deprecated (use "sensors" instead)
      }
      }
    }
    return true;
  } else if (stackIndexToEnum == sensorEnum::PIEZO_METER) {
    for (int i = 0; i < tableArraysWG["piezoMeterLocs"].toArray().size(); ++i) {
      QJsonObject piezoMetersObject;
      QJsonArray piezoMeterArray = tableArraysPM["piezoMeterLocs"].toArray()[i].toArray();
      piezoMetersObject["preset"] = QJsonValue(sensorType->currentText()).toString();
      piezoMetersObject["toggle"] = (QJsonValue(togglePM->currentText()).toString() == "Yes") ? QJsonValue(true) : QJsonValue(false);
      piezoMetersObject["type"] = QJsonValue(typePM->currentText()).toString();
      piezoMetersObject["attribute"] = QJsonValue(attributePM->currentText()).toString();
      piezoMetersObject["operation"] = operationPM->itemText(operationPM->currentIndex());
      piezoMetersObject["output_frequency"] = output_frequencyPM->text().toDouble();
      piezoMetersObject["direction"] = directionPM->itemText(directionPM->currentIndex());
      piezoMetersObject["name"] = piezoMeterArray[0].toString();

      // Future schema
      QJsonArray origin;
      for (int j=1; j<4; ++j) origin.append(piezoMeterArray[j].toDouble());

      QJsonArray dimensions;
      for (int j=4; j<7; ++j) dimensions.append(piezoMeterArray[j].toDouble());

      // ClaymoreUW artifacts
      QJsonArray domain_start;
      domain_start.append(piezoMeterArray[1].toDouble());
      domain_start.append(piezoMeterArray[2].toDouble());
      domain_start.append(piezoMeterArray[3].toDouble());

      QJsonArray domain_end;
      domain_end.append(piezoMeterArray[1].toDouble() + piezoMeterArray[4].toDouble());
      domain_end.append(piezoMeterArray[2].toDouble() + piezoMeterArray[5].toDouble());
      domain_end.append(piezoMeterArray[3].toDouble() + piezoMeterArray[6].toDouble());
      if (0) { // Future schema
        piezoMetersObject["origin"] = origin;
        piezoMetersObject["dimensions"] = dimensions;
      } else { // ClaymoreUW artifacts, to be deprecated
        piezoMetersObject["domain_start"] = domain_start;
        piezoMetersObject["domain_end"] = domain_end;
      }

      if (togglePM->currentText() == "Yes") {
        sensorsArray.append(piezoMetersObject);
        if (typePM->currentText() == "grid") {
          gridSensorsArray.append(piezoMetersObject);
          jsonObject["grid-sensors"] = gridSensorsArray; // ClaymoreUW, to be deprecated (use "sensors" instead)
        } else {
          particleSensorsArray.append(piezoMetersObject);
          jsonObject["particle-sensors"] = particleSensorsArray; // ClaymoreUW, to be deprecated (use "sensors" instead)
        }
      }
    }
    return true;
  } else {
    // Debug
    qDebug() << "SensorMPM::outputToJSON() - Error: Invalid sensor type";
    // return false; 
  }
  if (0) jsonObject["sensors"] = sensorsArray; // future schema
  return true;
}

bool
SensorMPM::inputFromJSON(QJsonObject &jsonObject)
{
  // Exit early for now while debugging
  return true;

  // ----
  // sensorType->setCurrentIndex(0); // Custom default
  if (jsonObject.contains("preset")) {
    QString sensorPreset = jsonObject["preset"].toString();
    if (sensorPreset == "Custom") {
      setSensorType(0);
    } else if (sensorPreset == "Wave-Gauges") {
      setSensorType(1);
    } else if (sensorPreset == "Velocimeters") {
      setSensorType(2);
    } else if (sensorPreset == "Load-Cells") {
      setSensorType(3);
    } else if (sensorPreset == "Piezometers") {
      setSensorType(4);
    }
  }
  else {
    if (jsonObject.contains("attribute")) {
      QString sensorAttribute = jsonObject["attribute"].toString();
      if (sensorAttribute == "Elevation" || sensorAttribute == "Position_Y") {
        setSensorType(1);
      } else if (sensorAttribute == "Velocity" || sensorAttribute == "Velocity_X" || sensorAttribute == "Velocity_Y" || sensorAttribute == "Velocity_Z" || sensorAttribute == "Velocity_Magnitude") {
        setSensorType(2);
      } else if (sensorAttribute == "Force" || sensorAttribute == "Force_X" || sensorAttribute == "Force_Y" || sensorAttribute == "Force_Z" || sensorAttribute == "Force_Magnitude") {
        setSensorType(3);
      } else if (sensorAttribute == "Pressure") {
        setSensorType(4);
      }
    }  else {
      setSensorType(0);
    }
  }

  if (sensorType->currentIndex() == 0) {
    toggle->inputFromJSON(jsonObject);
    type->inputFromJSON(jsonObject);
    attribute->inputFromJSON(jsonObject);
    operation->inputFromJSON(jsonObject);
    direction->inputFromJSON(jsonObject);
    output_frequency->inputFromJSON(jsonObject);
    customTable->inputFromJSON(jsonObject);
  }
  else if (sensorType->currentIndex() == 1) {
    toggleWG->inputFromJSON(jsonObject);
    typeWG->inputFromJSON(jsonObject);
    attributeWG->inputFromJSON(jsonObject);
    operationWG->inputFromJSON(jsonObject);
    directionWG->inputFromJSON(jsonObject);
    output_frequencyWG->inputFromJSON(jsonObject);  
    waveGaugesTable->inputFromJSON(jsonObject);
  }
  else if (sensorType->currentIndex() == 2) {
    toggleVM->inputFromJSON(jsonObject);
    typeVM->inputFromJSON(jsonObject);
    attributeVM->inputFromJSON(jsonObject);
    operationVM->inputFromJSON(jsonObject);
    directionVM->inputFromJSON(jsonObject);
    output_frequencyVM->inputFromJSON(jsonObject);
    velociMetersTable->inputFromJSON(jsonObject);
  }
  else if (sensorType->currentIndex() == 3) {
    toggleLC->inputFromJSON(jsonObject);
    typeLC->inputFromJSON(jsonObject);
    attributeLC->inputFromJSON(jsonObject);
    operationLC->inputFromJSON(jsonObject);
    directionLC->inputFromJSON(jsonObject);
    output_frequencyLC->inputFromJSON(jsonObject);
    loadCellsTable->inputFromJSON(jsonObject);
  }
  else if (sensorType->currentIndex() == 4) {
    togglePM->inputFromJSON(jsonObject);
    typePM->inputFromJSON(jsonObject);
    attributePM->inputFromJSON(jsonObject);
    operationPM->inputFromJSON(jsonObject);
    directionPM->inputFromJSON(jsonObject);
    output_frequencyPM->inputFromJSON(jsonObject);
    // Make sure to append to the table, it may have multiple sensors
    piezoMetersTable->inputFromJSON(jsonObject);
  }

  return true;
}

bool
SensorMPM::copyFiles(QString &destDir)
{
  Q_UNUSED(destDir);
  return true;
}


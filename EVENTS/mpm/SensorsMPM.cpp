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

#include <SensorsMPM.h>
#include <QGroupBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QStringList>
#include <QJsonArray>
#include <QTabWidget>

// #include <SC_FileEdit.h>
#include <SC_TableEdit.h>
#include <SC_ComboBox.h>
#include <SC_DoubleLineEdit.h>

SensorsMPM::SensorsMPM(QWidget *parent)
  :SimCenterWidget(parent)
{
  //
  // create selectable options widgets
  //
  // theOpenSeesPyScript = new SC_FileEdit("openSeesPyScript");
  // theSurfaceFile = new SC_FileEdit("interfaceSurface");

  // QGridLayout *theLayout = new QGridLayout();
  // theLayout->addWidget(new QLabel("OpenSeesPy Script"),0,0);
  // theLayout->addWidget(theOpenSeesPyScript, 0,1);
  // theLayout->addWidget(new QLabel("Surface File"),1,0);
  // theLayout->addWidget(theSurfaceFile, 1,1);
  // theLayout->setRowStretch(2,1);
  // this->setLayout(theLayout);
    


  //
  // create all little widgets
  //
  
  QStringList yesNo; yesNo <<  "Yes" << "No";
  QStringList noYes; noYes <<  "No" << "Yes";
  QStringList typeList; typeList <<  "particles" << "grid"; // << "nodes" << "elements" << "surface" << "edge";
  QStringList typeGridList; typeGridList << "grid";
  QStringList typeParticleList; typeParticleList << "particles";

  // ===========================================================================
  QStringList  listWG; listWG << "Name" << "Origin X" << "Origin Y" << "Origin Z" << "Dimension X" << "Dimension Y" << "Dimension Z" ;
  QStringList  dataWG; dataWG << "WaveGauge1" << "16.0" << "1.75" << "0.4" << "0.05" << "1.00" << "0.05" 
				                      << "WaveGauge2" << "26.0" << "1.75" << "0.4" << "0.05" << "1.00" << "0.05" 
				                      << "WaveGauge3" << "38.0" << "1.75" << "0.4" << "0.05" << "1.00" << "0.05" ;
  waveGaugesTable = new SC_TableEdit("waveGaugeLocs",  listWG, 3, dataWG);
  
  QStringList  listVM; listVM << "Name" << "Origin X" << "Origin Y" << "Origin Z" << "Dimension X" << "Dimension Y" << "Dimension Z" ;
  QStringList  dataVM; dataVM << "VelocityMeter1" << "16.0" << "0.00" << "0.4" << "0.05" << "2.75" << "0.05" 
				                      << "VelocityMeter2" << "43.8" << "1.75" << "0.4" << "0.05" << "1.00" << "0.05" ;
  velociMetersTable  = new SC_TableEdit("velociMeterLocs", listVM, 2, dataVM);
  
  QStringList  listLC; listLC << "Name" << "Origin X" << "Origin Y" << "Origin Z" << "Dimension X" << "Dimension Y" << "Dimension Z" ;
  QStringList  dataLC; dataLC << "LoadCell1" << "45.799" << "2.10" << "1.35" << "0.05" << "0.625" << "0.95" ;  
  loadCellsTable  = new SC_TableEdit("loadCellLocs", listLC, 1, dataLC);

  // QStringList  listLC; listLC<< "Name" << "Attributes" << "Operation" <<  "Sample Freq." <<  "Origin X" << "Origin Y" << "Origin Z" << "Dimension X" << "Dimension Y" << "Dimension Z" ;


  // 
  // now add the widgets to Grpup Boxes
  //

  // QGroupBox *openseesBox = new QGroupBox("Bodies' Geometry Output");
  // QGridLayout *openseesLayout = new QGridLayout();  
  // openseesBox->setLayout(openseesLayout);

  // openseesLayout->addWidget(new QLabel("Output File Type"),0,0);
  // openseesLayout->addWidget(vtkOS_Output,0,1);  
  // openseesLayout->addWidget(new QLabel("Output Frequency"),1,0);
  // openseesLayout->addWidget(outputOS_Dt,1,1);
  // openseesLayout->addWidget(new QLabel("Hz"),1,2);  
			    
  QGroupBox *sensorBox = new QGroupBox("Specify Instrumentation");
  QGridLayout *sensorLayout = new QGridLayout();  
  sensorBox->setLayout(sensorLayout);

  // sensorLayout->addWidget(new QLabel("Output File Type"),0,0);
  // sensorLayout->addWidget(vtkSensor_Output,0,1);    
  // sensorLayout->addWidget(new QLabel("Output Frequency"),1,0);
  // sensorLayout->addWidget(outputSensor_Dt,1,1);
  // sensorLayout->addWidget(new QLabel("sec."),1,2);

  // sensorLayout->addWidget(new QLabel("Free Surface Probes"),0,0);
  // sensorLayout->addWidget(toggleWG,0,1);


  // ===========================================================================
  toggleWG = new SC_ComboBox("toggleWG", yesNo); // wave gauge (elevation rel. to grav. vec. Sensor particle free surface)
  typeWG = new SC_ComboBox("typeWG", typeParticleList); // wave gauge (elevation rel. to grav. vec. Sensor particle free surface)
  attributeWG = new SC_ComboBox("attribute_WG", QStringList() << "Elevation" << "Position_Y");
  operationWG = new SC_ComboBox("operation_WG", QStringList() << "Max");
  output_frequencyWG = new SC_DoubleLineEdit("output_frequency_WG", 30);
  directionWG = new SC_ComboBox("directionWG", QStringList() << "N/A");

  toggleLC  = new SC_ComboBox("toggleLC", yesNo); // load cell (force on grid)
  typeLC  = new SC_ComboBox("typeLC", typeGridList); // load cell (force on grid)
  attributeLC = new SC_ComboBox("attribute_LC", QStringList() << "Force_X" << "Force_Y" << "Force_Z" << "Force_Magnitude");
  operationLC = new SC_ComboBox("operation_LC", QStringList() << "Sum");
  output_frequencyLC = new SC_DoubleLineEdit("output_frequency_LC", 120);
  directionLC = new SC_ComboBox("directionLC", QStringList() << "X" << "Y" << "Z" << "X+" << "Y+" << "Z+" << "X-" << "Y-" << "Z-" << "N/A");

  toggleVM  = new SC_ComboBox("toggleVM", noYes); // velocity meter (velocity on grid)
  typeVM  = new SC_ComboBox("typeVM", typeParticleList); // velocity meter (velocity on grid)
  attributeVM = new SC_ComboBox("attribute_VM", QStringList() << "Velocity_X" << "Velocity_Y" << "Velocity_Z" << "Velocity_Magnitude");
  operationVM = new SC_ComboBox("operation_VM", QStringList() << "Average" << "Max" << "Min");
  output_frequencyVM = new SC_DoubleLineEdit("output_frequency_VM", 30);
  directionVM = new SC_ComboBox("directionVM", QStringList() << "N/A");


  // ===========================================================================
  QWidget *wgWidget = new QWidget();
  QGridLayout *wgLayout = new QGridLayout();
  wgWidget->setLayout(wgLayout);

  wgLayout->addWidget(new QLabel("Use Wave-Gauges?"),0,0);
  wgLayout->addWidget(toggleWG,0,1);
  wgLayout->addWidget(new QLabel("Apply On"),1,0);
  wgLayout->addWidget(typeWG,1,1);
  wgLayout->addWidget(new QLabel("Attribute to Measure"),2,0);
  wgLayout->addWidget(attributeWG,2,1);
  wgLayout->addWidget(new QLabel("Operation to Perform"),3,0);
  wgLayout->addWidget(operationWG,3,1);
  wgLayout->addWidget(new QLabel("Sampling Rate (Freq.)"),4,0);
  wgLayout->addWidget(output_frequencyWG,4,1);
  wgLayout->addWidget(new QLabel("Hz"),4,2);
  wgLayout->addWidget(new QLabel("In Direction"),5,0);
  wgLayout->addWidget(directionWG,5,1);
  wgLayout->addWidget(waveGaugesTable,7,0,1,4);
  // waveGaugesTable->setMinimumHeight(200);
  // waveGaugesTable->setMaximumHeight(200);
  // waveGaugesTable->setMinimumWidth(500);
  // waveGaugesTable->setMaximumWidth(500);
  // waveGaugesTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  wgLayout->setRowStretch(6,1);
  // ===========================================================================
  QWidget *vmWidget = new QWidget();
  QGridLayout *vmLayout = new QGridLayout();
  vmWidget->setLayout(vmLayout);
  
  vmLayout->addWidget(new QLabel("Use Veloci-Meters?"),0,0);
  vmLayout->addWidget(toggleVM,0,1);
  vmLayout->addWidget(new QLabel("Apply On"),1,0);
  vmLayout->addWidget(typeVM,1,1);
  vmLayout->addWidget(new QLabel("Attribute to Measure"),2,0);
  vmLayout->addWidget(attributeVM,2,1);
  vmLayout->addWidget(new QLabel("Operation to Perform"),3,0);
  vmLayout->addWidget(operationVM,3,1);
  vmLayout->addWidget(new QLabel("Sampling Rate (Freq.)"),4,0);
  vmLayout->addWidget(output_frequencyVM,4,1);
  vmLayout->addWidget(new QLabel("Hz"),4,2);
  vmLayout->addWidget(new QLabel("In Direction"),5,0);
  vmLayout->addWidget(directionVM,5,1);
  vmLayout->addWidget(velociMetersTable,7,0,1,4);
  vmLayout->setRowStretch(6,1);
  // ===========================================================================
  QWidget *lcWidget = new QWidget();
  QGridLayout *lcLayout = new QGridLayout();
  lcWidget->setLayout(lcLayout);
  
  lcLayout->addWidget(new QLabel("Use Load-Cells?"),0,0);
  lcLayout->addWidget(toggleLC,0,1);
  lcLayout->addWidget(new QLabel("Apply On"),1,0);
  lcLayout->addWidget(typeLC,1,1);
  lcLayout->addWidget(new QLabel("Attribute to Measure"),2,0);
  lcLayout->addWidget(attributeLC,2,1);
  lcLayout->addWidget(new QLabel("Operation to Perform"),3,0);
  lcLayout->addWidget(operationLC,3,1);
  lcLayout->addWidget(new QLabel("Sampling Rate (Freq.)"),4,0);
  lcLayout->addWidget(output_frequencyLC,4,1);
  lcLayout->addWidget(new QLabel("Hz"),4,2);
  lcLayout->addWidget(new QLabel("In Direction"),5,0);
  lcLayout->addWidget(directionLC,5,1);
  lcLayout->addWidget(loadCellsTable,7,0,1,4);    
  lcLayout->setRowStretch(6,1);
  // ===========================================================================
  QTabWidget *theTabWidget = new QTabWidget();
  theTabWidget->addTab(wgWidget, "Wave-Gauges");
  theTabWidget->addTab(vmWidget, "Velocity-Meters");
  theTabWidget->addTab(lcWidget, "Load-Cells");  
  sensorLayout->addWidget(theTabWidget,2,0,1,4);
  sensorLayout->setRowStretch(3,1);
  // int sizePrimaryTabs = 20;
  // theTabWidget->setIconSize(QSize(sizePrimaryTabs,sizePrimaryTabs));
  // theTabWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

  
  //
  // now boxes to this widget
  //
  
  QGridLayout *layout = new QGridLayout;
  layout->addWidget(sensorBox, 1,0);

  this->setLayout(layout);
  layout->setRowStretch(2,1);
}

SensorsMPM::~SensorsMPM()
{

}

bool
SensorsMPM::outputToJSON(QJsonObject &jsonObject)
{
  toggleWG->outputToJSON(jsonObject);
  typeWG->outputToJSON(jsonObject);
  attributeWG->outputToJSON(jsonObject);
  operationWG->outputToJSON(jsonObject);
  directionWG->outputToJSON(jsonObject);
  output_frequencyWG->outputToJSON(jsonObject);
  waveGaugesTable->outputToJSON(jsonObject);

  toggleVM->outputToJSON(jsonObject);
  typeVM->outputToJSON(jsonObject);
  attributeVM->outputToJSON(jsonObject);
  operationVM->outputToJSON(jsonObject);
  directionVM->outputToJSON(jsonObject);
  output_frequencyVM->outputToJSON(jsonObject);
  velociMetersTable->outputToJSON(jsonObject);

  toggleLC->outputToJSON(jsonObject);
  typeLC->outputToJSON(jsonObject);
  attributeLC->outputToJSON(jsonObject);
  operationLC->outputToJSON(jsonObject);
  directionLC->outputToJSON(jsonObject);
  output_frequencyLC->outputToJSON(jsonObject);
  loadCellsTable->outputToJSON(jsonObject);

  return true;
}

bool
SensorsMPM::inputFromJSON(QJsonObject &jsonObject)
{
  toggleWG->inputFromJSON(jsonObject);
  typeWG->inputFromJSON(jsonObject);
  attributeWG->inputFromJSON(jsonObject);
  operationWG->inputFromJSON(jsonObject);
  directionWG->inputFromJSON(jsonObject);
  output_frequencyWG->inputFromJSON(jsonObject);  
  waveGaugesTable->inputFromJSON(jsonObject);
  
  toggleVM->inputFromJSON(jsonObject);
  typeVM->inputFromJSON(jsonObject);
  attributeVM->inputFromJSON(jsonObject);
  operationVM->inputFromJSON(jsonObject);
  directionVM->inputFromJSON(jsonObject);
  output_frequencyVM->inputFromJSON(jsonObject);
  velociMetersTable->inputFromJSON(jsonObject);
  
  toggleLC->inputFromJSON(jsonObject);
  typeLC->inputFromJSON(jsonObject);
  attributeLC->inputFromJSON(jsonObject);
  operationLC->inputFromJSON(jsonObject);
  directionLC->inputFromJSON(jsonObject);
  output_frequencyLC->inputFromJSON(jsonObject);
  loadCellsTable->inputFromJSON(jsonObject);

  return true;
}

// bool
// SensorsMPM::copyFiles(QString &destDir)
// {
//   // if (theOpenSeesPyScript->copyFile(destDir) != true)
//   //   return false;
//   // return theSurfaceFile->copyFile(destDir);
//   return false;    
// }


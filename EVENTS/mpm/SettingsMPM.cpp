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

#include <SettingsMPM.h>
#include <QLabel>
#include <QComboBox>
#include <QGroupBox>
#include <QGridLayout>
#include <SC_ComboBox.h>
#include <SC_CheckBox.h>
#include <SC_DoubleLineEdit.h>
#include <SC_IntLineEdit.h>
#include <SC_StringLineEdit.h>
#include <QJsonObject>
#include <QJsonArray>



SettingsMPM::SettingsMPM(QWidget *parent)
  :SimCenterWidget(parent)
{
  int numRow = 0;
  QGridLayout *layout = new QGridLayout();
  this->setLayout(layout);
  QGroupBox *simSettings = new QGroupBox("Simulation Settings");
  QGridLayout *simSettingsLayout = new QGridLayout();  
  simSettings->setLayout(simSettingsLayout);


  // -----------------------
  numRow = 0;

  QGroupBox *ambientBox = new QGroupBox("Ambient");
  QGridLayout *ambientBoxLayout = new QGridLayout();
  ambientBox->setLayout(ambientBoxLayout);  

  cflNumber = new SC_DoubleLineEdit("cfl", 0.5);
  ambientBoxLayout->addWidget(new QLabel("CFL Number"), numRow, 0);
  ambientBoxLayout->itemAt(ambientBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  ambientBoxLayout->itemAt(ambientBoxLayout->count()-1)->widget()->setToolTip("Courant-Friedrichs-Lewy Number, Time-Step <= CFL * Grid-Cell-Size / P-Wave-Velocity. Controls simulation stability. CFL = 0.3 to 0.5 is a good range.");
  ambientBoxLayout->addWidget(cflNumber, numRow, 1); 
  ambientBoxLayout->addWidget(new QLabel(""), numRow++, 2);

  // temperature = new SC_DoubleLineEdit("temperature", 0.5);
  // ambientBoxLayout->addWidget(new QLabel("Temperature"), numRow, 0);
  // ambientBoxLayout->itemAt(ambientBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  // ambientBoxLayout->itemAt(ambientBoxLayout->count()-1)->widget()->setToolTip("Base-line temperature of the domain. Areas occupied by some type of material can have a different temperature.");
  // ambientBoxLayout->addWidget(temperature, numRow, 1); 
  // ambientBoxLayout->addWidget(new QLabel("deg. C"), numRow++, 2);

  gravityX = new SC_DoubleLineEdit("gravityX", 0.0);
  gravityY = new SC_DoubleLineEdit("gravityY", -9.81);
  gravityZ = new SC_DoubleLineEdit("gravityZ", 0.0);
  ambientBoxLayout->addWidget(new QLabel("Gravity (X,Y,Z)"), numRow, 0);
  ambientBoxLayout->itemAt(ambientBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  ambientBoxLayout->addWidget(gravityX, numRow, 1);  
  ambientBoxLayout->addWidget(gravityY, numRow, 2);  
  ambientBoxLayout->addWidget(gravityZ, numRow, 3);  
  ambientBoxLayout->addWidget(new QLabel("m/sec.^2"), numRow++, 4);

  ambientBoxLayout->setRowStretch(numRow,1);
  // ambientBoxLayout->setColumnStretch(5,1);
  simSettingsLayout->addWidget(ambientBox, 0, 0, 2, 5);
  
  // -----------------------
  numRow = 0;  

  QGroupBox *dimensionsBox = new QGroupBox("Spatial");
  QGridLayout *dimensionsBoxLayout = new QGridLayout();
  dimensionsBox->setLayout(dimensionsBoxLayout);  

  gridCellSize = new SC_DoubleLineEdit("defaultDx", 0.10);
  dimensionsBoxLayout->addWidget(new QLabel("Grid Cell Size (dx)"), numRow, 0);
  dimensionsBoxLayout->itemAt(dimensionsBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  dimensionsBoxLayout->addWidget(gridCellSize,numRow,1);
  dimensionsBoxLayout->addWidget(new QLabel("m"), numRow++, 2);

  domainSizeX = new SC_DoubleLineEdit("domain_X", 90);
  domainSizeY = new SC_DoubleLineEdit("domain_Y", 2.9);
  domainSizeZ = new SC_DoubleLineEdit("domain_Z", 3.65);  
  dimensionsBoxLayout->addWidget(new QLabel("Simulation Domain (X, Y, Z)"), numRow, 0);  
  dimensionsBoxLayout->itemAt(dimensionsBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  dimensionsBoxLayout->addWidget(domainSizeX, numRow, 1);
  dimensionsBoxLayout->addWidget(domainSizeY, numRow, 2);
  dimensionsBoxLayout->addWidget(domainSizeZ, numRow, 3);
  dimensionsBoxLayout->addWidget(new QLabel("m"), numRow++, 4);

  mirrorDomainX = new SC_CheckBox("mirrorDomainX",false);
  mirrorDomainY = new SC_CheckBox("mirrorDomainY",false);
  mirrorDomainZ = new SC_CheckBox("mirrorDomainZ",false);
  dimensionsBoxLayout->addWidget(new QLabel("Mirror Domain Over YZ-XZ-XY?"), numRow, 0);
  dimensionsBoxLayout->itemAt(dimensionsBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  dimensionsBoxLayout->addWidget(mirrorDomainX, numRow, 1);  
  dimensionsBoxLayout->itemAt(dimensionsBoxLayout->count()-1)->setAlignment(Qt::AlignCenter);
  dimensionsBoxLayout->addWidget(mirrorDomainY, numRow, 2);  
  dimensionsBoxLayout->itemAt(dimensionsBoxLayout->count()-1)->setAlignment(Qt::AlignCenter);
  dimensionsBoxLayout->addWidget(mirrorDomainZ, numRow, 3);  
  dimensionsBoxLayout->itemAt(dimensionsBoxLayout->count()-1)->setAlignment(Qt::AlignCenter);
  dimensionsBoxLayout->addWidget(new QLabel(""), numRow++, 4);
  dimensionsBoxLayout->setRowStretch(numRow,1);
  dimensionsBoxLayout->setColumnStretch(5,1);

  simSettingsLayout->addWidget(dimensionsBox, 4, 0, 4, 5);


  // -----------------------
  QGroupBox *timeBox = new QGroupBox("Temporal");
  QGridLayout *timeBoxLayout = new QGridLayout();
  timeBox->setLayout(timeBoxLayout);  

  numRow = 0;

  timeStep = new SC_DoubleLineEdit("defaultDt", 1e-5);
  timeBoxLayout->addWidget(new QLabel("Max Time Step (dt)"), numRow, 0);
  timeBoxLayout->itemAt(timeBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  timeBoxLayout->addWidget(timeStep, numRow, 1);
  timeBoxLayout->addWidget(new QLabel("sec."), numRow++, 2);

  QStringList timeIntegrationList ; timeIntegrationList <<  "Explicit (Forward Euler)" << "Semi-Implicit (Symplectic Euler)";
  timeIntegration = new SC_ComboBox("time_integration", timeIntegrationList);    
  timeBoxLayout->addWidget(new QLabel("Time-Integration Style"), numRow, 0);
  timeBoxLayout->itemAt(timeBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  timeBoxLayout->addWidget(timeIntegration, numRow, 1);  
  timeBoxLayout->addWidget(new QLabel(""), numRow++, 2);
  duration = new SC_DoubleLineEdit("duration",25.0);
  timeBoxLayout->addWidget(new QLabel("Simulation Duration"), numRow, 0);
  timeBoxLayout->itemAt(timeBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  timeBoxLayout->addWidget(duration,numRow, 1);  
  timeBoxLayout->addWidget(new QLabel("sec."), numRow++, 2);

  initialTime = new SC_DoubleLineEdit("initialTime",0.0);
  timeBoxLayout->addWidget(new QLabel("Initial Time"), numRow, 0);
  timeBoxLayout->itemAt(timeBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  timeBoxLayout->addWidget(initialTime,numRow, 1);  
  timeBoxLayout->addWidget(new QLabel("sec."), numRow++, 2);
  
  timeBoxLayout->setRowStretch(numRow,1);
  // timeBoxLayout->setColumnStretch(3,1);

  simSettingsLayout->addWidget(timeBox, 9, 0, 4, 3);
  simSettingsLayout->setRowStretch(13,1);
  // simSettingsLayout->setColumnStretch(5,1);
  // -----------------------
  
  numRow = 13;


  // -----------------------
  QGroupBox *scalingSettings = new QGroupBox("Scaling Laws");
  QGridLayout *scalingSettingsLayout = new QGridLayout();  
  scalingSettings->setLayout(scalingSettingsLayout);

  numRow = 0;

  froudeScaling = new SC_CheckBox("froudeScaling",false);
  scalingSettingsLayout->addWidget(new QLabel("Apply Froude Similitude?"), numRow, 0);
  scalingSettingsLayout->itemAt(scalingSettingsLayout->count()-1)->setAlignment(Qt::AlignRight);
  scalingSettingsLayout->addWidget(froudeScaling, numRow++, 1);  

  froudeLengthRatio = new SC_DoubleLineEdit("lengthRatio",1.0);
  scalingSettingsLayout->addWidget(new QLabel("Froude Scaling (Length Ratio)"), numRow, 0);
  scalingSettingsLayout->itemAt(scalingSettingsLayout->count()-1)->setAlignment(Qt::AlignRight);
  scalingSettingsLayout->addWidget(froudeLengthRatio, numRow, 1);  
  scalingSettingsLayout->addWidget(new QLabel("m/m"), numRow++, 2);
  
  froudeTimeRatio = new SC_DoubleLineEdit("timeRatio",1.0);
  scalingSettingsLayout->addWidget(new QLabel("Froude Time Ratio"), numRow, 0);
  scalingSettingsLayout->itemAt(scalingSettingsLayout->count()-1)->setAlignment(Qt::AlignRight);
  scalingSettingsLayout->addWidget(froudeTimeRatio, numRow, 1);  
  scalingSettingsLayout->addWidget(new QLabel("s/s"), numRow++, 2);
  
  cauchyScaling = new SC_CheckBox("cauchyScaling",false);
  scalingSettingsLayout->addWidget(new QLabel("Apply Cauchy Similitude?"), numRow, 0);
  scalingSettingsLayout->itemAt(scalingSettingsLayout->count()-1)->setAlignment(Qt::AlignRight);
  scalingSettingsLayout->addWidget(cauchyScaling, numRow++, 1);  

  cauchyBulkRatio = new SC_DoubleLineEdit("bulkRatio",1.0);
  scalingSettingsLayout->addWidget(new QLabel("Cauchy Elasticity Ratio"), numRow, 0);
  scalingSettingsLayout->itemAt(scalingSettingsLayout->count()-1)->setAlignment(Qt::AlignRight);
  scalingSettingsLayout->addWidget(cauchyBulkRatio, numRow, 1);  
  scalingSettingsLayout->addWidget(new QLabel("Pa/Pa"), numRow++, 2);
  scalingSettingsLayout->setRowStretch(numRow,1);
  scalingSettingsLayout->setColumnStretch(3,1);


  // -----------------------
  QGroupBox *gpuSettings = new QGroupBox("Computer");
  QGridLayout *gpuSettingsLayout = new QGridLayout();
  gpuSettings->setLayout(gpuSettingsLayout);

  numRow = 0;

  QStringList hpcList; hpcList << "TACC - UT Austin - Frontera" << "TACC - UT Austin - Lonestar6" <<  "TACC - UT Austin - Stampede3" << "Hyak - UW Seattle - Klone" << "ACCESS - TAMU - ACES" << "ACCESS - TAMU - FASTER" << "Your Computer" <<  "Custom";
  hpc = new SC_ComboBox("hpcSubType",hpcList);
  gpuSettingsLayout->addWidget(new QLabel("Computing Facility"),numRow,0);
  gpuSettingsLayout->itemAt(gpuSettingsLayout->count()-1)->setAlignment(Qt::AlignRight);
  gpuSettingsLayout->addWidget(hpc,numRow++,1);


  numGPUs = new SC_IntLineEdit("numGPUs", 3);  
  gpuSettingsLayout->addWidget(new QLabel("Max Number of GPUs"), numRow, 0);
  gpuSettingsLayout->itemAt(gpuSettingsLayout->count()-1)->setAlignment(Qt::AlignRight);
  gpuSettingsLayout->addWidget(numGPUs, numRow++, 1);

  modelsPerGPU = new SC_IntLineEdit("modelsPerGPU",3);
  gpuSettingsLayout->addWidget(new QLabel("Max Material Bodies Per GPU"), numRow, 0);
  gpuSettingsLayout->itemAt(gpuSettingsLayout->count()-1)->setAlignment(Qt::AlignRight);
  gpuSettingsLayout->addWidget(modelsPerGPU, numRow++, 1);  

  hpcCardBrand = new SC_StringLineEdit("hpcCardBrand", "NVIDIA");
  gpuSettingsLayout->addWidget(new QLabel("GPU Brand"), numRow, 0);
  gpuSettingsLayout->itemAt(gpuSettingsLayout->count()-1)->setAlignment(Qt::AlignRight);
  gpuSettingsLayout->addWidget(hpcCardBrand, numRow, 1); 
  gpuSettingsLayout->addWidget(new QLabel(""), numRow++, 2);

  hpcCardName = new SC_StringLineEdit("hpcCardName","NVIDIA A100");
  gpuSettingsLayout->addWidget(new QLabel("GPU Name"), numRow, 0);
  gpuSettingsLayout->itemAt(gpuSettingsLayout->count()-1)->setAlignment(Qt::AlignRight);
  gpuSettingsLayout->addWidget(hpcCardName, numRow++, 1); 

  hpcCardArchitecture = new SC_StringLineEdit("hpcCardArchitecture","Ampere");
  gpuSettingsLayout->addWidget(new QLabel("GPU Architecture"), numRow, 0);
  gpuSettingsLayout->itemAt(gpuSettingsLayout->count()-1)->setAlignment(Qt::AlignRight);
  gpuSettingsLayout->addWidget(hpcCardArchitecture, numRow++, 1); 

  hpcCardGlobalMemory = new SC_IntLineEdit("hpcCardGlobalMemory",40);
  gpuSettingsLayout->addWidget(new QLabel("GPU Global Memory"), numRow, 0);
  gpuSettingsLayout->itemAt(gpuSettingsLayout->count()-1)->setAlignment(Qt::AlignRight);
  gpuSettingsLayout->addWidget(hpcCardGlobalMemory, numRow, 1); 
  gpuSettingsLayout->addWidget(new QLabel("GB"), numRow++, 2);
  
  hpcCardComputeCapability = new SC_IntLineEdit("hpcCardComputeCapability",80);
  gpuSettingsLayout->addWidget(new QLabel("GPU Compute Capability"), numRow, 0);
  gpuSettingsLayout->itemAt(gpuSettingsLayout->count()-1)->setAlignment(Qt::AlignRight);
  gpuSettingsLayout->addWidget(hpcCardComputeCapability, numRow, 1); 
  gpuSettingsLayout->addWidget(new QLabel("XY <- arch_XY"), numRow++, 2);




  connect(hpc, &QComboBox::currentTextChanged, [=](QString val) {
    if (val == "TACC - UT Austin - Frontera") {
      numGPUs->setText("4");
      modelsPerGPU->setText("3");
      hpcCardBrand->setText("NVIDIA");
      hpcCardName->setText("NVIDIA Quadro RTX 5000");
      hpcCardArchitecture->setText("Turing");
      hpcCardComputeCapability->setText("75");
      hpcCardGlobalMemory->setText("16");
    } else if (val == "TACC - UT Austin - Lonestar6") {
      numGPUs->setText("4");
      modelsPerGPU->setText("3");
      hpcCardBrand->setText("NVIDIA");
      hpcCardName->setText("NVIDIA A100");
      hpcCardArchitecture->setText("Ampere");
      hpcCardComputeCapability->setText("80");
      hpcCardGlobalMemory->setText("40");
    } else if (val == "TACC - UT Austin - Stampede3") {
      // TODO: Make this for Stampeed3 and not Lonestar6
      numGPUs->setText("4");
      modelsPerGPU->setText("3");
      hpcCardBrand->setText("NVIDIA");
      hpcCardName->setText("Intel Max");
      hpcCardArchitecture->setText("Ponte Vecchio");
      hpcCardComputeCapability->setText("80");
      hpcCardGlobalMemory->setText("80");
    } else if (val == "Hyak - UW Seattle - Klone") {
      // Note: Multiple partitions on this machine
      numGPUs->setText("2");
      modelsPerGPU->setText("3");
      hpcCardBrand->setText("NVIDIA");
      hpcCardName->setText("NVIDIA RTX 2080ti");
      hpcCardArchitecture->setText("Turing");
      hpcCardComputeCapability->setText("75");
      hpcCardGlobalMemory->setText("12");
    } else if (val == "ACCESS - TAMU - ACES") {
      // Note: There is a 2 GPU and 4 GPU partition on this machine, assume 2 GPU needed
      numGPUs->setText("2");
      modelsPerGPU->setText("3");
      hpcCardBrand->setText("NVIDIA");
      hpcCardName->setText("NVIDIA H100 PCIe");
      hpcCardArchitecture->setText("Hopper");
      hpcCardComputeCapability->setText("90");
      hpcCardGlobalMemory->setText("80");
    } else if (val == "ACCESS - TAMU - FASTER") {
      // TODO: Make this for FASTER and not ACES
      numGPUs->setText("2");
      modelsPerGPU->setText("3");
      hpcCardBrand->setText("NVIDIA");
      hpcCardName->setText("NVIDIA V100");
      hpcCardArchitecture->setText("Tesla");
      hpcCardComputeCapability->setText("70");
      hpcCardGlobalMemory->setText("80");
    } 
    else if ((val == "Your Computer") || (val == "Custom")) {
      numGPUs->setText("1"); // Assume 1 GPU on user's computer
      modelsPerGPU->setText("2"); // Assume just 2 models fit on user's GPU
      hpcCardName->setText("Enter GPU Name"); 
      hpcCardBrand->setText("Enter Brand");   
      hpcCardArchitecture->setText("Enter Architecture");
      hpcCardComputeCapability->setText("Enter Compute Capability (XY)");
      hpcCardGlobalMemory->setText("Enter Global Memory");
      }
  });


  //  simSettings->setMaximumWidth(300);  
  layout->addWidget(simSettings,0,0);
  layout->addWidget(scalingSettings,1,0);  
  layout->addWidget(gpuSettings,2,0);  
  layout->setRowStretch(3,1);
  // layout->setColumnStretch(1,1);
  hpc->setCurrentIndex(1); // Start with "TACC - UT Austin - Lonestar6", as it is more powerful than Frontera in double-precision
  hpc->setCurrentIndex(0); // For now, Default to "TACC - UT Austin - Frontera" for now, as Tapis apps are already made for Frontera over Lonestar6
}

SettingsMPM::~SettingsMPM()
{

}

bool
SettingsMPM::outputToJSON(QJsonObject &jsonObject)
{
  QJsonObject settingsObject;

  settingsObject["cfl"] = cflNumber->text().toDouble(); // Check not negative or zero

  QJsonArray gravityArray;
  gravityArray.append(gravityX->text().toDouble()); 
  gravityArray.append(gravityY->text().toDouble());
  gravityArray.append(gravityZ->text().toDouble());
  settingsObject["gravity"] = gravityArray; 

  QJsonArray domainArray;
  domainArray.append(domainSizeX->text().toDouble());
  domainArray.append(domainSizeY->text().toDouble());
  domainArray.append(domainSizeZ->text().toDouble());
  settingsObject["domain"] = domainArray; // Check not inverted, not zero volume, not too big relative to grid cell size and compiled ClaymoreUW limits

  settingsObject["default_dx"] = gridCellSize->text().toDouble(); // Check not negative or zero

  QJsonArray mirrorArray;
  mirrorArray.append(mirrorDomainX->isChecked() ? QJsonValue(true).toBool() : QJsonValue(false).toBool());
  mirrorArray.append(mirrorDomainY->isChecked() ? QJsonValue(true).toBool() : QJsonValue(false).toBool());
  mirrorArray.append(mirrorDomainZ->isChecked() ? QJsonValue(true).toBool() : QJsonValue(false).toBool());
  settingsObject["mirror_domain"] = mirrorArray; // TODO: Fully implement this in ClaymoreUW

  // Time settings
  settingsObject["initial_time"] = initialTime->text().toDouble(); // future schema
  settingsObject["time"] = initialTime->text().toDouble(); // Current schema in ClaymoreUW, TODO: update to initial_time
  settingsObject["duration"] = duration->text().toDouble(); // Check not negative or zero, TODO: Remove ClaymoreUW's dependence on "frames" and "fps" to determine "duration" implicitly (artifact from computer graphics)
  settingsObject["default_dt"] = timeStep->text().toDouble(); // Check not negative or zero
  // settingsObject["frames"] = static_cast<int>(framesPerSecond->text().toInt() * duration->text().toDouble()); // TODO: Move to outputs
  settingsObject["time_integration"] = QJsonValue(timeIntegration->currentText()).toString();
  // settingsObject["fps"] = framesPerSecond->text().toInt(); // TODO: NOT YET INITIALIZED, also, Move to outputs

  // // TODO: Move to a separate "scaling" object, or "similitude"
  // // TODO: Remove dependency on "froude" and "cauchy" for "time_ratio", "length_ratio", etc., they should be handled by the UI and not the backend if we intend to extrapolate to hold many more scaling laws (e.g., Reynolds, Weber, etc.)
  settingsObject["use_froude_scaling"] = froudeScaling->isChecked() ? QJsonValue(true).toBool() : QJsonValue(false).toBool(); 
  settingsObject["froude_scaling"] = froudeLengthRatio->text().toDouble(); // Note inconsistent naming, TODO: update to "froude_length_ratio" in ClaymoreUW
  settingsObject["froude_time_ratio"] = froudeTimeRatio->text().toDouble();
  settingsObject["use_cauchy_scaling"] = cauchyScaling->isChecked() ? QJsonValue(true).toBool() : QJsonValue(false).toBool();
  settingsObject["cauchy_bulk_ratio"] = cauchyBulkRatio->text().toDouble();

  // // For future use, not in ClaymoreUW yet as a separate "scaling" object
  QJsonObject scalingObject;
  scalingObject["use_froude_scaling"] = froudeScaling->isChecked() ? QJsonValue(true).toBool() : QJsonValue(false).toBool();
  scalingObject["froude_length_ratio"] = froudeLengthRatio->text().toDouble();
  scalingObject["froude_time_ratio"] = froudeTimeRatio->text().toDouble();
  scalingObject["use_cauchy_scaling"] = cauchyScaling->isChecked() ? QJsonValue(true).toBool() : QJsonValue(false).toBool();
  scalingObject["cauchy_bulk_ratio"] = cauchyBulkRatio->text().toDouble();
  jsonObject["scaling"] = scalingObject;

  // // For future use, not in ClaymoreUW yet as a separate "computer" object
  QJsonObject computerObject;
  computerObject["num_gpus"] = numGPUs->text().toInt();
  computerObject["models_per_gpu"] = modelsPerGPU->text().toInt();
  computerObject["hpc_card_name"] = hpcCardName->text();
  computerObject["hpc_card_architecture"] = hpcCardArchitecture->text();
  computerObject["hpc_card_global_memory"] = hpcCardGlobalMemory->text().toInt();
  computerObject["hpc_card_compute_capability"] = hpcCardComputeCapability->text().toInt();
  computerObject["hpc_card_brand"] = hpcCardBrand->text();
  computerObject["hpc"] = QJsonValue(hpc->currentText()).toString();
  jsonObject["computer"] = computerObject;

  jsonObject["simulation"] = settingsObject;



  // domainSizeX->outputToJSON(jsonObject);
  // domainSizeY->outputToJSON(jsonObject);
  // domainSizeZ->outputToJSON(jsonObject);
  // gridCellSize->outputToJSON(jsonObject);
  // mirrorDomainX->outputToJSON(jsonObject);
  // mirrorDomainY->outputToJSON(jsonObject);
  // mirrorDomainZ->outputToJSON(jsonObject);

  // timeStep->outputToJSON(jsonObject);
  // timeIntegration->outputToJSON(jsonObject);
  // initialTime->outputToJSON(jsonObject);
  // duration->outputToJSON(jsonObject);

  // cflNumber->outputToJSON(jsonObject);
  // gravityX->outputToJSON(jsonObject);
  // gravityY->outputToJSON(jsonObject);
  // gravityZ->outputToJSON(jsonObject);

  // froudeScaling->outputToJSON(jsonObject);
  // froudeLengthRatio->outputToJSON(jsonObject);
  // froudeTimeRatio->outputToJSON(jsonObject);
  // cauchyScaling->outputToJSON(jsonObject);
  // cauchyBulkRatio->outputToJSON(jsonObject);

  // numGPUs->outputToJSON(jsonObject);
  // modelsPerGPU->outputToJSON(jsonObject);  
  // hpcCardName->outputToJSON(jsonObject);
  // hpcCardArchitecture->outputToJSON(jsonObject);
  // hpcCardGlobalMemory->outputToJSON(jsonObject);
  // hpcCardComputeCapability->outputToJSON(jsonObject);
  // hpcCardBrand->outputToJSON(jsonObject);
  // hpc->outputToJSON(jsonObject);
  return true;
}

bool
SettingsMPM::inputFromJSON(QJsonObject &jsonObject)
{
  domainSizeX->inputFromJSON(jsonObject);
  domainSizeY->inputFromJSON(jsonObject);
  domainSizeZ->inputFromJSON(jsonObject);
  gridCellSize->inputFromJSON(jsonObject);
  mirrorDomainX->inputFromJSON(jsonObject);
  mirrorDomainY->inputFromJSON(jsonObject);
  mirrorDomainZ->inputFromJSON(jsonObject);

  timeStep->inputFromJSON(jsonObject);
  timeIntegration->inputFromJSON(jsonObject);
  initialTime->inputFromJSON(jsonObject);
  duration->inputFromJSON(jsonObject);

  cflNumber->inputFromJSON(jsonObject);
  gravityX->inputFromJSON(jsonObject);
  gravityY->inputFromJSON(jsonObject);
  gravityZ->inputFromJSON(jsonObject);

  froudeScaling->inputFromJSON(jsonObject);
  froudeLengthRatio->inputFromJSON(jsonObject);
  froudeTimeRatio->inputFromJSON(jsonObject);
  cauchyScaling->inputFromJSON(jsonObject);
  cauchyBulkRatio->inputFromJSON(jsonObject);

  numGPUs->inputFromJSON(jsonObject);
  modelsPerGPU->inputFromJSON(jsonObject);
  hpcCardName->inputFromJSON(jsonObject);
  hpcCardArchitecture->inputFromJSON(jsonObject);
  hpcCardGlobalMemory->inputFromJSON(jsonObject);
  hpcCardComputeCapability->inputFromJSON(jsonObject);
  hpcCardBrand->inputFromJSON(jsonObject);
  hpc->inputFromJSON(jsonObject);
  return true;
}


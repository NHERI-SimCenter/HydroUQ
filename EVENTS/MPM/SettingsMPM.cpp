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

// #include <SimCenterWidget.h>
#include <SettingsMPM.h>
#include <SimCenterAppWidget.h>

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

#include <cmath>

SettingsMPM::SettingsMPM(QWidget *parent)
  :SimCenterWidget(parent)
{
  int numRow = 0;
  QGridLayout *layout = new QGridLayout();
  this->setLayout(layout);
  QGroupBox *simSettings = new QGroupBox("Simulation");
  QGridLayout *simSettingsLayout = new QGridLayout();  
  simSettings->setLayout(simSettingsLayout);

  int maxWidth = 1280; 

  // -----------------------
  numRow = 0;

  QGroupBox *ambientBox = new QGroupBox("Ambient");
  QGridLayout *ambientBoxLayout = new QGridLayout();
  ambientBox->setLayout(ambientBoxLayout);  

  cflNumber = new SC_DoubleLineEdit("cfl", 0.5);
  ambientBoxLayout->addWidget(new QLabel("CFL Number"), numRow, 0, 1, 1, Qt::AlignRight);
  ambientBoxLayout->addWidget(cflNumber, numRow, 1, 1, 3);
  ambientBoxLayout->itemAt(ambientBoxLayout->count()-1)->widget()->setMaximumWidth(maxWidth);
  ambientBoxLayout->addWidget(new QLabel(""), numRow++, 4, 1, 1);
  for (int i=0; i<3; ++i) ambientBoxLayout->itemAt(ambientBoxLayout->count()-(i+1))->widget()->setToolTip("Courant-Friedrichs-Lewy Number, Time-Step <= CFL * Grid-Cell-Size / P-Wave-Velocity. Controls simulation stability. CFL = 0.3 to 0.5 is a good range.");
  // ambientBoxLayout->setColumnStretch(numRow,3);
  // ambientBoxLayout->itemAt(ambientBoxLayout->count()-1)->widget()->setToolTip("Courant-Friedrichs-Lewy Number, Time-Step <= CFL * Grid-Cell-Size / P-Wave-Velocity. Controls simulation stability. CFL = 0.3 to 0.5 is a good range.");


  // temperature = new SC_DoubleLineEdit("temperature", 0.5);
  // ambientBoxLayout->addWidget(new QLabel("Temperature"), numRow, 0);
  // ambientBoxLayout->itemAt(ambientBoxLayout->count()-1)->setAlignment(Qt::AlignRight);
  // ambientBoxLayout->itemAt(ambientBoxLayout->count()-1)->widget()->setToolTip("Base-line temperature of the domain. Areas occupied by some type of material can have a different temperature.");
  // ambientBoxLayout->addWidget(temperature, numRow, 1); 
  // ambientBoxLayout->addWidget(new QLabel("deg. C"), numRow++, 2);

  gravityX = new SC_DoubleLineEdit("gravityX", 0.0);
  gravityY = new SC_DoubleLineEdit("gravityY", -9.80665);
  gravityZ = new SC_DoubleLineEdit("gravityZ", 0.0);
  ambientBoxLayout->addWidget(new QLabel("Gravity (X,Y,Z)"), numRow, 0, 1, 1, Qt::AlignRight);
  ambientBoxLayout->addWidget(gravityX, numRow, 1, 1, 1);  
  ambientBoxLayout->addWidget(gravityY, numRow, 2, 1, 1);  
  ambientBoxLayout->addWidget(gravityZ, numRow, 3, 1, 1);  
  ambientBoxLayout->addWidget(new QLabel("m/s^2"), numRow++, 4, 1, 1);

  // ambientBoxLayout->setRowStretch(numRow,1);
  // ambientBoxLayout->setColumnStretch(5,1);
  simSettingsLayout->addWidget(ambientBox, 0, 0, 2, 5);
  
  // -----------------------
  numRow = 0;  

  QGroupBox *dimensionsBox = new QGroupBox("Spatial");
  QGridLayout *dimensionsBoxLayout = new QGridLayout();
  dimensionsBox->setLayout(dimensionsBoxLayout);  

  gridCellSize = new SC_DoubleLineEdit("default_dx", 0.10);
  dimensionsBoxLayout->addWidget(new QLabel("Grid Cell Size (dx)"), numRow, 0, 1, 1, Qt::AlignRight);
  dimensionsBoxLayout->addWidget(gridCellSize, numRow, 1, 1, 3);
  dimensionsBoxLayout->itemAt(dimensionsBoxLayout->count()-1)->widget()->setMaximumWidth(maxWidth); 
  dimensionsBoxLayout->addWidget(new QLabel("m"), numRow++, 4, 1, 1);
  for (int i=0; i<3; ++i) dimensionsBoxLayout->itemAt(dimensionsBoxLayout->count()-(i+1))->widget()->setToolTip("Size of the Cartesian grid's cells. Assumed to be cubes, so volume is dx^3. Smaller values provide more accurate results, but require more computer memory, O(dx^3), and smaller time-steps, O(dx^-1).");

  domainSizeX = new SC_DoubleLineEdit("domain_X", 90);
  domainSizeY = new SC_DoubleLineEdit("domain_Y", 4.5);
  domainSizeZ = new SC_DoubleLineEdit("domain_Z", 3.6);  
  dimensionsBoxLayout->addWidget(new QLabel("Full Domain (X,Y,Z)"), numRow, 0, 1, 1, Qt::AlignRight);  
  dimensionsBoxLayout->addWidget(domainSizeX, numRow, 1, 1, 1);
  dimensionsBoxLayout->addWidget(domainSizeY, numRow, 2, 1, 1);
  dimensionsBoxLayout->addWidget(domainSizeZ, numRow, 3, 1, 1);
  dimensionsBoxLayout->addWidget(new QLabel("m"), numRow++, 4, 1, 1);

  mirrorDomainX = new SC_CheckBox("mirrorDomainX",false);
  mirrorDomainY = new SC_CheckBox("mirrorDomainY",false);
  mirrorDomainZ = new SC_CheckBox("mirrorDomainZ",false);
  mirrorDomainX->setEnabled(false);
  mirrorDomainY->setEnabled(false);
  mirrorDomainZ->setEnabled(false);
  dimensionsBoxLayout->addWidget(new QLabel("Mirror On YZ-XZ-XY"), numRow, 0, 1, 1, Qt::AlignRight);
  dimensionsBoxLayout->addWidget(mirrorDomainX, numRow, 1, 1, 1);  
  dimensionsBoxLayout->itemAt(dimensionsBoxLayout->count()-1)->setAlignment(Qt::AlignCenter);
  dimensionsBoxLayout->addWidget(mirrorDomainY, numRow, 2, 1, 1);  
  dimensionsBoxLayout->itemAt(dimensionsBoxLayout->count()-1)->setAlignment(Qt::AlignCenter);
  dimensionsBoxLayout->addWidget(mirrorDomainZ, numRow, 3, 1, 1);  
  dimensionsBoxLayout->itemAt(dimensionsBoxLayout->count()-1)->setAlignment(Qt::AlignCenter);
  dimensionsBoxLayout->addWidget(new QLabel(""), numRow++, 4, 1, 1);
  // dimensionsBoxLayout->setRowStretch(numRow,1);
  // dimensionsBoxLayout->setColumnStretch(5,1);

  simSettingsLayout->addWidget(dimensionsBox, 3, 0, 3, 5);


  // -----------------------
  QGroupBox *timeBox = new QGroupBox("Temporal");
  QGridLayout *timeBoxLayout = new QGridLayout();
  timeBox->setLayout(timeBoxLayout);  

  numRow = 0;

  timeStep = new SC_DoubleLineEdit("default_dt", 1e-4);
  timeBoxLayout->addWidget(new QLabel("Max Time Step (dt)"), numRow, 0, 1, 1, Qt::AlignRight);
  timeBoxLayout->addWidget(timeStep, numRow, 1, 1, 3);
  timeBoxLayout->setColumnStretch(1, 1); // Add this line to make the middle column expand
  timeBoxLayout->itemAt(timeBoxLayout->count()-1)->widget()->setMaximumWidth(maxWidth);
  timeBoxLayout->addWidget(new QLabel("sec."), numRow++, 4, 1, 1);

  QStringList timeIntegrationList ; timeIntegrationList <<  "Explicit"; //<< "Semi-Implicit (Symplectic Euler)";
  timeIntegration = new SC_ComboBox("time_integration", timeIntegrationList);    
  timeBoxLayout->addWidget(new QLabel("Time-Integration"), numRow, 0, 1, 1, Qt::AlignRight);
  timeBoxLayout->addWidget(timeIntegration, numRow, 1, 1, 3);
  timeBoxLayout->itemAt(timeBoxLayout->count()-1)->widget()->setMaximumWidth(maxWidth);
  timeBoxLayout->itemAt(timeBoxLayout->count()-1)->widget()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  timeBoxLayout->addWidget(new QLabel(""), numRow++, 4, 1, 1);


  initialTime = new SC_DoubleLineEdit("initial_time", 0.0);
  timeBoxLayout->addWidget(new QLabel("Initial Time (t0)"), numRow, 0, 1, 1, Qt::AlignRight);
  timeBoxLayout->addWidget(initialTime, numRow, 1, 1, 3);  
  timeBoxLayout->itemAt(timeBoxLayout->count()-1)->widget()->setMaximumWidth(maxWidth);
  timeBoxLayout->addWidget(new QLabel("sec."), numRow++, 4, 1, 1);

  duration = new SC_DoubleLineEdit("duration", 5.0);
  timeBoxLayout->addWidget(new QLabel("Duration (tf-t0)"), numRow, 0, 1, 1, Qt::AlignRight);
  timeBoxLayout->addWidget(duration, numRow, 1, 1, 3);  
  timeBoxLayout->itemAt(timeBoxLayout->count()-1)->widget()->setMaximumWidth(maxWidth);
  timeBoxLayout->addWidget(new QLabel("sec."), numRow++, 4, 1, 1);
  // -----------------------
  simSettingsLayout->addWidget(timeBox, 6, 0, 4, 5);
  

  // -----------------------
  QGroupBox *scalingSettings = new QGroupBox("Scaling Laws");
  QGridLayout *scalingSettingsLayout = new QGridLayout();  
  scalingSettings->setLayout(scalingSettingsLayout);

  numRow = 0;

  // "Froude", "Cauchy", "Reynolds", "Weber", "Mach", "Strouhal", "Peclet", "Prandtl", "Nusselt", "Sherwood", "Grashof", "Rayleigh", "Eotvos", "Bond", "Capillary", "Ohnesorge", "Morton", "Froude", "Cauchy", "Reynolds", "Weber", "Mach", "Strouhal", "Peclet", "Prandtl", "Nusselt", "Sherwood", "Grashof", "Rayleigh", "Eotvos", "Bond", "Capillary", "Ohnesorge", "Morton"
  SC_ComboBox* similitudePriority = new SC_ComboBox("similitudePriority", {"", "Froude", "Cauchy"});
  scalingSettingsLayout->addWidget(new QLabel("Dominant Law"), numRow, 0, 1, 1, Qt::AlignRight);
  scalingSettingsLayout->addWidget(similitudePriority, numRow++, 1, 1, 3);
  scalingSettingsLayout->setColumnStretch(1, 1); // Add this line to make the middle column expand
  scalingSettingsLayout->itemAt(scalingSettingsLayout->count()-1)->widget()->setMaximumWidth(maxWidth);

  froudeScaling = new SC_CheckBox("use_froude_scaling",false);
  scalingSettingsLayout->addWidget(new QLabel("Apply Froude?"), numRow, 0, 1, 1, Qt::AlignRight);
  scalingSettingsLayout->addWidget(froudeScaling, numRow++, 1, 1, 1);  

  froudeLengthRatio = new SC_DoubleLineEdit("froude_scaling",1.0); // froude_length_ratio
  scalingSettingsLayout->addWidget(new QLabel("Length Ratio"), numRow, 0, 1, 1, Qt::AlignRight);
  scalingSettingsLayout->addWidget(froudeLengthRatio, numRow, 1, 1, 3);  
  scalingSettingsLayout->itemAt(scalingSettingsLayout->count()-1)->widget()->setMaximumWidth(maxWidth);
  scalingSettingsLayout->addWidget(new QLabel("m/m"), numRow++, 4, 1, 1);
  
  froudeTimeRatio = new SC_DoubleLineEdit("froude_time_ratio",1.0);
  scalingSettingsLayout->addWidget(new QLabel("Time Ratio"), numRow, 0, 1, 1, Qt::AlignRight);
  scalingSettingsLayout->addWidget(froudeTimeRatio, numRow, 1, 1, 3);  
  scalingSettingsLayout->itemAt(scalingSettingsLayout->count()-1)->widget()->setMaximumWidth(maxWidth);
  scalingSettingsLayout->addWidget(new QLabel("s/s"), numRow++, 4, 1, 1);
  
  cauchyScaling = new SC_CheckBox("use_cauchy_scaling",false);
  scalingSettingsLayout->addWidget(new QLabel("Apply Cauchy?"), numRow, 0, 1, 1, Qt::AlignRight);
  scalingSettingsLayout->addWidget(cauchyScaling, numRow++, 1, 1, 1);  

  cauchyBulkRatio = new SC_DoubleLineEdit("cauchy_bulk_ratio",1.0);
  scalingSettingsLayout->addWidget(new QLabel("Elasticity Ratio"), numRow, 0, 1, 1, Qt::AlignRight);
  scalingSettingsLayout->addWidget(cauchyBulkRatio, numRow, 1, 1, 3);  
  scalingSettingsLayout->itemAt(scalingSettingsLayout->count()-1)->widget()->setMaximumWidth(maxWidth);
  scalingSettingsLayout->addWidget(new QLabel("Pa/Pa"), numRow++, 4, 1, 1);
  for (int i=0; i<3; ++i) scalingSettingsLayout->itemAt(scalingSettingsLayout->count()-(i+1))->widget()->setStyleSheet("QLineEdit:disabled { background-color: #e0e0e0; }");

  // Make disabled double line edits have a gray background
  froudeLengthRatio->setStyleSheet("QLineEdit:disabled { background-color: #e0e0e0; }");
  froudeTimeRatio->setStyleSheet("QLineEdit:disabled { background-color: #e0e0e0; }");
  
  froudeScaling->setChecked(false); // Default to off
  cauchyScaling->setChecked(false); // Default to off
  // If editable widget disabled, disable qlabel widgets before and after it
  for (int i=-1; i<2; ++i) scalingSettingsLayout->itemAt(scalingSettingsLayout->indexOf(froudeLengthRatio)-i)->widget()->setEnabled(froudeScaling->isChecked());
  for (int i=-1; i<2; ++i) scalingSettingsLayout->itemAt(scalingSettingsLayout->indexOf(froudeTimeRatio)-i)->widget()->setEnabled(froudeScaling->isChecked());
  for (int i=-1; i<2; ++i) scalingSettingsLayout->itemAt(scalingSettingsLayout->indexOf(cauchyBulkRatio)-i)->widget()->setEnabled(cauchyScaling->isChecked());

  // Make lambda that holds the internals of the connect function, so that it can be called from multiple places
  auto updateFroudeLengthRatio = [=]() {
    if (froudeLengthRatio->text().toDouble() <= 0.0) froudeLengthRatio->setText("1.0");
    if (similitudePriority->currentText() == "Froude") {
      cauchyBulkRatio->setText(QString::number(sqrt(froudeLengthRatio->text().toDouble())));
    } else if (similitudePriority->currentText() == "Cauchy") {
      froudeLengthRatio->setText(QString::number(cauchyBulkRatio->text().toDouble() * cauchyBulkRatio->text().toDouble()));
    }
    froudeTimeRatio->setText(QString::number(sqrt(froudeLengthRatio->text().toDouble())));
  };

  auto updateFroudeTimeRatio = [=]() {
    if (froudeTimeRatio->text().toDouble() <= 0.0) froudeTimeRatio->setText("1.0");
    if (similitudePriority->currentText() == "Froude") {
      cauchyBulkRatio->setText(QString::number(froudeTimeRatio->text().toDouble()));
    } else if (similitudePriority->currentText() == "Cauchy") {
      froudeTimeRatio->setText(QString::number(cauchyBulkRatio->text().toDouble()));
    } 
    froudeLengthRatio->setText(QString::number(froudeTimeRatio->text().toDouble() * froudeTimeRatio->text().toDouble()));
  };

  auto updateCauchyBulkRatio = [=]() {
    if (cauchyBulkRatio->text().toDouble() <= 0.0) cauchyBulkRatio->setText("1.0");
    if (similitudePriority->currentText() == "Froude") {
      cauchyBulkRatio->setText(QString::number(sqrt(froudeLengthRatio->text().toDouble())));
    } else if (similitudePriority->currentText() == "Cauchy") {
      froudeLengthRatio->setText(QString::number(cauchyBulkRatio->text().toDouble() * cauchyBulkRatio->text().toDouble()));
      froudeTimeRatio->setText(QString::number(cauchyBulkRatio->text().toDouble()));
    } 
  };

  connect(froudeScaling, &QCheckBox::toggled, [=](bool checked) {
    // Find qlabel widget before and after froudeLengthRatio, and set their background color to gray if froudeLengthRatio is disabled
    for (int i=-1; i<2; ++i) scalingSettingsLayout->itemAt(scalingSettingsLayout->indexOf(froudeLengthRatio)-i)->widget()->setEnabled(checked);
    for (int i=-1; i<2; ++i) scalingSettingsLayout->itemAt(scalingSettingsLayout->indexOf(froudeTimeRatio)-i)->widget()->setEnabled(checked);
    if (froudeLengthRatio->text().toDouble() <= 0.0) froudeLengthRatio->setText("1.0");
    updateFroudeLengthRatio();
  });

  connect(cauchyScaling, &QCheckBox::toggled, [=](bool checked) {
    for (int i=-1; i<2; ++i) scalingSettingsLayout->itemAt(scalingSettingsLayout->indexOf(cauchyBulkRatio)-i)->widget()->setEnabled(checked);
    if (cauchyBulkRatio->text().toDouble() <= 0.0) cauchyBulkRatio->setText("1.0");
    updateCauchyBulkRatio();
  });

  connect(similitudePriority, &QComboBox::currentTextChanged, updateFroudeLengthRatio);
  connect(froudeLengthRatio, &QLineEdit::editingFinished, updateFroudeLengthRatio);
  connect(froudeTimeRatio, &QLineEdit::editingFinished, updateFroudeTimeRatio);
  connect(cauchyBulkRatio, &QLineEdit::editingFinished, updateCauchyBulkRatio);


  // -----------------------
  QGroupBox *gpuSettings = new QGroupBox("Computer");
  QGridLayout *gpuSettingsLayout = new QGridLayout();
  gpuSettings->setLayout(gpuSettingsLayout);

  numRow = 0;

  QStringList hpcList; hpcList  << "TACC - UT Austin - Lonestar6" << "TACC - UT Austin - Frontera" << "TACC - UT Austin - Stampede3" << "Hyak - UW Seattle - Klone" << "ACCESS - TAMU - ACES" << "Your Computer" ;
  hpc = new SC_ComboBox("hpcSubType", hpcList);
  gpuSettingsLayout->addWidget(new QLabel("Computing Facility"), numRow, 0, 1, 1, Qt::AlignRight);
  gpuSettingsLayout->addWidget(hpc,numRow++,1, 1, 3);
  gpuSettingsLayout->itemAt(gpuSettingsLayout->count()-1)->widget()->setMaximumWidth(maxWidth);
  gpuSettingsLayout->setColumnStretch(1, 1); // Add this line to make the middle column expand

  hpcQueue = new SC_StringLineEdit("hpcQueue", "gpu-a100");
  gpuSettingsLayout->addWidget(new QLabel("Queue"), numRow, 0, 1, 1, Qt::AlignRight);
  gpuSettingsLayout->addWidget(hpcQueue, numRow++, 1, 1, 3);
  gpuSettingsLayout->itemAt(gpuSettingsLayout->count()-1)->widget()->setMaximumWidth(maxWidth);


  numGPUs = new SC_IntLineEdit("num_gpus", 3);  
  gpuSettingsLayout->addWidget(new QLabel("Max Number of GPUs"), numRow, 0, 1, 1, Qt::AlignRight);
  gpuSettingsLayout->addWidget(numGPUs, numRow++, 1, 1, 3);
  gpuSettingsLayout->itemAt(gpuSettingsLayout->count()-1)->widget()->setMaximumWidth(maxWidth);

  modelsPerGPU = new SC_IntLineEdit("models_per_gpu", 3);
  gpuSettingsLayout->addWidget(new QLabel("Max Bodies Per GPU"), numRow, 0, 1, 1, Qt::AlignRight);
  gpuSettingsLayout->addWidget(modelsPerGPU, numRow++, 1, 1, 3);  
  gpuSettingsLayout->itemAt(gpuSettingsLayout->count()-1)->widget()->setMaximumWidth(maxWidth);

  hpcCardBrand = new SC_StringLineEdit("hpc_card_brand", "NVIDIA");
  gpuSettingsLayout->addWidget(new QLabel("GPU Brand"), numRow, 0, 1, 1, Qt::AlignRight);
  gpuSettingsLayout->addWidget(hpcCardBrand, numRow, 1, 1, 3); 
  gpuSettingsLayout->itemAt(gpuSettingsLayout->count()-1)->widget()->setMaximumWidth(maxWidth);
  gpuSettingsLayout->addWidget(new QLabel(""), numRow++, 4, 1, 1);

  hpcCardName = new SC_StringLineEdit("hpc_card_name","A100");
  gpuSettingsLayout->addWidget(new QLabel("GPU Name"), numRow, 0, 1, 1, Qt::AlignRight);
  gpuSettingsLayout->addWidget(hpcCardName, numRow++, 1, 1, 3); 
  gpuSettingsLayout->itemAt(gpuSettingsLayout->count()-1)->widget()->setMaximumWidth(maxWidth);

  hpcCardArchitecture = new SC_StringLineEdit("hpc_card_architecture", "Ampere");
  gpuSettingsLayout->addWidget(new QLabel("GPU Architecture"), numRow, 0, 1, 1, Qt::AlignRight);
  gpuSettingsLayout->addWidget(hpcCardArchitecture, numRow++, 1, 1, 3); 
  gpuSettingsLayout->itemAt(gpuSettingsLayout->count()-1)->widget()->setMaximumWidth(maxWidth);

  hpcCardGlobalMemory = new SC_IntLineEdit("hpc_card_global_memory", 40);
  gpuSettingsLayout->addWidget(new QLabel("GPU Global Memory"), numRow, 0, 1, 1, Qt::AlignRight);
  gpuSettingsLayout->addWidget(hpcCardGlobalMemory, numRow, 1, 1, 3); 
  gpuSettingsLayout->itemAt(gpuSettingsLayout->count()-1)->widget()->setMaximumWidth(maxWidth);
  gpuSettingsLayout->addWidget(new QLabel("GB"), numRow++, 4, 1, 1);
  
  hpcCardComputeCapability = new SC_IntLineEdit("hpc_card_compute_capability", 80);
  gpuSettingsLayout->addWidget(new QLabel("GPU Compute Capability"), numRow, 0, 1, 1, Qt::AlignRight);
  gpuSettingsLayout->addWidget(hpcCardComputeCapability, numRow, 1, 1, 3); 
  gpuSettingsLayout->itemAt(gpuSettingsLayout->count()-1)->widget()->setMaximumWidth(maxWidth);
  gpuSettingsLayout->addWidget(new QLabel("arch_{XY}"), numRow++, 4, 1, 1);


  // HPC System Presets
  connect(hpc, &QComboBox::currentTextChanged, [=](QString val) {
    if (val == "TACC - UT Austin - Frontera") {
      hpcQueue->setText("rtx");
      numGPUs->setText("4");
      modelsPerGPU->setText("3");
      hpcCardBrand->setText("NVIDIA");
      hpcCardName->setText("Quadro RTX 5000");
      hpcCardArchitecture->setText("Turing");
      hpcCardComputeCapability->setText("75");
      hpcCardGlobalMemory->setText("16");
    } else if (val == "TACC - UT Austin - Lonestar6") {
      hpcQueue->setText("gpu-a100"); //gpu-a100-small, gpu-a100-dev, gpu-h100
      numGPUs->setText("3");
      modelsPerGPU->setText("3");
      hpcCardBrand->setText("NVIDIA");
      hpcCardName->setText("A100");
      hpcCardArchitecture->setText("Ampere");
      hpcCardComputeCapability->setText("80");
      hpcCardGlobalMemory->setText("40");
    } else if (val == "TACC - UT Austin - Stampede3") {
      // TODO: Make this for Stampeed3 and not Lonestar6
      hpcQueue->setText("");
      numGPUs->setText("4");
      modelsPerGPU->setText("3");
      hpcCardBrand->setText("Intel");
      hpcCardName->setText("Max");
      hpcCardArchitecture->setText("Ponte Vecchio");
      hpcCardComputeCapability->setText("80");
      hpcCardGlobalMemory->setText("80");
    } else if (val == "Hyak - UW Seattle - Klone") {
      // Note: Multiple partitions on this machine
      hpcQueue->setText("");
      numGPUs->setText("2");
      modelsPerGPU->setText("3");
      hpcCardBrand->setText("NVIDIA");
      hpcCardName->setText("RTX 2080ti");
      hpcCardArchitecture->setText("Turing");
      hpcCardComputeCapability->setText("75");
      hpcCardGlobalMemory->setText("12");
    } else if (val == "ACCESS - TAMU - ACES") {
      // Note: There is a 2 GPU and 4 GPU partition on this machine, assume 2 GPU needed
      hpcQueue->setText("gpu-h100");
      numGPUs->setText("2");
      modelsPerGPU->setText("3");
      hpcCardBrand->setText("NVIDIA");
      hpcCardName->setText("H100");
      hpcCardArchitecture->setText("Hopper");
      hpcCardComputeCapability->setText("90");
      hpcCardGlobalMemory->setText("80");
    } else if (val == "ACCESS - TAMU - FASTER") {
      // TODO: Make this for FASTER and not ACES
      hpcQueue->setText("");
      numGPUs->setText("2");
      modelsPerGPU->setText("3");
      hpcCardBrand->setText("NVIDIA");
      hpcCardName->setText("V100");
      hpcCardArchitecture->setText("Tesla");
      hpcCardComputeCapability->setText("70");
      hpcCardGlobalMemory->setText("32");
    } 
    else if ((val == "Your Computer") || (val == "Custom")) {
      numGPUs->setText("1"); // Assume 1 GPU on user's computer
      modelsPerGPU->setText("2"); // Assume just 2 models fit on user's GPU
      hpcCardName->setText(""); 
      hpcCardBrand->setText("");   
      hpcCardArchitecture->setText("");
      hpcCardComputeCapability->setText("");
      hpcCardGlobalMemory->setText("");
      }
  });

  connect(numGPUs, &QLineEdit::editingFinished, [=]() {
    if (numGPUs->text().toInt() <= 0) numGPUs->setText("1");
  });

  connect(modelsPerGPU, &QLineEdit::editingFinished, [=]() {
    if (modelsPerGPU->text().toInt() <= 0) modelsPerGPU->setText("1");
  });

  //  simSettings->setMaximumWidth(300);  
  layout->addWidget(simSettings);
  layout->addWidget(scalingSettings);  
  layout->addWidget(gpuSettings);  
  layout->setRowStretch(3,1);
  hpc->setCurrentIndex(1); // Start with "TACC - UT Austin - Lonestar6", as it is more powerful than Frontera in double-precision
  hpc->setCurrentIndex(0); // For now, Default to "TACC - UT Austin - Frontera" for now, as Tapis apps are already made for Frontera over Lonestar6

  // So user doesn't change HPC specs
  numGPUs->setEnabled(false);
  modelsPerGPU->setEnabled(false);
  hpcQueue->setEnabled(false);
  hpcCardName->setEnabled(false);
  hpcCardBrand->setEnabled(false);
  hpcCardArchitecture->setEnabled(false);
  hpcCardComputeCapability->setEnabled(false);
  hpcCardGlobalMemory->setEnabled(false);
  
}

SettingsMPM::~SettingsMPM()
{

}

void SettingsMPM::clear(void) {
  cflNumber->clear();
  gravityX->clear();
  gravityY->clear();
  gravityZ->clear();
  gridCellSize->clear();
  domainSizeX->clear();
  domainSizeY->clear();
  domainSizeZ->clear();
  mirrorDomainX->setChecked(false);
  mirrorDomainY->setChecked(false);
  mirrorDomainZ->setChecked(false);
  timeStep->clear();
  timeIntegration->setCurrentIndex(0);
  initialTime->clear();
  duration->clear();
  froudeScaling->setChecked(false);
  froudeLengthRatio->clear();
  froudeTimeRatio->clear();
  cauchyScaling->setChecked(false);
  cauchyBulkRatio->clear();
  numGPUs->clear();
  modelsPerGPU->clear();
  hpcQueue->clear();
  hpcCardName->clear();
  hpcCardArchitecture->clear();
  hpcCardGlobalMemory->clear();
  hpcCardComputeCapability->clear();
  hpcCardBrand->clear();
  hpc->setCurrentIndex(0);
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

  // // For future use, not in ClaymoreUW yet as a separate "computer" object
  QJsonObject computerObject;
  computerObject["num_gpus"] = numGPUs->text().toInt();
  computerObject["models_per_gpu"] = modelsPerGPU->text().toInt();
  computerObject["hpc_queue"] = hpcQueue->text();
  computerObject["hpc_card_name"] = hpcCardName->text();
  computerObject["hpc_card_architecture"] = hpcCardArchitecture->text();
  computerObject["hpc_card_global_memory"] = hpcCardGlobalMemory->text().toInt();
  computerObject["hpc_card_compute_capability"] = hpcCardComputeCapability->text().toInt();
  computerObject["hpc_card_brand"] = hpcCardBrand->text();
  computerObject["hpc"] = QJsonValue(hpc->currentText()).toString();

  jsonObject["simulation"] = settingsObject;
  jsonObject["scaling"] = scalingObject;
  jsonObject["computer"] = computerObject;

  return true;
}

bool
SettingsMPM::inputFromJSON(QJsonObject &jsonObject)
{
  QJsonObject settingsObject = jsonObject["simulation"].toObject();
  QJsonObject scalingObject = jsonObject["scaling"].toObject();
  QJsonObject computerObject = jsonObject["computer"].toObject();

  QJsonArray domainArray = settingsObject["domain"].toArray();
  domainSizeX->setText(QString::number(domainArray[0].toDouble()));
  domainSizeY->setText(QString::number(domainArray[1].toDouble()));
  domainSizeZ->setText(QString::number(domainArray[2].toDouble()));
  
  QJsonArray mirrorArray = settingsObject["mirror_domain"].toArray();
  mirrorDomainX->setChecked(mirrorArray[0].toBool());
  mirrorDomainY->setChecked(mirrorArray[1].toBool());
  mirrorDomainZ->setChecked(mirrorArray[2].toBool());
  
  gridCellSize->inputFromJSON(settingsObject);

  initialTime->inputFromJSON(settingsObject);
  duration->inputFromJSON(settingsObject);
  timeStep->inputFromJSON(settingsObject);
  framesPerSecond->inputFromJSON(settingsObject);
  cflNumber->inputFromJSON(settingsObject);
  timeIntegration->inputFromJSON(settingsObject);

  QJsonArray gravityArray = settingsObject["gravity"].toArray();
  gravityX->setText(QString::number(gravityArray[0].toDouble()));
  gravityY->setText(QString::number(gravityArray[1].toDouble()));
  gravityZ->setText(QString::number(gravityArray[2].toDouble()));

  froudeScaling->inputFromJSON(scalingObject);
  cauchyScaling->inputFromJSON(scalingObject);
  froudeLengthRatio->inputFromJSON(scalingObject);
  froudeTimeRatio->inputFromJSON(scalingObject);
  cauchyBulkRatio->inputFromJSON(scalingObject);

  hpc->inputFromJSON(computerObject);
  hpcQueue->inputFromJSON(computerObject);
  hpcCardBrand->inputFromJSON(computerObject);
  hpcCardName->inputFromJSON(computerObject);
  hpcCardArchitecture->inputFromJSON(computerObject);
  hpcCardGlobalMemory->inputFromJSON(computerObject);
  hpcCardComputeCapability->inputFromJSON(computerObject);
  numGPUs->inputFromJSON(computerObject);
  modelsPerGPU->inputFromJSON(computerObject);
  return true;
}

bool
SettingsMPM::copyFiles(QString& destDir)
{
  Q_UNUSED(destDir);
  return true;
}


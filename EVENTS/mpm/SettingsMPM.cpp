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



SettingsMPM::SettingsMPM(QWidget *parent)
  :SimCenterWidget(parent)
{
  QGridLayout *layout = new QGridLayout();
  this->setLayout(layout);

  QGroupBox *simSettings = new QGroupBox("Simulation Settings");
  QGridLayout *simSettingsLayout = new QGridLayout();  
  simSettings->setLayout(simSettingsLayout);

  QStringList yesNo; yesNo << "Yes" << "No";  

  QGroupBox *dimensionsBox = new QGroupBox("Domain Dimensions");
  QGridLayout *dimensionsBoxLayout = new QGridLayout();
  dimensionsBox->setLayout(dimensionsBoxLayout);  

  int numRow = 0;  
  domainSizeX = new SC_DoubleLineEdit("domainSizeX", 90);
  dimensionsBoxLayout->addWidget(new QLabel("Length (X)"), numRow, 0);  
  dimensionsBoxLayout->addWidget(domainSizeX, numRow, 1);
  dimensionsBoxLayout->addWidget(new QLabel("m"), numRow++, 2);
  
  domainSizeY = new SC_DoubleLineEdit("domainSizeY", 2.9);
  dimensionsBoxLayout->addWidget(new QLabel("Width (Y)"), numRow, 0);    
  dimensionsBoxLayout->addWidget(domainSizeY, numRow, 1);
  dimensionsBoxLayout->addWidget(new QLabel("m"), numRow++, 2);

  domainSizeZ = new SC_DoubleLineEdit("domainSizeZ", 3.65);  
  dimensionsBoxLayout->addWidget(new QLabel("Height (Z)"), numRow, 0);      
  dimensionsBoxLayout->addWidget(domainSizeZ, numRow, 1);
  dimensionsBoxLayout->addWidget(new QLabel("m"), numRow++, 2);

  simSettingsLayout->addWidget(dimensionsBox, 0, 0, 3, 3);

  numRow = 4;
  gridCellSize = new SC_DoubleLineEdit("gridCellSize", 0.05);
  simSettingsLayout->addWidget(new QLabel("Grid Cell Size"), numRow, 0);
  simSettingsLayout->addWidget(gridCellSize,numRow,1);
  simSettingsLayout->addWidget(new QLabel("m"), numRow++, 2);
  
  gridCellSize = new SC_DoubleLineEdit("gridCellSize",0.05);  
  simSettingsLayout->addWidget(new QLabel("Grid Cell Size"), numRow, 0);
  simSettingsLayout->addWidget(gridCellSize,numRow,1);
  simSettingsLayout->addWidget(new QLabel("m"), numRow++, 2);
  
  timeStep = new SC_DoubleLineEdit("SolutionDT", 1e-5);
  simSettingsLayout->addWidget(new QLabel("Max Time Step"), numRow, 0);
  simSettingsLayout->addWidget(timeStep, numRow, 1);
  simSettingsLayout->addWidget(new QLabel("sec."), numRow++, 2);

  duration = new SC_DoubleLineEdit("duration",25.0);
  simSettingsLayout->addWidget(new QLabel("Duration"), numRow, 0);
  simSettingsLayout->addWidget(duration,numRow, 1);  
  simSettingsLayout->addWidget(new QLabel("sec."), numRow++, 2);

  initialTime = new SC_DoubleLineEdit("initialTime",0.0);
  simSettingsLayout->addWidget(new QLabel("Initial Time"), numRow, 0);
  simSettingsLayout->addWidget(initialTime,numRow, 1);  
  simSettingsLayout->addWidget(new QLabel("sec."), numRow++, 2);
  
  framesPerSecond = new SC_IntLineEdit("framesPerSecond", 20);
  simSettingsLayout->addWidget(new QLabel("Frames Per Second"), numRow, 0);
  simSettingsLayout->addWidget(framesPerSecond, numRow, 1);  
  simSettingsLayout->addWidget(new QLabel("sec."), numRow++, 2);
  
  mirrorDomain = new SC_CheckBox("mirrorDomain",false);
  simSettingsLayout->addWidget(new QLabel("Mirror Domain"), numRow, 0);
  simSettingsLayout->addWidget(mirrorDomain, numRow++, 1);  

  gravity = new SC_DoubleLineEdit("gravity",-9.91);
  simSettingsLayout->addWidget(new QLabel("Gravity"), numRow, 0);
  simSettingsLayout->addWidget(framesPerSecond, numRow, 1);  
  simSettingsLayout->addWidget(new QLabel("m/sec.^2"), numRow++, 2);
  
  lengthRatio = new SC_DoubleLineEdit("lengthRatio",1.0);
  simSettingsLayout->addWidget(new QLabel("Froude Scaling (Length Ratio)"), numRow, 0);
  simSettingsLayout->addWidget(lengthRatio, numRow, 1);  
  simSettingsLayout->addWidget(new QLabel("m/m"), numRow++, 2);
  
  froudeScaling = new SC_CheckBox("froudeScaling",false);
  simSettingsLayout->addWidget(new QLabel("Apply Froude Scaling"), numRow, 0);
  simSettingsLayout->addWidget(froudeScaling, numRow++, 1);  
  
  
  QGroupBox *gpuSettings = new QGroupBox("GPU Settings");
  QGridLayout *gpuSettingsLayout = new QGridLayout();
  gpuSettings->setLayout(gpuSettingsLayout);

  numRow = 0;

  numGPUs = new SC_IntLineEdit("numGPUs", 3);  
  gpuSettingsLayout->addWidget(new QLabel("Number of GPUs"), numRow, 0);
  gpuSettingsLayout->addWidget(numGPUs, numRow++, 1);

  materialModelsPerGPU = new SC_IntLineEdit("matModelsPerGPU",3);
  gpuSettingsLayout->addWidget(new QLabel("Max Material Models Per GPU"), numRow, 0);
  gpuSettingsLayout->addWidget(materialModelsPerGPU, numRow++, 1);  

  // gravZ = new SC_DoubleLineEdit("g", -9.81);

  //  simSettings->setMaximumWidth(300);  
  layout->addWidget(simSettings,0,0);
  layout->addWidget(gpuSettings,1,0);  
}

SettingsMPM::~SettingsMPM()
{

}

bool
SettingsMPM::outputToJSON(QJsonObject &jsonObject)
{
  gridCellSize->outputToJSON(jsonObject);
  timeStep->outputToJSON(jsonObject);
  duration->outputToJSON(jsonObject);
  initialTime->outputToJSON(jsonObject);
  framesPerSecond->outputToJSON(jsonObject);
  mirrorDomain->outputToJSON(jsonObject);
  gravity->outputToJSON(jsonObject);
  lengthRatio->outputToJSON(jsonObject);
  froudeScaling->outputToJSON(jsonObject);

  numGPUs->outputToJSON(jsonObject);
  materialModelsPerGPU->outputToJSON(jsonObject);  
  return true;
}

bool
SettingsMPM::inputFromJSON(QJsonObject &jsonObject)
{
  gridCellSize->inputFromJSON(jsonObject);
  timeStep->inputFromJSON(jsonObject);
  duration->inputFromJSON(jsonObject);
  initialTime->inputFromJSON(jsonObject);
  framesPerSecond->inputFromJSON(jsonObject);
  mirrorDomain->inputFromJSON(jsonObject);
  gravity->inputFromJSON(jsonObject);
  lengthRatio->inputFromJSON(jsonObject);
  froudeScaling->inputFromJSON(jsonObject);

  numGPUs->inputFromJSON(jsonObject);
  materialModelsPerGPU->inputFromJSON(jsonObject);
  
  return true;
}


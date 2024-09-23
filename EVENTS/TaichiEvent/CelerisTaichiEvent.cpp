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

#include <CelerisTaichiEvent.h>
#include <QLabel>
#include <QString>
#include <QGridLayout>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <SC_FileEdit.h>
#include <SimCenterPreferences.h>

CelerisTaichiEvent::CelerisTaichiEvent(QWidget *parent)
  :SimCenterWidget(parent)
{
  QString defaultWorkflowFilename = "CelerisTaichiEvent.py";
  QString defaultSimulationFilename = "setrun.py";
  QString defaultConfigurationFilename = "config.json";
  QString defaultBathymetryFilename = "test_curve.xyz";
  QString defaultWaveFilename = "irrWaves.txt";
  QString defaultSensorFilename = "euler.py";
  QString sourceDir = "celeris";
  QString defaultWorkflowScript = pyScriptsPath() + QDir::separator() + defaultWorkflowFilename;
  QString defaultSimulationScript = pyScriptsPath() + QDir::separator() + defaultSimulationFilename;
  QString defaultConfigurationFile = pyScriptsPath() + QDir::separator() + defaultConfigurationFilename;
  QString defaultBathymetryFile = pyScriptsPath() + QDir::separator() + defaultBathymetryFilename;
  QString defaultWaveFile = pyScriptsPath() + QDir::separator() + defaultWaveFilename;
  QString defaultSensorFile = pyScriptsPath() + QDir::separator() + defaultSensorFilename;

  theCelerisPyScript = new SC_FileEdit("basicPyScript");
  theSimulationScript = new SC_FileEdit("interfaceSurface");
  theConfigurationFile = new SC_FileEdit("configFile");
  theBathymetryFile = new SC_FileEdit("bathymetryFile");
  theWaveFile = new SC_FileEdit("waveFile");
  theSensorScript = new SC_FileEdit("sensorPyScript");
  theCelerisPyScript->setToolTip("Workflow backend script (*.py) which launches the CelerisTaichiEvent simulation script. Handles the inputs and outputs for coupling Celeris Taichi Lang to the SimCenter workflow.");
  theSensorScript->setToolTip("Simulation script (*.py) which defines the CelerisTaichiEvent numerical simulation program. This script is launched from the workflow backend script in the SimCenter workflow.");
  theConfigurationFile->setToolTip("Configuration file (*.json) which defines the CelerisTaichiEvent simulation parameters.");
  theBathymetryFile->setToolTip("Bathymetry file (*.xyz) which defines the CelerisTaichiEvent bathymetry.");
  theWaveFile->setToolTip("Wave input file (*.txt) which defines the CelerisTaichiEvent wave input.");
  theSensorScript->setToolTip("Sensor script (*.py) which defines the CelerisTaichiEvent sensor output.");

  theCelerisPyScript->setFilename(defaultWorkflowScript);
  theSimulationScript->setFilename(defaultSimulationScript);
  theConfigurationFile->setFilename(defaultConfigurationFile);
  theBathymetryFile->setFilename(defaultBathymetryFile);
  theWaveFile->setFilename(defaultWaveFile);
  theSensorScript->setFilename(defaultSensorFile);

  QGridLayout *theLayout = new QGridLayout();
  theLayout->addWidget(new QLabel("Workflow Backend Script (*.py)"),0,0);
  theLayout->addWidget(theCelerisPyScript, 0,1);
  theLayout->addWidget(new QLabel("Celeris Simulation Script (*.py)"),1,0);
  theLayout->addWidget(theSimulationScript, 1,1);
  theLayout->addWidget(new QLabel("Celeris Configuration File (*.json)"),2,0);
  theLayout->addWidget(theConfigurationFile, 2,1);
  theLayout->addWidget(new QLabel("Celeris Bathymetry File (*.xyz)"),3,0);
  theLayout->addWidget(theBathymetryFile, 3,1);
  theLayout->addWidget(new QLabel("Celeris Wave Input File (*.txt)"),4,0);
  theLayout->addWidget(theWaveFile, 4,1);
  theLayout->addWidget(new QLabel("Celeris Sensor Script (*.py)"),5,0);
  theLayout->addWidget(theSensorScript, 5,1);
  theLayout->setRowStretch(6,1);
  this->setLayout(theLayout);
}

CelerisTaichiEvent::~CelerisTaichiEvent()
{

}

bool
CelerisTaichiEvent::outputToJSON(QJsonObject &jsonObject)
{
  theCelerisPyScript->outputToJSON(jsonObject);
  theSimulationScript->outputToJSON(jsonObject);
  theConfigurationFile->outputToJSON(jsonObject);
  theBathymetryFile->outputToJSON(jsonObject);
  theWaveFile->outputToJSON(jsonObject);
  theSensorScript->outputToJSON(jsonObject);
  return true;
}

bool
CelerisTaichiEvent::inputFromJSON(QJsonObject &jsonObject)
{
  theCelerisPyScript->inputFromJSON(jsonObject);
  theSimulationScript->inputFromJSON(jsonObject);
  theConfigurationFile->inputFromJSON(jsonObject);
  theBathymetryFile->inputFromJSON(jsonObject);
  theWaveFile->inputFromJSON(jsonObject);
  theSensorScript->inputFromJSON(jsonObject);
  return true;
}

QString CelerisTaichiEvent::pyScriptsPath()
{
    QString backendAppDir = SimCenterPreferences::getInstance()->getAppDir() + QDir::separator()
             + QString("applications") + QDir::separator() + QString("createEVENT") + QDir::separator()
             + QString("CelerisTaichiEvent");
    return backendAppDir;
}

bool
CelerisTaichiEvent::copyFiles(QString &destDir)
{
  QString defaultWorkflowFilename = "CelerisTaichiEvent.py";
  QString defaultSimulationFilename = "setrun.py";
  QString defaultConfigurationFilename = "config.json";
  QString defaultBathymetryFilename = "test_curve.xyz";
  QString defaultWaveFilename = "irrWaves.txt";
  QString defaultSensorFilename = "euler.py";
  QString sourceDir = "celeris";
  QString defaultWorkflowScript = pyScriptsPath() + QDir::separator() + defaultWorkflowFilename;
  QString defaultSimulationScript = pyScriptsPath() + QDir::separator() + defaultSimulationFilename;
  QString defaultConfigurationFile = pyScriptsPath() + QDir::separator() + defaultConfigurationFilename;
  QString defaultBathymetryFile = pyScriptsPath() + QDir::separator() + defaultBathymetryFilename;
  QString defaultWaveFile = pyScriptsPath() + QDir::separator() + defaultWaveFilename;
  QString defaultSensorFile = pyScriptsPath() + QDir::separator() + defaultSensorFilename;
  if (theCelerisPyScript->copyFile(destDir) != true) {
    theCelerisPyScript->setFilename(defaultWorkflowScript);
    if (theCelerisPyScript->copyFile(destDir) != true) {
      return false;
    }
  }
  if (theSimulationScript->copyFile(destDir) != true) {
    theSimulationScript->setFilename(defaultSimulationScript);
    if (theSimulationScript->copyFile(destDir) != true) {
      return false;
    }
  }
  if (theConfigurationFile->copyFile(destDir) != true) {
    theConfigurationFile->setFilename(defaultConfigurationFile);
    if (theConfigurationFile->copyFile(destDir) != true) {
      return false;
    }
  }
  if (theBathymetryFile->copyFile(destDir) != true) {
    theBathymetryFile->setFilename(defaultBathymetryFile);
    if (theBathymetryFile->copyFile(destDir) != true) {
      return false;
    }
  }
  if (theWaveFile->copyFile(destDir) != true) {
    theWaveFile->setFilename(defaultWaveFile);
    if (theWaveFile->copyFile(destDir) != true) {
      return false;
    }
  }
  if (theSensorScript->copyFile(destDir) != true) {
    theSensorScript->setFilename(defaultSimulationScript);
    if (theSensorScript->copyFile(destDir) != true) {
      return false;
    }
  }
  return true;
}


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

#include <CelerisTaichi.h>
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

CelerisTaichi::CelerisTaichi(QWidget *parent)
  :SimCenterWidget(parent)
{
  QString defaultWorkflowFilename = "Celeris.py";
  QString defaultSimulationFilename = "setrun.py";
  QString defaultConfigurationFilename = "config.json";
  QString defaultBathymetryFilename = "bathy.txt";
  QString defaultWaveFilename = "waves.txt";
  QString defaultSensorFilename = "euler.py";
  QString sourceDir = "celeris";
  QString defaultWorkflowScript = pyScriptsPath() + QDir::separator() + defaultWorkflowFilename;
  QString defaultSimulationScript = pyScriptsPath() + QDir::separator() + defaultSimulationFilename;
  QString defaultConfigurationFile = examplesDirPath() + QDir::separator() + QString("OSU_Seaside") + QDir::separator() + defaultConfigurationFilename;
  QString defaultBathymetryFile = examplesDirPath() + QDir::separator() + QString("OSU_Seaside") + QDir::separator() + defaultBathymetryFilename;
  QString defaultWaveFile = examplesDirPath() + QDir::separator() + QString("OSU_Seaside") + QDir::separator() + defaultWaveFilename;
  QString defaultSensorFile = pyScriptsPath() + QDir::separator() + defaultSensorFilename;

  theCelerisPyScript = new SC_FileEdit("backendScript");
  theSimulationScript = new SC_FileEdit("simulationScript");
  theConfigurationFile = new SC_FileEdit("configFile");
  theBathymetryFile = new SC_FileEdit("bathymetryFile");
  theWaveFile = new SC_FileEdit("waveFile");
  theSensorScript = new SC_FileEdit("sensorPyScript");
  theCelerisPyScript->setToolTip("Workflow backend script (*.py) which launches the Celeris simulation script. Handles the inputs and outputs for coupling Celeris Taichi Lang to the SimCenter workflow.");
  theSensorScript->setToolTip("Simulation script (*.py) which defines the Celeris numerical simulation program. This script is launched from the workflow backend script in the SimCenter workflow.");
  theConfigurationFile->setToolTip("Configuration file (*.json) which defines the Celeris simulation parameters.");
  theBathymetryFile->setToolTip("Bathymetry file (*.xyz, *.txt) which defines the Celeris bathymetry.");
  theWaveFile->setToolTip("Wave input file (*.txt) which defines the Celeris wave input.");
  theSensorScript->setToolTip("Sensor script (*.py) which defines the Celeris sensor output.");

  theCelerisPyScript->setFilename(defaultWorkflowScript);
  theSimulationScript->setFilename(defaultSimulationScript);
  theConfigurationFile->setFilename(defaultConfigurationFile);
  theBathymetryFile->setFilename(defaultBathymetryFile);
  theWaveFile->setFilename(defaultWaveFile);
  theSensorScript->setFilename(defaultSensorFile);

  QGridLayout *theLayout = new QGridLayout();
  theLayout->addWidget(new QLabel("Workflow Backend Script (*.py)"),0,0);
  theLayout->addWidget(theCelerisPyScript, 0,1);
  theLayout->addWidget(new QLabel("Simulation Script (*.py)"),1,0);
  theLayout->addWidget(theSimulationScript, 1,1);
  theLayout->addWidget(new QLabel("Configuration File (*.json)"),2,0);
  theLayout->addWidget(theConfigurationFile, 2,1);
  theLayout->addWidget(new QLabel("Bathymetry File (*.txt, *.xyz)"),3,0);
  theLayout->addWidget(theBathymetryFile, 3,1);
  theLayout->addWidget(new QLabel("Wave Input File (*.txt)"),4,0);
  theLayout->addWidget(theWaveFile, 4,1);
  theLayout->addWidget(new QLabel("Sensor Script (*.py)"),5,0);
  theLayout->addWidget(theSensorScript, 5,1);
  theLayout->setRowStretch(6,1);
  this->setLayout(theLayout);
}

CelerisTaichi::~CelerisTaichi()
{

}

bool
CelerisTaichi::outputToJSON(QJsonObject &jsonObject)
{

  // if (theCelerisPyScript->outputToJSON(jsonObject) == false) {
    // qDebug() << "CelerisTaichi::outputToJSON: failed to output celeris py script";
    // return false;
  // }
  
  if (theSimulationScript->outputToJSON(jsonObject) == false) {
    qDebug() << "CelerisTaichi::outputToJSON: failed to output simulation script";
    // return false;
  }
  
  if (theConfigurationFile->outputToJSON(jsonObject) == false) {
    qDebug() << "CelerisTaichi::outputToJSON: failed to output configuration file";
    // return false;
  }
  
  if (theBathymetryFile->outputToJSON(jsonObject) == false) {
    qDebug() << "CelerisTaichi::outputToJSON: failed to output bathymetry file";
    // return false;
  }
  if (theWaveFile->outputToJSON(jsonObject) == false) {
    qDebug() << "CelerisTaichi::outputToJSON: failed to output wave file";
    // return false;
  }
  if (theSensorScript->outputToJSON(jsonObject) == false) {
    qDebug() << "CelerisTaichi::outputToJSON: failed to output sensor script";
    // return false;
  }
  return true;
}

bool
CelerisTaichi::inputFromJSON(QJsonObject &jsonObject)
{
  theCelerisPyScript->inputFromJSON(jsonObject);
  theSimulationScript->inputFromJSON(jsonObject);
  theConfigurationFile->inputFromJSON(jsonObject);
  theBathymetryFile->inputFromJSON(jsonObject);
  theWaveFile->inputFromJSON(jsonObject);
  theSensorScript->inputFromJSON(jsonObject);
  return true;
}

QString CelerisTaichi::pyScriptsPath()
{
    QString backendAppDir = SimCenterPreferences::getInstance()->getAppDir() + QDir::separator()
             + QString("applications") + QDir::separator() + QString("createEVENT") + QDir::separator()
             + QString("Celeris");
    return backendAppDir;
}

QString CelerisTaichi::examplesDirPath()
{
    QString examplesDir = SimCenterPreferences::getInstance()->getAppDir() + QDir::separator()
             + QString("Examples");
    return examplesDir;
}

bool
CelerisTaichi::copyFiles(QString &destDir)
{
  QString defaultWorkflowFilename = "Celeris.py";
  QString defaultSimulationFilename = "setrun.py";
  QString defaultConfigurationFilename = "config.json";
  QString defaultBathymetryFilename = "bathy.txt";
  QString defaultWaveFilename = "waves.txt";
  QString defaultSensorFilename = "euler.py";
  QString sourceDir = "celeris";
  QString defaultWorkflowScript = pyScriptsPath() + QDir::separator() + defaultWorkflowFilename;
  QString defaultSimulationScript = pyScriptsPath() + QDir::separator() + defaultSimulationFilename;
  QString defaultConfigurationFile = examplesDirPath() + QDir::separator() + QString("OSU_Seaside") + QDir::separator() + defaultConfigurationFilename;
  QString defaultBathymetryFile = examplesDirPath() + QDir::separator() + QString("OSU_Seaside") + QDir::separator() + defaultBathymetryFilename;
  QString defaultWaveFile = examplesDirPath() + QDir::separator() + QString("OSU_Seaside") + QDir::separator() + defaultWaveFilename;
  QString defaultSensorFile = pyScriptsPath() + QDir::separator() + defaultSensorFilename;
  // if (theCelerisPyScript->copyFile(destDir) != true) {
  //   qDebug() << "CelerisTaichi::copyFiles: failed to copy backend workflow script: " << theCelerisPyScript->getFilename();
  //   qDebug() << "CelerisTaichi::copyFiles: try defaultWorkflowScript: " << defaultWorkflowScript;
  //   theCelerisPyScript->setFilename(defaultWorkflowScript);
  //   if (theCelerisPyScript->copyFile(destDir) != true) {
  //     qDebug() << "CelerisTaichi::copyFiles: failed to copy backend workflow script";
  //     // return false;
  //   }
  // }
  if (theSimulationScript->copyFile(destDir) != true) {
    qDebug() << "CelerisTaichi::copyFiles: failed to copy simulation script: " << theSimulationScript->getFilename();
    qDebug() << "CelerisTaichi::copyFiles: try defaultSimulationScript: " << defaultSimulationScript;
    theSimulationScript->setFilename(defaultSimulationScript);
    if (theSimulationScript->copyFile(destDir) != true) {
      qDebug() << "CelerisTaichi::copyFiles: failed to copy simulation script";
      // return false;
    }
  }
  if (theConfigurationFile->copyFile(destDir) != true) {
    qDebug() << "CelerisTaichi::copyFiles: failed to copy configuration file: " << theConfigurationFile->getFilename();
    qDebug() << "CelerisTaichi::copyFiles: try defaultConfigurationFile: " << defaultConfigurationFile;
    theConfigurationFile->setFilename(defaultConfigurationFile);
    if (theConfigurationFile->copyFile(destDir) != true) {
      qDebug() << "CelerisTaichi::copyFiles: failed to copy configuration file";
      // return false;
    }
  }
  if (theBathymetryFile->copyFile(destDir) != true) {
    qDebug() << "CelerisTaichi::copyFiles: failed to copy bathymetry file: " << theBathymetryFile->getFilename();
    qDebug() << "CelerisTaichi::copyFiles: try defaultBathymetryFile: " << defaultBathymetryFile;
    theBathymetryFile->setFilename(defaultBathymetryFile);
    if (theBathymetryFile->copyFile(destDir) != true) {
      qDebug() << "CelerisTaichi::copyFiles: failed to copy bathymetry file";
      // return false;
    }
  }
  if (theWaveFile->copyFile(destDir) != true) {
    qDebug() << "CelerisTaichi::copyFiles: failed to copy wave file: " << theWaveFile->getFilename();
    qDebug() << "CelerisTaichi::copyFiles: try defaultWaveFile: " << defaultWaveFile;
    theWaveFile->setFilename(defaultWaveFile);
    if (theWaveFile->copyFile(destDir) != true) {
      qDebug() << "CelerisTaichi::copyFiles: failed to copy wave file";
      // return false;
    }
  }
  if (theSensorScript->copyFile(destDir) != true) {
    qDebug() << "CelerisTaichi::copyFiles: failed to copy sensor script: " << theSensorScript->getFilename();
    qDebug() << "CelerisTaichi::copyFiles: try defaultSensorFile: " << defaultSensorFile;
    theSensorScript->setFilename(defaultSimulationScript);
    if (theSensorScript->copyFile(destDir) != true) {
      qDebug() << "CelerisTaichi::copyFiles: failed to copy sensor script";
      // return false;
    }
  }
  return true;
}


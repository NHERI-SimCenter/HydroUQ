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

#include <BasicMPMEvent.h>
#include <QLabel>
#include <QString>
#include <QGridLayout>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <SC_FileEdit.h>
#include <SC_IntLineEdit.h>
#include <SimCenterPreferences.h>

BasicMPMEvent::BasicMPMEvent(QWidget *parent)
  :SimCenterWidget(parent)
{
  QString defaultExecutableFilename = "osu_lwf.exe";
  QString defaultWorkflowFilename = "MPMEvent.py";
  QString defaultSimulationFilename = "scene.json";
  QString defaultResourceFilename = "wmdisp_hydro2sec_1200hz_smooth_14032023.csv";
  QString defaultExecutable = SimCenterPreferences::getInstance()->getAppDir() + QDir::separator()
             + QString("applications") + QDir::separator() + QString("ClaymoreUW") + QDir::separator() 
             + defaultExecutableFilename;
  QString defaultWorkflowScript = pyScriptsPath() + QDir::separator() 
             + defaultWorkflowFilename;
  QString defaultSimulationScript =   SimCenterPreferences::getInstance()->getAppDir() + QDir::separator()
             + QString("Examples") + QDir::separator() 
             + QString("hdro-0002") + QDir::separator() 
             + QString("src") + QDir::separator() 
             + defaultSimulationFilename;
  QString defaultResourceFile = SimCenterPreferences::getInstance()->getAppDir() + QDir::separator()
             + QString("Examples") + QDir::separator()
             + QString("WaveMaker") + QDir::separator()
             + defaultResourceFilename;
  int defaultMaxMinutes = 1;

  theBackendApp = new SC_FileEdit("executableFile");
  theBackendScript = new SC_FileEdit("basicPyScript");
  theSimulationScript = new SC_FileEdit("configFile");
  theResourceFile = new SC_FileEdit("resourceFile");
  theMaxMinutes = new SC_IntLineEdit("maxMinutes", defaultMaxMinutes);
  theBackendApp->setToolTip("ClaymoreUW MPM executable file (*, *.exe) which launches the MPMEvent simulation script. This executable is launched from the workflow backend script in the SimCenter workflow.");
  theBackendScript->setToolTip("Workflow backend script (*.py) which launches the MPMEvent simulation script. Handles the inputs and outputs for coupling ClaymoreUW MPM to the SimCenter workflow.");
  theSimulationScript->setToolTip("ClaymoreUW MPM Scene File (*.json) which defines the MPMEvent numerical simulation program. This script is launched from the workflow backend script in the SimCenter workflow.");
  theResourceFile->setToolTip("Resource file (*.csv) which defines the wave maker displacement for the MPMEvent numerical simulation program. This file is used to define the wave maker displacement for the MPMEvent numerical simulation program.");
  theMaxMinutes->setToolTip("Maximum number of minutes to run the MPMEvent numerical simulation program.");
  theBackendApp->setFilename(defaultExecutable);
  theBackendScript->setFilename(defaultWorkflowScript);
  theSimulationScript->setFilename(defaultSimulationScript);
  theResourceFile->setFilename(defaultResourceFile);

  QGridLayout *theLayout = new QGridLayout();
  theLayout->addWidget(new QLabel("ClaymoreUW MPM Executable (*, *.exe)"),0,0);
  theLayout->addWidget(theBackendApp, 0,1);
  theLayout->addWidget(new QLabel("Workflow Backend Script (*.py)"),1,0);
  theLayout->addWidget(theBackendScript, 1,1);
  theLayout->addWidget(new QLabel("ClaymoreUW MPM Scene File (*.json)"),2,0);
  theLayout->addWidget(theSimulationScript, 2,1);
  theLayout->addWidget(new QLabel("Resource File (*.csv)"),3,0);
  theLayout->addWidget(theResourceFile, 3,1);
  theLayout->addWidget(new QLabel("Max Runtime Minutes"),4,0);
  theLayout->addWidget(theMaxMinutes, 4,1);
  theLayout->setRowStretch(5,1);
  this->setLayout(theLayout);
}

BasicMPMEvent::~BasicMPMEvent()
{

}

bool
BasicMPMEvent::outputToJSON(QJsonObject &jsonObject)
{
  theBackendApp->outputToJSON(jsonObject);
  theBackendScript->outputToJSON(jsonObject);
  theSimulationScript->outputToJSON(jsonObject);  
  theResourceFile->outputToJSON(jsonObject);
  theMaxMinutes->outputToJSON(jsonObject);
  return true;
}

bool
BasicMPMEvent::inputFromJSON(QJsonObject &jsonObject)
{
  theBackendApp->inputFromJSON(jsonObject);
  theBackendScript->inputFromJSON(jsonObject);
  theSimulationScript->inputFromJSON(jsonObject);  
  theResourceFile->inputFromJSON(jsonObject);  
  theMaxMinutes->inputFromJSON(jsonObject);
  return true;
}

QString BasicMPMEvent::pyScriptsPath()
{
    QString backendAppDir = SimCenterPreferences::getInstance()->getAppDir() + QDir::separator()
             + QString("applications") + QDir::separator() + QString("createEVENT") + QDir::separator()
             + QString("MPMEvent");
    return backendAppDir;
}

bool
BasicMPMEvent::copyFiles(QString &destDir)
{
  QString defaultExecutableFilename = "osu_lwf.exe";
  QString defaultWorkflowFilename = "MPMEvent.py";
  QString defaultSimulationFilename = "scene.json";
  QString defaultResourceFilename = "wmdisp_hydro2sec_1200hz_smooth_14032023.csv";
  QString defaultExecutable = SimCenterPreferences::getInstance()->getAppDir() + QDir::separator()
             + QString("applications") + QDir::separator() + QString("ClaymoreUW") + QDir::separator() 
             + defaultExecutableFilename;
  QString defaultWorkflowScript = pyScriptsPath() + QDir::separator() 
             + defaultWorkflowFilename;
  QString defaultSimulationScript =   SimCenterPreferences::getInstance()->getAppDir() + QDir::separator()
             + QString("Examples") + QDir::separator() 
             + QString("hdro-0002") + QDir::separator() 
             + QString("src") + QDir::separator() 
             + defaultSimulationFilename;
  QString defaultResourceFile = SimCenterPreferences::getInstance()->getAppDir() + QDir::separator()
             + QString("Examples") + QDir::separator()
             + QString("WaveMaker") + QDir::separator()
             + defaultResourceFilename;
  if (theBackendApp->copyFile(destDir) != true) {
    theBackendApp->setFilename(defaultExecutable);
    if (theBackendApp->copyFile(destDir) != true) {
      return false;
    }
  }
  if (theBackendScript->copyFile(destDir) != true) {
    theBackendScript->setFilename(defaultWorkflowScript);
    if (theBackendScript->copyFile(destDir) != true) {
      return false;
    }
  }
  if (theSimulationScript->copyFile(destDir) != true) {
    theSimulationScript->setFilename(defaultSimulationScript);
    if (theSimulationScript->copyFile(destDir) != true) {
      return false;
    }
  }
  if (theResourceFile->copyFile(destDir) != true) {
    theResourceFile->setFilename(defaultResourceFile);
    if (theResourceFile->copyFile(destDir) != true) {
      return false;
    }
  }
  return true;
}


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

#include <BasicTaichiEvent.h>
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

BasicTaichiEvent::BasicTaichiEvent(QWidget *parent)
  :SimCenterWidget(parent)
{
  QString defaultWorkflowFilename = "TaichiEvent.py";
  QString defaultSimulationFilename = "pbf2d.py";
  QString defaultWorkflowScript = pyScriptsPath() + QDir::separator() + defaultWorkflowFilename;
  QString defaultSimulationScript = pyScriptsPath() + QDir::separator() + defaultSimulationFilename;

  theBasicPyScript = new SC_FileEdit("basicPyScript");
  theSurfaceFile = new SC_FileEdit("interfaceSurface");
  theBasicPyScript->setToolTip("Workflow backend script (*.py) which launches the TaichiEvent simulation script. Handles the inputs and outputs for coupling Taichi Lang to the SimCenter workflow.");
  theSurfaceFile->setToolTip("Simulation script (*.py) which defines the TaichiEvent numerical simulation program. This script is launched from the workflow backend script in the SimCenter workflow.");
  theBasicPyScript->setFilename(defaultWorkflowScript);
  theSurfaceFile->setFilename(defaultSimulationScript);

  QGridLayout *theLayout = new QGridLayout();
  theLayout->addWidget(new QLabel("Workflow Backend Script"),0,0);
  theLayout->addWidget(theBasicPyScript, 0,1);
  theLayout->addWidget(new QLabel("Taichi Lang Simulation Script"),1,0);
  theLayout->addWidget(theSurfaceFile, 1,1);
  theLayout->setRowStretch(2,1);
  this->setLayout(theLayout);
    
}

BasicTaichiEvent::~BasicTaichiEvent()
{

}

bool
BasicTaichiEvent::outputToJSON(QJsonObject &jsonObject)
{
  theBasicPyScript->outputToJSON(jsonObject);
  theSurfaceFile->outputToJSON(jsonObject);  
  return true;
}

bool
BasicTaichiEvent::inputFromJSON(QJsonObject &jsonObject)
{
  theBasicPyScript->inputFromJSON(jsonObject);
  theSurfaceFile->inputFromJSON(jsonObject);    
  return true;
}

QString BasicTaichiEvent::pyScriptsPath()
{
    QString backendAppDir = SimCenterPreferences::getInstance()->getAppDir() + QDir::separator()
             + QString("applications") + QDir::separator() + QString("createEVENT") + QDir::separator()
             + QString("TaichiEvent");
    return backendAppDir;
}

bool
BasicTaichiEvent::copyFiles(QString &destDir)
{
  QString defaultWorkflowFilename = "TaichiEvent.py";
  QString defaultSimulationFilename = "pbf2d.py";
  QString defaultWorkflowScript = pyScriptsPath() + QDir::separator() + defaultWorkflowFilename;
  QString defaultSimulationScript = pyScriptsPath() + QDir::separator() + defaultSimulationFilename;
  if (theBasicPyScript->copyFile(destDir) != true) {
    theBasicPyScript->setFilename(defaultWorkflowScript);
    if (theBasicPyScript->copyFile(destDir) != true) {
      return false;
    }
  }
  if (theSurfaceFile->copyFile(destDir) != true) {
    theSurfaceFile->setFilename(defaultSimulationScript);
    if (theSurfaceFile->copyFile(destDir) != true) {
      return false;
    }
  }
  return true;
}


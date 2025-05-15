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
#include <QJsonDocument>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <SC_FileEdit.h>
#include <SC_DoubleLineEdit.h>
#include <SC_IntLineEdit.h>
#include <SimCenterPreferences.h>
#include <QPixmap>
#include <QDebug>
#include <QCoreApplication>
#include <QPushButton>
#include <QProcess>
#include <QStringList>

CelerisTaichi::CelerisTaichi(QWidget *parent)
  :SimCenterWidget(parent)
{
  QString defaultWorkflowFilename = "Celeris.py";
  QString defaultSimulationFilename = "setrun.py";
  QString defaultConfigurationFilename = "config.json";
  QString defaultBathymetryFilename = "bathy.txt";
  QString defaultWaveFilename = "waves.txt";
  QString sourceDir = "celeris";
  QString defaultWorkflowScript = pyScriptsPath() + QDir::separator() + defaultWorkflowFilename;
  QString defaultSimulationScript = pyScriptsPath() + QDir::separator() + defaultSimulationFilename;
  QString defaultConfigurationFile = examplesDirPath() + QDir::separator() + QString("hdro-0020/src") + QDir::separator() + defaultConfigurationFilename;
  QString defaultBathymetryFile = examplesDirPath() + QDir::separator() + QString("hdro-0020/src") + QDir::separator() + defaultBathymetryFilename;
  QString defaultWaveFile = examplesDirPath() + QDir::separator() + QString("hdro-0020/src") + QDir::separator() + defaultWaveFilename;

  theCelerisPyScript = new SC_FileEdit("backendScript");
  theSimulationScript = new SC_FileEdit("simulationScript");
  theConfigurationFile = new SC_FileEdit("configFile");
  theBathymetryFile = new SC_FileEdit("bathymetryFile");
  theWaveFile = new SC_FileEdit("waveFile");
  theCelerisPyScript->setToolTip("Workflow backend script (*.py) which launches the Celeris simulation script. Handles the inputs and outputs for coupling Celeris Taichi Lang to the SimCenter workflow.");
  theConfigurationFile->setToolTip("Configuration file (*.json) which defines the Celeris simulation parameters.");
  theBathymetryFile->setToolTip("Bathymetry file (*.xyz, *.txt) which defines the Celeris bathymetry.");
  theWaveFile->setToolTip("Wave input file (*.txt) which defines the Celeris wave input.");

  theCelerisPyScript->setFilename(defaultWorkflowScript);
  theSimulationScript->setFilename(defaultSimulationScript);
  theConfigurationFile->setFilename(defaultConfigurationFile);
  theBathymetryFile->setFilename(defaultBathymetryFile);
  theWaveFile->setFilename(defaultWaveFile);

  QGridLayout *theLayout = new QGridLayout();
  theLayout->addWidget(new QLabel("Workflow Backend Script (*.py)"),0,0,1,2);
  theLayout->addWidget(theCelerisPyScript, 0,1,1,3);
  theLayout->addWidget(new QLabel("Simulation Script (*.py)"),1,0,1,2);
  theLayout->addWidget(theSimulationScript, 1,1,1,3);
  theLayout->addWidget(new QLabel("Configuration File (*.json)"),2,0,1,2);
  theLayout->addWidget(theConfigurationFile, 2,1,1,3);
  theLayout->addWidget(new QLabel("Bathymetry File (*.txt)"),3,0,1,2);
  theLayout->addWidget(theBathymetryFile, 3,1,1,3);
  theLayout->addWidget(new QLabel("Wave Input File (*.txt)"),4,0,1,2);
  theLayout->addWidget(theWaveFile, 4,1,1,3);
  theForceSensorBeginX = new SC_DoubleLineEdit("force_sensor_begin_x", 668.0);
  theForceSensorBeginY = new SC_DoubleLineEdit("force_sensor_begin_y", 207.0);
  theForceSensorEndX = new SC_DoubleLineEdit("force_sensor_end_x", 668.0);
  theForceSensorEndY = new SC_DoubleLineEdit("force_sensor_end_y", 221.0);
  theLayout->addWidget(new QLabel("Define a line to record forces on. Typically, it is on a structure's perimeter."), 5,0,1,5);
  theLayout->addWidget(new QLabel("Force Sensor Begin (X,Y)"),6,0,1,2);
  theLayout->addWidget(theForceSensorBeginX, 6,1,1,1);
  theLayout->addWidget(theForceSensorBeginY, 6,2,1,1);
  theLayout->addWidget(new QLabel("pixels"),6,3,1,1);
  theLayout->addWidget(new QLabel("Force Sensor End (X,Y)"),7,0,1,2);
  theLayout->addWidget(theForceSensorEndX, 7,1,1,1);
  theLayout->addWidget(theForceSensorEndY, 7,2,1,1);
  theLayout->addWidget(new QLabel("pixels"),7,3,1,1);

  QPushButton *theButton = new QPushButton("Draw Bathymetry");
  theButton->setToolTip("Draw the bathymetry in the image above.");
  theButton->setIcon(QIcon(":/icons/pencil-plus-white.svg"));
  theButton->setIconSize(QSize(24,24));
  theLayout->addWidget(theButton, 8,0,1,5);

  QString bathFilename = QCoreApplication::applicationDirPath() + QDir::separator() + "Examples" + QDir::separator() + "hdro-0020" + QDir::separator() + "src" + QDir::separator() + "bathy.jpg";
  QPixmap *pix = new QPixmap(bathFilename);
  QLabel *theImageLabel = new QLabel();
  theImageLabel->setPixmap(*pix);
  theLayout->addWidget(theImageLabel, 9,0,1,5);

  connect(theButton, &QPushButton::released, this, [=]() {
    
      QString pythonScriptName = QCoreApplication::applicationDirPath() + QDir::separator() + "Examples" + QDir::separator() + "Bathymetry" + QDir::separator() + "celeris_draw_bathy.py";
      QJsonArray forceSensorBeginArray;
      // Append the integer values to the JSON array
      forceSensorBeginArray.append(theForceSensorBeginX->text().toInt());
      forceSensorBeginArray.append(theForceSensorBeginY->text().toInt());
      QJsonArray forceSensorEndArray;
      forceSensorEndArray.append(theForceSensorEndX->text().toInt());
      forceSensorEndArray.append(theForceSensorEndY->text().toInt());

      // QJsonArray bathymetryArrayJSON = boundariesObjectJSON["boundaries"].toArray()[bathymetryID].toObject()["bathymetry"].toArray();
      QJsonDocument forceSensorBeginDoc;
      forceSensorBeginDoc.setArray(forceSensorBeginArray);
      QString forceSensorBeginString = forceSensorBeginDoc.toJson(QJsonDocument::Compact);
      QJsonDocument forceSensorEndDoc;
      forceSensorEndDoc.setArray(forceSensorEndArray);
      QString forceSensorEndString = forceSensorEndDoc.toJson(QJsonDocument::Compact);

      // double extrude_length = boundariesObjectJSON["boundaries"].toArray()[bathymetryID].toObject()["domain_end"].toArray()[2].toDouble() - boundariesObjectJSON["boundaries"].toArray()[bathymetryID].toObject()["domain_start"].toArray()[2].toDouble(); 
      QString inputPath = theBathymetryFile->getFilename();
      QString outputPath = QCoreApplication::applicationDirPath() + QDir::separator() + "Examples" + QDir::separator() + "Bathymetry" + QDir::separator() + "custom_bathy.jpg";
      qDebug() << "Python script: " << pythonScriptName;
      qDebug() << "Bathymetry file: " << inputPath;
      qDebug() << "Force sensor coordinates begin: " << forceSensorBeginString;
      qDebug() << "Force sensor coordinates end: " << forceSensorEndString;
      qDebug() << "Output path: " << outputPath;
      // Launch python script to generate the bathymetry mesh
      QString program = SimCenterPreferences::getInstance()->getPython();
      QStringList args;
      args << pythonScriptName << inputPath << forceSensorBeginString << forceSensorEndString << outputPath;
      QProcess *process = new QProcess();

      // Catch python print statements and errors and display them in through the qDebug() stream.
      QObject::connect(process, &QProcess::readyRead, [process] () {
          QByteArray a = process->readAll();
          qDebug() << a;
      });

      // Delete process instance / thread when done (later), and get the exit status to handle errors.
      QObject::connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                      [=](int exitCode, QProcess::ExitStatus /*exitStatus*/){
          qDebug()<< "process exited with code " << exitCode;
          process->deleteLater();
      });

      process->start(program, args);
      process->waitForStarted();
      process->waitForFinished(-1);
      if (process->exitStatus() == QProcess::CrashExit)
      {
          qDebug() << "MPM::updateBathymetry - The script has crashed.";
      } 
      else if (process->exitStatus() == QProcess::NormalExit)
      {
          qDebug() << "MPM::updateBathymetry - The script has finished running.";
      }
      else 
      {
          qDebug() << "MPM::updateBathymetry - The script has finished running with an unknown exit status.";
      }
    
    
    QString bathyFilename = QCoreApplication::applicationDirPath() + QDir::separator() + "Examples" + QDir::separator() + "Bathymetry" + QDir::separator() + "custom_bathy.jpg";
    QFileInfo fileInfo(bathyFilename);
    if (fileInfo.exists()) {
      qDebug() << "CelerisTaichi::CelerisTaichi: Bathymetry file already exists: " << bathFilename;
    } else {
      qDebug() << "CelerisTaichi::CelerisTaichi: Bathymetry file does not exist: " << bathFilename;
    }
    pix->load(bathyFilename);
    theImageLabel->setPixmap(*pix);
  });
  
  theLayout->setRowStretch(10,1);
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

  // Add contents of config.json to the JSON object
  QString val;
  QFile file;
  file.setFileName(theConfigurationFile->getFilename());
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  val = file.readAll();
  file.close();
  // qWarning() << val;
  QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
  QJsonObject configObj = d.object();

  QJsonArray forceSensorBeginArray;
  QJsonArray forceSensorEndArray;
  forceSensorBeginArray.append(theForceSensorBeginX->text().toInt());
  forceSensorBeginArray.append(theForceSensorBeginY->text().toInt());
  forceSensorEndArray.append(theForceSensorEndX->text().toInt());
  forceSensorEndArray.append(theForceSensorEndY->text().toInt());
  configObj["force_sensor_begin"] = forceSensorBeginArray;
  configObj["force_sensor_end"] = forceSensorEndArray;

  jsonObject["config"] = configObj;

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
  
  QJsonObject configObj;
  if (jsonObject.contains("config")) {
    QJsonValue theValue = jsonObject["config"];
    configObj = theValue.toObject();
  } else {
    qDebug() << "CelerisTaichi::inputFromJSON: no config object in JSON";
    // return false;
  }
  if (configObj.contains("force_sensor_begin")) {
    QJsonValue theValue = configObj["force_sensor_begin"];
    QJsonArray forceSensorBeginArray = theValue.toArray();
    theForceSensorBeginX->setText(QString::number(forceSensorBeginArray[0].toDouble()));
    theForceSensorBeginY->setText(QString::number(forceSensorBeginArray[1].toDouble()));
  } else {
    qDebug() << "CelerisTaichi::inputFromJSON: no force_sensor_begin object in JSON";
    // return false;
  }
  if (configObj.contains("force_sensor_end")) {
    QJsonValue theValue = configObj["force_sensor_end"];
    QJsonArray forceSensorEndArray = theValue.toArray();
    theForceSensorEndX->setText(QString::number(forceSensorEndArray[0].toDouble()));
    theForceSensorEndY->setText(QString::number(forceSensorEndArray[1].toDouble()));
  } else {
    qDebug() << "CelerisTaichi::inputFromJSON: no force_sensor_end object in JSON";
    // return false;
  }


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
  QString sourceDir = "celeris";
  QString defaultWorkflowScript = pyScriptsPath() + QDir::separator() + defaultWorkflowFilename;
  QString defaultSimulationScript = pyScriptsPath() + QDir::separator() + defaultSimulationFilename;
  QString defaultConfigurationFile = examplesDirPath() + QDir::separator() + QString("hdro-0020") + QDir::separator() + QString("src") + QDir::separator() + defaultConfigurationFilename;
  QString defaultBathymetryFile = examplesDirPath() + QDir::separator() + QString("hdro-0020") + QDir::separator() + QString("src") + QDir::separator() + defaultBathymetryFilename;
  QString defaultWaveFile = examplesDirPath() + QDir::separator() + QString("hdro-0020") + QDir::separator() + QString("src") + QDir::separator() + defaultWaveFilename;

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

  return true;
}


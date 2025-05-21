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
#include <SC_TableEdit.h>
#include <SimCenterPreferences.h>
#include <QPixmap>
#include <QDebug>
#include <QCoreApplication>
#include <QPushButton>
#include <QProcess>
#include <QStringList>
#include <QGroupBox>

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

  QGroupBox *theFileGroupBox = new QGroupBox("Input Files");
  QGridLayout *theFileLayout = new QGridLayout();
  theFileGroupBox->setLayout(theFileLayout);

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

  int numRow = 0;
  int numRowFiles = 0;
  QGridLayout *theLayout = new QGridLayout();
  // theFileLayout->addWidget(new QLabel("Workflow Backend Script (*.py)"),numRowFiles,0,1,2);
  // theFileLayout->addWidget(theCelerisPyScript, numRowFiles,2,1,3);
  // numRowFiles++;
  // theFileLayout->addWidget(new QLabel("Simulation Script (*.py)"),numRowFiles,0,1,2);
  // theFileLayout->addWidget(theSimulationScript, numRowFiles,2,1,3);
  // numRowFiles++;
  theFileLayout->addWidget(new QLabel("Configuration File (*.json)"),numRowFiles,0,1,2);
  theFileLayout->addWidget(theConfigurationFile, numRowFiles,2,1,3);
  numRowFiles++;
  theFileLayout->addWidget(new QLabel("Bathymetry File (*.txt)"),numRowFiles,0,1,2);
  theFileLayout->addWidget(theBathymetryFile, numRowFiles,2,1,3);
  numRowFiles++;
  theFileLayout->addWidget(new QLabel("Wave Input File (*.txt)"),numRowFiles,0,1,2);
  theFileLayout->addWidget(theWaveFile, numRowFiles,2,1,3);
  numRowFiles++;

  theLayout->addWidget(theFileGroupBox, numRow,0,1,5);
  numRow++;

  int numRowForces = 0;
  QGroupBox *theForceSensorGroupBox = new QGroupBox("Force Sensor");
  QGridLayout *theForceSensorLayout = new QGridLayout();
  theForceSensorGroupBox->setLayout(theForceSensorLayout);
  theForceSensorBeginX = new SC_DoubleLineEdit("force_sensor_begin_x", 33.4);
  theForceSensorBeginY = new SC_DoubleLineEdit("force_sensor_begin_y", 10.35);
  theForceSensorEndX = new SC_DoubleLineEdit("force_sensor_end_x", 33.4);
  theForceSensorEndY = new SC_DoubleLineEdit("force_sensor_end_y", 11.05);
  theForceSensorLayout->addWidget(new QLabel("Define a line to record forces on. Typically, it is on a structure's perimeter."), numRowForces,0,1,5);
  numRowForces++;
  theForceSensorLayout->addWidget(new QLabel("Force Sensor Begin (X,Y)"),numRowForces,0,1,2);
  theForceSensorLayout->addWidget(theForceSensorBeginX, numRowForces,2,1,1);
  theForceSensorLayout->addWidget(theForceSensorBeginY, numRowForces,3,1,1);
  theForceSensorLayout->addWidget(new QLabel("length unit"),numRowForces,4,1,1);
  numRowForces++;
  theForceSensorLayout->addWidget(new QLabel("Force Sensor End (X,Y)"),numRowForces,0,1,2);
  theForceSensorLayout->addWidget(theForceSensorEndX, numRowForces,2,1,1);
  theForceSensorLayout->addWidget(theForceSensorEndY, numRowForces,3,1,1);
  theForceSensorLayout->addWidget(new QLabel("length unit"),numRowForces,4,1,1);
  numRowForces++;
  theLayout->addWidget(theForceSensorGroupBox, numRow,0,1,5);
  numRow++;

  int numRowVisual = 0;
  QGroupBox *theVisualGroupBox = new QGroupBox("Bathymetry and Sensor Visualization");
  QGridLayout *theVisualLayout = new QGridLayout();
  theVisualGroupBox->setLayout(theVisualLayout);

  // theVisualLayout->addWidget(new QLabel("Ensure (dx, dy) matches the domain tab."), numRowVisual,0,1,5);
  // numRowVisual++;
  theDx = new SC_DoubleLineEdit("dx", 0.05);
  theDy = new SC_DoubleLineEdit("dy", 0.05);
  theVisualLayout->addWidget(new QLabel("Bathymetry grid spacing (dx, dy)"), numRowVisual, 0, 1, 2);
  theVisualLayout->addWidget(theDx, numRowVisual, 2, 1, 1);
  theVisualLayout->addWidget(theDy, numRowVisual, 3, 1, 1);
  theVisualLayout->addWidget(new QLabel("length unit"), numRowVisual, 4, 1, 1);
  numRowVisual++;

  QPushButton *theButton = new QPushButton("Draw Bathymetry");
  theButton->setToolTip("Draw the bathymetry in the image above.");
  theButton->setIcon(QIcon(":/icons/pencil-plus-white.svg"));
  theButton->setIconSize(QSize(24,24));
  theVisualLayout->addWidget(theButton, numRowVisual,0,1,8);
  numRowVisual++;
  QString bathFilename = QCoreApplication::applicationDirPath() + QDir::separator() + "Examples" + QDir::separator() + "hdro-0020" + QDir::separator() + "src" + QDir::separator() + "bathy.jpg";
  QPixmap *pix = new QPixmap(bathFilename);
  QLabel *theImageLabel = new QLabel();
  theImageLabel->setPixmap(*pix);
  theVisualLayout->addWidget(theImageLabel, numRowVisual,0,1,8);
  theLayout->addWidget(theVisualGroupBox, numRow,0,1,5);
  numRow++;

  connect(theButton, &QPushButton::released, this, [=]() {
    
      QString pythonScriptName = QCoreApplication::applicationDirPath() + QDir::separator() + "Examples" + QDir::separator() + "Bathymetry" + QDir::separator() + "celeris_draw_bathy.py";
      QJsonArray forceSensorBeginArray;
      // Append the integer values to the JSON array
      forceSensorBeginArray.append(int(theForceSensorBeginX->text().toDouble() / theDx->text().toDouble()));
      forceSensorBeginArray.append(int(theForceSensorBeginY->text().toDouble() / theDy->text().toDouble()));
      QJsonArray forceSensorEndArray;
      forceSensorEndArray.append(int(theForceSensorEndX->text().toDouble() / theDx->text().toDouble()));
      forceSensorEndArray.append(int(theForceSensorEndY->text().toDouble() / theDy->text().toDouble()));

      // QJsonArray bathymetryArrayJSON = boundariesObjectJSON["boundaries"].toArray()[bathymetryID].toObject()["bathymetry"].toArray();
      QJsonDocument forceSensorBeginDoc;
      forceSensorBeginDoc.setArray(forceSensorBeginArray);
      QString forceSensorBeginString = forceSensorBeginDoc.toJson(QJsonDocument::Compact);
      QJsonDocument forceSensorEndDoc;
      forceSensorEndDoc.setArray(forceSensorEndArray);
      QString forceSensorEndString = forceSensorEndDoc.toJson(QJsonDocument::Compact);
      QJsonDocument waveGaugesDoc;
      QJsonObject waveGaugesObjectTemp;
      QJsonArray waveGaugesArrayTemp;
      theWaveGaugesTable->outputToJSON(waveGaugesObjectTemp);
      QJsonValue theValue = waveGaugesObjectTemp["locationOfTimeSeries"];
      waveGaugesArrayTemp = theValue.toArray();
      waveGaugesDoc.setArray(waveGaugesArrayTemp);
      QString waveGaugesString = waveGaugesDoc.toJson(QJsonDocument::Compact);
      QString dx = theDx->text();
      QString dy = theDy->text();
      // double extrude_length = boundariesObjectJSON["boundaries"].toArray()[bathymetryID].toObject()["domain_end"].toArray()[2].toDouble() - boundariesObjectJSON["boundaries"].toArray()[bathymetryID].toObject()["domain_start"].toArray()[2].toDouble(); 
      QString inputPath = theBathymetryFile->getFilename();
      QString outputPath = QCoreApplication::applicationDirPath() + QDir::separator() + "Examples" + QDir::separator() + "Bathymetry" + QDir::separator() + "custom_bathy.jpg";
      qDebug() << "Python script: " << pythonScriptName;
      qDebug() << "Bathymetry file: " << inputPath;
      qDebug() << "Force sensor coordinates begin: " << forceSensorBeginString;
      qDebug() << "Force sensor coordinates end: " << forceSensorEndString;
      qDebug() << "Wave gauge coordinates: " << waveGaugesString;
      qDebug() << "Grid-spacing dx: " << dx;
      qDebug() << "Grid-spacing dy: " << dy;
      qDebug() << "Output path: " << outputPath;
      // Launch python script to generate the bathymetry mesh
      QString program = SimCenterPreferences::getInstance()->getPython();
      QStringList args;
      args << pythonScriptName << inputPath << forceSensorBeginString << forceSensorEndString << waveGaugesString << dx << dy << outputPath;
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
  
  QStringList theWaveGaugeLocs; theWaveGaugeLocs = QStringList() << "0.0" << "0.5" << "1.0" << "1.5" << "2.0" << "2.5" << "3.0" << "3.5" << "4.0" << "4.5" << "5.0";
  

  QStringList  listWG; listWG << "Origin X" << "Origin Y" ;
  QStringList  dataWG; dataWG << "16.0" << "1.5"
				                      << "34.269" << "1.5"                 
				                      << "38.114" << "1.5" ;
  theWaveGaugesTable = new SC_TableEdit("locationOfTimeSeries",  listWG, 3, dataWG);
  // theLayout->addWidget(new QLabel("Wave Gauge Locations"), 0,5,1,3);
  QGroupBox *theWaveGaugesGroupBox = new QGroupBox("Wave Gauge Locations");
  QGridLayout *theWaveGaugesLayout = new QGridLayout();
  theWaveGaugesGroupBox->setLayout(theWaveGaugesLayout);

  theWaveGaugesLayout->addWidget(theWaveGaugesTable, 0,5,6,4);
  theWaveGaugesLayout->setRowStretch(6,0);
  theLayout->addWidget(theWaveGaugesGroupBox, 0,5,2,4);
  this->setLayout(theLayout);
  // When the config file is change, inputFromJSON is called on the parent
  connect(theConfigurationFile, &SC_FileEdit::fileNameChanged, this, [=](void) {
    // Only emit if the file exists and is readable
    QFileInfo fileInfo(theConfigurationFile->getFilename());
    if (fileInfo.exists() && fileInfo.isReadable()) {
      qDebug() << "CelerisTaichi::CelerisTaichi: Configuration file exists and is readable: " << theConfigurationFile->getFilename();
      emit this->configFileChanged();
    } else {
      qDebug() << "CelerisTaichi::CelerisTaichi: Configuration file does not exist or is not readable: " << theConfigurationFile->getFilename();
    }
  });

}

CelerisTaichi::~CelerisTaichi()
{

}

bool
CelerisTaichi::outputToJSON(QJsonObject &jsonObject)
{

  // if (theCelerisPyScript->outputToJSON(jsonObject) == false) {
  //   qDebug() << "CelerisTaichi::outputToJSON: failed to output celeris py script";
  //   // return false;
  // }

  // if (theSimulationScript->outputToJSON(jsonObject) == false) {
  //   qDebug() << "CelerisTaichi::outputToJSON: failed to output simulation script";
  //   // return false;
  // }
  
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
  forceSensorBeginArray.append(theForceSensorBeginX->text().toDouble());
  forceSensorBeginArray.append(theForceSensorBeginY->text().toDouble());
  forceSensorEndArray.append(theForceSensorEndX->text().toDouble());
  forceSensorEndArray.append(theForceSensorEndY->text().toDouble());
  configObj["force_sensor_begin"] = forceSensorBeginArray;
  configObj["force_sensor_end"] = forceSensorEndArray;
  configObj["dx"] = theDx->text().toDouble();
  configObj["dy"] = theDy->text().toDouble();

  QJsonObject waveGaugesTableObject;
  QJsonArray waveGaugesTableArray;
  theWaveGaugesTable->outputToJSON(waveGaugesTableObject);
  QJsonValue theValue = waveGaugesTableObject["locationOfTimeSeries"];
  waveGaugesTableArray = theValue.toArray();
  int numRows = waveGaugesTableArray.size();
  QJsonArray waveGaugesArray;
  for (int i = 0; i < numRows; ++i) {
    QJsonObject waveGaugeObject;
    waveGaugeObject["xts"] = waveGaugesTableArray[i].toArray()[0].toDouble();
    waveGaugeObject["yts"] = waveGaugesTableArray[i].toArray()[1].toDouble();
    waveGaugesArray.append(waveGaugeObject);
  }

  configObj["locationOfTimeSeries"] = waveGaugesArray;
  configObj["NumberOfTimeSeries"] = numRows;
  jsonObject["config"] = configObj;

  return true;
}

bool
CelerisTaichi::inputFromJSON(QJsonObject &jsonObject)
{
  // theCelerisPyScript->inputFromJSON(jsonObject);
  // theSimulationScript->inputFromJSON(jsonObject);
  // theConfigurationFile->inputFromJSON(jsonObject);
  // theBathymetryFile->inputFromJSON(jsonObject);
  // theWaveFile->inputFromJSON(jsonObject);
  // if (theCelerisPyScript->inputFromJSON(jsonObject) == false) {
  //   qDebug() << "CelerisTaichi::inputFromJSON: failed to input celeris py script";
  //   // return false;
  // }
  // if (theSimulationScript->inputFromJSON(jsonObject) == false) {
  //   qDebug() << "CelerisTaichi::inputFromJSON: failed to input simulation script";
  //   // return false;
  // }
  if (theConfigurationFile->inputFromJSON(jsonObject) == false) {
    qDebug() << "CelerisTaichi::inputFromJSON: failed to input configuration file";
    // return false;
  }
  if (theBathymetryFile->inputFromJSON(jsonObject) == false) {
    qDebug() << "CelerisTaichi::inputFromJSON: failed to input bathymetry file";
    // return false;
  }
  if (theWaveFile->inputFromJSON(jsonObject) == false) {
    qDebug() << "CelerisTaichi::inputFromJSON: failed to input wave file";
    // return false;
  }

  // QString defaultConfigurationFile = examplesDirPath() + QDir::separator() + QString("hdro-0021") + QDir::separator() + ("src") + QDir::separator() + QString("config.json");
  // theConfigurationFile->setFilename(defaultConfigurationFile);
  // QString configFile = jsonObject["configFile"].toString();
  // QString configFilePath = jsonObject["configFilePath"].toString();
  // if (configFilePath.isEmpty() == false) {
  //   configFile = configFilePath + QDir::separator() + configFile;
  // }
  // if (configFile.isEmpty() == false) {
  //   theConfigurationFile->setFilename(configFile);
  // } else {
  //   qDebug() << "CelerisTaichi::inputFromJSON: no config file in JSON";
  //   // return false;
  // }
  
  
  // We read in the 'config.json' file and add it to the main scInput.json JSON on an object called "config" in the Event
  // It will overwrite the existing config object in the JSON file if we are loading an example, e.g., 'input.json'

  // Check if file exists and is readable
  QFileInfo fileInfo(theConfigurationFile->getFilename());
  if (!fileInfo.exists()) {
    qDebug() << "CelerisTaichi::inputFromJSON: Configuration file does not exist: " << theConfigurationFile->getFilename();
    // return false;
  }

  // Check if file is readable
  if (!fileInfo.isReadable()) {
    qDebug() << "CelerisTaichi::inputFromJSON: Configuration file is not readable: " << theConfigurationFile->getFilename();
    // return false;
  }

  QJsonDocument d = QJsonDocument::fromJson(theConfigurationFile->getFilename().toUtf8());
  QJsonObject configObj;
  configObj = d.object();

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

  if (configObj.contains("dx")) {
    QJsonValue theValue = configObj["dx"];
    theDx->setText(QString::number(theValue.toDouble()));
  } else {
    qDebug() << "CelerisTaichi::inputFromJSON: no dx object in JSON";
    // return false;
  }
  if (configObj.contains("dy")) {
    QJsonValue theValue = configObj["dy"];
    theDy->setText(QString::number(theValue.toDouble()));
  } else {
    qDebug() << "CelerisTaichi::inputFromJSON: no dy object in JSON";
    // return false;
  }

  if (configObj.contains("locationOfTimeSeries")) {
    QJsonArray waveGaugesTableArray;
    QJsonObject waveGaugesTableObject;
    QJsonValue theValue = configObj["locationOfTimeSeries"];
    QJsonArray waveGaugesArray = theValue.toArray();
    int numRows = waveGaugesArray.size();
    for (int i = 0; i < numRows; ++i) {
      QJsonObject waveGaugeObject = waveGaugesArray[i].toObject();
      double xts = waveGaugeObject["xts"].toDouble();
      double yts = waveGaugeObject["yts"].toDouble();
      QJsonArray tableRowArray; 
      tableRowArray.append(xts);
      tableRowArray.append(yts);
      waveGaugesTableArray.append(tableRowArray);
    
    }
    waveGaugesTableObject["locationOfTimeSeries"] = waveGaugesTableArray;
    theWaveGaugesTable->inputFromJSON(waveGaugesTableObject);
  } else {
    qDebug() << "CelerisTaichi::inputFromJSON: no locationOfTimeSeries object in JSON";
    // return false;
  }

  return true;
}

bool CelerisTaichi::inputFromConfigJSON(QJsonObject &jsonObject)
{

  QJsonObject configObj;
  if (theConfigurationFile->getFilename().isEmpty()) {
    qDebug() << "CelerisTaichi::inputFromConfigJSON: config file is empty";
    // return false;
  }
  // readable
  QFileInfo fileInfo(theConfigurationFile->getFilename());
  if (!fileInfo.exists()) {
    qDebug() << "CelerisTaichi ::inputFromConfigJSON: Configuration file does not exist: " << theConfigurationFile->getFilename();
    // return false;
  }
  if (!fileInfo.isReadable()) {
    qDebug() << "CelerisTaichi::inputFromConfigJSON: Configuration file is not readable: " << theConfigurationFile->getFilename();
    // return false;
  }
  QFile file(theConfigurationFile->getFilename());
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  QByteArray rawData = file.readAll();
  file.close();
  QJsonDocument doc(QJsonDocument::fromJson(rawData));
  configObj = doc.object();
  foreach(const QString& key, configObj.keys())
  {
    QJsonValue value = configObj.value(key);
    qDebug() << "CelerisTaichi::inputFromConfigJSON: key: " << key << " value: " << value.toString();
  }

  if (configObj.contains("force_sensor_begin")) {
    QJsonValue theValue = configObj["force_sensor_begin"];
    QJsonArray forceSensorBeginArray = theValue.toArray();
    theForceSensorBeginX->setText(QString::number(forceSensorBeginArray[0].toDouble()));
    theForceSensorBeginY->setText(QString::number(forceSensorBeginArray[1].toDouble()));
  } else {
    qDebug() << "CelerisTaichi::inputFromConfigJSON: no force_sensor_begin object in JSON";
    // return false;
  }

  if (configObj.contains("force_sensor_end")) {
    QJsonValue theValue = configObj["force_sensor_end"];
    QJsonArray forceSensorEndArray = theValue.toArray();
    theForceSensorEndX->setText(QString::number(forceSensorEndArray[0].toDouble()));
    theForceSensorEndY->setText(QString::number(forceSensorEndArray[1].toDouble()));
  } else {
    qDebug() << "CelerisTaichi::inputFromConfigJSON: no force_sensor_end object in JSON";
    // return false;
  }
  if (configObj.contains("dx")) {
    QJsonValue theValue = configObj["dx"];
    theDx->setText(QString::number(theValue.toDouble()));
  } else {
    qDebug() << "CelerisTaichi::inputFromConfigJSON: no dx object in JSON";
    // return false;
  }
  if (configObj.contains("dy")) {
    QJsonValue theValue = configObj["dy"];
    theDy->setText(QString::number(theValue.toDouble()));
  } else {
    qDebug() << "CelerisTaichi::inputFromConfigJSON: no dy object in JSON";
    // return false;
  }

  // wave gauges
  if (configObj.contains("locationOfTimeSeries")) {
    QJsonArray waveGaugesTableArray;
    QJsonObject waveGaugesTableObject;
    QJsonValue theValue = configObj["locationOfTimeSeries"];
    QJsonArray waveGaugesArray = theValue.toArray();
    int numRows = waveGaugesArray.size();
    for (int i = 0; i < numRows; ++i) {
      QJsonObject waveGaugeObject = waveGaugesArray[i].toObject();
      double xts = waveGaugeObject["xts"].toDouble();
      double yts = waveGaugeObject["yts"].toDouble();
      QJsonArray tableRowArray; 
      tableRowArray.append(xts);
      tableRowArray.append(yts);
      waveGaugesTableArray.append(tableRowArray);
    
    }
    waveGaugesTableObject["locationOfTimeSeries"] = waveGaugesTableArray;
    theWaveGaugesTable->inputFromJSON(waveGaugesTableObject);
  } else {
    qDebug() << "CelerisTaichi::inputFromConfigJSON: no locationOfTimeSeries object in JSON";
    // return false;
  }
  // Add contents of config.json to the JSON object
  jsonObject["config"] = configObj;
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

  // if (theSimulationScript->copyFile(destDir) != true) {
  //   qDebug() << "CelerisTaichi::copyFiles: failed to copy simulation script: " << theSimulationScript->getFilename();
  //   qDebug() << "CelerisTaichi::copyFiles: try defaultSimulationScript: " << defaultSimulationScript;
  //   theSimulationScript->setFilename(defaultSimulationScript);
  //   if (theSimulationScript->copyFile(destDir) != true) {
  //     qDebug() << "CelerisTaichi::copyFiles: failed to copy simulation script";
  //     // return false;
  //   }
  // }
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


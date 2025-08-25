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
#include <QtMath>
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
#include "RunPythonInThread.h"

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

  theConfigurationFile = new SC_FileEdit("configFile");
  theBathymetryFile = new SC_FileEdit("bathymetryFile");
  theWaveFile = new SC_FileEdit("waveFile");
  // theCelerisPyScript->setToolTip("Workflow backend script (*.py) which launches the Celeris simulation script. Handles the inputs and outputs for coupling Celeris Taichi Lang to the SimCenter workflow.");
  theConfigurationFile->setToolTip("Configuration file (*.json) which defines the Celeris simulation parameters.");
  theBathymetryFile->setToolTip("Bathymetry file (*.xyz, *.txt) which defines the Celeris bathymetry.");
  theWaveFile->setToolTip("Wave input file (*.txt) which defines the Celeris wave input.");

  // theCelerisPyScript->setFilename(defaultWorkflowScript);
  // theSimulationScript->setFilename(defaultSimulationScript);
  theConfigurationFile->setFilename(defaultConfigurationFile);
  theBathymetryFile->setFilename(defaultBathymetryFile);
  theWaveFile->setFilename(defaultWaveFile);

  int numRow = 0;
  int numRowFiles = 0;
  QGridLayout *theLayout = new QGridLayout();

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
  theLatLongFSCheckBox = new QCheckBox("Use Lon/Lat");
  theLatLongFSCheckBox->setChecked(false);
  theLatLongFSCheckBox->setToolTip("Use Lon/Lat coordinates for the force sensor. If unchecked, the coordinates will be in the local coordinate system defined by the bathymetry grid.");
  theForceSensorLayout->addWidget(theLatLongFSCheckBox, numRowForces,0,1,5);
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
  theLatLongPlotCheckBox = new QCheckBox("Use Lon/Lat");
  theLatLongPlotCheckBox->setChecked(false);
  theLatLongPlotCheckBox->setToolTip("Use Lon/Lat coordinates for the visualization.");
  theVisualLayout->addWidget(theLatLongPlotCheckBox, numRowVisual,0,1,5);
  numRowVisual++;
  theDx = new SC_DoubleLineEdit("dx", 0.05);
  theDy = new SC_DoubleLineEdit("dy", 0.05);
  theVisualLayout->addWidget(new QLabel("Bathymetry grid spacing (dx, dy)"), numRowVisual, 0, 1, 2);
  theVisualLayout->addWidget(theDx, numRowVisual, 2, 1, 1);
  theVisualLayout->addWidget(theDy, numRowVisual, 3, 1, 1);
  theVisualLayout->addWidget(new QLabel("length unit"), numRowVisual, 4, 1, 1);
  numRowVisual++;


  theVisualLayout->addWidget(new QLabel("lon_LL"), numRowVisual, 0, 1, 1);
  long1Edit = new SC_DoubleLineEdit("lon_LL", -122.34053007546347);
  long1Edit->setToolTip("Longitude Lower-Left");
  theVisualLayout->addWidget(long1Edit, numRowVisual, 1, 1, 1);
  theVisualLayout->addWidget(new QLabel("lat_LL:"), numRowVisual, 2, 1, 1);
  lat1Edit = new SC_DoubleLineEdit("lat_LL", 37.8992412074125);
  lat1Edit->setToolTip("Latitude Lower-Left");
  theVisualLayout->addWidget(lat1Edit, numRowVisual, 3, 1, 1);
  theVisualLayout->addWidget(new QLabel("lon_UR"), numRowVisual, 4, 1, 1);
  long2Edit = new SC_DoubleLineEdit("lon_UR", -122.32314730065123);
  long2Edit->setToolTip("Longitude Upper-Right");
  theVisualLayout->addWidget(long2Edit, numRowVisual, 5, 1, 1);
  theVisualLayout->addWidget(new QLabel("lat_UR"), numRowVisual, 6, 1, 1);
  lat2Edit = new SC_DoubleLineEdit("lat_UR", 37.91514928711621);
  lat2Edit->setToolTip("Latitude Upper-Right");
  theVisualLayout->addWidget(lat2Edit, numRowVisual, 7, 1, 1);
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

  // lambda

  
    auto drawBathymetry = [=](void) {
      QString pythonScriptName = QCoreApplication::applicationDirPath() + QDir::separator() + "Examples" + QDir::separator() + "Bathymetry" + QDir::separator() + "celeris_draw_bathy.py";
      QJsonArray forceSensorBeginArray;
      // Append the integer values to the JSON array
      QJsonArray forceSensorEndArray;
      if (theLatLongFSCheckBox->isChecked()) {
        qDebug() << "dx, dy: " << theDx->text() << theDy->text();
        qDebug() << "long1, lat1: " << long1Edit->text() << lat1Edit->text();
        qDebug() << "Force sensor coordinates in lat/long";
        qDebug() << "force sensor begin: " << theForceSensorBeginX->text() << theForceSensorBeginY->text();
        qDebug() << "force sensor end: " << theForceSensorEndX->text() << theForceSensorEndY->text();
        qDebug() << "Convert to meters";
        forceSensorBeginArray.append(((theForceSensorBeginX->text().toDouble() - long1Edit->text().toDouble()) * qCos(lat1Edit->text().toDouble() * 3.14159265359 / 180.0) * 111111.0) / theDx->text().toDouble());
        forceSensorBeginArray.append(((theForceSensorBeginY->text().toDouble() - lat1Edit->text().toDouble()) * 111111.0) / theDy->text().toDouble());
        forceSensorEndArray.append(((theForceSensorEndX->text().toDouble() - long1Edit->text().toDouble()) * qCos(lat1Edit->text().toDouble() * 3.14159265359 / 180.0) * 111111.0) / theDx->text().toDouble());
        forceSensorEndArray.append(((theForceSensorEndY->text().toDouble() - lat1Edit->text().toDouble()) * 111111.0) / theDy->text().toDouble());
        qDebug() << "force sensor begin: " << forceSensorBeginArray[0].toDouble() << forceSensorBeginArray[1].toDouble();
        qDebug() << "force sensor end: " << forceSensorEndArray[0].toDouble() << forceSensorEndArray[1].toDouble();
      } else {
        forceSensorBeginArray.append(int(theForceSensorBeginX->text().toDouble() / theDx->text().toDouble()));
        forceSensorBeginArray.append(int(theForceSensorBeginY->text().toDouble() / theDy->text().toDouble()));
        forceSensorEndArray.append(int(theForceSensorEndX->text().toDouble() / theDx->text().toDouble()));
        forceSensorEndArray.append(int(theForceSensorEndY->text().toDouble() / theDy->text().toDouble()));
      }
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
      // go through all elements and convert degrees lat long to meters
      if (theLatLongWGCheckBox->isChecked()) {
        for (int i = 0; i < waveGaugesArrayTemp.size(); i++) {
          QJsonArray gaugeArray = waveGaugesArrayTemp[i].toArray();
          if (theLatLongWGCheckBox->isChecked()) {
            gaugeArray[0] = ((gaugeArray[0].toDouble() - long1Edit->text().toDouble()) * qCos(lat1Edit->text().toDouble() * 3.14159265359 / 180.000000000) * 111111.000000000);
            gaugeArray[1] = ((gaugeArray[1].toDouble() - lat1Edit->text().toDouble()) * 111111.0000000000);
          }
          waveGaugesArrayTemp[i] = gaugeArray;
        }
      }
      waveGaugesDoc.setArray(waveGaugesArrayTemp);
      QString waveGaugesString = waveGaugesDoc.toJson(QJsonDocument::Compact);
      QString dx = theDx->text();
      QString dy = theDy->text();

      QString bboxString = "";
      QJsonArray bboxArray;
      bboxArray.append(long1Edit->text().toDouble());
      bboxArray.append(lat1Edit->text().toDouble());
      bboxArray.append(long2Edit->text().toDouble());
      bboxArray.append(lat2Edit->text().toDouble());
      QJsonDocument bboxDoc;
      bboxDoc.setArray(bboxArray);
      bboxString = bboxDoc.toJson(QJsonDocument::Compact);
      
      // double extrude_length = boundariesObjectJSON["boundaries"].toArray()[bathymetryID].toObject()["domain_end"].toArray()[2].toDouble() - boundariesObjectJSON["boundaries"].toArray()[bathymetryID].toObject()["domain_start"].toArray()[2].toDouble(); 
      QString inputPath = theBathymetryFile->getFilename();
      inputPath = QDir::toNativeSeparators(inputPath); // make sure its posix path
      QString outputPath = QCoreApplication::applicationDirPath() + QDir::separator() + "Examples" + QDir::separator() + "Bathymetry" + QDir::separator() + "custom_bathy.jpg";
      qDebug() << "Python script: " << pythonScriptName;
      qDebug() << "Bathymetry file: " << inputPath;
      qDebug() << "Force sensor coordinates begin: " << forceSensorBeginString;
      qDebug() << "Force sensor coordinates end: " << forceSensorEndString;
      qDebug() << "Wave gauge coordinates: " << waveGaugesString;
      qDebug() << "Grid-spacing dx: " << dx;
      qDebug() << "Grid-spacing dy: " << dy;
      qDebug() << "Output path: " << outputPath;
      qDebug() << "Bounding box coordinates: " << bboxString;

      QStringList arguments;
      arguments << inputPath << forceSensorBeginString << forceSensorEndString << waveGaugesString << dx << dy << outputPath;
      if (theLatLongPlotCheckBox->isChecked()) {
        qDebug() << "CelerisTaichi::drawBathymetry - Using Lon/Lat coordinates for the bathymetry visualization.";
        arguments << bboxString;
      } else {
        qDebug() << "CelerisTaichi::drawBathymetry - Using local coordinates for the bathymetry visualization.";
      }
      QString workingDir = QCoreApplication::applicationDirPath() + QDir::separator() + "Examples" + QDir::separator() + "Bathymetry";
      RunPythonInThread* pythonThread = new RunPythonInThread(pythonScriptName, arguments, workingDir);
      pythonThread->runProcess();
      connect(pythonThread, &RunPythonInThread::processFinished, this, [=](int exitCode) {
          qDebug() << "CelerisTaichi::drawBathymetry: Finished running python script with exit code: " << exitCode;
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


      // // Launch python script to generate the bathymetry mesh
      // QString program = SimCenterPreferences::getInstance()->getPython();
      // QStringList args;
      // args << pythonScriptName << inputPath << forceSensorBeginString << forceSensorEndString << waveGaugesString << dx << dy << outputPath;
      // if (theLatLongPlotCheckBox->isChecked()) {
      //   qDebug() << "CelerisTaichi::drawBathymetry - Using Lon/Lat coordinates for the bathymetry visualization.";
      //   args << bboxString;
      // } else {
      //   qDebug() << "CelerisTaichi::drawBathymetry - Using local coordinates for the bathymetry visualization.";
      // }
      
      // QProcess *process = new QProcess();

      // // Catch python print statements and errors and display them in through the qDebug() stream.
      // QObject::connect(process, &QProcess::readyRead, [process] () {
      //     QByteArray a = process->readAll();
      //     qDebug() << a;
      // });

      // // Delete process instance / thread when done (later), and get the exit status to handle errors.
      // QObject::connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
      //                 [=](int exitCode, QProcess::ExitStatus /*exitStatus*/){
      //     qDebug()<< "process exited with code " << exitCode;
      //     process->deleteLater();
      // });

      // process->start(program, args);
      // process->waitForStarted();
      // process->waitForFinished(-1);
      // if (process->exitStatus() == QProcess::CrashExit)
      // {
      //     qDebug() << "MPM::updateBathymetry - The script has crashed.";
      // } 
      // else if (process->exitStatus() == QProcess::NormalExit)
      // {
      //     qDebug() << "MPM::updateBathymetry - The script has finished running.";
      // }
      // else 
      // {
      //     qDebug() << "MPM::updateBathymetry - The script has finished running with an unknown exit status.";
      // }
    
    
      // QString bathyFilename = QCoreApplication::applicationDirPath() + QDir::separator() + "Examples" + QDir::separator() + "Bathymetry" + QDir::separator() + "custom_bathy.jpg";
      // QFileInfo fileInfo(bathyFilename);
      // if (fileInfo.exists()) {
      //   qDebug() << "CelerisTaichi::CelerisTaichi: Bathymetry file already exists: " << bathFilename;
      // } else {
      //   qDebug() << "CelerisTaichi::CelerisTaichi: Bathymetry file does not exist: " << bathFilename;
      // }
      // pix->load(bathyFilename);
      // theImageLabel->setPixmap(*pix);

    };



  connect(theButton, &QPushButton::released, this, [=]() {
    drawBathymetry();
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
  
  theLatLongWGCheckBox = new QCheckBox("Use Lon/Lat");
  theWaveGaugesLayout->addWidget(theLatLongWGCheckBox, 0,5,1,4);

  theWaveGaugesLayout->addWidget(theWaveGaugesTable, 1,5,5,4);
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

  connect(theBathymetryFile, &SC_FileEdit::fileNameChanged, this, [=](void) {
    // Only emit if the file exists and is readable
    QFileInfo fileInfo(theBathymetryFile->getFilename());
    if (fileInfo.exists() && fileInfo.isReadable()) {
      qDebug() << "CelerisTaichi::CelerisTaichi: Bathymetry file exists and is readable: " << theBathymetryFile->getFilename();
      emitBathymetryFileChanged();
    } else {
      qDebug() << "CelerisTaichi::CelerisTaichi: Bathymetry file does not exist or is not readable: " << theBathymetryFile->getFilename();
    }
  });

  connect(this, &CelerisTaichi::bathymetryFileChanged, this, [=]() {
    // When the bathymetry file is changed, we need to update the bathymetry image
    qDebug() << "CelerisTaichi::CelerisTaichi: bathymetryFileChanged signal received";
    drawBathymetry();
  });

  emitBathymetryFileChanged(); // emit the signal to draw the bathymetry image

}

CelerisTaichi::~CelerisTaichi()
{

}

bool
CelerisTaichi::outputToJSON(QJsonObject &jsonObject)
{
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

  
  // We read in the 'config.json' file and add it to the main scInput.json JSON on an object called "config" in the Event
  // It will overwrite the existing config object in the JSON file if we are loading an example, e.g., 'input.json'
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

  if (configObj.contains("lon_LL")) { 
    QJsonValue theValue = configObj["lon_LL"];
    long1Edit->setText(QString::number(theValue.toDouble()));
  }
  if (configObj.contains("lat_LL")) {
    QJsonValue theValue = configObj["lat_LL"];
    lat1Edit->setText(QString::number(theValue.toDouble()));
  }
  if (configObj.contains("lon_UR")) {
    QJsonValue theValue = configObj["lon_UR"];
    long2Edit->setText(QString::number(theValue.toDouble()));
  }
  if (configObj.contains("lat_UR")) {
    QJsonValue theValue = configObj["lat_UR"];
    lat2Edit->setText(QString::number(theValue.toDouble()));
  }

  emitBathymetryFileChanged(); // emit the signal to draw the bathymetry image

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

  if (configObj.contains("lon_LL")) { 
    QJsonValue theValue = configObj["lon_LL"];
    long1Edit->setText(QString::number(theValue.toDouble()));
  }
  if (configObj.contains("lat_LL")) {
    QJsonValue theValue = configObj["lat_LL"];
    lat1Edit->setText(QString::number(theValue.toDouble()));
  }
  if (configObj.contains("lon_UR")) {
    QJsonValue theValue = configObj["lon_UR"];
    long2Edit->setText(QString::number(theValue.toDouble()));
  }
  if (configObj.contains("lat_UR")) {
    QJsonValue theValue = configObj["lat_UR"];
    lat2Edit->setText(QString::number(theValue.toDouble()));
  }

  // Add contents of config.json to the JSON object
  jsonObject["config"] = configObj;

  emitBathymetryFileChanged(); // emit the signal to draw the bathymetry image

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

void CelerisTaichi::setConfigFile(QString &filename)
{
  theConfigurationFile->setFilename(filename);
  emit this->configFileChanged();
}

void CelerisTaichi::setBathymetryFile(QString &filename)
{
  theBathymetryFile->setFilename(filename);
  emit this->bathymetryFileChanged();
}

void CelerisTaichi::emitBathymetryFileChanged()
{
  emit this->bathymetryFileChanged();
  qDebug() << "CelerisTaichi::emitBathymetryFileChanged: emitted bathymetryFileChanged signal";
}

void CelerisTaichi::setWavesFile(QString &filename)
{
  theWaveFile->setFilename(filename);
}
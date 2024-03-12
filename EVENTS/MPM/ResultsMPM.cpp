/* *****************************************************************************
Copyright (c) 2016-2017, The Regents of the University of California (Regents).
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
 OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
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

// Written by: Abiy, JustinBonus

#include <QDir>
#include <QFile>
#include <QJsonDocument>

#include "ResultsMPM.h"
#include "MPM.h"
#include <GeneralInformationWidget.h>
#include <RandomVariablesContainer.h>
#include <LineEditRV.h>
#include <SimCenterPreferences.h>
#include <GeneralInformationWidget.h>
#include <SectionTitle.h>
#include <QPushButton>
#include <QScrollArea>
#include <QJsonArray>
#include <QJsonObject>
#include <QLabel>
#include <QLineEdit>
#include <QDebug>
#include <QFileDialog>
#include <QPushButton>
#include <QFileInfo>
#include <QMovie>
#include <QPixmap>
#include <QIcon>
#include <QRadioButton>
#include <QButtonGroup>
#include <QMessageBox>
#include <QComboBox>
#include <QGridLayout>
#include <QSpinBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QVector>
#include <QProcess>
#include <QJsonArray>
#include <QJsonObject>
#include <QList>
// #include "vtkGenericOpenGLRenderWindow.h"
// #include "vtkSmartPointer.h"
// #include <vtkDataObjectToTable.h>
// #include <vtkElevationFilter.h>
// #include <vtkNew.h>
// #include <vtkPolyDataMapper.h>
// #include <vtkQtTableView.h>
// #include <vtkRenderWindow.h>
// #include <vtkRenderer.h>
// #include <vtkVectorText.h>
// #include <vtkStructuredGrid.h>
// #include <vtkUnstructuredGrid.h>
// #include <vtkGenericDataObjectReader.h>
// #include <vtkRectilinearGrid.h>
// #include <vtkCellData.h>
// #include <vtkDataSetMapper.h>
// #include <vtkMultiBlockDataSet.h>
// #include <vtkSTLReader.h>
// #include <vtkPointData.h>
// #include <vtkProperty.h>
// #include <vtkRenderWindow.h>
// #include <vtkRenderWindowInteractor.h>
// #include <vtkRenderer.h>
// #include <vtkSmartPointer.h>
// #include <vtkUnstructuredGrid.h>
// #include <QVTKRenderWidget.h>
// #include <vtkRegressionTestImage.h>
// #include <vtkTestUtilities.h>
// #include <vtkSimplePointsReader.h>
#include <QVector3D>
#include <QTextStream>
#include <QString>
#include <QtMath>
#include <QWebEngineView>

ResultsMPM::ResultsMPM(MPM *parent)
    : SC_ResultsWidget(parent), mainModel(parent)
{
    if (mainModel == nullptr)
    {
        qDebug() << "ResultsMPM: parent MPM mainModel is nullptr with the constructor of ResultsMPM.";
    }
    if (!mainModel->isInitialize())
    {
        qDebug() << "ResultsMPM: mainModel is not initialized";
        // mainModel->initialize();
    }

    layout = new QVBoxLayout();

    plotProfileGroup = new QGroupBox("Wave Profiles");
    plotProfileLayout = new QGridLayout();
    plotProfileGroup->setLayout(plotProfileLayout);

    plotSpectraGroup = new QGroupBox("Velocity Spectra");
    plotSpectraLayout = new QGridLayout();
    plotSpectraGroup->setLayout(plotSpectraLayout);

    plotPressureGroup = new QGroupBox("Pressure Fluctuations");
    plotPressureLayout = new QGridLayout();
    plotPressureGroup->setLayout(plotPressureLayout);

    plotElevationGroup = new QGroupBox("Elevation Profiles");
    plotElevationLayout = new QGridLayout();
    plotElevationGroup->setLayout(plotElevationLayout);

    plotForceGroup = new QGroupBox("Force Profiles");
    plotForceLayout = new QGridLayout();
    plotForceGroup->setLayout(plotForceLayout);

    //==================================================================
    //              Plot Hydro Profiles
    //==================================================================
    QLabel* profileNameULabel = new QLabel("Name of the Profile: ");
    profileNameU = new QComboBox();
    profileNameU->addItem("Profile1");
    profileNameU->addItem("Profile2");
    profileNameU->setToolTip("Name of the profile to show.");
    profileNameU->setCurrentIndex(1);

    processSensorsButton = new QPushButton("Process Sensor Data");
    processSensorsButton->setToolTip("Processes the simulated sensor / instrument recordings to a suitable format for interpretation using Python scripts as the back-end process.");

    plotProfileLayout->addWidget(profileNameULabel, 0, 0, Qt::AlignRight);
    plotProfileLayout->addWidget(profileNameU, 0, 1);
    plotProfileLayout->addWidget(processSensorsButton, 0, 2);

    //==================================================================
    //              Plot Velocity Spectra
    //==================================================================
    QLabel* profileNameSLabel = new QLabel("Sensor Style: ");
    profileNameS = new QComboBox();
    profileNameS->addItem("particle");
    // profileNameS->addItem("grid");
    profileNameS->setToolTip("Sensors may record on different numerical bodies, so you must specify the type to dispaly data for.");
    profileNameS->setCurrentIndex(0);

    QLabel* locationSLabel = new QLabel("Sensor ID, Body ID, Device ID:");
    sensorNumS = new QComboBox();
    sensorNumS->addItem("Wave-Gauge:1");
    sensorNumS->addItem("Wave-Gauge:2");
    sensorNumS->addItem("Wave-Gauge:3");
    sensorNumS->addItem("Wave-Gauge:4");
    sensorNumS->setToolTip("ID of the sensor to display results for.");
    sensorNumS->setCurrentIndex(0);

    bodyNumS = new QComboBox();
    bodyNumS->addItem("Body:0");
    bodyNumS->addItem("Body:1");
    bodyNumS->addItem("Body:2");
    bodyNumS->addItem("Body:3");
    bodyNumS->setToolTip("ID of the body to display results for.");
    bodyNumS->setCurrentIndex(0);

    deviceNumS = new QComboBox();
    deviceNumS->addItem("GPU:0");
    deviceNumS->addItem("GPU:1");
    deviceNumS->addItem("GPU:2");
    deviceNumS->addItem("GPU:3");
    deviceNumS->setToolTip("ID of the device to display results for.");
    deviceNumS->setCurrentIndex(0);

    plotSpectra = new QPushButton("Plot Sensor");
    plotSpectra->setToolTip("Plots the sensor measurements for a given ID.");

    plotSpectraLayout->addWidget(profileNameSLabel, 0, 0, Qt::AlignRight);
    plotSpectraLayout->addWidget(profileNameS, 0, 1);
    plotSpectraLayout->addWidget(locationSLabel, 0, 2, Qt::AlignRight);
    plotSpectraLayout->addWidget(sensorNumS, 0, 3);
    plotSpectraLayout->addWidget(bodyNumS, 0, 4);
    plotSpectraLayout->addWidget(deviceNumS, 0, 5);
    plotSpectraLayout->addWidget(plotSpectra, 0, 6, 1,2);

    //==================================================================
    //              Plot Pressure Profiles
    //==================================================================
    QLabel* profileNamePLabel = new QLabel("Name of the Profile: ");
    profileNameP = new QComboBox();
    profileNameP->addItem("Profile3");
    profileNameP->setToolTip("Name of the profile to show.");
    profileNameP->setCurrentIndex(0);

    plotPressure = new QPushButton("Plot Pressure");
    plotPressure->setToolTip("Plots the pressure fluctuation on a given line probe.");

    plotPressureLayout->addWidget(profileNamePLabel, 0, 0, Qt::AlignRight);
    plotPressureLayout->addWidget(profileNameP, 0, 1);
    plotPressureLayout->addWidget(plotPressure, 0, 2);

    //==================================================================
    //              Plot Elevation Profiles
    //==================================================================
    QLabel* profileNameELabel = new QLabel("Name of the Profile: ");
    profileNameE = new QComboBox();
    profileNameE->addItem("Profile4");
    profileNameE->setToolTip("Name of the profile to show.");
    profileNameE->setCurrentIndex(0);

    plotElevation = new QPushButton("Plot Elevation");
    plotElevation->setToolTip("Plots the elevation profile for a given line probe.");

    plotElevationLayout->addWidget(profileNameELabel, 0, 0, Qt::AlignRight);
    plotElevationLayout->addWidget(profileNameE, 0, 1, Qt::AlignLeft);
    plotElevationLayout->addWidget(plotElevation, 0, 2);

    //==================================================================
    //              Plot Force Profiles
    //==================================================================
    QLabel* profileNameFLabel = new QLabel("Name of the Profile: ");
    profileNameF = new QComboBox();
    profileNameF->addItem("Profile5");
    profileNameF->setToolTip("Name of the profile to show.");
    profileNameF->setCurrentIndex(0);

    plotForce = new QPushButton("Plot Force");
    plotForce->setToolTip("Plots the force profile for a given line probe.");
    
    plotForceLayout->addWidget(profileNameFLabel, 0, 0, Qt::AlignRight);
    plotForceLayout->addWidget(profileNameF, 0, 1, Qt::AlignLeft);
    plotForceLayout->addWidget(plotForce, 0, 2);

    //==================================================================
    //              Connect Signals and Slots
    //==================================================================
    connect(processSensorsButton, SIGNAL(clicked()), this, SLOT(onProcessSensorsClicked()));
    connect(processSensorsButton, SIGNAL(clicked()), this, SLOT(onPlotProfileClicked()));
    connect(plotSpectra, SIGNAL(clicked()), this, SLOT(onPlotSpectraClicked()));
    connect(plotPressure, SIGNAL(clicked()), this, SLOT(onPlotPressureClicked()));
    connect(plotElevation, SIGNAL(clicked()), this, SLOT(onPlotElevationClicked()));
    connect(plotForce, SIGNAL(clicked()), this, SLOT(onPlotForceClicked()));

    layout->addWidget(plotProfileGroup);
    layout->addWidget(plotSpectraGroup);
    layout->addWidget(plotPressureGroup);
    layout->addWidget(plotElevationGroup);
    layout->addWidget(plotForceGroup);
    this->setLayout(layout);
}


ResultsMPM::~ResultsMPM()
{

}

void 
ResultsMPM::clear(void)
{

}

void 
ResultsMPM::onPlotProfileClicked(void)
{
    int dialogHeight = 875;
    int dialogWidth = 1250;

    QVBoxLayout *plotLayout = new QVBoxLayout();

    QWebEngineView *plotView = new QWebEngineView();
    plotView->page()->setBackgroundColor(Qt::transparent);
    plotLayout->addWidget(plotView);

    plotView->setMinimumWidth(dialogWidth);
    plotView->setMinimumHeight(dialogHeight);


    QString ext = ".html"; // ".csv"
    QString plotPath = mainModel->caseDir() + QDir::separator() 
                        + "output" + QDir::separator() 
                        + profileNameS->currentText() 
                        + ext;

    if(QFileInfo::exists(plotPath))
    {
        plotView->load(QUrl::fromLocalFile(plotPath));
        plotView->setWindowFlag(Qt::WindowStaysOnTopHint);
        plotView->show();
        plotView->activateWindow();
        plotView->raise();
    }
}


void 
ResultsMPM::onPlotSpectraClicked(void)
{
    int dialogHeight = 500;
    int dialogWidth = 1550;



    QVBoxLayout *plotLayout = new QVBoxLayout();

    QWebEngineView *plotView = new QWebEngineView();
    plotView->page()->setBackgroundColor(Qt::transparent);
    plotLayout->addWidget(plotView);

    plotView->setMinimumWidth(dialogWidth);
    plotView->setMinimumHeight(dialogHeight);

    QString ext = ".html"; // ".csv"
    QString pre = "Target"; // "Sensor"
    QString bodyLabel = "model"; // "body";
    QString deviceLabel = "dev"; // "gpu";
    QString plotPath = mainModel->caseDir() + QDir::separator() 
                        + "output" + QDir::separator() 
                        + profileNameS->currentText()
                        + pre + "[" + QString::number(sensorNumS->currentIndex()) + "]_" 
                        + bodyLabel + "[" + QString::number(bodyNumS->currentIndex()) + "]_"
                        + deviceLabel + "[" + QString::number(deviceNumS->currentIndex()) + "]"
                        + ext;

    if(QFileInfo::exists(plotPath))
    {
        plotView->load(QUrl::fromLocalFile(plotPath));
        plotView->setWindowFlag(Qt::WindowStaysOnTopHint);
        plotView->show();
        plotView->activateWindow();
        plotView->raise();
    } else {
        QMessageBox::warning(this, tr("File Not Found: "), plotPath);        
    }

}



void 
ResultsMPM::onPlotPressureClicked(void)
{
    int dialogHeight = 450;
    int dialogWidth = 850;

    QVBoxLayout *plotLayout = new QVBoxLayout();

    QWebEngineView *plotView = new QWebEngineView();
    plotView->page()->setBackgroundColor(Qt::transparent);
    plotLayout->addWidget(plotView);

    plotView->setMinimumWidth(dialogWidth);
    plotView->setMinimumHeight(dialogHeight);

    QString ext = ".html";
    QString plotPath = mainModel->caseDir() + QDir::separator() 
                        + "output" + QDir::separator() 
                        + profileNameP->currentText() 
                        + ext;

    if(QFileInfo::exists(plotPath))
    {
        plotView->load(QUrl::fromLocalFile(plotPath));
        plotView->setWindowFlag(Qt::WindowStaysOnTopHint);
        plotView->show();
        plotView->activateWindow();
        plotView->raise();
    }
}

void 
ResultsMPM::onPlotElevationClicked(void)
{
    int dialogHeight = 450;
    int dialogWidth = 850;

    QVBoxLayout *plotLayout = new QVBoxLayout();

    QWebEngineView *plotView = new QWebEngineView();
    plotView->page()->setBackgroundColor(Qt::transparent);
    plotLayout->addWidget(plotView);

    plotView->setMinimumWidth(dialogWidth);
    plotView->setMinimumHeight(dialogHeight);

    QString ext = ".html";
    QString plotPath = mainModel->caseDir() + QDir::separator() 
                        + "constant" + QDir::separator() 
                        + "simCenter" + QDir::separator() 
                        + "output" + QDir::separator() 
                        + "sensors" + QDir::separator()
                        + profileNameE->currentText() 
                        + ext;

    if(QFileInfo::exists(plotPath))
    {
        plotView->load(QUrl::fromLocalFile(plotPath));
        plotView->setWindowFlag(Qt::WindowStaysOnTopHint);
        plotView->show();
        plotView->activateWindow();
        plotView->raise();
    }
}

void 
ResultsMPM::onPlotForceClicked(void)
{
    int dialogHeight = 450;
    int dialogWidth = 850;

    QVBoxLayout *plotLayout = new QVBoxLayout();

    QWebEngineView *plotView = new QWebEngineView();
    plotView->page()->setBackgroundColor(Qt::transparent);
    plotLayout->addWidget(plotView);

    plotView->setMinimumWidth(dialogWidth);
    plotView->setMinimumHeight(dialogHeight);

    QString ext =  ".html"; // ".html"; 
    QString plotPath = mainModel->caseDir() + QDir::separator() 
                        + "constant" + QDir::separator() 
                        + "simCenter" + QDir::separator() 
                        + "output" + QDir::separator() 
                        + "sensors" + QDir::separator()
                        + profileNameF->currentText() 
                        + ext;

    if(QFileInfo::exists(plotPath))
    {
        plotView->load(QUrl::fromLocalFile(plotPath));
        plotView->setWindowFlag(Qt::WindowStaysOnTopHint);
        plotView->show();
        plotView->activateWindow();
        plotView->raise();
    }

}



bool 
ResultsMPM::outputToJSON(QJsonObject &jsonObject)
{
    // Writes wind load monitoring options JSON file.  
    // QJsonObject resDisplayJson = QJsonObject();
    // QJsonArray spectralPlotLocations = {0.25, 0.5, 1.0, 2.0};
    // resDisplayJson["spectralPlotLocations"] = spectralPlotLocations;
    // jsonObject["resultDisplay"] = resDisplayJson;
    return true;
}


void 
ResultsMPM::plotSensors(MPM* host)
{
    //
    //  Python scripts hosted remotely by SimCenterBackendApplications/modules/createEVENT/*
    // 

    QString scriptName = "post_process_sensors.py"; // "MPM.py";
    QString scriptPath = mainModel->pyScriptsPath() + QDir::separator() + scriptName; 
    QString sensorsPath = mainModel->caseDir() + QDir::separator() + "output" + QDir::separator() ;
    QString outputPath = mainModel->caseDir() + QDir::separator() + "output" + QDir::separator() ;
    // Find all the sensors in the sensorsPath folder if it exists, make them into one QString that is comma separated.

    qDebug() << "ResultsMPM::plotSensors - sensorsPath: " << sensorsPath;
    qDebug() << "ResultsMPM::plotSensors - outputPath: " << outputPath;
    qDebug() << "ResultsMPM::plotSensors - scriptPath: " << scriptPath;
    qDebug() << "ResultsMPM::plotSensors - scriptName: " << scriptName;

    QString sensorsList =  "";
    QDir sensorsDir(sensorsPath);
    if (sensorsDir.exists())
    {

        // Print all the files in the directory (max 64 files for now, to avoid spamming the console)
        qDebug() << "Files in the sensors directory: "; 
        for (int i = 0; i < sensorsDir.count() && i < 64; i++)
        {
            qDebug() << sensorsDir[i];
        }

        QStringList filters("*.csv"); // This is the file extension of the sensor files, it may change in the future.
        // entryList returns a QStringList of all the files in the directory that match the filters.
        QStringList sensorFiles = sensorsDir.entryList(filters); //, QDir::Files, QDir::Name); 
        if (sensorFiles.size() == 0)
        {
            qDebug() << "Sensor directory exists, but no sensor files found in the output directory. Cannot run the post_process_sensors.py script. Dir: " << sensorsPath;
            return;
        }
        for (int i = 0; i < sensorFiles.size(); i++)
        {
            // Turn StringList into a comma separated QString
            sensorsList += sensorFiles[i]; 
            if (i < sensorFiles.size() - 1)
            {
                sensorsList += ","; // For QString , is this the correct way to do this? 
            }
            qDebug() << "Sensor file: " << sensorFiles[i];
        }
    } else {
        qDebug() << "The sensor's measurement files directory does not exist: " << sensorsPath;
    }
    
    qDebug() << "ResultsMPM::plotSensors - sensorsList: " << sensorsList;

    if (sensorsList.isEmpty())
    {
        qDebug() << "No sensor files found in the output directory. Cannot run the post_process_sensors.py script. Dir: " << sensorsPath << " sensorsList: " << sensorsList; 
        return;
    }

    if (!QDir(outputPath).exists())
    {
        qDebug() << "ResultsMPM::plotSensors - Creating the output directory: " << outputPath;
        QDir().mkdir(outputPath);
    } 


    if (QFileInfo(scriptPath).exists() && QFileInfo(scriptPath).isFile())
    {
        QString program = SimCenterPreferences::getInstance()->getPython();
        qDebug() << "ResultsMPM::plotSensors - Python program path: " << program;
        QProcess *process = new QProcess();
        QStringList arguments; 
        arguments << scriptPath << sensorsPath << outputPath << sensorsList;

        // Catch python print statements and errors and display them in through the qDebug() stream.
        QObject::connect(process, &QProcess::readyRead, [process] () {
            QByteArray a = process->readAll();
            qDebug() <<  a;
        });

        // Delete process instance / thread when done (later), and get the exit status to handle errors.
        QObject::connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                        [=](int exitCode, QProcess::ExitStatus /*exitStatus*/){
            qDebug()<< "process exited with code " << exitCode;
            process->deleteLater();
        });
        process->start(program, arguments);
        process->waitForStarted(); 
        process->waitForFinished(-1);
        if (process->exitStatus() == QProcess::CrashExit)
        {
            qDebug() << "ResultsMPM::plotSensors - The post_process_sensors.py script has crashed.";
        } 
        else if (process->exitStatus() == QProcess::NormalExit)
        {
            qDebug() << "ResultsMPM::plotSensors - The post_process_sensors.py script has finished running.";
        }
        else 
        {
            qDebug() << "ResultsMPM::plotSensors - The post_process_sensors.py script has finished running with an unknown exit status.";
        }
        // process->close();
        qDebug() << "ResultsMPM::plotSensors - Finished running the post_process_sensors.py script.";
    } 
    else 
    {
        qDebug() << "ERROR: Cannot find the post-process-sensors.py script path file, consider changing SimCenterBackendApplications path preference under the file drop-down to alter this to be valid: " << scriptPath;
    }
    return;
}


void
ResultsMPM::processResults(QString &dirName)
{
  QDir resultsDir(dirName);
  QString resultsPath = resultsDir.absolutePath() + QDir::separator() + "results";
  QString inputFileName = "MPM.json"; // "ResultsMPM.json"
  QString inputFilePath = resultsPath + QDir::separator() 
                            + "constant" + QDir::separator() 
                            + "simCenter" + QDir::separator() 
                            + "input" + QDir::separator() 
                            + inputFileName;
  QFile jsonFile(inputFilePath);
  if (!jsonFile.open(QFile::ReadOnly | QFile::Text))
  {
        qDebug() << "Cannot find the path: " << inputFilePath;
        return;
  }

  QString val = jsonFile.readAll();
  QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
  QJsonObject jsonObject = doc.object();
  jsonFile.close();

  jsonObject["caseDirectoryPath"] = resultsPath;
  mainModel->inputFromJSON(jsonObject);

  return;  
}

int
ResultsMPM::processResults(QString &inputFile, QString &dirName)
{
  qDebug() << "ResultsMPM::processResults - dirName: " << dirName;
  QDir resultsDir(dirName);
  QString resultsPath = resultsDir.absolutePath() + QDir::separator() + "results";
  QString inputFileName = "MPM.json"; // "ResultsMPM.json"
  QString inputFilePath = resultsPath + QDir::separator() 
                            + "constant" + QDir::separator() 
                            + "simCenter" + QDir::separator() 
                            + "input" + QDir::separator() 
                            + inputFileName;
  QFile jsonFile(inputFilePath);
  if (!jsonFile.open(QFile::ReadOnly | QFile::Text))
  {
        qDebug() << "Cannot find the path: " << inputFilePath;
        return -1;
  }

  QString val = jsonFile.readAll();
  QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
  QJsonObject jsonObject = doc.object();
  jsonFile.close();

//   jsonObject["caseDirectoryPath"] = resultsPath;
  mainModel->inputFromJSON(jsonObject);

  return 0;  
}

int
ResultsMPM::processResults(QString &inputFile, QString &dirName, QString &assetType, QList<QString> typesInAssetType)
{
  qDebug() << "ResultsMPM::processResults - dirName: " << dirName;
  QDir resultsDir(dirName);
  QString resultsPath = resultsDir.absolutePath() + QDir::separator() + "results";
  QString inputFileName = "MPM.json"; // "ResultsMPM.json"
  QString inputFilePath = resultsPath + QDir::separator() 
                            + "constant" + QDir::separator() 
                            + "simCenter" + QDir::separator() 
                            + "input" + QDir::separator() 
                            + inputFileName;
  QFile jsonFile(inputFilePath);
  if (!jsonFile.open(QFile::ReadOnly | QFile::Text))
  {
        qDebug() << "Cannot find the path: " << inputFilePath;
        return -1;
  }

  QString val = jsonFile.readAll();
  QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
  QJsonObject jsonObject = doc.object();
  jsonFile.close();

//   jsonObject["caseDirectoryPath"] = resultsPath;

    mainModel->inputFromJSON(jsonObject);
    
    return 0;  
}

bool 
ResultsMPM::inputFromJSON(QJsonObject &jsonObject)
{
    // Writes Event load (IMs/EDPs) monitoring options JSON file.
    // QJsonObject resMonitoringJson = jsonObject["resultMonitoring"].toObject();
    // QJsonArray profiles = resMonitoringJson["hydroProfiles"].toArray();
    QJsonArray profiles = jsonObject["particle-sensors"].toArray();
    // QJsonArray profiles = resMonitoringJson["hydroProfiles"].toArray();
    // profileNameU->clear();
    // profileNameS->clear();
    // profileNameP->clear();
    // profileNameE->clear();
    // profileNameF->clear();

    QString key = "attribute";
    for (int i = 0; i < profiles.size(); i++)
    {
        QJsonObject profile  = profiles[i].toObject();

        profileNameS->addItem(QString::number(i)); 

        if (profile[key].toString() == "Velocity")
        {
            profileNameU->addItem(profile["name"].toString()); // Wave Profile
            profileNameS->addItem(profile["name"].toString()); // Wave Spectra
            // profileNameS->addItem(QString("0")); // Wave Spectra
        }
        if (profile[key].toString() == "Pressure")
        {
            profileNameP->addItem(profile["name"].toString());
        }

        if (profile[key].toString() == "Elevation" || profile[key].toString() == "Position_Y")
        {
            profileNameE->addItem(profile["name"].toString());
        }

        if (profile[key].toString() == "Force" || profile[key].toString() == "Load")
        {
            profileNameF->addItem(profile["name"].toString());
        }

    }

    return true;
}

void 
ResultsMPM::updateWidgets()
{

}

bool 
ResultsMPM::simulationCompleted()
{
    return true;
}
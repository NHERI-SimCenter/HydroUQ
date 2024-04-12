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
    
    processSensorsGroup = new QGroupBox("Post-Process Sensors");
    processSensorsLayout = new QGridLayout();
    processSensorsGroup->setLayout(processSensorsLayout);

    plotSpectraGroup = new QGroupBox("Plot Sensor Measurements");
    plotSpectraLayout = new QGridLayout();
    plotSpectraGroup->setLayout(plotSpectraLayout);

    plotElevationGroup = new QGroupBox("Plot Elevation");
    plotElevationLayout = new QGridLayout();
    plotElevationGroup->setLayout(plotElevationLayout);

    plotForceGroup = new QGroupBox("Plot Force");
    plotForceLayout = new QGridLayout();
    plotForceGroup->setLayout(plotForceLayout);

    plotPressureGroup = new QGroupBox("Plot Pressure");
    plotPressureLayout = new QGridLayout();
    plotPressureGroup->setLayout(plotPressureLayout);


    //==================================================================
    //              Plot Hydro Profiles
    //==================================================================
    QLabel* processSensorsLabel = new QLabel("Post-Process Script File: ");
    processSensorsName = new QComboBox();
    // processSensorsName->addItem("post_process_output.py");
    processSensorsName->addItem("post_process_sensors.py");
    processSensorsName->addItem("post_process_sensors_tsunami.py");
    processSensorsName->addItem("post_process_sensors_surge.py");
    processSensorsName->setToolTip("Name of the Post-Processing Script.");
    processSensorsName->setCurrentIndex(0);

    processSensorsButton = new QPushButton("Process Sensor Data");
    processSensorsButton->setToolTip("Post-Processes the simulated sensor / instrument recordings to a suitable format for interpretation / plotting using Python scripts as the back-end process.");

    processSensorsLayout->addWidget(processSensorsLabel, 0, 0, Qt::AlignRight);
    processSensorsLayout->addWidget(processSensorsName, 0, 1);
    processSensorsLayout->addWidget(processSensorsButton, 0, 2);

    // //==================================================================
    // //              Plot Hydro Profiles
    // //==================================================================
    // QLabel* profileNameULabel = new QLabel("Name of the Profile: ");
    // profileNameU = new QComboBox();
    // profileNameU->addItem("Profile1");
    // profileNameU->addItem("Profile2");
    // profileNameU->setToolTip("Name of the profile to show.");
    // profileNameU->setCurrentIndex(1);

    // processSensorsButton = new QPushButton("Process Sensor Data");
    // processSensorsButton->setToolTip("Processes the simulated sensor / instrument recordings to a suitable format for interpretation using Python scripts as the back-end process.");

    // plotProfileLayout->addWidget(profileNameULabel, 0, 0, Qt::AlignRight);
    // plotProfileLayout->addWidget(profileNameU, 0, 1);
    // plotProfileLayout->addWidget(processSensorsButton, 0, 2);

    //==================================================================
    //              Plot Velocity Spectra
    //==================================================================
    QLabel* profileNameSLabel = new QLabel("Numerical-Type: ");
    profileNameS = new QComboBox();
    profileNameS->addItem("particle");
    profileNameS->addItem("grid");
    profileNameS->setToolTip("Sensors record various different numerical bodies, so you must specify the type to display data for.");
    profileNameS->setCurrentIndex(0);

    QLabel* locationSLabel = new QLabel("Sensor ID: ");
    sensorNumS = new QComboBox();
    sensorNumS->addItem("Sensor:0");
    sensorNumS->addItem("Sensor:1");
    sensorNumS->addItem("Sensor:2");
    sensorNumS->addItem("Sensor:3");
    // sensorNumS->addItem("Sensor:4");
    // sensorNumS->addItem("Sensor:5");
    // sensorNumS->addItem("Sensor:6");
    // sensorNumS->addItem("Sensor:7");
    sensorNumS->setToolTip("ID of the sensor numerical-type to display results for.");
    sensorNumS->setCurrentIndex(0);


    QLabel* bodyLabel = new QLabel("Body ID: ");
    bodyNumS = new QComboBox();
    bodyNumS->addItem("Body:0");
    bodyNumS->addItem("Body:1");
    bodyNumS->addItem("Body:2");
    bodyNumS->addItem("Body:3");
    bodyNumS->setToolTip("ID of the material body (per-device) measured by a sensor to display results for.");
    bodyNumS->setCurrentIndex(0);

    QLabel* deviceLabel = new QLabel("Device ID: ");
    deviceNumS = new QComboBox();
    deviceNumS->addItem("GPU:0");
    deviceNumS->addItem("GPU:1");
    deviceNumS->addItem("GPU:2");
    deviceNumS->addItem("GPU:3");
    // deviceNumS->addItem("GPU:4");
    // deviceNumS->addItem("GPU:5");
    // deviceNumS->addItem("GPU:6");
    // deviceNumS->addItem("GPU:7");
    deviceNumS->setToolTip("ID of the hardware device that the sensor was simulated on to display results for.");
    deviceNumS->setCurrentIndex(0);

    plotSpectra = new QPushButton("Plot Sensor");
    plotSpectra->setToolTip("Plots sensor / instrument measurements for a given sensor ID, body ID, and device ID.");

    plotSpectraLayout->addWidget(profileNameSLabel, 0, 0, Qt::AlignRight);
    plotSpectraLayout->addWidget(profileNameS, 0, 1);
    plotSpectraLayout->addWidget(locationSLabel, 0, 2, Qt::AlignRight);
    plotSpectraLayout->addWidget(sensorNumS, 0, 3);
    plotSpectraLayout->addWidget(bodyLabel, 0, 4, Qt::AlignRight);
    plotSpectraLayout->addWidget(bodyNumS, 0, 5);
    plotSpectraLayout->addWidget(deviceLabel, 0, 6, Qt::AlignRight);
    plotSpectraLayout->addWidget(deviceNumS, 0, 7);
    plotSpectraLayout->addWidget(plotSpectra, 0, 8, 1,2);

    // //==================================================================
    // //              Plot Elevation Profiles
    // //==================================================================
    // QLabel* profileNameELabel = new QLabel("Name of the Wave-Gauge: ");
    // profileNameE = new QComboBox();
    // profileNameE->addItem("particleTarget[0]_model[0]_dev[0].webp");
    // profileNameE->setToolTip("Name of the wave-gauge to show.");
    // profileNameE->setCurrentIndex(0);

    // plotElevation = new QPushButton("Plot Elevation.");
    // plotElevation->setToolTip("Plots the free-surface elevation readings of wave-gauges.");

    // plotElevationLayout->addWidget(profileNameELabel, 0, 0, Qt::AlignRight);
    // plotElevationLayout->addWidget(profileNameE, 0, 1, Qt::AlignLeft);
    // plotElevationLayout->addWidget(plotElevation, 0, 2);

    // //==================================================================
    // //              Plot Pressure Profiles
    // //==================================================================
    // QLabel* profileNamePLabel = new QLabel("Name of the Piezometer: ");
    // profileNameP = new QComboBox();
    // profileNameP->addItem("gridTarget[0]_dev[0].webp");
    // profileNameP->setToolTip("Name of the piezometer to show.");
    // profileNameP->setCurrentIndex(0);

    // plotPressure = new QPushButton("Plot Pressure");
    // plotPressure->setToolTip("Plots the pressure measurements of piezometers.");

    // plotPressureLayout->addWidget(profileNamePLabel, 0, 0, Qt::AlignRight);
    // plotPressureLayout->addWidget(profileNameP, 0, 1);
    // plotPressureLayout->addWidget(plotPressure, 0, 2);

    // //==================================================================
    // //              Plot Force Profiles
    // //==================================================================
    // QLabel* profileNameFLabel = new QLabel("Name of the Load-Cell: ");
    // profileNameF = new QComboBox();
    // profileNameF->addItem("gridTarget[0]_dev[0].webp");
    // profileNameF->setToolTip("Name of the load-cell to show.");
    // profileNameF->setCurrentIndex(0);

    // plotForce = new QPushButton("Plot Force");
    // plotForce->setToolTip("Plots the force measurements of load-cells.");
    
    // plotForceLayout->addWidget(profileNameFLabel, 0, 0, Qt::AlignRight);
    // plotForceLayout->addWidget(profileNameF, 0, 1, Qt::AlignLeft);
    // plotForceLayout->addWidget(plotForce, 0, 2);

    //==================================================================
    //              Connect Signals and Slots
    //==================================================================
    connect(processSensorsButton, SIGNAL(clicked()), this, SLOT(onProcessSensorsClicked()));
    connect(plotSpectra, SIGNAL(clicked()), this, SLOT(onPlotSpectraClicked()));
    // connect(plotPressure, SIGNAL(clicked()), this, SLOT(onPlotPressureClicked()));
    // connect(plotElevation, SIGNAL(clicked()), this, SLOT(onPlotElevationClicked()));
    // connect(plotForce, SIGNAL(clicked()), this, SLOT(onPlotForceClicked()));

    layout->addWidget(processSensorsGroup);
    layout->addWidget(plotSpectraGroup);
    // layout->addWidget(plotElevationGroup);
    // layout->addWidget(plotForceGroup);
    // layout->addWidget(plotPressureGroup);
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
    plotSensors(mainModel);
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

    jsonObject["caseDirectoryPath"] = resultsPath;
    mainModel->inputFromJSON(jsonObject);
    plotSensors(mainModel);
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

    jsonObject["caseDirectoryPath"] = resultsPath;
    mainModel->inputFromJSON(jsonObject);
    plotSensors(mainModel);
    return 0;  
}


void 
ResultsMPM::onProcessSensorsClicked(void)
{
    plotSensors(mainModel);
    // processResults(mainModel->caseDir());
    // int dialogHeight = 800;
    // int dialogWidth  = 800;

    // QVBoxLayout *plotLayout = new QVBoxLayout();

    // QWebEngineView *plotView = new QWebEngineView();
    // plotView->page()->setBackgroundColor(Qt::transparent);
    // plotLayout->addWidget(plotView);

    // plotView->setMinimumWidth(dialogWidth);
    // plotView->setMinimumHeight(dialogHeight);


    // QString ext = ".webp" ;  // ".html"; // ".csv"
    // QString plotPath = mainModel->caseDir() + QDir::separator() 
    //                     + "output" + QDir::separator() 
    //                     + profileNameS->currentText() 
    //                     + ext;

    
    // if(QFileInfo::exists(plotPath))
    // {
    //     plotView->load(QUrl::fromLocalFile(plotPath));
    //     plotView->setWindowFlag(Qt::WindowStaysOnTopHint);
    //     plotView->show();
    //     plotView->activateWindow();
    //     plotView->raise();
    // }

}


void 
ResultsMPM::onPlotSpectraClicked(void)
{
    int dialogHeight = 800;
    int dialogWidth  = 800;

    QVBoxLayout *plotLayout = new QVBoxLayout();
    QWebEngineView *plotView = new QWebEngineView();
    plotView->page()->setBackgroundColor(Qt::transparent);
    plotLayout->addWidget(plotView);

    plotView->setMinimumWidth(dialogWidth);
    plotView->setMinimumHeight(dialogHeight);

    QString ext = ".webp"; // ".html"; // ".csv"
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

    QString ext = ".png";
    for (int i=0; i<2; ++i) {
        if (i == 0) ext = ".webp";
        if (i == 1) ext = ".html";
        QString intermediateFolder = "";
        for (int j=0; j<3; ++j)
        {
            if (j == 0) intermediateFolder = "";
            if (j == 1) intermediateFolder = "sensors";
            if (j == 2) intermediateFolder = "results";
            if (j == 3) intermediateFolder = ""; // TODO: Just use the preferences for this.
            
            QString plotDir = mainModel->caseDir() + QDir::separator() 
                                + "output" + QDir::separator()
                                + intermediateFolder + QDir::separator();
            // If directory doesn't exist then skip to the next one.
            if (!QDir(plotDir).exists())
            {
                qDebug() << "ResultsMPM::onPlotPressureClicked - Checked for results.zip in " << plotDir << ", but folder does not exist. Skipping...";
                continue;
            }

            QString zipPath = mainModel->caseDir() + QDir::separator() 
                            + "output" + QDir::separator()
                            + intermediateFolder + QDir::separator() 
                            + "results.zip";

            if (j == 3)
            {
                // Remoteworkdir
                zipPath = SimCenterPreferences::getInstance()->getRemoteAppDir() + QDir::separator() 
                            + "results.zip";
            }
            if (QFileInfo::exists(zipPath))
            {
                QString program = "tar";
                QStringList arguments;
                // Extract results.zip file from zipPath (either in the GUI set caseDir/output/{'','sensors','results}, variants in brackets, or in RemoteWorkDir when retrieving run from DesignSafe. Extract to plotDir
                arguments << "-xzf" << zipPath << "-c" << plotDir; 
                QProcess *process = new QProcess();
                process->start(program, arguments);
                process->waitForStarted(); 
                process->waitForFinished(-1);
                if (process->exitStatus() == QProcess::CrashExit)
                {
                    qDebug() << "ResultsMPM::onPlotPressureClicked - The unzip process has crashed.";
                } 
                else if (process->exitStatus() == QProcess::NormalExit)
                {
                    qDebug() << "ResultsMPM::onPlotPressureClicked - The unzip process has finished running.";
                }
                else 
                {
                    qDebug() << "ResultsMPM::onPlotPressureClicked - The unzip process has finished running with an unknown exit status.";
                }
                process->deleteLater();
            }
            
            QString plotPath = mainModel->caseDir() + QDir::separator() 
                                + "output" + QDir::separator()
                                + intermediateFolder + QDir::separator() 
                                + profileNameP->currentText() 
                                + ext;
            if (QFileInfo::exists(plotPath))
            {
                // Check if results.zip here, if so, extract it.

                plotView->load(QUrl::fromLocalFile(plotPath));
                plotView->setWindowFlag(Qt::WindowStaysOnTopHint);
                plotView->show();
                plotView->activateWindow();
                plotView->raise();
            }
        }
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

    QString ext = ".webp";
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
    int dialogHeight = 800;
    int dialogWidth = 800;

    QVBoxLayout *plotLayout = new QVBoxLayout();
    QWebEngineView *plotView = new QWebEngineView();
    plotView->page()->setBackgroundColor(Qt::transparent);
    plotLayout->addWidget(plotView);

    plotView->setMinimumWidth(dialogWidth);
    plotView->setMinimumHeight(dialogHeight);

    QString ext = ".webp"; // ".html"; // ".csv"
    QString pre = "gridTarget"; // "Sensor"
    QString deviceLabel = "dev"; // "gpu";
    QString plotPath = mainModel->caseDir() + QDir::separator() 
                        + "output" + QDir::separator() 
                        + pre + "[" + QString::number(sensorNumS->currentIndex()) + "]_" 
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

// Rename to processSensors, and vice versa
void 
ResultsMPM::plotSensors(MPM* host)
{
    //
    //  Python scripts hosted remotely by SimCenterBackendApplications/modules/createEVENT/*
    // 

    QString scriptName = "post_process_sensors.py"; // Default script name., in SimCenterBackendApplications/modules/createEVENT/
    if (processSensorsName) {
        scriptName = processSensorsName->currentText(); // Must be initialized to a valid QString.
    }
    QString scriptPath = mainModel->pyScriptsPath() + QDir::separator() + scriptName; 
    QString sensorsPath = mainModel->caseDir() + QDir::separator() + "output" + QDir::separator() ;
    QString outputPath = mainModel->caseDir() + QDir::separator() + "output" + QDir::separator() ;
    // Find all the sensors in the sensorsPath folder if it exists, make them into one QString that is comma separated.
    qDebug() << "ResultsMPM::plotSensors - sensorsPath: " << sensorsPath;
    qDebug() << "ResultsMPM::plotSensors - outputPath: " << outputPath;
    qDebug() << "ResultsMPM::plotSensors - scriptPath: " << scriptPath;
    qDebug() << "ResultsMPM::plotSensors - scriptName: " << scriptName;

    // We want to ensure that results.zip is extracted into individual sensor files for processing
    // Check the user specified case director for the results.zip
    // Also check most likely local directories for the results.zip file
    // Also check the remote work directory for the results.zip file
    // Extract to 
    QString intermediateFolder = "";
    for (int j=0; j<4; ++j)
    {
        if (j == 0) intermediateFolder = "."; // RemoteWorkDir
        if (j == 1) intermediateFolder = "sensors"; // LocalWorkDir
        if (j == 2) intermediateFolder = "results"; // LocalWorkDir
        if (j == 3) intermediateFolder = "."; // LocalWorkDir
        
        QString plotDir = sensorsPath; // + intermediateFolder + QDir::separator(); // Save the extracted files to the sensors directory.
        // NOTE: The sensors directory is where the sensor time-series files are stored.
        //       The plots are stored in the output directory once created.
    
        // If directory doesn't exist then skip to the next one.
        if (!QDir(plotDir).exists())
        {
            qDebug() << "ResultsMPM::plotSensors - Checked if the folder to extract to exists: " << plotDir << ", but folder does not exist. Skipping...";
            continue;
        }

        QString zipDir = SimCenterPreferences::getInstance()->getLocalWorkDir() + QDir::separator();
        if (j == 0)
        {
            zipDir = SimCenterPreferences::getInstance()->getRemoteWorkDir() + QDir::separator();
        } 
        else 
        {
            zipDir = mainModel->caseDir() + QDir::separator() 
                            + "output" + QDir::separator()
                            + intermediateFolder + QDir::separator();
        }

        QString zipPath = zipDir + "results.zip";
        if (!QDir(zipDir).exists())
        {
            qDebug() << "ResultsMPM::plotSensors - Checked if folder " << zipDir << " exists, but folder does not exist. Skipping...";
            continue;
        }

        if (QFileInfo::exists(zipPath))
        {
            QString program = "tar"; // "unzip"; // TODO: consider cross-platform compatibility.
            QStringList arguments;
            // Extract results.zip file from zipPath (either in the GUI set caseDir/output/{'','sensors','results}, variants in brackets, or in RemoteWorkDir when retrieving run from DesignSafe. Extract to plotDir
            // plotDir must exist, and the zipPath must exist.
            arguments << "-xzf" << zipPath << "-C" << plotDir; 
            QProcess *process = new QProcess();
            process->start(program, arguments);
            process->waitForStarted(); 
            process->waitForFinished(-1);
            if (process->exitStatus() == QProcess::CrashExit)
            {
                qDebug() << "ResultsMPM::plotSensors - The unzip process has crashed.";
            } 
            else if (process->exitStatus() == QProcess::NormalExit)
            {
                qDebug() << "ResultsMPM::plotSensors - The unzip process has finished running.";
                process->deleteLater(); 
                break;
            }
            else 
            {
                qDebug() << "ResultsMPM::plotSensors - The unzip process has finished running with an unknown exit status.";
            }
            process->deleteLater();
        } else {
            qDebug () << "ERROR - ResultsMPM::plotSensors - Cannot find the results.zip file in the checked directory: " << plotDir;
        }
    }



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


bool 
ResultsMPM::inputFromJSON(QJsonObject &jsonObject)
{
    // Writes Event load (IMs/EDPs) monitoring options JSON file.
    QJsonArray profiles = jsonObject["particle-sensors"].toArray();
    QJsonArray particleProfiles = jsonObject["particle-sensors"].toArray();
    QJsonArray gridProfiles = jsonObject["grid-sensors"].toArray();
    // QJsonObject resMonitoringJson = jsonObject["resultMonitoring"].toObject();
    // QJsonArray profiles = resMonitoringJson["hydroProfiles"].toArray();
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
            // profileNameU->addItem(profile["name"].toString()); // Wave Profile
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
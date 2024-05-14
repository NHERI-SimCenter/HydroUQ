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

// Written: JustinBonus

#include "SimpleWaves.h"

#include <QVector>
#include <QScrollArea>
#include <QLineEdit>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QJsonObject>
#include <QJsonArray>
#include <QSvgWidget>
#include <QString>
#include <QIcon>
#include <QPixmap>
#include <QToolButton>
#include <QStackedWidget>
// #include "slidingstackedwidget.h"

#include <SC_DoubleLineEdit.h>
#include <SC_IntLineEdit.h>

#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QPhongAlphaMaterial>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DRender/QMesh>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DRender/QCamera>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QEntity>
#include <QQuaternion>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DRender/QAttribute>
#include <Qt3DRender/QBuffer>
#include <Qt3DRender/QGeometry>
#include <Qt3DRender/QGeometryRenderer>


// #include <QOpenGLWidget>
#include "QVector3D"
#include <qcustomplot.h>
#include <QJsonDocument>
#include <QFileDialog>
#include <SectionTitle.h>
#include <QFileInfo>
#include <QMovie>
#include <QPixmap>
#include <RandomVariablesContainer.h>
#include <QRadioButton>
#include <QButtonGroup>
#include <QComboBox>
#include <QSpinBox>
#include <QGroupBox>
#include <QVector>
#include <LineEditRV.h>
#include <QDebug>
#include <SimCenterPreferences.h>
#include <GeneralInformationWidget.h>
#include <QProcess>
#include <QDir>
#include <QTextEdit>
#include <QFormLayout>

#include <QWebEngineView>
#include <QUrl> 
// #include <QWebEngineView>
// #include <QWebEnginePage>
// #include <QWebEngineSettings>
// #include <QWebEngineProfile>
// #include <QWebEngineScriptCollection>
// #include <QWebEngineScript>
// #include <QWebEngineScriptCollection>

// Trying out
// #include <SimCenterAppWidget.h>
// #include <WorkflowAppHydroUQ.h>
// #include <MainWindowWorkflowApp.h>
// #include <HydroEventSelection.h>
// #include <LocalApplication.h>
// #include <RemoteApplication.h>
// #include <RemoteJobManager.h>
// #include <RunWidget.h>
// #include <UQ_EngineSelection.h>
// #include <UQ_Results.h>
// #include <SC_ToolDialog.h>
// #include <SC_RemoteAppTool.h>

// #include <QtSystemDetection>

SimpleWaves::SimpleWaves(RandomVariablesContainer *theRandomVariableIW, QWidget *parent)
    :  SimCenterAppWidget(parent), theRandomVariablesContainer(theRandomVariableIW)
{

}

SimpleWaves::~SimpleWaves()
{

}


void SimpleWaves::executeBackendScript()
{
    //
    //  Update JSON input file and then pass arguments to a python script. Runs script to prepare case directory.
    //  Python scripts hosted remotely by SimCenterBackendApplications/modules/createEVENT/*
    // 

    updateJSON(); 
    QString scriptName = "SimpleWaves.py"; // "setup_case.py";
    QString scriptPath = pyScriptsPath() + QDir::separator() + scriptName; 
    QString templatePath = templateDictDir();
    QString jsonPath = caseDir() + QDir::separator() + "constant" + QDir::separator() + "simCenter" + QDir::separator() + "input";
    QString outputPath = caseDir();
    if (QFileInfo(scriptPath).exists())
    {
      QString program = SimCenterPreferences::getInstance()->getPython();
      QStringList arguments; arguments << scriptPath << jsonPath << templatePath << outputPath;
      QProcess *process = new QProcess(this);
      process->start(program, arguments);
      process->waitForFinished(-1);
      process->close();
    } 
    else 
    {
      qDebug() << "Cannot find the script path: " << scriptPath;
    }
    return;
}

void SimpleWaves::readCaseData()
{
    //Write it to JSON becase it is needed for the mesh generation before the final simulation is run.
    //In future only one JSON file in temp.SimCenter directory might be enough
    QString inputFileName = "SimpleWaves.json";
    QString inputFilePath = caseDir() + QDir::separator() 
                            + "constant" + QDir::separator() 
                            + "simCenter" + QDir::separator() 
                            + "input" + QDir::separator() 
                            + inputFileName;
    QFile jsonFile(inputFilePath);
    if (!jsonFile.open(QFile::ReadOnly | QFile::Text))
    {
      qDebug() << "Cannot find/read input-file path: " << inputFilePath;
      return;
    }

    QString val = jsonFile.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = doc.object();
    inputFromJSON(jsonObject);
    jsonFile.close();
    removeOldFiles();
}

void SimpleWaves::onBrowseCaseDirectoryButtonClicked(void)
{
    // QString fileName = QFileDialog::getExistingDirectory(this, tr("Open Directory"), caseDir(),
    //                                                 QFileDialog::ShowDirsOnly
    //                                                 | QFileDialog::DontResolveSymlinks);
    // QDir newCaseDir(fileName);
    // if (!newCaseDir.exists())
    // {
    //    return;
    // }
    // caseDirectoryPathWidget->setText(fileName);

    // if (!isCaseConfigured())
    // {
    //     setupCase();
    //     return;
    // }

    // // Need to have JSON (SimpleWaves.json) in LocalWorkDir/SimpleWaves/constant/simCenter/input
    // readCaseData();
    // caseDirectoryPathWidget->setText(fileName);
    // return;
}

void SimpleWaves::clear(void)
{

}

bool SimpleWaves::outputCitation(QJsonObject &jsonObject)
{
    QJsonObject citeClaymore;
    QJsonObject citeClaymoreUW;
    
    citeClaymore["citation"] = "Wang, Xinlei and Qiu Yuxing, et al. (2020). “A massively parallel and scalable multi-GPU material point method.”";
    citeClaymore["description"] = "The Multi-GPU Material Point Method software, claymore, which is the predeccesor to ClaymoreUW SimpleWaves. It is a highly optimized C++/CUDA code for explicit MLS-SimpleWaves simulations on multiple NVIDIA GPUs. It is designed primarily for back-end computer graphics usage.";
    citeClaymoreUW["citation"] = "Bonus, Justin (2023). “Evaluation of Fluid-Driven Debris Impacts in a High-Performance Multi-GPU Material Point Method.” PhD thesis, University of Washington, Seattle, WA.";
    citeClaymoreUW["description"] = "The ClaymoreUW Multi-GPU Material Point Method software developed in this PhD thesis is the engineering refactor of the claymore SimpleWaves software. It is a highly optimized C++/CUDA code for explicit MLS-SimpleWaves simulations on multiple NVIDIA GPUs. It features higher computational precision, validated accuracy in multiple debris-fluid-structure interaction problems, new algorithms (ASFLIP, F-Bar antilocking), an expanded user-interface, and improved material behavior.";
    jsonObject["claymore"] = citeClaymore;
    jsonObject["ClaymoreUW"] = citeClaymoreUW;
    return true;
}

bool SimpleWaves::inputFromJSON(QJsonObject &jsonObject)
{
  this->clear();
  
  QString newCaseDirectoryPath(jsonObject["caseDirectoryPath"].toString());

  if (newCaseDirectoryPath.isEmpty()) {
    qDebug() << "SimpleWaves::inputFromJSON: newCaseDirectoryPath is empty in JSON input.";
    return false;
  }

  QDir newCaseDir(newCaseDirectoryPath);
  if (!newCaseDir.exists()) {
    qDebug() << "SimpleWaves::inputFromJSON: newCaseDir does not exist in folder structure: " << newCaseDirectoryPath;
    return false;
  }

  if (newCaseDirectoryPath != caseDirectoryPathWidget->text()) {
    caseDirectoryPathWidget->setText(newCaseDirectoryPath);
  }

  caseDirectoryPathWidget->setText(jsonObject["caseDirectoryPath"].toString());

  return true;
}

bool SimpleWaves::outputToJSON(QJsonObject &jsonObject)
{
  jsonObject["EventClassification"] = "Hydro"; // Important for workflow (Earthquake vs Wind vs Hydro, etc.)
  jsonObject["type"] = "SimpleWaves";

  jsonObject["Application"] = "SimpleWaves"; // For accessing SimCenterBackendApplications/applications/createEVENTS/{Application}/*.py ?
  jsonObject["subtype"] = "SimpleWaves";

  return true;
}

bool SimpleWaves::outputAppDataToJSON(QJsonObject &jsonObject) {

    //
    // Per API, need to add name of application to be called in Application
    // and all data to be used in ApplicationData
    //

    // jsonObject["EventClassification"] = "Hydro";
    // jsonObject["Application"] = "SimpleWaves";
    // QJsonObject dataObj;
    // jsonObject["ApplicationData"] = dataObj;

    // jsonObject["programFile"] = "SimpleWaves"; // <- ClaymoreUW SimpleWaves executable filename on remote machine. Can be changed depending on compiled optimizations, versions, digital twin, etc.
    // jsonObject["maxRunTime"] = "00:05:00"; // <- Maximum run time for the simulation, timeout if exceeded
    return true;
}
bool SimpleWaves::inputAppDataFromJSON(QJsonObject &jsonObject) {

    Q_UNUSED(jsonObject);
    return true;
}


bool SimpleWaves::copyFiles(QString &destDir) {
    //
    //  Copy the files in the case directory to the destination directory
    //  This is the directory where the simulations will be run / staged
    //  Should pull together any files needed for the simulation, e.g. specified input files
    //

    executeBackendScript();
    QString caseName = "SimpleWaves";
    QString destDirCase = destDir + QDir::separator() + caseName;
    QDir destDirCaseDir(destDirCase);
    if (!destDirCaseDir.exists()) 
    {
        destDirCaseDir.mkpath("."); // Make the directory if it doesn't exist
    }
    bool result = this->copyPath(caseDir(), destDirCase, false); // False means don't copy the directory itself, just the contents
    if (!result) 
    {
        QString errorMessage; errorMessage = "SimpleWaves - failed to copy files in: " + caseDir() + " to: " + destDirCase;
        emit sendFatalMessage(errorMessage);
        qDebug() << errorMessage;
        return false;
    }

    //
    //  Copy files from all the major sub-widgets
    //

    if (simpleWavesSettings->copyFiles(destDir) == false) 
    {
      qDebug() << "SimpleWaves - failed to copy settings files";
      return false;
    }
    if (simpleWavesBodies->copyFiles(destDir) == false)
    {
      qDebug() << "SimpleWaves - failed to copy bodies files";
      return false;
    }
    // if (simpleWavesBoundaries->copyFiles(destDir) == false)
    // {
    //   qDebug() << "SimpleWaves - failed to copy boundaries files";
    //   return false;
    // }
    if (simpleWavesSensors->copyFiles(destDir) == false)
    {
      qDebug() << "SimpleWaves - failed to copy sensors files";
      return false;
    }
    if (simpleWavesOutputs->copyFiles(destDir) == false)
    {
      qDebug() << "SimpleWaves - failed to copy outputs files";
      return false;
    }
    // if (simpleWavesResults->copyFiles(destDir) == false)
    // {
    //   qDebug() << "SimpleWaves - failed to copy results files";
    //   return false;
    // }

    return true;
 }


bool SimpleWaves::cleanCase()
{
    // 
    //  Remove the primary folders and log file within the case directory recursively
    // 

    QDir zeroDir(caseDir() + QDir::separator() + "0");
    QDir constDir(caseDir() + QDir::separator() + "constant");
    QDir systemDir(caseDir() + QDir::separator() + "system");
    zeroDir.removeRecursively();
    constDir.removeRecursively();
    systemDir.removeRecursively();
    QFile logFile(caseDir() + QDir::separator() + "log.txt");
    if (logFile.exists()) {
      logFile.remove();
    }
    return true;
}

bool SimpleWaves::removeOldFiles()
{
    //
    // Remove extra files if they exist in case directory's "0" folder
    //
    
    auto removeFile = [this](QString filePath) {
        QFile file(caseDir() + QDir::separator() + "0" + QDir::separator() + filePath);
        if (file.exists()) { 
            qDebug() << "Removing old file: " << filePath;
            file.remove();
        }
    };
    removeFile(caseDir() + QDir::separator() + "0" + QDir::separator() + "oldFile");
    return true;
}

bool SimpleWaves::setupCase()
{
    cleanCase();
    QDir targetDir(caseDir());
    if (!targetDir.exists())
    {
        targetDir.mkpath(caseDir());
    }
    targetDir.mkpath("0");
    targetDir.mkpath("constant");
    targetDir.mkpath("constant/geometry");
    targetDir.mkpath("constant/simCenter");
    targetDir.mkpath("constant/simCenter/output");
    targetDir.mkpath("constant/simCenter/input");
    targetDir.mkpath("constant/boundaryData");
    targetDir.mkpath("constant/boundaryData/inlet");
    targetDir.mkpath("system");

    // Write setup files using the backend python script
    executeBackendScript();
    return true;
}

// From WE-UQ EmptyDomainCFD
QVector<QVector<double>> SimpleWaves::readTxtData(QString fileName)
{
    int colCount  = 0;
    QVector<QVector<double>>  data;
    QFile inputFileTest(fileName);
    if (inputFileTest.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFileTest);

       while (!in.atEnd())
       {
            QString line = in.readLine();
            QStringList  fields = line.split(" ");
            colCount  = fields.size();
            break;
       }
       inputFileTest.close();
    }

    for (int i=0; i < colCount; i++)
    {
        QVector<double> row;
        data.append(row);
    }

    int count  = 0;
    QFile inputFile(fileName);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
            QString line = in.readLine();
            QStringList  fields = line.split(" ");
            for (int i=0; i < colCount; i++)
            {
                data[i].append(fields[i].toDouble());
            }
       }
       inputFile.close();
    }

    return data;
}

bool SimpleWaves::isCaseConfigured()
{
    QDir zeroDir(caseDir() + QDir::separator() +  "0");
    QDir constDir(caseDir() + QDir::separator() + "constant");
    QDir systemDir(caseDir() + QDir::separator() + "system");
    // QFile contrlDict(caseDir() + QDir::separator() + "system" + QDir::separator() + "controlDict");
    // QFile blockDict(caseDir() + QDir::separator() + "system" +  QDir::separator() + "blockMeshDict");
    // QFile snappyDict(caseDir() + QDir::separator() + "system" + QDir::separator() + "snappyHexMeshDict");

    // //Better if we check other files too, for now these are enougg to run a mesh
    // return zeroDir.exists() && constDir.exists() && systemDir.exists() &&
    //        contrlDict.exists() && blockDict.exists() && snappyDict.exists();
    return zeroDir.exists() && constDir.exists() && systemDir.exists();
}

QString SimpleWaves::caseDir()
{
    return caseDirectoryPathWidget->text();
}

QString SimpleWaves::pyScriptsPath()
{
    QString backendAppDir = SimCenterPreferences::getInstance()->getAppDir() + QDir::separator()
             + QString("applications") + QDir::separator() + QString("createEVENT") + QDir::separator()
             + QString("SimpleWaves");

    QString backendAppDir = QString("./") + QDir::separator()
             + QString("SimpleWaves");
    return backendAppDir;
}

// Probably not needed for anything but OpenFOAM
QString SimpleWaves::templateDictDir()
{
    QString templateSubFolder = QString("templateOF10Dicts");// "templateSimpleWavesDicts";
    QString templateDictsDir = SimCenterPreferences::getInstance()->getAppDir() + QDir::separator()
                                + QString("applications") + QDir::separator() 
                                + QString("createEVENT") + QDir::separator()
                                + QString("SimpleWaves") + QDir::separator() 
                                + templateSubFolder;
    return templateDictsDir;
}

QString SimpleWaves::simulationType()
{
    return QString("SimpleWaves"); // Yet to support turbulence models in SimpleWaves, so its just "SimpleWaves" (i.e. DNS)
}

SC_ResultsWidget* SimpleWaves::getResultsWidget(QWidget *parent)
{
  // theTabWidget.setCurrentIndex(theTabWidget.indexOf("Results"));
  // Set theTabWidget to show the "Results" tab using its text
  if (simpleWavesResults)
  {
    theTabWidget->setCurrentIndex(theTabWidget->count() - 1);
  }
  else 
  {
    QWidget* resultsWidget = new QWidget();
    QVBoxLayout* resultsLayout  = new QVBoxLayout();
    resultsWidget->setLayout(resultsLayout);
    simpleWavesResults = new ResultsSimpleWaves(this);

    resultsLayout->addWidget(simpleWavesResults);
    resultsLayout->addStretch();
    theTabWidget->addTab(resultsWidget, QIcon(QString(":/icons/flag-black.svg")), "Results");
    theTabWidget->setCurrentIndex(theTabWidget->count() - 1);
  }  

  statusMessage("HydroUQ EVENTS SimpleWaves - Get results widget for the EVT to allow us to post-process the downloaded results (or locally saved results) for visualization.");
  return simpleWavesResults;
}

void SimpleWaves::importMainDomainJsonFile(QJsonObject &jsonObject)
{
    // openFoamVersion->setCurrentText(jsonObject["OpenFoamVersion"].toString());
    // geometry->inputFromJSON(jsonObject);
    // snappyHexMesh->inputFromJSON(jsonObject);
    // windCharacteristics->inputFromJSON(jsonObject);
    // boundaryConditions->inputFromJSON(jsonObject);
    // turbulenceModeling->inputFromJSON(jsonObject);
    // numericalSetup->inputFromJSON(jsonObject);
}


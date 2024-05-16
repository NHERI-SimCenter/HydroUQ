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

#include <RandomVariablesContainer.h>
#include <LineEditRV.h>
#include <SC_DoubleLineEdit.h>
#include <SC_IntLineEdit.h>
#include <QComboBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

#include <QJsonObject>

#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>

#include <QComboBox>
#include <QDebug>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QLabel>
#include <QSpinBox>
#include <QString>
#include <QVBoxLayout>

#include <RandomVariablesContainer.h>
#include <SimCenterWidget.h>

#include <QComboBox>
#include <QDebug>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QLabel>
#include <QSpinBox>
#include <QString>
#include <QVBoxLayout>
#include <RandomVariablesContainer.h>

// #include <Qt3DExtras/QCuboidMesh>
// #include <Qt3DExtras/QPhongMaterial>
// #include <Qt3DExtras/QPhongAlphaMaterial>
// #include <Qt3DExtras/Qt3DWindow>
// #include <Qt3DRender/QMesh>
// #include <Qt3DExtras/QForwardRenderer>
// #include <Qt3DRender/QCamera>
// #include <Qt3DCore/QTransform>
// #include <Qt3DCore/QEntity>
// #include <QQuaternion>
// #include <Qt3DExtras/QOrbitCameraController>
// #include <Qt3DRender/QAttribute>
// #include <Qt3DRender/QBuffer>
// #include <Qt3DRender/QGeometry>
// #include <Qt3DRender/QGeometryRenderer>


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

// #include <QWebEngineView>
// #include <QUrl> 
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


  
//   caseDirectoryPathWidget = new QLineEdit();

  // Create label and add items to combo box for model selection 
  QLabel* selection_label = new QLabel(tr("Stochastic Loading Model"));
  selection_label->setStyleSheet("font-weight: bold");
  modelSelection = new QComboBox();
  modelSelection->setObjectName("StochasticLoadingModel");
  modelSelection->addItem(tr("Ocean Wave Spectra"));
//   stochasticModel = new WittigSinha(rvInputWidget, this);
  
  // Add widgets to layouts and layouts to this
  QHBoxLayout* model_layout = new QHBoxLayout();

  model_layout->addWidget(modelSelection);
  model_layout->addStretch();



//     // Initialize member variables
  dragCoefficient = new LineEditRV(theRandomVariablesContainer);
  dragCoefficient->setText("2.1");

//   peakPeriod = new LineEditRV(theRandomVariablesContainer);
//   peakPeriod->setText("12.7");

//   significantWaveHeight = new LineEditRV(theRandomVariablesContainer);
//   significantWaveHeight->setText("8.1");

//   waterDepth = new LineEditRV(theRandomVariablesContainer);
//   waterDepth->setText("30.0");

//   recorderOriginX = new LineEditRV(theRandomVariablesContainer);
//   recorderOriginX->setText("0.0");

//   recorderCountZ = new SC_IntLineEdit("recorderCountZ",2);
//     // recorderCountZ->setText("2");

//   timeStep = new LineEditRV(theRandomVariablesContainer);
//   timeStep->setText("0.1");

//   timeDuration = new LineEditRV(theRandomVariablesContainer);
//   timeDuration->setText("3600.0");

//   exposureCategory = new QComboBox();
//   exposureCategory->addItem("JONSWAP");

//   seed = new QSpinBox();
//   seed->setMinimum(1);
//   seed->setMaximum(2147483647);
//   seed->setValue(500);  
//   seed->setEnabled(false);
//   useSeed = new QRadioButton("Provide seed value");
//   useSeed->setChecked(false);

  parametersLayout = new QHBoxLayout();
  QFormLayout *parameters = new QFormLayout();

//   exposureCategory = new QComboBox();
//   exposureCategory->addItem("JONSWAP");
// //   exposureCategory->addItem("Pierson-Moskowitz");

  parameters->addRow(new QLabel("Drag Coefficient"), dragCoefficient);
//   parameters->addRow(new QLabel(tr("Drag Area")), dragArea);
//   parameters->addRow(new QLabel(tr("Peak Period [s]")), peakPeriod);
//   parameters->addRow(new QLabel(tr("Significant Wave Height [m]")), significantWaveHeight);
//   parameters->addRow(new QLabel(tr("Water Depth [m]")), waterDepth);
//   parameters->addRow(new QLabel(tr("Recorder Horizontal Position [m]")), recorderOriginX);
//   parameters->addRow(new QLabel(tr("Wave Spectrum")), exposureCategory);
//     parameters->addRow(new QLabel(tr("Time Step [s]")), timeStep);
//     parameters->addRow(new QLabel(tr("Time Duration [s]")), timeDuration);
    
// //   parameters->addRow(new QLabel(tr("Gust Wind Speed (mph)")), gustWindSpeed);
// //   gustWindSpeed->setToolTip("3 sec gust speed at height of 10m (33ft)");
//   // Add description label
  modelDescription =
      new QLabel(tr("This model provides wind speed time histories using a "
                    "power law for the wind profile based on the ASCE Exposure\n"
                    "Category and a discrete frequency function with FFT to "
                    "account for wind fluctuations (Wittig & Sinha, 1975)"));
  //model_description_->setStyleSheet("QLabel { color : gray; }");

//   // Construct required layouts
// //   QVBoxLayout* mainWindowLayout = new QVBoxLayout();
//   QHBoxLayout* seedLayout = new QHBoxLayout();
// //   QHBoxLayout* parametersLayout = new QHBoxLayout();

//   // Add widgets to layouts and layouts to this
//   seedLayout->addWidget(useSeed);
//   seedLayout->addWidget(seed);
//   seedLayout->addStretch();
QVBoxLayout* internalLayout = new QVBoxLayout();
QHBoxLayout* internalParametersLayout = new QHBoxLayout();
    internalParametersLayout->addLayout(parameters);
// //   parametersLayout->addWidget(stochasticModel);
//   parametersLayout->addStretch();
  // Construct required layouts
internalLayout->addWidget(modelDescription);
internalLayout->addLayout(internalParametersLayout);
// internalLayout->addLayout(seedLayout);
internalLayout->addStretch();

QWidget* internalWidget = new QWidget();
internalWidget->setLayout(internalLayout);

// QScrollArea* scrollArea = new QScrollArea();
// scrollArea->setWidget(internalWidget);
// scrollArea->setWidgetResizable(true);



parametersLayout->addWidget(internalWidget);
parametersLayout->addStretch();

  mainWindowLayout = new QHBoxLayout();
  mainWindowLayout->addWidget(selection_label);
  mainWindowLayout->addLayout(model_layout);
  mainWindowLayout->addLayout(parametersLayout);
//   mainWindowLayout->addLayout(seedLayout);
  mainWindowLayout->addStretch();
  this->setLayout(mainWindowLayout);

//   // Connect slots
//   connect(useSeed, &QRadioButton::toggled, this,
//           &SimpleWaves::provideSeed);

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

    // updateJSON(); 
    // QString scriptName = "SimpleWaves.py"; // "setup_case.py";
    QString scriptName = "Ex4_WaveLoads.py"; // "setup_case.py";
    QString scriptPath = pyScriptsPath() + QDir::separator() + scriptName; 
    QString templatePath = ".";

    

    QString jsonPath = SimCenterPreferences::getInstance()->getLocalWorkDir() + QDir::separator();
    QString outputPath = SimCenterPreferences::getInstance()->getLocalWorkDir()  + QDir::separator(); //+ "output";
    if (QFileInfo(scriptPath).exists())
    {
      QString program = SimCenterPreferences::getInstance()->getPython();
      QStringList arguments; arguments << scriptPath; //<< jsonPath << templatePath << outputPath;
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
    // // Clear all widgets
    // dragCoefficient->clear();
    // dragArea->clear();
    // significantWaveHeight->clear();
    // peakPeriod->clear();
    // waterDepth->clear();
    // recorderOriginX->clear();
    // recorderCountZ->clear();
    // timeStep->clear();
    // timeDuration->clear();
    // seed->clear();
    // useSeed->setChecked(false);
    // exposureCategory->setCurrentIndex(0);
    // return;

}

bool SimpleWaves::outputCitation(QJsonObject &jsonObject)
{
    QJsonObject citeClaymoreUW;
    
    citeClaymoreUW["citation"] = "Bonus, Justin (2023). “Evaluation of Fluid-Driven Debris Impacts in a High-Performance Multi-GPU Material Point Method.” PhD thesis, University of Washington, Seattle, WA.";
    citeClaymoreUW["description"] = "The ClaymoreUW Multi-GPU Material Point Method software developed in this PhD thesis is the engineering refactor of the claymore SimpleWaves software. It is a highly optimized C++/CUDA code for explicit MLS-SimpleWaves simulations on multiple NVIDIA GPUs. It features higher computational precision, validated accuracy in multiple debris-fluid-structure interaction problems, new algorithms (ASFLIP, F-Bar antilocking), an expanded user-interface, and improved material behavior.";
    jsonObject["welib"] = citeClaymoreUW;
    return true;
}

bool SimpleWaves::inputFromJSON(QJsonObject &jsonObject)
{
  this->clear();
  

  if (jsonObject.contains("exposureCategory")) {

      QJsonValue theValue = jsonObject["exposureCategory"];
      if (theValue.isString()) {
	QString exposure  = theValue.toString();
	exposureCategory->setCurrentText(exposure);
      }
  }

    if (jsonObject.contains("seed")) {
        if (jsonObject["seed"].isString()) {
            useSeed->setChecked(false);
        } else {
            useSeed->setChecked(true);
            seed->setValue(jsonObject["seed"].toInt());
        }
    } else {
        useSeed->setChecked(false);
    }

    dragCoefficient->inputFromJSON(jsonObject, QString("dragCoefficient"));
    dragArea->inputFromJSON(jsonObject, QString("dragArea"));
    significantWaveHeight->inputFromJSON(jsonObject, QString("significantWaveHeight"));
    peakPeriod->inputFromJSON(jsonObject, QString("peakPeriod"));
    waterDepth->inputFromJSON(jsonObject, QString("waterDepth"));
    recorderOriginX->inputFromJSON(jsonObject, QString("recorderOriginX"));
    recorderCountZ->inputFromJSON(jsonObject);
    timeStep->inputFromJSON(jsonObject, QString("timeStep"));
    timeDuration->inputFromJSON(jsonObject, QString("timeDuration"));

    // dragCoefficient->inputFromJSON(jsonObject["dragCoefficient"].toObject());
    // dragArea->inputFromJSON(jsonObject["dragArea"].toObject());
    // significantWaveHeight->inputFromJSON(jsonObject["significantWaveHeight"].toObject());
    // peakPeriod->inputFromJSON(jsonObject["peakPeriod"].toObject());
    // waterDepth->inputFromJSON(jsonObject["waterDepth"].toObject());
    // recorderOriginX->inputFromJSON(jsonObject["recorderOriginX"].toObject());
    // recorderCountZ->inputFromJSON(jsonObject["recorderCountZ"].toObject());
    // timeStep->inputFromJSON(jsonObject["timeStep"].toObject());
    // timeDuration->inputFromJSON(jsonObject["timeDuration"].toObject());

  return true;
}

bool SimpleWaves::outputToJSON(QJsonObject &jsonObject)
{




    bool result = true;

    jsonObject["type"] = "SimpleWaves";
    jsonObject["EventClassification"] = "Hydro";
    dragCoefficient->outputToJSON(jsonObject, QString("dragCoefficient"));
    dragArea->outputToJSON(jsonObject, QString("dragArea"));
    significantWaveHeight->outputToJSON(jsonObject, QString("significantWaveHeight"));
    peakPeriod->outputToJSON(jsonObject, QString("peakPeriod"));
    waterDepth->outputToJSON(jsonObject, QString("waterDepth"));
    recorderOriginX->outputToJSON(jsonObject, QString("recorderOriginX"));
    recorderCountZ->outputToJSON(jsonObject);
    timeStep->outputToJSON(jsonObject, QString("timeStep"));
    timeDuration->outputToJSON(jsonObject, QString("timeDuration"));

    jsonObject.insert("exposureCategory",exposureCategory->currentText());

    if (useSeed->isChecked()) {
        jsonObject.insert("seed", seed->value());
    } else {
        jsonObject.insert("seed", "None");
    }
    
    return result;

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

    // executeBackendScript();
    // QString caseName = "SimpleWaves";
    // QString destDirCase = destDir + QDir::separator() + caseName;
    // QDir destDirCaseDir(destDirCase);
    // if (!destDirCaseDir.exists()) 
    // {
    //     destDirCaseDir.mkpath("."); // Make the directory if it doesn't exist
    // }
    // bool result = this->copyPath(caseDir(), destDirCase, false); // False means don't copy the directory itself, just the contents
    // if (!result) 
    // {
    //     QString errorMessage; errorMessage = "SimpleWaves - failed to copy files in: " + caseDir() + " to: " + destDirCase;
    //     emit sendFatalMessage(errorMessage);
    //     qDebug() << errorMessage;
    //     return false;
    // }

    return true;
 }


// bool SimpleWaves::removeOldFiles()
// {
//     //
//     // Remove extra files if they exist in case directory's "0" folder
//     //
    
//     auto removeFile = [this](QString filePath) {
//         QFile file(caseDir() + QDir::separator() + "0" + QDir::separator() + filePath);
//         if (file.exists()) { 
//             qDebug() << "Removing old file: " << filePath;
//             file.remove();
//         }
//     };
//     removeFile(caseDir() + QDir::separator() + "0" + QDir::separator() + "oldFile");
//     return true;
// }

// bool SimpleWaves::setupCase()
// {
//     // cleanCase();
//     QDir targetDir(caseDir());
//     if (!targetDir.exists())
//     {
//         targetDir.mkpath(caseDir());
//     }
//     // targetDir.mkpath("0");
//     // targetDir.mkpath("constant");
//     // targetDir.mkpath("constant/geometry");
//     // targetDir.mkpath("constant/simCenter");
//     // targetDir.mkpath("constant/simCenter/output");
//     // targetDir.mkpath("constant/simCenter/input");
//     // targetDir.mkpath("constant/boundaryData");
//     // targetDir.mkpath("constant/boundaryData/inlet");
//     // targetDir.mkpath("system");

//     // Write setup files using the backend python script
//     executeBackendScript();
//     return true;
// }


// bool SimpleWaves::isCaseConfigured()
// {
//     QDir zeroDir(caseDir() + QDir::separator() +  "0");
//     QDir constDir(caseDir() + QDir::separator() + "constant");
//     QDir systemDir(caseDir() + QDir::separator() + "system");
//     // QFile contrlDict(caseDir() + QDir::separator() + "system" + QDir::separator() + "controlDict");
//     // QFile blockDict(caseDir() + QDir::separator() + "system" +  QDir::separator() + "blockMeshDict");
//     // QFile snappyDict(caseDir() + QDir::separator() + "system" + QDir::separator() + "snappyHexMeshDict");

//     // //Better if we check other files too, for now these are enougg to run a mesh
//     // return zeroDir.exists() && constDir.exists() && systemDir.exists() &&
//     //        contrlDict.exists() && blockDict.exists() && snappyDict.exists();
//     return zeroDir.exists() && constDir.exists() && systemDir.exists();
// }

// QString SimpleWaves::caseDir()
// {
//     caseDirectoryPathWidget->setText(SimCenterPreferences::getInstance()->getLocalWorkDir());

//     return caseDirectoryPathWidget->text();
// }

QString SimpleWaves::pyScriptsPath()
{
    // QString backendAppDir = SimCenterPreferences::getInstance()->getAppDir() + QDir::separator()
    //          + QString("applications") + QDir::separator() + QString("createEVENT") + QDir::separator()
    //          + QString("SimpleWaves");

    QString backendAppDir = QString("./") + QDir::separator();
    return backendAppDir;
}

// // Probably not needed for anything but OpenFOAM
// QString SimpleWaves::templateDictDir()
// {
//     QString templateSubFolder = QString("templateOF10Dicts");// "templateSimpleWavesDicts";
//     QString templateDictsDir = SimCenterPreferences::getInstance()->getAppDir() + QDir::separator()
//                                 + QString("applications") + QDir::separator() 
//                                 + QString("createEVENT") + QDir::separator()
//                                 + QString("SimpleWaves") + QDir::separator() 
//                                 + templateSubFolder;
//     return templateDictsDir;
// }

// QString SimpleWaves::simulationType()
// {
//     return QString("SimpleWaves"); // Yet to support turbulence models in SimpleWaves, so its just "SimpleWaves" (i.e. DNS)
// }

// SC_ResultsWidget* SimpleWaves::getResultsWidget(QWidget *parent)
// {
//   // theTabWidget.setCurrentIndex(theTabWidget.indexOf("Results"));
//   // Set theTabWidget to show the "Results" tab using its text
//   if (simpleWavesResults)
//   {
//     theTabWidget->setCurrentIndex(theTabWidget->count() - 1);
//   }
//   else 
//   {
//     QWidget* resultsWidget = new QWidget();
//     QVBoxLayout* resultsLayout  = new QVBoxLayout();
//     resultsWidget->setLayout(resultsLayout);
//     simpleWavesResults = new ResultsSimpleWaves(this);

//     resultsLayout->addWidget(simpleWavesResults);
//     resultsLayout->addStretch();
//     theTabWidget->addTab(resultsWidget, QIcon(QString(":/icons/flag-black.svg")), "Results");
//     theTabWidget->setCurrentIndex(theTabWidget->count() - 1);
//   }  

//   statusMessage("HydroUQ EVENTS SimpleWaves - Get results widget for the EVT to allow us to post-process the downloaded results (or locally saved results) for visualization.");
//   return simpleWavesResults;
// }



void SimpleWaves::provideSeed(const bool& checked) {
  if (checked) {
    seed->setEnabled(true);
  } else {
    seed->setEnabled(false);
    seed->setValue(500);
  }
}
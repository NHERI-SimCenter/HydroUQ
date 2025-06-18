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

#include "TaichiEvent.h"
#include <QScrollArea>
#include <QLineEdit>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QFrame>
#include <QGroupBox>
#include <QProcess>
#include <QPushButton>
#include <SimCenterPreferences.h>
#include <SC_StringLineEdit.h>
#include <SC_DoubleLineEdit.h>
#include <SC_IntLineEdit.h>
#include <SC_QRadioButton.h>
#include <SC_ComboBox.h>
#include <QGridLayout>
#include <QStackedWidget>
#include <QLabel>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QDir>
#include <QCoreApplication>
#include <CelerisTaichiEvent.h>
#include <CelerisTaichi.h>
#include <CelerisSolver.h>
#include <CelerisDomain.h>
#include <RandomVariablesContainer.h>

CelerisTaichiEvent::CelerisTaichiEvent(RandomVariablesContainer* random_variables, QWidget *parent)
    : SimCenterAppWidget(parent), rvInputWidget(random_variables)
{
    int windowWidth = 1200;

    QWidget     *mainGroup = new QWidget();
    QGridLayout *mainLayout = new QGridLayout();

    QLabel *generalDescriptionLabel = new QLabel("General Event - Celeris Wave-Solver: "
                                                 "\n 1. Select a SimCenter compatible backend application. (Flags: --filenameAIM --filenameEVENT --getRV)"						 
                                                 "\n 2. Choose the Celeris wave-solver's main script."
                                                 "\n 3. Specify the Celeris configuration file."
                                                 "\n 4. Define a bathymetry input file."
                                                 "\n 5. Set a sea-state input file.");



    mainLayout->addWidget(generalDescriptionLabel, 0, 0);

    QTabWidget *theTabWidget = new QTabWidget();
    inputCeleris = new CelerisTaichi();
    theTabWidget->addTab(inputCeleris, "Celeris");

    theCelerisSolver = new CelerisSolver(rvInputWidget);
    theCelerisSolver->setObjectName("Solver");
    theCelerisSolver->setToolTip("Celeris Solver Parameters");
    theTabWidget->addTab(theCelerisSolver, "Solver");

    theCelerisDomain = new CelerisDomain(rvInputWidget);
    theCelerisDomain->setObjectName("Domain");
    theCelerisDomain->setToolTip("Celeris Domain Parameters");
    theTabWidget->addTab(theCelerisDomain, "Domain");

    QWidget *theCelerisBrails = new QWidget();
    QVBoxLayout *theCelerisBrailsLayout = new QVBoxLayout();
    theCelerisBrails->setLayout(theCelerisBrailsLayout);

    
    theCelerisBrailsLayout->addWidget(new QLabel("Celeris-BRAILS Coupling Tool"));
    theCelerisBrailsLayout->addWidget(new QLabel("This tool is used to couple Celeris with BRAILS inventories. It also acquires topo-bathymetry data from NOAA APIs automatically."));
    QStackedWidget *theCelerisBrailsStack = new QStackedWidget();
    QGroupBox *theCelerisBrailsBbox = new QGroupBox("Location Selection");
    QHBoxLayout *theCelerisBrailsBboxLayout = new QHBoxLayout();
    theCelerisBrailsBbox->setLayout(theCelerisBrailsBboxLayout);
    QGroupBox *theCelerisBrailsAddress = new QGroupBox("Location Selection");
    QVBoxLayout *theCelerisBrailsAddressVLayout = new QVBoxLayout();
    theCelerisBrailsAddress->setLayout(theCelerisBrailsAddressVLayout);

    QHBoxLayout *theCelerisBrailsAddressHLayout = new QHBoxLayout();
    QWidget *theCelerisBrailsAddressHWidget = new QWidget();
    theCelerisBrailsAddressHWidget->setLayout(theCelerisBrailsAddressHLayout);

    QWidget *theCelerisBrailsAddressBufferWidget = new QWidget();
    QHBoxLayout *theCelerisBrailsAddressBufferLayout = new QHBoxLayout();
    theCelerisBrailsAddressBufferWidget->setLayout(theCelerisBrailsAddressBufferLayout);

    theCelerisBrailsAddressVLayout->addWidget(theCelerisBrailsAddressHWidget);
    theCelerisBrailsAddressVLayout->addWidget(theCelerisBrailsAddressBufferWidget);

    theCelerisBrailsBboxLayout->addWidget(new QLabel("long1:"));
    SC_DoubleLineEdit *long1Edit = new SC_DoubleLineEdit("long1", -122.34053007546347);
    long1Edit->setToolTip("Longitude 1");
    theCelerisBrailsBboxLayout->addWidget(long1Edit);
    theCelerisBrailsBboxLayout->addWidget(new QLabel("lat1:"));
    SC_DoubleLineEdit *lat1Edit = new SC_DoubleLineEdit("lat1", 37.8992412074125);
    lat1Edit->setToolTip("Latitude 1");
    theCelerisBrailsBboxLayout->addWidget(lat1Edit);
    theCelerisBrailsBboxLayout->addWidget(new QLabel("long2:"));
    SC_DoubleLineEdit *long2Edit = new SC_DoubleLineEdit("long2", -122.32314730065123);
    long2Edit->setToolTip("Longitude 2");
    theCelerisBrailsBboxLayout->addWidget(long2Edit);
    theCelerisBrailsBboxLayout->addWidget(new QLabel("lat2:"));
    SC_DoubleLineEdit *lat2Edit = new SC_DoubleLineEdit("lat2", 37.91514928711621);
    lat2Edit->setToolTip("Latitude 2");
    theCelerisBrailsBboxLayout->addWidget(lat2Edit);

    theCelerisBrailsStack->addWidget(theCelerisBrailsBbox);


    SC_StringLineEdit *addressEdit = new SC_StringLineEdit("address", "Richmond Field Station, Richmond, CA");
    addressEdit->setToolTip("Address for the geocoded location.");
    theCelerisBrailsAddressHLayout->addWidget(new QLabel("Address:"));
    theCelerisBrailsAddressHLayout->addWidget(addressEdit);
    SC_DoubleLineEdit *bufferEdit = new SC_DoubleLineEdit("buffer_radius", 0.01);
    SC_DoubleLineEdit *offsetLatitudeEdit = new SC_DoubleLineEdit("offset_latitude", 0.0);
    SC_DoubleLineEdit *offsetLongitudeEdit = new SC_DoubleLineEdit("offset_longitude", 0.0);
    bufferEdit->setToolTip("Buffer radius in degrees for the geocoded location.");

    

    theCelerisBrailsAddressBufferLayout->addWidget(new QLabel("Buffer Radius (deg):"));
    theCelerisBrailsAddressBufferLayout->addWidget(bufferEdit);
    theCelerisBrailsAddressBufferLayout->addWidget(new QLabel("Offset Longitude (deg):"));
    theCelerisBrailsAddressBufferLayout->addWidget(offsetLongitudeEdit);
    theCelerisBrailsAddressBufferLayout->addWidget(new QLabel("Offset Latitude (deg):"));
    theCelerisBrailsAddressBufferLayout->addWidget(offsetLatitudeEdit);

    theCelerisBrailsStack->addWidget(theCelerisBrailsAddress);

    theCelerisBrailsStack->setCurrentIndex(1); // Default to Address mode
    
    SC_ComboBox *mode = new SC_ComboBox("Mode", QStringList() << "Bounding Box" << "Address");
    mode->setCurrentIndex(1);
    mode->setToolTip("Select the location selection mode for the Celeris-BRAILS coupling tool.");
    theCelerisBrailsLayout->addWidget(mode);

    connect(mode, &QComboBox::currentTextChanged, [=](QString val) {
        if (val == "Bounding Box") {
            qDebug() << "CelerisTaichiEvent::CelerisTaichiEvent: Bounding Box mode selected";
            theCelerisBrailsStack->setCurrentIndex(0);
        }
        else if (val == "Address") {
            qDebug() << "CelerisTaichiEvent::CelerisTaichiEvent: Address mode selected";
            theCelerisBrailsStack->setCurrentIndex(1);
        }
    });

    // SC_QRadioButton *mode = new SC_QRadioButton("Address", "Bounding Box", true);
    // mode->setToolTip("Select the location selection mode for the Celeris-BRAILS coupling tool.");
    // theCelerisBrailsLayout->addWidget(mode);

    // connect(mode, &SC_QRadioButton::radioButtonChanged, this, [=](bool checked) {
    //     if (checked) {
    //         qDebug() << "CelerisTaichiEvent::CelerisTaichiEvent: Address mode selected";
    //         theCelerisBrailsStack->setCurrentIndex(1);
    //     } else {
    //         qDebug() << "CelerisTaichiEvent::CelerisTaichiEvent: Bounding Box mode selected";
    //         theCelerisBrailsStack->setCurrentIndex(0);
    //     }
    // });



    theCelerisBrailsLayout->addWidget(theCelerisBrailsStack);

    QGroupBox *theCelerisBrailsSettings = new QGroupBox("Settings");
    QHBoxLayout *theCelerisBrailsSettingsLayout = new QHBoxLayout();
    theCelerisBrailsSettings->setLayout(theCelerisBrailsSettingsLayout);
    SC_IntLineEdit *resolutionFactorEdit = new SC_IntLineEdit("Resolution", 3.0);
    SC_DoubleLineEdit *scaleFactorEdit = new SC_DoubleLineEdit("Scale", 1.0);
    resolutionFactorEdit->setToolTip("Approximate size of a bathymetry grid-cell that you want to request from the NOAA API. There will be some discrepancy (especially for longitudinal direction) due to the globe's coordinate space. This is used to determine the conversion of latitude degrees to meters.");
    scaleFactorEdit->setToolTip("Upsampling scale factor. This is used to upsample the bathymetry data. E.g., a scale factor of 2 will double the resolution of the bathymetry data retrieved from the NOAA API, while a scale factor of 1 will keep the original resolution.");
    theCelerisBrailsSettingsLayout->addWidget(new QLabel("Approx. Grid-Cell Size (m):"));
    theCelerisBrailsSettingsLayout->addWidget(resolutionFactorEdit);
    theCelerisBrailsSettingsLayout->addWidget(new QLabel("Upsampling Ratio:"));
    theCelerisBrailsSettingsLayout->addWidget(scaleFactorEdit);
    // Move to right side of the layout
    theCelerisBrailsSettingsLayout->addWidget(new QLabel("Include Buildings?"), Qt::AlignRight);
    QCheckBox *enableBrailsCheckBox = new QCheckBox("");
    enableBrailsCheckBox->setChecked(true);
    enableBrailsCheckBox->setToolTip("Enable or disable the coupling with BRAILS inventories. If disabled, the Celeris-BRAILS coupling tool will not retrieve or process BRAILS data.");
    theCelerisBrailsSettingsLayout->addWidget(enableBrailsCheckBox);
    
    theCelerisBrailsLayout->addWidget(theCelerisBrailsSettings);

    QPushButton *runButton = new QPushButton("Run");
    runButton->setToolTip("Run the Celeris-BRAILS coupling tool with the specified parameters.");
    theCelerisBrailsLayout->addWidget(runButton);

    // Vertical space
    theCelerisBrailsLayout->addStretch(1);

    theTabWidget->addTab(theCelerisBrails, "BRAILS");


    auto runWorkflow = [=]() {
      QString pythonScriptName = QCoreApplication::applicationDirPath() + QDir::separator() + "Examples" + QDir::separator() + "Bathymetry" + QDir::separator() + "main.py";
      QString modeChoice = mode->currentText();
      qDebug() << "Python: " << SimCenterPreferences::getInstance()->getPython();
      qDebug() << "Python script: " << pythonScriptName;
      QString long1String = long1Edit->text();
      QString lat1String = lat1Edit->text();
      QString long2String = long2Edit->text();
      QString lat2String = lat2Edit->text();
      QString addressString = addressEdit->text();
      QString modeChoiceSimple = "address";
      QString bufferString = bufferEdit->text();
      QString resolutionFactorString = QString::number(int(111111.0 / (resolutionFactorEdit->text()).toDouble()));
      QString scaleFactorString = scaleFactorEdit->text();
      QString offsetLongitudeString = offsetLongitudeEdit->text();
      QString offsetLatitudeString = offsetLatitudeEdit->text();
      if (modeChoice == "Bounding Box") {
        modeChoiceSimple = "bbox";
        qDebug() << "Mode choice: " << modeChoiceSimple;
        qDebug() << "bbox: " << long1String << lat1String << long2String << lat2String;
      } else if (modeChoice == "Address") {
        modeChoiceSimple = "address";
        qDebug() << "Mode choice: " << modeChoiceSimple;
        qDebug() << "address: " << addressString;
        qDebug() << "buffer: " << bufferString;
      }
      qDebug() << "Resolution factor: " << resolutionFactorString;
      qDebug() << "Scale factor: " << scaleFactorString;

      QString disableBrailsString = "";
      if (!enableBrailsCheckBox->isChecked()) {
        disableBrailsString = "--disable_brails";
        qDebug() << "CelerisTaichiEvent::runWorkflow - Disabling BRAILS coupling.";
      }

      // Launch python script to generate the bathymetry mesh
      QString program = SimCenterPreferences::getInstance()->getPython();
      QStringList args;
      if (modeChoice == "Bounding Box") {
        if (enableBrailsCheckBox->isChecked()) {
          args << pythonScriptName << QString("--mode") << modeChoiceSimple << QString("--bbox") << long1String << lat1String << long2String << lat2String << QString("--resolution_factor") << resolutionFactorString << QString("--scale_factor") << scaleFactorString;
        } else {
          args << pythonScriptName << QString("--mode") << modeChoiceSimple << QString("--bbox") << long1String << lat1String << long2String << lat2String << QString("--resolution_factor") << resolutionFactorString << QString("--scale_factor") << scaleFactorString << disableBrailsString;
        }
      } else if (modeChoice == "Address") {
        if (enableBrailsCheckBox->isChecked()) {
          args << pythonScriptName << QString("--mode") << modeChoiceSimple << QString("--address") << addressString << QString("--buffer") << bufferString << QString("--offset") << offsetLongitudeString << offsetLatitudeString << QString("--resolution_factor") << resolutionFactorString << QString("--scale_factor") << scaleFactorString;
        } else {
          args << pythonScriptName << QString("--mode") << modeChoiceSimple << QString("--address") << addressString << QString("--buffer") << bufferString << QString("--offset") << offsetLongitudeString << offsetLatitudeString << QString("--resolution_factor") << resolutionFactorString << QString("--scale_factor") << scaleFactorString << disableBrailsString;
        }
      }
      qDebug() << "CelerisTaichiEvent::runWorkflow - Running Python script with args: " << args;
      QProcess *process = new QProcess();

      // Catch python print statements and errors and display them in through the qDebug() stream.
      QObject::connect(process, &QProcess::readyRead, [process] () {
          QByteArray aByte = process->readAll();
          qDebug() << aByte;
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
          qDebug() << "CelerisTaichiEvent::runWorkflow - The script has crashed.";
      } 
      else if (process->exitStatus() == QProcess::NormalExit)
      {
          qDebug() << "CelerisTaichiEvent::runWorkflow - The script has finished running.";
      }
      else 
      {
          qDebug() << "CelerisTaichiEvent::runWorkflow - The script has finished running with an unknown exit status.";
      }
      QString p_stdout = process->readAllStandardOutput();
      QString p_stderr = process->readAllStandardError();
      qDebug() << "CelerisTaichiEvent::runWorkflow - Standard Output: " << p_stdout;
      qDebug() << "CelerisTaichiEvent::runWorkflow - Standard Error: " << p_stderr;

      QString configFile = QCoreApplication::applicationDirPath() + QDir::separator() + "Examples" + QDir::separator() + "Bathymetry" + QDir::separator() + "CelerisInit" + QDir::separator() + "config.json";
      QString bathyFile = QCoreApplication::applicationDirPath() + QDir::separator() + "Examples" + QDir::separator() + "Bathymetry" + QDir::separator() + "CelerisInit" + QDir::separator() + "bathy.txt";
      QString wavesFile = QCoreApplication::applicationDirPath() + QDir::separator() + "Examples" + QDir::separator() + "Bathymetry" + QDir::separator() + "CelerisInit" + QDir::separator() + "waves.txt";
      inputCeleris->setConfigFile(configFile);
      inputCeleris->setBathymetryFile(bathyFile);
      inputCeleris->setWavesFile(wavesFile);
    };

    connect(runButton, &QPushButton::clicked, this, runWorkflow);

    mainLayout->addWidget(theTabWidget, 1, 0);
    mainGroup->setLayout(mainLayout);
    mainGroup->setMaximumWidth(windowWidth);
    
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setLineWidth(1);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setWidget(mainGroup);
    scrollArea->setMaximumWidth(windowWidth + 25);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(scrollArea);
    this->setLayout(layout);

    // Listen for any signals from the CelerisTaichi widget called configFileChanged
    // If the config file changes, inputFromJSON
    connect(inputCeleris, &CelerisTaichi::configFileChanged, this, [=]() {
        qDebug() << "CelerisTaichiEvent::CelerisTaichiEvent: config file changed";
        QJsonObject jsonObject;
        this->inputFromConfigJSON(jsonObject);
    });
}


CelerisTaichiEvent::~CelerisTaichiEvent()
{

}


void CelerisTaichiEvent::clear(void)
{

}


bool CelerisTaichiEvent::inputFromJSON(QJsonObject &jsonObject)
{
  this->clear();
  
  inputCeleris->inputFromJSON(jsonObject);
  theCelerisSolver->inputFromJSON(jsonObject);
  theCelerisDomain->inputFromJSON(jsonObject);
  return true;
}

bool CelerisTaichiEvent::inputFromConfigJSON(QJsonObject &jsonObject)
{
  this->clear();
  inputCeleris->inputFromConfigJSON(jsonObject);
  theCelerisSolver->inputFromJSON(jsonObject);
  theCelerisDomain->inputFromJSON(jsonObject);
  return true;
}

bool CelerisTaichiEvent::outputToJSON(QJsonObject &jsonObject)
{
  jsonObject["EventClassification"] = "Hydro";
  jsonObject["type"] = "Celeris";
  jsonObject["subtype"] = "Celeris";
  jsonObject["Application"] = "Celeris";
  inputCeleris->outputToJSON(jsonObject);
  theCelerisSolver->outputToJSON(jsonObject);
  theCelerisDomain->outputToJSON(jsonObject);
  return true;
}

bool CelerisTaichiEvent::outputAppDataToJSON(QJsonObject &jsonObject) {

    //
    // per API, need to add name of application to be called in Application
    // and all data to be used in ApplicationData
    //

    jsonObject["EventClassification"] = "Hydro";
    jsonObject["Application"] = "Celeris";
    QJsonObject dataObj;
    jsonObject["ApplicationData"] = dataObj;

    return true;
}
bool CelerisTaichiEvent::inputAppDataFromJSON(QJsonObject &jsonObject) {

    Q_UNUSED(jsonObject);
    return true;
}


bool CelerisTaichiEvent::copyFiles(QString &destDir) {
  if (inputCeleris->copyFiles(destDir) == false) {
    qDebug() << "Celeris::copyFiles(): Failed to copy Celeris files";
    // return false;
  }
  return true;
}

bool CelerisTaichiEvent::supportsLocalRun() {

  //
  // Allows use on local machines with Taichi Lang installed (python -m pip install taichi)
  //

  return true;
}

bool CelerisTaichiEvent::outputCitation(QJsonObject &jsonObject) {
  QJsonObject citeTaichi;
  QJsonObject citeCeleris;

  citeTaichi["citation"] = "Yuanming Hu (2019). Taichi Lang.";
  citeTaichi["description"] = "HydroUQ applied Taichi for two-way coupled CFD-FEA, developed in this thesis as the Taichi software. It couples Boundaries and Bodies for the simulation of civil engineering structures subject to multi-hazards via the PreCICE coupling library.";
  
  citeCeleris["title"] = "Celeris Base: An interactive and immersive Boussinesq-type nearshore wave simulation software";
  citeCeleris["citation"] = "Sasan Tavakkol and Patrick Lynett (2020). Celeris Base: An interactive and immersive Boussinesq-type nearshore wave simulation software.";
  citeCeleris["description"] = "Celeris Advent enabled researchers and engineers for the first time to simulate nearshore waves with a Boussinesq-type model, faster than real-time and in an interactive environment. However, its development platform and implementation complexity hindered researchers from developing it further and made adding new features to the software a daunting task. The software used graphics shaders to solve scientific equations which could be confusing for many. The visualization environment was wired from scratch which made it very difficult to add features such as virtual reality. Solution method: A new software is developed completely from scratch following Celeris Advent, called Celeris Base. This software uses the same hybrid finite volume–finite difference scheme to solve the extended Boussinesq equations, but using a variant of shaders called compute shaders, removing possible barriers for other researchers to understand the code and develop it further. The software is developed in Unity3D, a popular game engine with a large and helpful community as well as thousands of ready to use plugins. Celeris Base is equipped with virtual reality and is the first nearshore simulation software to provide this feature.";
  citeCeleris["doi"] = "https://doi.org/10.1016/j.cpc.2019.106966.";
  citeCeleris["license"] = "MIT License";
  citeCeleris["keywords"] = "Celeris; Boussinesq; Wave modeling; Immersive; Interactive; GPU";
  citeCeleris["year"] = "2020";
  citeCeleris["author"] = "Sasan Tavakkol and Patrick Lynett";
  citeCeleris["journal"] = "Computer Physics Communications";

  jsonObject["Taichi"] = citeTaichi;
  jsonObject["Celeris"] =  citeCeleris;
  return true;
}
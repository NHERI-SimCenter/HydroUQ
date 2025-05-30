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

// Written: fmckenna

#include "WorkflowAppHydroUQ.h"
#include <MainWindowWorkflowApp.h>
#include <Utils/FileOperations.h>

#include <QPushButton>
#include <QScrollArea>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QLabel>
#include <QDebug>
#include <QMessageBox>

#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>

#include <HydroEventSelection.h>
#include <RunLocalWidget.h>
#include <QProcess>

#include <QCoreApplication>
#include <RemoteService.h>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QHostInfo>
#include <QUuid>
#include <QDir>
#include <QFile>
#include <QSettings>



#include <SimCenterComponentSelection.h>
#include "GeneralInformationWidget.h"
#include <SIM_Selection.h>
#include <RandomVariablesContainer.h>
#include <FEA_Selection.h>
#include <UQ_EngineSelection.h>
#include <UQ_Results.h>
#include <LocalApplication.h>
#include <RemoteApplication.h>
#include <RemoteJobManager.h>
#include <RunWidget.h>
#include <InputWidgetBIM.h>
#include <HydroEDP_Selection.h>
// #include <EDP_Selection.h>


#include "CustomizedItemModel.h"

#include <Utils/ProgramOutputDialog.h>
#include <Utils/RelativePathResolver.h>
#include <GoogleAnalytics.h>

#include <QList>
#include <QMenuBar>

#include <Stampede3Machine.h>
#include <FronteraMachine.h>
#include <SC_ToolDialog.h>
#include <SC_RemoteAppTool.h>
#include <SC_LocalAppTool.h>
#include <RemoteOpenSeesApp.h>
#include <SimCenterPreferences.h>
#include <RemoteAppTest.h>
// #include <DakotaResultsSampling.h>

#include <QtGlobal>
// #include <QSvgWidget>

// EVT classes for standalone tool runs

// HydroUQ original EVT classes from Ajay. Used OpenFOAM with GeoCLAW. TODO: Update OpenFOAM / GeoClaw version and build for TapisV3
#if defined(HYDROUQ_GEOCLAW)
#endif
#include <GeoClawOpenFOAM/GeoClawOpenFOAM.h>
#include <WaveDigitalFlume/WaveDigitalFlume.h>
#include <coupledDigitalTwin/CoupledDigitalTwin.h>
#include <MPM/MPM.h>
#include <MPM/SPH.h>
#include <StochasticWaveModel/include/StochasticWaveInput.h>
#include <TaichiEvent/TaichiEvent.h>
#include <CelerisWebGPU/Celeris.h>
// #include <Celeris/WebGPU.h>
#include <NOAA/DigitalCoast.h>
#include <Utils/FileOperations.h>

// static pointer for global procedure set in constructor
static WorkflowAppHydroUQ *theApp = 0;

// global procedure
int getNumParallelTasks() {
    return theApp->getMaxNumParallelTasks();
}

WorkflowAppHydroUQ::WorkflowAppHydroUQ(RemoteService *theService, QWidget *parent)
    : WorkflowAppWidget(theService, parent)
{
    // set static pointer for global procedure
    theApp = this;

    //
    // create the various widgets
    //

    theRVs = RandomVariablesContainer::getInstance();
    theGI = GeneralInformationWidget::getInstance();
    theSIM = new SIM_Selection(true, true);
    theEventSelection = new HydroEventSelection(theRVs, theService);
    // theEventSelection = new HydroEventSelection(theRVs, theGI);
    theAnalysisSelection = new FEA_Selection(true);
    theUQ_Selection = new UQ_EngineSelection(ForwardReliabilitySensitivitySurrogate); // ForwardReliabilitySensitivitySurrogate
    theEDP_Selection = new HydroEDP_Selection(theRVs);
    theResults = theUQ_Selection->getResults();

    //
    // Set workflow scripts
    //
    TapisMachine *theMachine = new FronteraMachine();
    localApp = new LocalApplication("sWHALE.py");
    remoteApp = new RemoteApplication("sWHALE.py", theService, theMachine, nullptr);


    //QStringList filesToDownload; filesToDownload << "inputRWHALE.json" << "input_data.zip" << "Results.zip";
    theJobManager = new RemoteJobManager(theService);

    SimCenterWidget *theWidgets[1];// =0;
    theRunWidget = new RunWidget(localApp, remoteApp, theWidgets, 0);

    //
    // connect signals and slots for (1) local and (2) remote application runs.
    //

    connect(localApp, &Application::setupForRun, this, [this](QString &workingDir, QString &subDir) 
    {
        currentApp = localApp;
        setUpForApplicationRun(workingDir, subDir);
    });
    connect(localApp, SIGNAL(processResults(QString&)), this, SLOT(processResults(QString&)));
    connect(localApp, SIGNAL(runComplete()), this, SLOT(runComplete())); // swao with next?
    connect(localApp,SIGNAL(sendErrorMessage(QString)),
	    this,SLOT(errorMessage(QString)));
    connect(localApp,SIGNAL(sendStatusMessage(QString)),
	    this,SLOT(statusMessage(QString)));
    connect(localApp,SIGNAL(sendFatalMessage(QString)),
	    this,SLOT(fatalMessage(QString)));
    

    connect(remoteApp, &Application::setupForRun, this, [this](QString &workingDir, QString &subDir) 
    {
        currentApp = remoteApp;
        setUpForApplicationRun(workingDir, subDir);
    });
    connect(remoteApp, SIGNAL(successfullJobStart()), theRunWidget, SLOT(hide()));;
    connect(remoteApp, SIGNAL(successfullJobStart()), this, SLOT(runComplete()));
    connect(remoteApp,SIGNAL(sendErrorMessage(QString)),
	    this,SLOT(errorMessage(QString)));
    connect(remoteApp,SIGNAL(sendStatusMessage(QString)),
	    this,SLOT(statusMessage(QString)));
    connect(remoteApp,SIGNAL(sendFatalMessage(QString)),
	    this,SLOT(fatalMessage(QString)));        
    
    connect(theJobManager, SIGNAL(processResults(QString&)), this, SLOT(processResults(QString&)));
    connect(theJobManager, SIGNAL(loadFile(QString&)), this, SLOT(loadFile(QString&)));
    connect(theJobManager, SIGNAL(closeDialog()), this, SLOT(runComplete()));
    connect(theJobManager,SIGNAL(sendErrorMessage(QString)),
	    this,SLOT(errorMessage(QString)));
    connect(theJobManager,SIGNAL(sendStatusMessage(QString)),
	    this,SLOT(statusMessage(QString)));
    connect(theJobManager,SIGNAL(sendFatalMessage(QString)),
	    this,SLOT(fatalMessage(QString)));
    
    connect(this, SIGNAL(setUpForApplicationRunDone(QString&, QString &)), theRunWidget, SLOT(setupForRunApplicationDone(QString&, QString &)));    

    connect(theService, SIGNAL(closeDialog()), this, SLOT(runComplete()));

    // KZ connect queryEVT and the reply
    connect(theUQ_Selection, SIGNAL(queryEVT()), theEventSelection, SLOT(replyEventType()));
    connect(theEventSelection, SIGNAL(typeEVT(QString)), theUQ_Selection, SLOT(setEventType(QString)));    

    //
    // create layout to hold component selection
    //

    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    horizontalLayout->setMargin(0);
    this->setLayout(horizontalLayout);

    //
    // create the component selection & add the components to it
    //

    theComponentSelection = new SimCenterComponentSelection();
    horizontalLayout->addWidget(theComponentSelection);
    horizontalLayout->setAlignment(Qt::AlignLeft);
    theComponentSelection->addComponent(QString("UQ"),  theUQ_Selection);
    theComponentSelection->addComponent(QString("GI"),  theGI);
    theComponentSelection->addComponent(QString("SIM"), theSIM);
    theComponentSelection->addComponent(QString("EVT"), theEventSelection);
    theComponentSelection->addComponent(QString("FEM"), theAnalysisSelection);
    theComponentSelection->addComponent(QString("EDP"), theEDP_Selection); // Using EDP_HydroSelection
    theComponentSelection->addComponent(QString("RV"),  theRVs);
    theComponentSelection->addComponent(QString("RES"), theResults);
    
    theComponentSelection->displayComponent("EVT"); // Initial page on startup
    
    //
    // set the defults in the General Info
    //

    theGI->setDefaultProperties(1,144,360,360,37.8715,-122.2730); // Berkeley, kips and inches

    // access a web page which will increment the usage count for this tool
    // manager = new QNetworkAccessManager(this);
    // connect(manager, SIGNAL(finished(QNetworkReply*)),
    //         this, SLOT(replyFinished(QNetworkReply*)));
    // manager->get(QNetworkRequest(QUrl("http://opensees.berkeley.edu/OpenSees/developer/eeuq/use.php"))); // EE-UQ?


    ProgramOutputDialog *theDialog=ProgramOutputDialog::getInstance();
    theDialog->appendInfoMessage("Welcome to HydroUQ");

    // load example
    QString pathToExample = QCoreApplication::applicationDirPath() + QDir::separator() + "Examples" + QDir::separator() + "hdro-0002" + QDir::separator() + "src" + QDir::separator() + "input.json";
    if (QFile::exists(pathToExample))
    this->loadFile(pathToExample);
    //loadExample(pathToExample); // - jb
}

// JB - Update franks way to a function later
// void WorkflowAppHydroUQ::loadExample(QString path) {
//     if (QFile::exists(path))
//     this->loadFile(path);
// }

// Development mode for tools
constexpr bool DEV_MODE = false; // Set to true for development mode, false for production mode

// Quickly enable/disable tools here for compile-time
constexpr bool USE_CLAYMORE_TOOL = true;
constexpr bool USE_MPM_EVENT_TOOL = true;
constexpr bool USE_NOAA_TOOL = DEV_MODE; 
constexpr bool USE_TAICHI_TOOL = false;
constexpr bool USE_CELERIS_TOOL = false;
constexpr bool USE_WEBGPU_TOOL = false;
constexpr bool USE_OPENSEES_TOOL = true;

void
WorkflowAppHydroUQ::setMainWindow(MainWindowWorkflowApp* window) {

    this->WorkflowAppWidget::setMainWindow(window); // Call the parent class's function, which sets the main window

    auto menuBar = theMainWindow->menuBar();

    //
    // Add a Tool option to menu bar & add options to it
    //

    QMenu *toolsMenu = new QMenu(tr("&Tools"), menuBar);
    SC_ToolDialog *theToolDialog = new SC_ToolDialog(this);

    //
    // Add standalone events to tools menu
    //
    QString appName;
    QList<QString> queues; 


    if constexpr (USE_CLAYMORE_TOOL) {
        // #define MPM_WAVEGENERATION_NO_PLOT // Define this to disable the plot in the MPM Wave Generation tool
        MPM *miniMPM = new MPM(theRVs);
        if (!miniMPM->isInitialize()) {
            miniMPM->initialize();
        }

        if constexpr (DEV_MODE) {
            appName = "simcenter-claymore-ls6"; // Lonestar6 dev app for ClaymoreUW MPM, Justin Bonus (bonusj) 
            queues << "gpu-a100-dev"; // These are later changed to "normal" and "fast" in the tool based on number of cores/processors? Should fix this
        } else {
            appName = "simcenter-claymore-ls6"; // Lonestar6 public app for ClaymoreUW MPM
            queues << "gpu-a100"; // These are later changed to "normal" and "fast" in the tool based on number of cores/processors? Should fix this
        }
        // QString appVersion = "1.0.0";
        // QString machine = "lonestar6"; // "ls6";
        QString appVersion = "1.0.1";
        QString machine = "ls6"; // "ls6";
        SC_RemoteAppTool *miniMPMTool = new SC_RemoteAppTool(appName, appVersion, machine, queues, theRemoteService, miniMPM, theToolDialog); // lonestar6
        // delete miniMPM; // Clean up the MPM object after creating the tool?
        
        theToolDialog->addTool(miniMPMTool, "Digital Flume (MPM)");
        QAction *showMPM = toolsMenu->addAction("Digital Flume (&MPM)");
        connect(showMPM, &QAction::triggered, this,[this, theDialog=theToolDialog, miniM = miniMPMTool] {
            theDialog->showTool("Digital Flume (MPM)");
        });
    
        // currentTool = miniMPMTool; // TODO: Make this more dynamics / use a better interface
    }

    if constexpr (USE_TAICHI_TOOL) {
        queues.clear(); queues << "rtx" << "rtx-dev"; // These are later changed to "normal" and "fast" in the tool based on number of cores/processors? Should fix this
        TaichiEvent *miniTaichi = new TaichiEvent();
        appName =  "simcenter-taichi-frontera"; // Frontera
        QString appVersion = "1.0.0";
        QString machine = "frontera";
        SC_RemoteAppTool *miniTaichiTool = new SC_RemoteAppTool(appName, appVersion, machine, queues, theRemoteService, miniTaichi, theToolDialog);
        theToolDialog->addTool(miniTaichiTool, "General Event (Taichi)");
        QAction *showTaichi = toolsMenu->addAction("General Event (&Taichi)");  
        connect(showTaichi, &QAction::triggered, this,[this, theDialog=theToolDialog, miniT = miniTaichiTool] {
            theDialog->showTool("General Event (Taichi)");
        });

    }


    if constexpr (USE_NOAA_TOOL) {
        DigitalCoast *miniDC = new DigitalCoast();
        QString appNameDC =  "noaa-digital-coast-localhost"; // Frontera
        QString appVersion = "1.0.0";
        QString machine = "localhost";
        queues.clear(); queues << "chromium"; // These are later changed to "normal" and "fast" in the tool based on number of cores/processors? Should fix this
        SC_RemoteAppTool *miniDCTool = new SC_RemoteAppTool(appNameDC, appVersion, machine, queues, theRemoteService, miniDC, theToolDialog);
        theToolDialog->addTool(miniDCTool, "Sea-Level Rise (NOAA Digital Coast)");
        QAction *showDC = toolsMenu->addAction("Sea-Level Rise (&NOAA Digital Coast)");
        connect(showDC, &QAction::triggered, this,[this, theDialog=theToolDialog, miniD = miniDCTool] {
            theDialog->showTool("Sea-Level Rise (NOAA Digital Coast)");
        });
    }

    if constexpr (USE_OPENSEES_TOOL) {
        // opensees@designsafe  
        RemoteOpenSeesApp *theOpenSeesApp = new RemoteOpenSeesApp();
        QString testAppName = "simcenter-opensees-frontera";
        QString testAppVersion = "1.0.0";
        TapisMachine *theMachine = new Stampede3Machine();
        SC_RemoteAppTool *theOpenSeesTool = new SC_RemoteAppTool(testAppName,
                                    testAppVersion,
                                    theMachine,
                                    theRemoteService,
                                    theOpenSeesApp,
                                    theToolDialog);
        QStringList filesToDownload; filesToDownload << "results.zip";
        theOpenSeesTool->setFilesToDownload(filesToDownload, false);
        theOpenSeesTool->setAppNameReport(QString("OpenSeesAtDesignSafe"));
        
                        
        
        theToolDialog->addTool(theOpenSeesTool, "OpenSees@DesignSafe");
        QAction *showOpenSees = toolsMenu->addAction("&OpenSees@DesignSafe");
        connect(showOpenSees, &QAction::triggered, this,[this, theDialog=theToolDialog, theEmp = theOpenSeesApp] {
            theDialog->showTool("OpenSees@DesignSafe");
        });

    }
    // if constexpr (USE_CELERIS_TOOL) {
    //     Celeris *miniCeleris = new Celeris();
    //     QString appNameCeleris =  "simcenter-celeris-frontera"; // Frontera
    //     QString systemNameCeleris = "frontera";
    //     QString appVersion = "1.0.0";
    //     QString machine = "frontera";      
    //     QList<QString> queuesCeleris; queuesCeleris << "rtx" << "rtx-dev"; // These are later changed to "normal" and "fast" in the tool based on number of cores/processors? Should fix this
    //     SC_RemoteAppTool *miniCelerisTool = new SC_RemoteAppTool(appNameCeleris, appVersion, machine, queuesCeleris, theRemoteService, miniCeleris, theToolDialog);
    //     theToolDialog->addTool(miniCelerisTool, "Boussinesq Waves (Celeris)");
    //     QAction *showCeleris = toolsMenu->addAction("Boussinesq Waves (&Celeris)");
    //     connect(showCeleris, &QAction::triggered, this,[this, theDialog=theToolDialog, miniC = miniCelerisTool] {
    //         theDialog->showTool("Boussinesq Waves (Celeris)");
    //     });
    // }

    // if constexpr (USE_WEBGPU_TOOL) {
    //     WebGPU *miniWebGPU = new WebGPU();
    //     QString appNameWebGPU =  "WebGPU-1.0.0"; // Frontera
    //     QString systemNameWebGPU = "frontera";
    //     QList<QString> queuesWebGPU; queuesWebGPU << "rtx" << "rtx-dev"; // These are later changed to "normal" and "fast" in the tool based on number of cores/processors? Should fix this
    //     SC_RemoteAppTool *miniWebGPUTool = new SC_RemoteAppTool(appNameWebGPU, queuesWebGPU, theRemoteService, miniWebGPU, theToolDialog);
    //     theToolDialog->addTool(miniWebGPUTool, "Trouble-Shoot WebGPU (Hardware Acceleration)");
    //     QAction *showWebGPU = toolsMenu->addAction("Trouble-Shoot &WebGPU (Hardware Acceleration)");
    //     connect(showWebGPU, &QAction::triggered, this,[this, theDialog=theToolDialog, miniW = miniWebGPUTool] {
    //         theDialog->showTool("Trouble-Shoot WebGPU (Hardware Acceleration)");
    //     });
    // }


    /*
    RemoteAppTest *theTest = new RemoteAppTest();
    QString appNameTest = "remoteAppTest-1.0.0";
    QList<QString> queuesTest; queuesTest << "normal" << "fast";
    SC_RemoteAppTool *theTestTool = new SC_RemoteAppTool(appNameTest, queuesTest, theRemoteService, theTest, theToolDialog);
    theToolDialog->addTool(theTestTool, "Build and Run MPI Program");
    QAction *showTest = toolsMenu->addAction("&Build and Run MPI Program");
    connect(showTest, &QAction::triggered, this,[this, theDialog=theToolDialog, theEmp = theTestTool] {
        theDialog->showTool("Build and Run MPI Program");
    });  
    */


    //
    // Add Tools to menu bar
    //

    QAction* menuAfter = nullptr;
    foreach (QAction *action, menuBar->actions()) {
        // First check for an examples menu and if that does not exist put it before the help menu
        auto actionText = action->text();
        if(actionText.compare("&Examples") == 0)
        {
            menuAfter = action;
            break;
        }
        else if(actionText.compare("&Help") == 0)
        {
            menuAfter = action;
            break;
        }
    }
    menuBar->insertMenu(menuAfter, toolsMenu);    



    // TODO - Make this a bit more dynamic, use bibtex, and consider swapping tools in and out automaticlly
    // This outputs citations, makes it easy for people to add their own 
    // to tools and have them grouped for output with the rest

    auto prefs = SimCenterPreferences::getInstance();
    

    // defaultWorkDir = QDir(stringLocalWorkDir);
    QString localWorkDirString = prefs->getLocalWorkDir();

    QDir localWorkDir(localWorkDirString);
    if (!localWorkDir.exists()) {
        localWorkDir.mkpath(localWorkDirString);
    }

    QString tmpDirName = QString("tmp.SimCenter");
    QString tmpDirectoryString = localWorkDir.absoluteFilePath(tmpDirName);
    QDir tmpDirectory(tmpDirectoryString);
    if (tmpDirectory.exists()) {
        if (SCUtils::isSafeToRemoveRecursivily(tmpDirectoryString))      
            tmpDirectory.removeRecursively();
        else {
            QString msg("The Program stopped, it was about to recursivily remove: ");
            msg += tmpDirName;
            fatalMessage(msg);
            return;	
        }      
    }
    
    tmpDirectory.mkpath(tmpDirectoryString);
    tmpDirectory.mkdir(defaultSubDir);
    defaultWorkDir = QDir(tmpDirectoryString);

    QString templateDirectoryString = tmpDirectory.absoluteFilePath(defaultSubDir); // "templatedir" by default
    QDir templateDirectory(templateDirectoryString);
    if (templateDirectory.exists()) {
        templateDirectory.removeRecursively();
    } else {
        templateDirectory.mkpath(templateDirectoryString);
    }

    
    // connect(theToolDialog, SIGNAL(toolSelected(QString)), this, SLOT(toolSelected(QString)));
    QJsonObject citations;
    QString localCiteFile = templateDirectoryString + QDir::separator() + tr("tool_cite.json");    
    // QString citeFile = destinationDirectory.filePath("please_cite.json"); // file getting deleted
    currentTool = nullptr;
    this->createToolCitation(citations, localCiteFile);
    // }

    /**
    QString remoteWorkDirString = prefs->getRemoteWorkDir();
    QDir remoteWorkDir(remoteWorkDirString);
    if (!remoteWorkDir.exists()) {
        remoteWorkDir.mkpath(remoteWorkDirString);
    }
    QString tmpDirName = QString("tmp.SimCenter");
    remoteWorkDir.mkdir(tmpDirName); // defaultWorkDirString should start as "tmp.SimCenter"
    {
        QString tmpDirectoryString = remoteWorkDir.absoluteFilePath(tmpDirName);
        QDir tmpDirectory(tmpDirectoryString);
        if (tmpDirectory.exists()) {
            tmpDirectory.removeRecursively();
        } else {
            tmpDirectory.mkpath(tmpDirectoryString);
        }
        tmpDirectory.mkdir(defaultSubDir);
        defaultWorkDir = QDir(tmpDirectoryString);

        QString templateDirectoryString = tmpDirectory.absoluteFilePath(defaultSubDir); // "templatedir" by default
        QDir templateDirectory(templateDirectoryString);
        if (templateDirectory.exists()) {
            templateDirectory.removeRecursively();
        } else {
            templateDirectory.mkpath(templateDirectoryString);
        }

        QJsonObject citations;
        QString remoteCiteFile = templateDirectoryString + QDir::separator() + tr("tool_cite.json");
        this->createToolCitation(citations, remoteCiteFile);
    }
    **/

    // json.insert("citations",citations);

}


// WorkflowAppHydroUQ::toolSelected(QString toolName) {
//     if (currentTool != nullptr) {
//         currentTool->hide();
//     }
//     currentTool = theToolDialog->getTool(toolName);
//     currentTool->show();
// }


WorkflowAppHydroUQ::~WorkflowAppHydroUQ()
{
    // hack to get around a sometimes occuring seg fault
    // as some classes in destructor remove RV from the RVContainer
    // which may already have been destructed .. so removing so no destructor called

    //    QWidget *newUQ = new QWidget();
    //    theComponentSelection->swapComponent("RV",newUQ);
}


void WorkflowAppHydroUQ::replyFinished(QNetworkReply *pReply)
{
    Q_UNUSED(pReply);
    return;
}


bool WorkflowAppHydroUQ::canRunLocally()
{
    // From old HydroUQ, assumes no local run and only checks event app
    // TODO: Look into local run 
    // QMessageBox msgBox;
    // msgBox.setText("The current workflow cannot run locally, please run at DesignSafe instead.");
    // msgBox.exec();
    // return false;

    QList<SimCenterAppWidget*> apps({theEventSelection, theEDP_Selection, theSIM});

    foreach(SimCenterAppWidget* app, apps)
    {
        if(!app->supportsLocalRun())
        {
            theRunWidget->close();
            QMessageBox msgBox;
            msgBox.setText("The current workflow cannot run locally, please run at DesignSafe instead.");
            msgBox.exec();
            return false;
        }
    }
    return true;
}


bool
WorkflowAppHydroUQ::outputToJSON(QJsonObject &jsonObjectTop) {

    //
    // get each of the main widgets to output themselves
    //
  
    bool result = true;
    QJsonObject apps;

    //
    // get each of the main widgets to output themselves to top 
    // and workflow widgets to output appData to apps
    //

    // theGI
    QJsonObject jsonObjGenInfo;
    result = theGI->outputToJSON(jsonObjGenInfo);
    if (result == false)
        { this->errorMessage("ERROR: WorkflowAppHydroUQ::outputToJSON() theGI->outputToJSON() returned false!"); return result; }
    jsonObjectTop["GeneralInformation"] = jsonObjGenInfo;

    // theRVs
    result = theRVs->outputToJSON(jsonObjectTop);
    if (result == false)
        { this->errorMessage("ERROR: WorkflowAppHydroUQ::outputToJSON() theRVs->outputToJSON() returned false!"); return result; }

    // theEDP
    QJsonObject jsonObjectEDP;
    result = theEDP_Selection->outputToJSON(jsonObjectEDP);
    if (result == false)
        { this->errorMessage("ERROR: WorkflowAppHydroUQ::outputToJSON() theEDP_Selection->outputToJSON() returned false!"); return result; }
    jsonObjectTop["EDP"] = jsonObjectEDP;

    QJsonObject appsEDP;
    result = theEDP_Selection->outputAppDataToJSON(appsEDP);
    if (result == false)
        { this->errorMessage("ERROR: WorkflowAppHydroUQ::outputToJSON() theEDP_Selection->outputAppDataToJSON() returned false!"); return result; }
    apps["EDP"]=appsEDP;

    // theUQ
    result = theUQ_Selection->outputAppDataToJSON(apps);
    if (result == false)
        { this->errorMessage("ERROR: WorkflowAppHydroUQ::outputToJSON() theUQ_Selection->outputAppDataToJSON() returned false!"); return result; }
    
    result = theUQ_Selection->outputToJSON(jsonObjectTop);
    if (result == false)
        { this->errorMessage("ERROR: WorkflowAppHydroUQ::outputToJSON() theUQ_Selection->outputToJSON() returned false!"); return result; }

    // theSIM
    result = theSIM->outputAppDataToJSON(apps);
    if (result == false)
        { this->errorMessage("ERROR: WorkflowAppHydroUQ::outputToJSON() theSIM->outputAppDataToJSON() returned false!"); return result; }

    result = theSIM->outputToJSON(jsonObjectTop);
    if (result == false)
        { this->errorMessage("ERROR: WorkflowAppHydroUQ::outputToJSON() theSIM->outputToJSON() returned false!"); return result; }

    // theAnalysis
    result = theAnalysisSelection->outputAppDataToJSON(apps);
    if (result == false)
        { this->errorMessage("ERROR: WorkflowAppHydroUQ::outputToJSON() theAnalysisSelection->outputAppDataToJSON() returned false!"); return result; }

    result = theAnalysisSelection->outputToJSON(jsonObjectTop);
    if (result == false)
        { this->errorMessage("ERROR: WorkflowAppHydroUQ::outputToJSON() theAnalysisSelection->outputToJSON() returned false!"); return result; }

    // theEventSelection
    // NOTE: Events treated differently, due to array nature of objects
    result = theEventSelection->outputToJSON(jsonObjectTop);
    if (result == false)
        { this->errorMessage("ERROR: WorkflowAppHydroUQ::outputToJSON() theEventSelection->outputToJSON() returned false!"); return result; }

    result = theEventSelection->outputAppDataToJSON(apps);
    if (result == false)
        { this->errorMessage("ERROR: WorkflowAppHydroUQ::outputToJSON() theEventSelection->outputAppDataToJSON() returned false!"); return result; }


    // theRunWidget
    result = theRunWidget->outputToJSON(jsonObjectTop);
    if (result == false)
        { this->errorMessage("ERROR: WorkflowAppHydroUQ::outputToJSON() theRunWidget->outputToJSON() returned false!"); return result; }

    // theResults
    // sy - to save results
    result = theResults->outputToJSON(jsonObjectTop);
    if (result == false)
        { this->errorMessage("ERROR: WorkflowAppHydroUQ::outputToJSON() theResults->outputToJSON() returned false!"); return result; }

    jsonObjectTop["Applications"]=apps;

    QJsonObject defaultValues;
    defaultValues["workflowInput"]=QString("scInput.json");    
    defaultValues["filenameAIM"]=QString("AIM.json");
    defaultValues["filenameEVENT"] = QString("EVENT.json");
    defaultValues["filenameSAM"]= QString("SAM.json");
    defaultValues["filenameEDP"]= QString("EDP.json");
    defaultValues["filenameSIM"]= QString("SIM.json");
    defaultValues["driverFile"]= QString("driver");
    defaultValues["filenameDL"]= QString("BIM.json");
    defaultValues["workflowOutput"]= QString("EDP.json");
    QJsonArray rvFiles, edpFiles;
    rvFiles.append(QString("AIM.json"));
    rvFiles.append(QString("SAM.json"));
    rvFiles.append(QString("EVENT.json"));
    rvFiles.append(QString("SIM.json"));
    edpFiles.append(QString("EDP.json"));
    defaultValues["rvFiles"]= rvFiles;
    defaultValues["edpFiles"]=edpFiles;
    jsonObjectTop["DefaultValues"]=defaultValues;

    return result;
}


void 
WorkflowAppHydroUQ::processResults(QString &dirName)
{
    //
    // get results widget for currently selected UQ option
    //

    theResults = theUQ_Selection->getResults();
    if (theResults == NULL) {
        this->errorMessage("FATAL - UQ option selected not returning results widget");
        return;
    }

    //
    // connect signals for results widget
    //

    //   connect(theResults,SIGNAL(sendStatusMessage(QString)), this,SLOT(statusMessage(QString)));
    //   connect(theResults,SIGNAL(sendErrorMessage(QString)), this,SLOT(errorMessage(QString)));
    
    
    //
    // swap current results with existing one in selection & disconnect signals
    //

    QWidget *oldResults = theComponentSelection->swapComponent(QString("RES"), theResults);
    if (oldResults != NULL) {
        this->statusMessage("WorkflowAppHydroUQ::processResults() - Deleting oldResults");
        delete oldResults;
    }
    // if (oldResults != NULL && oldResults != theResults) {;
    //     this->errorMessage("WorkflowAppHydroUQ::processResults() - Deleting oldResults");
    //     // disconnect(oldResults,SIGNAL(sendErrorMessage(QString)), this,SLOT(errorMessage(QString)));
    //     // disconnect(oldResults,SIGNAL(sendFatalMessage(QString)), this,SLOT(fatalMessage(QString)));  
    //     delete oldResults;
    // }

    //
    // process results
    // 

    theResults->processResults(dirName);
    // theRunWidget->hide(); // Hide the run widget after the results are processed, as the results are now displayed
    theComponentSelection->displayComponent("RES");
}

void
WorkflowAppHydroUQ::clear(void)
{
    // EE-UQ
    theGI->clear();
    theSIM->clear();

    // /*******************************************
    // Needed?
    theRVs->clear();
    theUQ_Selection->clear();
    theEventSelection->clear();
    theAnalysisSelection->clear();

    // Function theUQ_Selection->getResults returns UQ simulation results to the theResults from a "Workflow" perspective. I.e., it will host the results after retrieving the data from a completed workflow simulation on a remote HPC system (or local if that is implemented). It won't contain the results from an "individual" app/tool perspective, i.e. if just EVT is ran to perform a normal CFD simulation, the results will be in the EVT app in its own results widget. Depending on the EVT implementation, this widget can be theResults if it is "passed" to it. (JB)
    theResults=theUQ_Selection->getResults();
    if (theResults == NULL) {
        this->errorMessage("FATAL - UQ option selected not returning results widget");
        return; 
    }

    //
    // swap current results with existing one in selection & disconnect signals
    //

    QWidget *oldResults = theComponentSelection->swapComponent(QString("RES"), theResults); // The "swap" takes care of deleting the oldResults widget that was swapped out from theComponentSelection. theResults is the new widget that was swapped in and is now owned by theComponentSelection. oldResults is the old widget that was swapped out and is now owned by this function so it needs to be deleted, though smart pointers could take care of this if we refactor the code to use them.
    if (oldResults != NULL && oldResults != theResults) {
        this->statusMessage("WorkflowAppHydroUQ::clear() - Deleting oldResults");
        delete oldResults;
    }

    //
    // ready to process results
    //
    // *******************************************/
} 

bool
WorkflowAppHydroUQ::inputFromJSON(QJsonObject &jsonObject)
{
    //
    // get each of the main widgets to input themselves
    //

    if (jsonObject.contains("GeneralInformation")) {
        QJsonObject jsonObjGeneralInformation = jsonObject["GeneralInformation"].toObject();
        if (theGI->inputFromJSON(jsonObjGeneralInformation) == false) {
            this->errorMessage("Hydro_UQ: failed to read GeneralInformation");
        }
    } else {
        this->errorMessage("Hydro_UQ: failed to find GeneralInformation");
        return false;
    }

    if (jsonObject.contains("Applications")) {

        QJsonObject theApplicationObject = jsonObject["Applications"].toObject();

        // note: Events is different because the object is an Array
        if (theApplicationObject.contains("Events")) {
            //  QJsonObject theObject = theApplicationObject["Events"].toObject(); it is null object, actually an array
            if (theEventSelection->inputAppDataFromJSON(theApplicationObject) == false) {
                this->errorMessage("Hydro_UQ: found Events in Applications but failed to read");
            }

        } else {
            this->errorMessage("Hydro_UQ: failed to find Events in Applications");
            return false;
        }

        if (theUQ_Selection->inputAppDataFromJSON(theApplicationObject) == false)
            this->errorMessage("Hydro_UQ: failed to read UQ application");

        if (theSIM->inputAppDataFromJSON(theApplicationObject) == false)
            this->errorMessage("Hydro_UQ: failed to read SIM application");
    
        if (theAnalysisSelection->inputAppDataFromJSON(theApplicationObject) == false)
            this->errorMessage("Hydro_UQ: failed to read FEM application");

        if (theApplicationObject.contains("EDP")) {
            QJsonObject theObject = theApplicationObject["EDP"].toObject();
            if (theEDP_Selection->inputAppDataFromJSON(theObject) == false) {
                this->errorMessage("Hydro_UQ: failed to read EDP application");
            }
        } else {
            this->errorMessage("Hydro_UQ: failed to find EDP application");
            return false;
        }
    } else {
        this->errorMessage("WorkflowAppHydroUQ::inputFromJSON failed to find Applications in JSON");
        return false;
    }

    /*
    ** Note to me - RVs and Events treated differently as both use arrays .. rethink API!
    */

    theEventSelection->inputFromJSON(jsonObject);
    theRVs->inputFromJSON(jsonObject);
    theRunWidget->inputFromJSON(jsonObject);

    if (jsonObject.contains("EDP")) {
        QJsonObject edpObj = jsonObject["EDP"].toObject();
        if (theEDP_Selection->inputFromJSON(edpObj) == false)
            this->errorMessage("Hydro_UQ: failed to read EDP data");
    } else {
        this->errorMessage("Hydro_UQ: failed to find EDP data");
        return false;
    }
    if (theUQ_Selection->inputFromJSON(jsonObject) == false) {
       this->errorMessage("Hydro_UQ: failed to read UQ Method data");
    } 
    if (theSIM->inputFromJSON(jsonObject) == false) {
        this->errorMessage("Hydro_UQ: failed to read SIM Modeling Method data");
    }
    if (theAnalysisSelection->inputFromJSON(jsonObject) == false) {
        this->errorMessage("Hydro_UQ: failed to read FEM Analysis Method data");
    }

    // Below allows users to load in existing results from a previous run / example. Appear in RES tab.
    // sy - to display results
    auto *theNewResults = theUQ_Selection->getResults();
    if (theNewResults->inputFromJSON(jsonObject) == false) {
        this->errorMessage("Hydro_UQ: failed to read RES Method data");
    }
    theResults->setResultWidget(theNewResults);
    this->statusMessage("WorkflowAppHydroUQ::inputFromJSON - Done Loading File");
    return true;  


    // I guess below is incorrect? Above was from WE-UQ's refactor Sep 14 and May 2, 2022
    // ---
    // if (theUQ_Selection->inputFromJSON(jsonObject) == false)
    //    this->errorMessage("Hydro_UQ: failed to read UQ Method data");

    // if (theAnalysisSelection->inputFromJSON(jsonObject) == false)
    //     this->errorMessage("Hydro_UQ: failed to read FEM Method data");

    // if (theSIM->inputFromJSON(jsonObject) == false)
    //     this->errorMessage("Hydro_UQ: failed to read SIM Method data");

    // this->statusMessage("WorkflowAppHydroUQ::inputFromJSON - Done Loading File");
    // return true;  
    // ---

}


void
WorkflowAppHydroUQ::onRunButtonClicked() {
    emit errorMessage("");
    if (!canRunLocally())
        emit errorMessage("HydroUQ cannot be run locally yet. Please run remotely on DesignSafe.");
    else
    {
        theRunWidget->hide();
        theRunWidget->setMinimumWidth(this->width()*0.5);
        theRunWidget->showLocalApplication();
        GoogleAnalytics::ReportLocalRun();
    }
}

void
WorkflowAppHydroUQ::onRemoteRunButtonClicked(){
    emit errorMessage("");

    bool loggedIn = theRemoteService->isLoggedIn();

    if (loggedIn == true) {
        theRunWidget->hide();
        theRunWidget->setMinimumWidth(this->width()*0.5);
        theRunWidget->showRemoteApplication();

    } else {
        errorMessage("ERROR - You Need to Login to DesignSafe to Run HydroUQ Remotely.");
    }

    GoogleAnalytics::ReportDesignSafeRun();
}

void
WorkflowAppHydroUQ::onRemoteGetButtonClicked(){

    emit errorMessage("");

    bool loggedIn = theRemoteService->isLoggedIn();

    if (loggedIn == true) {

        theJobManager->hide();
        theJobManager->updateJobTable("");
        theJobManager->show();

    } else {
        errorMessage("ERROR - You Need to Login to DesignSafe to Get HydroUQ Results From Remote Storage.");
    }
}

void
WorkflowAppHydroUQ::onExitButtonClicked(){

}

void
WorkflowAppHydroUQ::setUpForApplicationRun(QString &workingDir, QString &subDir) {

    // errorMessage(""); // I dont think we need this? Will clutter up any error counting tool. - JB

    //
    // create temporary directory in working dir
    // and copy all files needed to this directory by invoking copyFiles() on app widgets
    //

    // designsafe will need a unique name
    /* *********************************************
    will let ParallelApplication rename dir
    QUuid uniqueName = QUuid::createUuid();
    QString strUnique = uniqueName.toString();
    strUnique = strUnique.mid(1,36);
    QString tmpDirName = QString("tmp.SimCenter") + strUnique;
    *********************************************** */

    QString tmpDirName = QString("tmp.SimCenter");
    qDebug() << "TMP_DIR: " << tmpDirName;
    QDir workDir(workingDir);

    QString tmpDirectory = workDir.absoluteFilePath(tmpDirName);
    qDebug() << "tmpDirectory: " << tmpDirectory;
    
    QDir destinationDirectory(tmpDirectory);


    if (destinationDirectory.exists()) {
        qDebug() << "Destination Directory Exists, trying to remove it";
        if (SCUtils::isSafeToRemoveRecursivily(tmpDirectory)) {
            qDebug() << "Removing Destination Directory Recursivily";
            destinationDirectory.removeRecursively();
        }
        else {
            QString msg("The Program stopped, it was about to recursivily remove: ");
            msg.append(tmpDirectory);
            fatalMessage(msg);
        }
    }
    // Used in other places temporarily, 
    // e.g. citation output for Tools to avoid passing parameters
    defaultWorkDir = destinationDirectory;
    defaultSubDir = subDir;

    qDebug() << "defaultWorkDir: " << defaultWorkDir;
    qDebug() << "defaultSubDir: " << defaultSubDir;

    destinationDirectory.mkpath(tmpDirectory);
    QString templateDirectory  = destinationDirectory.absoluteFilePath(subDir);
    qDebug() << "templateDirectory: " << templateDirectory;
    destinationDirectory.mkpath(templateDirectory);




    // copyPath(path, tmpDirectory, false);
    if (theSIM->copyFiles(templateDirectory) == false) {
      errorMessage("Workflow Failed to start as SIM failed in copyFiles");
      return;
    } else {
      qDebug() << "SIM copyFiles() successful";
    }
    if (theEventSelection->copyFiles(templateDirectory) == false) {
      errorMessage("Workflow Failed to start as EVENT failed in copyFiles");
      return;
    } else {
      qDebug() << "EVENT copyFiles() successful";
    }

    if (theAnalysisSelection->copyFiles(templateDirectory) == false) {
      errorMessage("Workflow Failed to start as FEM failed in copyFiles");
      return;
    } else {
      qDebug() << "FEM copyFiles() successful";
    }
    if (theUQ_Selection->copyFiles(templateDirectory) == false) {
        errorMessage("Workflow Failed to start as UQ failed in copyFiles");
        return;
    } else {
        qDebug() << "UQ copyFiles() successful";
    }
    if (theEDP_Selection->copyFiles(templateDirectory) == false) {
        errorMessage("Workflow Failed to start as EDP failed in copyFiles");
        return;
    } else {
        qDebug() << "EDP copyFiles() successful";
    }

    //
    // in new templatedir dir save the UI data into dakota.json or scInput.json file (same result as using saveAs)
    // NOTE: we append object workingDir to this which points to template dir
    //

    QString inputFile = templateDirectory + QDir::separator() + tr("scInput.json");
    qDebug() << "inputFile: " << inputFile;


    QFile file(inputFile);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        //errorMessage();
        qDebug() << "ERROR - FATAL - WorkflowAppHydroUQ::setUpForApplicationRun failed to open file for writing";
        return;
    }
    QJsonObject json;
    bool validOutput = this->outputToJSON(json);
    if (!validOutput) 
    {
        errorMessage("ERROR - FATAL - WorkflowAppHydroUQ::setUpForApplicationRun receieved outputToJSON() as false");
        return;
    }
    json["runDir"]=tmpDirectory;
    json["WorkflowType"]="Building Simulation";


    QJsonDocument doc(json);
    file.write(doc.toJson());
    file.close();
    QJsonArray events = json["Applications"].toObject()["Events"].toArray();

    bool hasMPMEvent = false;
    bool hasCFDEvent = false;
    QJsonObject eventAppData;
    for (QJsonValueRef eventJson: events)
    {
        qDebug() << "WorkflowAppHydroUQ::setUpForApplicationRun - Found Event in Events with Application: " << eventJson.toObject()["Application"].toString();
        QString eventApp = eventJson.toObject()["Application"].toString();
        if(0 == eventApp.compare("MPM", Qt::CaseSensitivity::CaseInsensitive))
        {
            qDebug() << "WorkflowAppHydroUQ::setUpForApplicationRun - Found Application MPM in Events, attaching AppData";
            eventAppData = eventJson.toObject()["ApplicationData"].toObject();
            hasMPMEvent = true;
            break;
        }
        else if (0 == eventApp.compare("CFDEvent", Qt::CaseSensitivity::CaseInsensitive))
        {
            qDebug() << "WorkflowAppHydroUQ::setUpForApplicationRun - Found Application CFDEvent in Events, attaching AppData";
            eventAppData = eventJson.toObject()["ApplicationData"].toObject();
            hasCFDEvent = true;
            break;
        }
    }
    if (hasMPMEvent == false)
        qDebug() << "WorkflowAppHydroUQ::setUpForApplicationRun - No MPM Event found in Events, continuing";
    if (hasCFDEvent == false)
        qDebug() << "WorkflowAppHydroUQ::setUpForApplicationRun - No CFDEvent Event found in Events, continuing";
    
    RemoteApplication* remoteApplication = static_cast<RemoteApplication*>(remoteApp);


    if (currentApp == remoteApp)
    {
        remoteApplication->clearExtraInputs();
        remoteApplication->clearExtraParameters();
        qDebug() << "WorkflowAppHydroUQ::setUpForApplicationRun - Running Remotely. Cleared extra inputs and parameters key-value pairs for the JSON submission payload to the tapis application";
    }
    else
    {
        if (!canRunLocally()) {
            qDebug() << "WorkflowAppHydroUQ::setUpForApplicationRun - Cannot run locally, returning";
            return;
        }
    }

    if (hasMPMEvent) 
    {
        QMap<QString, QString> extraFileInputs;
        QMap<QString, QString> extraParameters;
        // Adding extra job inputs for MPM
        // QMap<QString, QString> extraInputs;
        // if(eventAppData.contains("MPMCase"))
        //     extraInputs.insert("MPMCase", eventAppData["MPMCase"].toString());
        // remoteApplication->setExtraInputs(extraInputs);

        // QStringList requiredFileInputs = {"dataDirectory"};
        // QStringList defaultFileInputs = {"bonusj/mpm-public-ls6"};
        // for (auto reqInput : requiredFileInputs)
        // {
        //     if (eventAppData.contains(reqInput))
        //     {
        //         if (eventAppData[reqInput].isString() && !eventAppData[reqInput].toString().isEmpty()) {
        //             extraFileInputs.insert(reqInput, eventAppData[reqInput].toString());
        //             continue;
        //         }
        //         else if (eventAppData[reqInput].isDouble()) {
        //             extraFileInputs.insert(reqInput, QString::number(eventAppData[reqInput].toDouble()));
        //             continue;
        //         }
        //         else if (eventAppData[reqInput].isBool()) {
        //             if (eventAppData[reqInput].toBool())
        //                 extraFileInputs.insert(reqInput, "true");
        //             else
        //                 extraFileInputs.insert(reqInput, "false");
        //             continue;
        //         }
        //     }
        //     auto defaultInput = defaultFileInputs[requiredFileInputs.indexOf(reqInput)];
        //     qDebug() << "WorkflowAppHydroUQ::setUpForApplicationRun - Added default '" << reqInput << "' to parameters: " << defaultInput;
        //     extraFileInputs.insert(reqInput, defaultInput);
        // }
        // dataInput["sourceUrl"]   = "tapis://" + QString("designsafe.storage.default/") + QString("bonusj/mpm-public-ls6");
        // QJsonObject dataPathInput;
        // dataInput["sourceUrl"]   = QString("tapis://designsafe.storage.default/bonusj/mpm-public-ls6");
        // dataInput["targetPath"]  = "*";
        // dataInput["envKey"] = "dataDirectory";
        // fileInputs.append(data);
        // fileInputs contains and array of json object which hold "sourceUrl", "targetPath", "envKey" 

        // if (eventAppData.contains("fileInputs")) {
        //     qDebug() << "WorkflowAppHydroUQ::setUpForApplicationRun - Added custom 'fileInputs' to parameters: " << eventAppData["fileInputs"].toArray();
        //     if (eventAppData["fileInputs"].toArray().size() > 0)
        //     {
        //         QJsonArray fileInputs = eventAppData["fileInputs"].toArray();
        //         for (auto fileInput : fileInputs)
        //         {
        //             auto fileInputObj = fileInput.toObject();
        //             if (fileInputObj.contains("envKey") && fileInputObj.contains("sourceUrl") && fileInputObj.contains("targetPath"))
        //             {
        //                 extraFileInputs.insert("envKey", fileInputObj["envKey"].toString());
        //                 extraFileInputs.insert("sourceUrl", fileInputObj["sourceUrl"].toString());
        //                 extraFileInputs.insert("targetPath", fileInputObj["targetPath"].toString());
        //             }
        //         }
        //     }
        // }

        // extraFileInputs.insert("envKey", "dataDirectory");
        // extraFileInputs.insert("sourceUrl", "tapis://designsafe.storage.default/bonusj/mpm-public-ls6");
        // extraFileInputs.insert("targetPath", "*");
        

        // Adding extra job parameters for MPM, already has "driverFile", "errorFile", "inputFile", "outputFile"
        QStringList requiredEnvVars = {"publicDirectory", "programFile", "defaultMaxRunTime", "maxRunTime"};
        QStringList defaultEnvVars = {"./", "osu_lwf", "1440", "120"};
        for (auto reqVar : requiredEnvVars)
        {
            if (eventAppData.contains(reqVar))
            {
                if (eventAppData[reqVar].isString() && !eventAppData[reqVar].toString().isEmpty()) {
                    extraParameters.insert(reqVar, eventAppData[reqVar].toString());
                    continue;
                }
                else if (eventAppData[reqVar].isDouble()) {
                    extraParameters.insert(reqVar, QString::number(eventAppData[reqVar].toDouble()));
                    continue;
                }
                else if (eventAppData[reqVar].isBool()) {
                    if (eventAppData[reqVar].toBool())
                        extraParameters.insert(reqVar, "true");
                    else
                        extraParameters.insert(reqVar, "false");
                    extraParameters.insert(reqVar, eventAppData[reqVar].toString());
                    continue;
                }
            }
            auto defaultVar = defaultEnvVars[requiredEnvVars.indexOf(reqVar)];
            qDebug() << "WorkflowAppHydroUQ::setUpForApplicationRun - Added default '" << reqVar << "' to parameters: " << defaultVar;
            extraParameters.insert(reqVar, defaultVar);
        }
        
        
        // if (eventAppData.contains("driverFile")) {
        //     qDebug() << "WorkflowAppHydroUQ::setUpForApplicationRun - Added custom 'driverFile' to parameters: " << eventAppData["driverFile"].toString();
        //     extraParameters.insert("driverFile", eventAppData["driverFile"].toString());
        // } else {
        //     auto defaultMPMCase = "driver";
        //     qDebug() << "WorkflowAppHydroUQ::setUpForApplicationRun - Added default 'driverFile' to parameters: " << defaultMPMCase;
        //     extraParameters.insert("driverFile", defaultMPMCase);
        // }

        // if (eventAppData.contains("inputFile")) {
        //     qDebug() << "WorkflowAppHydroUQ::setUpForApplicationRun - Added custom 'inputFile' to parameters: " << eventAppData["inputFile"].toString();
        //     extraParameters.insert("inputFile", eventAppData["inputFile"].toString());
        // } else {
        //     auto defaultErrorFile = "scInput.json";
        //     qDebug() << "WorkflowAppHydroUQ::setUpForApplicationRun - Added default 'inputFile' to parameters: " << defaultErrorFile;
        //     extraParameters.insert("inputFile", defaultErrorFile);
        // }


        // if (eventAppData.contains("publicDirectory")) {
        //     qDebug() << "WorkflowAppHydroUQ::setUpForApplicationRun - Added custom 'publicDirectory' to parameters: " << eventAppData["publicDirectory"].toString();
        //     extraParameters.insert("publicDirectory", eventAppData["publicDirectory"].toString());
        // } else {
        //     auto defaultPublicDirectory = "../mpm-public-ls6";
        //     qDebug() << "WorkflowAppHydroUQ::setUpForApplicationRun - Added default 'publicDirectory' to parameters: " << defaultPublicDirectory;
        //     extraParameters.insert("publicDirectory", defaultPublicDirectory);
        // }

        // if (eventAppData.contains("programFile")) {
        //     qDebug() << "WorkflowAppHydroUQ::setUpForApplicationRun - Added custom 'programFile' to parameters: " << eventAppData["programFile"].toString();
        //     extraParameters.insert("programFile", eventAppData["programFile"].toString());
        // } else {
        //     auto defaultProgramFile = "fbar";
        //     qDebug() << "WorkflowAppHydroUQ::setUpForApplicationRun - Added default 'programFile' to parameters: " << defaultProgramFile;
        //     extraParameters.insert("programFile", defaultProgramFile);
        // }
        // if (eventAppData.contains("defaultMaxRunTime")) {
        //     qDebug() << "WorkflowAppHydroUQ::setUpForApplicationRun - Added custom 'defaultMaxRunTime' to parameters: " << eventAppData["defaultMaxRunTime"].toString();
        //     extraParameters.insert("defaultMaxRunTime", eventAppData["defaultMaxRunTime"].toString());
        // } else {
        //     auto defaultMaxRunTime = "1440"; 
        //     qDebug() << "WorkflowAppHydroUQ::setUpForApplicationRun - Added default 'defaultMaxRunTime' to parameters: " << defaultMaxRunTime;
        //     extraParameters.insert("defaultMaxRunTime", defaultMaxRunTime);  // Include max run time for MPM application, TODO: move into the remote application class so we may set it through the pop-up remote app window
        // }

        // if (eventAppData.contains("maxRunTime")) {
        //     qDebug() << "WorkflowAppHydroUQ::setUpForApplicationRun - Added custom 'maxRunTime' to parameters: " << eventAppData["maxRunTime"].toString();
        //     extraParameters.insert("maxRunTime", eventAppData["maxRunTime"].toString());
        // } else {
        //     auto defaultMaxRunTime = "120"; 
        //     qDebug() << "WorkflowAppHydroUQ::setUpForApplicationRun - Added default 'maxRunTime' to parameters: " << defaultMaxRunTime;
        //     extraParameters.insert("maxRunTime", defaultMaxRunTime);  // Include max run time for MPM application, TODO: move into the remote application class so we may set it through the pop-up remote app window
        // }


        // if (eventAppData.contains("maxMinutes")) {
        //     qDebug() << "WorkflowAppHydroUQ::setUpForApplicationRun - Added custom 'maxMinutes' to parameters: " << eventAppData["maxMinutes"].toString();
        //     extraParameters.insert("maxMinutes", eventAppData["maxMinutes"].toString());
        // } else {
        //     auto defaultMaxRunTime = "120"; 
        //     qDebug() << "WorkflowAppHydroUQ::setUpForApplicationRun - Added default 'maxMinutes' to parameters: " << defaultMaxRunTime;
        //     extraParameters.insert("maxMinutes", defaultMaxRunTime);  // Include max run time for MPM application, TODO: move into the remote application class so we may set it through the pop-up remote app window
        // }

        remoteApplication->setExtraParameters(extraParameters);
        // remoteApplication->setExtraInputs(extraFileInputs);


        // else {
        //     qDebug() << "WorkflowAppHydroUQ::setUpForApplicationRun - No MPM Event found in Events, continuing";
        //     QMap<QString, QString> extraParameters;
        //     auto defaultMaxRunTime = "02:00:00";
        //     extraParameters.insert("maxRunTime", defaultMaxRunTime);  // Include max run time for MPM application, TODO: move into the remote application class so we may set it through the pop-up remote app window
        //     remoteApplication->setExtraParameters(extraParameters);
        // }
    } 

    if (hasCFDEvent)
    {
        // Adding extra job inputs for CFD
        QMap<QString, QString> extraInputs;
        if(eventAppData.contains("OpenFOAMCase"))
            extraInputs.insert("OpenFOAMCase", eventAppData["OpenFOAMCase"].toString());
        remoteApplication->setExtraInputs(extraInputs);

        // Adding extra job parameters for CFD
        QMap<QString, QString> extraParameters;
        if(eventAppData.contains("OpenFOAMSolver"))
            extraParameters.insert("OpenFOAMSolver", eventAppData["OpenFOAMSolver"].toString());
        remoteApplication->setExtraParameters(extraParameters);
    }
    
    // This outputs citations, makes it easy for people to add their own 
    // to tools and have them grouped for output with the rest
    QJsonObject citations;
    QString citeFile = templateDirectory + QDir::separator() + tr("please_cite.json");    
    // QString citeFile = destinationDirectory.filePath("please_cite.json"); // file getting deleted
    this->createCitation(citations, citeFile);
    // json.insert("citations",citations);

    // statusMessage("Set-Up Done .. Now Starting HydroUQ Application");
    qDebug() << "WorkflowAppHydroUQ::setUpForApplicationRun - Set-Up Done .. Now Starting HydroUQ Application";
    qDebug() << "WorkflowAppHydroUQ::setUpForApplicationRun - Emitting setUpForApplicationRunDone( " << tmpDirectory << ", " << inputFile << " )";
    emit setUpForApplicationRunDone(tmpDirectory, inputFile);
    return;
}

int
WorkflowAppHydroUQ::loadFile(QString &fileName){

    //
    // open file
    //

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        emit errorMessage(QString("ERROR: WorkflowAppHydroUQ::loadFile() Could Not Open File: ") + fileName);
        return -1; 
    }

    //
    // place contents of file into json object
    //

    QString val;
    val=file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObj = doc.object();

    // close file
    file.close();

    //Resolve absolute paths from relative ones
    QFileInfo fileInfo(fileName);
    SCUtils::ResolveAbsolutePaths(jsonObj, fileInfo.dir());
    
    //
    // clear current and input from new JSON
    //

    this->clear();
    bool result = this->inputFromJSON(jsonObj);
    
    if (result == false)
      return -1;
    else
      return 0;
}

int
WorkflowAppHydroUQ::getMaxNumParallelTasks() {
    return theUQ_Selection->getNumParallelTasks();
}

int
WorkflowAppHydroUQ::createCitation(QJsonObject &citation, QString citeFile) {

    QString cit("{\"HydroUQ\": { \"citations\": [{\"citation\": \"Justin Bonus, Frank McKenna, Nicolette Lewis, Ajay B Harish, & Pedro, A. (2025). NHERI-SimCenter/HydroUQ: Version 4.1.0 (v4.1.0). Zenodo. https://doi.org/10.5281/zenodo.15319477\",\"description\": \"This is the overall tool reference used to indicate the version of the tool.\"},{\"citation\": \"Gregory G. Deierlein, Frank McKenna, Adam Zsarnóczay, Tracy Kijewski-Correa, Ahsan Kareem, Wael Elhaddad, Laura Lowes, Matthew J. Schoettler, and Sanjay Govindjee (2020) A Cloud-Enabled Application Framework for Simulating Regional-Scale Impacts of Natural Hazards on the Built Environment. Frontiers in the Built Environment. 6:558706. doi: 10.3389/fbuil.2020.558706\",\"description\": \" This marker paper describes the SimCenter application framework, which was designed to simulate the impacts of natural hazards on the built environment. It is a necessary attribute for publishing work resulting from the use of SimCenter tools, software, and datasets.\"}]}}");

    QJsonDocument docC = QJsonDocument::fromJson(cit.toUtf8());
    if(!docC.isNull()) {
        if (docC.isObject()) {
            citation = docC.object();        
        } else {
            qDebug() << "WorkflowAppHydro citation text is not valid JSON: \n" << cit << Qt::endl;
        }
    }
    // theGI->outputCitation(citation);
    theSIM->outputCitation(citation);
    theEventSelection->outputCitation(citation);
    theAnalysisSelection->outputCitation(citation);
    theUQ_Selection->outputCitation(citation);
    theEDP_Selection->outputCitation(citation);
    //   theRVs->outputCitation(citation);
    //   theRunWidget->outputCitation(citation);

    // write the citation to a citeFile if provided
  
    if (!citeFile.isEmpty()) {
        
        QFile file(citeFile);
        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            errorMessage(QString("WorkflowAppHydroUQ::writeCitation - could not open read-only file ") + citeFile);
            //  progressDialog->hideProgressBar(); // Not in HydroUQ currently
            return 0;
        }

        QJsonDocument doc(citation);
        file.write(doc.toJson());
        file.close();
    }
  
    return 0;    
}

int
WorkflowAppHydroUQ::createToolCitation(QJsonObject &citation, QString citeFile) {

    if (currentTool == nullptr) {
        // errorMessage("WorkflowAppHydroUQ::createToolCitation - currentTool is nullptr");
        return 0;
    }

    QString cit("{\"HydroUQ\": { \"citations\": [{\"citation\": \"Frank McKenna, Justin Bonus, Ajay B Harish, & Nicolette Lewis. (2024). NHERI-SimCenter/HydroUQ: Version 3.2.0 (v3.2.0). Zenodo. https://doi.org/10.5281/zenodo.4731073\",\"description\": \"This is the overall tool reference used to indicate the version of the tool.\"},{\"citation\": \"Gregory G. Deierlein, Frank McKenna, Adam Zsarnóczay, Tracy Kijewski-Correa, Ahsan Kareem, Wael Elhaddad, Laura Lowes, Matthew J. Schoettler, and Sanjay Govindjee (2020) A Cloud-Enabled Application Framework for Simulating Regional-Scale Impacts of Natural Hazards on the Built Environment. Frontiers in the Built Environment. 6:558706. doi: 10.3389/fbuil.2020.558706\",\"description\": \" This marker paper describes the SimCenter application framework, which was designed to simulate the impacts of natural hazards on the built environment. It is a necessary attribute for publishing work resulting from the use of SimCenter tools, software, and datasets.\"}]}}");

    QJsonDocument docC = QJsonDocument::fromJson(cit.toUtf8());
    if(!docC.isNull()) {
        if (docC.isObject()) {
            citation = docC.object();        
        }  else {
            qDebug() << "WorkflowAppHydro citation text is not valid JSON: \n" << cit << Qt::endl;
        }
    }

    if (currentTool) {
        currentTool->outputCitation(citation);
    }


    // write the citation to a citeFile if provided

    if (citeFile.isEmpty()) {
        errorMessage(QString("WorkflowAppHydroUQ::createToolCitation - no citeFile provided for the currentTool's citation"));
        return 0;
    }

    QFile file(citeFile);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        errorMessage(QString("WorkflowAppHydroUQ::createToolCitation - could not open read-only file ") + citeFile);
        // progressDialog->hideProgressBar(); // Not in HydroUQ currently
        return 0;
    }

    QJsonDocument doc(citation);
    file.write(doc.toJson());
    file.close();
    

    return 0;    
}

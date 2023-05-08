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
#include <QPushButton>
#include <QScrollArea>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QLabel>
#include <QDebug>
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

#include <SimCenterComponentSelection.h>
#include "GeneralInformationWidget.h"
#include <SIM_Selection.h>
#include <RandomVariablesContainer.h>
#include <FEA_Selection.h>
#include <QDir>
#include <QFile>
#include <UQ_EngineSelection.h>
#include <LocalApplication.h>
#include <RemoteApplication.h>
#include <RemoteJobManager.h>
#include <RunWidget.h>
#include <InputWidgetBIM.h>
#include <UQ_EngineSelection.h>
#include <UQ_Results.h>

#include <EDP_Selection.h>

#include "CustomizedItemModel.h"

#include <QSettings>
#include <QUuid>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QHostInfo>

#include <GoogleAnalytics.h>

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
    theSIM = new SIM_Selection(false, false);
    theEventSelection = new HydroEventSelection(theRVs, theGI, this);
    theAnalysisSelection = new FEA_Selection(true);
    theUQ_Selection = new UQ_EngineSelection();
    theEDP_Selection = new EDP_Selection(theRVs);

    //theResults = new DakotaResultsSampling(theRVs);
    theResults = theUQ_Selection->getResults();

    localApp = new LocalApplication("femUQ.py");
    remoteApp = new RemoteApplication("femUQ.py", theService);

    //    localApp = new LocalApplication("EE-UQ workflow.py");
    //   remoteApp = new RemoteApplication("EE-UQ workflow.py", theService);

    // localApp = new LocalApplication("EE-UQ.py");
    // remoteApp = new RemoteApplication("EE-UQ.py", theService);
    theJobManager = new RemoteJobManager(theService);

    SimCenterWidget *theWidgets[1];// =0;
    theRunWidget = new RunWidget(localApp, remoteApp, theWidgets, 0);

    //
    // connect signals and slots
    //

    // error messages and signals


    connect(localApp,SIGNAL(setupForRun(QString &,QString &)), this, SLOT(setUpForApplicationRun(QString &,QString &)));
    connect(this,SIGNAL(setUpForApplicationRunDone(QString&, QString &)), theRunWidget, SLOT(setupForRunApplicationDone(QString&, QString &)));
    connect(localApp,SIGNAL(processResults(QString&)), this, SLOT(processResults(QString&)));
    connect(theJobManager,SIGNAL(processResults(QString&)), this, SLOT(processResults(QString&)));
    connect(remoteApp,SIGNAL(setupForRun(QString &,QString &)), this, SLOT(setUpForApplicationRun(QString &,QString &)));
    connect(theJobManager,SIGNAL(loadFile(QString&)), this, SLOT(loadFile(QString&)));

    connect(remoteApp,SIGNAL(successfullJobStart()), theRunWidget, SLOT(hide()));
       
    //connect(theRunLocalWidget, SIGNAL(runButtonPressed(QString, QString)), this, SLOT(runLocal(QString, QString)));


    //
    // create layout to hold component selectio
    //


    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    this->setLayout(horizontalLayout);
    this->setContentsMargins(0,5,0,5);
//    horizontalLayout->setMargin(0);

    //
    // create the component selection & add the components to it
    //

    theComponentSelection = new SimCenterComponentSelection();
    horizontalLayout->addWidget(theComponentSelection);

    theComponentSelection->addComponent(QString("UQ"),  theUQ_Selection);
    theComponentSelection->addComponent(QString("GI"),  theGI);
    theComponentSelection->addComponent(QString("SIM"), theSIM);
    theComponentSelection->addComponent(QString("EVT"), theEventSelection);
    theComponentSelection->addComponent(QString("FEM"), theAnalysisSelection);
    theComponentSelection->addComponent(QString("EDP"), theEDP_Selection);
    theComponentSelection->addComponent(QString("RV"),  theRVs);
    theComponentSelection->addComponent(QString("RES"), theResults);
    theComponentSelection->displayComponent("UQ");

    // access a web page which will increment the usage count for this tool
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl("http://opensees.berkeley.edu/OpenSees/developer/eeuq/use.php")));


    //
    // set the defults in the General Info
    //

    theGI->setDefaultProperties(1,144,360,360,37.8715,-122.2730);
}

WorkflowAppHydroUQ::~WorkflowAppHydroUQ()
{
    // hack to get around a sometimes occuring seg fault
    // as some classes in destructur remove RV from the RVCOntainer
    // which may already have been destructed .. so removing so no destructor called

  //    QWidget *newUQ = new QWidget();
  //    theComponentSelection->swapComponent("RV",newUQ);
}

void WorkflowAppHydroUQ::replyFinished(QNetworkReply *pReply)
{
    return;
}


bool
WorkflowAppHydroUQ::outputToJSON(QJsonObject &jsonObjectTop) {

    //
    // get each of the main widgets to output themselves
    //

    bool result = true;
    QJsonObject apps;

    QJsonObject jsonObjGenInfo;
    result = theGI->outputToJSON(jsonObjGenInfo);
    if (result == false) {
        emit errorMessage("WorkflowAppHydro - failed in outputToJSON");
        return false;
    }
    jsonObjectTop["GeneralInformation"] = jsonObjGenInfo;
qDebug() << "GI WRITTEN";

    QJsonObject jsonObjStructural;
    result = theSIM->outputToJSON(jsonObjStructural);
    if (result == false) {
        emit errorMessage("WorkflowAPpHydro - failed in outputToJSON");
        return false;
    }
    jsonObjectTop["StructuralInformation"] = jsonObjStructural;
    QJsonObject appsSIM;
    result = theSIM->outputAppDataToJSON(appsSIM);
    if (result == false) {
        emit errorMessage("WorkflowAPpHydro - failed in outputToJSON");
        return false;
    }
    apps["Modeling"]=appsSIM;

    theRVs->outputToJSON(jsonObjectTop);

    QJsonObject jsonObjectEDP;
    result = theEDP_Selection->outputToJSON(jsonObjectEDP);
    if (result == false) {
        emit errorMessage("WorkflowAPpHydro - failed in outputToJSON");
        return false;
    }
    jsonObjectTop["EDP"] = jsonObjectEDP;

    QJsonObject appsEDP;
    result = theEDP_Selection->outputAppDataToJSON(appsEDP);
    if (result == false) {
        emit errorMessage("WorkflowAPpHydro - failed in outputToJSON");
        return false;
    }
    apps["EDP"]=appsEDP;

    /*
    QJsonObject jsonObjectUQ;
    theUQ_Selection->outputToJSON(jsonObjectUQ);
    jsonObjectTop["UQ_Method"] = jsonObjectUQ;
    */

    result = theUQ_Selection->outputAppDataToJSON(apps);
    if (result == false) {
        emit errorMessage("WorkflowAPpHydro - failed in outputToJSON");
        return false;
    }
    result = theUQ_Selection->outputToJSON(jsonObjectTop);
    if (result == false) {
        emit errorMessage("WorkflowAPpHydro - failed in outputToJSON");
        return false;
    }

    result = theAnalysisSelection->outputAppDataToJSON(apps);
    if (result == false) {
        emit errorMessage("WorkflowAPpHydro - failed in outputToJSON");
        return false;
    }
    result = theAnalysisSelection->outputToJSON(jsonObjectTop);
    if (result == false) {
        emit errorMessage("WorkflowAPpHydro - failed in outputToJSON");
        return false;
    }

   // NOTE: Events treated differently, due to array nature of objects
    result = theEventSelection->outputToJSON(jsonObjectTop);
    if (result == false) {
        emit errorMessage("WorkflowAPpHydro - failed in outputToJSON");
        return false;
    }
    result = theEventSelection->outputAppDataToJSON(apps);
    if (result == false) {
        emit errorMessage("WorkflowAPpHydro - failed in outputToJSON");
        return false;
    }

    result = theRunWidget->outputToJSON(jsonObjectTop);
    if (result == false) {
        emit errorMessage("WorkflowAPpHydro - failed in outputToJSON");
        return false;
    }

    jsonObjectTop["Applications"]=apps;

    //theRunLocalWidget->outputToJSON(jsonObjectTop);
    return true;
}


void WorkflowAppHydroUQ::processResults(QString &dirName)
{


  //
  // get results widget fr currently selected UQ option
  //

  theResults=theUQ_Selection->getResults();
  if (theResults == NULL) {
    this->errorMessage("FATAL - UQ option selected not returning results widget");
    return;
  }

  //
  // connect signals for results widget
  //

  /*
  connect(theResults,SIGNAL(sendStatusMessage(QString)), this,SLOT(statusMessage(QString)));
  connect(theResults,SIGNAL(sendErrorMessage(QString)), this,SLOT(errorMessage(QString)));
  */
  
  //
  // swap current results with existing one in selection & disconnect signals
  //

  QWidget *oldResults = theComponentSelection->swapComponent(QString("RES"), theResults);
  if (oldResults != NULL) {
    //disconnect(oldResults,SIGNAL(sendErrorMessage(QString)), this,SLOT(errorMessage(QString)));
    //disconnect(oldResults,SIGNAL(sendFatalMessage(QString)), this,SLOT(fatalMessage(QString)));  
    delete oldResults;
  }

  //
  // proess results
  // 

  theResults->processResults(dirName);
  theRunWidget->hide();
  theComponentSelection->displayComponent("RES");
}

void
WorkflowAppHydroUQ::clear(void)
{
    theGI->clear();
    theSIM->clear();
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
            emit errorMessage("HydroUQ: failed to read GeneralInformation");
        }
    } else {
        emit errorMessage("HydroUQ: failed to find General Information");
        return false;
    }

    if (jsonObject.contains("Applications")) {

        QJsonObject theApplicationObject = jsonObject["Applications"].toObject();

        if (theApplicationObject.contains("Modeling")) {
            QJsonObject theObject = theApplicationObject["Modeling"].toObject();
            if (theSIM->inputAppDataFromJSON(theObject) == false) {
                emit errorMessage("HydroUQ: failed to read Modeling Application");
            }
        } else {
            emit errorMessage("HydroUQ: failed to find Modeling Application");
            return false;
        }

        // note: Events is different because the object is an Array
        if (theApplicationObject.contains("Events"))
        {
            QJsonObject theObject = theApplicationObject["Events"].toObject(); //it is null object, actually an array
            if (theEventSelection->inputAppDataFromJSON(theApplicationObject) == false)
            {
                emit errorMessage("HydroUQ: failed to read Event Application");
            }

        }
        else
        {
            emit errorMessage("HydroUQ: failed to find Event Application");
            return false;
        }

        // UQ application
        if (theUQ_Selection->inputAppDataFromJSON(theApplicationObject) == false)
            emit errorMessage("HydroUQ: failed to read UQ application");

        // FEM application
        if (theAnalysisSelection->inputAppDataFromJSON(theApplicationObject) == false)
            emit errorMessage("HydroUQ: failed to read FEM application");

        // EDP application
        if (theApplicationObject.contains("EDP"))
        {
            QJsonObject theObject = theApplicationObject["EDP"].toObject();
            if (theEDP_Selection->inputAppDataFromJSON(theObject) == false)
            {
                emit errorMessage("HydroUQ: failed to read EDP application");
            }
        }
        else
        {
            emit errorMessage("HydroUQ: failed to find EDP application");
            return false;
        }

    }
    else
    {
        return false;
    }

    /*
    ** Note to me - RVs and Events treated differently as both use arrays .. rethink API!
    */

    theEventSelection->inputFromJSON(jsonObject);
    theRVs->inputFromJSON(jsonObject);
    theRunWidget->inputFromJSON(jsonObject);

    if (jsonObject.contains("StructuralInformation")) {
        QJsonObject jsonObjStructuralInformation = jsonObject["StructuralInformation"].toObject();
        if (theSIM->inputFromJSON(jsonObjStructuralInformation) == false) {
            emit errorMessage("HydroUQ: failed to read StructuralInformation");
        }
    } else {
        emit errorMessage("HydroUQ: failed to find StructuralInformation");
        return false;
    }

    if (jsonObject.contains("EDP")) {
        QJsonObject edpObj = jsonObject["EDP"].toObject();
        if (theEDP_Selection->inputFromJSON(edpObj) == false)
            emit errorMessage("HydroUQ: failed to read EDP data");
    } else {
        emit errorMessage("HydroUQ: failed to find EDP data");
        return false;
    }


    if (theUQ_Selection->inputFromJSON(jsonObject) == false)
        emit errorMessage("HydroUQ: failed to read UQ Method data");

    if (theAnalysisSelection->inputFromJSON(jsonObject) == false)
        emit errorMessage("HydroUQ: failed to read FEM Method data");

    return true;
}


void
WorkflowAppHydroUQ::onRunButtonClicked() {
    emit errorMessage("This app cannot be run locally. Please run remotely on DesignSafe");
//    theRunWidget->hide();
//    theRunWidget->setMinimumWidth(this->width()*0.5);
//    theRunWidget->showLocalApplication();
//    GoogleAnalytics::ReportLocalRun();
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
        errorMessage("ERROR - You Need to Login");
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
        errorMessage("ERROR - You Need to Login");
    }
}

void
WorkflowAppHydroUQ::onExitButtonClicked(){

}

void
WorkflowAppHydroUQ::setUpForApplicationRun(QString &workingDir, QString &subDir) {

    errorMessage("");

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
    QDir destinationDirectory(tmpDirectory);

    if(destinationDirectory.exists()) {
      destinationDirectory.removeRecursively();
    } else
      destinationDirectory.mkpath(tmpDirectory);

    QString templateDirectory  = destinationDirectory.absoluteFilePath(subDir);
    destinationDirectory.mkpath(templateDirectory);

    // copyPath(path, tmpDirectory, false);
    theSIM->copyFiles(templateDirectory);
    theEventSelection->copyFiles(templateDirectory);
    theAnalysisSelection->copyFiles(templateDirectory);
    theUQ_Selection->copyFiles(templateDirectory);
    theEDP_Selection->copyFiles(templateDirectory);

    //
    // in new templatedir dir save the UI data into dakota.json file (same result as using saveAs)
    // NOTE: we append object workingDir to this which points to template dir
    //

    QString inputFile = templateDirectory + QDir::separator() + tr("dakota.json");

    QFile file(inputFile);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        //errorMessage();
        return;
    }
    QJsonObject json;
    if (this->outputToJSON(json) == false)
        return;

    json["runDir"]=tmpDirectory;
    json["WorkflowType"]="Building Simulation";


    QJsonDocument doc(json);
    file.write(doc.toJson());
    file.close();


    statusMessage("SetUp Done .. Now starting application");
    emit setUpForApplicationRunDone(tmpDirectory, inputFile);
}

int
WorkflowAppHydroUQ::loadFile(QString &fileName){

    //
    // open file
    //

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        emit errorMessage(QString("Could Not Open File: ") + fileName);
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

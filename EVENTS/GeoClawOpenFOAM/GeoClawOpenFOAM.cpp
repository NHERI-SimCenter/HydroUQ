#include "GeoClawOpenFOAM.h"
#include "ui_GeoClawOpenFOAM.h"

#include "AgaveCurl.h"
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QSettings>
#include <QUuid>
#include <ZipUtils.h>
#include <QStandardPaths>


//*********************************************************************************
// Main window
//*********************************************************************************
GeoClawOpenFOAM::GeoClawOpenFOAM(RandomVariablesContainer *theRV, QWidget *parent)
    : SimCenterAppWidget(parent), theRemoteService(NULL)
    , ui(new Ui::GeoClawOpenFOAM)
{
    // Start the UI
    ui->setupUi(this);

    // Initialize the UI
    initialize();
}

//*********************************************************************************
// Delete main window
//*********************************************************************************
GeoClawOpenFOAM::~GeoClawOpenFOAM()
{
    delete ui;
}

//*********************************************************************************
// Initialize the UI
//*********************************************************************************
void GeoClawOpenFOAM::initialize()
{
    // Add project page
    ui->stackedWidget->addWidget(new projectsettings(0)); // Project settings
    ui->stackedWidget->addWidget(new bathymetry(0)); // Bathymetry
    ui->stackedWidget->addWidget(new swcfdint(0)); // SW-CFD interface: Check this if working
    ui->stackedWidget->addWidget(new buildings(0)); // Buildings
    ui->stackedWidget->addWidget(new floatingbds(0)); // Floating bodies
    ui->stackedWidget->addWidget(new meshing(0)); // Meshing
    ui->stackedWidget->addWidget(new materials(0)); // Materials
    ui->stackedWidget->addWidget(new initialconVel(0)); // Initial velocity
    ui->stackedWidget->addWidget(new initialconPres(0)); // Initial pressure
    ui->stackedWidget->addWidget(new initialconAlpha(0)); // Initial alpha
    ui->stackedWidget->addWidget(new boundary(0)); // Boundary condition
    ui->stackedWidget->addWidget(new solver(0)); // Solver settings

    // Set index to zero & simtype to zero
    ui->stackedWidget->setCurrentIndex(0);
    simtype = 0;
}


bool GeoClawOpenFOAM::outputToJSON(QJsonObject &jsonObject)
{
  jsonObject["EventClassification"]="Hydro";
  jsonObject["Application"] = "GeoClawOpenFOAM";


    // Get the simulation type
    refresh_projsettings();

    // Get data from project settings - index 0
    QMap<QString, QString> *singleData;
    this->clearAllData();
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<projectsettings *>(ui->stackedWidget->widget(0))->getData(*singleData,simtype))
    {
        allData.insert(0, singleData);
    }

    // Get data from Bathymetry - index 1
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<bathymetry *>(ui->stackedWidget->widget(1))->getData(*singleData,simtype))
    {
        allData.insert(1, singleData);
    }

    // Add SW-CFD Interface - Index 2
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<swcfdint *>(ui->stackedWidget->widget(2))->getData(*singleData,simtype))
    {
        allData.insert(2, singleData);
    }

    // Get data from buildings - index 3
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<buildings *>(ui->stackedWidget->widget(3))->getData(*singleData,simtype))
    {
        allData.insert(3, singleData);
    }

    // Get data from floating bodies - Index 4
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<floatingbds *>(ui->stackedWidget->widget(4))->getData(*singleData,simtype))
    {
        allData.insert(4, singleData);
    }

    // Get data from mesh - index 5
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<meshing *>(ui->stackedWidget->widget(5))->getData(*singleData,simtype))
    {
        allData.insert(5, singleData);
    }

    // Get data from materials - index 6
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<materials *>(ui->stackedWidget->widget(6))->getData(*singleData,simtype))
    {
        allData.insert(6, singleData);
    }

    // Initial conditions: velocity - index 7
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<initialconVel *>(ui->stackedWidget->widget(7))->getData(*singleData,simtype))
    {
        allData.insert(7, singleData);
    }

    // Initial conditions: pressure - index 8
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<initialconPres *>(ui->stackedWidget->widget(8))->getData(*singleData,simtype))
    {
        allData.insert(8, singleData);
    }

    // Initial conditions: alpha - index 9
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<initialconAlpha *>(ui->stackedWidget->widget(9))->getData(*singleData,simtype))
    {
        allData.insert(9, singleData);
    }

    // Boundary conditions - index 10
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<boundary *>(ui->stackedWidget->widget(10))->getData(*singleData,simtype))
    {
        allData.insert(10, singleData);
    }

    // Solver settings - index 11
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<solver *>(ui->stackedWidget->widget(11))->getData(*singleData,simtype))
    {
        allData.insert(11, singleData);
    }

    /*// Show in text window (Just to print out the map)
    // This will later be replaced by writing to JSON
    QString text;
    foreach (int key, allData.keys())
    {
        QMap<QString, QString> *singleDataSet = allData.value(key);
        foreach (QString varname, singleDataSet->keys())
        {
            QString oneEntry = QString("%1: %2 = %3\n").arg(key+1).arg(varname).arg(singleDataSet->value(varname));
            text.append(oneEntry);
        }
    }
    ui->textEdit->setPlainText(text);
    ui->textEdit->repaint();*/

    // Get directory and project name for writing JSON file
    QMap<QString, QString> *singleDataSet = allData.value(0);
    QString wdir = singleDataSet->value("Work directory");
    QString pname = singleDataSet->value("Project name");

    // Convert to QJsonObject
    //    QVariantMap vmap;
    //vmap.insert("Application name",applicationname);
    //    vmap.insert("Application version",applicationversion);
    foreach (int key, allData.keys())
    {
        QMap<QString, QString> *singleDataSet = allData.value(key);
        foreach (QString varname, singleDataSet->keys())
        {
	  // QString oneEntry = QString("%1: %2 = %3\n").arg(key+1).arg(varname).arg(singleDataSet->value(varname));
	  // vmap.insert(varname, singleDataSet->value(varname));
	    jsonObject[varname] = singleDataSet->value(varname);
        }
    }
  
  return true;
}

bool GeoClawOpenFOAM::inputFromJSON(QJsonObject &jsonObject)
{
  return false;
}

bool
GeoClawOpenFOAM::outputAppDataToJSON(QJsonObject &jsonObject)
{
    jsonObject["EventClassification"]="Hydro";
    jsonObject["Application"] = "GeoClawOpenFOAM";
    QJsonObject dataObj;
    jsonObject["ApplicationData"] = dataObj;
    return true;  
}

bool
GeoClawOpenFOAM::inputAppDataFromJSON(QJsonObject &jsonObject)
{
  return true;
}

bool
GeoClawOpenFOAM::copyFiles(QString &dirName)
{
  return false;
}

void
GeoClawOpenFOAM::errorMessage(QString message){
    emit sendErrorMessage(message);
}


//*********************************************************************************
// Clear all data
//*********************************************************************************
void GeoClawOpenFOAM::clearAllData(void)
{
    foreach (int key, allData.keys()) { delete allData.value(key); }
    allData.clear();
}

//*********************************************************************************
// Refresh project map and get latest simulation type
//*********************************************************************************
void GeoClawOpenFOAM::refresh_projsettings()
{
    // Refresh the map to get the project data
    QMap<QString, QString> *singleData;
    this->clearAllData();
    singleData = new QMap<QString,QString>;
    int numberOfPanes = 1;
    for (int i=0;i<numberOfPanes;i++) {
        singleData = new QMap<QString,QString>;
        if (dynamic_cast<projectsettings *>(ui->stackedWidget->widget(i))->getData(*singleData,simtype))
        {
            allData.insert(i, singleData);
        }
    }

    // Search for simulation type
    QMap<QString, QString> *singleDataSet = allData.value(0);
    QString simty = singleDataSet->value("Simulation type");

    // Get new simulation type, if user has changed it intermediately
    // This can also be same as old simulation type
    simtype = simty.split(" ")[0].toInt();
}

//*********************************************************************************
// Read all the pages for data and get data
// Temporarily writing to a text window - to be replaced by write to JSON
//*********************************************************************************
void GeoClawOpenFOAM::on_Btn_Generate_Files_clicked()
{

    // Get the simulation type
    refresh_projsettings();

    // Get data from project settings - index 0
    QMap<QString, QString> *singleData;
    this->clearAllData();
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<projectsettings *>(ui->stackedWidget->widget(0))->getData(*singleData,simtype))
    {
        allData.insert(0, singleData);
    }

    // Get data from Bathymetry - index 1
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<bathymetry *>(ui->stackedWidget->widget(1))->getData(*singleData,simtype))
    {
        allData.insert(1, singleData);
    }

    // Add SW-CFD Interface - Index 2
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<swcfdint *>(ui->stackedWidget->widget(2))->getData(*singleData,simtype))
    {
        allData.insert(2, singleData);
    }

    // Get data from buildings - index 3
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<buildings *>(ui->stackedWidget->widget(3))->getData(*singleData,simtype))
    {
        allData.insert(3, singleData);
    }

    // Get data from floating bodies - Index 4
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<floatingbds *>(ui->stackedWidget->widget(4))->getData(*singleData,simtype))
    {
        allData.insert(4, singleData);
    }

    // Get data from mesh - index 5
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<meshing *>(ui->stackedWidget->widget(5))->getData(*singleData,simtype))
    {
        allData.insert(5, singleData);
    }

    // Get data from materials - index 6
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<materials *>(ui->stackedWidget->widget(6))->getData(*singleData,simtype))
    {
        allData.insert(6, singleData);
    }

    // Initial conditions: velocity - index 7
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<initialconVel *>(ui->stackedWidget->widget(7))->getData(*singleData,simtype))
    {
        allData.insert(7, singleData);
    }

    // Initial conditions: pressure - index 8
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<initialconPres *>(ui->stackedWidget->widget(8))->getData(*singleData,simtype))
    {
        allData.insert(8, singleData);
    }

    // Initial conditions: alpha - index 9
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<initialconAlpha *>(ui->stackedWidget->widget(9))->getData(*singleData,simtype))
    {
        allData.insert(9, singleData);
    }

    // Boundary conditions - index 10
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<boundary *>(ui->stackedWidget->widget(10))->getData(*singleData,simtype))
    {
        allData.insert(10, singleData);
    }

    // Solver settings - index 11
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<solver *>(ui->stackedWidget->widget(11))->getData(*singleData,simtype))
    {
        allData.insert(11, singleData);
    }

    /*// Show in text window (Just to print out the map)
    // This will later be replaced by writing to JSON
    QString text;
    foreach (int key, allData.keys())
    {
        QMap<QString, QString> *singleDataSet = allData.value(key);
        foreach (QString varname, singleDataSet->keys())
        {
            QString oneEntry = QString("%1: %2 = %3\n").arg(key+1).arg(varname).arg(singleDataSet->value(varname));
            text.append(oneEntry);
        }
    }
    ui->textEdit->setPlainText(text);
    ui->textEdit->repaint();*/

    // Get directory and project name for writing JSON file
    QMap<QString, QString> *singleDataSet = allData.value(0);
    QString wdir = singleDataSet->value("Work directory");
    QString pname = singleDataSet->value("Project name");

    // Convert to QJsonObject
    QVariantMap vmap;
    vmap.insert("Application name",applicationname);
    vmap.insert("Application version",applicationversion);
    foreach (int key, allData.keys())
    {
        QMap<QString, QString> *singleDataSet = allData.value(key);
        foreach (QString varname, singleDataSet->keys())
        {
            QString oneEntry = QString("%1: %2 = %3\n").arg(key+1).arg(varname).arg(singleDataSet->value(varname));
            vmap.insert(varname, singleDataSet->value(varname));
        }
    }

    // Create a QJsonDocument from the Variant map
    QJsonDocument jsondoc = QJsonDocument::fromVariant(vmap);

    // Create a JSON file with this name and write all data to this
    saveJson(wdir,pname,jsondoc);

    // Call the OpenFOAM method to read the JSON file
    // Write the OpenFOAM files & folders
    // Create an object for openfoam
    openfoam ofwrite;
    ofwrite.genopenfoam(wdir,pname);

}

//*********************************************************************************
// Save JSON file
//*********************************************************************************
void GeoClawOpenFOAM::saveJson(QString wdir,QString pname, QJsonDocument jsondoc)
{
    // Concatenate to get new dir path where files will be written
    QString finaldirpath = QDir(wdir).filePath(pname);
    QUrl finaldirpathUrl(finaldirpath);

    // Create a directory if it does not exist
    // All files to be written to this directory
    QDir fildirs(finaldirpath);
    if (!fildirs.exists())
        fildirs.mkpath(".");

    // Create the JSON file to write to
    QFile jsonfile(fildirs.filePath(pname+".json"));
    if(!jsonfile.open(QIODevice::ReadWrite))
    {
        //qDebug() << "File open error";
    }
    else
    {
        //qDebug() <<"File open!";
    }
    // Clear the original file content
    jsonfile.resize(0);

    // Write a json file
    jsonfile.write(jsondoc.toJson());
    jsonfile.close();
}

//*********************************************************************************
// Tree item double clicked
//*********************************************************************************
void GeoClawOpenFOAM::on_SimOptions_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    // Get the item double clicked on
    QString sel = item->text(column);

    // Get the simulation type
    refresh_projsettings();

    // Bathymetry
    if(simtype == 0)
    {
        ui->stackedWidget->setCurrentIndex(0);
    }
    else
    {
        // Move to project settings page
        if(sel == "Project settings")
        {
            ui->stackedWidget->setCurrentIndex(0);
        }

        // Update bathymetry
        else if(sel == "Bathymetry")
        {
            dynamic_cast<bathymetry *>(ui->stackedWidget->widget(1))->refreshData(simtype);
            ui->stackedWidget->setCurrentIndex(1);
        }

        // Update sw-cfd interface
        else if(sel == "SW-CFD interface")
        {
            dynamic_cast<swcfdint *>(ui->stackedWidget->widget(2))->refreshData(simtype);
            ui->stackedWidget->setCurrentIndex(2);
        }

        // Update buildings
        else if(sel == "Buildings")
        {
            dynamic_cast<buildings *>(ui->stackedWidget->widget(3))->refreshData(simtype);
            ui->stackedWidget->setCurrentIndex(3);
        }

        // Update floating bodies
        else if(sel == "Floating bodies")
        {
            dynamic_cast<floatingbds *>(ui->stackedWidget->widget(4))->refreshData(simtype);
            ui->stackedWidget->setCurrentIndex(4);
        }

        // Update Meshing
        else if(sel == "Meshing")
        {
            dynamic_cast<meshing *>(ui->stackedWidget->widget(5))->refreshData(simtype);
            ui->stackedWidget->setCurrentIndex(5);
        }

        // Update Materials
        else if(sel == "Materials")
        {
            dynamic_cast<materials *>(ui->stackedWidget->widget(6))->refreshData(simtype);
            ui->stackedWidget->setCurrentIndex(6);
        }

        // Update Initial conditions - velocity
        else if(sel == "Initial velocity")
        {
            dynamic_cast<initialconVel *>(ui->stackedWidget->widget(7))->refreshData(simtype);
            ui->stackedWidget->setCurrentIndex(7);
        }

        // Update Initial conditions - Pressure
        else if(sel == "Initial pressure")
        {
            dynamic_cast<initialconPres *>(ui->stackedWidget->widget(8))->refreshData(simtype);
            ui->stackedWidget->setCurrentIndex(8);
        }

        // Update Initial conditions - Alpha
        else if(sel == "Initial phase")
        {
            dynamic_cast<initialconAlpha *>(ui->stackedWidget->widget(9))->refreshData(simtype);
            ui->stackedWidget->setCurrentIndex(9);
        }

        // Update boundary conditions
        else if(sel == "Boundary conditions")
        {
            dynamic_cast<boundary *>(ui->stackedWidget->widget(10))->refreshData(simtype);
            ui->stackedWidget->setCurrentIndex(10);
        }

        // Update solvers
        else if(sel == "Solver")
        {
            dynamic_cast<solver *>(ui->stackedWidget->widget(11))->refreshData(simtype);
            ui->stackedWidget->setCurrentIndex(11);
        }
    }
}

//*********************************************************************************
// Submit to TACC
//*********************************************************************************

int recursiveCopy(const QString &source,
                  const QString &target)
{

  QFileInfo sourceInfo(source);

  if (!sourceInfo.isDir()) {

   // std::cerr << "FILE:\n";
   // std::cerr << "source: " << source.toStdString() << " target: " << target.toStdString() << "\n";

    // if not directory, then a file just copy
    if (!QFile::copy(source, target))
      return -1;
    else
      return 0;

  } else {

    // don't of course copy from HOME,DESKTOP, DOWNLOADS,
    /*
      QStandardPaths::DesktopLocation
      QStandardPaths::DocumentsLocation
      QStandardPaths::ApplicationsLocation
      QStandardPaths::HomeLocation
      QStandardPaths::DownloadLocation
    */

    //
    // source is a directory:
    //   1. make directory for target
    //   2. now copy all files and directory in source to target
    //

    // mkdir target
    //std::cerr << "DIR: \n";
    //std::cerr << "source: " << source.toStdString() << " target: " << target.toStdString() << "\n";

    QDir targetDir(target);
    targetDir.cdUp();
    if (!targetDir.mkdir(QFileInfo(target).fileName())) {
      return -1;
    }

    // get list of all files in source and copy them, by calling this function

    QDir sourceDir(source);
    std::cerr << "sourceDir path: " << sourceDir.absolutePath().toStdString() << "\n";

    QStringList fileNames = sourceDir.entryList(QDir::Files
                        | QDir::Dirs
                        | QDir::NoDotAndDotDot);

    //qDebug() << fileNames;

    foreach (const QString &fileName, fileNames) {
      std::cerr << "\tcopying: " << fileName.toStdString() << "\n";
      const QString newSrcFilePath = source + QDir::separator() + fileName;
      const QString newTgtFilePath = target + QDir::separator() + fileName;
      if (recursiveCopy(newSrcFilePath, newTgtFilePath) != 0)
    return -1;
    }
  }

  return 0;
}

void GeoClawOpenFOAM::on_Btn_SubTACC_clicked()
{
    // Get directory and project name for writing JSON file
    QMap<QString, QString> *singleDataSet = allData.value(0);
    QString wdir = singleDataSet->value("Work directory");
    QString pname = singleDataSet->value("Project name");

    /* not needed
    openfoam ofwrite;
    ofwrite.genopenfoam(wdir,pname);
    */

    qDebug() << "WROTE: " << wdir << pname;

    QString caseDirectory = wdir + QDir::separator() + pname;


    int count = 1;
    QString jobName("OpenFOAM:");
    QString maxRunTime ("48:00:00");
    int numNode = 1;
    int numProcessors = 4;
    //char *username = NULL;
   // char *password = NULL;

    char *solver = "olaFlow";
    char *mesh = "On";

    //QString caseDirectory(dirName);
    QDir copyDir(caseDirectory);
    if (!copyDir.exists()) {
        qDebug() << "ERROR - no case dir  exists\n";
        return;
    }

    QString copyDirPath = copyDir.absolutePath();
    QString copyDirName = copyDir.dirName();

    //  qDebug() << "dirExists: " << inputFileDir;
    qDebug() << "absolutePath: " << copyDirPath;

    //
    // get pointer to QSettings .. we are ging to need some entries
    //

    QString appName = QCoreApplication::applicationName();
    QSettings settingsCommon("SimCenter", "Common");
    QSettings settingsApplication("SimCenter", appName);

    //
    // get remote workdir and copy all input files there
    //

    QVariant  remoteWorkdirVariant = settingsApplication.value("remoteWorkDir");
    QString workingDir;
    if (remoteWorkdirVariant.isValid()) {
      workingDir = remoteWorkdirVariant.toString();
    } else {

      remoteWorkdirVariant = settingsApplication.value("remoteWorkDir");
      QDir workingDir(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
      QString remoteWorkDirLocation = workingDir.filePath(QCoreApplication::applicationName() + "/RemoteWorkDir");
      settingsApplication.setValue("remoteWorkDir", remoteWorkDirLocation);
      if (remoteWorkdirVariant.isValid()) {
        workingDir = remoteWorkdirVariant.toString();
      } else {
        qDebug() << "Could not create Working dir\n";
        return;
      }
    }

    QDir dirWork(workingDir);
     if (!dirWork.exists())
       if (!dirWork.mkpath(workingDir)) {
         std::cerr << "Could not create Working Dir: " << workingDir.toStdString() << "\n";
         exit(-1);
       }

     // create dir with unique name .. using UIUID
     QUuid uniqueName = QUuid::createUuid();
     QString strUnique = uniqueName.toString();
     strUnique = strUnique.mid(1,36);

     QString zipLocation = workingDir + QDir::separator() + strUnique;

     if (!dirWork.mkpath(zipLocation)) {

     }

     QString copyLocation = zipLocation + QDir::separator() + copyDirName;
     QString originalLocation = copyDirPath;

     //
     // copy input file and all directories and subdir to new dir
     //

     std::cerr << "Obtaining Files From: " << originalLocation.toStdString() << "\n";
     std::cerr << "& Copying files to " << copyLocation.toStdString() << "\n";

     recursiveCopy(originalLocation, copyLocation);

     QString zipFile(zipLocation + QDir::separator() + copyDirName + QString(".zip"));
     std::cerr << "ZIP FILE: " << zipFile.toStdString() << "\n";
     std::cerr << "DIR TO ZIP: " << zipLocation.toStdString() << "\n";


     //QDir tmpDir(templateDIR);
     QString tempvar = zipLocation + QDir::separator() + copyDirName;

     // CHanged heres
     ZipUtils::ZipFolder(QDir(copyLocation), zipFile);

     // remove the copied dir
     QDir copyLocationDir(copyLocation);
     if (copyLocationDir.removeRecursively() != true) {
         qDebug() << "ERROR - could not remove " << copyLocation;
         return;
     };

     //
     // login to designsafe
     //
    QString username = "username";
    QString password = "password";
    qDebug() << "Logging in ..\n";
    if (theRemoteService->login(username, password) < 0) {
      qDebug() << "ERROR - could not login ";
      return;
    };

    //
    // upload files
    //


    
    std::cerr << "Uploading files .. \n";
    QString remoteDir =  theRemoteService->getHomeDirPath() + QString("/") + appName;
    if (!theRemoteService->uploadDirectory(zipLocation, remoteDir))
      {
	qDebug() << "Could not upload directory: " << remoteDir;
	return;
      }
    
    std::cerr << "Uploaded files .. \n";

     //
     // create json job description
     //

     QJsonObject job;
     job["name"]=jobName;
     job["nodeCount"]=numNode; //QString::number(numNode);
     job["processorsPerNode"]=numProcessors; // QString::number(numNode*numProcessors); // tapis people messed up!
     // job["processorsOnEachNode"]=QString::number(numProcessors);
     job["maxRunTime"]=maxRunTime;
     /* to FIX
     QVariant  remoteAppNameVariant = settingsApplication.value("remoteTapisApp");
     QString remoteAppName;
     if (remoteAppNameVariant.isValid()) {
       remoteAppName = remoteAppNameVariant.toString();
     }
     *************************/

     job["appId"]="simcenter-openfoam_v7-1.0.0";
     job["memoryPerNode"]= "1GB";
     job["archive"]=true;
     job["archivePath"]="";
     job["archiveSystem"]="designsafe.storage.default";

     QJsonObject parameters;

     parameters["openFoamDir"]=QString(copyDirName);
     parameters["mesh"]=QString(mesh);
     parameters["solver"]=QString(solver);

     job["parameters"]=parameters;
     QJsonObject inputs;
     inputs["inputDirectory"]=remoteDir + QDir::separator() + strUnique;

     job["inputs"]=inputs;

     qDebug() << job;

     //
     // start the remote job
     //

     std::cerr << "Starting Job ... \n";

     QString result =  theRemoteService->startJob(job);

     std::cerr << result.toStdString() << "\n";

     //
     // now remove the tmp directory
     // remove the copied dir
     /*QDir zipLocationDir(zipLocation);
     if (zipLocationDir.removeRecursively() != true) {
         qDebug() << "ERROR - could not remove " << zipLocation;
         return;
     };*/

     // theDirectory.removeRecursively();
     //

     return;

}







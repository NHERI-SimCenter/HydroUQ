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
    ui->pushButton->setVisible(false);

    // Suppress unused parameters
    (void)theRV;

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
    ui->stackedWidget->addWidget(new postprocess(0)); //postprocessing

    // Set index to zero & simtype to zero
    ui->stackedWidget->setCurrentIndex(0);
    simtype = 0;
}

//*********************************************************************************
// Output to JSON
//*********************************************************************************
bool GeoClawOpenFOAM::outputToJSON(QJsonObject &jsonObject)
{
    jsonObject["EventClassification"]="Hydro";
    jsonObject["Application"] = "GeoClawOpenFOAM";
    bool isitready = true;

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
    else
    {
        isitready = false;
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

    // Solver settings - index 12
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<postprocess *>(ui->stackedWidget->widget(12))->getData(*singleData,simtype))
    {
        allData.insert(11, singleData);
    }

    // Add all objects to the json object
    foreach (int key, allData.keys())
    {
        QMap<QString, QString> *singleDataSet = allData.value(key);
        foreach (QString varname, singleDataSet->keys())
        {
            jsonObject[varname] = singleDataSet->value(varname);
        }
    }
  
    return isitready;
    //return true;
//    return false;
}

//*********************************************************************************
// Use JSON file to update all elements in the GUI (Need to add this)
//*********************************************************************************
bool GeoClawOpenFOAM::inputFromJSON(QJsonObject &jsonObject)
{
    (void) jsonObject;

    error.criterrormessage("This is not presently supported! Contact developer");

    return false;
}

//*********************************************************************************
// Output app Data to JSON file
//*********************************************************************************
bool GeoClawOpenFOAM::outputAppDataToJSON(QJsonObject &jsonObject)
{
    jsonObject["EventClassification"]="Hydro"; // Event is Hydro
    jsonObject["Application"] = "GeoClawOpenFOAM"; // Event inHydro
    QJsonObject dataObj;
    jsonObject["ApplicationData"] = dataObj; // All application data
    return true;  
}

//*********************************************************************************
// Read app data from JSON file (Need to add)
//*********************************************************************************
bool GeoClawOpenFOAM::inputAppDataFromJSON(QJsonObject &jsonObject)
{
    (void) jsonObject;
    return true;
}

//*********************************************************************************
// Copy files
//*********************************************************************************
bool GeoClawOpenFOAM::copyFiles(QString &dirName)
{

    // Copy bathymetry and solution files
    dynamic_cast<bathymetry *>(ui->stackedWidget->widget(1))->copyFiles(dirName,simtype);

    // Copy SW-CFD interface files
    dynamic_cast<swcfdint *>(ui->stackedWidget->widget(2))->copyFiles(dirName,simtype);

    // Meshing
    dynamic_cast<meshing *>(ui->stackedWidget->widget(5))->copyFiles(dirName,simtype);

    // Boundary
    dynamic_cast<solver *>(ui->stackedWidget->widget(11))->copyFiles(dirName,simtype);

    // Solver
    dynamic_cast<boundary *>(ui->stackedWidget->widget(10))->copyFiles(dirName,simtype);

    // Postprocess
    dynamic_cast<postprocess *>(ui->stackedWidget->widget(12))->copyFiles(dirName,simtype);

    // Return
    return true;
}

//*********************************************************************************
// Send error message
//*********************************************************************************
void GeoClawOpenFOAM::errorMessage(QString message)
{
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
    QString simty = singleDataSet->value("SimulationType");

    // Get new simulation type, if user has changed it intermediately
    // This can also be same as old simulation type
    simtype = simty.split(" ")[0].toInt();
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

        // Postprocessing
        else if(sel == "Post-processing")
        {
            dynamic_cast<postprocess *>(ui->stackedWidget->widget(12))->refreshData(simtype);
            ui->stackedWidget->setCurrentIndex(12);
        }
    }
}

//*********************************************************************************
// Temporary button
//*********************************************************************************
void GeoClawOpenFOAM::on_pushButton_clicked()
{

//    QMap<QString, QString> *singleData;
//    this->clearAllData();
//    singleData = new QMap<QString,QString>;
//    // Get data from Bathymetry - index 1
//    singleData = new QMap<QString,QString>;
//    if (dynamic_cast<bathymetry *>(ui->stackedWidget->widget(1))->getData(*singleData,simtype))
//    {
//        allData.insert(1, singleData);
//    }

    //qDebug() << allData;
    // Create the file and add the segments
    // Create and open a text file
//    QString filename = "FlSegmentData.txt";
//    QFile file(filename);
//    QFileInfo fi(file);
//    qDebug() << fi.absolutePath() << " fn=" << fi.fileName();
//    if (file.open(QIODevice::ReadWrite))
//    {
//        QTextStream stream(&file);
//        stream << "something" << Qt::endl;
//    }
}

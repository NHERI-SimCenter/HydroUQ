#include "projectsettings.h"
#include "ui_projectsettings.h"
#include <QDebug>

//*********************************************************************************
// Project settings
//*********************************************************************************
projectsettings::projectsettings(int type, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::projectsettings)
{
    ui->setupUi(this);

    // Initialize to show / hide elements
    hideshowelems(type);
}

//*********************************************************************************
// Delete project settings
//*********************************************************************************
projectsettings::~projectsettings()
{
    delete ui;
}

//*********************************************************************************
// Refresh data
//*********************************************************************************
void projectsettings::refreshData(int type)
{
    // Initialize to show / hide elements
    hideshowelems(type);
}

//*********************************************************************************
// Reset data
//*********************************************************************************
void projectsettings::resetData()
{
    //ui->Led_PName->clear();
    //ui->Ted_PDesc->clear();
    ui->CmB_SimType->setCurrentIndex(0);
    ui->CmB_TurbModel->setCurrentIndex(0);
}

//*********************************************************************************
// Show - hide elements
//*********************************************************************************
void projectsettings::hideshowelems(int type)
{
    (void) type;
}

//*********************************************************************************
// Get data from project settings for JSON file output
//*********************************************************************************
bool projectsettings::getData(QMap<QString, QString> & map, int type)
{
    bool hasData=false;
    (void) type;

    //map.insert("ProjectName",ui->Led_PName->text());
    //map.insert("ProjectDescription",ui->Ted_PDesc->toPlainText());
    map.insert("SimulationType",QString::number(ui->CmB_SimType->currentIndex()));
    map.insert("TurbulenceModel",QString::number(ui->CmB_TurbModel->currentIndex()));

    hasData = true;

    return hasData;
}

//*********************************************************************************
// Read data from JSON file
//*********************************************************************************
bool projectsettings::putData(QJsonObject &jsonObject, int stype)
{

    // Reset the data
    resetData();

//    // Project name
//    if(jsonObject.contains("ProjectName"))
//    {
//        ui->Led_PName->setText(jsonObject["ProjectName"].toString());
//    }

//    // Project description
//    if(jsonObject.contains("ProjectDescription"))
//    {
//        ui->Ted_PDesc->document()->setPlainText(jsonObject["ProjectDescription"].toString());
//    }

    // Simulation type
    ui->CmB_SimType->setCurrentIndex(stype);

    // Turbulence model
    if(jsonObject.contains("TurbulenceModel"))
    {
        ui->CmB_TurbModel->setCurrentIndex(jsonObject["TurbulenceModel"].toString().toInt());
    }

    // Return true
    return true;
}

//*********************************************************************************
// Show - hide elements
//*********************************************************************************
bool projectsettings::activateflume(int type)
{
    // Simulation type
    ui->CmB_SimType->setCurrentIndex(type);
    ui->CmB_SimType->setEnabled("False");

    // Return
    return true;
}

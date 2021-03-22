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
// Show - hide elements
//*********************************************************************************
void projectsettings::hideshowelems(int type)
{
    (void) type;
}

//*********************************************************************************
// Get data from project settings
//*********************************************************************************
bool projectsettings::getData(QMap<QString, QString> & map, int type)
{
    bool hasData=false;
    (void) type;

    map.insert("Project name",ui->Led_PName->text());
    map.insert("Project description",ui->Ted_PDesc->toPlainText());
    map.insert("Simulation type",QString::number(ui->CmB_SimType->currentIndex()));
    map.insert("Turbulence model",QString::number(ui->CmB_TurbModel->currentIndex()));

    hasData = true;

    return hasData;
}

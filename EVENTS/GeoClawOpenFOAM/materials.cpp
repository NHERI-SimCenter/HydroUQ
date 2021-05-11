#include "materials.h"
#include "ui_materials.h"

//*********************************************************************************
// Materials settings
//*********************************************************************************
materials::materials(int type, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::materials)
{
    ui->setupUi(this);

    // Initialize to show / hide elements
    hideshowelems(type);
}

//*********************************************************************************
// Delete materials settings
//*********************************************************************************
materials::~materials()
{
    delete ui;
}

//*********************************************************************************
// Refresh data
//*********************************************************************************
void materials::refreshData(int type)
{
    // Initialize to show / hide elements
    hideshowelems(type);
}

//*********************************************************************************
// Hide-show elements
//*********************************************************************************
void materials::hideshowelems(int type)
{
    (void) type;
}

//*********************************************************************************
// Get data from meshing
//*********************************************************************************
bool materials::getData(QMap<QString, QString>& map,int type)
{
    bool hasData=false;
    (void) type;

    // Add properties of water
    map.insert("WaterViscosity",ui->DSpBx_WaterVisc->textFromValue(ui->DSpBx_WaterVisc->value()));
    map.insert("WaterViscosityExp",ui->DSpBx_WaterViscExp->textFromValue(ui->DSpBx_WaterViscExp->value()));
    map.insert("WaterDensity",ui->DSpBx_WaterDen->textFromValue(ui->DSpBx_WaterDen->value()));

    // Add properties of air
    map.insert("AirViscosity",ui->DSpBx_AirVisc->textFromValue(ui->DSpBx_AirVisc->value()));
    map.insert("AirViscosityExp",ui->DSpBx_AirViscExp->textFromValue(ui->DSpBx_AirViscExp->value()));
    map.insert("AirDensity",ui->DSpBx_AirDen->textFromValue(ui->DSpBx_AirDen->value()));

    // Add surface tension
    map.insert("SurfaceTension",ui->DSpBx_SurfTen->textFromValue(ui->DSpBx_SurfTen->value()));

    // Change hasData to be true
    hasData = true;

    // Return the bool
    return hasData;

}

//*********************************************************************************
// Put data into materials from the JSON file
//*********************************************************************************
bool materials::putData(QJsonObject &jsonObject,int stype, QString workpath)
{
    // Suppress warnings
    (void) stype;
    (void) workpath;

    // Water properties
    if(jsonObject.contains("WaterViscosity"))
        ui->DSpBx_WaterVisc->setValue(jsonObject["WaterViscosity"].toString().toDouble());
    if(jsonObject.contains("WaterViscosityExp"))
        ui->DSpBx_WaterViscExp->setValue(jsonObject["WaterViscosityExp"].toString().toDouble());
    if(jsonObject.contains("WaterDensity"))
        ui->DSpBx_WaterDen->setValue(jsonObject["WaterDensity"].toString().toDouble());

    // Air properties
    if(jsonObject.contains("AirViscosity"))
        ui->DSpBx_AirVisc->setValue(jsonObject["AirViscosity"].toString().toDouble());
    if(jsonObject.contains("AirViscosityExp"))
        ui->DSpBx_AirViscExp->setValue(jsonObject["AirViscosityExp"].toString().toDouble());
    if(jsonObject.contains("AirDensity"))
        ui->DSpBx_AirDen->setValue(jsonObject["AirDensity"].toString().toDouble());

    // Surface tension
    if(jsonObject.contains("SurfaceTension"))
        ui->DSpBx_SurfTen->setValue(jsonObject["SurfaceTension"].toString().toDouble());

    // Return true
    return true;
}

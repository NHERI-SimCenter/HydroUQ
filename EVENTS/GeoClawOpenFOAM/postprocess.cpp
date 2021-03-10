#include "postprocess.h"
#include "ui_postprocess.h"

#include <QFileInfo>
#include <QDebug>

//*********************************************************************************
// Postprocessing settings
//*********************************************************************************
postprocess::postprocess(int type, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::postprocess)
{
    ui->setupUi(this);

    // Initialize to show / hide elements
    hideshowelems(type);
}

//*********************************************************************************
// Delete Postprocessing settings
//*********************************************************************************
postprocess::~postprocess()
{
    delete ui;
}

//*********************************************************************************
// Refresh data
//*********************************************************************************
void postprocess::refreshData(int type)
{
    qDebug() << "Arrived here";
    // Initialize to show / hide elements
    hideshowelems(type);
}

//*********************************************************************************
// Get data from bathymetry
//*********************************************************************************
bool postprocess::getData(QMap<QString, QString>& map,int type)
{
    bool hasData=false;

    // Insert data into map
    map.insert("Postprocess",QString::number(100));

    // Change hasData to be true
    hasData = true;

    // Return the bool
    return hasData;
}

//*********************************************************************************
// Show - hide elements (initially at start)
//*********************************************************************************
void postprocess::hideshowelems(int type)
{
    if(ui->CmB_Probelocation->currentIndex() == 0) // No postprocessing
    {
        ui->Btn_UploadFiles->hide();
        ui->Lbl_Probes->hide();
        ui->Tbl_Probes->hide();
        ui->Btn_AddProbe->hide();
        ui->Btn_RemProbe->hide();
    }
    else if(ui->CmB_Probelocation->currentIndex() == 0) // Manual addition
    {

    }
}

//*********************************************************************************
// Show - hide elements (initially at start)
//*********************************************************************************
void postprocess::hideshowelems2()
{
    if(ui->CmB_Probelocation->currentIndex() == 0) // No postprocessing
    {
        ui->Btn_UploadFiles->hide();
        ui->Lbl_Probes->hide();
        ui->Tbl_Probes->hide();
        ui->Btn_AddProbe->hide();
        ui->Btn_RemProbe->hide();
    }
    else if(ui->CmB_Probelocation->currentIndex() == 1) // Manual addition
    {
        ui->Btn_UploadFiles->hide();
        ui->Lbl_Probes->show();
        ui->Tbl_Probes->show();
        ui->Btn_AddProbe->show();
        ui->Btn_RemProbe->show();
    }
    else if(ui->CmB_Probelocation->currentIndex() == 2) // CSV File
    {
        ui->Btn_UploadFiles->show();
        ui->Lbl_Probes->hide();
        ui->Tbl_Probes->hide();
        ui->Btn_AddProbe->hide();
        ui->Btn_RemProbe->hide();
    }
}

//*********************************************************************************
// What to do when user chooses different option
//*********************************************************************************
void postprocess::on_CmB_Probelocation_currentIndexChanged(int index)
{
    hideshowelems2();
}

//*********************************************************************************
// Add probe locations
//*********************************************************************************
void postprocess::on_Btn_AddProbe_clicked()
{
    ui->Tbl_Probes->insertRow(ui->Tbl_Probes->rowCount());
}

//*********************************************************************************
// Remove probe locations
//*********************************************************************************
void postprocess::on_Btn_RemProbe_clicked()
{
    ui->Tbl_Probes->removeRow(ui->Tbl_Probes->currentRow());
}

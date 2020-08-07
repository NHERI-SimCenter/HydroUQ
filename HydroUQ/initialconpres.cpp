#include "initialconpres.h"
#include "ui_initialconpres.h"

//*********************************************************************************
// Initial conditions: Pressure
//*********************************************************************************
initialconPres::initialconPres(int type, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::initialconPres)
{
    ui->setupUi(this);

    // Initialize to show / hide elements
    hideshowelems(type);
}

//*********************************************************************************
// Delete initial conditions: Pressure
//*********************************************************************************
initialconPres::~initialconPres()
{
    delete ui;
}

//*********************************************************************************
// Show - hide elements
//*********************************************************************************
void initialconPres::hideshowelems(int type)
{
    if((type == 1) || (type == 2))
    {
        ui->Lbl_Notice->show();
        ui->Lbl_Pres->hide();
        ui->DSpBx_Pres->hide();
        ui->Lbl_Regions->hide();
        ui->Tbl_IniCondTable->hide();
        ui->Btn_AddRegion->hide();
        ui->Btn_RemRegion->hide();
    }
    else
    {
        ui->Lbl_Notice->hide();
        ui->Lbl_Pres->show();
        ui->DSpBx_Pres->show();
        ui->Lbl_Regions->show();
        ui->Tbl_IniCondTable->show();
        ui->Btn_AddRegion->show();
        ui->Btn_RemRegion->show();
    }
}

//*********************************************************************************
// Get data from initial phase
//*********************************************************************************
bool initialconPres::getData(QMap<QString, QString>& map,int type)
{
    bool hasData = false;

    // If not dealing with SW-solutions
    if((type != 1) || (type != 2))
    {
        map.insert("Initial pressure global",ui->DSpBx_Pres->textFromValue(ui->DSpBx_Pres->value()));
        if(ui->Tbl_IniCondTable->rowCount() > 0)
        {
            for(int ii=0;ii<ui->Tbl_IniCondTable->rowCount(); ++ii)
            {
                QString presdata = ui->Tbl_IniCondTable->item(ii,0)->text() +
                        "," + ui->Tbl_IniCondTable->item(ii,1)->text() +
                        "," + ui->Tbl_IniCondTable->item(ii,2)->text();
                map.insert("Initial pressure local"+QString::number(ii),presdata);
            }
        }

    }

    return hasData;
}

//*********************************************************************************
// Add regions for pressure initial condition
//*********************************************************************************
void initialconPres::on_Btn_AddRegion_clicked()
{
    ui->Tbl_IniCondTable->insertRow(ui->Tbl_IniCondTable->rowCount());
}

//*********************************************************************************
// Remove regions for pressure initial condition
//*********************************************************************************
void initialconPres::on_Btn_RemRegion_clicked()
{

}

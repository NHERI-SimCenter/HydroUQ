#include "initialconalpha.h"
#include "ui_initialconalpha.h"

//*********************************************************************************
// Initial conditions: Alpha
//*********************************************************************************
initialconAlpha::initialconAlpha(int type, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::initialconAlpha)
{
    ui->setupUi(this);

    // Initialize to show / hide elements
    hideshowelems(type);
}

//*********************************************************************************
// Initial conditions: Alpha (Delete)
//*********************************************************************************
initialconAlpha::~initialconAlpha()
{
    delete ui;
}

//*********************************************************************************
// Show - hide elements
//*********************************************************************************
void initialconAlpha::hideshowelems(int type)
{
    if((type == 1) || (type == 2))
    {
        ui->Lbl_Notice->show();
        ui->Lbl_Alpha->hide();
        ui->DSpBx_Alpha->hide();
        ui->Lbl_Regions->hide();
        ui->Tbl_IniCondTable->hide();
        ui->Btn_AddRegion->hide();
        ui->Btn_RemRegion->hide();
    }
    else
    {
        ui->Lbl_Notice->hide();
        ui->Lbl_Alpha->show();
        ui->DSpBx_Alpha->show();
        ui->Lbl_Regions->show();
        ui->Tbl_IniCondTable->show();
        ui->Btn_AddRegion->show();
        ui->Btn_RemRegion->show();
    }
}

//*********************************************************************************
// Get data from initial phase
//*********************************************************************************
bool initialconAlpha::getData(QMap<QString, QString>& map,int type)
{
    bool hasData = false;

    // If not dealing with SW-solutions
    if((type != 1) || (type != 2))
    {
        map.insert("Initial alpha global",ui->DSpBx_Alpha->textFromValue(ui->DSpBx_Alpha->value()));
        if(ui->Tbl_IniCondTable->rowCount() > 0)
        {
            for(int ii=0;ii<ui->Tbl_IniCondTable->rowCount(); ++ii)
            {
                QString alphadata = ui->Tbl_IniCondTable->item(ii,0)->text() +
                        "," + ui->Tbl_IniCondTable->item(ii,1)->text() +
                        "," + ui->Tbl_IniCondTable->item(ii,2)->text();
                map.insert("Initial alpha local"+QString::number(ii),alphadata);
            }
        }

    }

    return hasData;
}

//*********************************************************************************
// Add regions for alpha initial condition
//*********************************************************************************
void initialconAlpha::on_Btn_AddRegion_clicked()
{
    ui->Tbl_IniCondTable->insertRow(ui->Tbl_IniCondTable->rowCount());
}

//*********************************************************************************
// Remove regions for alpha initial condition
//*********************************************************************************
void initialconAlpha::on_Btn_RemRegion_clicked()
{

}

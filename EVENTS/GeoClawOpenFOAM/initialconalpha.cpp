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
// Refresh data
//*********************************************************************************
void initialconAlpha::refreshData(int type)
{
    // Initialize to show / hide elements
    hideshowelems(type);
}

//*********************************************************************************
// Show - hide elements
//*********************************************************************************
void initialconAlpha::hideshowelems(int type)
{
    if(type == 1)
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
    //if((type != 1) || (type != 2))
    if(type > 2)
    {
        map.insert("InitialAlphaGlobal",ui->DSpBx_Alpha->textFromValue(ui->DSpBx_Alpha->value()));
        map.insert("NumAlphaRegion",QString::number(ui->Tbl_IniCondTable->rowCount()));
        if(ui->Tbl_IniCondTable->rowCount() > 0)
        {
            for(int ii=0;ii<ui->Tbl_IniCondTable->rowCount(); ++ii)
            {
                QString alphadata = ui->Tbl_IniCondTable->item(ii,0)->text() +
                        "," + ui->Tbl_IniCondTable->item(ii,1)->text() +
                        "," + ui->Tbl_IniCondTable->item(ii,2)->text();
                map.insert("InitialAlphaRegion"+QString::number(ii),alphadata);
            }
        }
    }

    // Change hasData to be true
    hasData = true;

    // Return the bool
    return hasData;
}

//*********************************************************************************
// Put data into alpha initial condition from the JSON file
//*********************************************************************************
bool initialconAlpha::putData(QJsonObject &jsonObject,int stype, QString workpath)
{
    // Suppress warnings
    (void) workpath;

    // For all simulations except SW-CFD
    if(stype !=1)
    {
        // Get the global value of alpha
        if(jsonObject.contains("InitialAlphaGlobal"))
            ui->DSpBx_Alpha->setValue(jsonObject["InitialAlphaGlobal"].toString().toDouble());

        // Fill the alpha table
        if(jsonObject.contains("NumAlphaRegion"))
        {
            int numalphareg = jsonObject["NumAlphaRegion"].toString().toInt();
            if(numalphareg > 0)
            {
                for(int ii=0; ii<numalphareg; ++ii)
                {
                    // Add a row for the building
                    ui->Tbl_IniCondTable->insertRow(ui->Tbl_IniCondTable->rowCount());
                    // Add the particular building parameters
                    if(jsonObject.contains("InitialAlphaRegion"+QString::number(ii)))
                    {
                        // Get the parameters for each building / building table row
                        QString alphareg = jsonObject["InitialAlphaRegion"+QString::number(ii)].toString();
                        QStringList alpharegdata = alphareg.split(',');
                        if(alpharegdata.size() == 7)
                        {
                            QTableWidgetItem* itemtoAdd = new QTableWidgetItem();
                            QTableWidgetItem* itemtoAdd2 = new QTableWidgetItem();
                            QTableWidgetItem* itemtoAdd3 = new QTableWidgetItem();
                            itemtoAdd->setText(alpharegdata[0]+","+alpharegdata[1]+","+alpharegdata[2]);
                            ui->Tbl_IniCondTable->setItem(ii,0,itemtoAdd);
                            itemtoAdd2->setText(alpharegdata[3]+","+alpharegdata[4]+","+alpharegdata[5]);
                            ui->Tbl_IniCondTable->setItem(ii,1,itemtoAdd2);
                            itemtoAdd3->setText(alpharegdata[6]);
                            ui->Tbl_IniCondTable->setItem(ii,2,itemtoAdd3);
                        }
                    }
                }
            }
        }
    }

    // Return true
    return true;
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
    ui->Tbl_IniCondTable->removeRow(ui->Tbl_IniCondTable->currentRow());
}

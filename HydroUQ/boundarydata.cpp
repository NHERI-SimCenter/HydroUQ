#include "boundarydata.h"
#include "ui_boundarydata.h"

//*********************************************************************************
// Boundary conditions data settings widget
//*********************************************************************************
boundaryData::boundaryData(const QString titleString, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::boundaryData)
{
    ui->setupUi(this);
    ui->Lbl_H1->setText(titleString);

    // Initialize to show / hide elements
    hideshowelems();
}

//*********************************************************************************
// Delete Boundary conditions data settings
//*********************************************************************************
boundaryData::~boundaryData()
{
    delete ui;
}

//*********************************************************************************
// Show - hide elements
//*********************************************************************************
void boundaryData::hideshowelems()
{
    // Vel UI components
    on_Cmb_UBC_currentIndexChanged(ui->Cmb_UBC->currentIndex());

    // Pres UI components
    on_Cmb_PresBC_currentIndexChanged(ui->Cmb_PresBC->currentIndex());
}

//*********************************************************************************
// When U-BC option is changed
//*********************************************************************************
void boundaryData::on_Cmb_UBC_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->Btn_UploadFile->hide();
        ui->Cmb_WaveType->hide();
        ui->Lbl_Umean->hide();
        ui->DSpBx_UMeanX->hide();
        ui->DSpBx_UMeanY->hide();
        ui->DSpBx_UMeanZ->hide();
        ui->Lbl_Origin->hide();
        ui->DSpBx_OX->hide();
        ui->DSpBx_OY->hide();
        ui->DSpBx_OZ->hide();
        ui->Lbl_Dirn->hide();
        ui->DSpBx_DirnX->hide();
        ui->DSpBx_DirnY->hide();
        ui->DSpBx_DirnZ->hide();
        ui->Lbl_WavePara->hide();
        ui->Led_WavePara->hide();
    }

    if(((index == 1) || (index == 5)) || (index == 7)) // Uniform velocityinlet/outlet
    {
        if(index == 1) ui->Lbl_Umean->setText("Velocity");
        else if(index == 5) ui->Lbl_Umean->setText("UMean");
        else if(index == 7) ui->Lbl_Umean->setText("UMean");

        ui->Btn_UploadFile->hide();
        ui->Cmb_WaveType->hide();
        ui->Lbl_Umean->show();
        ui->DSpBx_UMeanX->show();
        ui->DSpBx_UMeanY->show();
        ui->DSpBx_UMeanZ->show();
        ui->Lbl_Origin->hide();
        ui->DSpBx_OX->hide();
        ui->DSpBx_OY->hide();
        ui->DSpBx_OZ->hide();
        ui->Lbl_Dirn->hide();
        ui->DSpBx_DirnX->hide();
        ui->DSpBx_DirnY->hide();
        ui->DSpBx_DirnZ->hide();
        ui->Lbl_WavePara->hide();
        ui->Led_WavePara->hide();
    }
    else if(index == 2)
    {
        ui->Btn_UploadFile->hide();
        ui->Cmb_WaveType->show();
        ui->Lbl_Umean->show();
        ui->Lbl_Umean->setText("Umean");
        ui->DSpBx_UMeanX->show();
        ui->DSpBx_UMeanY->show();
        ui->DSpBx_UMeanZ->show();
        ui->Lbl_Origin->show();
        ui->DSpBx_OX->show();
        ui->DSpBx_OY->show();
        ui->DSpBx_OZ->show();
        ui->Lbl_Dirn->show();
        ui->DSpBx_DirnX->show();
        ui->DSpBx_DirnY->show();
        ui->DSpBx_DirnZ->show();
        ui->Lbl_WavePara->show();
        ui->Led_WavePara->show();
    }
    else if((index == 3) || (index == 4))
    {
        ui->Btn_UploadFile->show();
        ui->Cmb_WaveType->hide();
        ui->Lbl_Umean->hide();
        //ui->Lbl_Umean->setText("Umean");
        ui->DSpBx_UMeanX->hide();
        ui->DSpBx_UMeanY->hide();
        ui->DSpBx_UMeanZ->hide();
        ui->Lbl_Origin->hide();
        ui->DSpBx_OX->hide();
        ui->DSpBx_OY->hide();
        ui->DSpBx_OZ->hide();
        ui->Lbl_Dirn->hide();
        ui->DSpBx_DirnX->hide();
        ui->DSpBx_DirnY->hide();
        ui->DSpBx_DirnZ->hide();
        ui->Lbl_WavePara->hide();
        ui->Led_WavePara->hide();
    }
    else if((index == 6) || (index == 8))
    {
        if(index == 6)
        {
            ui->Lbl_Umean->setText("Flow rate");
            ui->Lbl_Umean->show();
            ui->DSpBx_UMeanX->show();
        }
        else
        {
            ui->Lbl_Umean->hide();
            ui->DSpBx_UMeanX->hide();
        }
        ui->Btn_UploadFile->hide();
        ui->Cmb_WaveType->hide();
        ui->DSpBx_UMeanY->hide();
        ui->DSpBx_UMeanZ->hide();
        ui->Lbl_Origin->hide();
        ui->DSpBx_OX->hide();
        ui->DSpBx_OY->hide();
        ui->DSpBx_OZ->hide();
        ui->Lbl_Dirn->hide();
        ui->DSpBx_DirnX->hide();
        ui->DSpBx_DirnY->hide();
        ui->DSpBx_DirnZ->hide();
        ui->Lbl_WavePara->hide();
        ui->Led_WavePara->hide();
    }
}

//*********************************************************************************
// When pressure-BC option is changed
//*********************************************************************************
void boundaryData::on_Cmb_PresBC_currentIndexChanged(int index)
{
    if((index == 1) || (index == 0))
    {
        ui->Lbl_Pres->hide();
        ui->DSpBx_Pres->hide();
    }
    else
    {
        ui->Lbl_Pres->show();
        ui->DSpBx_Pres->show();
        if((index == 2)||(index==3)) ui->Lbl_Pres->setText("Pressure");
        else if(index == 4) ui->Lbl_Pres->setText("Pressure gradient");
    }
}

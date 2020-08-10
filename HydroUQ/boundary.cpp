#include "boundary.h"
#include "ui_boundary.h"
#include "boundarydata.h"

//*********************************************************************************
// Boundary conditions settings
//*********************************************************************************
boundary::boundary(int type, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::boundary)
{
    ui->setupUi(this);

    // Initialize to show / hide elements
    hideshowelems(type);
}

//*********************************************************************************
// Delete Boundary conditions settings
//*********************************************************************************
boundary::~boundary()
{
    delete ui;
}

//*********************************************************************************
// Refresh building settings
//*********************************************************************************
void boundary::refreshData(int type)
{
    // Initialize to show / hide elements
    hideshowelems(type);
}

//*********************************************************************************
// Show - hide elements
//*********************************************************************************
void boundary::hideshowelems(int type)
{
    //(void) type;
    //on_Cmb_MeshType_currentIndexChanged(ui->Cmb_MeshType->currentIndex());
    if((type == 1) || (type == 2))
    {
        ui->Lbl_Notice->show();
        ui->SWg_Interface->hide();
        ui->Btn_AddBoundary->hide();
        ui->Btn_RemBoundary->hide();
        ui->Btn_Next->hide();
        ui->Btn_Previous->hide();
    }
    else
    {
        ui->Lbl_Notice->hide();
        ui->SWg_Interface->show();
        ui->Btn_AddBoundary->show();
        ui->Btn_RemBoundary->show();
        ui->Btn_Next->show();
        ui->Btn_Previous->show();
    }

}

//*********************************************************************************
// Get data from meshing
//*********************************************************************************
bool boundary::getData(QMap<QString, QString>& map,int type)
{
    (void) map;
    (void) type;

    QMap<QString, QString> *singleData;
    int numberOfPanes = ui->SWg_Interface->count();
    for (int i=0;i<numberOfPanes;i++)
    {
        singleData = new QMap<QString,QString>;
        if(i>0)
        {
            // Loop over the entire map and insert each key and value
            //map.insert(singleData);
        }
    }

}

//*********************************************************************************
// Add Boundary
//*********************************************************************************
void boundary::on_Btn_AddBoundary_clicked()
{
    bool ok;
    QString bpatchname = QInputDialog::getText(this, tr("Add boundary conditions"),
                                            tr("Boundary patch name"), QLineEdit::Normal,
                                            QDir::home().dirName(), &ok);

    if(ok && !bpatchname.isEmpty())
    {
        int patchcount = ui->SWg_Interface->count();
        ui->SWg_Interface->addWidget(new boundaryData(bpatchname));
        ui->SWg_Interface->setCurrentIndex(patchcount);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Critical error!");
        msgBox.setInformativeText("A patch name is required to set the boundary!");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
    }
}

//*********************************************************************************
// Move to next boundary
//*********************************************************************************
void boundary::on_Btn_Next_clicked()
{
    int ind = ui->SWg_Interface->currentIndex();
    if(ind < ui->SWg_Interface->count())
    {
        ui->SWg_Interface->setCurrentIndex(ind+1);
    }
}

//*********************************************************************************
// Move to previous boundary
//*********************************************************************************
void boundary::on_Btn_Previous_clicked()
{
    int ind = ui->SWg_Interface->currentIndex();
    if(ind > 0)
    {
        ui->SWg_Interface->setCurrentIndex(ind-1);
    }
}


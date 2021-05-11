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
    (void) type;
    ui->Lbl_Notice->hide();
    ui->SWg_Interface->show();
    ui->Btn_AddBoundary->show();
    ui->Btn_RemBoundary->show();
    ui->Btn_Next->show();
    ui->Btn_Previous->show();
}

//*********************************************************************************
// Get data from boundary
//*********************************************************************************
bool boundary::getData(QMap<QString, QString>& map,int type)
{
    bool hasData=false;

    QMap<QString, QString> *singleData;
    singleData = new QMap<QString,QString>;
    int numberOfPanes = ui->SWg_Interface->count();
    map.insert("NumberOfBoundaries",QString::number(numberOfPanes));
    for (int i=0;i<numberOfPanes;i++)
    {
        if (dynamic_cast<boundaryData *>(ui->SWg_Interface->widget(i))->getData(*singleData,type,i))
        {
            // Loop over the entire map and insert all elements
            foreach(QString varname, singleData->keys())
            {
                map.insert(varname,singleData->value(varname));
            }

            // Clear the QMap
            singleData->clear();
        }
    }

    // Change hasData to be true
    hasData = true;

    // Return the bool
    return hasData;
}

//*********************************************************************************
// Put data to boundary
//*********************************************************************************
bool boundary::putData(QJsonObject &jsonObject,int stype,QString workpath)
{

    // Get the number of boundary panes
    int numboun = 0;
    QString bpatchname;
    if(jsonObject.contains("NumberOfBoundaries"))
        numboun = jsonObject["NumberOfBoundaries"].toString().toInt();

    // Loop over all the patches
    for(int ii=0; ii<numboun; ++ii)
    {
        // Get the patchname
        if(jsonObject.contains("BounPatch"+QString::number(ii)))
        {
            // If patch name exists
            bpatchname = jsonObject["BounPatch"+QString::number(ii)].toString();

            // Add the patch
            ui->SWg_Interface->addWidget(new boundaryData(bpatchname));

            // Put the data into this patch
            dynamic_cast<boundaryData *>(ui->SWg_Interface->widget(ii))->putData(jsonObject,stype,workpath,bpatchname);
        }
        else
        {   // if no patchname
            bpatchname = "patch" + QString::number(ii);

            // Add the patch
            ui->SWg_Interface->addWidget(new boundaryData(bpatchname));
        }
    }

    // Return true
    return true;
}

//*********************************************************************************
// Copyfiles
//*********************************************************************************
bool boundary::copyFiles(QString dirName,int type)
{
    (void) type;

    // Initialize if has data
    bool hasdata = false;

    // Copy the data from each pane
    int numberOfPanes = ui->SWg_Interface->count();
    for (int i=0;i<numberOfPanes;i++)
    {
        dynamic_cast<boundaryData *>(ui->SWg_Interface->widget(i))->copyFiles(dirName,type);
    }

    // Return if data exists
    return hasdata;
}

//*********************************************************************************
// Add Boundary
//*********************************************************************************
void boundary::on_Btn_AddBoundary_clicked()
{
    bool ok;
    QString temppname = "patch_" + QString::number(ui->SWg_Interface->count());
    QString bpatchname = QInputDialog::getText(this, tr("Add boundary conditions"),
                                            tr("Boundary patch name"), QLineEdit::Normal,
                                            temppname, &ok);

    if(ok && !bpatchname.isEmpty())
    {
        int patchcount = ui->SWg_Interface->count();
        ui->SWg_Interface->addWidget(new boundaryData(bpatchname));
        ui->SWg_Interface->setCurrentIndex(patchcount);
    }
    else
    {
        int patchcount = ui->SWg_Interface->count();
        bpatchname = "patch" + QString::number(patchcount);
    }
}

//*********************************************************************************
// Remove Boundary
//*********************************************************************************
void boundary::on_Btn_RemBoundary_clicked()
{
    int patchcount = ui->SWg_Interface->count();
    if(patchcount > 0)
    {
        --patchcount;
        ui->SWg_Interface->removeWidget(ui->SWg_Interface->widget(patchcount));
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




#include "bathymetry.h"
#include "ui_bathymetry.h"

//*********************************************************************************
// Bathymetry settings
//*********************************************************************************
bathymetry::bathymetry(int type, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::bathymetry)
{
    ui->setupUi(this);

    // Initialize to show / hide elements
    hideshowelems(type);
}

//*********************************************************************************
// Delete Bathymetry settings
//*********************************************************************************
bathymetry::~bathymetry()
{
    delete ui;
}

//*********************************************************************************
// Refresh data
//*********************************************************************************
void bathymetry::refreshData(int type)
{
    // Initialize to show / hide elements
    hideshowelems(type);
}

//*********************************************************************************
// Show - hide elements
//*********************************************************************************
void bathymetry::hideshowelems(int type)
{
    // Hide - Show elements
    if(type == 4)
    {
        // Set heading
        ui->Lbl_H1->setText("<b>WAVE FLUME SETTINGS</b>");

        // Show wave flume
        ui->Lbl_SideViewH2->show();
        ui->Lbl_SideView->show();
        ui->Lbl_Depth->show();
        ui->DSpBx_Depth->show();
        ui->Lbl_TopViewH2->show();
        ui->Lbl_TopView->show();
        ui->Lbl_Breadth->show();
        ui->DSpBx_Breadth->show();
        ui->Lbl_Segments->show();
        ui->Tbl_Segments->show();
        ui->Btn_AddSeg->show();
        ui->Btn_RemSeg->show();

        // Hide all other elements
        ui->Lbl_SelFiles->hide();
        ui->Btn_UploadFiles->hide();
        ui->Btn_UploadSolution->hide();
        ui->CmB_FileType->hide();
        ui->CmB_SolFormat->hide();
        ui->CmB_Library->hide();
        ui->Lbl_Notice->hide();
    }
    else
    {
        // Hide wave flume
        ui->Lbl_SideViewH2->hide();
        ui->Lbl_SideView->hide();
        ui->Lbl_Depth->hide();
        ui->DSpBx_Depth->hide();
        ui->Lbl_TopViewH2->hide();
        ui->Lbl_TopView->hide();
        ui->Lbl_Breadth->hide();
        ui->DSpBx_Breadth->hide();
        ui->Lbl_Segments->hide();
        ui->Tbl_Segments->hide();
        ui->Btn_AddSeg->hide();
        ui->Btn_RemSeg->hide();
    }

    // If STL / Maps / Surrogate - show only notice
    if( ((type == 5)
            || (type == 6))
            || (type == 7))
    {
        // Set heading and notice
        if(type == 5)
        {
            ui->Lbl_H1->setText("<b>STL/OBJ FILE SETTINGS</b>");
            ui->Lbl_Notice->setText("STL option is not yet available. "
                                       "Watch out for future updates");
        }
        else if(type == 6)
        {
            ui->Lbl_H1->setText("<b>BATHYMETRY USING MAPS</b>");
            ui->Lbl_Notice->setText("Maps option is not yet available. "
                                       "Watch out for future updates");
        }
        else if(type == 7)
        {
            ui->Lbl_H1->setText("<b>BATHYMETRY FOR SURROGATE MODELS</b>");
            ui->Lbl_Notice->setText("Surrogate model option is not yet available. "
                                       "Watch out for future updates");
        }

        // Show notice
        ui->Lbl_Notice->show();

        // Hide all other elements
        ui->Lbl_SelFiles->hide();
        ui->Btn_UploadFiles->hide();
        ui->Btn_UploadSolution->hide();
        ui->CmB_FileType->hide();
        ui->CmB_SolFormat->hide();
        ui->CmB_Library->hide();
    }
    else
    {
        // Hide the notice
        ui->Lbl_Notice->hide();
    }

    // Show-Hide elements based on type of simulations
    if(type == 1) //SW solutions
    {
        // Set the heading
        ui->Lbl_H1->setText("<b>BATHYMETRY AND SW SOLUTIONS</b>");

        // Show bathy items
        ui->Btn_UploadFiles->show();
        ui->Btn_UploadSolution->show();
        ui->CmB_FileType->show();
        ui->CmB_SolFormat->show();

        // Hide library items
        ui->CmB_Library->hide();
    }
    else if(type == 2) //Library
    {
        // Set the heading
        ui->Lbl_H1->setText("<b>BATHYMETRY AND SW LIBRRAY</b>");

        // Show library items
        ui->CmB_Library->show();

        // Hide bathy items
        ui->Btn_UploadFiles->hide();
        ui->Btn_UploadSolution->hide();
        ui->CmB_FileType->hide();
        ui->CmB_SolFormat->hide();
    }
    else if(type == 3) // Bathymetry files
    {
        // Set the heading
        ui->Lbl_H1->setText("<b>BATHYMETRY FILE SETTINGS</b>");

        // Show bathy items
        ui->Btn_UploadFiles->show();
        ui->CmB_FileType->show();

        // Hide solutions and library items
        ui->Btn_UploadSolution->hide();
        ui->CmB_SolFormat->hide();
        ui->CmB_Library->hide();
    }
}

//*********************************************************************************
// Get data from bathymetry
//*********************************************************************************
bool bathymetry::getData(QMap<QString, QString>& map,int type)
{
    bool hasData=false;

    // Shallow water bathymetry files
    if(((type == 1) || (type == 2)) || (type == 3))
    {
        map.insert("Bathymetry file number",QString::number(bathfilenames.size()));
        // Write the bathymetry file names
        for (int ii=0; ii<bathfilenames.size(); ++ii)
        {
            map.insert("Bathymetry file"+QString::number(ii),bathfilenames[ii]);
        }
    }

    // Shallow water solutions
    if(type == 1)
    {
        map.insert("Solution files number",QString::number(solfilenames.size()));
        // Write the solution file names
        for (int ii=0; ii<solfilenames.size(); ++ii)
        {
            map.insert("SW solution file"+QString::number(ii),solfilenames[ii]);
        }
        // Type of bathymetry
        map.insert("Bathymetry file type",QString::number(ui->CmB_FileType->currentIndex()));
        // Type of solution file
        map.insert("Solution file type",QString::number(ui->CmB_SolFormat->currentIndex()));
    }

    // SimCenter library
    if(type == 2)
        map.insert("SimCenter Library",QString::number(ui->CmB_Library->currentIndex()));

    // Only bathymetry
    if(type == 3)
    {
        // Type of bathymetry
        map.insert("Bathymetry file type",QString::number(ui->CmB_FileType->currentIndex()));
    }

    // Wave flume
    if(type == 4)
    {
        map.insert("Flume water depth",ui->DSpBx_Depth->textFromValue(ui->DSpBx_Depth->value()));
        map.insert("Flume water depth",ui->DSpBx_Breadth->textFromValue(ui->DSpBx_Breadth->value()));
        if(ui->Tbl_Segments->rowCount() > 0)
        {
            for(int ii=0;ii<ui->Tbl_Segments->rowCount(); ++ii)
            {
                QString segdata = ui->Tbl_Segments->item(ii,0)->text() +
                        "," + ui->Tbl_Segments->item(ii,1)->text();
                map.insert("Flume segment"+QString::number(ii),segdata);
            }
        }
    }

    // Change hasData to be true
    hasData = true;

    // Return the bool
    return hasData;
}

//*********************************************************************************
// Select bathymetry files
//*********************************************************************************
void bathymetry::on_Btn_UploadFiles_clicked()
{
    // Open a dialog window to select the files
    // Here one can select multiple files
    // The selected files are stored in the String list intefilenames (declared in mainwindow.h)
    QFileDialog selectfilesdialog(this);
    selectfilesdialog.setFileMode(QFileDialog::ExistingFiles);
    selectfilesdialog.setNameFilter(tr("All files (*.*)"));
    if(selectfilesdialog.exec()) bathfilenames = selectfilesdialog.selectedFiles();
}

//*********************************************************************************
// Select SW solution files
//*********************************************************************************
void bathymetry::on_Btn_UploadSolution_clicked()
{
    // Open a dialog window to select the files
    // Here one can select multiple files
    // The selected files are stored in the String list intefilenames (declared in mainwindow.h)
    QFileDialog selectfilesdialog(this);
    selectfilesdialog.setFileMode(QFileDialog::ExistingFiles);
    selectfilesdialog.setNameFilter(tr("All files (*.*)"));
    if(selectfilesdialog.exec()) solfilenames = selectfilesdialog.selectedFiles();
}

//*********************************************************************************
// Add segments to flume
//*********************************************************************************
void bathymetry::on_Btn_AddSeg_clicked()
{
    ui->Tbl_Segments->insertRow(ui->Tbl_Segments->rowCount());
}

//*********************************************************************************
// Delete segments from flume
//*********************************************************************************
void bathymetry::on_Btn_RemSeg_clicked()
{

}

//*********************************************************************************
// Copyfiles
//*********************************************************************************
bool bathymetry::copyFiles(QString dirName)
{
    qDebug() << bathfilenames;
    for (int ii=0; ii<bathfilenames.size(); ++ii)
    {
        QFile::copy(bathfilenames[ii], dirName);
    }


    //(void) dirName;
    return true;
}

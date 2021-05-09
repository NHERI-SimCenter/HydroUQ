#include "meshing.h"
#include "ui_meshing.h"

//*********************************************************************************
// Meshing settings
//*********************************************************************************
meshing::meshing(int type, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::meshing)
{
    ui->setupUi(this);

    // Initialize to show / hide elements
    hideshowelems(type);
}

//*********************************************************************************
// Delete meshing settings
//*********************************************************************************
meshing::~meshing()
{
    delete ui;
}

//*********************************************************************************
// Refresh data
//*********************************************************************************
void meshing::refreshData(int type)
{
    // Initialize to show / hide elements
    hideshowelems(type);
}

//*********************************************************************************
// Show - hide elements
//*********************************************************************************
void meshing::hideshowelems(int type)
{
    (void) type;
    on_Cmb_MeshType_currentIndexChanged(ui->Cmb_MeshType->currentIndex());
}

//*********************************************************************************
// Change elements when item in combo box is changed
//*********************************************************************************
void meshing::on_Cmb_MeshType_currentIndexChanged(int index)
{

    // Show the selection boxes
    ui->Lbl_MeshType->show();
    ui->Cmb_MeshType->show();

    // Hide everything else by default
    ui->Btn_UploadMesh->hide();
    ui->Lbl_FineH2->hide();
    ui->HSl_MeshSize->hide();
    ui->Lbl_FineMesh->hide();
    ui->Lbl_CoarseMesh->hide();
    ui->Lbl_H2Regions->hide();
    ui->Tbl_Regions->hide();
    ui->Btn_AddRegion->hide();
    ui->Btn_RemRegion->hide();
    ui->Lbl_MeshGen->hide();
    ui->Cmb_MeshGen->hide();

    // Hide / Unhide elements based on mesh options
    if(index == 0) // In-built mesher
    {
        ui->Lbl_FineH2->show();
        ui->HSl_MeshSize->show();
        ui->Lbl_CoarseMesh->show();
        ui->Lbl_FineMesh->show();
        ui->Lbl_H2Regions->show();
        ui->Tbl_Regions->show();
        ui->Btn_AddRegion->show();
        ui->Btn_RemRegion->show();
    }
    else // Upload mesh / mesh dictionaries
    {
        ui->Btn_UploadMesh->show();
        ui->Lbl_MeshGen->show();
        ui->Cmb_MeshGen->show();
    }

    // Change name on the button
    if(index == 1)
    {
        ui->Btn_UploadMesh->setText("\nUpload mesh files\n");
        ui->Lbl_MeshGen->show();
        ui->Cmb_MeshGen->show();
    }
    else if(index == 2)
    {
        ui->Btn_UploadMesh->setText("\nUpload mesh dictionary files\n");
        ui->Lbl_MeshGen->hide();
        ui->Cmb_MeshGen->hide();
    }
}

//*********************************************************************************
// Get data from meshing
//*********************************************************************************
bool meshing::getData(QMap<QString, QString>& map,int type)
{
    bool hasData=false;
    (void) type;

    // Get type of meshing
    int index = ui->Cmb_MeshType->currentIndex();

    // Insert mesh type
    map.insert("MeshType",QString::number(ui->Cmb_MeshType->currentIndex()));

    // If internal meshing
    if(index == 0) // Our own meshing
    {
        // Fineness of mesh to be generated
        map.insert("MeshSize",QString::number(ui->HSl_MeshSize->value()));
        // Write data from the table
        map.insert("NumMeshRefine",QString::number(ui->Tbl_Regions->rowCount()));
        if(ui->Tbl_Regions->rowCount() > 0)
        {
            for(int ii=0;ii<ui->Tbl_Regions->rowCount(); ++ii)
            {
                QString regdata = ui->Tbl_Regions->item(ii,0)->text() +
                        "," + ui->Tbl_Regions->item(ii,1)->text() +
                        "," + ui->Tbl_Regions->item(ii,1)->text();
                map.insert("MeshRegion"+QString::number(ii),regdata);
            }
        }
    }
    else if(index == 1) // Mesh from other software
    {
        //Mesh generating software
        map.insert("MeshSoftware",QString::number(ui->Cmb_MeshGen->currentIndex()));
        // Write only the first mesh file
        QFile f(meshfilenames[0]);
        QFileInfo fileInfo(f.fileName());
        QString filename(fileInfo.fileName());
        map.insert("MeshFile",filename);
    }
    else if(index == 2) // Get the mesh dict
    {
        // Do nothing
        // We find if the file exists. If not then error is produced
    }


    // Change hasData to be true
    hasData = true;

    // Return the bool
    return hasData;
}

//*********************************************************************************
// Select mesh files
//*********************************************************************************
void meshing::on_Btn_UploadMesh_clicked()
{
    // Open a dialog window to select the files
    // Here one can select multiple files
    // The selected files are stored in the String list intefilenames (declared in mainwindow.h)
    QFileDialog selectfilesdialog(this);
    selectfilesdialog.setFileMode(QFileDialog::ExistingFiles);
    selectfilesdialog.setNameFilter(tr("All files (*.*)"));
    if(selectfilesdialog.exec()) meshfilenames = selectfilesdialog.selectedFiles();
}

//*********************************************************************************
// Add refinement regions
//*********************************************************************************
void meshing::on_Btn_AddRegion_clicked()
{
    ui->Tbl_Regions->insertRow(ui->Tbl_Regions->rowCount());
}

//*********************************************************************************
// Remove refinement regions
//*********************************************************************************
void meshing::on_Btn_RemRegion_clicked()
{
    ui->Tbl_Regions->removeRow(ui->Tbl_Regions->currentRow());
}

//*********************************************************************************
// Copyfiles
//*********************************************************************************
bool meshing::copyFiles(QString dirName,int type)
{
    // Initialize if has data
    bool hasdata = false;

    // Get type of meshing
    int index = ui->Cmb_MeshType->currentIndex();

    // Depending on the index - copy relevant files
    if(index == 0) // Own meshing
    {
        // Nothing to upload
    }
    else if(index == 1) // Upload mesh files
    {
        if(meshfilenames.size() == 0)
        {
            error.criterrormessage("No mesh files provided!");
        }
        else
        {
            QFile fileToCopy(meshfilenames[0]);
            QFileInfo fileInfo(meshfilenames[0]);
            QString theFile = fileInfo.fileName();
            fileToCopy.copy(dirName + QDir::separator() + theFile);

            // Change data to true
            hasdata = true;
        }
    }
    else if(index == 2) // Upload mesh dictionaries
    {
        if(meshfilenames.size() == 0)
        {
            error.criterrormessage("No mesh dictionaries provided!");
        }
        else
        {
            for (int ii=0; ii<meshfilenames.size(); ++ii)
            {
                QFile fileToCopy(meshfilenames[ii]);
                QFileInfo fileInfo(meshfilenames[ii]);
                QString theFile = fileInfo.fileName();
                fileToCopy.copy(dirName + QDir::separator() + theFile);
            }
            // Change data to true
            hasdata = true;
        }

    }

    // Return if data exists
    return hasdata;
}


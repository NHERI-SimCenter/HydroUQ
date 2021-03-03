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
    // Hide / Unhide elements based on mesh options
    if(index == 0) // In-built mesher
    {
        ui->Btn_UploadMesh->hide();
        ui->Lbl_MeshGen->hide();
        ui->Cmb_MeshGen->hide();
        //ui->cBoxblockMesh->hide();
        //ui->cBoxsnappyHex->hide();
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
        //ui->cBoxblockMesh->hide();
        //ui->cBoxsnappyHex->hide();
        ui->Lbl_FineH2->hide();
        ui->HSl_MeshSize->hide();
        ui->Lbl_CoarseMesh->hide();
        ui->Lbl_FineMesh->hide();
        ui->Lbl_H2Regions->hide();
        ui->Tbl_Regions->hide();
        ui->Btn_AddRegion->hide();
        ui->Btn_RemRegion->hide();
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
        //ui->cBoxblockMesh->show();
        //ui->cBoxsnappyHex->show();
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
        if(ui->Tbl_Regions->rowCount() > 0)
        {
            for(int ii=0;ii<ui->Tbl_Regions->rowCount(); ++ii)
            {
                QString regdata = ui->Tbl_Regions->item(ii,0)->text() +
                        "," + ui->Tbl_Regions->item(ii,1)->text() +
                        "," + ui->Tbl_Regions->item(ii,1)->text();
                map.insert("Region"+QString::number(ii),regdata);
            }
        }
    }
    else if(index == 1) // Mesh from other software
    {
        //Mesh generating software
        map.insert("MeshSoftware",QString::number(ui->Cmb_MeshGen->currentIndex()));
        // Write only the first mesh file
        map.insert("MeshFile",meshfilenames[0]);
        // Number of mesh files
        //map.insert("NumMeshfiles",QString::number(meshfilenames.size()));
        // Write the mesh file names
        //for (int ii=0; ii<meshfilenames.size(); ++ii)
        //{
        //    map.insert("Meshfiles"+QString::number(ii),meshfilenames[ii]);
        //}
    }
    else if(index == 2) // Get the mesh dict
    {
//        // Number of mesh files
//        map.insert("NumMeshDicts",QString::number(meshfilenames.size()));
//        // Write the mesh dictionaries
//        for (int ii=0; ii<meshfilenames.size(); ++ii)
//        {
//            map.insert("MeshDict"+QString::number(ii),meshfilenames[ii]);
//        }
//        //Mesh generating software
//        //map.insert("Solver",QString::number(ui->Cmb_MeshDict->currentIndex()));
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

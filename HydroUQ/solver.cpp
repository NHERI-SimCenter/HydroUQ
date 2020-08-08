#include "solver.h"
#include "ui_solver.h"

//*********************************************************************************
// Solver settings
//*********************************************************************************
solver::solver(int type, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::solver)
{
    ui->setupUi(this);

    // Initialize to show / hide elements
    hideshowelems(type);
}

//*********************************************************************************
// Delete solver settings
//*********************************************************************************
solver::~solver()
{
    delete ui;
}

//*********************************************************************************
// Refresh data
//*********************************************************************************
void solver::refreshData(int type)
{
    // Initialize to show / hide elements
    hideshowelems(type);
}

//*********************************************************************************
// Show - hide elements
//*********************************************************************************
void solver::hideshowelems(int type)
{
    (void) type;
    if(ui->ChB_Restart->isChecked())
        ui->Btn_UploadFiles->show();
    else
        ui->Btn_UploadFiles->hide();
}

//*********************************************************************************
// Get data from solvers
//*********************************************************************************
bool solver::getData(QMap<QString, QString>& map, int type)
{
    bool hasData=false;
    (void) type;

    // Change hasData to be true
    hasData = true;

    // Get the times
    map.insert("Start time",ui->DSpBx_Start->textFromValue(ui->DSpBx_Start->value()));
    map.insert("End time",ui->DSpBx_End->textFromValue(ui->DSpBx_End->value()));
    map.insert("Time interval",ui->DSpBx_DeltaT->textFromValue(ui->DSpBx_DeltaT->value()));
    map.insert("Write interval",ui->DSpBx_WriteT->textFromValue(ui->DSpBx_WriteT->value()));

    // Restart files
    // Write the mesh file names
    for (int ii=0; ii<restartfilenames.size(); ++ii)
    {
        map.insert("Restart files"+QString::number(ii),restartfilenames[ii]);
    }

    // Decomposition
    QString decomp = QString::number(ui->Cmb_Decomp->currentIndex()) +
            "," + ui->DSpBx_Px->textFromValue(ui->DSpBx_Px->value()) +
            "," + ui->DSpBx_Py->textFromValue(ui->DSpBx_Py->value()) +
            "," + ui->DSpBx_Pz->textFromValue(ui->DSpBx_Pz->value());
    map.insert("Domain decomposition",decomp);

    // Solver type
    map.insert("Solver choice",QString::number(ui->Cmb_Solver->currentIndex()));

    // Change hasData to be true
    hasData = true;

    // Return the bool
    return hasData;
}

//*********************************************************************************
// Show upload button
//*********************************************************************************
void solver::on_ChB_Restart_stateChanged(int arg1)
{
    // Show upload button
    if(arg1 > 0)
        ui->Btn_UploadFiles->show();
    else
        ui->Btn_UploadFiles->hide();
}

//*********************************************************************************
// Select restart files
//*********************************************************************************
void solver::on_Btn_UploadFiles_clicked()
{
    // Open a dialog window to select the files
    // Here one can select multiple files
    // The selected files are stored in the String list intefilenames (declared in mainwindow.h)
    QFileDialog selectfilesdialog(this);
    selectfilesdialog.setFileMode(QFileDialog::ExistingFiles);
    selectfilesdialog.setNameFilter(tr("All files (*.*)"));
    if(selectfilesdialog.exec()) restartfilenames = selectfilesdialog.selectedFiles();
}

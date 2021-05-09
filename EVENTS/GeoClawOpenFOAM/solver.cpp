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
        on_ChB_Restart_stateChanged(2);
    else
        on_ChB_Restart_stateChanged(-2);
}

//*********************************************************************************
// When state of check box is changed
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
// Get data from solvers
//*********************************************************************************
bool solver::getData(QMap<QString, QString>& map, int type)
{
    bool hasData=false;
    (void) type;

    // Get the times
    map.insert("StartTime",ui->DSpBx_Start->textFromValue(ui->DSpBx_Start->value()));
    map.insert("EndTime",ui->DSpBx_End->textFromValue(ui->DSpBx_End->value()));
    map.insert("TimeInterval",ui->DSpBx_DeltaT->textFromValue(ui->DSpBx_DeltaT->value()));
    map.insert("WriteInterval",ui->DSpBx_WriteT->textFromValue(ui->DSpBx_WriteT->value()));

    // Restart files
    // Write the restart file
    if(ui->ChB_Restart->isChecked())
    {
        if(restartfilenames.size() == 0)
        {
            map.insert("Restart","No");
        }
        else
        {
            map.insert("Restart","Yes");
            QFile f(restartfilenames[0]);
            QFileInfo fileInfo(f.fileName());
            QString filename(fileInfo.fileName());
            map.insert("RestartFile",filename);
        }
    }
    else
    {
        // No restart
        map.insert("Restart","No");
    }

    // Decomposition
    QString decomp = ui->DSpBx_Px->textFromValue(ui->DSpBx_Px->value()) +
            "," + ui->DSpBx_Py->textFromValue(ui->DSpBx_Py->value()) +
            "," + ui->DSpBx_Pz->textFromValue(ui->DSpBx_Pz->value());
    map.insert("DomainDecomposition",decomp);
    map.insert("DecompositionMethod",ui->Cmb_Decomp->currentText().toLower());

    // Solver type
    map.insert("SolverChoice",QString::number(ui->Cmb_Solver->currentIndex()));

    // Change hasData to be true
    hasData = true;

    // Return the bool
    return hasData;
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

//*********************************************************************************
// Copyfiles
//*********************************************************************************
bool solver::copyFiles(QString dirName,int type)
{
    (void) type;

    // Initialize if has data
    bool hasdata = false;

    // If restart is enabled
    if(ui->ChB_Restart->isChecked())
    {
        if(restartfilenames.size() == 0)
        {
            error.warnerrormessage("Restart files not provided. Restart disabled!");
        }
        else
        {
            QFile fileToCopy(restartfilenames[0]);
            QFileInfo fileInfo(restartfilenames[0]);
            QString theFile = fileInfo.fileName();
            fileToCopy.copy(dirName + QDir::separator() + theFile);
        }
        // Change data to true
        hasdata = true;
    }

    // Return if data exists
    return hasdata;
}

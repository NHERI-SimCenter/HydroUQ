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
    // Hiding elements
    ui->DSpBx_Py->hide();
    ui->DSpBx_Pz->hide();

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
    {
        ui->Btn_UploadFiles->show();
        ui->Led_Path->show();
    }
    else
    {
        ui->Btn_UploadFiles->hide();
        ui->Led_Path->hide();
    }
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
        if(restartfilenames.size() > 0)
        {
            map.insert("Restart","Yes");
            QFile f(restartfilenames[0]);
            QFileInfo fileInfo(f.fileName());
            QString filename(fileInfo.fileName());
            map.insert("RestartFile",filename);
        }
        else
        {
            map.insert("Restart","No");
        }
    }
    else
    {
        // No restart
        map.insert("Restart","No");
    }

    // Decomposition
    QString decomp = ui->DSpBx_Px->textFromValue(ui->DSpBx_Px->value());
//            +
//            "," + ui->DSpBx_Py->textFromValue(ui->DSpBx_Py->value()) +
//            "," + ui->DSpBx_Pz->textFromValue(ui->DSpBx_Pz->value());
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
// Put data into solvers from the JSON file
//*********************************************************************************
bool solver::putData(QJsonObject &jsonObject,int stype, QString workpath)
{
    // Suppress warnings
    (void) stype;

    // Get the time properties
    if(jsonObject.contains("StartTime"))
        ui->DSpBx_Start->setValue(jsonObject["StartTime"].toString().toDouble());
    if(jsonObject.contains("EndTime"))
        ui->DSpBx_End->setValue(jsonObject["EndTime"].toString().toDouble());
    if(jsonObject.contains("TimeInterval"))
        ui->DSpBx_DeltaT->setValue(jsonObject["TimeInterval"].toString().toDouble());
    if(jsonObject.contains("WriteInterval"))
        ui->DSpBx_WriteT->setValue(jsonObject["WriteInterval"].toString().toDouble());

    // Get the domain decomposition method
    if(jsonObject.contains("DecompositionMethod"))
    {
        QString decompmeth = jsonObject["DecompositionMethod"].toString();
//        if(QString::compare(decompmeth, "Simple", Qt::CaseInsensitive) == 0)
//            ui->Cmb_Decomp->setCurrentIndex(0);
        if(QString::compare(decompmeth, "Scotch", Qt::CaseInsensitive) == 0)
            ui->Cmb_Decomp->setCurrentIndex(0);
    }

    // Set the domain decomposition for subdomains
    if(jsonObject.contains("DomainDecomposition"))
    {
        ui->DSpBx_Px->setValue(jsonObject["DomainDecomposition"].toString().toInt());
//        QString totalproc = jsonObject["DomainDecomposition"].toString();
//        QStringList procs = totalproc.split(',');
//        if(procs.size() == 3)
//        {
//            ui->DSpBx_Px->setValue(procs[0].toInt());
//            ui->DSpBx_Py->setValue(procs[1].toInt());
//            ui->DSpBx_Pz->setValue(procs[2].toInt());
//        }

    }

    // Get the solver
    if(jsonObject.contains("SolverChoice"))
        ui->Cmb_Solver->setCurrentIndex(jsonObject["SolverChoice"].toString().toInt());

    // Set the restart file
    if(jsonObject.contains("Restart"))
    {
        QString restart = jsonObject["Restart"].toString();
        if(QString::compare(restart, "No", Qt::CaseInsensitive) == 0)
        {
            // Set the checked state to unchecked
            ui->ChB_Restart->setChecked(false);
        }
        else
        {
            // Set the checked state to checked
            ui->ChB_Restart->setChecked(true);

            // Get the restart file
            if(!workpath.isEmpty())
            {
                if(jsonObject.contains("RestartFile"))
                {
                    // Set the STL file if exists
                    QString filename = jsonObject["RestartFile"].toString();
                    QFileInfo fi(QDir(workpath),filename);
                    restartfilenames.append(fi.canonicalFilePath());
                    ui->Led_Path->setText(restartfilenames.join(";\n\n"));
                }
            }
        }
    }

    // return true
    return true;
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
    selectfilesdialog.setNameFilter(tr("All files (*.zip)"));
    if(selectfilesdialog.exec()) restartfilenames = selectfilesdialog.selectedFiles();
    if(restartfilenames.size() > 0)
    {
        ui->Led_Path->setText(restartfilenames[0]);
    }
    else
    {
        error.warnerrormessage("No files selected!");
    }
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
        if(restartfilenames.size() > 0)
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

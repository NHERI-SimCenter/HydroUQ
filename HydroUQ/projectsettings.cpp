#include "projectsettings.h"
#include "ui_projectsettings.h"

//*********************************************************************************
// Project settings
//*********************************************************************************
projectsettings::projectsettings(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::projectsettings)
{
    ui->setupUi(this);
}

//*********************************************************************************
// Delete project settings
//*********************************************************************************
projectsettings::~projectsettings()
{
    delete ui;
}

//*********************************************************************************
// Get data from project settings
//*********************************************************************************
bool projectsettings::getData(QMap<QString, QString> & map)
{
    bool hasData=false;

    map.insert("Work directory",ui->Lbl_WorkDir->text());
    map.insert("Project name",ui->Led_PName->text());
    map.insert("Project description",ui->Ted_PDesc->toPlainText());
    map.insert("Simulation type",QString::number(ui->CmB_SimType->currentIndex()));
    map.insert("Turbulence model",QString::number(ui->CmB_TurbModel->currentIndex()));

    //map.insert("QString",ui->lineEdit->text());
    //map.insert("double", ui->doubleSpinBox->textFromValue(ui->doubleSpinBox->value()));
    hasData = true;

    return hasData;
}

//*********************************************************************************
// Setting project directory
//*********************************************************************************
void projectsettings::on_Btn_WDir_clicked()
{
    workdirUrl = QFileDialog::getExistingDirectoryUrl(this, tr("Open Directory"), QUrl("/home/Users"),QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    QString workdir = workdirUrl.toString();

    // If the workdir is not empty or not, set the text accordingly
    if(workdir.isEmpty())
    {
        ui->Lbl_WorkDir->setText("\nSet working directory\n");
    }
    else
    {
        ui->Lbl_WorkDir->setText("\n"+workdirUrl.toString()+"\n");
    }
}

//*********************************************************************************
// When index of simulation type changes
//*********************************************************************************
void projectsettings::on_CmB_SimType_currentIndexChanged(int index)
{

    std::ofstream myfile;
    myfile.open ("/Users/ajaybh/simtype.txt");
    myfile << index;
    myfile.close();

    //MainWindow::simtype = index;

    //simtype = index;
    //simtype = index;
}

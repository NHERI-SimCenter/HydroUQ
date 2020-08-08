#include "mainwindow.h"
#include "ui_mainwindow.h"

//*********************************************************************************
// Main window
//*********************************************************************************
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Start the UI
    ui->setupUi(this);

    // Initialize the UI
    initialize();
}

//*********************************************************************************
// Delete main window
//*********************************************************************************
MainWindow::~MainWindow()
{
    delete ui;
}

//*********************************************************************************
// Initialize the UI
//*********************************************************************************
void MainWindow::initialize()
{
    // Add project page
    ui->stackedWidget->addWidget(new projectsettings(0)); // Project settings
    ui->stackedWidget->addWidget(new bathymetry(0)); // Bathymetry
    ui->stackedWidget->addWidget(new swcfdint(0)); // SW-CFD interface: Check this if working
    ui->stackedWidget->addWidget(new buildings(0)); // Buildings
    ui->stackedWidget->addWidget(new floatingbds(0)); // Floating bodies
    ui->stackedWidget->addWidget(new meshing(0)); // Meshing
    ui->stackedWidget->addWidget(new materials(0)); // Materials
    ui->stackedWidget->addWidget(new initialconVel(0)); // Initial velocity
    ui->stackedWidget->addWidget(new initialconPres(0)); // Initial pressure
    ui->stackedWidget->addWidget(new initialconAlpha(0)); // Initial alpha
    ui->stackedWidget->addWidget(new initialconVel(0)); // Boundary (Velocity)
    ui->stackedWidget->addWidget(new initialconPres(0)); // Boundary (Pressure)
    ui->stackedWidget->addWidget(new initialconAlpha(0)); // Boundary (Alpha)
    ui->stackedWidget->addWidget(new solver(0)); // Solver settings

    // Set index to zero & simtype to zero
    ui->stackedWidget->setCurrentIndex(0);
    simtype = 0;
}

//*********************************************************************************
// Clear all data
//*********************************************************************************
void MainWindow::clearAllData(void)
{
    foreach (int key, allData.keys()) { delete allData.value(key); }
    allData.clear();
}

//*********************************************************************************
// Refresh project map and get latest simulation type
//*********************************************************************************
void MainWindow::refresh_projsettings()
{
    // Refresh the map to get the project data
    QMap<QString, QString> *singleData;
    this->clearAllData();
    singleData = new QMap<QString,QString>;
    int numberOfPanes = 1;
    for (int i=0;i<numberOfPanes;i++) {
        singleData = new QMap<QString,QString>;
        if (dynamic_cast<projectsettings *>(ui->stackedWidget->widget(i))->getData(*singleData,simtype))
        {
            allData.insert(i, singleData);
        }
    }

    // Search for simulation type
    QMap<QString, QString> *singleDataSet = allData.value(0);
    QString simty = singleDataSet->value("Simulation type");
    //wdir = singleDataSet->value("Work directory");

    // Get new simulation type, if user has changed it intermediately
    // This can also be same as old simulation type
    simtype = simty.split(" ")[0].toInt();
}

//*********************************************************************************
// Read all the pages for data and get data
// Temporarily writing to a text window - to be replaced by write to JSON
//*********************************************************************************
void MainWindow::on_Btn_Generate_Files_clicked()
{

    // Get the simulation type
    refresh_projsettings();

    // Get data from project settings - index 0
    QMap<QString, QString> *singleData;
    this->clearAllData();
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<projectsettings *>(ui->stackedWidget->widget(0))->getData(*singleData,simtype))
    {
        allData.insert(0, singleData);
    }

    // Get data from Bathymetry - index 1
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<bathymetry *>(ui->stackedWidget->widget(1))->getData(*singleData,simtype))
    {
        allData.insert(1, singleData);
    }

    // Add SW-CFD Interface - Index 2
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<swcfdint *>(ui->stackedWidget->widget(2))->getData(*singleData,simtype))
    {
        allData.insert(2, singleData);
    }

    // Get data from buildings - index 3
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<buildings *>(ui->stackedWidget->widget(3))->getData(*singleData,simtype))
    {
        allData.insert(3, singleData);
    }

    // Get data from floating bodies - Index 4
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<floatingbds *>(ui->stackedWidget->widget(4))->getData(*singleData,simtype))
    {
        allData.insert(4, singleData);
    }

    // Get data from mesh - index 5
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<meshing *>(ui->stackedWidget->widget(5))->getData(*singleData,simtype))
    {
        allData.insert(5, singleData);
    }

    // Get data from materials - index 6
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<materials *>(ui->stackedWidget->widget(6))->getData(*singleData,simtype))
    {
        allData.insert(6, singleData);
    }

    // Initial conditions: velocity - index 7
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<initialconVel *>(ui->stackedWidget->widget(7))->getData(*singleData,simtype))
    {
        allData.insert(7, singleData);
    }

    // Initial conditions: pressure - index 8
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<initialconPres *>(ui->stackedWidget->widget(8))->getData(*singleData,simtype))
    {
        allData.insert(8, singleData);
    }

    // Initial conditions: alpha - index 9
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<initialconAlpha *>(ui->stackedWidget->widget(9))->getData(*singleData,simtype))
    {
        allData.insert(9, singleData);
    }

    // Boundary conditions - index 10 / 11 / 12

    // Solver settings - index 13
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<solver *>(ui->stackedWidget->widget(13))->getData(*singleData,simtype))
    {
        allData.insert(13, singleData);
    }

    // Show in text window (Just to print out the map)
    // This will later be replaced by writing to JSON
    QString text;
    foreach (int key, allData.keys())
    {
        QMap<QString, QString> *singleDataSet = allData.value(key);
        foreach (QString varname, singleDataSet->keys())
        {
            QString oneEntry = QString("%1: %2 = %3\n").arg(key+1).arg(varname).arg(singleDataSet->value(varname));
            text.append(oneEntry);
        }
    }
    ui->textEdit->setPlainText(text);
    ui->textEdit->repaint();

    // Write map to JSON file

    // Call the OpenFOAM method to read the JSON file
    // Write the OpenFOAM files & folders

}

//*********************************************************************************
// Tree item double clicked
//*********************************************************************************
void MainWindow::on_SimOptions_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    // Get the item double clicked on
    QString sel = item->text(column);

    // Get the simulation type
    refresh_projsettings();

    // Bathymetry
    if(simtype == 0)
    {
        ui->stackedWidget->setCurrentIndex(0);
    }
    else
    {
        // Move to project settings page
        if(sel == "Project settings")
        {
            ui->stackedWidget->setCurrentIndex(0);
        }

        // Update bathymetry
        else if(sel == "Bathymetry")
        {
            dynamic_cast<bathymetry *>(ui->stackedWidget->widget(1))->refreshData(simtype);
            ui->stackedWidget->setCurrentIndex(1);
        }

        // Update sw-cfd interface
        else if(sel == "SW-CFD interface")
        {
            dynamic_cast<swcfdint *>(ui->stackedWidget->widget(2))->refreshData(simtype);
            ui->stackedWidget->setCurrentIndex(2);
        }

        // Update buildings
        else if(sel == "Buildings")
        {
            dynamic_cast<buildings *>(ui->stackedWidget->widget(3))->refreshData(simtype);
            ui->stackedWidget->setCurrentIndex(3);
        }

        // Update floating bodies
        else if(sel == "Floating bodies")
        {
            dynamic_cast<floatingbds *>(ui->stackedWidget->widget(4))->refreshData(simtype);
            ui->stackedWidget->setCurrentIndex(4);
        }

        // Update Meshing
        else if(sel == "Meshing")
        {
            dynamic_cast<meshing *>(ui->stackedWidget->widget(5))->refreshData(simtype);
            ui->stackedWidget->setCurrentIndex(5);
        }

        // Update Materials
        else if(sel == "Materials")
        {
            dynamic_cast<materials *>(ui->stackedWidget->widget(6))->refreshData(simtype);
            ui->stackedWidget->setCurrentIndex(6);
        }

        // Update Initial conditions - velocity
        else if(sel == "Initial velocity")
        {
            dynamic_cast<initialconVel *>(ui->stackedWidget->widget(7))->refreshData(simtype);
            ui->stackedWidget->setCurrentIndex(7);
        }

        // Update Initial conditions - Pressure
        else if(sel == "Initial pressure")
        {
            dynamic_cast<initialconPres *>(ui->stackedWidget->widget(8))->refreshData(simtype);
            ui->stackedWidget->setCurrentIndex(8);
        }

        // Update Initial conditions - Alpha
        else if(sel == "Initial phase")
        {
            dynamic_cast<initialconAlpha *>(ui->stackedWidget->widget(9))->refreshData(simtype);
            ui->stackedWidget->setCurrentIndex(9);
        }

        // Update solvers
        else if(sel == "Solver")
        {
            dynamic_cast<solver *>(ui->stackedWidget->widget(13))->refreshData(simtype);
            ui->stackedWidget->setCurrentIndex(13);
        }
    }
}

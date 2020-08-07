#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "projectsettings.h"
#include "bathymetry.h"
#include "buildings.h"
#include "floatingbds.h"
#include "meshing.h"
#include "materials.h"
#include "initialconvel.h"
#include "initialconpres.h"
#include "initialconalpha.h"
#include "solver.h"

#include <QString>
#include <QMap>
#include <QDebug>
#include <QTreeWidget>

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
    ui->stackedWidget->addWidget(new projectsettings);
    ui->stackedWidget->addWidget(new bathymetry(0));
    ui->stackedWidget->addWidget(new projectsettings); // Later change to SW-CFD Interface
    ui->stackedWidget->addWidget(new buildings(0));
    ui->stackedWidget->addWidget(new floatingbds);
    ui->stackedWidget->addWidget(new meshing(0));
    ui->stackedWidget->addWidget(new materials);
    ui->stackedWidget->addWidget(new initialconAlpha(0)); // Initial velocity (CHange)
    ui->stackedWidget->addWidget(new initialconAlpha(0)); // Initial pressure (CHange)
    ui->stackedWidget->addWidget(new initialconAlpha(0));
    ui->stackedWidget->addWidget(new initialconAlpha(0)); // Boundary (Velocity)
    ui->stackedWidget->addWidget(new initialconAlpha(0)); // Boundary (Pressure)
    ui->stackedWidget->addWidget(new initialconAlpha(0)); // Boundary (Alpha)
    ui->stackedWidget->addWidget(new solver);


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

    // Save simtype into oldsimtype
    oldsimtype = simtype;

    // Refresh the map to get the project data
    QMap<QString, QString> *singleData;
    this->clearAllData();
    singleData = new QMap<QString,QString>;
    int numberOfPanes = 1;
    for (int i=0;i<numberOfPanes;i++) {
        singleData = new QMap<QString,QString>;
        if (dynamic_cast<projectsettings *>(ui->stackedWidget->widget(i))->getData(*singleData))
        {
            allData.insert(i, singleData);
        }
    }

    // Search
    QMap<QString, QString> *singleDataSet = allData.value(0);
    QString temp = "Simulation type";
    QString simty = singleDataSet->value(temp);
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
    if (dynamic_cast<projectsettings *>(ui->stackedWidget->widget(0))->getData(*singleData))
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

    // Get data from buildings - index 3
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<buildings *>(ui->stackedWidget->widget(3))->getData(*singleData,simtype))
    {
        allData.insert(3, singleData);
    }

    // Get data from floating bodies - Index 4
    // At the moment, there is no data and not necessary to use this

    // Get data from mesh - index 5
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<meshing *>(ui->stackedWidget->widget(5))->getData(*singleData,simtype))
    {
        allData.insert(5, singleData);
    }

    // Get data from materials - index 6
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<materials *>(ui->stackedWidget->widget(6))->getData(*singleData))
    {
        allData.insert(6, singleData);
    }

    // Initial conditions - index 7 / 8 / 9

    // Initial conditions: alpha - index 9
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<initialconAlpha *>(ui->stackedWidget->widget(9))->getData(*singleData,simtype))
    {
        allData.insert(9, singleData);
    }

    // Boundary conditions - index 10 / 11 / 12

    // Solver settings - index 13
    singleData = new QMap<QString,QString>;
    if (dynamic_cast<solver *>(ui->stackedWidget->widget(13))->getData(*singleData))
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

    // Write to JSON file

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
            // Check if simulation type is not same as earlier
            // Then delete and create a new widget
            if(oldsimtype != simtype)
            {
                ui->stackedWidget->removeWidget(ui->stackedWidget->widget(1));
                ui->stackedWidget->insertWidget(1, new bathymetry(simtype));
                ui->stackedWidget->setCurrentIndex(1);
            }
            // else just set the index to one
            else
            {
                ui->stackedWidget->setCurrentIndex(1);
            }
        }

        // Update buildings
        else if(sel == "Buildings")
        {
            // Check if simulation type is not same as earlier
            // Then delete and create a new widget
            if(oldsimtype != simtype)
            {
                ui->stackedWidget->removeWidget(ui->stackedWidget->widget(3));
                ui->stackedWidget->insertWidget(3, new buildings(simtype));
                ui->stackedWidget->setCurrentIndex(3);
            }
            // else just set the index to one
            else
            {
                ui->stackedWidget->setCurrentIndex(3);
            }
        }

        // Update floating bodies
        else if(sel == "Floating bodies")
        {
            // Check if simulation type is not same as earlier
            // Then delete and create a new widget
            if(oldsimtype != simtype)
            {
                ui->stackedWidget->removeWidget(ui->stackedWidget->widget(4));
                ui->stackedWidget->insertWidget(4, new floatingbds);
                ui->stackedWidget->setCurrentIndex(4);
            }
            // else just set the index to one
            else
            {
                ui->stackedWidget->setCurrentIndex(4);
            }
        }

        // Update Meshing
        else if(sel == "Meshing")
        {
            // Check if simulation type is not same as earlier
            // Then delete and create a new widget
            if(oldsimtype != simtype)
            {
                ui->stackedWidget->removeWidget(ui->stackedWidget->widget(5));
                ui->stackedWidget->insertWidget(5, new meshing(simtype));
                ui->stackedWidget->setCurrentIndex(5);
            }
            // else just set the index to one
            else
            {
                ui->stackedWidget->setCurrentIndex(5);
            }
        }

        // Update Materials
        else if(sel == "Materials")
        {
            // Check if simulation type is not same as earlier
            // Then delete and create a new widget
            if(oldsimtype != simtype)
            {
                ui->stackedWidget->removeWidget(ui->stackedWidget->widget(6));
                ui->stackedWidget->insertWidget(6, new materials);
                ui->stackedWidget->setCurrentIndex(6);
            }
            // else just set the index to one
            else
            {
                ui->stackedWidget->setCurrentIndex(6);
            }
        }

        // Update Initial conditions - velocity
        else if(sel == "Initial velocity")
        {
            // Check if simulation type is not same as earlier
            // Then delete and create a new widget
            if(oldsimtype != simtype)
            {
                ui->stackedWidget->removeWidget(ui->stackedWidget->widget(7));
                ui->stackedWidget->insertWidget(7, new initialconVel(simtype));
                ui->stackedWidget->setCurrentIndex(7);
            }
            // else just set the index to one
            else
            {
                ui->stackedWidget->setCurrentIndex(7);
            }
        }

        // Update Initial conditions - Pressure
        else if(sel == "Initial pressure")
        {
            // Check if simulation type is not same as earlier
            // Then delete and create a new widget
            if(oldsimtype != simtype)
            {
                ui->stackedWidget->removeWidget(ui->stackedWidget->widget(8));
                ui->stackedWidget->insertWidget(8, new initialconPres(simtype));
                ui->stackedWidget->setCurrentIndex(8);
            }
            // else just set the index to one
            else
            {
                ui->stackedWidget->setCurrentIndex(8);
            }
        }

        // Update Initial conditions - Alpha
        else if(sel == "Initial phase")
        {
            // Check if simulation type is not same as earlier
            // Then delete and create a new widget
            if(oldsimtype != simtype)
            {
                ui->stackedWidget->removeWidget(ui->stackedWidget->widget(9));
                ui->stackedWidget->insertWidget(9, new initialconAlpha(simtype));
                ui->stackedWidget->setCurrentIndex(9);
            }
            // else just set the index to one
            else
            {
                ui->stackedWidget->setCurrentIndex(9);
            }
        }

        // Update solvers
        else if(sel == "Solver")
        {
            // Check if simulation type is not same as earlier
            // Then delete and create a new widget
            if(oldsimtype != simtype)
            {
                ui->stackedWidget->removeWidget(ui->stackedWidget->widget(13));
                ui->stackedWidget->insertWidget(13, new solver);
                ui->stackedWidget->setCurrentIndex(13);
            }
            // else just set the index to one
            else
            {
                ui->stackedWidget->setCurrentIndex(13);
            }
        }
    }
}

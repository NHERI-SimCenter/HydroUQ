#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mymainframe.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // set central widget
    this->setCentralWidget(new MyMainFrame(this));

    // define menues

    // define actions

    // ....


}

MainWindow::~MainWindow()
{
    delete ui;
}


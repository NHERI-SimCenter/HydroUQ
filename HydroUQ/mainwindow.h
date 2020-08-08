#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "projectsettings.h"
#include "swcfdint.h"
#include "bathymetry.h"
#include "buildings.h"
#include "floatingbds.h"
#include "meshing.h"
#include "materials.h"
#include "initialconvel.h"
#include "initialconpres.h"
#include "initialconalpha.h"
#include "solver.h"

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QInputDialog>
#include <QMap>
#include <QString>
#include <QTreeWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //QString getprojdetails();

private slots:
    void on_Btn_Generate_Files_clicked();
    void on_SimOptions_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    void clearAllData(void);
    void initialize();
    void refresh_projsettings();

    Ui::MainWindow *ui;
    QMap<int, QMap<QString, QString>*> allData;
    QMap<QString, QString> allData2;

    int simtype; // Simulation type
    QStringList optiontree; // Tree widget names
    QString wdir;
};
#endif // MAINWINDOW_H

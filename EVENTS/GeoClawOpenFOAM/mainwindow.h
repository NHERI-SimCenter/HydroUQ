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
#include "boundary.h"
#include "solver.h"
#include "cfdsolvers/openfoam/openfoam.h"

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QInputDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>
#include <QString>
#include <QTreeWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class AgaveCurl;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(AgaveCurl *, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Btn_Generate_Files_clicked();
    void on_SimOptions_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_Btn_SubTACC_clicked();

private:
    void clearAllData(void);
    void initialize();
    void refresh_projsettings();
  
    void saveJson(QString wdir, QString pname, QJsonDocument jsondoc);
 
    Ui::MainWindow *ui;
    QMap<int, QMap<QString, QString>*> allData;

    int simtype; // Simulation type
    QStringList optiontree; // Tree widget names
    QString applicationname = "Hydro-UQ";
    QString applicationversion = "0.9.0 (Alpha)";
    AgaveCurl *theRemoteService;
};
#endif // MAINWINDOW_H

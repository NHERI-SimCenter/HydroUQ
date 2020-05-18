#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUrl>
#include "../Eigen/Dense"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    //Tab 01: Bathymetry data
    //Button
    void on_SetWorkDirBut_clicked();
    void on_SelectBathFileBut_clicked();
    void on_AcceptBathDataBut_clicked();
    void on_InterfaceConfBut_clicked();
    void on_Tab1Accept_clicked();
    void on_Tab1Reset_clicked();
    //Comboboxes
    void on_BathType_currentIndexChanged(int index);

    // Tab 02: Generate bathymetry
    void on_NumBuildingsBut_clicked();
    void on_AddBuilding_clicked();
    void on_RemoveBuilding_clicked();
    void on_SegmentsConf_But_clicked();
    void on_GenGeomConf_But_clicked();
    void on_AddSegment_clicked();
    void on_RemoveSegment_clicked();
    void on_GenGeomReset_But_clicked();
    void on_BuildDataAcceptBut_clicked();
    void on_BuildDataResetBut_clicked();

    // Tab 03: Boundary conditions
    void on_BCAccept_But_clicked();
    void on_SolutionFiles_But_clicked();

    // Tab 04: CFD solver properties
    void on_ConfTurb_but_clicked();
    void on_ResetTurb_but_clicked();
    void on_ParallelConf_But_clicked();
    void on_ResetParall_But_clicked();
    void on_ConfMeshing_But_clicked();
    void on_ResetMeshing_But_clicked();
    void on_TimeSetConf_But_clicked();
    void on_ResetTimeBut_clicked();
    void on_Transport_ConfirmBut_clicked();
    void on_ResetTransport_But_clicked();
    void on_ClusterConf_But_clicked();
    void on_ResetClusterl_But_clicked();
    void on_AcceptCFDSolver_But_clicked();
    void on_ResetSolver_But_clicked();
    void on_GenSolverFiles_clicked();

    // Plotting
    void plotbathy();

    // Writers
    //void OFheaderWrite(QString path);
    void HydroHeader();
    int HydroBCSW2CFD(int flag);

    // Readers
    int SCBathFileReader(QString filename);

    // Process
    void processfail();


private:
    Ui::MainWindow *ui;

    QUrl defaultdir;
    QString bathfilename,projname;
    QStringList bathfilenames,bathfilenamesSC;
    QStringList SWsolutionfilenames,SWsolutionfilenamesSC;

    int errorcode = 0;
    int nx,ny;
    double dx,dy,xlower,ylower,nodatavalue;
    double xmin,xmax,ymin,ymax;
    double slopeval, interceptval;
    Eigen::MatrixXd Zdata;
    Eigen::VectorXd Xdata,Ydata;
    std::string defdir,opfilename,cfdsolver;
};
#endif // MAINWINDOW_H

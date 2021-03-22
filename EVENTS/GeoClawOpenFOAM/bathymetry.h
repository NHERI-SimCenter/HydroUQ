#ifndef BATHYMETRY_H
#define BATHYMETRY_H

//#include "mainwindow.h"

#include <QFrame>
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QFileInfo>
#include "hydroerror.h"

namespace Ui {
class bathymetry;
}

class bathymetry : public QFrame
{
    Q_OBJECT

public:
    explicit bathymetry(int, QWidget *parent = nullptr);
    ~bathymetry();
    bool getData(QMap<QString, QString>&, int);
    void refreshData(int);
    bool copyFiles(QString dirName, int);

private slots:
    void on_Btn_UploadFiles_clicked();
    void on_Btn_UploadSolution_clicked();
    void on_Btn_AddSeg_clicked();
    void on_Btn_RemSeg_clicked();
    void on_CmB_FlumeGeoType_currentIndexChanged(int index);

private:
    void hideshowelems(int);
    Ui::bathymetry *ui;
    QStringList bathfilenames,solfilenames;
    Hydroerror error;
};

#endif // BATHYMETRY_H

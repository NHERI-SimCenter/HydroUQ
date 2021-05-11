#ifndef SWCFDINT_H
#define SWCFDINT_H

#include <QFrame>
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <QJsonObject>
#include "hydroerror.h"
#include "GeoClawOpenFOAM.h"

namespace Ui {
class swcfdint;
}

class swcfdint : public QFrame
{
    Q_OBJECT

public:
    explicit swcfdint(int,QWidget *parent = nullptr);
    ~swcfdint();
    bool getData(QMap<QString, QString>&,int);
    bool putData(QJsonObject &,int,QString);
    void refreshData(int);
    bool copyFiles(QString dirName, int);

private slots:
    void on_Btn_UploadFile_clicked();

private:
    void hideshowelems(int);
    Ui::swcfdint *ui;
    QStringList interffilenames;
    Hydroerror error;
};

#endif // SWCFDINT_H

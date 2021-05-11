#ifndef BOUNDARYDATA_H
#define BOUNDARYDATA_H

#include <QFrame>
#include <QFileDialog>
#include <QDir>
#include <QJsonObject>
#include "hydroerror.h"

namespace Ui {
class boundaryData;
}

class boundaryData : public QFrame
{
    Q_OBJECT

public:
    explicit boundaryData(const QString, QWidget *parent = nullptr);
    ~boundaryData();
    bool getData(QMap<QString, QString>&,int,int);
    bool putData(QJsonObject &,int,QString,QString);
    bool copyFiles(QString dirName, int);

private slots:
    void on_Cmb_UBC_currentIndexChanged(int index);
    void on_Cmb_PresBC_currentIndexChanged(int index);
    void on_Cmb_PatchLoc_currentIndexChanged(int index);
    void on_Btn_UploadFile_clicked();

    void on_Btn_UploadFile_2_clicked();

private:
    void hideshowelems();
    Ui::boundaryData *ui;
    QStringList dispfilenames,heightfilenames;
    Hydroerror error;
};

#endif // BOUNDARYDATA_H

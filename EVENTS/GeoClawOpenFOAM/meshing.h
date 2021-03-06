#ifndef MESHING_H
#define MESHING_H

#include <QFrame>
#include <QFileDialog>
#include <QDir>
#include <QJsonObject>
#include "hydroerror.h"

namespace Ui {
class meshing;
}

class meshing : public QFrame
{
    Q_OBJECT

public:
    explicit meshing(int, QWidget *parent = nullptr);
    ~meshing();
    bool getData(QMap<QString, QString>&,int);
    bool putData(QJsonObject &,int,QString);
    void refreshData(int);
    bool copyFiles(QString dirName, int);

private slots:
    void on_Cmb_MeshType_currentIndexChanged(int index);
    void on_Btn_UploadMesh_clicked();
    void on_Btn_AddRegion_clicked();
    void on_Btn_RemRegion_clicked();

private:
    void hideshowelems(int);
    Ui::meshing *ui;
    QStringList meshfilenames;
    Hydroerror error;
};

#endif // MESHING_H

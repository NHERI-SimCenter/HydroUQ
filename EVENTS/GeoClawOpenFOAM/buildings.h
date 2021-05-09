#ifndef BUILDINGS_H
#define BUILDINGS_H

#include <QFrame>
#include <QFileDialog>
#include "hydroerror.h"

namespace Ui {
class buildings;
}

class buildings : public QFrame
{
    Q_OBJECT

public:
    explicit buildings(int, QWidget *parent = nullptr);
    ~buildings();
    bool getData(QMap<QString, QString>&,int);
    void refreshData(int);
    bool copyFiles(QString dirName, int);

private slots:
    void on_Btn_AddBuild_clicked();
    void on_Btn_RemBuild_clicked();
    void on_CmB_BuildData_currentIndexChanged(int index);
    void on_CmB_BuildShape_currentIndexChanged(int index);
    void on_Btn_CustomBuild_clicked();

private:
    void hideshowelems(int);
    Ui::buildings *ui;
    QStringList STLfilenames;
    int simtype;
    Hydroerror error;
};

#endif // BUILDINGS_H

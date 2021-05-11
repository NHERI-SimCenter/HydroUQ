#ifndef SOLVER_H
#define SOLVER_H

#include <QFrame>
#include <QFileDialog>
#include <QDir>
#include <QJsonObject>
#include "hydroerror.h"

namespace Ui {
class solver;
}

class solver : public QFrame
{
    Q_OBJECT

public:
    explicit solver(int, QWidget *parent = nullptr);
    ~solver();
    bool getData(QMap<QString, QString>&,int);
    bool putData(QJsonObject &,int,QString);
    void refreshData(int);
    bool copyFiles(QString dirName, int);

private slots:
    void on_ChB_Restart_stateChanged(int arg1);
    void on_Btn_UploadFiles_clicked();

private:
    void hideshowelems(int);
    Ui::solver *ui;
    QStringList restartfilenames;
    Hydroerror error;
};

#endif // SOLVER_H

#ifndef SOLVER_H
#define SOLVER_H

#include <QFrame>
#include <QFileDialog>
#include <QDir>

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
    void refreshData(int);

private slots:
    void on_ChB_Restart_stateChanged(int arg1);
    void on_Btn_UploadFiles_clicked();

private:
    void hideshowelems(int);
    Ui::solver *ui;
    QStringList restartfilenames;
};

#endif // SOLVER_H

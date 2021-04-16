#ifndef BOUNDARY_H
#define BOUNDARY_H

#include <QDir>
#include <QDebug>
#include <QFrame>
#include <QInputDialog>
#include <QMessageBox>

namespace Ui {
class boundary;
}

class boundary : public QFrame
{
    Q_OBJECT

public:
    explicit boundary(int, QWidget *parent = nullptr);
    ~boundary();
    bool getData(QMap<QString, QString>&,int);
    void refreshData(int);
    bool copyFiles(QString dirName, int);

private slots:
    void on_Btn_AddBoundary_clicked();
    void on_Btn_Previous_clicked();
    void on_Btn_Next_clicked();
    void on_Btn_RemBoundary_clicked();

private:
    void hideshowelems(int);
    Ui::boundary *ui;
};

#endif // BOUNDARY_H

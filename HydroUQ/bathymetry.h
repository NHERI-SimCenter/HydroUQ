#ifndef BATHYMETRY_H
#define BATHYMETRY_H

#include <QFrame>
#include <QFileDialog>
#include <QDir>

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

private slots:
    void on_Btn_UploadFiles_clicked();
    void on_Btn_UploadSolution_clicked();
    void on_Btn_AddSeg_clicked();
    void on_Btn_RemSeg_clicked();

private:
    void hideshowelems(int);
    Ui::bathymetry *ui;
    QStringList bathfilenames,solfilenames;
};

#endif // BATHYMETRY_H

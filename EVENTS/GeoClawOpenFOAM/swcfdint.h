#ifndef SWCFDINT_H
#define SWCFDINT_H

#include <QFrame>
#include <QFileDialog>
#include <QDir>
#include <QDebug>

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
    void refreshData(int);

private slots:
    void on_Btn_UploadFile_clicked();

private:
    void hideshowelems(int);
    Ui::swcfdint *ui;
    QStringList interffilenames;
};

#endif // SWCFDINT_H

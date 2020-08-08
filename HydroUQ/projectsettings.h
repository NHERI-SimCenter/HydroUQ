#ifndef PROJECTSETTINGS_H
#define PROJECTSETTINGS_H

#include <QFrame>
#include <QFileDialog>
#include <QDir>
#include <iostream>
#include <fstream>

namespace Ui {
class projectsettings;
}

class projectsettings : public QFrame
{
    Q_OBJECT

public:
    explicit projectsettings(int, QWidget *parent = nullptr);
    ~projectsettings();
    bool getData(QMap<QString, QString>&,int);
    void refreshData(int);

private slots:
    void on_Btn_WDir_clicked();
    //void on_CmB_SimType_currentIndexChanged(int index);

private:
    void hideshowelems(int);
    Ui::projectsettings *ui;
    QUrl workdirUrl; // Defaulty workdirectory
};

#endif // PROJECTSETTINGS_H

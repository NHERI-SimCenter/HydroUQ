#ifndef PROJECTSETTINGS_H
#define PROJECTSETTINGS_H

#include <QFrame>
#include <QFileDialog>
#include <QDir>
#include <iostream>
#include <fstream>
#include <QJsonObject>

#include "hydroerror.h"

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
    bool putData(QJsonObject &);
    void refreshData(int);

private slots:

private:
    void hideshowelems(int);
    Ui::projectsettings *ui;
    QUrl workdirUrl; // Defaulty workdirectory
    Hydroerror error;
};

#endif // PROJECTSETTINGS_H

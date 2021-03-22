#ifndef HYDROERROR_H
#define HYDROERROR_H

#include <QFrame>
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QFileInfo>

class Hydroerror
{
public:
    Hydroerror();
    void errormessage(QString csMsg, QString csTitle);
    void criterrormessage(QString csMsg);
    void warnerrormessage(QString csMsg);
};

#endif // HYDROERROR_H

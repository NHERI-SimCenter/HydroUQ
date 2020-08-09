#ifndef OPENFOAM_H
#define OPENFOAM_H

#include <QDebug>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QMap>
#include <QString>
#include <QUrl>

class openfoam
{
public:
    void genopenfoam(QString wdir,QString pname);

private:
    // System directories
    void fvSchemegen(QDir systdirs);

};

#endif // OPENFOAM_H

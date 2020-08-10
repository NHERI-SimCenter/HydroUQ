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
#include <Eigen>

class openfoam
{
public:
    void genopenfoam(QString wdir,QString pname);

private:
    // System directories
    void fvSchemegen(QDir systdirs);
    void fvSolutiongen(QDir fvSolution);
    void controldictgen(QDir controldict, QStringList data);
    void decomposepargen(QDir systdirs,QStringList data);
    void toposetdictgen(QDir systdirs,QStringList data);
    Eigen::MatrixXf getbuilddatasimple(int nx, int ny,
                                 double dx, double dy, double dc,
                                 double Ox, double Oy, double bs);
    void setFieldsDictgen(QDir systdirs,QStringList data);
};

#endif // OPENFOAM_H

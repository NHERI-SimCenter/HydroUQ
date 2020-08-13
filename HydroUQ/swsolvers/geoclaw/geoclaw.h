#ifndef GEOCLAW_H
#define GEOCLAW_H

#include <QString>
#include <QStringList>

class geoclaw
{
public:
    explicit geoclaw(int, QStringList);

private:
    void readtopo();
    int gclawtotaltime(QString);
    QString getfilename(QString,int,int);

};

#endif // GEOCLAW_H

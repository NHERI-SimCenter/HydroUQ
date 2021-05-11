#ifndef POSTPROCESS_H
#define POSTPROCESS_H

#include <QFrame>
#include <QFileDialog>
#include <QDir>
#include <QJsonObject>
#include "hydroerror.h"

namespace Ui {
class postprocess;
}

class postprocess : public QFrame
{
    Q_OBJECT

public:
    explicit postprocess(int, QWidget *parent = nullptr);
    ~postprocess();
    bool getData(QMap<QString, QString>&, int);
    bool putData(QJsonObject &,int,QString);
    void refreshData(int);
    bool copyFiles(QString dirName, int);

private slots:
    void on_CmB_PPFlag_currentIndexChanged(int index);

    void on_Btn_UploadFiles_clicked();

private:
    Ui::postprocess *ui;
    QStringList pprocessfilenames;
    void hideshowelems(int);
    Hydroerror error;

};

#endif // POSTPROCESS_H

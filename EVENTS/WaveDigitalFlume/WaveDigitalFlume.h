#ifndef WAVEDIGITALFLUME_H
#define WAVEDIGITALFLUME_H

#include <RandomVariablesContainer.h>
#include <SimCenterAppWidget.h>
#include "AgaveCurl.h"

#include <QDebug>
#include <QFile>
#include <QDir>
#include <QInputDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>
#include <QString>
#include <QTreeWidget>
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QSettings>
#include <QUuid>
#include <ZipUtils.h>
#include <QStandardPaths>

namespace Ui {
class WaveDigitalFlume;
}


class WaveDigitalFlume : public SimCenterAppWidget
{
    Q_OBJECT

public:
    explicit WaveDigitalFlume(RandomVariablesContainer *theRV, QWidget *parent = nullptr);
    ~WaveDigitalFlume();

private:
    Ui::WaveDigitalFlume *ui;

    AgaveCurl *theRemoteService;
};

#endif // WAVEDIGITALFLUME_H

#ifndef WAVEDIGITALFLUME_H
#define WAVEDIGITALFLUME_H

/* *****************************************************************************
Copyright (c) 2016-2017, The Regents of the University of California (Regents).
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of the FreeBSD Project.

REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED HEREUNDER IS
PROVIDED "AS IS". REGENTS HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT,
UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

*************************************************************************** */

// Written: Ajay B Harish (May 2022)
// Modified:

#include "../Common/projectsettings.h"
#include "../GeoClawOpenFOAM/swcfdint.h"
#include "../Common/bathymetry.h"
#include "../GeoClawOpenFOAM/buildings.h"
#include "../GeoClawOpenFOAM/floatingbds.h"
#include "../GeoClawOpenFOAM/meshing.h"
#include "../GeoClawOpenFOAM/materials.h"
#include "../GeoClawOpenFOAM/initialconvel.h"
#include "../GeoClawOpenFOAM/initialconpres.h"
#include "../GeoClawOpenFOAM/initialconalpha.h"
#include "../GeoClawOpenFOAM/boundary.h"
#include "../GeoClawOpenFOAM/solver.h"
#include "cfdsolvers/openfoam/openfoam.h"
#include "../GeoClawOpenFOAM/postprocess.h"
#include "../GeoClawOpenFOAM/hydroerror.h"
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

class AgaveCurl;


class WaveDigitalFlume : public SimCenterAppWidget
{
    Q_OBJECT

public:
    WaveDigitalFlume(RandomVariablesContainer *theRV, QWidget *parent = nullptr);
    ~WaveDigitalFlume();

    bool outputToJSON(QJsonObject &rvObject);
    bool inputFromJSON(QJsonObject &rvObject);
    bool outputAppDataToJSON(QJsonObject &rvObject);
    bool inputAppDataFromJSON(QJsonObject &rvObject);
    bool copyFiles(QString &dirName);
    bool outputCitation(QJsonObject &jsonObject) override;

private slots:
    void on_SimOptions_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    void clearAllData(void);
    void initialize();
    void refresh_projsettings();

    void saveJson(QString wdir, QString pname, QJsonDocument jsondoc);

    Ui::WaveDigitalFlume *ui;
    QMap<int, QMap<QString, QString>*> allData;

    int simtype; // Simulation type
    QStringList optiontree; // Tree widget names
    QString applicationname = "Hydro-UQ";
    QString applicationversion = "3.2.0";
    AgaveCurl *theRemoteService;
    projectsettings *theSettings;
};

#endif // WAVEDIGITALFLUME_H

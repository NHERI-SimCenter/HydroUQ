#ifndef GEOCLAW_OPENFOAM_H
#define GEOCLAW_OPENFOAM_H

#include "projectsettings.h"
#include "swcfdint.h"
#include "bathymetry.h"
#include "buildings.h"
#include "floatingbds.h"
#include "meshing.h"
#include "materials.h"
#include "initialconvel.h"
#include "initialconpres.h"
#include "initialconalpha.h"
#include "boundary.h"
#include "solver.h"
#include "cfdsolvers/openfoam/openfoam.h"
#include "postprocess.h"
#include "hydroerror.h"

#include <SimCenterAppWidget.h>
#include <QDebug>
#include <QFile>
#include <QInputDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>
#include <QString>
#include <QTreeWidget>
#include <RandomVariablesContainer.h>

//QT_BEGIN_NAMESPACE
//QT_END_NAMESPACE

namespace Ui {
  class GeoClawOpenFOAM;
}


class AgaveCurl;

class GeoClawOpenFOAM : public SimCenterAppWidget
{
    Q_OBJECT

public:
  GeoClawOpenFOAM(RandomVariablesContainer *theRV, QWidget *parent = nullptr);
  ~GeoClawOpenFOAM();
   
    bool outputToJSON(QJsonObject &rvObject);
    bool inputFromJSON(QJsonObject &rvObject);
    bool outputAppDataToJSON(QJsonObject &rvObject);
    bool inputAppDataFromJSON(QJsonObject &rvObject);
    bool copyFiles(QString &dirName);
				    
private slots:
    void errorMessage(QString message);
    void on_SimOptions_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    void clearAllData(void);
    void initialize();
    void refresh_projsettings();
  
    void saveJson(QString wdir, QString pname, QJsonDocument jsondoc);
 
    Ui::GeoClawOpenFOAM *ui;
    QMap<int, QMap<QString, QString>*> allData;

    int simtype; // Simulation type
    QStringList optiontree; // Tree widget names
    QString applicationname = "Hydro-UQ";
    QString applicationversion = "1.0.0";
    AgaveCurl *theRemoteService;
    Hydroerror error;
};
#endif // GEOCLAW_OPENFOAM_H

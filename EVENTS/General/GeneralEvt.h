#ifndef GENERALEVT_H
#define GENERALEVT_H

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
  class GeneralEvt;
}


class AgaveCurl;

class GeneralEvt : public SimCenterAppWidget
{
    Q_OBJECT

public:
  GeneralEvt(RandomVariablesContainer *theRV, QWidget *parent = nullptr);
  ~GeneralEvt();
   
    bool outputToJSON(QJsonObject &rvObject);
    bool inputFromJSON(QJsonObject &rvObject);
    bool outputAppDataToJSON(QJsonObject &rvObject);
    bool inputAppDataFromJSON(QJsonObject &rvObject);
    bool copyFiles(QString &dirName);
				    
private slots:
   void errorMessage(QString message);  
    void on_Btn_Generate_Files_clicked();
    void on_SimOptions_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_Btn_SubTACC_clicked();

private:
    void clearAllData(void);
    void initialize();
    void refresh_projsettings();
  
    void saveJson(QString wdir, QString pname, QJsonDocument jsondoc);
 
    Ui::GeneralEvt *ui;
    QMap<int, QMap<QString, QString>*> allData;

    int simtype; // Simulation type
    QStringList optiontree; // Tree widget names
    QString applicationname = "Hydro-UQ";
    QString applicationversion = "0.9.0 (Alpha)";
    AgaveCurl *theRemoteService;
};
#endif // GENERALEVT_H

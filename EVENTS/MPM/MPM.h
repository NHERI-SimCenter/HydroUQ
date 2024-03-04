#ifndef MATERIAL_POINT_METHOD_H
#define MATERIAL_POINT_METHOD_H

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

// Author: JustinBonus
// Date: 1/2024

#include <SimCenterAppWidget.h>
class SC_DoubleLineEdit;
class SC_IntLineEdit;

//Forward declaration
class InputWidgetParameters;
class RandomVariablesContainer;
class QComboBox;
class QGridLayout;
class QVBoxLayout;
class QHBoxLayout;
class QSpinBox;
class QLineEdit;
class QTabWidget;
class LineEditRV;
class QGroupBox;
class QPushButton;
class QCheckBox;
class QFormLayout;
class QLabel;

class SettingsMPM;
class BodiesMPM;
class BoundariesMPM;
class SensorsMPM;
class OutputsMPM; 

// Trying this
// class SC_RemoteAppTool;
// class SlidingStackedWidget;

class MPM : public SimCenterAppWidget
{
public:
   //  explicit MPM(RandomVariablesContainer *theRandomVariableIW, QWidget *parent = 0);
    MPM( QWidget *parent = 0);
    ~MPM();

    bool inputFromJSON(QJsonObject &rvObject);
    bool outputToJSON(QJsonObject &rvObject);  
    bool outputAppDataToJSON(QJsonObject &rvObject);
    bool inputAppDataFromJSON(QJsonObject &rvObject);
    bool copyFiles(QString &dirName);

    bool setupCase();
    bool cleanCase();
    bool removeOldFiles();
    bool isCaseConfigured();
    void readCaseData();

    bool initialize(); // From WE-UQ
    bool isInitialize(); // From WE-UQ

    QVector<QVector<double>> readTxtData(QString fileName);

   void writeMPMFiles();
   void updateJSON();
    QString caseDir();
   //  QString foamDictsPath();
    QString templateDictDir();
    QString pyScriptsPath();
    QString simulationType();

signals:

public slots:
   void clear(void);
   void onBrowseCaseDirectoryButtonClicked(void);
   // void  updateStructureDimensionsSlot(QString val);
   // void  updateStructureOriginSlot(QString val);
private:
   QHBoxLayout                  *mainWindowLayout;

   // QVBoxLayout                  *inputWindowLayout;
   // QGroupBox                    *inputWindowGroup;

   SettingsMPM   *mpmSettings;
   BodiesMPM     *mpmBodies;
   BoundariesMPM *mpmBoundaries;
   SensorsMPM    *mpmSensors;
   OutputsMPM    *mpmOutputs; 
  
   QLineEdit                    *caseDirectoryPathWidget;
   QGroupBox                    *caseDirectoryGroup;
   QGridLayout                  *caseDirectoryLayout;

   RandomVariablesContainer     *theRandomVariablesContainer;
   QStringList                  varNamesAndValues;

   QString                      workingDirPath;

   bool caseInitialized = false; // From WE-UQ

};

#endif // MATERIAL_POINT_METHOD_H

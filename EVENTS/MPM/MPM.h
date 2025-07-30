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

// #include <ResultsMPM.h>

// Forward declaration
class InputWidgetParameters;
class RandomVariablesContainer;
class LineEditRV;

class SettingsMPM;
class BodiesMPM;
class BoundariesMPM;
class SensorsMPM;
class OutputsMPM; 
class ResultsMPM;

class SC_DoubleLineEdit;
class SC_IntLineEdit;

class QGridLayout;
class QVBoxLayout;
class QHBoxLayout;

class QComboBox;
class QSpinBox;
class QLineEdit;
class QTabWidget;

class QGroupBox;
class QPushButton;
class QCheckBox;
class QFormLayout;
class QLabel;
class QScrollArea;
class QStackedWidget;
class SlidingStackedWidget;


namespace Qt3DExtras {
   class Qt3DWindow;
}

class MPM : public SimCenterAppWidget
{
   // friend class ResultsMPM; // Allow ResultsMPM to access private members. TODO: use a better vis architecture
   
   Q_OBJECT 

public:
    explicit MPM(RandomVariablesContainer *theRandomVariableIW, QWidget *parent = 0);
   // MPM( QWidget *parent = 0);
   ~MPM();


   bool inputFromJSON(QJsonObject &rvObject) override;
   bool outputToJSON(QJsonObject &rvObject) override;  
   bool outputAppDataToJSON(QJsonObject &rvObject);
   bool inputAppDataFromJSON(QJsonObject &rvObject);
   bool copyFiles(QString &dirName) override;
   bool outputCitation(QJsonObject &jsonObject) override;

   bool initialize();
   bool isInitialize();
   void emitInitializeVisualization(void);

   bool setupCase();
   bool cleanCase();
   bool removeOldFiles();
   bool isCaseConfigured();
   void readCaseData();

   void importMainDomainJsonFile(QJsonObject &rvObject);
   // QVector<QVector<double>> readTxtData(QString fileName);

   void executeBackendScript();
   void updateJSON();
   QString caseDir();
   // QString templateDictDir();
   QString pyScriptsPath();
   QString simulationType();
   //  QString foamDictsPath(); // For OpenFOAM from WE-UQ, not MPM

#define USE_MPM_RESULTS_WIDGET_FUNCTIONS true
#ifdef USE_MPM_RESULTS_WIDGET_FUNCTIONS
   SC_ResultsWidget* getResultsWidget(QWidget *parent); // For vis of output data results 
#endif
   void hideVisualization(void);
   void showVisualization(void);
   int emitSetSliderIndex(int index);
signals:
   void initializeVisualization(void);
   int setSliderIndex(int index);
public slots:
   void clear(void);
   void onBrowseCaseDirectoryButtonClicked(void);

private:
   QHBoxLayout                  *mainWindowLayout;
   QGridLayout                  *mainLayout;
   SettingsMPM                  *mpmSettings;
   BodiesMPM                    *mpmBodies;
   BoundariesMPM                *mpmBoundaries;
   SensorsMPM                   *mpmSensors;
   OutputsMPM                   *mpmOutputs; 
   ResultsMPM                   *mpmResults;

   RandomVariablesContainer     *theRandomVariablesContainer;
   QStringList                  varNamesAndValues;

   QString                      workingDirPath;
   QLineEdit                    *caseDirectoryPathWidget;
   QGroupBox                    *caseDirectoryGroup;
   QGridLayout                  *caseDirectoryLayout;
   QTabWidget                   *theTabWidget;
   // QScrollArea                  *theScrollArea;
   // QVBoxLayout                  *visWindowLayout;
   // QGroupBox                    *visWindowGroup;
   // QVBoxLayout                  *inputWindowLayout;
   // QGroupBox                    *inputWindowGroup;
   bool caseInitialized = false; 

#if ( ( defined(_WIN32) || defined(__linux__) || defined(linux) || defined(WIN32) ) && !defined(__APPLE__) ) && !defined(NO_MPM_QT3D)
   Qt3DExtras::Qt3DWindow* view;
   QWidget* container;
#endif
   // QStackedWidget *parentStackedWidget;
   // SlidingStackedWidget *stackedWidget;
   // QWebEngineView* m_pWebView;
};

#endif // MATERIAL_POINT_METHOD_H

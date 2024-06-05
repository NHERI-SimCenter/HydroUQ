#ifndef SIMPLE_WAVES_H
#define SIMPLE_WAVES_H

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
// Date: 5/2024

#include <SimCenterAppWidget.h>

// #include <ResultsSimpleWaves.h>
#include <RandomVariablesContainer.h>
#include <LineEditRV.h>
#include <SC_DoubleLineEdit.h>
#include <SC_IntLineEdit.h>

#include <QJsonObject>
#include <QString>
#include <QWidget>


// #include <QWebEngineView>
// Forward declaration
class InputWidgetParameters;
class RandomVariablesContainer;
class LineEditRV;
class QJsonObject;
class QString;
class QWidget;

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
class QRadioButton;
class QStackedWidget;


class SimpleWaves : public SimCenterAppWidget
{
      Q_OBJECT 

public:
    explicit SimpleWaves(RandomVariablesContainer *theRandomVariableIW, QWidget *parent = 0);
   // SimpleWaves( QWidget *parent = 0);
    ~SimpleWaves() ;

//    friend class ResultsSimpleWaves; // Allow ResultsSimpleWaves to access private members. TODO: use a better vis architecture

   bool inputFromJSON(QJsonObject &rvObject) override;
   bool outputToJSON(QJsonObject &rvObject) override;  
   bool outputAppDataToJSON(QJsonObject &rvObject) ;
   bool inputAppDataFromJSON(QJsonObject &rvObject);
   bool copyFiles(QString &dirName) override;
   bool outputCitation(QJsonObject &jsonObject) override;

//    bool initialize();
//    bool isInitialize();

//    bool setupCase();
//    bool cleanCase();
//    bool removeOldFiles();
//    bool isCaseConfigured();
//    void readCaseData();

//    void importMainDomainJsonFile(QJsonObject &rvObject);
//    QVector<QVector<double>> readTxtData(QString fileName);

   void executeBackendScript();
//    void updateJSON();
//    QString caseDir();
   QString pyScriptsPath();

//    SC_ResultsWidget* getResultsWidget(QWidget *parent) override; // For vis of output data results 

signals:

public slots:
   void clear(void) override;
   void onBrowseCaseDirectoryButtonClicked(void);

 /**
   * Update ability to provide seed based on changed status of radio button
   * @param[in] checked Current status of radio button for providing seed
   */
  void provideSeed(const bool& checked);

private:
   QHBoxLayout                  *mainWindowLayout;
//    QGridLayout                  *mainLayout;
// 
//  RandomVariablesContainer* rvInputWidget; /**< Widget for inputting random
						//   variables */
   QHBoxLayout * parametersLayout; /**< Layout for stochastic model widget */
   QComboBox* modelSelection; /**< Selection of ground motion model inputs */

   RandomVariablesContainer     *theRandomVariablesContainer;
//    QStringList                  varNamesAndValues;

//    QString                      workingDirPath;
//    QLineEdit                    *caseDirectoryPathWidget;

  

//    QGroupBox                    *caseDirectoryGroup;
//    QGridLayout                  *caseDirectoryLayout;
//    QTabWidget                   *theTabWidget;


   QLabel *modelDescription; /**< Brief description of model indicating relevant
   				 paper where more information can be found describing
   				 model in greater detail */
   
   QComboBox *exposureCategory; /**< type of wave spectrum */
   LineEditRV *dragCoefficient; /**< drag Coefficient */
   LineEditRV *dragArea; /**< drag Area */
   LineEditRV *significantWaveHeight; /**< significant wave height (ft) */
   LineEditRV *peakPeriod; /**< peak period (s) */
   LineEditRV *waterDepth; /**< water depth (ft) */
   LineEditRV *recorderOriginX; /**< x-coordinate of recorder origin */
   SC_IntLineEdit *recorderCountZ; /**< number of recorders in z-direction */
   LineEditRV *timeStep; /**< time step (s) */
   LineEditRV *timeDuration; /**< time duration (s) */
   
   
   
   QSpinBox *seed; /**< Value to use as seed for motion generation */
   QRadioButton *useSeed; /**< Radio button to indicate whether specific seed
                              value should be used */

};

#endif // SIMPLE_WAVES_H

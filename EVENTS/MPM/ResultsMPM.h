#ifndef RESULTS_MPM_H
#define RESULTS_MPM_H

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

// Written by: JustinBonus

#include <SC_ResultsWidget.h>
// #include <QList>
// #include <MPM.h>
class MPM;
class InputWidgetParameters;
class RandomVariablesContainer;
class QComboBox;
class QGridLayout;
class QVBoxLayout;
class QHBoxLayout;
class QSpinBox;
class QCheckBox;
class QLineEdit;
class LineEditRV;
class QTabWidget;
class QTableWidget;
class QGroupBox;
class QPushButton;
class QDoubleSpinBox;
class QLabel;
class QRadioButton;
class QString;


class ResultsMPM : public SC_ResultsWidget
{
    friend class MPM; // Allow MPM to access private members. TODO: use a better vis architecture (e.g. MVC, VIPER, etc.) 
    Q_OBJECT
public:
    explicit ResultsMPM(MPM *parent = 0);
    ~ResultsMPM() override;

    void processResults(QString &dirName);     
    int processResults(QString &outputFile, QString &dirName, QString &assetType, QList<QString> typesInAssetType) ;
    int processResults(QString &outputFile, QString &dirName) ;   
    bool inputFromJSON(QJsonObject &jsonObject) override;
    bool outputToJSON(QJsonObject &jsonObject) override; 
    void clear(void) override;  // This is a virtual function in SC_ResultsWidget, so it must be implemented here.
    void updateWidgets(); 

signals:

public slots:
    void onProcessSensorsClicked(void);
    void onPlotSpectraClicked(void); // S
    // void onPlotPressureClicked(void); // P
    // void onPlotElevationClicked(void); // E
    // void onPlotForceClicked(void); // F
    bool simulationCompleted();
    void plotSensors(void);
    bool copyFiles(QString &dirName);

private:

    MPM                  *mainModel;
    QVBoxLayout          *layout;

    // A - Process Sensors
    QGroupBox            *processSensorsGroup;
    QGridLayout          *processSensorsLayout;
    QPushButton          *processSensorsButton;
    QComboBox            *processSensorsName;

    // S - Plot Selected Sensor
    QGroupBox            *plotSpectraGroup;
    QGridLayout          *plotSpectraLayout;
    QPushButton          *plotSpectra;
    QComboBox            *profileNameS;
    QComboBox            *sensorNumS;
    QComboBox            *bodyNumS;
    QComboBox            *deviceNumS;

    // // E - Plot Elevation
    // QGroupBox            *plotElevationGroup;
    // QGridLayout          *plotElevationLayout;
    // QPushButton          *plotElevation;
    // QComboBox            *profileNameE;

    // // F - Plot Force
    // QGroupBox            *plotForceGroup;
    // QGridLayout          *plotForceLayout;
    // QPushButton          *plotForce;
    // QComboBox            *profileNameF;

    // // P - Plot Pressure
    // QGroupBox            *plotPressureGroup;
    // QGridLayout          *plotPressureLayout;
    // QPushButton          *plotPressure;
    // QComboBox            *profileNameP;

public:

};

#endif // RESULTS_MPM_H
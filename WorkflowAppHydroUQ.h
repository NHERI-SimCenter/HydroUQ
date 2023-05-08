#ifndef WORKFLOW_APP_HYDRO_UQ_H
#define WORKFLOW_APP_HYDRO_UQ_H

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
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
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

// Written: fmckenna

#include <QWidget>

#include <WorkflowAppWidget.h>

class SimCenterComponentSelection;

class RandomVariablesContainer;
class InputWidgetBIM;
class InputWidgetUQ;
class SIM_Selection;
class UQ_EngineSelection;
class FEA_Selection;
class UQOptions;
class ResultsWidget;
class GeneralInformationWidget;
class HydroEventSelection;
class QStackedWidget;
class UQ_Results;

class RunLocalWidget;
class RunWidget;
class Application;
class RemoteService;
class RemoteJobManager;
class QNetworkAccessManager;
class QNetworkReply;
class EDP_Selection;

class WorkflowAppHydroUQ : public WorkflowAppWidget
{
    Q_OBJECT
public:
    explicit WorkflowAppHydroUQ(RemoteService *theService, QWidget *parent = 0);
    ~WorkflowAppHydroUQ();

    bool outputToJSON(QJsonObject &rvObject);
    bool inputFromJSON(QJsonObject &rvObject);
    void clear(void);

    //void setMainWindow(MainWindow* window);
    void onRunButtonClicked();
    void onRemoteRunButtonClicked();
    void onRemoteGetButtonClicked();
    void onExitButtonClicked();
    int getMaxNumParallelTasks();
    
signals:
    void setUpForApplicationRunDone(QString &tmpDirectory, QString &inputFile);
    void sendLoadFile(QString filename);

public slots:  

    void setUpForApplicationRun(QString &, QString &);
    void processResults(QString &resultsDir);
    //void processResults(QString dakotaOut, QString dakotaTab, QString inputFile);

    int loadFile(QString &filename);
    void replyFinished(QNetworkReply*);

private:
    // sidebar container selection
    SimCenterComponentSelection *theComponentSelection;

    // objects that go in sidebar
    GeneralInformationWidget *theGI;
    RandomVariablesContainer *theRVs;
    SIM_Selection *theSIM;
    UQ_EngineSelection *theUQ_Selection;
    HydroEventSelection *theEventSelection;
    FEA_Selection *theAnalysisSelection;
    EDP_Selection *theEDP_Selection;
    UQ_Results *theResults;

    // objects for running the workflow and obtaining results
    RunWidget *theRunWidget;
    Application *localApp;
    Application *remoteApp;
    RemoteJobManager *theJobManager;

    QJsonObject *jsonObjOrig;
    QNetworkAccessManager *manager;
};

#endif // WORKFLOW_APP_HYDRO_UQ_H

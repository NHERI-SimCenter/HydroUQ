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

// Written: fmckenna
// Modified: Ajay B Harish (Feb 2021)
// Modified: JustinBonus (2024)

#include "HydroEventSelection.h"


#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QStackedWidget>
#include <QComboBox>
#include <QJsonObject>
#include <QJsonArray>
#include <QLabel>
#include <QLineEdit>
#include <QDebug>
#include <QFileDialog>
#include <QPushButton>
#include <SectionTitle.h>
#include <QScrollArea>

#include <ExistingSimCenterEvents.h>
#include "Utils/ProgramOutputDialog.h"

#include <UserDefinedApplication.h>
#include <GeoClawOpenFOAM/GeoClawOpenFOAM.h>
#include <WaveDigitalFlume/WaveDigitalFlume.h>
#include <coupledDigitalTwin/CoupledDigitalTwin.h>
#include <MPM/MPM.h>
#include <StochasticWaveModel/include/StochasticWaveInput.h>
#include <TaichiEvent/TaichiEvent.h>
#include <MPM/SPH.h>
//*********************************************************************************
// Main Hydro event
//*********************************************************************************

enum class Event_b : bool {
    GeoClawOpenFOAM_b = false,
    WaveDigitalFlume_b = true,
    CoupledDigitalTwin_b = true,
    ClaymoreUW_b = true,
    TaichiEvent_b = true,
    StochasticWaves_b = true,
    SPH_b = false
};

enum class Event_e : int {
    Start_e = 0, // For C++ iteration
    GeoClawOpenFOAM_e = Start_e,
    WaveDigitalFlume_e,
    CoupledDigitalTwin_e,
    ClaymoreUW_e,   
    TaichiEvent_e,
    StochasticWaves_e,
    SPH_e,
    Last_e, // For C++ iteration
    Count_e = Last_e // Count of number of events
};

const int EventSelectionIndexArray[] = {
    static_cast<int>(Event_e::GeoClawOpenFOAM_e),
    static_cast<int>(Event_e::WaveDigitalFlume_e),
    static_cast<int>(Event_e::CoupledDigitalTwin_e),
    static_cast<int>(Event_e::ClaymoreUW_e),
    static_cast<int>(Event_e::TaichiEvent_e),
    static_cast<int>(Event_e::StochasticWaves_e),
    static_cast<int>(Event_e::SPH_e)
};

const bool EventSelectionEnabledArray[] = {
    static_cast<bool>(Event_b::GeoClawOpenFOAM_b),
    static_cast<bool>(Event_b::WaveDigitalFlume_b),
    static_cast<bool>(Event_b::CoupledDigitalTwin_b),
    static_cast<bool>(Event_b::ClaymoreUW_b),
    static_cast<bool>(Event_b::TaichiEvent_b),
    static_cast<bool>(Event_b::StochasticWaves_b),
    static_cast<bool>(Event_b::SPH_b)
};

const QString EventSelectionStringArray[] = {
    static_cast<QString>("GeoClawOpenFOAM"),
    static_cast<QString>("WaveDigitalFlume"),
    static_cast<QString>("CoupledDigitalTwin"),
    static_cast<QString>("MPM"),
    static_cast<QString>("TaichiEvent"),
    static_cast<QString>("StochasticWave"),
    static_cast<QString>("SPH")
};

const QString EventSelectionDisplayArray[] = {
    "General Event (GeoClaw and OpenFOAM)",
    "Digital Twin (GeoClaw and OpenFOAM)",
    "Digital Twin (OpenFOAM and OpenSees)",
    "Digital Twin (MPM)",
    "General Event (Taichi)",
    "Stochastic Wave Loading",
    "Digital Twin (SPH)"
};

const QString EventSelectionToolTipArray[] = {
    "Shallow-Water-Equations -> Finite-Volume-Method (GeoClaw -> OpenFOAM) [Multi-CPU]",
    "Shallow-Water-Equations -> Finite-Volume-Method -> Finite-Element-Analysis (GeoClaw -> OpenFOAM -> OpenSees) [Multi-CPU]",
    "Finite-Volume-Method <-> Finite-Element-Analysis (OpenFOAM <-> OpenSees) [Multi-CPU]",
    "Material-Point-Method (ClaymoreUW) [Multi-GPU]",
    "High-Performance Numerical Simulation (Taichi) [CPU-GPU]",
    "Stochastic Wave Loading By Sea-State (welib) [CPU]",
    "Smoothed-Particle-Hydrodynamics (DualSPHysics) [CPU-GPU]"
};

// Compile time checks to ensures above arrays are in sync
static_assert(static_cast<int>(sizeof(EventSelectionIndexArray) / sizeof(const int)) == static_cast<int>(Event_e::Count_e));
static_assert(sizeof(EventSelectionIndexArray) / sizeof(const int) == sizeof(EventSelectionEnabledArray) / sizeof(const bool));
static_assert(sizeof(EventSelectionIndexArray) / sizeof(const int) == sizeof(EventSelectionStringArray ) / sizeof(const QString));
static_assert(sizeof(EventSelectionIndexArray) / sizeof(const int) == sizeof(EventSelectionDisplayArray) / sizeof(const QString));
static_assert(sizeof(EventSelectionIndexArray) / sizeof(const int) == sizeof(EventSelectionToolTipArray) / sizeof(const QString));


// Design pattern for the HydroEventSelection class in OOP is the 
HydroEventSelection::HydroEventSelection(RandomVariablesContainer *theRandomVariableIW, RemoteService* remoteService, QWidget *parent)
    : SimCenterAppWidget(parent), theCurrentEvent(0), theRandomVariablesContainer(theRandomVariableIW)

{
    // Unused variables
    // (void) generalInfoWidget;
    QVBoxLayout *layout = new QVBoxLayout();

    // The selection of different events
    QHBoxLayout *theSelectionLayout = new QHBoxLayout();
    SectionTitle *label=new SectionTitle();
    label->setMinimumWidth(250);
    label->setText(QString("Event Type"));

    // Combobox for different simulation types
    eventSelection = new QComboBox();
    eventSelection->setObjectName("LoadingTypeCombox");
    eventSelection->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

    // Iterating through the array of event types to load them into the combobox
    for (int evt : EventSelectionIndexArray) {
        eventSelection->addItem(EventSelectionDisplayArray[evt]);
        if (EventSelectionEnabledArray[evt] == false) { 
            // eventSelection->setItemData(evt, QColor(Qt::gray), Qt::TextColorRole);
            eventSelection->setItemData(evt, false, Qt::UserRole - 1); // Disable the event
            continue;
        }
        eventSelection->setItemData(evt, EventSelectionToolTipArray[evt], Qt::ToolTipRole);
    }    

    theSelectionLayout->addWidget(label);
    QSpacerItem *spacer = new QSpacerItem(50,10);
    theSelectionLayout->addItem(spacer);
    theSelectionLayout->addWidget(eventSelection, 2);
    theSelectionLayout->addStretch(3);
    layout->addLayout(theSelectionLayout);


    // ---
    // Create the stacked widget for the different event-method types
    theStackedWidget = new QStackedWidget();

    // create the individual load widgets & add to stacked widget
    for (int evt : EventSelectionIndexArray) {
        if (EventSelectionEnabledArray[static_cast<int>(evt)] == false) { 
            theStackedWidget->addWidget(new QWidget()); // Add a dummy widget to keep the index in sync
            continue;
        }
        switch (static_cast<Event_e>(evt)) {
            case (Event_e::GeoClawOpenFOAM_e):
                theGeoClawOpenFOAM = new GeoClawOpenFOAM(theRandomVariablesContainer);
                theStackedWidget->addWidget(theGeoClawOpenFOAM);
                break;
            case (Event_e::WaveDigitalFlume_e):
                theWaveDigitalFlume = new WaveDigitalFlume(theRandomVariablesContainer);
                theStackedWidget->addWidget(theWaveDigitalFlume);
                break;
            case (Event_e::CoupledDigitalTwin_e):
                theCoupledDigitalTwin = new CoupledDigitalTwin(theRandomVariablesContainer);
                theStackedWidget->addWidget(theCoupledDigitalTwin);
                break;
            case (Event_e::ClaymoreUW_e):
                theMPM = new MPM(theRandomVariablesContainer);
                theStackedWidget->addWidget(theMPM);
                break;
            case (Event_e::TaichiEvent_e):
                theTaichiEvent = new TaichiEvent(theRandomVariablesContainer);
                theStackedWidget->addWidget(theTaichiEvent);
                break;
            case (Event_e::StochasticWaves_e):
                theStochasticWaves = new StochasticWaveInput(theRandomVariablesContainer);
                theStackedWidget->addWidget(theStochasticWaves);
                break;
            case (Event_e::SPH_e):
                theSPH = new SPH(theRandomVariablesContainer);
                theStackedWidget->addWidget(theSPH);
                break;
            default:
                qDebug() << "ERROR: HydroEventSelection::HydroEventSelection - Unknown Event Type: " << evt;
                break;
        }
    } 

    //  Setup the Layout

    //
    // put inside a scroll area
    //
    
    QScrollArea *sa = new QScrollArea;
    sa->setWidgetResizable(true);
    sa->setLineWidth(0);
    sa->setFrameShape(QFrame::NoFrame);
    sa->setWidget(theStackedWidget);
    layout->addWidget(sa);    

    this->setLayout(layout);
    
    // --
    // Set the default event to select at boot-up
    const Event_e indexDefault = Event_e::CoupledDigitalTwin_e;
    theStackedWidget->setCurrentIndex(static_cast<int>(indexDefault));
    if constexpr (indexDefault == Event_e::GeoClawOpenFOAM_e) {
        theCurrentEvent = theGeoClawOpenFOAM;
    }
    if constexpr (indexDefault == Event_e::WaveDigitalFlume_e) {
        theCurrentEvent = theWaveDigitalFlume;
    }
    if constexpr (indexDefault == Event_e::CoupledDigitalTwin_e) {
        theCurrentEvent = theCoupledDigitalTwin;
    }
    if constexpr (indexDefault == Event_e::ClaymoreUW_e) {
        theCurrentEvent = theMPM;
    }
    if constexpr (indexDefault == Event_e::TaichiEvent_e) {
        theCurrentEvent = theTaichiEvent;
    }
    if constexpr (indexDefault == Event_e::StochasticWaves_e) {
        theCurrentEvent = theStochasticWaves;
    }
    if constexpr (indexDefault == Event_e::SPH_e) {
        theCurrentEvent = theSPH;
    }

    connect(eventSelection, SIGNAL(currentIndexChanged(int)), this, SLOT(eventSelectionChanged(int)));
    connect(eventSelection, SIGNAL(currentTextChanged(QString)), this, SLOT(eventSelectionChanged(QString))); // WE-UQ
    
    eventSelection->setCurrentIndex(static_cast<int>(indexDefault));
    theStackedWidget->setCurrentIndex(static_cast<int>(indexDefault));

    // QString stringForMPM = "Digital Twin (MPM)";
    // QString stringForFOAMySees = "Digital Twin (OpenFOAM and OpenSees)";

    // // Connect signal and slots
    // connect(theMPM, SIGNAL(errorMessage(QString)), this, SIGNAL(sendErrorMessage(QString))); // WE-UQ
    // connect(theMPM, SIGNAL(statusMessage(QString)), this, SIGNAL(sendStatusMessage(QString))); // WE-UQ
    // connect(theMPM, SIGNAL(fatalMessage(QString)), this, SIGNAL(sendFatalMessage(QString))); // WE-UQ


    /*
    connect(theGeoClawOpenFOAM, &SimCenterAppWidget::sendErrorMessage, this, [this](QString message) {emit sendErrorMessage(message);});
    connect(theGeoClawOpenFOAM, &SimCenterAppWidget::sendFatalMessage, this, [this](QString message) {emit sendFatalMessage(message);});
    connect(theGeoClawOpenFOAM, &SimCenterAppWidget::sendStatusMessage, this, [this](QString message) {emit sendStatusMessage(message);});
    */
}

//*********************************************************************************
// Destructor for the main Hydro event
//*********************************************************************************
HydroEventSelection::~HydroEventSelection()
{


}

//*********************************************************************************
// If Event selection is changed
//*********************************************************************************
void HydroEventSelection::eventSelectionChanged(int arg1)
{
    // switch stacked widgets depending on text
    // note type output in json and name in pull down are not the same and hence the ||
    if constexpr (static_cast<bool>(Event_b::GeoClawOpenFOAM_b)) {
        if (arg1 == static_cast<int>(Event_e::GeoClawOpenFOAM_e)) {
            theCurrentEvent = theGeoClawOpenFOAM;
        }
    }

    if constexpr (static_cast<bool>(Event_b::WaveDigitalFlume_b)) {
        if (arg1 == static_cast<int>(Event_e::WaveDigitalFlume_e)) {
            theCurrentEvent = theWaveDigitalFlume;
        }
    }

    if constexpr (static_cast<bool>(Event_b::CoupledDigitalTwin_b)) {
        if (arg1 == static_cast<int>(Event_e::CoupledDigitalTwin_e)) {
            theCurrentEvent = theCoupledDigitalTwin;
        }
    }

    if constexpr (static_cast<bool>(Event_b::ClaymoreUW_b)) {
        if (arg1 == static_cast<int>(Event_e::ClaymoreUW_e)) {
            MPM* theM = dynamic_cast<MPM*>(theMPM);
            theM->hideVisualization();
            theM->showVisualization(); 
            theCurrentEvent = theM->isInitialize() ? theMPM 
                            : (theM->initialize() ? theMPM : nullptr);
            if (theCurrentEvent == nullptr) 
            {
                qDebug() << "ERROR: Hydro-EventSelection failed while attempting to initialize the MPM Event, index: " << arg1;
                return;
            }     
        }        
    }

    if constexpr (static_cast<bool>(Event_b::TaichiEvent_b)) {
        if (arg1 == static_cast<int>(Event_e::TaichiEvent_e)) {
            theCurrentEvent = theTaichiEvent;
        }
    }

    if constexpr (static_cast<bool>(Event_b::StochasticWaves_b)) {
        if (arg1 == static_cast<int>(Event_e::StochasticWaves_e)) {
            theCurrentEvent = theStochasticWaves;
        }
    }

    if constexpr (static_cast<bool>(Event_b::SPH_b)) {
        if (arg1 == static_cast<int>(Event_e::SPH_e)) {
            SPH* theM = dynamic_cast<SPH*>(theSPH);
            theCurrentEvent = theM->isInitialize() ? theSPH 
                            : (theM->initialize() ? theSPH : nullptr); 
            if (theCurrentEvent == nullptr) 
            {
                qDebug() << "ERROR: Hydro-EventSelection failed while attempting to initialize the SPH Event, index: " << arg1;
                return;
            }     
        }        
    }

    if (static_cast<bool>(EventSelectionEnabledArray[arg1]) == false) {
        qDebug() << "ERROR: Hydro-EventSelection selection-type disabled: " << arg1;
        return;
    }
    theStackedWidget->setCurrentIndex(arg1);
    return;
}

void HydroEventSelection::eventSelectionChanged(const QString &arg1)
{
    // qDebug() << arg1;

    //
    // switch stacked widgets depending on text
    // note type output in json and name in pull down are not the same and hence the ||
    //

    for (int evt : EventSelectionIndexArray) {
        bool matchesString = (arg1 == EventSelectionStringArray[evt]);
        bool matchesDisplay = (arg1 == EventSelectionDisplayArray[evt]);
        if ((matchesString || matchesDisplay) && EventSelectionEnabledArray[evt]){
                theStackedWidget->setCurrentIndex(static_cast<int>(evt));
                eventSelectionChanged(static_cast<int>(evt));
                eventSelection->repaint();
                return;
        }
    }
    qDebug() << "ERROR: HydroEventSelection selection-type unknown: " << arg1;
    return;
}



void
HydroEventSelection::sendStatusMessage(QString message) {
    ProgramOutputDialog *theDialog=ProgramOutputDialog::getInstance();
    theDialog->appendInfoMessage(message);
}

void
HydroEventSelection::sendErrorMessage(QString message) {
    ProgramOutputDialog *theDialog=ProgramOutputDialog::getInstance();
    theDialog->appendErrorMessage(message);
}

void
HydroEventSelection::sendFatalMessage(QString message) {
    ProgramOutputDialog *theDialog=ProgramOutputDialog::getInstance();
    theDialog->appendErrorMessage(message);
}


//*********************************************************************************
// Input data from JSON
//*********************************************************************************
bool HydroEventSelection::inputFromJSON(QJsonObject &jsonObject) {

    QString type;
    QJsonObject theEvent;

    if (jsonObject.contains("Events"))
    {
        QJsonArray theEvents = jsonObject["Events"].toArray();
        QJsonValue theValue = theEvents.at(0);
        if (theValue.isNull())
        {
            qDebug() << "HydroEventSelection::inputFromJSON no Event in Events";
            return false;
        }
        theEvent = theValue.toObject();
        // From WE-UQ, adds type
        if (theEvent.contains("type")) {
            QJsonValue theName = theEvent["type"];
            type = theName.toString();
        } else {
            qDebug() << "HydroEventSelection::inputFromJSON no type in Event";
            return false;
        }
    }
    else
    {
        qDebug() << "HydroEventSelection::inputFromJSON Events found";
        return false;
    }

    int index = static_cast<int>(Event_e::CoupledDigitalTwin_e);
    qDebug() << "TYPE: " << type;
    bool flag = false;
    for (int evt : EventSelectionIndexArray) {
        bool matchesString = (type == EventSelectionStringArray[evt]);
        bool matchesDisplay = (type == EventSelectionDisplayArray[evt]);
        if ((matchesString || matchesDisplay) && EventSelectionEnabledArray[evt]) {
            index = static_cast<int>(evt); // The && checks if the event is enabled
            flag = true;
        }
        if (flag) break; 
    }
    if (!flag) {
        qDebug() << "HydroEventSelection::inputFromJSON Event type unknown: " << type;
        return flag;
    }

    qDebug() << "TYPE: " << type << "INDEX: " << index;

    eventSelection->setCurrentIndex(index);

    // if worked, just invoke method on new type
    if (theCurrentEvent != NULL)
    {
        return theCurrentEvent->inputFromJSON(theEvent);
    } 
    else 
    {
        qDebug() << "HydroEventSelection::inputFromJSON theCurrentEvent is nullptr, set to appropriate event idx: " << index;
    }

    Event_e index_e = static_cast<Event_e>(index);
    eventSelectionChanged(index);

    if (theCurrentEvent != nullptr) {
        return theCurrentEvent->inputFromJSON(theEvent);
    }


    qDebug() << "HydroEventSelection::inputFromJSON theCurrentEvent is nullptr, return false";
    return false;
}

//*********************************************************************************
// Output data to JSON
//*********************************************************************************
bool HydroEventSelection::outputToJSON(QJsonObject &jsonObject)
{
    if (theCurrentEvent == nullptr) {
        qDebug() << "HydroEventSelection::outputToJSON theCurrentEvent is nullptr";
        return false;
    }
    QJsonArray eventArray;
    QJsonObject singleEventData;
    bool result = theCurrentEvent->outputToJSON(singleEventData);
    if (!result) {
        qDebug() << "HydroEventSelection::outputToJSON - theCurrentEvent->outputToJSON returned false";
        return result;
    }
    eventArray.append(singleEventData);
    jsonObject["Events"]=eventArray;
    return result;
}

//*********************************************************************************
// Input AppData to JSON
//*********************************************************************************
bool HydroEventSelection::inputAppDataFromJSON(QJsonObject &jsonObject)
{
    QJsonObject theEvent;
    QString type;
    QString subtype;

    // from Events get the single event
    if (jsonObject.contains("Events"))
    {
        QJsonArray theEvents = jsonObject["Events"].toArray();
        QJsonValue theValue = theEvents.at(0);
        if (theValue.isNull())
        {
            qDebug() << "HydroEventSelection::inputAppDataFromJSON no Event in Events";
          return false;
        }
        theEvent = theValue.toObject();
        if (theEvent.contains("Application"))
        {
            QJsonValue theName = theEvent["Application"];
            type = theName.toString();
            if(theEvent.contains("subtype"))
                subtype = theEvent["subtype"].toString();

            qDebug() << "HydroEventSelection::inputAppDataFromJSON type: " << type;
        }
        else
        {
            return false;
        }
    }
    else
    {
        qDebug() << "HydroEventSelection::inputAppDataFromJSON Events not found";
        return false;
    }

    // Need the || (or) statements to map the different names of the same event and display names for convenience. Ideally we would have a proper map or enum
    // The folder for the event, the event header file, the event input file, the event's python script folder in SimCenterCommon, etc. will usually match these
    int index = static_cast<int>(Event_e::Start_e);
    for (int evt : EventSelectionIndexArray) {
        if (type == EventSelectionStringArray[evt]) {
            index = static_cast<int>(static_cast<int>(evt) * static_cast<int>(EventSelectionEnabledArray[evt])); // The * checks if the event is enabled
            eventSelectionChanged(index);
            // eventSelection->setCurrentIndex(index);
            // theCurrentEvent = theStackedWidget->widget(index); // Check if this is correct, if not, use the if-else statements below
            break;
        }
    }
    if (index >= static_cast<int>(Event_e::Count_e)) {
        qDebug() << "HydroEventSelection::inputAppDataFromJSON Event type unknown: " << type;
        return false;
    }


    // if ( 
    //     ((type == "GeneralEvent")
	// || (type == "General Event")) || ((type == "General") || (type == "General Event (GeoClaw and OpenFOAM)") || (type == "GeoClawOpenFoam") || (type == "GeoClawOpenFOAM"))) {

    //   theCurrentEvent = theGeoClawOpenFOAM;
    //   index = 0;
    // }
    // else if (((type == "DigitalTwin")
	// || (type == "Digital Twin") || (type == "Digital Twin (GeoClaw and OpenFOAM)") || (type == "WaveDigitalFlume"))) {
      
    //   theCurrentEvent = theWaveDigitalFlume;
    //   index = 1;
    // }
    // else if (((type == "CoupledDigitalTwin")
	// || (type == "Coupled Digital Twin")) || (type == "Digital Twin (OpenFOAM and OpenSees)") || (type == "coupledDigitalTwin")) {
      
    //   theCurrentEvent = theCoupledDigitalTwin;
    //   index = 2;
    // }
    // else if (((type == "MPM")
	// || (type == "Material Point Method")) || ((type == "General Event (MPM)") || (type == "Digital Twin (MPM)")) || (type == "MPMDigitalTwin") || (type == "theMPM")) {
      
    //   theCurrentEvent = theMPM;
    //   index = 3;
    // }
    // else if ((type == "StochasticWave")
    // || (type == "StochasticWaveJonswap") || (type == "Stochastic Wave Loading")) {
      
    //   theCurrentEvent = theSimpleWaves;
    //   index = 4;
    // }
    // else if ((type == "TaichiEvent") || (type == "General Event (Taichi)") || (type == "Taichi")) {
      
    //   theCurrentEvent = theTaichiEvent;
    //   index = 5;
    // }
    // else if (((type == "SPH")
	// || (type == "Smoothed Particle Hydrodynamics")) || ((type == "General Event (SPH)") || (type == "Digital Twin (SPH)")) || (type == "SPHDigitalTwin") || (type == "theSPH")) {
      
    //   theCurrentEvent = theSPH;
    //   index = 6;
    // }
    // else {
    //   qDebug() << "HydroEventSelection::inputAppDataFromJSON type unknown: " << type;
    //   theCurrentEvent = theCoupledDigitalTwin;
    //   index = 2;
    // //   return false;
    // }

    // eventSelection->setCurrentIndex(index);
    // eventSelection->setCurrentIndex(index);
    
    // invoke inputAppDataFromJSON on new type
    if (theCurrentEvent && !theEvent.isEmpty()) {
      return theCurrentEvent->inputAppDataFromJSON(theEvent);
    }
    
    if (theCurrentEvent == nullptr) qDebug() << "HydroEventSelection::inputAppDataFromJSON theCurrentEvent is nullptr, return false";
    if (theEvent.isEmpty()) qDebug() << "HydroEventSelection::inputAppDataFromJSON theEvent is empty, return false";
    return false;
}

//*********************************************************************************
// Output AppData to JSON
//*********************************************************************************
bool HydroEventSelection::outputAppDataToJSON(QJsonObject &jsonObject)
{
    if (theCurrentEvent == nullptr) {
        qDebug() << "HydroEventSelection::outputAppDataToJSON theCurrentEvent is nullptr, return false";
        return false;
    }
    QJsonArray eventArray;
    QJsonObject singleEventData;
    theCurrentEvent->outputAppDataToJSON(singleEventData);
    eventArray.append(singleEventData);
    jsonObject["Events"]=eventArray;
    return true;
}

//*********************************************************************************
// Copy files
//*********************************************************************************
bool HydroEventSelection::copyFiles(QString &destDir) 
{
    if (theCurrentEvent == nullptr) {
        qDebug() << "HydroEventSelection::copyFiles theCurrentEvent is nullptr, return false";
        return false;
    }
    return  theCurrentEvent->copyFiles(destDir);
}

bool HydroEventSelection::supportsLocalRun()
{
    if (theCurrentEvent == nullptr) {
        qDebug() << "HydroEventSelection::supportsLocalRun theCurrentEvent is nullptr, return false";
        return false;
    }
    return theCurrentEvent->supportsLocalRun();
}

bool HydroEventSelection::outputCitation(QJsonObject &jsonObject) 
{
    if (theCurrentEvent == nullptr) {
        qDebug() << "HydroEventSelection::outputCitation theCurrentEvent is nullptr, return false";
        return false;
    }
    return theCurrentEvent->outputCitation(jsonObject);
}

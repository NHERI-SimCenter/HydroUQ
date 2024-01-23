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

#include "HydroEventSelection.h"
#include <CoupledDigitalTwin.h>
#include <MPM.h>

//*********************************************************************************
// Main Hydro event
//*********************************************************************************
HydroEventSelection::HydroEventSelection(RandomVariablesContainer *theRandomVariableIW,
					 GeneralInformationWidget* generalInfoWidget,
					 QWidget *parent)
    : SimCenterAppWidget(parent),
      theCurrentEvent(0),
      theRandomVariablesContainer(theRandomVariableIW)
{
    // Unused variables
    (void) generalInfoWidget;

    // Create layout
    QVBoxLayout *layout = new QVBoxLayout();

    // The selection of different events
    QHBoxLayout *theSelectionLayout = new QHBoxLayout();
    SectionTitle *label=new SectionTitle();
    label->setMinimumWidth(250);
    label->setText(QString("Event Type"));

    // Combobox for different simulation types
    eventSelection = new QComboBox();
    eventSelection->setObjectName("LoadingTypeCombox");
    // methodSelection = new QComboBox();
    // methodSelection->setObjectName("MethodTypeCombox");

    // Load the different event types
    eventSelection->addItem(tr("General Event (GeoClaw and OpenFOAM)"));
    eventSelection->addItem(tr("Digital Twin (GeoClaw and OpenFOAM)"));
    eventSelection->addItem(tr("Digital Twin (OpenFOAM and OpenSees)"));
    eventSelection->addItem(tr("General Event (MPM)"));        
    eventSelection->addItem(tr("Digital Twin (MPM)"));        
    // eventSelection->addItem(tr("Digital Twin (SPH)"));    
    // Datatips for the different event types
    eventSelection->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    eventSelection->setItemData(0, "Shallow-Water-Equations -> Finite-Volume-Method (GeoClaw -> OpenFOAM) [Multi-CPU]", Qt::ToolTipRole);
    eventSelection->setItemData(1, "Shallow-Water-Equations -> Finite-Volume-Method -> Finite-Element-Analysis (GeoClaw -> OpenFOAM -> OpenSees) [Multi-CPU]", Qt::ToolTipRole);
    eventSelection->setItemData(2, "Finite-Volume-Method <-> Finite-Element-Analysis (OpenFOAM <-> OpenSees) [Multi-CPU]", Qt::ToolTipRole);
    eventSelection->setItemData(3, "Material-Point-Method (ClaymoreUW) [Multi-GPU]", Qt::ToolTipRole);    
    eventSelection->setItemData(4, "Material-Point-Method (ClaymoreUW) [Multi-GPU]", Qt::ToolTipRole);
    // eventSelection->setItemData(5, "Smoothed-Particle-Hydrodynamics (DualSPHysics) [CPU, GPU]", Qt::ToolTipRole);    

    // eventSelection->addItem(tr("General Event"));
    // eventSelection->addItem(tr("Digital Twin"));
    // eventSelection->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    // eventSelection->setItemData(0, "Create a Hazard Event From Scratch In Your Choice of Numerical Method. [Difficulty: Moderate]", Qt::ToolTipRole);
    // eventSelection->setItemData(1, "Start From Pre-Designed Digital-Twins of Experimental Facilities, Case-Histories, and Other Assets. [Difficulty: Easy]", Qt::ToolTipRole);

    // methodSelection->addItem(tr("Shallow-Water-Equations -> Finite-Volume-Method (GeoClaw -> OpenFOAM) [Multi-CPU]"));
    // methodSelection->addItem(tr("Shallow-Water-Equations -> Finite-Volume-Method -> Finite-Element-Analysis (GeoClaw -> OpenFOAM -> OpenSees) [Multi-CPU]"));
    // methodSelection->addItem(tr("Finite-Volume-Method <-> Finite-Element-Analysis (OpenFOAM <-> OpenSees) [Multi-CPU]"));
    // methodSelection->addItem(tr("Material-Point-Method (ClaymoreUW) [Multi-GPU]"));    
    // methodSelection->addItem(tr("Smoothed-Particle-Hydrodynamics (DualSPHysics)"));   
    // // Datatips for the different event types
    // methodSelection->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    // methodSelection->setItemData(0, "Shallow-Water-Equations -> Finite-Volume-Method (GeoClaw -> OpenFOAM) [Multi-CPU]", Qt::ToolTipRole);
    // methodSelection->setItemData(1, "Shallow-Water-Equations -> Finite-Volume-Method -> Finite-Element-Analysis (GeoClaw -> OpenFOAM -> OpenSees) [Multi-CPU]", Qt::ToolTipRole);
    // methodSelection->setItemData(2, "Finite-Volume-Method <-> Finite-Element-Analysis (OpenFOAM <-> OpenSees) [Multi-CPU]", Qt::ToolTipRole);
    // methodSelection->setItemData(3, "Material-Point-Method (ClaymoreUW) [Multi-GPU]", Qt::ToolTipRole);    
    // methodSelection->setItemData(4, "Smoothed-Particle-Hydrodynamics (DualSPHysics) [CPU, GPU]", Qt::ToolTipRole);    

    theSelectionLayout->addWidget(label);
    QSpacerItem *spacer = new QSpacerItem(50,10);
    theSelectionLayout->addItem(spacer);
    theSelectionLayout->addWidget(eventSelection);
    theSelectionLayout->addStretch();
    layout->addLayout(theSelectionLayout);


    // ---
    // Create the stacked widget for the different event-method types
    theStackedWidget = new QStackedWidget();

    // create the individual load widgets & add to stacked widget
    theGeoClawOpenFOAM = new GeoClawOpenFOAM(theRandomVariablesContainer);
    theWaveDigitalFlume = new WaveDigitalFlume(theRandomVariablesContainer);
    theCoupledDigitalTwin = new CoupledDigitalTwin(theRandomVariablesContainer);
    theMPM = new MPM(theRandomVariablesContainer);
    theMPMDigitalTwin = new MPM(theRandomVariablesContainer);
    // theSPH = new MPM(theRandomVariablesContainer);
    // TODO: Fully implement SPH without using MPM

    theStackedWidget->addWidget(theGeoClawOpenFOAM);
    theStackedWidget->addWidget(theWaveDigitalFlume);
    theStackedWidget->addWidget(theCoupledDigitalTwin);
    theStackedWidget->addWidget(theMPM);        
    theStackedWidget->addWidget(theMPMDigitalTwin);        
    // --- 


    // Setup the Layout
    layout->addWidget(theStackedWidget);
    //layout->setMargin(0);
    this->setLayout(layout);
    //theCurrentEvent=theGeoClawOpenFOAM;
    // --
    // Set the default event to select at boot-up. For now, it is MPM
    int indexForMPM = 4;
    theStackedWidget->setCurrentIndex(indexForMPM);
    theStackedWidget->setCurrentIndex(indexForMPM);
    eventSelection->setCurrentIndex(indexForMPM);
    eventSelection->setCurrentIndex(indexForMPM);
    theCurrentEvent = theMPMDigitalTwin;
    theCurrentEvent = theMPMDigitalTwin;

    // Connect signal and slots
    connect(eventSelection, SIGNAL(currentIndexChanged(int)), this, SLOT(eventSelectionChanged(int)));
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
    if (arg1 == 0)
    {
        theStackedWidget->setCurrentIndex(0);
        theCurrentEvent = theGeoClawOpenFOAM;
    }
    else if (arg1 == 1)
    {
        theStackedWidget->setCurrentIndex(1);
        theCurrentEvent = theWaveDigitalFlume;
    }
    else if (arg1 == 2)
    {
        theStackedWidget->setCurrentIndex(2);
        theCurrentEvent = theCoupledDigitalTwin;
    }
    else if (arg1 == 3)
    {
        theStackedWidget->setCurrentIndex(3);
        theCurrentEvent = theMPM;
    }        
    else if (arg1 == 4)
    {
        theStackedWidget->setCurrentIndex(4);
        theCurrentEvent = theMPMDigitalTwin;
    }        
    else
    {
        qDebug() << "ERROR: Hydro-EventSelection selection-type unknown: " << arg1;
    }
}

//*********************************************************************************
// Input data from JSON
//*********************************************************************************
bool HydroEventSelection::inputFromJSON(QJsonObject &jsonObject) {

//    QString type;
    QJsonObject theEvent;

    if (jsonObject.contains("Events"))
    {
        QJsonArray theEvents = jsonObject["Events"].toArray();
        QJsonValue theValue = theEvents.at(0);
        if (theValue.isNull())
        {
            qDebug() << "HydroEventSelection::no Event in Events";
            return false;
        }
        theEvent = theValue.toObject();
    }
    else
    {
        qDebug() << "HydroEventSelection::no Events";
        return false;
    }

    if (theCurrentEvent != 0)
    {
        return theCurrentEvent->inputFromJSON(theEvent);
    }

    return false;
}

//*********************************************************************************
// Output data to JSON
//*********************************************************************************
bool HydroEventSelection::outputToJSON(QJsonObject &jsonObject)
{
    QJsonArray eventArray;
    QJsonObject singleEventData;
    bool result = theCurrentEvent->outputToJSON(singleEventData);
    if (result == true) {
        eventArray.append(singleEventData);
        jsonObject["Events"]=eventArray;
    }

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
          return false;
        }
        theEvent = theValue.toObject();
        if (theEvent.contains("Application"))
        {
            QJsonValue theName = theEvent["Application"];
            type = theName.toString();
            if(theEvent.contains("subtype"))
                subtype = theEvent["subtype"].toString();
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    int index = 3; // Open to MPM for now
    if (((type == "GeneralEvent")
	|| (type == "General Event")) || ((type == "General") || (type == "General Event (GeoClaw and OpenFOAM FVM)"))) {
      
      theCurrentEvent = theGeoClawOpenFOAM;
      index = 0;
    }
    else if (((type == "DigitalTwin")
	|| (type == "Digital Twin")) || (type == "Digital Twin (GeoClaw and OpenFOAM)")) {
      
      theCurrentEvent = theWaveDigitalFlume;
      index = 1;
    }
    else if (((type == "CoupledDigitalTwin")
	|| (type == "Coupled Digital Twin")) || (type == "Digital Twin (OpenFOAM and OpenSees)")) {
      
      theCurrentEvent = theCoupledDigitalTwin;
      index = 2;
    }
    else if (((type == "MPM")
	|| (type == "Material Point Method")) || (type == "General Event (MPM)")) {
      
      theCurrentEvent = theMPM;
      index = 3;
    }
    else if (((type == "MPMDigitalTwin")
	|| (type == "Digital Twin (Material Point Method)")) || (type == "Digital Twin (MPM)")) {
      
      theCurrentEvent = theMPMDigitalTwin;
      index = 4;
    }
    // else if (((type == "SPH")
	// || (type == "Smoothed Particle Hydrodynamics")) || (type == "Digital Twin (SPH)")) {
      
    //   theCurrentEvent = theSPH;
    //   index = 5;
    // }
    eventSelection->setCurrentIndex(index);
    
    eventSelection->setCurrentIndex(index);
    
    // invoke inputAppDataFromJSON on new type
    if (theCurrentEvent != 0 && !theEvent.isEmpty())
    {
      return theCurrentEvent->inputAppDataFromJSON(theEvent);
    }
    
    return true;
}

//*********************************************************************************
// Output AppData to JSON
//*********************************************************************************
bool HydroEventSelection::outputAppDataToJSON(QJsonObject &jsonObject)
{
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
bool HydroEventSelection::copyFiles(QString &destDir) {

    if (theCurrentEvent != 0)
    {
        return  theCurrentEvent->copyFiles(destDir);
    }

    return false;
}

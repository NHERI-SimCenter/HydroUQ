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

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QComboBox>
#include <QSpacerItem>
#include <QPushButton>
#include <QJsonObject>
#include <QJsonArray>
#include <QLabel>
#include <QLineEdit>
#include <QDebug>
#include <QFileDialog>
#include <QPushButton>
#include <sectiontitle.h>
#include <InputWidgetExistingEvent.h>
#include <GeoClawOpenFOAM.h>
//#include <FlumeDigiTwin.h>


HydroEventSelection::HydroEventSelection(RandomVariablesContainer *theRandomVariableIW,
					 GeneralInformationWidget* generalInfoWidget,
					 QWidget *parent)
    : SimCenterAppWidget(parent), theCurrentEvent(0), theRandomVariablesContainer(theRandomVariableIW)
{
    // Create layout
    QVBoxLayout *layout = new QVBoxLayout();


    // The selection of different events
    QHBoxLayout *theSelectionLayout = new QHBoxLayout();
    SectionTitle *label=new SectionTitle();
    label->setMinimumWidth(250);
    label->setText(QString("Simulation type"));

    // Combobox for different simulation types
    eventSelection = new QComboBox();
    eventSelection->setObjectName("LoadingTypeCombox");

    // Load the different event types
    eventSelection->addItem(tr("General"));
    eventSelection->addItem(tr("GeoClaw OpenFOAM"));
//    eventSelection->addItem(tr("SW-OpenFOAM"));
    eventSelection->addItem(tr("Wave Flume Digitwin"));

    // Datatips for the different event types
    eventSelection->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    eventSelection->setItemData(0, "This is a general event from which all other events can be setup", Qt::ToolTipRole);
    eventSelection->setItemData(1, "Coupling of shallow-water solver (GeoClaw) with CFD (OpenFOAM)", Qt::ToolTipRole);
    eventSelection->setItemData(2, "Digital twin of Wave Flume (at OSU)", Qt::ToolTipRole);

    theSelectionLayout->addWidget(label);
    QSpacerItem *spacer = new QSpacerItem(50,10);
    theSelectionLayout->addItem(spacer);
    theSelectionLayout->addWidget(eventSelection);
    theSelectionLayout->addStretch();
    layout->addLayout(theSelectionLayout);

    // Create the stacked widget
    theStackedWidget = new QStackedWidget();

    // create the individual load widgets & add to stacked widget
    theGeoClawOpenFOAM = new GeoClawOpenFOAM(theRandomVariablesContainer);
    theStackedWidget->addWidget(theGeoClawOpenFOAM);
    //theFlumeDigiTwin = new FlumeDigiTwin(theRandomVariablesContainer);
    //theStackedWidget->addWidget(theFlumeDigiTwin);

    // Setup the Layout
    layout->addWidget(theStackedWidget);
    layout->setMargin(0);
    this->setLayout(layout);
    theCurrentEvent=theGeoClawOpenFOAM;

    // Connect signal and slots
    connect(eventSelection, SIGNAL(currentIndexChanged(QString)), this, SLOT(eventSelectionChanged(QString)));
    connect(theGeoClawOpenFOAM, &SimCenterAppWidget::sendErrorMessage, this, [this](QString message) {emit sendErrorMessage(message);});
    connect(theGeoClawOpenFOAM, &SimCenterAppWidget::sendFatalMessage, this, [this](QString message) {emit sendFatalMessage(message);});
    connect(theGeoClawOpenFOAM, &SimCenterAppWidget::sendStatusMessage, this, [this](QString message) {emit sendStatusMessage(message);});

}


HydroEventSelection::~HydroEventSelection()
{

}


// Output data to JSON
bool HydroEventSelection::outputToJSON(QJsonObject &jsonObject)
{
    QJsonArray eventArray;
    QJsonObject singleEventData;
    theCurrentEvent->outputToJSON(singleEventData);
    eventArray.append(singleEventData);
    jsonObject["Events"]=eventArray;

    return true;
}


// Input data from JSON
bool HydroEventSelection::inputFromJSON(QJsonObject &jsonObject) {

    QString type;
    QJsonObject theEvent;

    if (jsonObject.contains("Events")) {
        QJsonArray theEvents = jsonObject["Events"].toArray();
        QJsonValue theValue = theEvents.at(0);
        if (theValue.isNull()) {
            qDebug() << "HydroEventSelection::no Event in Events";
            return false;
        }
        theEvent = theValue.toObject();

    } else {
        qDebug() << "HydroEventSelection::no Events";
        return false;
    }

    if (theCurrentEvent != 0) {
        return theCurrentEvent->inputFromJSON(theEvent);
    }

    return false;
}

// If Event selection is changed
void HydroEventSelection::eventSelectionChanged(const QString &arg1)
{
    // switch stacked widgets depending on text
    // note type output in json and name in pull down are not the same and hence the ||
    if (arg1 == "GeoClaw OpenFOAM")
    {
        theStackedWidget->setCurrentIndex(0);
        theCurrentEvent = theGeoClawOpenFOAM;
    }
    else
    {
        qDebug() << "ERROR: HydroEventSelection selection-type unknown: " << arg1;
    }
}

bool HydroEventSelection::outputAppDataToJSON(QJsonObject &jsonObject)
{
    QJsonArray eventArray;
    QJsonObject singleEventData;
    theCurrentEvent->outputAppDataToJSON(singleEventData);
    eventArray.append(singleEventData);
    jsonObject["Events"]=eventArray;
    return true;
}


bool HydroEventSelection::inputAppDataFromJSON(QJsonObject &jsonObject)
{
    QJsonObject theEvent;
    QString type;
    QString subtype;

    // from Events get the single event

    if (jsonObject.contains("Events")) {
        QJsonArray theEvents = jsonObject["Events"].toArray();
        QJsonValue theValue = theEvents.at(0);
        if (theValue.isNull()) {
          return false;
        }
        theEvent = theValue.toObject();
        if (theEvent.contains("Application")) {
            QJsonValue theName = theEvent["Application"];
            type = theName.toString();
            if(theEvent.contains("subtype"))
                subtype = theEvent["subtype"].toString();
        } else
            return false;
    } else
        return false;


    int index = 0;
    if ((type == QString("Existing Events")) ||
	(type == QString("Existing SimCenter Events")) ||
	(type == QString("ExistingSimCenterEvents"))) {
        index = 4;
    } else if ((type == QString("Existing PEER Records")) ||
               (type == QString("ExistingPEER_Events"))  ||
               (type == QString("ExistingPEER_Records"))) {
        if(!subtype.isEmpty() && subtype == "PEER NGA Records")
            index = 1;
        else
            index = 3;
  //  } else if (type == QString("Hazard Based Event")) {
  //      index = 3;
    } else if (type == QString("Site Response") ||
               type == QString("SiteResponse")) {
        index = 2;
    } else if (type == QString("Stochastic Ground Motion Model") ||
	       type == QString("Stochastic Ground Motion") ||
	       type == QString("StochasticGroundMotion") ||
               type == QString("StochasticMotion")) {
        index = 0;
   // } else if ((type == QString("User Application")) ||
   //            (type == QString("UserDefinedApplication"))) {
   //     index = 6;
    } else {
        return false;
    }

    eventSelection->setCurrentIndex(index);

    // invoke inputAppDataFromJSON on new type
    if (theCurrentEvent != 0 && !theEvent.isEmpty()) {
        return theCurrentEvent->inputAppDataFromJSON(theEvent);
    }
}

bool HydroEventSelection::copyFiles(QString &destDir) {

    if (theCurrentEvent != 0) {
        return  theCurrentEvent->copyFiles(destDir);
    }

    return false;
}

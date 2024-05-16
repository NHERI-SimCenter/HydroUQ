// Written: fmckenna

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
// Modified: JustinBonus

#include "HydroEDP_Selection.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QStackedWidget>
#include <QComboBox>


#include <QPushButton>
#include <QJsonObject>
#include <QJsonArray>

#include <QLabel>
#include <QLineEdit>
#include <QDebug>
#include <QFileDialog>
#include <QPushButton>
#include <SectionTitle.h>


#include <StandardEDP.h>
#include <StandardHydroEDP.h>
#include <StandardTsunamiEDP.h>
#include <StandardStormSurgeEDP.h>
#include <UserDefinedEDP.h>

HydroEDP_Selection::HydroEDP_Selection(QWidget *parent)
    : SimCenterAppWidget(parent), theCurrentEDP(0)
{
    QVBoxLayout *layout = new QVBoxLayout();

    //
    // the selection part
    //

    QHBoxLayout *theSelectionLayout = new QHBoxLayout();
    SectionTitle *label = new SectionTitle();
    label->setText(QString("Engineering Demand Parameters Generator"));
    label->setMinimumWidth(250);
    
    edpSelection = new QComboBox();
    edpSelection->addItem(tr("Standard Hydro"));
    edpSelection->addItem(tr("Standard Tsunami"));
    edpSelection->addItem(tr("Standard Storm Surge"));
    edpSelection->addItem(tr("User Defined"));
    edpSelection->addItem(tr("Standard"));
    edpSelection->setObjectName("EDPSelectionComboBox");

    //    edpSelection->setItemData(1, "A Seismic event using Seismic Hazard Analysis and Record Selection/Scaling", Qt::ToolTipRole);
    edpSelection->setItemData(0, "A general hydrodynamic event with measurement of common engineering demand parameters (EDPs).", Qt::ToolTipRole);
    edpSelection->setItemData(1, "A tsunami event with measurement of established tsunami demand parameters (EDPs) for coastal structures (e.g. residential, commercial).", Qt::ToolTipRole);
    edpSelection->setItemData(2, "A hurricane storm surge event with measurement of established hydrodynamic storm surge demand parameters (EDPs) for affected structures (e.g. residential, commercial).", Qt::ToolTipRole);
    edpSelection->setItemData(3, "User-defined selection of engineering demand parameters (EDPs) for custom workflows.", Qt::ToolTipRole);
    edpSelection->setItemData(4, "A general event with measurement of common (earthquake) engineering demand parameters (EDPs).", Qt::ToolTipRole);
    theSelectionLayout->addWidget(label);
    theSelectionLayout->addWidget(edpSelection);
    theSelectionLayout->addStretch();
    layout->addLayout(theSelectionLayout);

    //
    // create the stacked widget
    //

    theStackedWidget = new QStackedWidget();

    //
    // create the individual widgets add to stacked widget
    //

    theStandardHydroEDPs = new StandardHydroEDP();
    theStandardTsunamiEDPs = new StandardTsunamiEDP();
    theStandardStormSurgeEDPs = new StandardStormSurgeEDP();
    theUserDefinedEDPs = new UserDefinedEDP();
    theStandardEDPs = new StandardEDP();
    
    theStackedWidget->addWidget(theStandardHydroEDPs);
    theStackedWidget->addWidget(theStandardTsunamiEDPs);
    theStackedWidget->addWidget(theStandardStormSurgeEDPs);
    theStackedWidget->addWidget(theUserDefinedEDPs);
    theStackedWidget->addWidget(theStandardEDPs);
    theStackedWidget->setCurrentIndex(0);
    layout->addWidget(theStackedWidget);
    this->setLayout(layout);

    theCurrentEDP=theStandardEDPs;

    connect(edpSelection, SIGNAL(currentIndexChanged(QString)), this,
            SLOT(edpSelectionChanged(QString)));
}

HydroEDP_Selection::~HydroEDP_Selection()
{

}


bool
HydroEDP_Selection::outputToJSON(QJsonObject &jsonObject)
{
    theCurrentEDP->outputToJSON(jsonObject);
    return true;
}


bool
HydroEDP_Selection::inputFromJSON(QJsonObject &jsonObject) {

    if (theCurrentEDP != 0) {
        return theCurrentEDP->inputFromJSON(jsonObject);
    }

    return false;
}

void HydroEDP_Selection::edpSelectionChanged(const QString &arg1)
{
    //
    // switch stacked widgets depending on text
    // note type output in json and name in pull down are not the same and hence the ||
    //

    if (arg1 == "Standard Hydro" || arg1 == "StandardHydroEDP") {
        theStackedWidget->setCurrentIndex(0);
        theCurrentEDP = theStandardHydroEDPs;
    }

    else if(arg1 == "Standard Tsunami" || arg1 == "StandardTsunamiEDP") {
        theStackedWidget->setCurrentIndex(1);
        theCurrentEDP = theStandardTsunamiEDPs;
    }

    else if(arg1 == "Standard Storm Surge" || arg1 == "StandardStormSurgeEDP") {
        theStackedWidget->setCurrentIndex(2);
        theCurrentEDP = theStandardStormSurgeEDPs;
    }
    else if(arg1 == "User Defined" || arg1 == "UserDefinedEDP") {
        theStackedWidget->setCurrentIndex(3);
        theCurrentEDP = theUserDefinedEDPs;
    }
    else if (arg1 == "Standard" || arg1 == "StandardEDP") {
        theStackedWidget->setCurrentIndex(4);
        theCurrentEDP = theStandardEDPs;
    }
    else {
        qDebug() << "ERROR .. HydroEDP_Selection selection .. type unknown: " << arg1;
    }


}

bool
HydroEDP_Selection::outputAppDataToJSON(QJsonObject &jsonObject)
{
    theCurrentEDP->outputAppDataToJSON(jsonObject);
    return true;
}


bool
HydroEDP_Selection::inputAppDataFromJSON(QJsonObject &jsonObject)
{

    // get name from "Application" key

    QString type;
    if (jsonObject.contains("Application")) {
        QJsonValue theName = jsonObject["Application"];
        type = theName.toString();
    } else {
        errorMessage("HydroEDP_Selection - no Application key found");
        return false;
    }


    // based on application name value set edp type
    int index = 0;
    if ((type == QString("Standard Hydro EDPs")) ||
            (type == QString("StandardHydroEDP"))) {
        index = 0;
    } else if ((type == QString("StandardTsunamiEDP")) ||
               (type == QString("Standard Tsunami EDPs"))) {
        index = 1;
    } else if ((type == QString("StandardStormSurgeEDP")) ||
               (type == QString("Standard Storm Surge EDPs"))) {
        index = 2;
    } else if ((type == QString("UserDefinedEDP")) ||
               (type == QString("User Defined EDPs"))) {
        index = 3;
    }  else if ((type == QString("StandardEDP")) ||
                (type == QString("Standard EDPs"))) {
        index = 4;
    }
    else {
        errorMessage("HydroEDP_Selection - no valid type found");
        return false;
    }

    edpSelection->setCurrentIndex(index);

    // invoke inputAppDataFromJSON on new type

    if (theCurrentEDP != 0) {
        return theCurrentEDP->inputAppDataFromJSON(jsonObject);
    }

    return false;
}

bool
HydroEDP_Selection::copyFiles(QString &destDir) {

    if (theCurrentEDP != 0) {
        return  theCurrentEDP->copyFiles(destDir);
    }

    return false;
}

void
HydroEDP_Selection::clear(void) {

    if (theCurrentEDP != 0) {
        return  theCurrentEDP->clear();
    }
}
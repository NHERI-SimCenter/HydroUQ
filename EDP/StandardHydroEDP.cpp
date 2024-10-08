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

#include "EDP/StandardHydroEDP.h"
// #include <QJsonObject>
// #include <QLabel>

#include <RandomVariablesContainer.h>
// #include <InputWidgetParameters.h>
#include "SimCenterPreferences.h"
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QProcess>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

#include <QStackedWidget>
#include <QComboBox>

#include <QLineEdit>

#include <cstring>
#include <vector>
// #include "UserDefinedEDP.h"
#include <EDP.h>

#include <QPushButton>
#include <QScrollArea>
#include <QJsonArray>
#include <QJsonObject>
#include <QLabel>
#include <QLineEdit>
#include <QDebug>
#include <QFileDialog>
#include <QPushButton>
#include <SectionTitle.h>
#include <QFileInfo>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;
#include <QGridLayout>

StandardHydroEDP::StandardHydroEDP(QWidget *parent)
    : SimCenterAppWidget(parent)
{
    //
    // Adapted from 'UserDefinedEDP.cpp'. Borrowed for its GUI, as others are all grey/empty
    // However, we disable most functionality, we don't want users messing up the preset EDP set
    // Users may disable EDPs, but not add or remove them
    // They get to bind EDPs to preset sensors in the Event (EVT) tab for MPM, 
    // (OpenFOAM and GeoClaw in-progress)
    //

    QVBoxLayout *layout = new QVBoxLayout();


   // label1->setText("Processing Script");

   // QHBoxLayout *fileName1Layout = new QHBoxLayout();
    QGridLayout *scriptLayout = new QGridLayout();

    // add stuff to enter Additional Input
    QLabel *labelAI = new QLabel("Additional Input / Recorder Script");
    additionalInputLE = new QLineEdit;
    // Set the background text to (Optional)
    additionalInputLE->setPlaceholderText("(Optional. Check-in HydroUQ/Examples/EDP for example additional input scripts, e.g. OpenSees recorder tcl scripts.)");

    QFileInfo fileAI(SimCenterPreferences::getInstance()->getAppDir() + QDir::separator() + "Examples" + QDir::separator() + "EDP" + QDir::separator() + "StandardHydroEDP_FrameRecorder.tcl");
    additionalInputLE->setText(fileAI.absoluteFilePath());
    additionalInputLE->setReadOnly(true);
    additionalInputLE->setToolTip("This file is used to set-up the recorders / sensors / probes in the output of the structural response simulation, FEM, after the UQ workflow completes. Often it is a tcl script that contains the OpenSees recorder commands.");

    QPushButton *chooseAdditionalInputButton = new QPushButton();
    chooseAdditionalInputButton->setText(tr("Choose"));
    connect(chooseAdditionalInputButton,SIGNAL(clicked()),this,SLOT(chooseAdditionalInput()));
    scriptLayout->addWidget(labelAI,0,0);
    scriptLayout->addWidget(additionalInputLE,0,2);
    scriptLayout->addWidget(chooseAdditionalInputButton, 0, 4);

    // add stuff to enter processing script
    QLabel *labelPS = new QLabel("Post-Processing / EDP Extractor Script");
    processingScriptLE = new QLineEdit;
    // Set the background text to (Optional)
    processingScriptLE->setPlaceholderText("(Required. Check-in HydroUQ/Examples/EDP for example post-processing scripts, e.g. OpenSees post-processing tcl scripts.)");

    QFileInfo fileLE(SimCenterPreferences::getInstance()->getAppDir() + QDir::separator() + "Examples" + QDir::separator() + "EDP" + QDir::separator() + "StandardHydroEDP_FramePost.tcl");
    processingScriptLE->setText(fileLE.absoluteFilePath());
    processingScriptLE->setReadOnly(true);
    processingScriptLE->setToolTip("This script is used to process the output of the structural response simulation, FEM, to extract the Engineering Demand Parameters (EDPs) into a file for analysis, results.out, after the UQ workflow completes.");


    QPushButton *chooseProcessingScriptButton = new QPushButton();
    chooseProcessingScriptButton->setText(tr("Choose"));
    connect(chooseProcessingScriptButton,SIGNAL(clicked()),this,SLOT(chooseProcessingScript()));
    scriptLayout->addWidget(labelPS,1,0);
    scriptLayout->addWidget(processingScriptLE,1,2);
    scriptLayout->addWidget(chooseProcessingScriptButton, 1, 4);

    QSpacerItem *spacer3 = new QSpacerItem(30,10);
    QSpacerItem *spacer4 = new QSpacerItem(10,10);
    scriptLayout->addItem(spacer3,0,1);
    scriptLayout->addItem(spacer4,0,3);
    scriptLayout->setColumnStretch(5,1);
    scriptLayout->setColumnStretch(2,1);

    scriptLayout->setHorizontalSpacing(5);
    scriptLayout->setVerticalSpacing(5);

    layout->addLayout(scriptLayout);
    QSpacerItem *spacer = new QSpacerItem(20,10);
    layout->addSpacerItem(spacer);


    //layout->setColumnStretch(3,1);

    // title & add button
    QHBoxLayout *titleLayout = new QHBoxLayout();

    SectionTitle *title=new SectionTitle();
    title->setText(tr("Response Parameters"));
    title->setMinimumWidth(250);
    QSpacerItem *spacer1 = new QSpacerItem(50,10);
    QSpacerItem *spacer2 = new QSpacerItem(20,10);

    QPushButton *addEDP = new QPushButton();
    addEDP->setMinimumWidth(75);
    addEDP->setMaximumWidth(75);
    addEDP->setText(tr("Add"));
    connect(addEDP,SIGNAL(clicked()),this,SLOT(addEDP()));

    titleLayout->addWidget(title);
    titleLayout->addItem(spacer1);
    titleLayout->addWidget(addEDP);
    titleLayout->addItem(spacer2);

    
    QPushButton *removeEDP = new QPushButton();
    removeEDP->setMinimumWidth(75);
    removeEDP->setMaximumWidth(75);
    removeEDP->setText(tr("Remove"));
    connect(removeEDP,SIGNAL(clicked()),this,SLOT(removeEDP()));
    titleLayout->addWidget(removeEDP);


    titleLayout->addStretch();

    //layout->addWidget(titleLayout,1,0,3,0);
    layout->addLayout(titleLayout);

    QScrollArea *sa = new QScrollArea;
    sa->setWidgetResizable(true);
    sa->setLineWidth(0);
    sa->setFrameShape(QFrame::NoFrame);

    edp = new QFrame();
    edp->setFrameShape(QFrame::NoFrame);
    edp->setLineWidth(0);

    edpLayout = new QVBoxLayout;

    //setLayout(layout);
    edp->setLayout(edpLayout);
    edpLayout->addStretch();
    // make QStrings for EDP input

    QString edp1 = "peak-floor-displacement_1_1";
    // QString edp2 = "peak-interstory-drift";
    QString edp3 = "peak-floor-acceleration_1_1";
    // QString edp4 = "root-mean-square-acceleration";
    QString edp5 = "peak-floor-force_1_1"; // max force on the structure or component
    QString edp6 = "peak-floor-pressure_1_1"; // max pressure  on the structure or component

    // QString edp1 = "Disp";
    // QString edp2 = "RMSA";
    // QString edp3 = "Force";
    // QString edp4 = "Pressure";

    // QString edp7  = "total_floor_impulse"; // total impulse on the structure or component, integral of force-time series
    // QString edp10 = "max_interstory_drift"; // interstory drift, i.e. max relative displacement of floor n+1 vs floor n...
    // QString edp11 = "max_roof_drift"; // roof drift, i.e. max relative displacement of top floor to ground

    // QString edp1  = "max_force"; // max force on the structure or component
    // QString edp2  = "max_pressure"; // max pressure  on the structure or component
    // QString edp3  = "total_impulse"; // total impulse on the structure or component, integral of force-time series
    // QString edp10 = "max_interstory_drift"; // interstory drift, i.e. max relative displacement of floor n+1 vs floor n...
    // QString edp11 = "max_roof_drift"; // roof drift, i.e. max relative displacement of top floor to ground
    // QString edp4  = "max_wave_velocity"; // max wave velocity at a characteristic location near the structure
    // QString edp5  = "max_wave_height"; // max wave elevation at a characteristic location near the structure
    // QString edp6  = "average_wave_velocity"; // average wave elevation at a characteristic location near the structure
    // QString edp7  = "average_wave_height"; // average wave elevation at a characteristic location near the structure
    // QString edp8  = "total_wave_duration"; // wave duration based on exceeding a threshold of some variable at a characteristic location near the structure
    // QString edp9  = "total_wave_momentum_flux"; // wave momentum flux based at a characteristic location near the structure
    // QString edp12 = "max_abs_acceleration"; // absolute maximum of acceleration
    // QString edp13 = "max_rel_disp"; // floor relative displacement

    this->addEDP(edp1); 
    // this->addEDP(edp2); 
    this->addEDP(edp3); 
    // this->addEDP(edp4);
    this->addEDP(edp5);
    this->addEDP(edp6);
    // this->addEDP(edp7);
    // this->addEDP(edp8); 
    // this->addEDP(edp10); 
    // this->addEDP(edp11); 

    sa->setWidget(edp);
    layout->addWidget(sa);
    //layout->addStretch(1.0);

    layout->setSpacing(0);
    //layout->setMargin(0);

    this->setLayout(layout);

    /*
    // QWidget *dummyR = new QWidget();
    // layout->addWidget(dummyR,3,0);
    // layout->setRowStretch(4,1);
    // this->setLayout(layout);
    */

}

StandardHydroEDP::~StandardHydroEDP()
{

}


void
StandardHydroEDP::clear(void)
{
    //
    // from UserDefinedEDP.cpp, not needed for now
    //

    additionalInputLE->setText("");
    processingScriptLE->setText("");

    int numEDPs = theEDPs.size();
    for (int i = numEDPs-1; i >= 0; i--) {
        EDP *theEDP = theEDPs.at(i);
        theEDP->close();
        edpLayout->removeWidget(theEDP);
        theEDPs.remove(i);
        delete theEDP;
    }
}



bool
StandardHydroEDP::outputToJSON(QJsonObject &jsonObject)
{
    // just need to send the class type here.. type needed in object in case user screws up
    jsonObject["type"]="StandardHydroEDP";

    
    // 
    // From UserDefinedEDP.cpp
    //


    QString fileName = processingScriptLE->text();
    if (!fileName.isEmpty()) {
        QFileInfo fileInfoPS(fileName);
        if (fileInfoPS.exists()) {

            jsonObject["fileNamePS"] = fileInfoPS.fileName();
            jsonObject["filePathPS"] = fileInfoPS.path();

        } else {
            this->errorMessage("StandardHydroEDP :: Processing script does not exist");
        }
    } else {
       this->errorMessage("StandardHydroEDP :: no processing script");
    }

    fileName = additionalInputLE->text();
    if (!fileName.isEmpty()) {
        QFileInfo fileInfoPS(fileName);
        if (fileInfoPS.exists()) {

            jsonObject["fileNameAI"] = fileInfoPS.fileName();
            jsonObject["filePathAI"] = fileInfoPS.path();

        } else {
            this->errorMessage("StandardHydroEDP :: additional script does not exist");
        }
    } else {
       this->errorMessage("StandardHydroEDP :: no additional script");
    }


    QJsonArray edpArray;
    int numEDPs = theEDPs.size();
    for (int i = 0; i < numEDPs; i++) {
        QJsonObject edpObject;
        EDP *theEDP = theEDPs.at(i);
        theEDP->outputToJSON(edpObject);
        edpArray.append(edpObject);
    }
    jsonObject["EDP"]=edpArray;

    return true;
}


bool
StandardHydroEDP::inputFromJSON(QJsonObject &jsonObject)
{
    //
    // From StandardEarthquakeEDP.cpp
    //

    // Q_UNUSED(jsonObject);
    // return true;

    // ---------------------------------------------------
    //  From UserDefinedEDP.cpp
    // ---------------------------------------------------
    //
    // retrieve filename and path, set the QLIne Edit
    //

    QString fileName;
    QString filePath;

    if (jsonObject.contains("fileNamePS")) {
        QJsonValue theName = jsonObject["fileNamePS"];
        fileName = theName.toString();

        if (jsonObject.contains("filePathPS")) {
            QJsonValue theName = jsonObject["filePathPS"];
            filePath = theName.toString();

            processingScriptLE->setText(QDir(filePath).filePath(fileName));

        } else {
           this->errorMessage("StandardHydroEDP ::inputFromJSON  no filefilePathPS exists");
        }

    } else {
        this->errorMessage("StandardHydroEDP ::inputFromJSON  no fileNamePS exists");
    }

    if (jsonObject.contains("fileNameAI")) {
        QJsonValue theName = jsonObject["fileNameAI"];
        fileName = theName.toString();

        if (jsonObject.contains("filePathAI")) {
            QJsonValue theName = jsonObject["filePathAI"];
            filePath = theName.toString();

            additionalInputLE->setText(QDir(filePath).filePath(fileName));

        } else {
         this->errorMessage("StandardHydroEDP ::inputFromJSON  no filePathAI exists");
        }

    } else {
        this->errorMessage("StandardHydroEDP ::inputFromJSON  no fileNameAI exists");
    }


    if (jsonObject.contains("EDP")) {
        QJsonArray edpArray = jsonObject["EDP"].toArray();

        for (int i=0; i<edpArray.size(); i++) {
            QJsonObject edpData = edpArray.at(i).toObject();
            EDP *theEDP = new EDP();
            theEDPs.append(theEDP);
            theEDP->inputFromJSON(edpData);
            edpLayout->insertWidget(edpLayout->count()-1, theEDP);

            connect(theEDP, SIGNAL(removeEDP(EDP*)), this, SLOT(removeEDP(EDP*)));
        }
    }

    return true;


}


bool
StandardHydroEDP::outputAppDataToJSON(QJsonObject &jsonObject) {

    //
    // per API, need to add name of application to be called in Application
    // and all data to be used in ApplicationData
    //

    jsonObject["Application"] = "StandardHydroEDP";
    QJsonObject dataObj;
    jsonObject["ApplicationData"] = dataObj;

    return true;
}
bool
StandardHydroEDP::inputAppDataFromJSON(QJsonObject &jsonObject) {
    // Q_UNUSED(jsonObject);
    // return true;
    
    // ---------------------------------------------------
    //  From UserDefinedEDP.cpp
    // ---------------------------------------------------
    Q_UNUSED(jsonObject);

    //
    // from ApplicationData
    //

    this->clear();
    return true;
}


bool
StandardHydroEDP::copyFiles(QString &dirName) {
    // Q_UNUSED(dirName);
    // return true;

    // ---------------------------------------------------
    //  From UserDefinedEDP.cpp
    // ---------------------------------------------------
     QString filename = processingScriptLE->text();
     if (!filename.isEmpty()) {

         if (this->copyFile(filename, dirName) ==  false) {
             this->errorMessage(QString("ERROR: copyFiles: failed to copy") + filename);
             return false;
         }
     }
    else {
        this->errorMessage(QString("ERROR: copyFiles: failed to copy post-procesing script in EDP tab:") + filename);
        return false;
    }

     filename = additionalInputLE->text();
     if (!filename.isEmpty()) {

         if (this->copyFile(filename, dirName) ==  false) {
             this->errorMessage(QString("ERROR: copyFiles: failed to copy additional input script in EDP tab:") + filename);
             return false;
         }
     }

     return true;
}



bool
StandardHydroEDP::setProcessingScript(QString filename){
    
    // ---------------------------------------------------
    //  From UserDefinedEDP.cpp
    // ---------------------------------------------------

    // set file name & entry in qLine edit
    //filenameProcessingScript = name;

    // remove old EDP
    int numEDPs = theEDPs.size();
    for (int i = numEDPs-1; i >= 0; i--) {
        EDP *theEDP = theEDPs.at(i);
        theEDP->close();
        edpLayout->removeWidget(theEDP);
        theEDPs.remove(i);
        delete theEDP;
    }

    // set filename
    processingScriptLE->setText(filename);

    // process file looking for line with EDPs
    std::ifstream in_file(filename.toStdString());
    unsigned int max_iters = 100;
    unsigned int count = 0;
    bool found_line = false;
    std::string current_line;
    std::string EDP_array("EDPs");
    std::string token;
    
    // Iterate over file until line containing EDPs is found or maximum number of iterations
    // is reached
    while (!found_line && count < max_iters) {
        // Get current line and search for EDP array
        std::getline(in_file, current_line);
        std::size_t found_EDPs = current_line.find(EDP_array);

        // If EDP array found, iterate over it to find EDPs and add them
        if (found_EDPs != std::string::npos) {
            std::stringstream line_to_check(current_line);
            unsigned int counter = 0;
            while (std::getline(line_to_check, token, '\'')) {
                counter++;
                // Since names are between two "'" characters, only add token after second occurance
                if (counter == 2) {
                    QString name = QString::fromStdString(token);
                    this->addEDP(name);
                    counter = 0;
                }
            }
            found_line = true;
        }
        count++;
    }

    // close file
    in_file.close();

    if(!found_line)
        return false;

    return true;
}

void
StandardHydroEDP::chooseProcessingScript() {
    // ---------------------------------------------------
    //  From UserDefinedEDP.cpp
    // ---------------------------------------------------
    QString fileName=QFileDialog::getOpenFileName(this,tr("Open File"),"C://", "All files (*.*)");
    this->setProcessingScript(fileName);
}


void
StandardHydroEDP::setAdditionalInput(QString filename) {
    additionalInputLE->setText(filename);
    return;
}

void
StandardHydroEDP::chooseAdditionalInput(void) {
    QString fileName=QFileDialog::getOpenFileName(this,tr("Open File"),"C://", "All files (*.*)");
    this->setAdditionalInput(fileName);
    return;
}


 void
 StandardHydroEDP::addEDP(void)
 {
    // ---------------------------------------------------
    //  From UserDefinedEDP.cpp
    // ---------------------------------------------------
    EDP *theEDP = new EDP();
    theEDPs.append(theEDP);
    // edpLayout->addWidget(theEDP);
    edpLayout->insertWidget(edpLayout->count()-1, theEDP);

    connect(theEDP, SIGNAL(removeEDP(EDP*)), this, SLOT(removeEDP(EDP*)));
    return;
 }


 void
 StandardHydroEDP::addEDP(QString &name)
 {
    // Q_UNUSED(name);
    // return;
    // ---------------------------------------------------
    //  From UserDefinedEDP.cpp
    // ---------------------------------------------------
     EDP *theEDP = new EDP(&name, NULL);
     theEDPs.append(theEDP);
     edpLayout->insertWidget(edpLayout->count()-1, theEDP);

     // should not really allow user to remove these ones .. but then should not have a remove button! .. need to change script
     connect(theEDP, SIGNAL(removeEDP(EDP*)), this, SLOT(removeEDP(EDP*)));
 }


void StandardHydroEDP::removeEDP(EDP *theEDPtoRemove)
{
    // Find the ones selected & remove them
    int numEDPs = theEDPs.size();

    for (int i = numEDPs-1; i >= 0; i--) {
        EDP *theEDP = theEDPs.at(i);
        if (theEDP == theEDPtoRemove) {
            theEDP->close();
            edpLayout->removeWidget(theEDP);
            theEDPs.remove(i);
            //theEDP->setParent(0);
            delete theEDP;
            i=-1;
        }
    }

    // disconnect(theEDPtoRemove, SIGNAL(removeEDP(EDP*)), this, SLOT(removeEDP(EDP*))); // JB, maybe not needed
}

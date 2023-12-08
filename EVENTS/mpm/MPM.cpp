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

// Written: fmk

#include "MPM.h"
#include <QScrollArea>
#include <QLineEdit>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QJsonObject>

#include <SettingsMPM.h>
#include <ParticlesMPM.h>
#include <BoundariesMPM.h>
#include <SensorsMPM.h>
#include <OutputsMPM.h>

MPM::MPM(QWidget *parent)
    : SimCenterAppWidget(parent)
{
    int windowWidth = 800;

    QWidget     *mainGroup = new QWidget();
    QGridLayout *mainLayout = new QGridLayout();

    QLabel *generalDescriptionLabel = new QLabel("Digital Twins of NHERI Experimental Facilities and NSF Funded: "
                                                 "\n This page defines the event (EVT) to simulate in HydroUQ."
                                                 "\n Digital twins of pre-built and validated scaled flume facilities help set boundary and initial conditions"
                                                 "\n Available wave flume twins: Hinsdale Large Wave Flume (OSU LWF), Hinsdale Directional Wave Basin (OSU DWB), Wind-Air-Sea Interaction Facility (UW WASIRF), Waseda University's Tsunami Wave Basin (WU TWB)"
                                                 "\n Available wind-wave flume twins: Hinsdale Large Wave Flume (OSU LWF), Wind-Air-Sea Interaction Facility (UW WASIRF)"
                                                 "\n Available lahar flume twins: U.S. Geological Survey's Debris Flow Flume (USGS DFF)"						 
                                                 "\n ClaymoreUW, a high-performance 3D Material Point Method code, is the engine behind this page's functionality."
                                                 "\n Step 1.) Set general simulation Settings. E.g., the gravity vector."						 
                                                 "\n Step 2.) Define Bodies to model with initial conditions in the simulation."
                                                 "\n Step 3.) Select Flume Facility, Wave Generator, Rigid Structures, Walls, and Custom boundary conditions."
                                                 "\n Step 4.) Specify where to place Sensors (e.g. wave-gauges, piezometers) and what they measure."
                                                 "\n Step 5.) Choose Output settings for simulation results."
                                                 "\n Step 6.) If all side-bar pages are complete, click [RUN at DesignSafe] (bottom of the app) to simulate your Event.");


    mainLayout->addWidget(generalDescriptionLabel, 0, 0);

    QTabWidget *theTabWidget = new QTabWidget();
    mpmSettings = new SettingsMPM();
    theTabWidget->addTab(mpmSettings, "Settings");
    mpmParticles = new ParticlesMPM();
    theTabWidget->addTab(mpmParticles, "Bodies");
    mpmBoundaries = new BoundariesMPM();
    theTabWidget->addTab(mpmBoundaries, "Boundaries");
    mpmSensors = new SensorsMPM();
    theTabWidget->addTab(mpmSensors, "Sensors");
    mpmOutputs = new OutputsMPM();
    theTabWidget->addTab(mpmOutputs, "Outputs");    
    
    mainLayout->addWidget(theTabWidget, 1, 0);
    
    mainGroup->setLayout(mainLayout);
    mainGroup->setMaximumWidth(windowWidth);
    
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setLineWidth(1);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setWidget(mainGroup);
    scrollArea->setMaximumWidth(windowWidth + 25);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(scrollArea);
    this->setLayout(layout);
}


MPM::~MPM()
{

}


void MPM::clear(void)
{

}


bool MPM::inputFromJSON(QJsonObject &jsonObject)
{
  this->clear();
  
  /*
    if (jsonObject.contains("buildingWidth")) {
    QJsonValue theValue = jsonObject["buildingWidth"];
    QString selection = theValue.toString();
    buildingWidthWidget->setText(selection);
    } else
    return false;
  */
  
  mpmSettings->inputFromJSON(jsonObject);
  mpmParticles->inputFromJSON(jsonObject);
  mpmBoundaries->inputFromJSON(jsonObject);
  mpmSensors->inputFromJSON(jsonObject);
  mpmOutputs->inputFromJSON(jsonObject);
  
  return true;
}

bool MPM::outputToJSON(QJsonObject &jsonObject)
{
  jsonObject["EventClassification"]="Hydro";
  jsonObject["Application"] = "MPM";
    
  mpmSettings->outputToJSON(jsonObject);
  mpmParticles->outputToJSON(jsonObject);
  mpmBoundaries->outputToJSON(jsonObject);
  mpmSensors->outputToJSON(jsonObject);
  mpmOutputs->outputToJSON(jsonObject);
  
  /*
    if (jsonObject.contains("buildingWidth")) {
    QJsonValue theValue = jsonObject["buildingWidth"];
    QString selection = theValue.toString();
    buildingWidthWidget->setText(selection);
    } else
    return false;
  */
  
  return true;
}

bool MPM::outputAppDataToJSON(QJsonObject &jsonObject) {

    //
    // per API, need to add name of application to be called in AppLication
    // and all data to be used in ApplicationDate
    //

    jsonObject["EventClassification"]="Hydro";
    jsonObject["Application"] = "MPM";
    QJsonObject dataObj;
    jsonObject["ApplicationData"] = dataObj;

    return true;
}
bool MPM::inputAppDataFromJSON(QJsonObject &jsonObject) {

    Q_UNUSED(jsonObject);
    return true;
}


bool MPM::copyFiles(QString &destDir) {
  
  if (mpmParticles->copyFiles(destDir) == false)
    return false;
  if (mpmBoundaries->copyFiles(destDir) == false)
    return false;
  // if (mpmSensors->copyFiles(destDir) == false)
  //   return false;    

  return true;
 }


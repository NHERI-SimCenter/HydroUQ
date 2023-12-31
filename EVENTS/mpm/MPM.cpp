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
#include <QJsonArray>
#include <QSvgWidget>
#include <QString>
#include <QIcon>

#include <SettingsMPM.h>
#include <ParticlesMPM.h>
#include <BoundariesMPM.h>
#include <SensorsMPM.h>
#include <OutputsMPM.h>

MPM::MPM(QWidget *parent)
    : SimCenterAppWidget(parent)
{
    int windowWidth = 800;
    int windowWidthMin = 250;
    QWidget     *mainGroup = new QWidget();
    QGridLayout *mainLayout = new QGridLayout();

    QLabel *generalDescriptionLabel = new QLabel("Digital Twins of NHERI Experimental Facilities in Multi-GPU Material Point Method (ClaymoreUW MPM): "
                                                 "\n"
                                                 "\n Place waterborne events (EVT) in NHERI Digital Twins to streamline your experimental research."
                                                 "\n ClaymoreUW, a high-performance 3D Material Point Method code, is used."
                                                 "\n"
                                                 "\n 1.) Set general simulation Settings, e.g. the total simulation duration."						 
                                                 "\n 2.) Define Bodies (e.g. fluid, debris, structures, etc) via materials and initial conditions."
                                                 "\n 3.) Define Boundaries (Digital Twins, Structures, etc) as boundary conditions."
                                                 "\n 4.) Specify Sensors (e.g. wave-gauges) to measure within simulations."
                                                 "\n 5.) Select other Output settings (e.g. write simulation checkpoint-resume files).");
                                                //  "\n 6.) If all side-bar pages are complete, click [RUN at DesignSafe] (bottom of the app) to simulate your Event.");


    mainLayout->addWidget(generalDescriptionLabel, 0, 0);
    mpmSettings = new SettingsMPM();
    mpmParticles = new ParticlesMPM();
    mpmBoundaries = new BoundariesMPM();
    mpmSensors = new SensorsMPM();
    mpmOutputs = new OutputsMPM();

    QTabWidget *theTabWidget = new QTabWidget();
    theTabWidget->addTab(mpmSettings, QIcon(QString(":/icons/settings-black.svg")), "Settings");
    theTabWidget->addTab(mpmParticles, QIcon(QString(":/icons/deform-black.svg")), "Bodies");
    theTabWidget->addTab(mpmBoundaries, QIcon(QString(":/icons/man-door-black.svg")), "Boundaries");
    theTabWidget->addTab(mpmSensors, QIcon(QString(":/icons/dashboard-black.svg")), "Sensors");
    theTabWidget->addTab(mpmOutputs, QIcon(QString(":/icons/settings-black.svg")), "Outputs");    
    int sizePrimaryTabs =20;
    theTabWidget->setIconSize(QSize(sizePrimaryTabs,sizePrimaryTabs));
    // theTabWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

    mainLayout->addWidget(theTabWidget, 1, 0);
    mainGroup->setLayout(mainLayout);
    mainGroup->setMinimumWidth(windowWidthMin);
    mainGroup->setMaximumWidth(windowWidth);
    // mainGroup->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setLineWidth(1);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setWidget(mainGroup);
    scrollArea->setMinimumWidth(windowWidthMin + 25);
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
    
  // The JSON object-or-array that defines each main tab (i.e. Settings, Bodies, Boundaries, Sensors, Outputs)
  QJsonObject settingsObject;  
  QJsonArray bodiesArray;
  QJsonArray boundariesArray;
  QJsonArray sensorsArray;
  QJsonObject outputsObject;

  // Pass in the objects or array object wrappers to the outputToJSON functions
  QJsonObject bodiesObjectWrapper;
  QJsonObject boundariesObjectWrapper;
  QJsonObject sensorsObjectWrapper;
  QJsonArray  bodiesArrayWrapper;
  QJsonArray  boundariesArrayWrapper;
  QJsonArray  sensorsArrayWrapper;

  // Some of the outputToJSON functions will add to the arrays in the wrappers
  // We pass in objects wrapping the arrays to avoid two outputToJSON functions per class (could also template)
  bodiesObjectWrapper["bodies"] = bodiesArrayWrapper;  
  boundariesObjectWrapper["boundaries"] = boundariesArrayWrapper;
  sensorsObjectWrapper["sensors"] = sensorsArrayWrapper;

  // Call the outputToJSON functions in the sub-widget classes (i.e. tabs)
  mpmSettings->outputToJSON(settingsObject);
  mpmParticles->outputToJSON(bodiesObjectWrapper);
  mpmBoundaries->outputToJSON(boundariesObjectWrapper);
  mpmSensors->outputToJSON(sensorsObjectWrapper);
  mpmOutputs->outputToJSON(outputsObject);

  // ==================== Settings ====================
  // Settings (simulation in ClaymoreUW currently)
  if (settingsObject.contains("simulation") && settingsObject["simulation"].isObject()) {
    // Read in the simulation object from the settings object
    jsonObject["simulation"] = settingsObject["simulation"];

    // Move some values from the outputs object to the simulation settings object
    QJsonObject my_sim = jsonObject["simulation"].toObject(); 
    if (outputsObject.contains("save_suffix") && outputsObject["save_suffix"].isString()) {
      my_sim["save_suffix"] = outputsObject["save_suffix"].toString(); // for ClaymoreUW, simulation:save_suffix = outputs:bodies_save_suffix
    }
    if (outputsObject.contains("fps") && outputsObject["fps"].isDouble()) {
      my_sim["fps"] = outputsObject["fps"].toDouble(); // for ClaymoreUW, simulation:fps = outputs:outputBodies_Dt
    }
    // To be an output option, not a simulation option
    if ((my_sim.contains("duration") && my_sim["duration"].isDouble()) && (my_sim.contains("fps") && my_sim["fps"].isDouble())) {
      my_sim["frames"] = my_sim["duration"].toDouble() * my_sim["fps"].toDouble(); // for ClaymoreUW, simulation:frames = simulation:duration * simulation:fps
    } else {
      my_sim["frames"] = my_sim["fps"];
    }
    jsonObject["simulation"] = my_sim;
  }
  // Computer, as in hardware and how it is compiled for by application if relevant (e.g. number of GPUs)
  if (settingsObject.contains("computer") && settingsObject["computer"].isObject()) {
    jsonObject["computer"] = settingsObject["computer"];
  }
  // Similitude scaling
  if (settingsObject.contains("scaling") && settingsObject["scaling"].isObject()) {
    jsonObject["scaling"] = settingsObject["scaling"]; 
  }

  // ==================== Bodies ====================
  // Bodies (models in ClaymoreUW currently)
  if (bodiesObjectWrapper.contains("bodies") && bodiesObjectWrapper["bodies"].toArray().size() > 0) {
    bodiesArray = bodiesObjectWrapper["bodies"].toArray();
    if (0) jsonObject["bodies"] = bodiesArray; // for the future schema
    else   jsonObject["models"] = bodiesArray; // for ClaymoreUW, models = bodies
  }

  // ==================== Boundaries ====================
  // Boundaries (grid-boundaries in ClaymoreUW currently, TODO: Deprecate and change to "boundaries")
  if (boundariesObjectWrapper.contains("grid-boundaries") && boundariesObjectWrapper["grid-boundaries"].isArray()) {
    jsonObject["grid-boundaries"] = boundariesObjectWrapper["grid-boundaries"]; // ClaymoreUW artifact, TODO: Deprecate
  }

  // ==================== Sensors ====================
  // Sensors (grid-targets, particle-targets in ClaymoreUW currently, TODO: Deprecate and change to "sensors")
  if (0) {
    if (sensorsObjectWrapper.contains("sensors") && sensorsObjectWrapper["sensors"].isArray()) {
      // sensors is an array of objects, each is an individual sensor
      jsonObject["sensors"] = sensorsObjectWrapper["sensors"];
    }
  }
  if (sensorsObjectWrapper.contains("particle-sensors") && sensorsObjectWrapper["particle-sensors"].isArray()) {
    // jsonObject["particle-sensors"] = sensorsObjectWrapper["particle-sensors"];
    jsonObject["particle-targets"] = sensorsObjectWrapper["particle-sensors"]; // ClaymoreUW artifact, TODO: Deprecate
  }
  if (sensorsObjectWrapper.contains("grid-sensors") && sensorsObjectWrapper["grid-sensors"].isArray()) {
    // jsonObject["grid-sensors"] = sensorsObjectWrapper["grid-sensors"];
    jsonObject["grid-targets"] = sensorsObjectWrapper["grid-sensors"]; // ClaymoreUW artifact, TODO: Deprecate
  }

  // ==================== Outputs ====================
  // Outputs (not a separate object in ClaymoreUW currently, must move some fields to other objects manually for ClaymoreUW)
  if (outputsObject.contains("outputs") && outputsObject["outputs"].isObject()) {
    jsonObject["outputs"] = outputsObject["outputs"]; // for future schema, not used in ClaymoreUW currently
  }

  // if (bodiesArray.size() > 0) {
  //   bool allBodiesAreObjects = false;
  //   for (int i = 0; i < bodiesArray.size(); ++i) {
  //     if (bodiesArray[i].isObject() == false) 
  //       allBodiesAreObjects = false; 
  //   }
  //   if (allBodiesAreObjects) {
  //     if (0) jsonObject["bodies"] = bodiesArray; // for the future schema
  //     else   jsonObject["models"] = bodiesArray; // for ClaymoreUW, models = bodies
  //   }
  // }

  // // Boundaries (grid-boundaries in ClaymoreUW currently)
  // if (boundariesObjectWrapper.contains("boundaries") && boundariesObjectWrapper["boundaries"].toArray().size() > 0) {
  //   boundariesArray = boundariesObjectWrapper["boundaries"].toArray();
  // }
  // if (boundariesArray.size() > 0) {
  //   bool allBoundariesAreObjects = true;
  //   for (int i = 0; i < boundariesArray.size(); ++i) {
  //     // An individual boundary is an object
  //     if (boundariesArray[i].isObject() == false) 
  //         allBoundariesAreObjects = false; 
  //   }
  //   if (allBoundariesAreObjects) {
  //     jsonObject["grid-boundaries"] = boundariesArray; // for ClaymoreUW, grid-boundaries = boundaries
  //     // jsonObject["particle-boundaries"] = boundariesArray; // for ClaymoreUW, particle-boundaries = boundaries
  //     jsonObject["boundaries"] = boundariesArray; // for the future schema
  //   }
  // }

  // QJsonArray particleSensorsArray;
  // QJsonArray gridSensorsArray;
  // if (sensorsObjectWrapper.contains("sensors") && sensorsObjectWrapper["sensors"].toArray().size() > 0) {
  //   sensorsArray = sensorsObjectWrapper["sensors"].toArray();
  // }
  // if (sensorsArray.size() > 0) {
  //   bool allSensorsAreObjects = true;

  //   for (int i = 0; i < sensorsArray.size(); ++i) {
  //     // An individual sensor is an object
  //     if (sensorsArray[i].isObject() == false) 
  //         allSensorsAreObjects = false; 
  //   }
  //   for (int i = 0; i < sensorsArray.size(); ++i) {
  //     bool isGridSensor = false;
  //     bool isParticleSensor = false;
  //     if (sensorsArray[i].isObject()) {
  //       if (sensorsArray[i].toObject().contains("type")) {
  //         QJsonValue theValue = sensorsArray[i].toObject()["type"];
  //         QString selection = theValue.toString();

  //         if (selection == "grid") {
  //           isGridSensor = true;
  //           gridSensorsArray.append(sensorsArray[i]);
  //         }
  //         else if (selection == "particle") {
  //           isParticleSensor = true;
  //           particleSensorsArray.append(sensorsArray[i]);
  //         }

  //       }
  //     } 
  //   }

  //   if (allSensorsAreObjects) {
  //     jsonObject["grid-targets"] = gridSensorsArray; // for ClaymoreUW, grid-sensors = sensors
  //     jsonObject["particle-targets"] = particleSensorsArray; // for ClaymoreUW, particle-sensors = sensors
  //     jsonObject["sensors"] = sensorsArray; // for the future schema
  //   }
  // }

  // jsonObject["bodies"] = bodiesArray;

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


/* *****************************************************************************
Copyright (c) 2016-2023, The Regents Sensor the University Sensor California (Regents).
All rights reserved.

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:

1. Redistributions Sensor source code must retain the above copyright notice, this
   list Sensor conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list Sensor conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SSensorTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES Sensor MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT Sensor SUBSTITUTE GOODS OR SERVICES;
LOSS Sensor USE, DATA, OR PRSensorITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY Sensor LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT Sensor THE USE Sensor THIS
SSensorTWARE, EVEN IF ADVISED Sensor THE POSSIBILITY Sensor SUCH DAMAGE.

The views and conclusions contained in the sSensortware and documentation are those
Sensor the authors and should not be interpreted as representing Sensorficial policies,
either expressed or implied, Sensor the FreeBSD Project.

REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
THE IMPLIED WARRANTIES Sensor MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
THE SSensorTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED HEREUNDER IS 
PROVIDED "AS IS". REGENTS HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, 
UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

*************************************************************************** */

#include "SensorsMPM.h"
#include <QLabel>
#include <QComboBox>
#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>
#include <QTabWidget>
#include <QStackedWidget>
#include <QDebug>
// #include <QSvgWidget>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>


#include "SensorMPM.h"

// #include <SC_FileEdit.h>
#include <SC_TableEdit.h>
#include <SC_ComboBox.h>
#include <SC_DoubleLineEdit.h>

SensorsMPM::SensorsMPM(QWidget *parent)
  :SimCenterWidget(parent)
{
  //
  // This file creates the widgets used to define the sensors for the MPM application
  // Sensors are instruments that measure some quantity, e.g. free-surface elevation, velocity, force, etc.
  // These are meant to be digital twins of real sensors. Hence, they posses the same variables as their real-world counterparts.
  // The user can specify the type of sensor, attribute to measure, operation to perform, sampling frequency, name, location.
  // The user can also specify the direction in which to measure the attribute. This 
  // Each tab on this page is a different type of sensor
  // A general template for creating custom sensors is provided for users. 
  // I also provide a few template specializations
  // These are common, pre-made instruments.
  // They include wave gauges, velocity meters, and load cells
  //

  QGridLayout *layout = new QGridLayout();
  this->setLayout(layout);

  // int numRow = 0;
  // ===========================================================================
  QWidget *wgWidget = new QWidget();
  QWidget *vmWidget = new QWidget();
  QWidget *lcWidget = new QWidget();
  QWidget *pmWidget = new QWidget();
  QGridLayout *wgLayout = new QGridLayout();
  QGridLayout *vmLayout = new QGridLayout();
  QGridLayout *lcLayout = new QGridLayout();
  QGridLayout *pmLayout = new QGridLayout();
  wgWidget->setLayout(wgLayout);
  vmWidget->setLayout(vmLayout);
  lcWidget->setLayout(lcLayout);
  pmWidget->setLayout(pmLayout);


  // ===========================================================================
  QTabWidget *theTabWidget = new QTabWidget();
  theTabWidget->addTab(wgWidget, "Wave-Gauges");
  theTabWidget->addTab(vmWidget, "Velocity-Meters");
  theTabWidget->addTab(lcWidget, "Load-Cells");  
  theTabWidget->addTab(pmWidget, "Piezo-Meters");  

  // Buttons for creating and removing individual sensor
  // All geometries will be composed together for an individual body to form a single sensor
  QPushButton *addB = new QPushButton("Create Sensor"); 
  QPushButton *delB = new QPushButton("Remove Sensor");
  addB->setIcon(QIcon(":/icons/pencil-plus-white.svg"));
  delB->setIcon(QIcon(":/icons/eraser-white.svg"));
  addB->setIconSize(QSize(24,24));
  delB->setIconSize(QSize(24,24));

  QFrame *theHeaderFrame = new QFrame();
  QGridLayout *headerLayout = new QGridLayout();
  theHeaderFrame->setLayout(headerLayout);
  headerLayout->addWidget(addB,0,0);
  headerLayout->addWidget(delB,0,1);  
  headerLayout->setColumnStretch(2,1);
  
  ///%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // Add tab per Body
  QTabWidget *tabWidget = new QTabWidget();
  int sizeBodyTabs = 20;
  tabWidget->setIconSize(QSize(sizeBodyTabs, sizeBodyTabs));
  tabWidget->setTabsClosable(true); // Close tabs with X mark via mouse (connect to tabCloseRequested)
  tabWidget->setMovable(true); // Move tabs with mouse

  // ===========================================================================
  layout->addWidget(theHeaderFrame);
  layout->addWidget(tabWidget);
  layout->setRowStretch(2,1);
  // ===========================================================================

  int numDefaultTabs = 1; // Need atleast one sensor tab, so dont allow last one to be deleted
  QVector<QWidget*> theAdded(numReserveTabs); // 16 is max number of added tabs
  QVector<QGridLayout*> theAddedLayout(numReserveTabs);
  QVector<QTabWidget*> modelAddedTabWidget(numReserveTabs); 
  for (int i = 0; i < numReserveTabs; i++) {
    theAdded[i] = new QWidget();
    theAddedLayout[i] = new QGridLayout();
    addedSensor[i] = new SensorMPM();
  }

  // Init. default sensors automatically
  // Wave-gauges
  tabWidget->addTab(theAdded[numAddedTabs], QIcon(QString(":/icons/user-black.svg")), "Wave-Gauges");
  theAdded[numAddedTabs]->setLayout(theAddedLayout[numAddedTabs]);
  theAddedLayout[numAddedTabs]->addWidget(addedSensor[numAddedTabs]);
  numAddedTabs += 1;

  // Velocitmeters
  tabWidget->addTab(theAdded[numAddedTabs], QIcon(QString(":/icons/user-black.svg")), "Velocity-Meters");
  theAdded[numAddedTabs]->setLayout(theAddedLayout[numAddedTabs]);
  theAddedLayout[numAddedTabs]->addWidget(addedSensor[numAddedTabs]);
  numAddedTabs += 1;

  // Load-cells
  tabWidget->addTab(theAdded[numAddedTabs], QIcon(QString(":/icons/user-black.svg")), "Load-Cells");
  theAdded[numAddedTabs]->setLayout(theAddedLayout[numAddedTabs]);
  theAddedLayout[numAddedTabs]->addWidget(addedSensor[numAddedTabs]);
  numAddedTabs += 1;

  // Piezo-Meters
  tabWidget->addTab(theAdded[numAddedTabs], QIcon(QString(":/icons/user-black.svg")), "Piezo-Meters");
  theAdded[numAddedTabs]->setLayout(theAddedLayout[numAddedTabs]);
  theAddedLayout[numAddedTabs]->addWidget(addedSensor[numAddedTabs]);
  numAddedTabs += 1;



  // Create and Init. another sensor tab at user request (click create)
  connect(addB, &QPushButton::released, this, [=]() {
    // Concatenate string to say "Custom Body 1", "Custom Body 2", etc.
    if (numAddedTabs >= numReserveTabs) 
      return;
    tabWidget->addTab(theAdded[numAddedTabs], QIcon(QString(":/icons/user-black.svg")), "Custom " + QString::number(numAddedTabs + 1));
    theAdded[numAddedTabs]->setLayout(theAddedLayout[numAddedTabs]);
    theAddedLayout[numAddedTabs]->addWidget(addedSensor[numAddedTabs]);
    numAddedTabs += 1;
  });

  // Remove sensor at user request (click remove)
  connect(delB, &QPushButton::released, this, [=]() {
    if (( tabWidget->currentIndex() == -1) || (tabWidget->count() <= numDefaultTabs) || (tabWidget->currentIndex() < numDefaultTabs)) 
      return;
    auto widget = tabWidget->widget(tabWidget->currentIndex());
    if (widget) {
          // widget.deleteLater()
    }
    tabWidget->setCurrentIndex(tabWidget->currentIndex()-1);
    tabWidget->removeTab(tabWidget->currentIndex()+1);
    // clean up
    numAddedTabs -= 1;
  }); 
  // Remove sensor at user request (click the "X" mark on a tab)
  connect(tabWidget, &QTabWidget::tabCloseRequested, this, [=](int index) {
    if (( index == -1) || (tabWidget->count() <= numDefaultTabs) || (index < numDefaultTabs)) 
      return; 
    // tabWidget->setCurrentIndex(index-1);
    auto widget = tabWidget->widget(index);
    if (widget) {
          // widget.deleteLater()
    }
    if (index > 0 && index < tabWidget->count()-1 && tabWidget->currentIndex() == index) {
      tabWidget->setCurrentIndex(index-1);
    } 
    tabWidget->removeTab(index);
    // clean up
    numAddedTabs -= 1;
    
  });

  // Enum to set tab's icons, titles, init values, etc.
  enum sensorEnum : int {CUSTOM = 0, WAVE_GAUGE, VELOCITY_METER, LOAD_CELL, PIEZO_METER, TOTAL};

  // Set initial sensor preset
  for (int i=0; i<numAddedTabs; i++) {
    auto j = static_cast<sensorEnum>(i+1);
    if (i >= numReserveTabs) break;
    if (j == sensorEnum::WAVE_GAUGE)          addedSensor[i]->setSensorType(WAVE_GAUGE);
    else if (j == sensorEnum::VELOCITY_METER) addedSensor[i]->setSensorType(VELOCITY_METER);
    else if (j == sensorEnum::LOAD_CELL)      addedSensor[i]->setSensorType(LOAD_CELL);
    else if (j == sensorEnum::PIEZO_METER)    addedSensor[i]->setSensorType(PIEZO_METER);
    else addedSensor[i]->setSensorType(CUSTOM);
  }
  
}

SensorsMPM::~SensorsMPM()
{

}

void SensorsMPM::clear(void)
{
  for (int i=0; i<numAddedTabs; i++) {
    if (i >= numReserveTabs) break;
    addedSensor[i]->clear();
  }
}

bool
SensorsMPM::outputToJSON(QJsonObject &jsonObject)
{
  // TODO: Basic safety checks
  // Iterate over all tabs, fill a unique JSON object, and add to a JSON array
  QJsonArray theArray;// = jsonObject["sensors"].toArray(); // Holds array of sensor objects
  QJsonArray theGridArray;// = jsonObject["grid-sensors"].toArray(); // Holds array of sensor objects
  QJsonArray theParticleArray;// = jsonObject["particle-sensors"].toArray(); // Holds array of sensor objects
  QJsonObject theObject; // Passed to individual sensor objects to fill
  for (int i=0; i<numAddedTabs; i++) {
    if (i >= numReserveTabs) break;
    addedSensor[i]->outputToJSON(theObject);
    if (0) {
      theArray.append(theObject["sensors"].toArray());
    } else {
      theGridArray.append(theObject["grid-sensors"].toArray());
      theParticleArray.append(theObject["particle-sensors"].toArray());
    }
  }
  if (0) {
    theArray = theObject["sensors"].toArray();
    jsonObject["sensors"] = theArray; // Add array of sensor objects to the body object
  } else {
    theGridArray = theObject["grid-sensors"].toArray();
    theParticleArray = theObject["particle-sensors"].toArray();
    jsonObject["grid-sensors"] = theGridArray; // Add array of sensor objects to the body object
    jsonObject["particle-sensors"] = theParticleArray; // Add array of sensor objects to the body object
  }
  return true;
}

bool
SensorsMPM::inputFromJSON(QJsonObject &jsonObject)
{
  // if (jsonObject.contains("grid-sensors") == false) {
  //   qDebug() << "SensorsMPM::inputFromJSON grid-sensors not found in JSON";
  //   // return false;
  // }
  // if (jsonObject["grid-sensors"].isArray() == false) {
  //   qDebug() << "SensorsMPM::inputFromJSON grid-sensors is not an array in JSON";
  //   // return false;
  // }
  // if (jsonObject["grid-sensors"].toArray().size() == 0) {
  //   qDebug() << "SensorsMPM::inputFromJSON grid-sensors is empty in JSON";
  //   // return false;
  // }
  // QJsonArray theGridSensorArray = jsonObject["grid-sensors"].toArray();

  // for (int i=0; i<theGridSensorArray.size(); i++) {
  //   if (theGridSensorArray[i].isObject() == false) {
  //     qDebug() << "SensorsMPM::inputFromJSON grid-sensors is not an object in JSON";
  //     continue
  //   }
  //   addedSensor[i]->inputFromJSON(theGridSensorArray[i].toObject());


  //   // if (addedSensor[i] == nullptr) addedSensor[i] = new SensorMPM();
  //   // QJsonObject theObject = theGridSensorArray[i].toObject();
  //   // addedSensor[i]->inputFromJSON(theObject);
  // }
  
  if (jsonObject.contains("particle-sensors") == false) {
    qDebug() << "SensorsMPM::inputFromJSON particle-sensors not found in JSON";
    // return false;
  } else {
    if (jsonObject["particle-sensors"].isArray() == false) {
    qDebug() << "SensorsMPM::inputFromJSON particle-sensors is not an array in JSON";
    // return false;
    } else {
      if (jsonObject["particle-sensors"].toArray().size() == 0) {
        qDebug() << "SensorsMPM::inputFromJSON particle-sensors is empty in JSON";
        // return false;
      } else {
        QJsonArray theParticleSensorArray = jsonObject["particle-sensors"].toArray();
        int i = 0;
        for (auto theSensorObject : theParticleSensorArray) {
          if (theSensorObject.isObject() == false) {
            qDebug() << "SensorsMPM::inputFromJSON particle-sensors is not an object in JSON";
            // return false;
            continue;
          }
          qDebug() << "SensorsMPM::inputFromJSON particle-sensors is an object in JSON";
          QJsonObject theObject = theParticleSensorArray[i].toObject();
          int j = 0;
          if (theObject["attribute"].toString() == "Elevation" || theObject["attribute"].toString() == "Position_Y") {
            j = 0;
          } else if (theObject["attribute"].toString() == "Velocity" || theObject["attribute"].toString() == "Velocity_X" || theObject["attribute"].toString() == "Velocity_Y" || theObject["attribute"].toString() == "Velocity_Z" || theObject["attribute"].toString() == "Velocity_Magnitude") {
            j = 1;
          } else if (theObject["attribute"].toString() == "Force" || theObject["attribute"].toString() == "Force_X" || theObject["attribute"].toString() == "Force_Y" || theObject["attribute"].toString() == "Force_Z" || theObject["attribute"].toString() == "Force_Magnitude") {
            j = 2;
          } else if (theObject["attribute"].toString() == "Pressure") {
            j = 3;
          } else {
            j = 4;
          }
          if (addedSensor[j]->inputFromJSON(theObject)) {
            qDebug() << "SensorsMPM::inputFromJSON particle-sensors returned true for input from JSON";
          } else {
            qDebug() << "SensorsMPM::inputFromJSON particle-sensors returned false for input from JSON";
          }
          i += 1;
          // For now, the mapping to the sensor tabs is messy so we won't inputFromJSON
        }
      }
    }
  }
  
  if (jsonObject.contains("grid-sensors") == false) {
    qDebug() << "SensorsMPM::inputFromJSON grid-sensors not found in JSON";
    // return false;
  } else {
    if (jsonObject["grid-sensors"].isArray() == false) {
      qDebug() << "SensorsMPM::inputFromJSON grid-sensors is not an array in JSON";
      // return false;
    } else {
      if (jsonObject["grid-sensors"].toArray().size() == 0) {
        qDebug() << "SensorsMPM::inputFromJSON grid-sensors is empty in JSON";
        // return false;
      } else {
        QJsonArray theGridSensorArray = jsonObject["grid-sensors"].toArray();
        int i = 0;
        for (auto theSensorObject : theGridSensorArray) {
          if (theSensorObject.isObject() == false) {
            qDebug() << "SensorsMPM::inputFromJSON grid-sensors is not an object in JSON";
            // return false;
            continue;
          }
          QJsonObject theObject = theGridSensorArray[i].toObject();
          int j = 0;
          if (theObject["attribute"].toString() == "Elevation" || theObject["attribute"].toString() == "Position_Y") {
            j = 0;
          } else if (theObject["attribute"].toString() == "Velocity" || theObject["attribute"].toString() == "Velocity_X" || theObject["attribute"].toString() == "Velocity_Y" || theObject["attribute"].toString() == "Velocity_Z" || theObject["attribute"].toString() == "Velocity_Magnitude") {
            j = 1;
          } else if (theObject["attribute"].toString() == "Force" || theObject["attribute"].toString() == "Force_X" || theObject["attribute"].toString() == "Force_Y" || theObject["attribute"].toString() == "Force_Z" || theObject["attribute"].toString() == "Force_Magnitude") {
            j = 2;
          } else if (theObject["attribute"].toString() == "Pressure") {
            j = 3;
          } else {
            j = 4;
          }
          qDebug() << "SensorsMPM::inputFromJSON grid-sensors is an object in JSON";
          if (addedSensor[j]->inputFromJSON(theObject)) {
            qDebug() << "SensorsMPM::inputFromJSON grid-sensors returned true for input from JSON";
          } else {
            qDebug() << "SensorsMPM::inputFromJSON grid-sensors returned false for input from JSON";
          }
          i += 1;
          // For now, the mapping to the sensor tabs is messy so we won't inputFromJSON
        }
      }
    }
  }
  
  
  
  // for (int i=0; i<theParticleSensorArray.size(); i++) {
    //   if (theParticleSensorArray[i].isObject() == false) {
      //     qDebug() << "SensorsMPM::inputFromJSON particle-sensors is not an object in JSON";
      //     // return false;
      //     continue
      //   }
      //   // if (addedSensor[i] == nullptr) addedSensor[i] = new SensorMPM();
  //   // QJsonObject theObject = theParticleSensorArray[i].toObject();
  //   // addedSensor[i]->inputFromJSON(theObject);
  // }

  // numAddedTabs = (theArray.size() <= numReserveTabs) ? theArray.size() : numReserveTabs;
  // int shift = 0;
  // for (int i=0; i<theArray.size(); i++) {
  //   int j = i - shift;
  //   if (j >= numReserveTabs) break;
  //   if (theArray[i].isObject() == false) { shift=shift+1; continue;}
  //   if (addedSensor[j] == nullptr) addedSensor[j] = new SensorMPM();
  //   QJsonObject theObject = theArray[i].toObject();
  //   addedSensor[i]->inputFromJSON(theObject);
  //   // numAddedTabs += 1; // May go out of bounds if it doesnt start at 0
  // }
  return true;
}

bool
SensorsMPM::copyFiles(QString &destDir)
{
  for (int i=0; i<numAddedTabs; i++) {
    if (i >= numReserveTabs) break;
    addedSensor[i]->copyFiles(destDir);
  }
  return true;    
}

bool
SensorsMPM::setDigitalTwin(int twinIdx)
{
  for (int i=0; i<numAddedTabs; i++) {
    if (i >= numReserveTabs) break;
    addedSensor[i]->setDigitalTwin(twinIdx);
  }
  return true;
}
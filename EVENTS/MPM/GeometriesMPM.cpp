/* *****************************************************************************
Copyright (c) 2016-2023, The Regents of the University of California (Regents).
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

#include "GeometriesMPM.h"
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

#include <SC_ComboBox.h>
#include <SC_DoubleLineEdit.h>
#include <SC_IntLineEdit.h>
#include <SC_StringLineEdit.h>
#include <SC_TableEdit.h>
#include <SC_FileEdit.h>
#include <SC_CheckBox.h>

#include <GeometryMPM.h>

#include <vector>
#include <memory>

GeometriesMPM::GeometriesMPM(QWidget *parent)
  :SimCenterWidget(parent)
{
  int numRow = 0;

  QGridLayout *layout = new QGridLayout();
  this->setLayout(layout);
  
  // Buttons for creating and removing individual geometry
  // All geometries will be composed together for an individual body to form a single geometry
  QPushButton *addB = new QPushButton("Create Geometry"); 
  QPushButton *delB = new QPushButton("Remove Geometry");
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
  layout->addWidget(theHeaderFrame);

  ///%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // Add tab per Body
  QTabWidget *tabWidget = new QTabWidget();
  tabWidget->setTabsClosable(true); // Close tabs with X mark via mouse (connect to tabCloseRequested)
  tabWidget->setMovable(true); // Move tabs with mouse

  QVector<QWidget*> theAdded(numReserveTabs); // 16 is max number of added tabs

  int sizeBodyTabs = 20;
  layout->addWidget(tabWidget);

  int numDefaultTabs = 1; // Need atleast one geometry tab, so dont allow last one to be deleted
  QVector<QGridLayout*> theAddedLayout(numReserveTabs);
  QVector<QTabWidget*> modelAddedTabWidget(numReserveTabs); 
  for (int i = 0; i < numReserveTabs; i++) {
    theAdded[i] = new QWidget();
    theAddedLayout[i] = new QGridLayout();
    addedGeometry[i] = new GeometryMPM();
  }

  // Init. first geometry automatically
  tabWidget->addTab(theAdded[numAddedTabs], QIcon(QString(":/icons/triangle-square-circle-black.svg")), "Custom " + QString::number(numAddedTabs + 1));
  tabWidget->setIconSize(QSize(sizeBodyTabs, sizeBodyTabs));
  theAdded[numAddedTabs]->setLayout(theAddedLayout[numAddedTabs]);
  theAddedLayout[numAddedTabs]->addWidget(addedGeometry[numAddedTabs]);
  numAddedTabs += 1;

  // Add extra geometry at signal
  connect(this, &GeometriesMPM::addGeometry, this, [=]() {
    if (numAddedTabs >= numReserveTabs) {
      qDebug() << "Maximum number of geometries reached. Cannot add more.";
      return;
    }
    tabWidget->addTab(theAdded[numAddedTabs], QIcon(QString(":/icons/user-black.svg")), "Custom " + QString::number(numAddedTabs + 1));
    tabWidget->setIconSize(QSize(sizeBodyTabs, sizeBodyTabs));
    theAdded[numAddedTabs]->setLayout(theAddedLayout[numAddedTabs]);
    theAddedLayout[numAddedTabs]->addWidget(addedGeometry[numAddedTabs]);
    addedGeometry[numAddedTabs]->setBodyPreset(3); // TODO: Use enum for body presets
    numAddedTabs += 1;
  });

  // Remove geometry at signal
  connect(this, &GeometriesMPM::removeGeometry, this, [=]() {
    auto widget = tabWidget->widget(tabWidget->count()-1);
    if (widget) {
      // widget.deleteLater() // Delete the widget itself
    }
    tabWidget->setCurrentIndex(tabWidget->count()-2);
    tabWidget->removeTab(tabWidget->count()-1);
    // clean up
    numAddedTabs -= 1;
  });

  // Init. all extra geometry at user request (click create)
  connect(addB, &QPushButton::released, this, [=]() {
    // Concatenate string to say "Custom Body 1", "Custom Body 2", etc.
    if (numAddedTabs >= numReserveTabs) 
      return;
    tabWidget->addTab(theAdded[numAddedTabs], QIcon(QString(":/icons/user-black.svg")), "Custom " + QString::number(numAddedTabs + 1));
    tabWidget->setIconSize(QSize(sizeBodyTabs, sizeBodyTabs));
    theAdded[numAddedTabs]->setLayout(theAddedLayout[numAddedTabs]);
    theAddedLayout[numAddedTabs]->addWidget(addedGeometry[numAddedTabs]);
    addedGeometry[numAddedTabs]->setBodyPreset(3); // TODO: Use enum for body presets
    numAddedTabs += 1;
  });

  // Remove geometry at user request (click remove)
  connect(delB, &QPushButton::released, this, [=]() {
    if (( tabWidget->currentIndex() == -1) || (tabWidget->count() <= numDefaultTabs) || (tabWidget->currentIndex() < numDefaultTabs)) 
      return;
    auto widget = tabWidget->widget(tabWidget->currentIndex());
    if (widget) {
          // Delete the widget itself
          // widget.deleteLater()
    }
    tabWidget->setCurrentIndex(tabWidget->currentIndex()-1);
    tabWidget->removeTab(tabWidget->currentIndex()+1);
    // clean up
    numAddedTabs -= 1;
  }); 
  // Remove geometry at user request (click the "X" mark on a tab)
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

  // Set initial geometry body preset
  for (int i=0; i<numAddedTabs; i++) {
    this->setBodyPreset(3);
  }

}

GeometriesMPM::~GeometriesMPM()
{

}

void GeometriesMPM::clear(void)
{
  for (int i=0; i<numAddedTabs; i++) {
    addedGeometry[i]->clear();
  }
}

bool
GeometriesMPM::setBodyPreset(int index)
{
  // int numInitialTabs = 3; // 3 default tabs
  // for (int i=0; i<numInitialTabs; i++) {
  //   addedGeometry[i]->setBodyPreset(index);
  // }
  addedGeometry[0]->setBodyPreset(index);
  return true;
}

bool
GeometriesMPM::outputToJSON(QJsonObject &jsonObject)
{
  // TODO: Basic safety checks
  // Iterate over all tabs, fill a unique JSON object, and add to a JSON array
  QJsonArray theArray; // Holds array of geometry objects
  for (int i=0; i<numAddedTabs; i++) {
    QJsonObject theObject; // Passed to individual geometry objects to fill
    addedGeometry[i]->outputToJSON(theObject);
    theArray.append(theObject["geometry"].toObject());
  }
  jsonObject["geometry"] = theArray; // Add array of geometry objects to the body object
  return true;
}

bool
GeometriesMPM::inputFromJSON(QJsonObject &jsonObject)
{

  // Clear all geometries
  // this->clear();

  // Input all geometries (held in JSON array)
  if (jsonObject.contains("geometry") == false) {
    qDebug() << "GeometriesMPM::inputFromJSON geometry not found in JSON";
    // return false;
  }
  QJsonArray geometryArray = jsonObject["geometry"].toArray();
  while (geometryArray.size() < numAddedTabs) {
    qDebug() << "GeometriesMPM::inputFromJSON removing an excess geometry from interface";
    emitRemoveGeometry();
  }

  for (int i=0; i<geometryArray.size(); i++) {
    if (i >= numReserveTabs) {
      qDebug() << "GeometriesMPM::inputFromJSON too many geometries in JSON, exceeded reserved tabs";
      break;
    }
    if (i >= numAddedTabs){
      emitAddGeometry();
      // qDebug() << "GeometriesMPM::inputFromJSON too many geometries in JSON, exceeded current tabs";
      // break;
    }
    QJsonObject geometryObject = geometryArray[i].toObject();
    addedGeometry[i]->inputFromJSON(geometryObject);
  }

  return true;
}

bool
GeometriesMPM::copyFiles(QString &destDir)
{
  for (int i=0; i<numAddedTabs; i++) {
    if (i >= numReserveTabs) break; // Don't copy files for unreserved tabs
    if (addedGeometry[i]->copyFiles(destDir) == false) {
      qDebug() << "Error: Failed to copy geometry files to " << destDir << " for geometry " << i;
      // return false;
    } else {
      qDebug() << "Success: Copied geometry files to " << destDir << " for geometry " << i;
    }
  }
  return true;
}

bool GeometriesMPM::setDigitalTwin(int twinIdx)
{
  // TODO: Refactor because tabs can be moved around, etc.
  addedGeometry[0]->setDigitalTwin(twinIdx); // Assume first geometry is for digital twin
  return true;
}


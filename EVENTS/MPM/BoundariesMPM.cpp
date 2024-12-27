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

#include "BoundariesMPM.h"
#include <QLabel>
#include <QComboBox>
#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>
#include <QTabWidget>
#include <QStackedWidget>
#include <QDebug>
#include <QSvgWidget>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>

#include <BoundaryMPM.h>
#include <SC_ComboBox.h>
#include <SC_DoubleLineEdit.h>
#include <SC_IntLineEdit.h>
#include <SC_TableEdit.h>
#include <SC_FileEdit.h>
#include <SC_CheckBox.h>


BoundariesMPM::BoundariesMPM(QWidget *parent)
  :SimCenterWidget(parent)
{
  // --- Boundary
  QGridLayout *layout = new QGridLayout();
  this->setLayout(layout);

  int numRow = 0;
  
  // Buttons for creating and removing individual boundary
  // All geometries will be composed together for an individual body to form a single boundary
  QPushButton *addB = new QPushButton("Create Boundary"); 
  QPushButton *delB = new QPushButton("Remove Boundary");
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
  // Add tab per boundary
  QTabWidget *tabWidget = new QTabWidget();
  int sizeTabIcon = 20;
  tabWidget->setIconSize(QSize(sizeTabIcon,sizeTabIcon));
  tabWidget->setTabsClosable(true); // Close tabs with X mark via mouse (connect to tabCloseRequested)
  tabWidget->setMovable(true); // Move tabs with mouse

  QVector<QWidget*> theAdded(numReserveTabs); // numReserveTabs is max number of added tabs

  int sizeBodyTabs = 20;
  layout->addWidget(tabWidget);

  int numDefaultTabs = 1; // Need atleast one boundary tab, so dont allow last one to be deleted
  QVector<QGridLayout*> theAddedLayout(numReserveTabs);
  QVector<QTabWidget*> modelAddedTabWidget(numReserveTabs); 
  for (int i = 0; i < numReserveTabs; i++) {
    theAdded[i] = new QWidget();
    theAddedLayout[i] = new QGridLayout();
    addedBoundary[i] = new BoundaryMPM();
  }

  // Init. first four boundaries automatically for digital twin configuration
  // Wave Flume Facility
  tabWidget->addTab(theAdded[numAddedTabs], QIcon(QString(":/icons/wash-black.svg")), "Flume Facility");
  theAdded[numAddedTabs]->setLayout(theAddedLayout[numAddedTabs]);
  theAddedLayout[numAddedTabs]->addWidget(addedBoundary[numAddedTabs]);
  numAddedTabs += 1;

  // Wave Generator
  tabWidget->addTab(theAdded[numAddedTabs], QIcon(QString(":/icons/wave-break-black.svg")), "Wave Generator");
  theAdded[numAddedTabs]->setLayout(theAddedLayout[numAddedTabs]);
  theAddedLayout[numAddedTabs]->addWidget(addedBoundary[numAddedTabs]);
  numAddedTabs += 1;

  // Rigid Structure
  tabWidget->addTab(theAdded[numAddedTabs], QIcon(QString(":/icons/home-black.svg")), "Rigid Structure");
  theAdded[numAddedTabs]->setLayout(theAddedLayout[numAddedTabs]);
  theAddedLayout[numAddedTabs]->addWidget(addedBoundary[numAddedTabs]);
  numAddedTabs += 1;

  // Rigid Walls
  tabWidget->addTab(theAdded[numAddedTabs], QIcon(QString(":/icons/wall-black.svg")), "Rigid Walls");
  theAdded[numAddedTabs]->setLayout(theAddedLayout[numAddedTabs]);
  theAddedLayout[numAddedTabs]->addWidget(addedBoundary[numAddedTabs]);
  numAddedTabs += 1;


  // Create and Init. another boundary tab at user request (click create)
  connect(addB, &QPushButton::released, this, [=]() {
    // Concatenate string to say "Custom Body 1", "Custom Body 2", etc.
    if (numAddedTabs >= numReserveTabs) 
      return;
    tabWidget->addTab(theAdded[numAddedTabs], QIcon(QString(":/icons/user-black.svg")), "Custom " + QString::number(numAddedTabs + 1));
    tabWidget->setIconSize(QSize(sizeBodyTabs, sizeBodyTabs));
    theAdded[numAddedTabs]->setLayout(theAddedLayout[numAddedTabs]);
    theAddedLayout[numAddedTabs]->addWidget(addedBoundary[numAddedTabs]);
    numAddedTabs += 1;
  });

  // Remove boundary at user request (click remove)
  connect(delB, &QPushButton::released, this, [=]() {
    if (( tabWidget->currentIndex() == -1) || (tabWidget->count() <= numDefaultTabs) || (tabWidget->currentIndex() < numDefaultTabs)) 
      return;
    auto widget = tabWidget->widget(tabWidget->currentIndex());
    if (widget) {
          // Delete the widget itself manually?
          // widget.deleteLater()
    }
    tabWidget->setCurrentIndex(tabWidget->currentIndex()-1);
    tabWidget->removeTab(tabWidget->currentIndex()+1);
    // clean up
    numAddedTabs -= 1;
  }); 
  // Remove boundary at user request (click the "X" mark on a tab)
  connect(tabWidget, &QTabWidget::tabCloseRequested, this, [=](int index) {
    if (( index == -1) || (tabWidget->count() <= numDefaultTabs) || (index < numDefaultTabs)) 
      return; 
    // tabWidget->setCurrentIndex(index-1);
    auto widget = tabWidget->widget(index);
    if (widget) {
          // removes the widget
          // widget.deleteLater()
    }
    if (index > 0 && index < tabWidget->count()-1 && tabWidget->currentIndex() == index) {
      tabWidget->setCurrentIndex(index-1);
    } 
    tabWidget->removeTab(index);
    // clean up
    numAddedTabs -= 1;
    
  });

  // connect(addedBoundary[2], &BoundaryMPM::structDimensionsChanged, this, &BoundariesMPM::structDimensionsChangedSlot);

  // connect(addedBoundary[2], SIGNAL(&BoundaryMPM::structOriginChanged(QString)), this, SIGNAL(structOriginChanged(QString)));

  // connect(addedBoundary[2], &BoundaryMPM::structOriginChanged, this, &BoundariesMPM::structOriginChangedSlot);

  // BoundaryMPM signals to BoundariesMPM when structDimensionsChanged and structOriginChanged
  // are emitted. BoundariesMPM will then emit the same signals to the parent MPM widget
  // connect(addedBoundary[2], &BoundaryMPM::structDimensionsChanged, this, &BoundariesMPM::structDimensionsChanged);


  // Then we need to connect the signals from the addedBoundary[i] to the same signals in BoundariesMPM


  // TODO: without using a hardcoded index
  // connect(addedBoundary[0], &BoundaryMPM::structDimensionsChanged, this, &BoundariesMPM::structDimensionsChanged);
  // connect(addedBoundary[0], &BoundaryMPM::structOriginChanged, this, &BoundariesMPM::structOriginChanged);

  // Try to iterate over all addedBoundary[i] and connect to the same signal
  // For loops are not allowed in signal/slot connections, so use a lambda function


  // for loop version
  // for (int i=0; i<numAddedTabs; i++) {
  //   connect(addedBoundary[i], &BoundaryMPM::structDimensionChanged, this, &BoundariesMPM::structDimensionChanged);
  //   connect(addedBoundary[i], &BoundaryMPM::structOriginChanged, this, &BoundariesMPM::structOriginChanged);
  // }

  // connect(addedBoundary[structureID], &BoundaryMPM::dimensionChanged, this, &BoundariesMPM::structDimensionChanged);

  // Enum to set tab's icons, titles, init values, etc.
  enum boundaryEnum : int {CUSTOM = 0, WAVE_FLUME, WAVE_GENERATOR, RIGID_STRUCTURE, RIGID_WALLS, TOTAL};

  // Set initial boundary type
  for (int i=0; i<numAddedTabs; i++) {
    if (i >= numReserveTabs) break;
    if (i == 0) addedBoundary[i]->setBoundaryType(WAVE_FLUME);
    else if (i == 1) addedBoundary[i]->setBoundaryType(WAVE_GENERATOR);
    else if (i == 2) addedBoundary[i]->setBoundaryType(RIGID_STRUCTURE);
    else if (i == 3) addedBoundary[i]->setBoundaryType(RIGID_WALLS);
    else addedBoundary[i]->setBoundaryType(CUSTOM);
  }
}

BoundariesMPM::~BoundariesMPM()
{

}

void BoundariesMPM::clear(void)
{
  for (int i=0; i<numAddedTabs; i++) {
    if (i >= numReserveTabs) break;
    addedBoundary[i]->clear();
  }
}

// void BoundariesMPM::structDimensionsChangedSlot(void)
// {
//   emit structDimensionsChanged();
// }
// void BoundariesMPM::structOriginChangedSlot(void)
// {
//   emit structOriginChanged();
// }

int BoundariesMPM::getNumBoundaries()
{
  return numAddedTabs;
}

bool BoundariesMPM::getBoundary(int index, BoundaryMPM* &theBoundary)
{
  if (index < numAddedTabs) {
    theBoundary = addedBoundary[index];
    return true;
  }
  return false;
}

BoundaryMPM* BoundariesMPM::getBoundary(int index)
{
  if (index < numAddedTabs) {
    return addedBoundary[index];
  }
  return nullptr;
}

BoundaryMPM* BoundariesMPM::getStructureBoundary()
{
  if (structureID < 0 || structureID >= numReserveTabs) return nullptr;
  return addedBoundary[structureID];
}

BoundaryMPM* BoundariesMPM::getPaddleBoundary()
{
  if (paddleID < 0 || paddleID >= numReserveTabs) return nullptr;
  return addedBoundary[paddleID];
}

// BoundaryMPM* BoundariesMPM::getBoundary(QString name)
// {
//   for (int i=0; i<numAddedTabs; i++) {
//     if (addedBoundary[i]->objectName() == name) {
//       return addedBoundary[i];
//     }
//   }
//   return nullptr;
// }

int BoundariesMPM::getStructureID()
{
  return structureID;
}

int BoundariesMPM::getPaddleID()
{
  return paddleID;
}


double BoundariesMPM::getDimensionX(BoundaryMPM* theBoundary)
{
  return theBoundary->getDimensionX();
}

double BoundariesMPM::getDimensionY(BoundaryMPM* theBoundary)
{
  return theBoundary->getDimensionY();
}

double BoundariesMPM::getDimensionZ(BoundaryMPM* theBoundary)
{
  return theBoundary->getDimensionZ();
}

SC_DoubleLineEdit* BoundariesMPM::getDimensionXWidget(BoundaryMPM* theBoundary)
{
  return theBoundary->getDimensionXWidget();
}

SC_DoubleLineEdit* BoundariesMPM::getDimensionYWidget(BoundaryMPM* theBoundary)
{
  return theBoundary->getDimensionYWidget();
}

SC_DoubleLineEdit* BoundariesMPM::getDimensionZWidget(BoundaryMPM* theBoundary)
{
  return theBoundary->getDimensionZWidget();
}

double BoundariesMPM::getOriginX(BoundaryMPM* theBoundary)
{
  return theBoundary->getOriginX();
}

double BoundariesMPM::getOriginY(BoundaryMPM* theBoundary)
{
  return theBoundary->getOriginY();
}

double BoundariesMPM::getOriginZ(BoundaryMPM* theBoundary)
{
  return theBoundary->getOriginZ();
}

SC_DoubleLineEdit* BoundariesMPM::getOriginXWidget(BoundaryMPM* theBoundary)
{
  return theBoundary->getOriginXWidget();
}

SC_DoubleLineEdit* BoundariesMPM::getOriginYWidget(BoundaryMPM* theBoundary)
{
  return theBoundary->getOriginYWidget();
}

SC_DoubleLineEdit* BoundariesMPM::getOriginZWidget(BoundaryMPM* theBoundary)
{
  return theBoundary->getOriginZWidget();
}

int BoundariesMPM::getArrayX(BoundaryMPM* theBoundary)
{
  return theBoundary->getArrayX();
}

int BoundariesMPM::getArrayY(BoundaryMPM* theBoundary)
{
  return theBoundary->getArrayY();
}

int BoundariesMPM::getArrayZ(BoundaryMPM* theBoundary)
{
  return theBoundary->getArrayZ();
}


SC_IntLineEdit* BoundariesMPM::getArrayXWidget(BoundaryMPM* theBoundary)
{
  return theBoundary->getArrayXWidget();
}

SC_IntLineEdit* BoundariesMPM::getArrayYWidget(BoundaryMPM* theBoundary)
{
  return theBoundary->getArrayYWidget();
}

SC_IntLineEdit* BoundariesMPM::getArrayZWidget(BoundaryMPM* theBoundary)
{
  return theBoundary->getArrayZWidget();
}

double BoundariesMPM::getSpacingX(BoundaryMPM* theBoundary)
{
  return theBoundary->getSpacingX();
}

double BoundariesMPM::getSpacingY(BoundaryMPM* theBoundary)
{
  return theBoundary->getSpacingY();
}

double BoundariesMPM::getSpacingZ(BoundaryMPM* theBoundary)
{
  return theBoundary->getSpacingZ();
}

SC_DoubleLineEdit* BoundariesMPM::getSpacingXWidget(BoundaryMPM* theBoundary)
{
  return theBoundary->getSpacingXWidget();
}

SC_DoubleLineEdit* BoundariesMPM::getSpacingYWidget(BoundaryMPM* theBoundary)
{
  return theBoundary->getSpacingYWidget();
}

SC_DoubleLineEdit* BoundariesMPM::getSpacingZWidget(BoundaryMPM* theBoundary)
{
  return theBoundary->getSpacingZWidget();
}


// bool BoundariesMPM::addBoundary(BoundaryMPM* theBoundary)


// bool
// BoundariesMPM::setBoundaryType(int typeIdx)
// {
//   int numInitialTabs = 4; // 4 default tabs
//   for (int i=0; i<numInitialTabs; i++) {
//     addedBoundary[i]->setBoundaryType(typeIdx);
//   }
//   return true;
// }

bool
BoundariesMPM::outputToJSON(QJsonObject &jsonObject)
{
  // TODO: Basic safety checks
  // Iterate over all tabs, fill a unique JSON object, and add to a JSON array
  QJsonArray theArray; // Holds array of boundary objects
  QJsonObject theObject; // Passed to individual boundary objects to fill
  for (int i=0; i<numAddedTabs; i++) {
    if (i >= numReserveTabs) break;
    addedBoundary[i]->outputToJSON(theObject);
    theArray.append(theObject["boundaries"].toArray());
  }
  theArray = theObject["boundaries"].toArray();
  jsonObject["boundaries"] = theArray; // Add array of boundary objects to the body object
  return true;
}

bool
BoundariesMPM::inputFromJSON(QJsonObject &jsonObject)
{
  // if (jsonObject.contains("domainSubType")) {
  //   QJsonValue theValue = jsonObject["domainSubType"];
  //   QString valueString = theValue.toString();
  //   facility->setCurrentText(valueString);
  // }
  // bathSTL->inputFromJSON(jsonObject);
  // paddleDisplacementFile->inputFromJSON(jsonObject);
  for (int i=0; i<numAddedTabs; i++) {
    if (i >= numReserveTabs) break; // Don't copy files for unreserved tabs
    addedBoundary[i]->inputFromJSON(jsonObject);
  }


  return true;
}


bool
BoundariesMPM::copyFiles(QString &destDir)
{
  // Copy files for each boundary tab to the destination directory
  bool flag = true; // copyFile returns false on error. So if any of these fail, flag will be false
  for (int i=0; i<numAddedTabs; i++) {
    if (i >= numReserveTabs) break; // Don't copy files for unreserved tabs
    flag &= addedBoundary[i]->copyFiles(destDir);
    
    // Perform copyFile on each added boundary tab's contained files (e.g. velocity motion, STL/OBJ, bathymetry file, etc.)
    // flag &= addedBoundary[i].velFile->copyFile(destDir);
    // flag &= addedBoundary[i].paddleDisplacementFile->copyFile(destDir);
    // flag &= addedBoundary[i].bathSTL->copyFile(destDir);
  }
  return flag; // True if all copyFile return true (i.e., no errors)
}

bool
BoundariesMPM::setDigitalTwin(int twinIdx)
{
  // Set digital twin facility
  for (int i=0; i<numAddedTabs; i++) {
    if (i >= numReserveTabs) break;
    // Wave flume facility tab, TODO: Refactor a bit
    addedBoundary[i]->setDigitalTwin(twinIdx);
  }
  return true;
}

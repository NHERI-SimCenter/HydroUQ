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

#include "PartitionsMPM.h"
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

#include <SC_ComboBox.h>
#include <SC_DoubleLineEdit.h>
#include <SC_IntLineEdit.h>
#include <SC_StringLineEdit.h>
#include <SC_TableEdit.h>
#include <SC_FileEdit.h>
#include <SC_CheckBox.h>

#include <PartitionMPM.h>

#include <vector>
#include <array>
#include <memory>

PartitionsMPM::PartitionsMPM(QWidget *parent)
  :SimCenterWidget(parent)
{
  // --- Partition
  QGridLayout *layout = new QGridLayout();
  this->setLayout(layout);

  int numRow = 0;
  
  // Buttons for creating and removing individual partition
  // All geometries will be composed together for an individual body to form a single partition
  QPushButton *addB = new QPushButton("Create Partition"); 
  QPushButton *delB = new QPushButton("Remove Partition");
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

  int numDefaultTabs = 1; // Need atleast one partition tab, so dont allow last one to be deleted
  QVector<QGridLayout*> theAddedLayout(numReserveTabs);
  QVector<QTabWidget*> modelAddedTabWidget(numReserveTabs); 
  for (int i = 0; i < numReserveTabs; i++) {
    theAdded[i] = new QWidget();
    theAddedLayout[i] = new QGridLayout();
    addedPartition[i] = new PartitionMPM();
  }

  // Init. first partition automatically
  tabWidget->addTab(theAdded[numAddedTabs], QIcon(QString(":/icons/user-black.svg")), "Custom " + QString::number(numAddedTabs + 1));
  tabWidget->setIconSize(QSize(sizeBodyTabs, sizeBodyTabs));
  theAdded[numAddedTabs]->setLayout(theAddedLayout[numAddedTabs]);
  theAddedLayout[numAddedTabs]->addWidget(addedPartition[numAddedTabs]);
  numAddedTabs += 1;
  // Create and Init. another partition tab at user request (click create)
  connect(addB, &QPushButton::released, this, [=]() {
    // Concatenate string to say "Custom Body 1", "Custom Body 2", etc.
    if (numAddedTabs >= numReserveTabs) 
      return;
    tabWidget->addTab(theAdded[numAddedTabs], QIcon(QString(":/icons/user-black.svg")), "Custom " + QString::number(numAddedTabs + 1));
    tabWidget->setIconSize(QSize(sizeBodyTabs, sizeBodyTabs));
    theAdded[numAddedTabs]->setLayout(theAddedLayout[numAddedTabs]);
    theAddedLayout[numAddedTabs]->addWidget(addedPartition[numAddedTabs]);
    numAddedTabs += 1;

    // Set the bodies new partition's GPU ID and Model ID (latter must be unique for the GPU ID)
    setPartitionGPU(numAddedTabs-1, numAddedTabs-1); // Set the GPU to the partition index
    // Note: setModel uses numAddedTabs for its iteration, so its position is important
    setDefaultModelID(defaultModelID); // Set the default model ID to the default model ID
    setModel(defaultModelID); // Set the model ID to the default model ID 
  });

  // Remove partition at user request (click remove)
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
  // Remove partition at user request (click the "X" mark on a tab)
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



}

PartitionsMPM::~PartitionsMPM()
{

}

bool 
PartitionsMPM::setPartitionGPU(int index, int gpu) 
{
  // Check if the index is valid
  if (index < 0 || index > numAddedTabs) {
    return false;
  }
  // Check if the GPU is valid
  if (gpu < 0 || gpu >= maxNumGPUs) {
    return false;
  }
  // Set the GPU
  addedPartition[index]->setGPU(gpu);
  
  return true;
}

bool 
PartitionsMPM::setModel(int model)
{
  // TODO: Better distribute models across GPUs relative to number of Bodies
  // Set the Model ID, iterating through partitions
  // Check model ID is valid (TODO: Fix upper-bound for diff. supercomputers / gpu-nodes)
  if (model < 0 || model >= maxNumModels*maxNumGPUs) {
    return false;
  }
  for (int i = 0; i < numAddedTabs; i++) {
    addedPartition[i]->setDefaultModelID(model);
    addedPartition[i]->setModel(model);
  }
  return true;
}

bool 
PartitionsMPM::setDefaultModelID(int model) 
{
  // Tell all partitions for this Body to use a given model ID
  defaultModelID = (model >= 0)  
                    ? ( (model < maxNumModels*maxNumGPUs) 
                      ? model 
                      : maxNumModels*maxNumGPUs) 
                    : 0;
  return true;
}

bool
PartitionsMPM::outputToJSON(QJsonObject &jsonObject)
{
  // TODO: Basic safety checks
  // Iterate over all tabs, fill a unique JSON object, and add to a JSON array
  QJsonArray theArray; // Holds array of partition objects
  for (int i=0; i<numAddedTabs; i++) {
    QJsonObject theObject; // Passed to individual partition objects to fill
    addedPartition[i]->outputToJSON(theObject);
    theArray.append(theObject["partition"].toObject());
  }
  jsonObject["partition"] = theArray; // Add array of partition objects to the body object
  jsonObject["gpu"] = 0; // TODO: ClaymoreUW has a single GPU ID per body, but will need to be updated to support multiple GPUs per body via unraveling the partition array
  jsonObject["model"] = defaultModelID; // Add default model ID to the body object
  // TODO: Same as for "gpu", get rid of ClaymoreUW global partition_start and partition_end
  // This is a temp fix.
  QJsonArray partition_start;
  QJsonArray partition_end;
  partition_start.append(0.0);
  partition_start.append(0.0);
  partition_start.append(0.0);
  partition_end.append(100.0);
  partition_end.append(4.5);
  partition_end.append(3.75);
  jsonObject["partition_start"] = partition_start;
  jsonObject["partition_end"] = partition_end;
  return true;
}

bool
PartitionsMPM::inputFromJSON(QJsonObject &jsonObject)
{
  return true;
}

bool
PartitionsMPM::copyFiles(QString &destDir)
{
  return true;
}


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
#include <QGridLayout>
#include <QWidget>

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
  tabWidget = new QTabWidget();
  tabWidget->setTabsClosable(true); // Close tabs with X mark via mouse (connect to tabCloseRequested)
  tabWidget->setMovable(true); // Move tabs with mouse


  int sizeBodyTabs = 20;
  layout->addWidget(tabWidget);

  int numDefaultTabs = 1; // Need atleast one partition tab, so dont allow last one to be deleted
  QVector<QTabWidget*> modelAddedTabWidget(numReserveTabs); 
  for (int i = 0; i < numReserveTabs; i++) {
    theAdded[i] = new QWidget();
    theAddedLayout[i] = new QGridLayout();
    addedPartition[i] = new PartitionMPM();
  }

  // Init. first partition automatically
  tabWidget->addTab(theAdded[numAddedTabs], QIcon(QString(":/icons/user-black.svg")), "GPU:Body " + QString::number(numAddedTabs + 1));
  tabWidget->setIconSize(QSize(sizeBodyTabs, sizeBodyTabs));
  theAdded[numAddedTabs]->setLayout(theAddedLayout[numAddedTabs]);
  theAddedLayout[numAddedTabs]->addWidget(addedPartition[numAddedTabs]);
  numAddedTabs += 1;
  
  // Create and Init. another partition tab at user request (click create)
  connect(addB, &QPushButton::released, this, [=]() {
    addPartition(numAddedTabs, defaultModelID); // Add the partition to the body
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

void PartitionsMPM::clear(void)
{
  // Clear all partitions
  // for (int i = 0; i < numAddedTabs; i++) {
  //   addedPartition[i]->clear();
  // }
  // // Clear the tab widget
  // tabWidget->clear();
  // numAddedTabs = 0;
}

void
PartitionsMPM::updateHardwareLimits(int maxGPUs = 1, int maxModels = 1)
{
  if (maxGPUs < 1) {
    qDebug() << "Maximum number of GPUs must be >= 1, but is " << maxGPUs << ".";
    return;
  }
  if (maxModels < 1) {
    qDebug() << "Maximum number of models must be >= 1, but is " << maxModels << ".";
    return;
  }
  maxNumGPUs = maxGPUs;
  maxNumModels = maxModels;
  return;
}

void 
PartitionsMPM::updateHardwareLimits(QString systemName = "Lonestar6", QString queueName = "gpu-a100")
{
  // Defaults
  maxNumGPUs = 1;
  maxNumModels = 3;
  // TODO: Account for --gres:gpu:N options on many HPC systems
  // TODO: Account for different GPU types and models, e.g. A100, H100, etc. or NVIDIA vs Intel vs AMD
  // Update the maximum number of GPUs and models based on the HPC system name
  if (systemName == "Lonestar6" || systemName == "LS6" || systemName == "ls6") {
    if (queueName == "gpu-a100" || queueName == "gpu-a100-dev" || queueName == "normal") {
      maxNumGPUs = 3;
      maxNumModels = 3;
      return;
    } else if (queueName == "gpu-a100-small" || queueName == "vm-small" || queueName == "small") {
      maxNumGPUs = 1;
      maxNumModels = 3;
      return;
    } else if (queueName == "gpu-h100") {
      maxNumGPUs = 2;
      maxNumModels = 3;
      return;
    }
  } else if (systemName == "Frontera" || systemName == "frontera" || systemName == "FRONTERA") {
    if (queueName == "rtx" || queueName == "rtx-dev") {
      maxNumGPUs = 4;
      maxNumModels = 3;
      return;
    } 
  } else if (systemName == "ACES" || systemName == "aces" || systemName == "Aces") {
    if (queueName == "gpu" || queueName == "gpu-h100" || queueName == "gpu-h100:2" || queueName == "normal") {
      maxNumGPUs = 2;
      maxNumModels = 3;
      return;
    } else if (queueName == "gpu-h100:4" || queueName == "large") {
      maxNumGPUs = 4; 
      maxNumModels = 3;
      return;
    }
  } else {
    qDebug() << "Requested unknown queue name: " << queueName << " for system: " << systemName << ". Using default values.";
    return;
  }
}

bool
PartitionsMPM::updateOccupiedModelsOnGPUs(int gpuIndex, int modelIndex, bool occupied)
{
  // Update the occupied models on GPUs
  if (gpuIndex < 0 || gpuIndex >= maxNumGPUs) {
    return false;
  }
  if (modelIndex < 0 || modelIndex >= maxNumModels) {
    return false;
  }
  occupiedModelsOnGPUs[gpuIndex][modelIndex] = occupied;
  return true;
}

bool 
PartitionsMPM::addPartition(int gpuID, int modelID)
{
  if (numAddedTabs >= numReserveTabs) 
    return false;
  
  bool results = true;
  // Add a partition to the body
  int sizeBodyTabs = 20;
  tabWidget->addTab(theAdded[numAddedTabs], QIcon(QString(":/icons/user-black.svg")), "GPU:Body " + QString::number(numAddedTabs + 1));
  tabWidget->setIconSize(QSize(sizeBodyTabs, sizeBodyTabs));
  theAdded[numAddedTabs]->setLayout(theAddedLayout[numAddedTabs]);
  theAddedLayout[numAddedTabs]->addWidget(addedPartition[numAddedTabs]);
  numAddedTabs += 1;

  // Set the bodies new partition's GPU ID and Model ID (latter must be unique for the GPU ID)
  results &= setPartitionGPU(numAddedTabs - 1, gpuID % maxNumGPUs); // Set the GPU to the partition index

  // Note: setModel uses numAddedTabs for its iteration, so its position is important
  results &= setPartitionModel(numAddedTabs - 1, modelID % maxNumModels); // Set the model ID to the default model ID 
  if (!results) 
    qDebug() << "Failed to add partition to body.";
  return results;
}


bool 
PartitionsMPM::setPartitionModel(int index, int model)
{
  if (index >= numReserveTabs) {
    qDebug() << "Partition index out of range of reserved tabs.";
    return false;
  }
  if (index < 0 || index >= numAddedTabs) {
    qDebug() << "Partition index out of range of added tabs.";
    return false;
  }
  if (model < 0 || model >= maxNumModels) {
    qDebug() << "Model index out of range of maximum models.";
    return false;
  }
  addedPartition[index]->setDefaultModelID(model);
  return addedPartition[index]->setModel(model);
}

bool 
PartitionsMPM::setPartitionGPU(int index, int gpu) 
{
  if (index >= numReserveTabs) {
    qDebug() << "Partition index out of range of reserved tabs.";
    return false;
  }
  if (index < 0 || index >= numAddedTabs) {
    qDebug() << "Partition index out of range of added tabs.";
    return false;
  }
  if (gpu < 0 || gpu >= maxNumGPUs) {
    qDebug() << "GPU index out of range of maximum GPUs.";
    return false;
  }

  return addedPartition[index]->setGPU(gpu);
}

bool 
PartitionsMPM::setModel(int model)
{
  // TODO: Better distribute models across GPUs relative to number of Bodies
  // Set the Model ID for a bodies' partitions, iterating through individual partition objects
  if (model < 0 || model >= maxNumModels) {
    qDebug() << "Model ID must be >= 0 and < " << maxNumModels << ", but is " << model << ".";
    return false;
  }
  bool results = true;
  for (int i = 0; i < numAddedTabs; i++) {
    addedPartition[i]->setDefaultModelID(model);
    results &= addedPartition[i]->setModel(model);
  }
  return results;
}

bool 
PartitionsMPM::setGPU(int gpu)
{
  if (gpu < 0 || gpu >= maxNumGPUs) {
    qDebug() << "GPU ID must be >= 0 and < " << maxNumGPUs << ", but is " << gpu << ".";
    return false;
  } 
  bool results = true;
  for (int i = 0; i < numAddedTabs; i++) {
    results &= addedPartition[i]->setGPU(gpu);
  }
  return results;
}

bool 
PartitionsMPM::setDefaultModelID(int model = 0) 
{
  defaultModelID = (model >= 0)  
                  ? ( (model < maxNumModels) ? model : maxNumModels - 1 ) // Assumes maxNumGPUs > 0
                  : 0;
  return (defaultModelID == model);
}

bool 
PartitionsMPM::setDefaultGPUID(int gpu = 0) 
{
  defaultGPUID = (gpu >= 0)  
                  ? ( (gpu < maxNumGPUs) ? gpu : maxNumGPUs - 1 ) // Assumes maxNumGPUs > 0
                  : 0;
  return (defaultGPUID == gpu);
}

bool
PartitionsMPM::balance(double origin[3], double dimensions[3])
{
  bool results = true;
  for (int i=0; i<numAddedTabs; i++) {
    results &= addedPartition[i]->balance(origin, dimensions, numAddedTabs, i);
  }
  return results;
}

bool
PartitionsMPM::outputToJSON(QJsonObject &jsonObject)
{
  const bool useUpdatedSchema = false; // TODO: Update to new schema

  // TODO: Basic safety checks
  // Iterate over all tabs, fill a unique JSON object, and add to a JSON array
  QJsonArray theArray; // Holds array of partition objects
  for (int i=0; i<numAddedTabs; i++) {
    QJsonObject theObject; // Passed to individual partition objects to fill
    addedPartition[i]->outputToJSON(theObject);
    theArray.append(theObject["partition"].toObject());
  }
  jsonObject["partition"] = theArray; // Add array of partition objects to the body object

  if (useUpdatedSchema) {
    jsonObject["device"] = 0; // TODO: ClaymoreUW has a single GPU ID per body, but will need to be updated to support multiple GPUs per body via unraveling the partition array
    jsonObject["body"] = defaultModelID; // Add default model ID to the body object
  } else {
    jsonObject["gpu"] = 0; // TODO: ClaymoreUW has a single GPU ID per body, but will need to be updated to support multiple GPUs per body via unraveling the partition array
    jsonObject["model"] = defaultModelID; // Add default model ID to the body object
  }

  // TODO: Same as for "gpu", get rid of ClaymoreUW global partition_start and partition_end
  QJsonArray partition_start;
  QJsonArray partition_end;
  partition_start.append(0.0);
  partition_start.append(0.0);
  partition_start.append(0.0);
  partition_end.append(90.0);
  partition_end.append(4.5);
  partition_end.append(3.65);
  jsonObject["partition_start"] = partition_start;
  jsonObject["partition_end"] = partition_end;
  return true;
}

bool
PartitionsMPM::inputFromJSON(QJsonObject &jsonObject)
{
  const bool useUpdatedSchema = false; // TODO: Update to new schema
  QJsonArray partition_start;  
  QJsonArray partition_end;
  QJsonArray partitions;
  
  // lambda
  auto lambdaInputFromJSON = [&](QJsonObject jsonRef) {
    QJsonObject jsonThing = jsonRef;
    // Following call of this lambda, the updated jsonThing is passed to inputFromJson() for an appropriate partition. Note we captured it as a reference
    jsonThing["valid"] = true; // Mark the partition as valid
    const int absMaxNumGPUs = 256; // Based on the NVIDIA H100 NV-Switch - NVLink topology, 256 values representable by one byte during multi-gpu communications
    const int absMaxNumModels = 8; // Based on fact that few GPUs have enough memory to allow more than 8 bodies to a device
    
    if (jsonThing.contains("partition") || jsonThing.contains("partitions")) {
      qDebug() << "ERROR: PartitionsMPM - Partition object or array found double-nested in input JSON partition or partitions. Not valid schema! Ignoring double-nested partitions...";
      // return false; // Not a big deal, should just ignore and move on to check for actual schema reqs
    } 
    // TODO: full schema migration for these keys, must be handled on external simulation application side as well or we will need to output all keys values for both schemas
    // TODO: QVariant for handling int, double, long, etc. types for numerical input along with string input (i.e. char) of '1', or 'one'
    if (useUpdatedSchema) {
      if (jsonThing.contains("device") && jsonThing["device"].isDouble()) {
        defaultGPUID = jsonThing["device"].toInt();
        defaultGPUID = (defaultGPUID < absMaxNumGPUs) ? defaultGPUID : absMaxNumGPUs - 1; // We may set the maxNumGPUs after inputJSON, so use an upper-bound check only here
        defaultGPUID = (defaultGPUID >= 0) ? defaultGPUID : 0;
      }
      if (jsonThing.contains("body") && jsonThing["body"].isDouble()) {
        defaultModelID = jsonThing["body"].toInt();
        defaultModelID = (defaultModelID < absMaxNumModels) ? defaultModelID : absMaxNumModels - 1;
      }
    } else {
      if (jsonThing.contains("gpu") && jsonThing["gpu"].isDouble()) {
        defaultGPUID = jsonThing["gpu"].toInt();
        defaultGPUID = (defaultGPUID < absMaxNumGPUs) ? defaultGPUID : absMaxNumGPUs - 1;
        defaultGPUID = (defaultGPUID >= 0) ? defaultGPUID : 0;
      } else {
        defaultGPUID = (defaultModelID < absMaxNumGPUs) ? defaultModelID : absMaxNumGPUs - 1;
        defaultGPUID = (defaultGPUID >= 0) ? defaultGPUID : 0;
      }

      if (jsonThing.contains("model") && jsonThing["model"].isDouble()) {
        defaultModelID = jsonThing["model"].toInt();
        defaultModelID = (defaultModelID < absMaxNumModels) ? defaultModelID : absMaxNumModels - 1;
        defaultModelID = (defaultModelID >= 0) ? defaultModelID : 0;
      } else {
        defaultModelID = (defaultGPUID < absMaxNumModels) ? defaultGPUID : absMaxNumModels - 1;
        defaultModelID = (defaultModelID >= 0) ? defaultModelID : 0;
      }
    }
    // Must have both partition_start and partition_end, and they must be arrays, or we will just assume a default domain partition to be safe
    if (jsonThing.contains("partition_start") && jsonThing.contains("partition_end") && jsonThing["partition_start"].isArray() && jsonThing["partition_end"].isArray()) {
      partition_start = jsonThing["partition_start"].toArray();
      partition_end = jsonThing["partition_end"].toArray();
      // Check invalid partition start and end values
      const int reqDims = 3;
      if (partition_start.size() < reqDims) {
        // Append 0.0 to the end of the array until it has 3 elements
        while (partition_start.size() < reqDims) {
          partition_start.append(0.0);
        }
      } else if (partition_start.size() > reqDims) {
        for (int i = partition_start.size() - 1; i > reqDims-1; i--) {
          partition_start.removeLast();
        }
      }
      if (partition_end.size() < reqDims) {
        // Append associated partition_start element + 1 to the end of the array until it has 3 elements
        const double bufferVal = 1.0; // Ensure non-inverted partition start and end values when appending synth. values
        while (partition_end.size() < reqDims) {
          partition_end.append(partition_start[partition_end.size()].toDouble() + bufferVal); // Ideally have bufferVal be the grid-cell size or particle spacing
        }
      } else if (partition_end.size() > reqDims) {
        for (int i = partition_end.size() - 1; i > reqDims-1; i--) {
          partition_end.removeLast();
        }
      }

      for (int i = 0; i < 3; i++) {
        // Check inverted partition start and end values
        if (partition_start[i].toDouble() > partition_end[i].toDouble()) {
          // Swap the values
          double temp = partition_start[i].toDouble();
          partition_start[i] = partition_end[i].toDouble();
          partition_end[i] = temp;
        }
      }
    } else {
      // OSU LWF default values
      qDebug() << "WARNING: PartitionsMPM - Pair of valid partition start and end values not found in input JSON partition. Using default partition start and end values for full domain...";
      partition_start = {0.0, 0.0, 0.0};
      partition_end = {90.0, 4.5, 3.65}; 
    }
    // ---
    // Set the values in the jsonObject that is passed to inputFromJson() for each partition
    // TODO: Only use device:body or gpu:model, etc., not both as schemas are updating
    jsonThing["device"] = defaultGPUID   % maxNumGPUs;
    jsonThing["body"]   = defaultModelID % maxNumModels;
    jsonThing["gpu"]    = defaultGPUID   % maxNumGPUs;
    jsonThing["model"]  = defaultModelID % maxNumModels;
    jsonThing["partition_start"] = partition_start;
    jsonThing["partition_end"]   = partition_end;
    jsonThing["valid"] = true; // Mark the partition as valid
    jsonRef = jsonThing; // Update the reference to the updated jsonThing
    // return jsonRef;
  }; // End lambda

  // Figure out if we are taking an array of partitions, a single one, none (i.e. default init), and check various boudnds

  if (jsonObject.contains("partition")) {
    jsonObject["partitions"] = jsonObject["partition"];
    if (jsonObject["partitions"].isArray()) {
      partitions = jsonObject["partitions"].toArray();
    } else if (jsonObject["partitions"].isObject()) {
      partitions.append(jsonObject["partitions"].toObject());
    } else {
      qDebug() << "ERROR: PartitionsMPM - No partition array or object found in input JSON object. It is non valid type: " << jsonObject["partitions"].type();
      return false; // Incorrect type in input JSON-- something went wrong, return a false as error marker
    }
  } else if (jsonObject.contains("partitions")) {
    if (jsonObject["partitions"].isArray()) {
      partitions = jsonObject["partitions"].toArray();
    } else if (jsonObject["partitions"].isObject()) {
      partitions.append(jsonObject["partitions"].toObject());
    } else {
      qDebug() << "ERROR: PartitionsMPM - No partition array or object found in input JSON object. It is non valid type: " << jsonObject["partitions"].type();
      return false; // Incorrect type in input JSON-- something went wrong, return a false as error marker
    }
  } else {
    qDebug() << "WARNING: PartitionsMPM - No partitions found in input JSON object.";
    // Not bad, assume no partition means default domain size and GPU/Device 0, Model/Body 0
  }


  if (!partitions.size()) {
    qDebug() << "WARNING: PartitionsMPM - No entries within partitions of JSON file. Use default partition on Device 0 : Body 0 over simulation domain";
    QJsonObject tmpPartition = QJsonObject();
    if (useUpdatedSchema) {
      tmpPartition["device"] = 0;
      tmpPartition["body"] = 0;
    } else {
      tmpPartition["gpu"] = 0;
      tmpPartition["model"] = 0;
    }
    tmpPartition["partition_start"] = partition_start;
    tmpPartition["partition_end"] = partition_end;
    partitions.append(tmpPartition);
    // Not bad, assume no partition means default domain size and GPU/Device 0, Model/Body 0
  } 
  
  if (numAddedTabs > partitions.size()) {
    for (int i = numAddedTabs; i > partitions.size(); i--) {
      tabWidget->removeTab(i); // Remove the exterior tab from the tabWidget
      numAddedTabs -= 1;
    }
  } else if (numAddedTabs < partitions.size()) {
    for (int i = numAddedTabs; i < partitions.size(); i++) {
      addPartition(defaultGPUID, defaultModelID); // Add the partition to the body
    }
  }
  bool result = true;
  for (int i = 0; i < partitions.size(); i++) {
    result &= partitions[i].isObject() ? true : false;
    if (!result) {
      qDebug() << "ERROR: PartitionsMPM - Partition " << i << " out of [0, " << partitions.size() << ") entries within JSON partitions array for this body is not an object. Type: " << partitions[i].type();
      return result;
    }
    // cast away 
    lambdaInputFromJSON(partitions[i].toObject());
    result &= partitions[i].toObject()["valid"].toBool();
    if (!result) {
      qDebug() << "ERROR: PartitionsMPM - Failed to load using lambdaInputFromJSON for partition" << i << " out of [0, " << partitions.size() << ") entries within JSON partitions array for this body.";
      return result;
    } 
    QJsonObject uniquePartitionObject = partitions[i].toObject();
    result &= addedPartition[i]->inputFromJSON(uniquePartitionObject);
    if (!result) {
      qDebug() << "ERROR: PartitionsMPM - Failed to load partition with data from JSON file via inputFromJSON(), error at partition " << i << " out of [0, " << partitions.size() << ") entries within JSON partitions array for this body.";
      return result;
    }
  }
  return result;
}

bool
PartitionsMPM::copyFiles(QString &destDir)
{
  return true;
}


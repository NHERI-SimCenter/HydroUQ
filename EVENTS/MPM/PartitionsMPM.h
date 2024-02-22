#ifndef PARTITIONS_MPM_H
#define PARTITIONS_MPM_H

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

/**
 *  @author  Justin Bonus
 *  @date    1/2024
 *  @version 3.0
 *
 *  @section DESCRIPTION
 *
 *  This is the class providing the set of GPU partitions for an MPM body
 */

#include <SimCenterWidget.h>
#include <vector>
#include <array>
class QJsonObject;
class QJsonArray;
class SC_DoubleLineEdit;
class SC_IntLineEdit;
class SC_StringLineEdit;
class SC_ComboBox;
class SC_TableEdit;
class SC_FileEdit;
class SC_CheckBox;
class QTabWidget;
class QGridLayout;
class QWidget;
class PartitionMPM; // Individual GPU partitions
class PartitionsMPM : public SimCenterWidget
{
public:
    PartitionsMPM(QWidget *parent = 0);
    virtual ~PartitionsMPM();
    bool outputToJSON(QJsonObject &jsonObject);
    bool inputFromJSON(QJsonObject &jsonObject);
    bool copyFiles(QString &dirName);

    void updateHardwareLimits(int numGPUs, int numModels);
    void updateHardwareLimits(QString computerName, QString queueName);
    bool updateOccupiedModelsOnGPUs(int gpuIndex, int modelIndex, bool occupied);
    bool addPartition(int gpuIndex, int modelIndex);

    bool setPartitionGPU(int partitionIndex, int gpuIndex);
    bool setPartitionModel(int partitionIndex, int modelIndex);
    bool setModel(int modelID);
    bool setGPU(int gpuID);
    bool setDefaultModelID(int modelID);
    bool setDefaultGPUID(int gpuID);
signals:

private:
  // Should probably make these unsigned integers, but its convenient to use negatives for error checking
  int maxNumGPUs = 3; //< Maximum number of GPUs supported, TODO: update according to settings:computer 
  int maxNumModels = 3; //< Maximum number of models supported, update according to settings:computer
  int defaultModelID = 0; // Default model ID, updated in setModel
  int defaultGPUID = 0; // Default GPU ID, updated in setGPU
  int numPartitions = 0; // Number of partitions, init. at 0
  int numReserveTabs = 8;
  int numAddedTabs = 0;
  QTabWidget *tabWidget;
  QVector<QWidget*> theAdded {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}; 
  QVector<QGridLayout*> theAddedLayout {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
  QVector<PartitionMPM*> addedPartition {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
  std::vector<std::array<bool, 3>> occupiedModelsOnGPUs = {{false, false, false}, {false, false, false}, {false, false, false}, {false, false, false}}; //< Occupied models on GPUs 
  // bool occupiedModelsOnGPUs[maxNumGPUs][maxNumModels] = {{false, false, false}, {false, false, false}, {false, false, false}, {false, false, false}}; //< Occupied models on GPUs
};

#endif // PARTITIONS_MPM_H


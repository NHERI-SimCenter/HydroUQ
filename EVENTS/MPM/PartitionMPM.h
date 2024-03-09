#ifndef PARTITION_MPM_H
#define PARTITION_MPM_H

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
 *  @author  fmckenna
 *  @date    2/2017
 *  @version 1.0
 *
 *  @section DESCRIPTION
 *
 *  This is the class providing the Partition Tab for mpm
 */

#include <SimCenterWidget.h>

class QJsonObject;
class QJsonArray;
class SC_DoubleLineEdit;
class SC_IntLineEdit;
class SC_StringLineEdit;
class SC_ComboBox;
class SC_TableEdit;
class SC_FileEdit;
class SC_CheckBox;

class PartitionMPM : public SimCenterWidget
{
public:
    PartitionMPM(QWidget *parent = 0);
    virtual ~PartitionMPM();
    bool outputToJSON(QJsonObject &jsonObject);
    bool inputFromJSON(QJsonObject &jsonObject);
    bool copyFiles(QString &dirName);

    bool setDefaultModelID(int modelID);
    bool setModel(int modelID);
    bool setDefaultGPUID(int gpuID);
    bool setGPU(int gpuID);

    int getModel();
    int getGPU();

    void constrainPartitionWithin(double origin[3], double dimensions[3]);
    void constrainPartitionOutside(double origin[3], double dimensions[3]);
    bool balance(double origin[3], double dimensions[3], int count, int id);
signals:

private:
  int numPartitions = 0; // Partition number on body, used to set GPU ID initially
  int defaultModelID = 0; // Default model ID, updated in setDefaultModelID
  int defaultGPUID = 0; // Default GPU ID, updated in setDefaultGPUID
  SC_IntLineEdit    *deviceNumber; // GPU device ID
  SC_IntLineEdit    *bodyNumber; // Model-body number-ID on GPU device
  SC_DoubleLineEdit *partitionOrigin_X; // GPU domain start X
  SC_DoubleLineEdit *partitionOrigin_Y; // GPU domain start Y
  SC_DoubleLineEdit *partitionOrigin_Z; // GPU domain start Z
  SC_DoubleLineEdit *partitionDimensions_X; // GPU domain end X
  SC_DoubleLineEdit *partitionDimensions_Y; // GPU domain end Y
  SC_DoubleLineEdit *partitionDimensions_Z; // GPU domain end Z
  SC_TableEdit      *devicePartitions; // GPU device partitions;  
};

#endif // PARTITION_MPM_H


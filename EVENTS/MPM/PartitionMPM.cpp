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

#include "PartitionMPM.h"
#include <QLabel>
#include <QComboBox>
#include <QGroupBox>
#include <QGridLayout>
#include <QTabWidget>
#include <QStackedWidget>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

#include <SC_ComboBox.h>
#include <SC_DoubleLineEdit.h>
#include <SC_IntLineEdit.h>
#include <SC_StringLineEdit.h>
#include <SC_TableEdit.h>
#include <SC_FileEdit.h>
#include <SC_CheckBox.h>


PartitionMPM::PartitionMPM(QWidget *parent)
  :SimCenterWidget(parent)
{
  QGridLayout *layout = new QGridLayout();
  this->setLayout(layout);

  int numRow = 0;

  // Update to reflect the number of GPUs on the machine
  deviceNumber = new SC_IntLineEdit("gpu", numPartitions);
  layout->addWidget(new QLabel("Set GPU Device ID"), numRow, 0);
  layout->itemAt(layout->count()-1)->setAlignment(Qt::AlignRight);
  layout->addWidget(deviceNumber, numRow, 1);
  layout->addWidget(new QLabel("[0,8)"),numRow++, 2);

  // Update to reflect the number of max material bodies ClaymoreUW is compiled for per GPU
  bodyNumber = new SC_IntLineEdit("model", defaultModelID);
  layout->addWidget(new QLabel("Body ID on GPU Device"), numRow, 0);
  layout->itemAt(layout->count()-1)->setAlignment(Qt::AlignRight);
  layout->addWidget(bodyNumber, numRow, 1);
  layout->addWidget(new QLabel("[0,3)"),numRow++, 2);

  // Update to constrain the partition origin to the simulation domain dimensions set in the settings tab
  partitionOrigin_X = new SC_DoubleLineEdit("partition_origin_x", 0.0);
  partitionOrigin_Y = new SC_DoubleLineEdit("partition_origin_y", 0.0);
  partitionOrigin_Z = new SC_DoubleLineEdit("partition_origin_z", 0.0);
  layout->addWidget(new QLabel("Partition Origin (X,Y,Z)"), numRow, 0);
  layout->itemAt(layout->count()-1)->setAlignment(Qt::AlignRight);
  layout->addWidget(partitionOrigin_X, numRow, 1);
  layout->addWidget(partitionOrigin_Y, numRow, 2);
  layout->addWidget(partitionOrigin_Z, numRow, 3);
  layout->addWidget(new QLabel("m"),numRow++, 4);

  // TODO: Update default to the simulation domain dimensions set in the settings tab
  partitionDimensions_X = new SC_DoubleLineEdit("partition_dimensions_x", 90.0);
  partitionDimensions_Y = new SC_DoubleLineEdit("partition_dimensions_y", 2.9);
  partitionDimensions_Z = new SC_DoubleLineEdit("partition_dimensions_z", 3.65);
  layout->addWidget(new QLabel("Partition Dimensions (X,Y,Z)"), numRow, 0);
  layout->itemAt(layout->count()-1)->setAlignment(Qt::AlignRight);
  layout->addWidget(partitionDimensions_X, numRow, 1);
  layout->addWidget(partitionDimensions_Y, numRow, 2);
  layout->addWidget(partitionDimensions_Z, numRow, 3);
  layout->addWidget(new QLabel("m"),numRow++, 4);

  layout->setRowStretch(numRow,1);
}


PartitionMPM::~PartitionMPM()
{

}


bool
PartitionMPM::setModel(int model) 
{
  if (model < 0) {
    qDebug() << "PartitionMPM::setModel(), " << "Must have Model ID >= 0, but ID is " << model << ".";
    return false;
  }
  bodyNumber->setText(QString::number(model));
  return true;
}

bool
PartitionMPM::setGPU(int gpu) 
{
  if (gpu < 0) {
    qDebug() << "PartitionMPM::setGPU(), " << "Must have GPU ID >= 0, but ID is " << gpu << ".";
    return false;
  }
  deviceNumber->setText(QString::number(gpu));
  return true;
}

bool
PartitionMPM::setDefaultModelID(int model) 
{
  defaultModelID = (model >= 0) ? model : 0; // Assume check for upper-bound done in PartitionsMPM
  return (defaultModelID == model);
}

bool
PartitionMPM::setDefaultGPUID(int gpu) 
{
  defaultGPUID = (gpu >= 0) ? gpu : 0; // Assume check for upper-bound done in PartitionsMPM
  return (defaultGPUID == gpu);
}

int PartitionMPM::getModel() 
{
  return bodyNumber->text().toInt();
}

int PartitionMPM::getGPU() 
{
  return deviceNumber->text().toInt();
}

void 
PartitionMPM::constrainPartitionWithin(double origin[3], double dimensions[3])
{
  if (partitionOrigin_X->text().toDouble() < origin[0] || partitionOrigin_X->text().toDouble() > origin[0] + dimensions[0])
    partitionOrigin_X->setText(QString::number(origin[0]));
  if (partitionOrigin_Y->text().toDouble() < origin[1] || partitionOrigin_Y->text().toDouble() > origin[1] + dimensions[1])
    partitionOrigin_Y->setText(QString::number(origin[1]));
  if (partitionOrigin_Z->text().toDouble() < origin[2] || partitionOrigin_Z->text().toDouble() > origin[2] + dimensions[2])
    partitionOrigin_Z->setText(QString::number(origin[2]));
  
  if (partitionOrigin_X->text().toDouble() + partitionDimensions_X->text().toDouble() > dimensions[0] || partitionDimensions_X->text().toDouble() < 0)
    partitionDimensions_X->setText(QString::number(dimensions[0] - ( partitionOrigin_X->text().toDouble() - origin[0] ) ));
  if (partitionOrigin_Y->text().toDouble() + partitionDimensions_Y->text().toDouble() > dimensions[1] || partitionDimensions_Y->text().toDouble() < 0)
    partitionDimensions_Y->setText(QString::number(dimensions[1] - ( partitionOrigin_Y->text().toDouble() - origin[1] ) ));
  if (partitionOrigin_Z->text().toDouble() + partitionDimensions_Z->text().toDouble() > dimensions[2] || partitionDimensions_Z->text().toDouble() < 0)
    partitionDimensions_Z->setText(QString::number(dimensions[2] - ( partitionOrigin_Z->text().toDouble() - origin[2] ) ));
  return;
}

void 
PartitionMPM::constrainPartitionOutside(double origin[3], double dimensions[3])
{
  if (partitionOrigin_X->text().toDouble() < origin[0] || partitionOrigin_X->text().toDouble() > origin[0] + dimensions[0])
  {
    if (partitionOrigin_X->text().toDouble() < origin[0])
    {
      partitionOrigin_X->setText(QString::number(origin[0]));
      if (partitionOrigin_X->text().toDouble() + partitionDimensions_X->text().toDouble() > origin[0] + dimensions[0] || partitionDimensions_X->text().toDouble() < 0)
        partitionDimensions_X->setText(QString::number(origin[0] - partitionOrigin_X->text().toDouble()));
    }
    else
      partitionOrigin_X->setText(QString::number(origin[0] + dimensions[0]));
  }
  if (partitionOrigin_Y->text().toDouble() < origin[1] || partitionOrigin_Y->text().toDouble() > origin[1] + dimensions[1])
  {
    if (partitionOrigin_Y->text().toDouble() < origin[1]) 
    {
      partitionOrigin_Y->setText(QString::number(origin[1]));
      if (partitionOrigin_Y->text().toDouble() + partitionDimensions_Y->text().toDouble() > origin[1] + dimensions[1] || partitionDimensions_Y->text().toDouble() < 0)
        partitionDimensions_Y->setText(QString::number(origin[1] - partitionOrigin_Y->text().toDouble()));
    }
    else
      partitionOrigin_Y->setText(QString::number(origin[1] + dimensions[1]));
  }
  if (partitionOrigin_Z->text().toDouble() < origin[2] || partitionOrigin_Z->text().toDouble() > origin[2] + dimensions[2])
  {
    if (partitionOrigin_Z->text().toDouble() < origin[2]) 
    {
      partitionOrigin_Z->setText(QString::number(origin[2]));
      if (partitionOrigin_Z->text().toDouble() + partitionDimensions_Z->text().toDouble() > origin[2] + dimensions[2] || partitionDimensions_Z->text().toDouble() < 0)
        partitionDimensions_Z->setText( QString::number(origin[2] - partitionOrigin_Z->text().toDouble()));
    }
    else
      partitionOrigin_Z->setText(QString::number(origin[2] + dimensions[2]));
  }
  return;
}


bool
PartitionMPM::outputToJSON(QJsonObject &jsonObject)
{
  QJsonObject partitionObject;

  // Note: ClaymoreUW will also need these defined in the JSON model/body object, not just the nested JSON partition/device object
  partitionObject["gpu"] = deviceNumber->text().toInt();
  partitionObject["model"] = bodyNumber->text().toInt();

  // Future schema
  if (0) {
    QJsonArray partitionOrigin;
    partitionOrigin.append(partitionOrigin_X->text().toDouble());
    partitionOrigin.append(partitionOrigin_Y->text().toDouble());
    partitionOrigin.append(partitionOrigin_Z->text().toDouble());
    partitionObject["partition_origin"] = partitionOrigin;

    QJsonArray partitionDimensions;
    partitionDimensions.append(partitionDimensions_X->text().toDouble());
    partitionDimensions.append(partitionDimensions_Y->text().toDouble());
    partitionDimensions.append(partitionDimensions_Z->text().toDouble());
    partitionObject["partition_dimensions"] = partitionDimensions;
  }
  // ClaymoreUW artifacts, to be deprecated
  QJsonArray partition_start;
  partition_start.append(partitionOrigin_X->text().toDouble());
  partition_start.append(partitionOrigin_Y->text().toDouble());
  partition_start.append(partitionOrigin_Z->text().toDouble());
  partitionObject["partition_start"] = partition_start;

  QJsonArray partition_end; 
  partition_end.append(partitionOrigin_X->text().toDouble() + partitionDimensions_X->text().toDouble());
  partition_end.append(partitionOrigin_Y->text().toDouble() + partitionDimensions_Y->text().toDouble());
  partition_end.append(partitionOrigin_Z->text().toDouble() + partitionDimensions_Z->text().toDouble());
  partitionObject["partition_end"] = partition_end;
  
  jsonObject["partition"] = partitionObject;
  return true;
}

bool
PartitionMPM::inputFromJSON(QJsonObject &jsonObject)
{
  return true;
}

bool
PartitionMPM::copyFiles(QString &destDir)
{ 
  return true;
}


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

  // --- Partition
  QGridLayout *layout = new QGridLayout();
  this->setLayout(layout);

  int numRow = 0;


  deviceNumber = new SC_IntLineEdit("gpu", 0);
  layout->addWidget(new QLabel("Set GPU Device ID"), numRow, 0);
  layout->addWidget(deviceNumber, numRow, 1);
  layout->addWidget(new QLabel("[0,8)"),numRow++, 2);

  bodyNumber = new SC_IntLineEdit("model", 0);
  layout->addWidget(new QLabel("Set Body ID on GPU Device"), numRow, 0);
  layout->addWidget(bodyNumber, numRow, 1);
  layout->addWidget(new QLabel("[0,3)"),numRow++, 2);

  QStringList devicePartitionsHeadings; devicePartitionsHeadings << "Start [m]" << "End [m]";
  QStringList devicePartitionsDimensions; devicePartitionsDimensions << "0" << "0" << "1" << "1" << "2" << "2" << "3" << "3";
  devicePartitions = new SC_TableEdit("partition_start", devicePartitionsHeadings, 4, devicePartitionsDimensions);

  layout->addWidget(new QLabel("GPU Device Partitions"),(numRow + 3),0,1,4);    
  layout->addWidget(devicePartitions,(numRow + 4),0,1,4);  

  // layout->setRowStretch(numRow,1);

  // Debris Geometry File = new SC_FileEdit("file");
  // debrisGeometryLayout->addWidget(new QLabel("Debris Geometry File"),numRow, 0);
  // debrisGeometryLayout->addWidget(Debris Geometry File,numRow++, 1);  

  // // connext bathymetry to show correct widget
  // connect(waveGenComboBox, QOverload<int>::of(&QComboBox::activated),
	//   waveGenStack, &QStackedWidget::setCurrentIndex);
  // */

}

PartitionMPM::~PartitionMPM()
{

}

bool
PartitionMPM::outputToJSON(QJsonObject &jsonObject)
{
  // theOpenSeesPyScript->outputToJSON(jsonObject);
  // theSurfaceFile->outputToJSON(jsonObject);  
  return true;
}

bool
PartitionMPM::inputFromJSON(QJsonObject &jsonObject)
{
  // theOpenSeesPyScript->inputFromJSON(jsonObject);
  // theSurfaceFile->inputFromJSON(jsonObject);    
  return true;
}

bool
PartitionMPM::copyFiles(QString &destDir)
{
  // if (theOpenSeesPyScript->copyFile(destDir) != true)
  //   return false;
  // return theSurfaceFile->copyFile(destDir);    
  return true;
}


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

THIS SSensorsTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES Sensors MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPBodiesE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT Sensors SUBSTITUTE GOODS OR SERVICES;
LBodiesS Sensors USE, DATA, OR PRSensorsITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY Sensors LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT Sensors THE USE Sensors THIS
SSensorsTWARE, EVEN IF ADVISED Sensors THE PBodiesSIBILITY Sensors SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of the FreeBSD Project.

REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
THE IMPLIED WARRANTIES Sensors MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPBodiesE.
THE SSensorsTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED HEREUNDER IS 
PROVIDED "AS IS". REGENTS HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, 
UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

*************************************************************************** */


#include <ExecutionSPH.h>
#include <QGroupBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QStringList>
#include <QJsonObject>
#include <QJsonArray>
#include <QTabWidget>
#include <QVector>
#include <QStringList>

#include <SC_TableEdit.h>
#include <SC_ComboBox.h>
#include <SC_DoubleLineEdit.h>
#include <SC_CheckBox.h>


ExecutionSPH::ExecutionSPH(QWidget *parent)
  :SimCenterWidget(parent)
{

  //
  // create all little widgets
  //
  int maxWidth = 1280;
  int numRow = 0;
  QStringList yesNo; yesNo << "Yes" << "No";
  QStringList particleExt; particleExt << "BGEO" << "GEO" << "CSV" << "TXT"; // VTK
  QStringList checkpointsExt; checkpointsExt << "BGEO" << "GEO" << "CSV" << "TXT"; // VTK
  QStringList boundariesExt; boundariesExt << "OBJ" ;
  QStringList sensorExt; sensorExt << "CSV" << "TXT";
  QStringList energiesExt; energiesExt << "CSV" << "TXT";



  vtkBodies_Output = new SC_ComboBox("bodies_save_suffix", particleExt);  
  vtkCheckpoints_Output = new SC_ComboBox("checkpoints_save_suffix", checkpointsExt);
  vtkBoundaries_Output = new SC_ComboBox("boundaries_save_suffix", boundariesExt);
  vtkSensors_Output = new SC_ComboBox("sensors_save_suffix", sensorExt);
  vtkEnergies_Output = new SC_ComboBox("energies_save_suffix", energiesExt);

  outputBodies_Dt  = new SC_DoubleLineEdit("bodies_output_freq", 10);
  outputBoundaries_Dt  = new SC_DoubleLineEdit("boundaries_output_freq", 30);
  // outputSensors_Dt  = new SC_DoubleLineEdit("sensors_output_freq", 30);
  outputCheckpoints_Dt  = new SC_DoubleLineEdit("checkpoints_output_freq", 1);
  outputEnergies_Dt = new SC_DoubleLineEdit("energies_output_freq", 30);

  useKineticEnergy = new SC_CheckBox("useKineticEnergy");
  usePotentialEnergy = new SC_CheckBox("usePotentialEnergy");
  useStrainEnergy = new SC_CheckBox("useStrainEnergy");

  bodies_OutputExteriorOnly = new SC_CheckBox("particles_output_exterior_only");
  bodies_OutputExteriorOnly->setChecked(false);



  // --- Bodies
  numRow = 0;
  QGroupBox *bodiesBox = new QGroupBox("Bodies");
  QGridLayout *bodiesLayout = new QGridLayout();  
  bodiesBox->setLayout(bodiesLayout);
  bodiesLayout->addWidget(new QLabel("Output File Type"), numRow, 0, 1, 1, Qt::AlignRight);
  bodiesLayout->addWidget(vtkBodies_Output, numRow, 1, 1, 3);  
  bodiesLayout->setColumnStretch(1, 1); // Expand the middle column
  bodiesLayout->itemAt(bodiesLayout->count()-1)->widget()->setMaximumWidth(maxWidth);
  bodiesLayout->addWidget(new QLabel(""), numRow++, 4, 1, 1);

  bodiesLayout->addWidget(new QLabel("Output Frequency"), numRow, 0, 1, 1, Qt::AlignRight);
  bodiesLayout->addWidget(outputBodies_Dt, numRow, 1, 1, 3);
  bodiesLayout->itemAt(bodiesLayout->count()-1)->widget()->setMaximumWidth(maxWidth);
  bodiesLayout->addWidget(new QLabel("Hz"), numRow++, 4, 1, 1);  


  QStringList bodiesAttribsHeadings; bodiesAttribsHeadings << "1st" << "2nd" << "3rd" << "4th" << "5th";
  QStringList bodiesAttribsStrings; bodiesAttribsStrings << "ID" << "Pressure" << "" << "" << "" 
                                     << "ID" << "Pressure" << "Velocity_X" << "Velocity_Y" << "Velocity_Z" 
                                     << "ID" << "Pressure" << "VonMisesStress" << "DefGrad_Invariant2" << "DefGrad_Invariant3" ;
  bodiesAttribsTable = new SC_TableEdit("bodiesAttribsTable", bodiesAttribsHeadings, 3, bodiesAttribsStrings);
  bodiesLayout->addWidget(new QLabel("Output Attributes"), numRow, 0, 1, 1, Qt::AlignRight);
  bodiesLayout->addWidget(bodiesAttribsTable,numRow++, 1, 1, 3);
  bodiesLayout->itemAt(bodiesLayout->count()-1)->widget()->setMaximumWidth(maxWidth);

  bodiesLayout->addWidget(new QLabel("Only Save Exterior"), numRow, 0, 1, 1, Qt::AlignRight);
  bodiesLayout->addWidget(bodies_OutputExteriorOnly, numRow++, 1, 1, 3);
  bodiesLayout->itemAt(bodiesLayout->count()-1)->widget()->setMaximumWidth(maxWidth);

  // bodiesLayout->setRowStretch(numRow, 1);

  // --- Checkpoint-Resume
  numRow = 0;
  QGroupBox *checkpointBox = new QGroupBox("Checkpoint-Resume State");
  QGridLayout *checkpointLayout = new QGridLayout();  
  checkpointBox->setLayout(checkpointLayout);
  checkpointLayout->addWidget(new QLabel("Output File Type"), numRow, 0, 1, 1, Qt::AlignRight);
  checkpointLayout->addWidget(vtkCheckpoints_Output, numRow, 1, 1, 3);
  checkpointLayout->setColumnStretch(1, 1); // Expand the middle column
  checkpointLayout->itemAt(checkpointLayout->count()-1)->widget()->setMaximumWidth(maxWidth);
  checkpointLayout->addWidget(new QLabel(""), numRow++, 4, 1, 1);

  checkpointLayout->addWidget(new QLabel("Output Frequency"), numRow, 0, 1, 1, Qt::AlignRight);
  checkpointLayout->addWidget(outputCheckpoints_Dt, numRow, 1, 1, 3);
  checkpointLayout->itemAt(checkpointLayout->count()-1)->widget()->setMaximumWidth(maxWidth);
  checkpointLayout->addWidget(new QLabel("Hz"), numRow++, 4, 1, 1);
  checkpointLayout->setRowStretch(numRow, 1);

  // --- Boundaries
  numRow = 0;
  QGroupBox *boundariesBox = new QGroupBox("Boundaries");
  QGridLayout *boundariesLayout = new QGridLayout();  
  boundariesBox->setLayout(boundariesLayout);

  boundariesLayout->addWidget(new QLabel("Output File Type"), numRow, 0, 1, 1, Qt::AlignRight);
  boundariesLayout->addWidget(vtkBoundaries_Output, numRow, 1, 1, 3); 
  boundariesLayout->setColumnStretch(1, 1); // Expand the middle column
  boundariesLayout->itemAt(boundariesLayout->count()-1)->widget()->setMaximumWidth(maxWidth);
  boundariesLayout->addWidget(new QLabel(""), numRow++, 4, 1, 1);   

  boundariesLayout->addWidget(new QLabel("Output Frequency"), numRow, 0, 1, 1, Qt::AlignRight);
  boundariesLayout->addWidget(outputBoundaries_Dt, numRow, 1, 1, 3);
  boundariesLayout->itemAt(boundariesLayout->count()-1)->widget()->setMaximumWidth(maxWidth);
  boundariesLayout->addWidget(new QLabel("Hz"), numRow++, 4, 1, 1);
  boundariesLayout->setRowStretch(numRow, 1);

  // --- Sensors
  numRow = 0;
  QGroupBox *sensorsBox = new QGroupBox("Sensors");
  QGridLayout *sensorsLayout = new QGridLayout();  
  sensorsBox->setLayout(sensorsLayout);
  sensorsLayout->addWidget(new QLabel("Output File Type"), numRow, 0, 1, 1, Qt::AlignRight);
  sensorsLayout->addWidget(vtkSensors_Output, numRow, 1, 1, 3); 
  sensorsLayout->setColumnStretch(1, 1); // Expand the middle column
  sensorsLayout->itemAt(sensorsLayout->count()-1)->widget()->setMaximumWidth(maxWidth);   
  sensorsLayout->addWidget(new QLabel("  "), numRow++, 4, 1, 1);
  sensorsLayout->setRowStretch(numRow, 1);

  // --- Energies
  numRow = 0;
  QGroupBox *energiesBox = new QGroupBox("Energies");
  QGridLayout *energiesLayout = new QGridLayout();  
  energiesBox->setLayout(energiesLayout);
  energiesLayout->addWidget(new QLabel("Output File Type"), numRow, 0, 1, 1, Qt::AlignRight);
  energiesLayout->addWidget(vtkEnergies_Output, numRow, 1, 1, 3);
  energiesLayout->setColumnStretch(1, 1); // Expand the middle column
  energiesLayout->itemAt(energiesLayout->count()-1)->widget()->setMaximumWidth(maxWidth);
  energiesLayout->addWidget(new QLabel(""), numRow++, 4, 1, 1);

  energiesLayout->addWidget(new QLabel("Output Frequency"), numRow, 0, 1, 1, Qt::AlignRight);
  energiesLayout->addWidget(outputEnergies_Dt, numRow, 1, 1, 3);
  energiesLayout->itemAt(energiesLayout->count()-1)->widget()->setMaximumWidth(maxWidth);
  energiesLayout->addWidget(new QLabel("Hz"), numRow++, 4, 1, 1);

  energiesLayout->addWidget(new QLabel("Output Kinetic?"), numRow, 0, 1, 1, Qt::AlignRight);
  energiesLayout->addWidget(useKineticEnergy, numRow++, 1, 1, 3);
  energiesLayout->addWidget(new QLabel("Output Gravity?"), numRow, 0, 1, 1, Qt::AlignRight);
  energiesLayout->addWidget(usePotentialEnergy, numRow++, 1, 1, 3);
  energiesLayout->addWidget(new QLabel("Output Strain?"),  numRow, 0, 1, 1, Qt::AlignRight);
  energiesLayout->addWidget(useStrainEnergy, numRow++, 1, 1, 3);
  energiesLayout->setRowStretch(numRow, 1);

  //
  // now boxes to this widget
  //
  numRow = 0;
  QGridLayout *layout = new QGridLayout();
  layout->addWidget(bodiesBox, numRow++, 0);
  layout->addWidget(checkpointBox, numRow++, 0);
  layout->addWidget(boundariesBox, numRow++, 0);
  layout->addWidget(sensorsBox, numRow++, 0);
  layout->addWidget(energiesBox, numRow++, 0);
  layout->setRowStretch(numRow, 1);
  this->setLayout(layout);
}

ExecutionSPH::~ExecutionSPH()
{

}

bool
ExecutionSPH::outputToJSON(QJsonObject &jsonObject)
{
  QJsonObject outputsObject;

  // New schema
  outputsObject["bodies_save_suffix"] = vtkBodies_Output->itemText(vtkBodies_Output->currentIndex());
  outputsObject["checkpoints_save_suffix"] = vtkCheckpoints_Output->itemText(vtkCheckpoints_Output->currentIndex());
  outputsObject["boundaries_save_suffix"] = vtkBoundaries_Output->itemText(vtkBoundaries_Output->currentIndex());
  outputsObject["sensors_save_suffix"] = vtkSensors_Output->itemText(vtkSensors_Output->currentIndex());
  outputsObject["energies_save_suffix"] = vtkEnergies_Output->itemText(vtkEnergies_Output->currentIndex());

  outputsObject["bodies_output_freq"] = outputBodies_Dt->text().toDouble();
  outputsObject["checkpoints_output_freq"] = outputCheckpoints_Dt->text().toDouble();
  outputsObject["boundaries_output_freq"] = outputBoundaries_Dt->text().toDouble();
  outputsObject["energies_output_freq"] = outputEnergies_Dt->text().toDouble();

  outputsObject["useKineticEnergy"] = useKineticEnergy->isChecked();
  outputsObject["usePotentialEnergy"] = usePotentialEnergy->isChecked();
  outputsObject["useStrainEnergy"] = useStrainEnergy->isChecked();
  outputsObject["particles_output_exterior_only"] = bodies_OutputExteriorOnly->isChecked();

  // Each row of table becomes an array of strings, all arrays occupy a single array called "output_attribs"
  // In-post, sort each array element (i.e. row of table) into the appropiate JSON body object based on the row order
  // I.e., row 1 of table is added to the first JSON body object (should correspond to tab order I think)
  // TODO: Refactor to better couple to bodies, not good to rely on sequential ordering
  QJsonObject bodiesAttribsObject;
  QJsonArray bodiesAttribsArray;
  bodiesAttribsTable->outputToJSON(bodiesAttribsObject);
  for (int i = 0; i < bodiesAttribsObject["bodiesAttribsTable"].toArray().size(); i++) {
    QJsonArray temp_array = bodiesAttribsObject["bodiesAttribsTable"].toArray()[i].toArray();
    for (int j = 0; j < temp_array.size(); j++) {
      if (temp_array[j].toString().isEmpty()) {
        temp_array.removeAt(j);
        j--;
      }
    }
    bodiesAttribsArray.append(temp_array);
  }
  outputsObject["output_attribs"] = bodiesAttribsArray;

  jsonObject["outputs"] = outputsObject;

  // ClaymoreUW artifacts, will deprecate. These are moved into the "simulation" settings object 
  jsonObject["save_suffix"] = vtkBodies_Output->itemText(vtkBodies_Output->currentIndex());
  jsonObject["fps"] = outputBodies_Dt->text().toDouble();
  jsonObject["particles_output_exterior_only"] = bodies_OutputExteriorOnly->isChecked();
  return true;
}

bool
ExecutionSPH::inputFromJSON(QJsonObject &jsonObject)
{

  // vtkBodies_Output->inputFromJSON(jsonObject);  
  // vtkSensors_Output->inputFromJSON(jsonObject);
  // outputBodies_Dt->inputFromJSON(jsonObject);
  // outputSensors_Dt->inputFromJSON(jsonObject);
  // outputSensors_FM->inputFromJSON(jsonObject);
  // outputSensors_FSP->inputFromJSON(jsonObject);
  // outputSensors_FP->inputFromJSON(jsonObject);
  // outputSensors_SC->inputFromJSON(jsonObject);
  // freeSurfaceProbes->inputFromJSON(jsonObject);
  // fieldProbes->inputFromJSON(jsonObject);
  // sectionCuts->inputFromJSON(jsonObject);
  
  return true;
}


#ifndef SENSOR_MPM_H
#define SENSOR_MPM_H

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
 *  @author  JustinBonus
 *  @date    1/2024
 *  @version 4.0
 *
 *  @section DESCRIPTION
 *
 *  This is the class providing an individual Sensor for MPM
 */

#include <SimCenterWidget.h>

class QJsonObject;
class QJsonArray;
class QStackedWidget;
class QGroupBox;
class SC_DoubleLineEdit;
class SC_IntLineEdit;
class SC_ComboBox;
class SC_TableEdit;
class SC_FileEdit;
class SC_CheckBox;
class SC_ComboBox;
class QGridLayout;

class SensorMPM : public SimCenterWidget
{
    Q_OBJECT

public:
    SensorMPM(QWidget *parent = 0);
    virtual ~SensorMPM();
    void clear(void);
    bool outputToJSON(QJsonObject &jsonObject);
    bool inputFromJSON(QJsonObject &jsonObject);
    bool copyFiles(QString &dirName);

    bool setSensorType(int type);
  
signals:

private:
  // Wave-gauges (WG), Velocimeters (VM), and Load-cells (LC)
  SC_ComboBox       *sensorType; // Preset selector
  QStackedWidget    *stackedWidget;

  SC_ComboBox       *toggle;
  SC_ComboBox       *type;
  SC_ComboBox       *attribute;
  SC_ComboBox       *operation;
  SC_ComboBox       *direction;
  SC_DoubleLineEdit *output_frequency;
  SC_TableEdit      *customTable;

  SC_ComboBox       *toggleWG;
  SC_ComboBox       *typeWG;
  SC_ComboBox       *attributeWG;
  SC_ComboBox       *operationWG;
  SC_ComboBox       *directionWG;
  SC_DoubleLineEdit *output_frequencyWG;
  SC_TableEdit      *waveGaugesTable;
  
  SC_ComboBox       *toggleVM;
  SC_ComboBox       *typeVM;
  SC_ComboBox       *attributeVM;
  SC_ComboBox       *operationVM;
  SC_ComboBox       *directionVM;
  SC_DoubleLineEdit *output_frequencyVM;
  SC_TableEdit      *velociMetersTable;

  SC_ComboBox       *toggleLC;
  SC_ComboBox       *typeLC;
  SC_ComboBox       *attributeLC;
  SC_ComboBox       *operationLC;
  SC_ComboBox       *directionLC;
  SC_DoubleLineEdit *output_frequencyLC;
  SC_TableEdit      *loadCellsTable;

  SC_ComboBox       *togglePM;
  SC_ComboBox       *typePM;
  SC_ComboBox       *attributePM;
  SC_ComboBox       *operationPM;
  SC_ComboBox       *directionPM;
  SC_DoubleLineEdit *output_frequencyPM;
  SC_TableEdit      *piezoMetersTable;


  QWidget *theCustom;
  QWidget *theWaveGauges;
  QWidget *theVelocityMeters; 
  QWidget *theLoadCells; 
  QWidget *thePiezoMeters;
  QGridLayout *customLayout;
  QGridLayout *wgLayout;
  QGridLayout *vmLayout;
  QGridLayout *lcLayout;
  QGridLayout *pmLayout;
};

#endif // SENSOR_MPM_H


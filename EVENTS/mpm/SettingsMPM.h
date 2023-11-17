#ifndef SETTINGS_MPM_H
#define SETTINGS_MPM_H

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
 *  This is the class providing the Settings Tab for the CoupledDigitalTwin
 */

#include <SimCenterWidget.h>

class QJsonObject;
class SC_DoubleLineEdit;
class SC_IntLineEdit;
class SC_CheckBox;

class SettingsMPM : public SimCenterWidget
{
public:
    SettingsMPM(QWidget *parent = 0);
    virtual ~SettingsMPM();
    bool outputToJSON(QJsonObject &jsonObject);
    bool inputFromJSON(QJsonObject &jsonObject);

signals:

private:

  SC_DoubleLineEdit *domainSizeX;
  SC_DoubleLineEdit *domainSizeY;
  SC_DoubleLineEdit *domainSizeZ;  
  
  SC_DoubleLineEdit *gridCellSize;  
  SC_DoubleLineEdit *timeStep;
  SC_DoubleLineEdit *duration;
  SC_DoubleLineEdit *initialTime;  
  SC_IntLineEdit    *framesPerSecond;
  SC_CheckBox       *mirrorDomain;  
  SC_DoubleLineEdit *gravity;
  SC_DoubleLineEdit *lengthRatio;
  SC_CheckBox       *froudeScaling;    

  SC_IntLineEdit *numGPUs;
  SC_IntLineEdit *materialModelsPerGPU;  

};

#endif // SETTINGS_DIGITAL_TWIN_H

#ifndef OPENFOAM_DIGITAL_TWIN_H
#define OPENFOAM_DIGITAL_TWIN_H

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
 *  This is the class providing the OpenFOAM_ Tab for the CoupledDigitalTwin
 */

#include <SimCenterWidget.h>

class QJsonObject;
class SC_DoubleLineEdit;
class SC_ComboBox;
class SC_TableEdit;
class SC_FileEdit;

class OpenFOAM_DigitalTwin : public SimCenterWidget
{
public:
    OpenFOAM_DigitalTwin(QWidget *parent = 0);
    virtual ~OpenFOAM_DigitalTwin();
    bool outputToJSON(QJsonObject &jsonObject);
    bool inputFromJSON(QJsonObject &jsonObject);

signals:

private:

  SC_ComboBox       *facility;
  SC_DoubleLineEdit *flumeLength;
  SC_DoubleLineEdit *flumeHeight;
  SC_DoubleLineEdit *flumeWidth;
  SC_DoubleLineEdit *cellSize;

  SimCenterWidget *waveGeneration;

  // init Conditions
  SC_DoubleLineEdit *stillWaterLevel;
  SC_DoubleLineEdit *initVel;
  SC_DoubleLineEdit *refPressure;
  
  // turbilence settings
  SC_DoubleLineEdit *referenceLength;
  SC_DoubleLineEdit *turbulanceIntensity;
  SC_DoubleLineEdit *referenceVel;

  // bathymetry
  SC_ComboBox    *bathymetryComboBox;
  SC_TableEdit   *bathXZData;
  SC_FileEdit    *bathSTL;


  // wave generation
  SC_ComboBox    *waveGenComboBox;
  SC_FileEdit    *paddleDisplacementFile;    
  SC_DoubleLineEdit   *waveMag;
  SC_DoubleLineEdit   *waveCelerity;
  SC_DoubleLineEdit   *waveRepeatSpeed;    
};

#endif // OPENFOAM_DIGITAL_TWIN_H

#ifndef PARTICLES_MPM_H
#define PARTICLES_MPM_H

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
 *  This is the class providing the Particle Bodies Tab for mpm
 */

#include <SimCenterWidget.h>

class QJsonObject;
class SC_DoubleLineEdit;
class SC_ComboBox;
class SC_TableEdit;
class SC_FileEdit;
class SC_CheckBox;

class ParticlesMPM : public SimCenterWidget
{
public:
    ParticlesMPM(QWidget *parent = 0);
    virtual ~ParticlesMPM();
    bool outputToJSON(QJsonObject &jsonObject);
    bool inputFromJSON(QJsonObject &jsonObject);
    bool copyFiles(QString &dirName);
  
signals:

private:
  // SC_FileEdit *theOpenSeesPyScript;
  // SC_FileEdit *theSurfaceFile;

  // fluid
  SC_DoubleLineEdit *standingWaterLevel;
  SC_CheckBox *fillFlumeUptoSWL;
  SC_ComboBox       *facility;
  SC_DoubleLineEdit *flumeLength;
  SC_DoubleLineEdit *flumeHeight;
  SC_DoubleLineEdit *flumeWidth;
  SC_DoubleLineEdit *flumeOriginX;
  SC_DoubleLineEdit *flumeOriginY;
  SC_DoubleLineEdit *flumeOriginZ;  
  SC_ComboBox       *bathymetryComboBox;
  SC_TableEdit      *bathXZData;  

  // debris
  SC_ComboBox         *generationMethod;    
  SC_DoubleLineEdit   *paddleLength;    
  SC_DoubleLineEdit   *paddleHeight;
  SC_DoubleLineEdit   *paddleWidth;
  SC_DoubleLineEdit   *waveRepeatSpeed;
  SC_DoubleLineEdit   *paddleOriginX;
  SC_DoubleLineEdit   *paddleOriginY;;
  SC_DoubleLineEdit   *paddleOriginZ;
  SC_ComboBox         *debrisMaterialType;      
  SC_FileEdit         *paddleDisplacementFile;    

  // structures
  SC_ComboBox       *wallsContactType;
  SC_DoubleLineEdit *wallsLength;
  SC_DoubleLineEdit *wallsHeight;
  SC_DoubleLineEdit *wallsWidth;
  SC_DoubleLineEdit *originLength;
  SC_DoubleLineEdit *originHeight;
  SC_DoubleLineEdit *originWidth;
  SC_CheckBox       *applyCoulombFriction;    
  SC_DoubleLineEdit *staticFrictionWallX;
  SC_DoubleLineEdit *staticFrictionFloor;
  SC_DoubleLineEdit *staticFrictionWallZ;
  SC_DoubleLineEdit *dynamicFrictionWallX;
  SC_DoubleLineEdit *dynamicFrictionFloor;
  SC_DoubleLineEdit *dynamicFrictionWallZ;    
  
  // Custom Bodies


};

#endif // OPENSEES_DIGITAL_TWIN_H


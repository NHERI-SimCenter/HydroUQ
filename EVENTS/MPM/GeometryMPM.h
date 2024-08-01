#ifndef GEOMETRY_MPM_H
#define GEOMETRY_MPM_H

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
 *  @version 3.0
 *
 *  @section DESCRIPTION
 *
 *  This is the class providing the Geometry Tab for MPM
 */

#include <SimCenterWidget.h>

// Forward Declaration
class QJsonObject;
class QJsonArray;
class SC_DoubleLineEdit;
class SC_IntLineEdit;
class SC_StringLineEdit;
class SC_ComboBox;
class SC_TableEdit;
class SC_FileEdit;
class SC_CheckBox;

class GeometryAI; // Provide optional AI geometry generation, e.g. with point-e library and various backend scripts - Justin Bonus

class GeometryMPM : public SimCenterWidget
{
    Q_OBJECT
public:
    GeometryMPM(QWidget *parent = 0);
    virtual ~GeometryMPM();
    bool outputToJSON(QJsonObject &jsonObject); // override
    bool inputFromJSON(QJsonObject &jsonObject); // override
    bool copyFiles(QString &dirName);
    bool setBodyPreset(int index);
    bool setDigitalTwin(int twinIdx);
signals:

private:
  // QVBoxLayout         *layout;
  SC_ComboBox         *bodyPreset;
  SC_ComboBox         *objectType;
  SC_ComboBox         *operationType;
  SC_DoubleLineEdit   *length;
  SC_DoubleLineEdit   *height;
  SC_DoubleLineEdit   *width;
  SC_DoubleLineEdit   *radius;
  SC_ComboBox         *longAxis;
  SC_DoubleLineEdit   *originX;
  SC_DoubleLineEdit   *originY;
  SC_DoubleLineEdit   *originZ;  

  SC_CheckBox         *applyArray;
  SC_IntLineEdit      *arrayX;
  SC_IntLineEdit      *arrayY;
  SC_IntLineEdit      *arrayZ;
  SC_DoubleLineEdit   *spacingX;
  SC_DoubleLineEdit   *spacingY;
  SC_DoubleLineEdit   *spacingZ;
  
  SC_TableEdit        *trackerTable;  

  SC_CheckBox         *applyRotation;
  SC_DoubleLineEdit   *rotateAngleX;
  SC_DoubleLineEdit   *rotateAngleY;
  SC_DoubleLineEdit   *rotateAngleZ;
  SC_DoubleLineEdit   *rotateFulcrumX;
  SC_DoubleLineEdit   *rotateFulcrumY;
  SC_DoubleLineEdit   *rotateFulcrumZ;


  SC_DoubleLineEdit   *standingWaterLevel;
  SC_CheckBox         *fillFlumeUptoSWL;
  SC_ComboBox         *facility;
  SC_DoubleLineEdit   *facilityLength;
  SC_DoubleLineEdit   *facilityHeight;
  SC_DoubleLineEdit   *facilityWidth;
  SC_ComboBox         *bathymetryComboBox;
  SC_TableEdit        *bathXZData;  
  SC_FileEdit         *bathSTL;

  SC_FileEdit         *geometryFile;
  SC_FileEdit         *checkpointBGEO;

  // GeometryAI         *theGenAI;
  SimCenterWidget       *theGenAI;
  // QWidget            *holdGenAI;
};

#endif // GEOMETRY_MPM_H


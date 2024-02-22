#ifndef BOUNDARY_MPM_H
#define BOUNDARY_MPM_H

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
class QJsonArray;
class SC_DoubleLineEdit;
class SC_IntLineEdit;
class SC_ComboBox;
class SC_TableEdit;
class SC_FileEdit;
class SC_CheckBox;
class SC_ComboBox;
class QStackedWidget;
class QGroupBox;

class BoundaryMPM : public SimCenterWidget
{
public:
    BoundaryMPM(QWidget *parent = 0);
    virtual ~BoundaryMPM();
    bool outputToJSON(QJsonObject &jsonObject);
    bool inputFromJSON(QJsonObject &jsonObject);
    bool copyFiles(QString &dirName);  
    bool setBoundaryType(int typeIdx);
    bool setDigitalTwin(int typeIdx);

    // Refactor all (fluid, struct, etc.) to use same dimension and origin style
    double getDimensionX();
    double getDimensionY();
    double getDimensionZ();
    SC_DoubleLineEdit* getDimensionXWidget();
    SC_DoubleLineEdit* getDimensionYWidget();
    SC_DoubleLineEdit* getDimensionZWidget();
    double getOriginX();
    double getOriginY();
    double getOriginZ();
    SC_DoubleLineEdit* getOriginXWidget();
    SC_DoubleLineEdit* getOriginYWidget();
    SC_DoubleLineEdit* getOriginZWidget();

// Need to let parent know if a dimension or origin has changed
signals:
    // void structDimensionsChanged(void);
    // void structOriginChanged(void); 
    void structDimensionsChanged(QString val);
    void structOriginChanged(QString val); 

private:

  SC_ComboBox      *boundaryType;
  QStackedWidget   *stackedWidget;
  // waveFlume
  SC_ComboBox       *facility;
  SC_DoubleLineEdit *flumeLength;
  SC_DoubleLineEdit *flumeHeight;
  SC_DoubleLineEdit *flumeWidth;
  SC_DoubleLineEdit *flumeOriginX;
  SC_DoubleLineEdit *flumeOriginY;
  SC_DoubleLineEdit *flumeOriginZ;  
  SC_ComboBox       *bathymetryComboBox;

  SC_FileEdit       *bathSTL;
  SC_TableEdit      *bathXZData;  

  // wave generation
  SC_ComboBox         *generationMethod;    
  SC_DoubleLineEdit   *paddleLength;    
  SC_DoubleLineEdit   *paddleHeight;
  SC_DoubleLineEdit   *paddleWidth;

  SC_DoubleLineEdit   *waveMag;
  SC_DoubleLineEdit   *waveCelerity;
  SC_DoubleLineEdit   *waveRepeatSpeed;
  SC_DoubleLineEdit   *paddleOriginX;
  SC_DoubleLineEdit   *paddleOriginY;;
  SC_DoubleLineEdit   *paddleOriginZ;
  SC_ComboBox         *paddleContactType;      
  SC_FileEdit         *paddleDisplacementFile;    


  // structures
  SC_ComboBox       *structPreset;
  SC_ComboBox       *structObjectType;
  SC_ComboBox       *structContactType;
  SC_DoubleLineEdit *structLength;
  SC_DoubleLineEdit *structHeight;
  SC_DoubleLineEdit *structWidth;
  SC_DoubleLineEdit *structRadius;
  SC_DoubleLineEdit *structLongAxis;
  SC_DoubleLineEdit *structOriginLength;
  SC_DoubleLineEdit *structOriginHeight;
  SC_DoubleLineEdit *structOriginWidth;
  SC_CheckBox       *structApplyCoulombFriction;    
  SC_DoubleLineEdit *structStaticFrictionWallX;
  SC_DoubleLineEdit *structStaticFrictionWallY;
  SC_DoubleLineEdit *structStaticFrictionWallZ;
  SC_DoubleLineEdit *structDynamicFrictionWallX;
  SC_DoubleLineEdit *structDynamicFrictionWallY;
  SC_DoubleLineEdit *structDynamicFrictionWallZ;  
  
  SC_CheckBox      *autoCreateLoadCells;
  SC_ComboBox      *loadCellFace;

  SC_CheckBox         *applyArray;
  SC_IntLineEdit      *structArrayX;
  SC_IntLineEdit      *structArrayY;
  SC_IntLineEdit      *structArrayZ;
  SC_DoubleLineEdit   *structSpacingX;
  SC_DoubleLineEdit   *structSpacingY;
  SC_DoubleLineEdit   *structSpacingZ;

  SC_CheckBox       *applyRotation;    
  SC_DoubleLineEdit *structRotateAngleX;
  SC_DoubleLineEdit *structRotateAngleY;
  SC_DoubleLineEdit *structRotateAngleZ;
  SC_DoubleLineEdit *structRotateFulcrumX;
  SC_DoubleLineEdit *structRotateFulcrumY;
  SC_DoubleLineEdit *structRotateFulcrumZ;

  // walls
  SC_ComboBox       *wallsContactType;
  SC_DoubleLineEdit *wallsLength;
  SC_DoubleLineEdit *wallsHeight;
  SC_DoubleLineEdit *wallsWidth;
  SC_DoubleLineEdit *originLength;
  SC_DoubleLineEdit *originHeight;
  SC_DoubleLineEdit *originWidth;

  SC_CheckBox       *applyCoulombFriction;    
  SC_DoubleLineEdit *staticFrictionWallX;
  SC_DoubleLineEdit *staticFrictionWallY;
  SC_DoubleLineEdit *staticFrictionWallZ;
  SC_DoubleLineEdit *dynamicFrictionWallX;
  SC_DoubleLineEdit *dynamicFrictionWallY;
  SC_DoubleLineEdit *dynamicFrictionWallZ;  

  SC_CheckBox       *applyInletOutlet;
  SC_ComboBox       *inletOutletTypeSubX;
  SC_ComboBox       *inletOutletTypeSubY;
  SC_ComboBox       *inletOutletTypeSubZ;
  SC_ComboBox       *inletOutletTypePlusX;
  SC_ComboBox       *inletOutletTypePlusY;
  SC_ComboBox       *inletOutletTypePlusZ;
  SC_FileEdit       *inletOutletFileSubX;
  SC_FileEdit       *inletOutletFileSubY;
  SC_FileEdit       *inletOutletFileSubZ;
  SC_FileEdit       *inletOutletFilePlusX;
  SC_FileEdit       *inletOutletFilePlusY;
  SC_FileEdit       *inletOutletFilePlusZ;
  QWidget *theCustom;
  QWidget *theWaveFlume;
  QWidget *theWaveGeneration; 
  QWidget *theStructures; 
  QWidget *theWalls;

};

#endif // BOUNDARY_MPM_H

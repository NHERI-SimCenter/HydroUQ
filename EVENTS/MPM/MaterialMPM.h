#ifndef MATERIAL_MPM_H
#define MATERIAL_MPM_H

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
class QJsonArray;
class SC_DoubleLineEdit;
class SC_IntLineEdit;
class SC_StringLineEdit;
class SC_ComboBox;
class SC_TableEdit;
class SC_FileEdit;
class SC_CheckBox;

class MaterialMPM : public SimCenterWidget
{
    Q_OBJECT
public:
    MaterialMPM(QWidget *parent = 0);
    virtual ~MaterialMPM();
    bool outputToJSON(QJsonObject &jsonObject);
    bool inputFromJSON(QJsonObject &jsonObject);
    void clear(void);
    bool copyFiles(QString &dirName);
    bool setMaterialPreset(int presetIndex);
    // bool setMaterialPreset(QString &presetName);
signals:

private:
  SC_ComboBox       *materialPreset = nullptr;
  SC_ComboBox       *constitutive = nullptr;
  SC_DoubleLineEdit *CFL = nullptr;
  SC_DoubleLineEdit *density = nullptr;


  SC_DoubleLineEdit *bulkModulus = nullptr;
  SC_DoubleLineEdit *youngsModulus = nullptr;
  SC_DoubleLineEdit *poissonsRatio = nullptr;
  // lambda = mat.E * mat.nu / ((1 + mat.nu) * (1 - 2 * mat.nu));
  // mu = mat.E / (2 * (1 + mat.nu));
  // bm =
  //     2.f / 3.f * (mat.E / (2 * (1 + mat.nu))) + (mat.E * mat.nu / ((1 + mat.nu) * (1 - 2 * mat.nu)));

  SC_DoubleLineEdit *lambdaModulus = nullptr;
  SC_DoubleLineEdit *shearModulus = nullptr;

  SC_DoubleLineEdit *viscosity = nullptr;
  SC_DoubleLineEdit *bulkModulusDerivative = nullptr;
  SC_DoubleLineEdit *surfaceTension = nullptr;
  
  SC_DoubleLineEdit   *logJp = nullptr;

  SC_CheckBox *useVolumeCorrection = nullptr;
  SC_DoubleLineEdit   *cohesion = nullptr;
  SC_DoubleLineEdit   *frictionAngle = nullptr;
  SC_DoubleLineEdit   *dilationAngle = nullptr;
  
  SC_CheckBox *useHardening = nullptr;
  SC_DoubleLineEdit   *xi = nullptr;
  SC_DoubleLineEdit   *beta = nullptr;
  SC_DoubleLineEdit   *Mohr = nullptr;
  // static constexpr PREC mohrColumbFriction =
  //     0.503599787772409; //< sqrt((T)2 / (T)3) * (T)2 * sin_phi / ((T)3 -
  //                        // sin_phi);
  // static constexpr PREC M =
  //     1.850343771924453; ///< mohrColumbFriction * (T)dim / sqrt((T)2 / ((T)6
  //                        ///< - dim));
  // static constexpr PREC Msqr = 3.423772074299613; // M * M;

  SC_DoubleLineEdit *relativeToPressure = nullptr;
  SC_DoubleLineEdit *relativeToTemperature = nullptr;

  SC_DoubleLineEdit *thermalConductivity = nullptr;
  SC_DoubleLineEdit *specificHeat = nullptr;

  SC_DoubleLineEdit *porosity = nullptr;
  SC_DoubleLineEdit *permeability = nullptr;
  SC_DoubleLineEdit *grainSize = nullptr;
  SC_DoubleLineEdit *concentration = nullptr;
};

#endif // MATERIAL_MPM_H


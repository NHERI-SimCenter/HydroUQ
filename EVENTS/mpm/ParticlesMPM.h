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
#include <vector>
#include <memory>

class QJsonObject;
class SC_DoubleLineEdit;
class SC_IntLineEdit;
class SC_StringLineEdit;
class SC_ComboBox;
class SC_TableEdit;
class SC_FileEdit;
class SC_CheckBox;

class GeometryMPM;
class MaterialMPM;
class AlgorithmMPM;
class PartitionMPM;

class ParticlesMPM : public SimCenterWidget
{
public:
    ParticlesMPM(QWidget *parent = 0);
    virtual ~ParticlesMPM();

    bool outputToJSON(QJsonObject &jsonObject);
    bool inputFromJSON(QJsonObject &jsonObject);
    // bool outputAppDataToJSON(QJsonObject &rvObject);
    // bool inputAppDataFromJSON(QJsonObject &rvObject);
    bool copyFiles(QString &dirName);
  
signals:

private:
  GeometryMPM       *fluidGeometry = nullptr;
  MaterialMPM       *fluidMaterial = nullptr;
  AlgorithmMPM      *fluidAlgorithm = nullptr;
  PartitionMPM      *fluidPartition = nullptr;

  GeometryMPM       *debrisGeometry = nullptr;
  MaterialMPM       *debrisMaterial = nullptr;
  AlgorithmMPM      *debrisAlgorithm = nullptr;
  PartitionMPM      *debrisPartition = nullptr;

  GeometryMPM       *structureGeometry = nullptr;
  MaterialMPM       *structureMaterial = nullptr;
  AlgorithmMPM      *structureAlgorithm = nullptr;
  PartitionMPM      *structurePartition = nullptr;

  // GeometryMPM       *customGeometry;
  // MaterialMPM       *customMaterial;
  // AlgorithmMPM      *customAlgorithm;
  // PartitionMPM      *customPartition;

  QVector<GeometryMPM*> addedGeometry {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
  QVector<MaterialMPM*> addedMaterial {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
  QVector<AlgorithmMPM*> addedAlgorithm {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
  QVector<PartitionMPM*> addedPartition {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
  int numReserveTabs = 8;
  int numAddedTabs = 0;
};

#endif // PARTICLES_MPM_H


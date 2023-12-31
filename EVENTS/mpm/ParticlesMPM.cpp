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

#include "ParticlesMPM.h"
#include <QLabel>
#include <QComboBox>
#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>
#include <QTabWidget>
#include <QStackedWidget>
#include <QDebug>
#include <QSvgWidget>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>

#include <SC_ComboBox.h>
#include <SC_DoubleLineEdit.h>
#include <SC_IntLineEdit.h>
#include <SC_StringLineEdit.h>
#include <SC_TableEdit.h>
#include <SC_FileEdit.h>
#include <SC_CheckBox.h>

#include <GeometryMPM.h>
#include <MaterialMPM.h>
#include <AlgorithmMPM.h>
#include <PartitionMPM.h>

#include <vector>
#include <memory>

ParticlesMPM::ParticlesMPM(QWidget *parent)
  :SimCenterWidget(parent)
{
  QGridLayout *layout = new QGridLayout();
  this->setLayout(layout);

  QPushButton *addB = new QPushButton("Create Body"); 
  QPushButton *delB = new QPushButton("Remove Body");
  addB->setIcon(QIcon(":/icons/pencil-plus-white.svg"));
  delB->setIcon(QIcon(":/icons/eraser-white.svg"));
  addB->setIconSize(QSize(24,24));
  delB->setIconSize(QSize(24,24));

  QFrame *theHeaderFrame = new QFrame();
  QGridLayout *headerLayout = new QGridLayout();
  theHeaderFrame->setLayout(headerLayout);
  headerLayout->addWidget(addB,0,0);
  headerLayout->addWidget(delB,0,1);  
  headerLayout->setColumnStretch(2,1);

  layout->addWidget(theHeaderFrame);


  ///%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // Add tab per Body
  QTabWidget *tabWidget = new QTabWidget();
  tabWidget->setTabsClosable(true); // Close tabs with X mark via mouse (connect to tabCloseRequested)
  tabWidget->setMovable(true); // Move tabs with mouse

  QWidget *theFluid = new QWidget();
  QWidget *theDebris = new QWidget();
  QWidget *theStructure = new QWidget();
  QVector<QWidget*> theAdded(numReserveTabs); // 16 is max number of added tabs

  int sizeBodyTabs = 20;
  tabWidget->addTab(theFluid,QIcon(QString(":/icons/droplet-black.svg")), "Fluid");
  tabWidget->addTab(theDebris,QIcon(QString(":/icons/car-black.svg")), "Debris");  
  tabWidget->addTab(theStructure,QIcon(QString(":/icons/home-black.svg")), "Structures");
  tabWidget->setIconSize(QSize(sizeBodyTabs, sizeBodyTabs));
  // theFluid->setIconSize(QSize(24,24));
  // theDebris->setIconSize(QSize(24,24));
  // theStructure->setIconSize(QSize(24,24));
  layout->addWidget(tabWidget);

  int numDefaultTabs = 3; // Fluid, Debris, Structures. Specializations for digital twins. Add more after these
  QVector<QGridLayout*> theAddedLayout(numReserveTabs);
  QVector<QTabWidget*> modelAddedTabWidget(numReserveTabs); 
  for (int i = 0; i < numReserveTabs; i++) {
    theAdded[i] = new QWidget();
    theAddedLayout[i] = new QGridLayout();
    addedGeometry[i] = new GeometryMPM();
    addedMaterial[i] = new MaterialMPM();
    addedAlgorithm[i] = new AlgorithmMPM();
    addedPartition[i] = new PartitionMPM();
    modelAddedTabWidget[i] = new QTabWidget();
  }

  connect(addB, &QPushButton::released, this, [=]() {
    // if (curTab != -1)  // insert below selected
    // Concatenate string to say "Custom Body 1", "Custom Body 2", etc.
    if (numAddedTabs >= numReserveTabs) 
      return;
    tabWidget->addTab(theAdded[numAddedTabs], QIcon(QString(":/icons/user-black.svg")), "Custom " + QString::number(numAddedTabs + 1));
    // theAdded.back()->setIconSize(QSize(24,24));
    theAdded[numAddedTabs]->setLayout(theAddedLayout[numAddedTabs]);
    modelAddedTabWidget[numAddedTabs]->addTab(addedMaterial[numAddedTabs], QIcon(QString(":/icons/squares-filled-black.svg")),"Material");
    modelAddedTabWidget[numAddedTabs]->addTab(addedGeometry[numAddedTabs], QIcon(QString(":/icons/triangle-square-circle-black.svg")),"Geometry");
    modelAddedTabWidget[numAddedTabs]->addTab(addedAlgorithm[numAddedTabs], QIcon(QString(":/icons/engine-black.svg")),"Algorithm");
    modelAddedTabWidget[numAddedTabs]->addTab(addedPartition[numAddedTabs], QIcon(QString(":/icons/cpu-black.svg")),"Partition");
    modelAddedTabWidget[numAddedTabs]->setIconSize(QSize(sizeBodyTabs, sizeBodyTabs));
    theAddedLayout[numAddedTabs]->addWidget(modelAddedTabWidget[numAddedTabs]);
    numAddedTabs += 1;
  });

  connect(delB, &QPushButton::released, this, [=]() {
    if (( tabWidget->currentIndex() == -1) || (tabWidget->count() <= numDefaultTabs) || (tabWidget->currentIndex() < numDefaultTabs)) 
      return;
    
    auto widget = tabWidget->widget(tabWidget->currentIndex());
    if (widget) {
          // Delete the widget itself
          // widget.deleteLater()
    }

    tabWidget->setCurrentIndex(tabWidget->currentIndex()-1);
    tabWidget->removeTab(tabWidget->currentIndex()+1);
    // clean up 
    // delete addedMaterial[numAddedTabs];
    // delete addedGeometry[numAddedTabs];
    // delete addedAlgorithm[numAddedTabs];
    // delete addedPartition[numAddedTabs];
    // delete modelAddedTabWidget[numAddedTabs];
    // delete theAddedLayout[numAddedTabs];
    // delete theAdded[numAddedTabs];
    numAddedTabs -= 1;
  }); 

  connect(tabWidget, &QTabWidget::tabCloseRequested, this, [=](int index) {
    if (( index == -1) || (tabWidget->count() <= numDefaultTabs) || (index < numDefaultTabs)) 
      return; 

    // tabWidget->setCurrentIndex(index-1);
    auto widget = tabWidget->widget(index);
    if (widget) {
          // removes the widget
          // widget.deleteLater()
    }
    if (index > 0 && index < tabWidget->count()-1 && tabWidget->currentIndex() == index) {
      tabWidget->setCurrentIndex(index-1);
    } 
    tabWidget->removeTab(index);
    // clean up
    numAddedTabs -= 1;
    
  });


  ///%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  fluidMaterial = new MaterialMPM();
  fluidGeometry = new GeometryMPM();
  fluidAlgorithm = new AlgorithmMPM();
  fluidPartition = new PartitionMPM();

  ///%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  QGridLayout *theFluidLayout = new QGridLayout();
  theFluid->setLayout(theFluidLayout);

  // Per-model body tabs
  QTabWidget *modelFluidTabWidget = new QTabWidget();
  modelFluidTabWidget->addTab(fluidMaterial, QIcon(QString(":/icons/squares-filled-black.svg")), "Material");  
  modelFluidTabWidget->addTab(fluidGeometry, QIcon(QString(":/icons/triangle-square-circle-black.svg")), "Geometry");
  modelFluidTabWidget->addTab(fluidAlgorithm, QIcon(QString(":/icons/engine-black.svg")),"Algorithm");
  modelFluidTabWidget->addTab(fluidPartition, QIcon(QString(":/icons/cpu-black.svg")),"Partition");
  modelFluidTabWidget->setIconSize(QSize(sizeBodyTabs, sizeBodyTabs));


  theFluidLayout->addWidget(modelFluidTabWidget);


  // Debris 

  debrisMaterial = new MaterialMPM();
  debrisGeometry = new GeometryMPM();
  debrisAlgorithm = new AlgorithmMPM();
  debrisPartition = new PartitionMPM();

  ///%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  QGridLayout *theDebrisLayout = new QGridLayout();
  theDebris->setLayout(theDebrisLayout);

  // Per-model body tabs
  QTabWidget *modelDebrisTabWidget = new QTabWidget();
  modelDebrisTabWidget->addTab(debrisMaterial, QIcon(QString(":/icons/squares-filled-black.svg")),"Material");  
  modelDebrisTabWidget->addTab(debrisGeometry, QIcon(QString(":/icons/triangle-square-circle-black.svg")),"Geometry");
  modelDebrisTabWidget->addTab(debrisAlgorithm, QIcon(QString(":/icons/engine-black.svg")),"Algorithm");
  modelDebrisTabWidget->addTab(debrisPartition, QIcon(QString(":/icons/cpu-black.svg")),"Partition");
  modelDebrisTabWidget->setIconSize(QSize(sizeBodyTabs, sizeBodyTabs));

  theDebrisLayout->addWidget(modelDebrisTabWidget);


  // Structures
  structureMaterial = new MaterialMPM();
  structureGeometry = new GeometryMPM();
  structureAlgorithm = new AlgorithmMPM();
  structurePartition = new PartitionMPM();

  ///%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  QGridLayout *theStructureLayout = new QGridLayout();
  theStructure->setLayout(theStructureLayout);

  // Per-model body tabs
  QTabWidget *modelStructureTabWidget = new QTabWidget();
  modelStructureTabWidget->addTab(structureMaterial, QIcon(QString(":/icons/squares-filled-black.svg")),"Material");  
  modelStructureTabWidget->addTab(structureGeometry, QIcon(QString(":/icons/triangle-square-circle-black.svg")),"Geometry");
  modelStructureTabWidget->addTab(structureAlgorithm, QIcon(QString(":/icons/engine-black.svg")),"Algorithm");
  modelStructureTabWidget->addTab(structurePartition, QIcon(QString(":/icons/cpu-black.svg")),"Partition");
  modelStructureTabWidget->setIconSize(QSize(sizeBodyTabs, sizeBodyTabs));
  theStructureLayout->addWidget(modelStructureTabWidget);

  //
  // Preset some specialized defaults
  //

  // Set initial material preset
  fluidMaterial->setMaterialPreset(0); // Water (Fresh)
  fluidMaterial->setMaterialPreset(0); 
  debrisMaterial->setMaterialPreset(3); // Plastic
  debrisMaterial->setMaterialPreset(3); 
  structureMaterial->setMaterialPreset(6); // Wood
  structureMaterial->setMaterialPreset(6); 
  for (int i=0; i<numAddedTabs; i++) {
    // TODO: Don't rely on hard-coded indices, probably add a map or use text labels
    addedMaterial[i]->setMaterialPreset(10); // Custom
    addedMaterial[i]->setMaterialPreset(10);
  }
  // Set initial material preset
  fluidGeometry->setBodyPreset(0); // Fluid
  fluidGeometry->setBodyPreset(0);
  debrisGeometry->setBodyPreset(1); // Debris
  debrisGeometry->setBodyPreset(1);
  structureGeometry->setBodyPreset(2); // Structure
  structureGeometry->setBodyPreset(2);
  for (int i=0; i<numAddedTabs; i++) {
    addedGeometry[i]->setBodyPreset(3); // Custom
    addedGeometry[i]->setBodyPreset(3);
  }
}

ParticlesMPM::~ParticlesMPM()
{

}

bool
ParticlesMPM::outputToJSON(QJsonObject &jsonObject)
{
  QJsonArray bodiesArray = jsonObject["bodies"].toArray();
  
  // Fluid Body Preset
  if (fluidGeometry != nullptr && fluidMaterial != nullptr && fluidAlgorithm != nullptr && fluidPartition != nullptr) {
    QJsonObject bodyObject; // Holds geometry, material, algorithm, partition, and global values for fluid preset

    QJsonObject fluidGeometryObject; // Object wrapper holding an array of geometry objects
    QJsonObject fluidMaterialObject; // Object
    QJsonObject fluidAlgorithmObject; // Object
    QJsonObject fluidPartitionObject; // Object, TODO: Make this an array of objects for multiple auto-partitions over GPUs

    QJsonArray geometryArray;
    fluidGeometryObject["geometry"] = geometryArray;
    fluidGeometry->outputToJSON(fluidGeometryObject); 
    fluidMaterial->outputToJSON(fluidMaterialObject);
    fluidAlgorithm->outputToJSON(fluidAlgorithmObject);
    fluidPartition->outputToJSON(fluidPartitionObject);

    // Future schema
    bodyObject["geometry"] = fluidGeometryObject["geometry"];
    bodyObject["material"] = fluidMaterialObject["material"];
    bodyObject["algorithm"] = fluidAlgorithmObject["algorithm"];
    bodyObject["partition"] = fluidPartitionObject;

    bodyObject["constitutive"] = fluidMaterialObject["constitutive"]; // global

    bodyObject["ppc"]        = fluidAlgorithmObject["ppc"]; // global
    bodyObject["use_ASFLIP"] = fluidAlgorithmObject["use_ASFLIP"]; // global
    bodyObject["alpha"]      = fluidAlgorithmObject["alpha"]; // global
    bodyObject["beta_min"]   = fluidAlgorithmObject["beta_min"]; // global
    bodyObject["beta_max"]   = fluidAlgorithmObject["beta_max"]; // global
    bodyObject["use_FBAR"]   = fluidAlgorithmObject["use_FBAR"]; // global
    bodyObject["FBAR_ratio"] = fluidAlgorithmObject["FBAR_ratio"]; // global

    // ClaymoreUW artifacts, TODO: Deprecate
    if (0) bodyObject["device"] = fluidPartitionObject;
    else {
      bodyObject["gpu"] = fluidPartitionObject["gpu"]; // global
      bodyObject["model"] = fluidPartitionObject["model"]; // global
      bodyObject["partition_start"] = fluidPartitionObject["partition_start"]; // global
      bodyObject["partition_end"] = fluidPartitionObject["partition_end"]; // global
    }
    // ClaymoreUW, TODO: Deprecate in favor of MPM:bodies:outputs or MPM:outputs (latter preferred) 
    bodyObject["output_attribs"] = QJsonArray::fromStringList(QStringList() << "Velocity_X" << "Pressure" << "ID"); // global
    bodyObject["target_attribs"] = QJsonArray::fromStringList(QStringList() << "Position_Y"); // global
    bodyObject["track_attribs"] = QJsonArray::fromStringList(QStringList() << "Position_X" << "Position_Z" << "Velocity_X" << "Velocity_Z" << "Pressure"); // global
    // Use initialize list for arrray
    QJsonArray trackParticleIdsArray = QJsonArray();
    int trackedIDs[1] = {0};
    for (int i=0; i<1; i++) {
      trackParticleIdsArray.append(QJsonValue(trackedIDs[i]).toInt());
    }
    bodyObject["track_particle_id"] = trackParticleIdsArray; // global
    bodyObject["type"] = QJsonValue(QString("particles")); // global

    QJsonArray bodyVelocityArray; // Need to find a spot for a bodies global initial conditions in the schema
    bodyVelocityArray.append(QJsonValue(0.0).toDouble());
    bodyVelocityArray.append(QJsonValue(0.0).toDouble());
    bodyVelocityArray.append(QJsonValue(0.0).toDouble());
    bodyObject["velocity"] = bodyVelocityArray; // global
    bodiesArray.append(bodyObject);
  }

  // Debris Body Preset
  if (debrisGeometry != nullptr && debrisMaterial != nullptr && debrisAlgorithm != nullptr && debrisPartition != nullptr) {
    QJsonObject bodyObject; // Holds geometry, material, algorithm, partition, and global values for fluid preset

    QJsonObject debrisGeometryObject; // Object wrapper holding an array of geometry objects
    QJsonObject debrisMaterialObject; // Object
    QJsonObject debrisAlgorithmObject; // Object
    QJsonObject debrisPartitionObject; // Object, TODO: Make this an array of objects for multiple auto-partitions over GPUs

    QJsonArray geometryArray;
    debrisGeometryObject["geometry"] = geometryArray;
    debrisGeometry->outputToJSON(debrisGeometryObject); 
    debrisMaterial->outputToJSON(debrisMaterialObject);
    debrisAlgorithm->outputToJSON(debrisAlgorithmObject);
    debrisPartition->outputToJSON(debrisPartitionObject);

    // Future schema
    bodyObject["geometry"] = debrisGeometryObject["geometry"];
    bodyObject["material"] = debrisMaterialObject["material"];
    bodyObject["algorithm"] = debrisAlgorithmObject["algorithm"];
    bodyObject["partition"] = debrisPartitionObject;

    bodyObject["constitutive"] = debrisMaterialObject["constitutive"]; // global

    bodyObject["ppc"]        = debrisAlgorithmObject["ppc"]; // global
    bodyObject["use_ASFLIP"] = debrisAlgorithmObject["use_ASFLIP"]; // global
    bodyObject["alpha"]      = debrisAlgorithmObject["alpha"]; // global
    bodyObject["beta_min"]   = debrisAlgorithmObject["beta_min"]; // global
    bodyObject["beta_max"]   = debrisAlgorithmObject["beta_max"]; // global
    bodyObject["use_FBAR"]   = debrisAlgorithmObject["use_FBAR"]; // global
    bodyObject["FBAR_ratio"] = debrisAlgorithmObject["FBAR_ratio"]; // global

    // ClaymoreUW artifacts, TODO: Deprecate
    if (0) bodyObject["device"] = debrisPartitionObject; // device
    else {
      bodyObject["gpu"] = debrisPartitionObject["gpu"]; // global
      bodyObject["model"] = debrisPartitionObject["model"]; // global
      bodyObject["partition_start"] = debrisPartitionObject["partition_start"]; // global
      bodyObject["partition_end"] = debrisPartitionObject["partition_end"]; // global
    }
    // ClaymoreUW, TODO: Deprecate in favor of MPM:bodies:outputs or MPM:outputs (latter preferred) 
    bodyObject["output_attribs"] = QJsonArray::fromStringList(QStringList() << "Velocity_X" << "Pressure" << "ID"); // global
    bodyObject["target_attribs"] = QJsonArray::fromStringList(QStringList() << "Position_Y"); // global
    bodyObject["track_attribs"] = QJsonArray::fromStringList(QStringList() << "Position_X" << "Position_Z" << "Velocity_X" << "Velocity_Z" << "Pressure"); // global
    // Use initialize list for arrray
    QJsonArray trackParticleIdsArray = QJsonArray();
    int trackedIDs[1] = {0};
    for (int i=0; i<1; i++) {
      trackParticleIdsArray.append(QJsonValue(trackedIDs[i]).toInt());
    }
    bodyObject["track_particle_id"] = trackParticleIdsArray; // global
    bodyObject["type"] = QJsonValue(QString("particles")); // global

    QJsonArray bodyVelocityArray; // Need to find a spot for a bodies global initial conditions in the schema
    bodyVelocityArray.append(QJsonValue(0.0).toDouble());
    bodyVelocityArray.append(QJsonValue(0.0).toDouble());
    bodyVelocityArray.append(QJsonValue(0.0).toDouble());
    bodyObject["velocity"] = bodyVelocityArray; // global    
    
    // Place the new body JSON object into the main bodies array
    bodiesArray.append(bodyObject);
  }

  // Structure Body Preset
  if (structureGeometry != nullptr && structureMaterial != nullptr && structureAlgorithm != nullptr && structurePartition != nullptr) {
    QJsonObject bodyObject; // Holds geometry, material, algorithm, partition, and global values for fluid preset

    QJsonObject structureGeometryObject; // Object wrapper holding an array of geometry objects
    QJsonObject structureMaterialObject; // Object
    QJsonObject structureAlgorithmObject; // Object
    QJsonObject structurePartitionObject; // Object, TODO: Make this an array of objects for multiple auto-partitions over GPUs

    QJsonArray geometryArray;
    structureGeometryObject["geometry"] = geometryArray;
    structureGeometry->outputToJSON(structureGeometryObject); 
    structureMaterial->outputToJSON(structureMaterialObject);
    structureAlgorithm->outputToJSON(structureAlgorithmObject);
    structurePartition->outputToJSON(structurePartitionObject);

    // Future schema
    bodyObject["geometry"] = structureGeometryObject["geometry"];
    bodyObject["material"] = structureMaterialObject["material"];
    bodyObject["algorithm"] = structureAlgorithmObject["algorithm"];
    bodyObject["partition"] = structurePartitionObject;

    bodyObject["constitutive"] = structureMaterialObject["constitutive"]; // global

    bodyObject["ppc"]        = structureAlgorithmObject["ppc"]; // global
    bodyObject["use_ASFLIP"] = structureAlgorithmObject["use_ASFLIP"]; // global
    bodyObject["alpha"]      = structureAlgorithmObject["alpha"]; // global
    bodyObject["beta_min"]   = structureAlgorithmObject["beta_min"]; // global
    bodyObject["beta_max"]   = structureAlgorithmObject["beta_max"]; // global
    bodyObject["use_FBAR"]   = structureAlgorithmObject["use_FBAR"]; // global
    bodyObject["FBAR_ratio"] = structureAlgorithmObject["FBAR_ratio"]; // global

    // ClaymoreUW artifacts, TODO: Deprecate
    if (0) bodyObject["device"] = structurePartitionObject; // device
    else {
      bodyObject["gpu"] = structurePartitionObject["gpu"]; // global
      bodyObject["model"] = structurePartitionObject["model"]; // global
      bodyObject["partition_start"] = structurePartitionObject["partition_start"]; // global
      bodyObject["partition_end"] = structurePartitionObject["partition_end"]; // global
    }
    // bodyObject["output_attribs"] = structurePartitionOutputs; // global

    // ClaymoreUW, TODO: Deprecate in favor of MPM:bodies:outputs or MPM:outputs (latter preferred) 
    bodyObject["output_attribs"] = QJsonArray::fromStringList(QStringList() << "Velocity_X" << "Pressure" << "ID"); // global
    bodyObject["target_attribs"] = QJsonArray::fromStringList(QStringList() << "Position_Y"); // global
    bodyObject["track_attribs"] = QJsonArray::fromStringList(QStringList() << "Position_X" << "Position_Z" << "Velocity_X" << "Velocity_Z" << "Pressure"); // global
    // Use initialize list for arrray
    QJsonArray trackParticleIdsArray = QJsonArray();
    int trackedIDs[1] = {0};
    for (int i=0; i<1; i++) {
      trackParticleIdsArray.append(QJsonValue(trackedIDs[i]).toInt());
    }
    bodyObject["track_particle_id"] = trackParticleIdsArray; // global
    bodyObject["type"] = QJsonValue(QString("particles")); // global

    QJsonArray bodyVelocityArray; // Need to find a spot for a bodies global initial conditions in the schema
    bodyVelocityArray.append(QJsonValue(0.0).toDouble());
    bodyVelocityArray.append(QJsonValue(0.0).toDouble());
    bodyVelocityArray.append(QJsonValue(0.0).toDouble());
    bodyObject["velocity"] = bodyVelocityArray; // global
    bodiesArray.append(bodyObject);
  }

  // Custom Bodies, must loop over all bodies that have been added
  QJsonArray customBodiesArray; // Array of custom bodies
  {
    for (int i=0; i<numAddedTabs; i++) {
      if (i >= numReserveTabs) break;
      if (addedGeometry[i] != nullptr && addedMaterial[i] != nullptr && addedAlgorithm[i] != nullptr && addedPartition[i] != nullptr) {
        QJsonObject bodyObject; // Holds geometry, material, algorithm, partition, and global values for fluid preset

        QJsonObject customGeometryObject; // Object wrapper holding an array of geometry objects
        QJsonObject customMaterialObject; // Object
        QJsonObject customAlgorithmObject; // Object
        QJsonObject customPartitionObject; // Object, TODO: Make this an array of objects for multiple auto-partitions over GPUs

        QJsonArray geometryArray;
        customGeometryObject["geometry"] = geometryArray;
        addedGeometry[i]->outputToJSON(customGeometryObject); 
        addedMaterial[i]->outputToJSON(customMaterialObject);
        addedAlgorithm[i]->outputToJSON(customAlgorithmObject);
        addedPartition[i]->outputToJSON(customPartitionObject);

        // Future schema
        bodyObject["geometry"] = customGeometryObject["geometry"]; // geometry
        bodyObject["material"] = customMaterialObject["material"]; // material
        bodyObject["algorithm"] = customAlgorithmObject["algorithm"]; // algorithm
        bodyObject["partition"] = customPartitionObject; // partition

        bodyObject["constitutive"] = customMaterialObject["constitutive"]; // global

        bodyObject["ppc"]        = customAlgorithmObject["ppc"]; // global
        bodyObject["use_ASFLIP"] = customAlgorithmObject["use_ASFLIP"]; // global
        bodyObject["alpha"]      = customAlgorithmObject["alpha"]; // global
        bodyObject["beta_min"]   = customAlgorithmObject["beta_min"]; // global
        bodyObject["beta_max"]   = customAlgorithmObject["beta_max"]; // global
        bodyObject["use_FBAR"]   = customAlgorithmObject["use_FBAR"]; // global
        bodyObject["FBAR_ratio"] = customAlgorithmObject["FBAR_ratio"]; // global

        // ClaymoreUW artifacts, TODO: Deprecate
        if (0) bodyObject["device"] = customPartitionObject; // device
        else {
          bodyObject["gpu"] = customPartitionObject["gpu"]; // global
          bodyObject["model"] = customPartitionObject["model"]; // global
          bodyObject["partition_start"] = customPartitionObject["partition_start"]; // global
          bodyObject["partition_end"] = customPartitionObject["partition_end"]; // global
        }
        // bodyObject["output_attribs"] = customPartitionOutputs; // global

        // ClaymoreUW, TODO: Deprecate in favor of MPM:bodies:outputs or MPM:outputs (latter preferred) 
        bodyObject["output_attribs"] = QJsonArray::fromStringList(QStringList() << "Velocity_X" << "Pressure" << "ID"); // global
        bodyObject["target_attribs"] = QJsonArray::fromStringList(QStringList() << "Position_Y"); // global
        bodyObject["track_attribs"] = QJsonArray::fromStringList(QStringList() << "Position_X" << "Position_Z" << "Velocity_X" << "Velocity_Z" << "Pressure"); // global
        // Use initialize list for arrray
        QJsonArray trackParticleIdsArray = QJsonArray();
        int trackedIDs[1] = {0};
        for (int i=0; i<1; i++) {
          trackParticleIdsArray.append(QJsonValue(trackedIDs[i]).toInt());
        }
        bodyObject["track_particle_id"] = trackParticleIdsArray; // global
        bodyObject["type"] = QJsonValue(QString("particles")); // global

        QJsonArray bodyVelocityArray; // Need to find a spot for a bodies global initial conditions in the schema
        bodyVelocityArray.append(QJsonValue(0.0).toDouble());
        bodyVelocityArray.append(QJsonValue(0.0).toDouble());
        bodyVelocityArray.append(QJsonValue(0.0).toDouble());
        bodyObject["velocity"] = bodyVelocityArray; // global
        bodiesArray.append(bodyObject);
      }
    }
  }

  // Add all bodies to the bodies array
  // -----------------
  if (1) jsonObject["bodies"] = bodiesArray; // Future schema
  else jsonObject["models"] = bodiesArray; // ClaymoreUW artifacts, TODO: Deprecate

  return true;
}

bool
ParticlesMPM::inputFromJSON(QJsonObject &jsonObject)
{
  // theOpenSeesPyScript->inputFromJSON(jsonObject);
  // theSurfaceFile->inputFromJSON(jsonObject);    
  fluidGeometry->inputFromJSON(jsonObject);
  fluidMaterial->inputFromJSON(jsonObject);
  fluidAlgorithm->inputFromJSON(jsonObject);
  fluidPartition->inputFromJSON(jsonObject);
  // fluidOutputs->inputFromJSON(jsonObject);
  return true;
}

bool
ParticlesMPM::copyFiles(QString &destDir)
{
  // if (theOpenSeesPyScript->copyFile(destDir) != true)
  //   return false;
  // return theSurfaceFile->copyFile(destDir);    

  return true;
}


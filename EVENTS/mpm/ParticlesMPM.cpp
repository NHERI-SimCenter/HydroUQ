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

#include <GeometriesMPM.h>
#include <MaterialMPM.h>
#include <AlgorithmMPM.h>
#include <PartitionsMPM.h>

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
  layout->addWidget(tabWidget);

  int numDefaultTabs = 3; // Fluid, Debris, Structures. Specializations for digital twins. Add more after these
  QVector<QGridLayout*> theAddedLayout(numReserveTabs);
  QVector<QTabWidget*> modelAddedTabWidget(numReserveTabs); 
  for (int i = 0; i < numReserveTabs; i++) {
    theAdded[i] = new QWidget();
    theAddedLayout[i] = new QGridLayout();
    addedGeometries[i] = new GeometriesMPM();
    addedMaterial[i] = new MaterialMPM();
    addedAlgorithm[i] = new AlgorithmMPM();
    addedPartitions[i] = new PartitionsMPM();
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
    modelAddedTabWidget[numAddedTabs]->addTab(addedGeometries[numAddedTabs], QIcon(QString(":/icons/triangle-square-circle-black.svg")),"Geometry");
    modelAddedTabWidget[numAddedTabs]->addTab(addedAlgorithm[numAddedTabs], QIcon(QString(":/icons/engine-black.svg")),"Algorithm");
    modelAddedTabWidget[numAddedTabs]->addTab(addedPartitions[numAddedTabs], QIcon(QString(":/icons/cpu-black.svg")),"Partitions");
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
    // delete addedGeometries[numAddedTabs];
    // delete addedAlgorithm[numAddedTabs];
    // delete addedPartitions[numAddedTabs];
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
  fluidGeometries = new GeometriesMPM();
  fluidAlgorithm = new AlgorithmMPM();
  fluidPartitions = new PartitionsMPM();

  ///%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  QGridLayout *theFluidLayout = new QGridLayout();
  theFluid->setLayout(theFluidLayout);

  // Per-model body tabs
  QTabWidget *modelFluidTabWidget = new QTabWidget();
  modelFluidTabWidget->addTab(fluidMaterial, QIcon(QString(":/icons/squares-filled-black.svg")), "Material");  
  modelFluidTabWidget->addTab(fluidGeometries, QIcon(QString(":/icons/triangle-square-circle-black.svg")), "Geometry");
  modelFluidTabWidget->addTab(fluidAlgorithm, QIcon(QString(":/icons/engine-black.svg")),"Algorithm");
  modelFluidTabWidget->addTab(fluidPartitions, QIcon(QString(":/icons/cpu-black.svg")),"Partitions");
  modelFluidTabWidget->setIconSize(QSize(sizeBodyTabs, sizeBodyTabs));


  theFluidLayout->addWidget(modelFluidTabWidget);


  // Debris 

  debrisMaterial = new MaterialMPM();
  debrisGeometries = new GeometriesMPM();
  debrisAlgorithm = new AlgorithmMPM();
  debrisPartitions = new PartitionsMPM();

  ///%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  QGridLayout *theDebrisLayout = new QGridLayout();
  theDebris->setLayout(theDebrisLayout);

  // Per-model body tabs
  QTabWidget *modelDebrisTabWidget = new QTabWidget();
  modelDebrisTabWidget->addTab(debrisMaterial, QIcon(QString(":/icons/squares-filled-black.svg")),"Material");  
  modelDebrisTabWidget->addTab(debrisGeometries, QIcon(QString(":/icons/triangle-square-circle-black.svg")),"Geometry");
  modelDebrisTabWidget->addTab(debrisAlgorithm, QIcon(QString(":/icons/engine-black.svg")),"Algorithm");
  modelDebrisTabWidget->addTab(debrisPartitions, QIcon(QString(":/icons/cpu-black.svg")),"Partitions");
  modelDebrisTabWidget->setIconSize(QSize(sizeBodyTabs, sizeBodyTabs));

  theDebrisLayout->addWidget(modelDebrisTabWidget);


  // Structures
  structureMaterial = new MaterialMPM();
  structureGeometries = new GeometriesMPM();
  structureAlgorithm = new AlgorithmMPM();
  structurePartitions = new PartitionsMPM();

  ///%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  QGridLayout *theStructureLayout = new QGridLayout();
  theStructure->setLayout(theStructureLayout);

  // Per-model body tabs
  QTabWidget *modelStructureTabWidget = new QTabWidget();
  modelStructureTabWidget->addTab(structureMaterial, QIcon(QString(":/icons/squares-filled-black.svg")),"Material");  
  modelStructureTabWidget->addTab(structureGeometries, QIcon(QString(":/icons/triangle-square-circle-black.svg")),"Geometry");
  modelStructureTabWidget->addTab(structureAlgorithm, QIcon(QString(":/icons/engine-black.svg")),"Algorithm");
  modelStructureTabWidget->addTab(structurePartitions, QIcon(QString(":/icons/cpu-black.svg")),"Partitions");
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
  fluidGeometries->setBodyPreset(0); // Fluid
  fluidGeometries->setBodyPreset(0);
  debrisGeometries->setBodyPreset(1); // Debris
  debrisGeometries->setBodyPreset(1);
  structureGeometries->setBodyPreset(2); // Structure
  structureGeometries->setBodyPreset(2);
  for (int i=0; i<numAddedTabs; i++) {
    addedGeometries[i]->setBodyPreset(3); // Custom
    addedGeometries[i]->setBodyPreset(3);
  }


  // Set initial partition preset
  // Each bodies tab is, for now, assigned a unique model ID based on its tab index
  // TODO: Model IDs on a GPU must be unique, so we can't have more than 8 bodies for now, or 4 on Frontera unless we adjust distribution
  fluidPartitions->setDefaultModelID(0); // GPU 0
  debrisPartitions->setDefaultModelID(1); // Debris
  structurePartitions->setDefaultModelID(2); // Structure
  fluidPartitions->setModel(0); // Fluid
  fluidPartitions->setModel(0);
  debrisPartitions->setModel(1); 
  debrisPartitions->setModel(1);
  structurePartitions->setModel(2); 
  structurePartitions->setModel(2);
  for (int i=0; i<numAddedTabs; i++) {
    // TODO: Don't rely on hard-coded indices, probably add a map or use text labels
    addedPartitions[i]->setDefaultModelID(i+(numDefaultTabs-1));
    // TODO: Better distribute bodies as models across GPUs to allow for more bodies (i.e. 4+), as most are on just 1-2 GPUs and leave empty slots. 
    // TODO: Also guarantee no empty model ID slots on a GPU or ClaymoreUW will crash
    // TODO: Account for users manually changing the model ID on a body tab, i.e. limit their options to valid ones (change from numeric input to radio buttons)
    addedPartitions[i]->setModel(i+(numDefaultTabs-1)); 
    addedPartitions[i]->setModel(i+(numDefaultTabs-1));
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
  if (fluidGeometries != nullptr && fluidMaterial != nullptr && fluidAlgorithm != nullptr && fluidPartitions != nullptr) {
    QJsonObject bodyObject; // Holds geometry, material, algorithm, partition, and global values for fluid preset

    QJsonObject fluidGeometriesObject; // Object wrapper holding an array of geometry objects
    QJsonObject fluidMaterialObject; // Object
    QJsonObject fluidAlgorithmObject; // Object
    QJsonObject fluidPartitionsObject; // Object, TODO: Make this an array of objects for multiple auto-partitions over GPUs

    QJsonArray geometryArray;
    fluidGeometriesObject["geometry"] = geometryArray;
    fluidGeometries->outputToJSON(fluidGeometriesObject); 
    fluidMaterial->outputToJSON(fluidMaterialObject);
    fluidAlgorithm->outputToJSON(fluidAlgorithmObject);
    fluidPartitions->outputToJSON(fluidPartitionsObject);

    // Future schema
    bodyObject["geometry"] = fluidGeometriesObject["geometry"];
    bodyObject["material"] = fluidMaterialObject["material"];
    bodyObject["algorithm"] = fluidAlgorithmObject["algorithm"];
    bodyObject["partition"] = fluidPartitionsObject["partition"];

    bodyObject["constitutive"] = fluidMaterialObject["constitutive"]; // global

    bodyObject["ppc"]        = fluidAlgorithmObject["ppc"]; // global
    bodyObject["use_ASFLIP"] = fluidAlgorithmObject["use_ASFLIP"]; // global
    bodyObject["alpha"]      = fluidAlgorithmObject["alpha"]; // global
    bodyObject["beta_min"]   = fluidAlgorithmObject["beta_min"]; // global
    bodyObject["beta_max"]   = fluidAlgorithmObject["beta_max"]; // global
    bodyObject["use_FBAR"]   = fluidAlgorithmObject["use_FBAR"]; // global
    bodyObject["FBAR_ratio"] = fluidAlgorithmObject["FBAR_ratio"]; // global

    // ClaymoreUW artifacts, TODO: Deprecate
    if (0) bodyObject["device"] = fluidPartitionsObject;
    else {
      bodyObject["gpu"] = fluidPartitionsObject["gpu"]; // global
      bodyObject["model"] = fluidPartitionsObject["model"]; // global
      bodyObject["partition_start"] = fluidPartitionsObject["partition_start"]; // global
      bodyObject["partition_end"] = fluidPartitionsObject["partition_end"]; // global
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
  if (debrisGeometries != nullptr && debrisMaterial != nullptr && debrisAlgorithm != nullptr && debrisPartitions != nullptr) {
    QJsonObject bodyObject; // Holds geometry, material, algorithm, partition, and global values for fluid preset

    QJsonObject debrisGeometriesObject; // Object wrapper holding an array of geometry objects
    QJsonObject debrisMaterialObject; // Object
    QJsonObject debrisAlgorithmObject; // Object
    QJsonObject debrisPartitionsObject; // Object, TODO: Make this an array of objects for multiple auto-partitions over GPUs

    QJsonArray geometryArray;
    debrisGeometriesObject["geometry"] = geometryArray;
    debrisGeometries->outputToJSON(debrisGeometriesObject); 
    debrisMaterial->outputToJSON(debrisMaterialObject);
    debrisAlgorithm->outputToJSON(debrisAlgorithmObject);
    debrisPartitions->outputToJSON(debrisPartitionsObject);

    // Future schema
    bodyObject["geometry"] = debrisGeometriesObject["geometry"];
    bodyObject["material"] = debrisMaterialObject["material"];
    bodyObject["algorithm"] = debrisAlgorithmObject["algorithm"];
    bodyObject["partition"] = debrisPartitionsObject["partition"]; // device

    bodyObject["constitutive"] = debrisMaterialObject["constitutive"]; // global

    bodyObject["ppc"]        = debrisAlgorithmObject["ppc"]; // global
    bodyObject["use_ASFLIP"] = debrisAlgorithmObject["use_ASFLIP"]; // global
    bodyObject["alpha"]      = debrisAlgorithmObject["alpha"]; // global
    bodyObject["beta_min"]   = debrisAlgorithmObject["beta_min"]; // global
    bodyObject["beta_max"]   = debrisAlgorithmObject["beta_max"]; // global
    bodyObject["use_FBAR"]   = debrisAlgorithmObject["use_FBAR"]; // global
    bodyObject["FBAR_ratio"] = debrisAlgorithmObject["FBAR_ratio"]; // global

    // ClaymoreUW artifacts, TODO: Deprecate
    if (0) bodyObject["device"] = debrisPartitionsObject; // device
    else {
      bodyObject["gpu"] = debrisPartitionsObject["gpu"]; // global
      bodyObject["model"] = debrisPartitionsObject["model"]; // global
      bodyObject["partition_start"] = debrisPartitionsObject["partition_start"]; // global
      bodyObject["partition_end"] = debrisPartitionsObject["partition_end"]; // global
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
  if (structureGeometries != nullptr && structureMaterial != nullptr && structureAlgorithm != nullptr && structurePartitions != nullptr) {
    QJsonObject bodyObject; // Holds geometry, material, algorithm, partition, and global values for fluid preset

    QJsonObject structureGeometriesObject; // Object wrapper holding an array of geometry objects
    QJsonObject structureMaterialObject; // Object
    QJsonObject structureAlgorithmObject; // Object
    QJsonObject structurePartitionsObject; // Object, TODO: Make this an array of objects for multiple auto-partitions over GPUs

    QJsonArray geometryArray;
    structureGeometriesObject["geometry"] = geometryArray;
    structureGeometries->outputToJSON(structureGeometriesObject); 
    structureMaterial->outputToJSON(structureMaterialObject);
    structureAlgorithm->outputToJSON(structureAlgorithmObject);
    structurePartitions->outputToJSON(structurePartitionsObject);

    // Future schema
    bodyObject["geometry"] = structureGeometriesObject["geometry"];
    bodyObject["material"] = structureMaterialObject["material"];
    bodyObject["algorithm"] = structureAlgorithmObject["algorithm"];
    bodyObject["partition"] = structurePartitionsObject["partition"];

    bodyObject["constitutive"] = structureMaterialObject["constitutive"]; // global

    bodyObject["ppc"]        = structureAlgorithmObject["ppc"]; // global
    bodyObject["use_ASFLIP"] = structureAlgorithmObject["use_ASFLIP"]; // global
    bodyObject["alpha"]      = structureAlgorithmObject["alpha"]; // global
    bodyObject["beta_min"]   = structureAlgorithmObject["beta_min"]; // global
    bodyObject["beta_max"]   = structureAlgorithmObject["beta_max"]; // global
    bodyObject["use_FBAR"]   = structureAlgorithmObject["use_FBAR"]; // global
    bodyObject["FBAR_ratio"] = structureAlgorithmObject["FBAR_ratio"]; // global

    // ClaymoreUW artifacts, TODO: Deprecate
    if (0) bodyObject["device"] = structurePartitionsObject; // device
    else {
      bodyObject["gpu"] = structurePartitionsObject["gpu"]; // global
      bodyObject["model"] = structurePartitionsObject["model"]; // global
      bodyObject["partition_start"] = structurePartitionsObject["partition_start"]; // global
      bodyObject["partition_end"] = structurePartitionsObject["partition_end"]; // global
    }
    // bodyObject["output_attribs"] = structurePartitionsOutputs; // global

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
      if (addedGeometries[i] != nullptr && addedMaterial[i] != nullptr && addedAlgorithm[i] != nullptr && addedPartitions[i] != nullptr) {
        QJsonObject bodyObject; // Holds geometry, material, algorithm, partition, and global values for fluid preset

        QJsonObject customGeometriesObject; // Object wrapper holding an array of geometry objects
        QJsonObject customMaterialObject; // Object
        QJsonObject customAlgorithmObject; // Object
        QJsonObject customPartitionsObject; // Object, TODO: Make this an array of objects for multiple auto-partitions over GPUs

        QJsonArray geometryArray;
        customGeometriesObject["geometry"] = geometryArray;
        addedGeometries[i]->outputToJSON(customGeometriesObject); 
        addedMaterial[i]->outputToJSON(customMaterialObject);
        addedAlgorithm[i]->outputToJSON(customAlgorithmObject);
        addedPartitions[i]->outputToJSON(customPartitionsObject);

        // Future schema
        bodyObject["geometry"] = customGeometriesObject["geometry"]; // geometry
        bodyObject["material"] = customMaterialObject["material"]; // material
        bodyObject["algorithm"] = customAlgorithmObject["algorithm"]; // algorithm
        bodyObject["partition"] = customPartitionsObject["partition"]; // partition

        bodyObject["constitutive"] = customMaterialObject["constitutive"]; // global

        bodyObject["ppc"]        = customAlgorithmObject["ppc"]; // global
        bodyObject["use_ASFLIP"] = customAlgorithmObject["use_ASFLIP"]; // global
        bodyObject["alpha"]      = customAlgorithmObject["alpha"]; // global
        bodyObject["beta_min"]   = customAlgorithmObject["beta_min"]; // global
        bodyObject["beta_max"]   = customAlgorithmObject["beta_max"]; // global
        bodyObject["use_FBAR"]   = customAlgorithmObject["use_FBAR"]; // global
        bodyObject["FBAR_ratio"] = customAlgorithmObject["FBAR_ratio"]; // global

        // ClaymoreUW artifacts, TODO: Deprecate
        if (0) bodyObject["device"] = customPartitionsObject; // device
        else {
          bodyObject["gpu"] = customPartitionsObject["gpu"]; // global
          bodyObject["model"] = customPartitionsObject["model"]; // global
          bodyObject["partition_start"] = customPartitionsObject["partition_start"]; // global
          bodyObject["partition_end"] = customPartitionsObject["partition_end"]; // global
        }
        // bodyObject["output_attribs"] = customPartitionsOutputs; // global

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
  fluidGeometries->inputFromJSON(jsonObject);
  fluidMaterial->inputFromJSON(jsonObject);
  fluidAlgorithm->inputFromJSON(jsonObject);
  fluidPartitions->inputFromJSON(jsonObject);
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


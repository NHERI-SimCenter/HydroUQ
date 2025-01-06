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

#include "BodiesMPM.h"
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

BodiesMPM::BodiesMPM(QWidget *parent)
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
  tabWidget->setMovable(false); // Move tabs with mouse


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

  int numRequiredTabs = 1; // Always keep one tab so the JSON output is valid 
  connect(delB, &QPushButton::released, this, [=]() {
    if (( tabWidget->currentIndex() == -1) || (tabWidget->count() <= numDefaultTabs))
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
    if (( index == -1) || (tabWidget->count() <= numDefaultTabs) ) 
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

  toggleFluid = new SC_CheckBox("toggleFluid", true);
  theFluidLayout->addWidget(new QLabel("Enable Body"), 0, 0, Qt::AlignRight);
  theFluidLayout->addWidget(toggleFluid, 0, 1);

  fluidVelocityX = new SC_DoubleLineEdit("fluid_velocity_x", 0.0);
  fluidVelocityY = new SC_DoubleLineEdit("fluid_velocity_y", 0.0);
  fluidVelocityZ = new SC_DoubleLineEdit("fluid_velocity_z", 0.0);
  theFluidLayout->addWidget(new QLabel("Velocity (X,Y,Z)"), 1, 0);
  theFluidLayout->addWidget(fluidVelocityX, 1, 1);
  theFluidLayout->addWidget(fluidVelocityY, 1, 2);
  theFluidLayout->addWidget(fluidVelocityZ, 1, 3);
  theFluidLayout->addWidget(new QLabel("m/s"), 1, 4);
  theFluidLayout->addWidget(modelFluidTabWidget, 2, 0, 1, 5);


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

  toggleDebris = new SC_CheckBox("toggleDebris", true);
  theDebrisLayout->addWidget(new QLabel("Enable Body"), 0, 0, Qt::AlignRight);
  theDebrisLayout->addWidget(toggleDebris, 0, 1);

  debrisVelocityX = new SC_DoubleLineEdit("debris_velocity_x", 0.0);
  debrisVelocityY = new SC_DoubleLineEdit("debris_velocity_y", 0.0);
  debrisVelocityZ = new SC_DoubleLineEdit("debris_velocity_z", 0.0);
  theDebrisLayout->addWidget(new QLabel("Velocity (X,Y,Z)"), 1, 0);
  theDebrisLayout->addWidget(debrisVelocityX, 1, 1);
  theDebrisLayout->addWidget(debrisVelocityY, 1, 2);
  theDebrisLayout->addWidget(debrisVelocityZ, 1, 3);
  theDebrisLayout->addWidget(new QLabel("m/s"), 1, 4);
  theDebrisLayout->addWidget(modelDebrisTabWidget, 2, 0, 1, 5);
  // theDebrisLayout->addWidget(modelDebrisTabWidget);


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

  toggleStructure = new SC_CheckBox("toggleStructure", false);
  theStructureLayout->addWidget(new QLabel("Enable Body"), 0, 0, Qt::AlignRight);
  theStructureLayout->addWidget(toggleStructure, 0, 1);

  structureVelocityX = new SC_DoubleLineEdit("structure_velocity_x", 0.0);
  structureVelocityY = new SC_DoubleLineEdit("structure_velocity_y", 0.0);
  structureVelocityZ = new SC_DoubleLineEdit("structure_velocity_z", 0.0);
  theStructureLayout->addWidget(new QLabel("Velocity (X,Y,Z)"), 1, 0);
  theStructureLayout->addWidget(structureVelocityX, 1, 1);
  theStructureLayout->addWidget(structureVelocityY, 1, 2);
  theStructureLayout->addWidget(structureVelocityZ, 1, 3);
  theStructureLayout->addWidget(new QLabel("m/s"), 1, 4);
  theStructureLayout->addWidget(modelStructureTabWidget, 2, 0, 1, 5);
  // theStructureLayout->addWidget(modelStructureTabWidget);

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

  // Set initial algorithm preset
  fluidAlgorithm->enableASFLIP(false);
  fluidAlgorithm->setASFLIP_alpha(0.0);
  fluidAlgorithm->setASFLIP_betaMin(0.0);
  fluidAlgorithm->setASFLIP_betaMax(0.0);
  fluidAlgorithm->enableFBAR(true);
  fluidAlgorithm->setFBAR_psi(0.95);
  fluidAlgorithm->enableFBAR_fusedG2P2G(true);

  debrisAlgorithm->enableASFLIP(true);
  debrisAlgorithm->setASFLIP_alpha(0.0);
  debrisAlgorithm->setASFLIP_betaMin(0.0);
  debrisAlgorithm->setASFLIP_betaMax(0.0);
  debrisAlgorithm->enableFBAR(false);
  debrisAlgorithm->setFBAR_psi(0.0);
  debrisAlgorithm->enableFBAR_fusedG2P2G(true);

  structureAlgorithm->enableASFLIP(false);
  structureAlgorithm->setASFLIP_alpha(0.0);
  structureAlgorithm->setASFLIP_betaMin(0.0);
  structureAlgorithm->setASFLIP_betaMax(0.0);
  structureAlgorithm->enableFBAR(false);
  structureAlgorithm->setFBAR_psi(0.0);
  structureAlgorithm->enableFBAR_fusedG2P2G(false);
  


  // Set initial partition preset
  // TODO: Better distribute bodies as models across GPUs to allow for more bodies (i.e. 4+), as most are on just 1-2 GPUs and leave empty slots. 
  // TODO: Also guarantee no empty model ID slots on a GPU or ClaymoreUW will crash
  // TODO: Account for users manually changing the model ID on a body tab, i.e. limit their options to valid ones (change from numeric input to radio buttons)
  
  // Set the computer hardware limits
  QString computerName = "Lonestar6";
  QString queueName = "gpu-a100";
  fluidPartitions->updateHardwareLimits(computerName, queueName);
  debrisPartitions->updateHardwareLimits(computerName, queueName);
  structurePartitions->updateHardwareLimits(computerName, queueName);

  // Preset the default model ID for each body, helps avoid GPU:Model ID conflicts (must be unique)
  fluidPartitions->setDefaultModelID(0); // GPU 0 : Model 0
  debrisPartitions->setDefaultModelID(1); // GPU 0 : Model 1
  structurePartitions->setDefaultModelID(2); // GPU 0 : Model 2
  fluidPartitions->setModel(0);
  fluidPartitions->setModel(0);
  debrisPartitions->setModel(1); 
  debrisPartitions->setModel(1);
  structurePartitions->setModel(2); 
  structurePartitions->setModel(2);

  // Initialize with multiple partitions on selected body presets if desired (e.g. for the water)
  fluidPartitions->addPartition(1,0);    // GPU 1 : Model 0
  fluidPartitions->addPartition(2,0);    // GPU 2 : Model 0
  {
    double trueOrigin[3] = {0.0, 0.0, 0.0};
    double flumeOrigin[3] = {1.9, 0.0, 0.0};
    double flumeDimensions[3] = {90.0, 2.9, 3.6}; 
     // Balance partitions, i.e. decompose the geometry at equal volume for each partition (no-overlap)
    fluidPartitions->balance(flumeOrigin, flumeDimensions);
    debrisPartitions->balance(flumeOrigin, flumeDimensions); 
    // fluidPartitions->constrainPartitionWithin(trueOrigin, flumeDimensions);
    // debrisPartitions->constrainPartitionWithin(trueOrigin, flumeDimensions); 
  }
  // Do the same for custom body partitions with a loop
  for (int i=0; i<numAddedTabs; i++) {
    addedPartitions[i]->updateHardwareLimits(computerName, queueName);
    addedPartitions[i]->setDefaultModelID(i+(numDefaultTabs-1));
    addedPartitions[i]->setModel(i+(numDefaultTabs-1)); 
    addedPartitions[i]->setModel(i+(numDefaultTabs-1));
    double trueOrigin[3] = {0.0, 0.0, 0.0};
  }

}

BodiesMPM::~BodiesMPM()
{

}

void BodiesMPM::clear(void)
{
  // Clear all bodies
  // fluidGeometries->clear();
  // fluidMaterial->clear();
  // fluidAlgorithm->clear();
  // fluidPartitions->clear();
  // debrisGeometries->clear();
  // debrisMaterial->clear();
  // debrisAlgorithm->clear();
  // debrisPartitions->clear();
  // structureGeometries->clear();
  // structureMaterial->clear();
  // structureAlgorithm->clear();
  // structurePartitions->clear();
  // for (int i=0; i<numAddedTabs; i++) {
  //   addedGeometries[i]->clear();
  //   addedMaterial[i]->clear();
  //   addedAlgorithm[i]->clear();
  //   addedPartitions[i]->clear();
  // }
}

bool
BodiesMPM::outputToJSON(QJsonObject &jsonObject)
{
  QJsonArray bodiesArray = jsonObject["bodies"].toArray();
  
  // Fluid Body Preset
  if (toggleFluid->isChecked() && fluidGeometries != nullptr && fluidMaterial != nullptr && fluidAlgorithm != nullptr && fluidPartitions != nullptr) {
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

    QJsonArray fluidVelocity = QJsonArray();
    fluidVelocity.append(fluidVelocityX->text().toDouble());
    fluidVelocity.append(fluidVelocityY->text().toDouble());
    fluidVelocity.append(fluidVelocityZ->text().toDouble());
    bodyObject["velocity"] = fluidVelocity; // global, TODO: Improve schema for Init Conditions rel. to Geometries
  
    // ClaymoreUW, TODO: Deprecate in favor of MPM:bodies:outputs or MPM:outputs (latter preferred) 
    bodyObject["target_attribs"] = QJsonArray::fromStringList(QStringList() << "Position_Y"); // global
    bodyObject["track_attribs"] = QJsonArray::fromStringList(QStringList() << "Position_X" << "Position_Z" << "Pressure"); // global
    // Use initialize list for arrray
    QJsonArray trackParticleIdsArray = QJsonArray();
    int trackedIDs[1] = {0};
    for (int i=0; i<1; i++) {
      trackParticleIdsArray.append(QJsonValue(trackedIDs[i]).toInt());
    }
    bodyObject["track_particle_id"] = trackParticleIdsArray; // global
    bodyObject["type"] = QJsonValue(QString("particles")); // global
    bodyObject["name"] = QJsonValue(QString("fluid")); // global
    bodiesArray.append(bodyObject);
  }

  // Debris Body Preset
  if (toggleDebris->isChecked() && debrisGeometries != nullptr && debrisMaterial != nullptr && debrisAlgorithm != nullptr && debrisPartitions != nullptr) {
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

    QJsonArray debrisVelocity = QJsonArray();
    debrisVelocity.append(debrisVelocityX->text().toDouble());
    debrisVelocity.append(debrisVelocityY->text().toDouble());
    debrisVelocity.append(debrisVelocityZ->text().toDouble());
    bodyObject["velocity"] = debrisVelocity; // global, TODO: Improve schema for Init Conditions rel. to Geometries
  
    // ClaymoreUW, TODO: Deprecate in favor of MPM:bodies:outputs or MPM:outputs (latter preferred) 
    bodyObject["target_attribs"] = QJsonArray::fromStringList(QStringList() << "Position_Y"); // global
    bodyObject["track_attribs"] = QJsonArray::fromStringList(QStringList() << "Position_X" << "Position_Z" << "Pressure"); // global
    // Use initialize list for arrray
    QJsonArray trackParticleIdsArray = QJsonArray();
    int trackedIDs[1] = {0};
    for (int i=0; i<1; i++) {
      trackParticleIdsArray.append(QJsonValue(trackedIDs[i]).toInt());
    }
    bodyObject["track_particle_id"] = trackParticleIdsArray; // global
    bodyObject["type"] = QJsonValue(QString("particles")); // global
    bodyObject["name"] = QJsonValue(QString("debris")); // global

    // Place the new body JSON object into the main bodies array
    bodiesArray.append(bodyObject);
  }

  // Structure Body Preset
  if (toggleStructure->isChecked() && structureGeometries != nullptr && structureMaterial != nullptr && structureAlgorithm != nullptr && structurePartitions != nullptr) {
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

    QJsonArray structureVelocity = QJsonArray();
    structureVelocity.append(structureVelocityX->text().toDouble());
    structureVelocity.append(structureVelocityY->text().toDouble());
    structureVelocity.append(structureVelocityZ->text().toDouble());
    bodyObject["velocity"] = structureVelocity; // global, TODO: Improve schema for Init Conditions rel. to Geometries
  
    // bodyObject["output_attribs"] = structurePartitionsOutputs; // global

    // ClaymoreUW, TODO: Deprecate in favor of MPM:bodies:outputs or MPM:outputs (latter preferred) 
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
    bodyObject["name"] = QJsonValue(QString("structure")); // global
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

        // TODO : Make velocity usable for all added custom bodies
        // if (i == 0) {
        //   QJsonArray addedVelocity = QJsonArray();
        //   addedVelocity.append(addedVelocityX->text().toDouble());
        //   addedVelocity.append(addedVelocityY->text().toDouble());
        //   addedVelocity.append(addedVelocityZ->text().toDouble());
        //   bodyObject["velocity"] = addedVelocity; // global, TODO: Improve schema for Init Conditions rel. to Geometries
        // }


        // bodyObject["output_attribs"] = customPartitionsOutputs; // global

        // ClaymoreUW, TODO: Deprecate in favor of MPM:bodies:outputs or MPM:outputs (latter preferred) 
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
        bodyObject["name"] = QJsonValue(QString("custom_") + QString::number(i+1)); // global

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
  jsonObject["bodies"] = bodiesArray; // Future schema

  return true;
}

bool
BodiesMPM::inputFromJSON(QJsonObject &jsonObject)
{
  this->clear(); // Clear all bodies

  // Input all bodies
  QJsonArray bodiesArray = jsonObject["bodies"].toArray();
  for (int i=0; i<bodiesArray.size(); i++) {
    QJsonObject bodyObject = bodiesArray[i].toObject();
    QJsonObject materialObject = bodyObject["material"].toObject();
    QJsonObject algorithmObject = bodyObject["algorithm"].toObject();
    if (bodyObject["name"].toString() == "fluid") {
      fluidGeometries->inputFromJSON(bodyObject);
      fluidMaterial->inputFromJSON(materialObject);
      fluidAlgorithm->inputFromJSON(algorithmObject);
      fluidPartitions->inputFromJSON(bodyObject);
    } else if (bodyObject["name"].toString() == "debris") {
      debrisGeometries->inputFromJSON(bodyObject);
      debrisMaterial->inputFromJSON(materialObject);
      debrisAlgorithm->inputFromJSON(algorithmObject);
      debrisPartitions->inputFromJSON(bodyObject);
    } else if (bodyObject["name"].toString() == "structure") {
      structureGeometries->inputFromJSON(bodyObject);
      structureMaterial->inputFromJSON(materialObject);
      structureAlgorithm->inputFromJSON(algorithmObject);
      structurePartitions->inputFromJSON(bodyObject);
    } else if (bodyObject["name"].toString().startsWith("custom_")) {
      int customIdx = bodyObject["name"].toString().split("_")[1].toInt();
      if (customIdx >= numReserveTabs) break;
      addedGeometries[customIdx]->inputFromJSON(bodyObject);
      addedMaterial[customIdx]->inputFromJSON(materialObject);
      addedAlgorithm[customIdx]->inputFromJSON(algorithmObject);
      addedPartitions[customIdx]->inputFromJSON(bodyObject);
    }
  }

  // toggleFluid->setChecked(true); // Enable body by default if it exists in the JSON
  // toggleDebris->setChecked(true); // Enable body by default if it exists in the JSON
  // toggleStructure->setChecked(true); // Enable body by default if it exists in the JSON
  return true;
}

bool
BodiesMPM::copyFiles(QString &destDir)
{
  fluidGeometries->copyFiles(destDir);
  fluidMaterial->copyFiles(destDir);
  fluidAlgorithm->copyFiles(destDir);
  fluidPartitions->copyFiles(destDir);

  debrisGeometries->copyFiles(destDir);
  debrisMaterial->copyFiles(destDir);
  debrisAlgorithm->copyFiles(destDir);
  debrisPartitions->copyFiles(destDir);

  structureGeometries->copyFiles(destDir);
  structureMaterial->copyFiles(destDir);
  structureAlgorithm->copyFiles(destDir);
  structurePartitions->copyFiles(destDir);

  for (int i=0; i<numAddedTabs; i++) {
    addedGeometries[i]->copyFiles(destDir);
    addedMaterial[i]->copyFiles(destDir);
    addedAlgorithm[i]->copyFiles(destDir);
    addedPartitions[i]->copyFiles(destDir);
  }

  return true;
}

bool
BodiesMPM::setDigitalTwin(int twinIdx)
{
  fluidGeometries->setDigitalTwin(twinIdx);
  // fluidMaterial->setDigitalTwin(twinIdx);

  debrisGeometries->setDigitalTwin(twinIdx);
  // debrisMaterial->setDigitalTwin(twinIdx);

  structureGeometries->setDigitalTwin(twinIdx);
  // structureMaterial->setDigitalTwin(twinIdx);

  // Assuming we do not apply twins to custom tabs
  return true;
}


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
  addB->setIcon(QIcon(":/icons/pencil-plus-white.svg"));
  addB->setIconSize(QSize(24,24));

  QPushButton *delB = new QPushButton("Remove Body");
  delB->setIcon(QIcon(":/icons/eraser-white.svg"));
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
  tabWidget->setTabsClosable(true);
  tabWidget->setMovable(true);


  QWidget *theFluid = new QWidget();
  QWidget *theDebris = new QWidget();
  QWidget *theStructure = new QWidget();
  // QWidget *theCustom = new QWidget();
  // std::vector<std::unique_ptr<QWidget> > theAdded; // 16 is max number of added tabs

  QVector<QWidget*> theAdded(numReserveTabs); // 16 is max number of added tabs


  int sizeBodyTabs = 20;
  tabWidget->addTab(theFluid,QIcon(QString(":/icons/droplet-black.svg")), "Fluid");
  tabWidget->addTab(theDebris,QIcon(QString(":/icons/car-black.svg")), "Debris");  
  tabWidget->addTab(theStructure,QIcon(QString(":/icons/home-black.svg")), "Structures");
  tabWidget->setIconSize(QSize(sizeBodyTabs, sizeBodyTabs));
  // tabWidget->addTab(theCustom,QIcon(QString(":/icons/pencil-plus-black.svg")), "Custom Body 1");

  // theFluid->setIconSize(QSize(24,24));
  // theDebris->setIconSize(QSize(24,24));
  // theStructure->setIconSize(QSize(24,24));
  // theCustom->setIconSize(QSize(24,24));

  layout->addWidget(tabWidget);


  int numDefaultTabs = 3;
  // int numTabs = (int)tabWidget->count();
  // int curTab = (int)tabWidget->currentIndex();


  // numAddedTabs = 0;
  // QGridLayout *theAddedLayout[16] = {new QGridLayout()};
  // QTabWidget *modelAddedTabWidget[16] = {new QTabWidget()};
  QVector<QGridLayout*> theAddedLayout(numReserveTabs);
  QVector<QTabWidget*> modelAddedTabWidget(numReserveTabs); 
  // QWidget *theAdded[8] = {new QWidget()};

// MaterialMPM *addedMaterial[16] = {new MaterialMPM()};
  // theAdded.reserve(numReserveTabs);
  // theAddedLayout.reserve(numReserveTabs);
  // modelAddedTabWidget.reserve(numReserveTabs);
  // addedGeometry.reserve(numReserveTabs);
  // addedMaterial.reserve(numReserveTabs);
  // addedAlgorithm.reserve(numReserveTabs);
  // addedPartition.reserve(numReserveTabs);

  // (*theAdded)[numAddedTabs] = new QWidget();

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

    // theAdded.push_back(std::unique_ptr<QWidget>(new QWidget()));
    tabWidget->addTab(theAdded[numAddedTabs], QIcon(QString(":/icons/user-black.svg")), "Custom " + QString::number(numAddedTabs + 1));
    // theAdded.back()->setIconSize(QSize(24,24));

    // theAddedLayout.push_back(std::unique_ptr<QGridLayout>(new QGridLayout()));
    // addedGeometry.push_back(std::unique_ptr<GeometryMPM>(new GeometryMPM()));
    // addedMaterial.push_back(std::unique_ptr<MaterialMPM>(new MaterialMPM()));
    // addedAlgorithm.push_back(std::unique_ptr<AlgorithmMPM>(new AlgorithmMPM()));
    // addedPartition.push_back(std::unique_ptr<PartitionMPM>(new PartitionMPM()));
    // modelAddedTabWidget.push_back(std::unique_ptr<QTabWidget>(new QTabWidget()));



    theAdded[numAddedTabs]->setLayout(theAddedLayout[numAddedTabs]);
    modelAddedTabWidget[numAddedTabs]->addTab(addedMaterial[numAddedTabs], QIcon(QString(":/icons/squares-filled-black.svg")),"Material");
    modelAddedTabWidget[numAddedTabs]->addTab(addedGeometry[numAddedTabs], QIcon(QString(":/icons/triangle-square-circle-black.svg")),"Geometry");
    modelAddedTabWidget[numAddedTabs]->addTab(addedAlgorithm[numAddedTabs], QIcon(QString(":/icons/engine-black.svg")),"Algorithm");
    modelAddedTabWidget[numAddedTabs]->addTab(addedPartition[numAddedTabs], QIcon(QString(":/icons/cpu-black.svg")),"Partition");
    modelAddedTabWidget[numAddedTabs]->setIconSize(QSize(sizeBodyTabs, sizeBodyTabs));
    theAddedLayout[numAddedTabs]->addWidget(modelAddedTabWidget[numAddedTabs]);
    numAddedTabs += 1;

    // theAdded[tabWidget->count() - numDefaultTabs] = new QWidget();

    // theAdded[tabWidget->count() - numDefaultTabs]->setLayout(theAddedLayout[tabWidget->count() - numDefaultTabs]);  
    // theAdded.back()->setLayout(theAddedLayout.back());
    // addedMaterial[numAddedTabs] = new MaterialMPM();
    // addedGeometry[numAddedTabs] = new GeometryMPM();
    // addedAlgorithm[numAddedTabs] = new AlgorithmMPM();
    // addedPartition[numAddedTabs] = new PartitionMPM();

    // modelAddedTabWidget[numAddedTabs]->addTab(addedMaterial[numAddedTabs],"Material");
    // modelAddedTabWidget[numAddedTabs]->addTab(addedGeometry[numAddedTabs],"Geometry");
    // modelAddedTabWidget[numAddedTabs]->addTab(addedAlgorithm[numAddedTabs],"Algorithm");
    // modelAddedTabWidget[numAddedTabs]->addTab(addedPartition[numAddedTabs],"Partition");
    // theAddedLayout[numAddedTabs]->addWidget(modelAddedTabWidget[numAddedTabs]);

    // tabWidget->addTab(theAdded[tabWidget->count() - numDefaultTabs], QIcon(QString(":/icons/pencil-plus-white.svg")), "Custom Body " + QString::number(tabWidget->count() - numDefaultTabs + 2));

    // numAddedTabs += 1;
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


  ///%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  // // Fluid in Flume Facility
  // QGridLayout *fluidLayout = new QGridLayout();
  // theFluid->setLayout(fluidLayout);

  ///%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  // QWidget *fluidGeometry = new QWidget();
  // QWidget *fluidMaterial = new QWidget();
  // QWidget *fluidAlgorithm = new QWidget();
  // QWidget *fluidPartition = new QWidget();

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

  // int numRow = 0;

  // fluidLayout->addWidget(modelFluidTabWidget);
  // -----------------

  // // --- Geometry

  // int numRow = 2;
  
  // QStringList facilityList; facilityList << "Hinsdale Large Wave Flume (OSU LWF)" << "Hinsdale Directional Wave Basin (OSU DWB)" <<  "Wind-Air-Sea Interaction Facility (UW WASIRF)" << "Waseda University's Tsunami Wave Basin (WU TWB)" << "U.S. Geo. Survey's Debris Flow Flume (USGS DFF)" << "NICHE Full-Scale Wind-Wave Flume" << "INLETOUTLET";
  // facility = new SC_ComboBox("domainSubType",facilityList);
  // fluidGeometryLayout->addWidget(new QLabel("Digital Twin Facility"),numRow,0);
  // fluidGeometryLayout->addWidget(facility,numRow++,1);

  // numRow = 0;
  // standingWaterLevel = new SC_DoubleLineEdit("standingWaterLevel",2.0);
  // fluidGeometryLayout->addWidget(new QLabel("Standing Water Level (SWL)"), numRow, 0);
  // fluidGeometryLayout->addWidget(standingWaterLevel, numRow, 1);  
  // fluidGeometryLayout->addWidget(new QLabel("m"), numRow++, 2);

  // fillFlumeUptoSWL = new SC_CheckBox("fillFlumeUptoSWL");
  // fluidGeometryLayout->addWidget(new QLabel("Fill flume to SWL with fluid?"),numRow, 0);  
  // fluidGeometryLayout->addWidget(fillFlumeUptoSWL,numRow++, 1);
  
  // QGroupBox *dimensionsBox = new QGroupBox("Flume Facility Domain");
  // QGridLayout *dimensionsBoxLayout = new QGridLayout();
  // dimensionsBox->setLayout(dimensionsBoxLayout);

  // numRow = 0;  
  // flumeLength = new SC_DoubleLineEdit("flumeLength",104.0);  
  // flumeHeight = new SC_DoubleLineEdit("flumeHeight",4.6);  
  // flumeWidth = new SC_DoubleLineEdit("flumeWidth",3.658);
  // dimensionsBoxLayout->addWidget(new QLabel("Dimensions (X,Y,Z)"), numRow, 0);
  // dimensionsBoxLayout->addWidget(flumeLength, numRow, 1);  
  // dimensionsBoxLayout->addWidget(flumeHeight, numRow, 2);  
  // dimensionsBoxLayout->addWidget(flumeWidth, numRow, 3);  
  // dimensionsBoxLayout->addWidget(new QLabel("m"), numRow++, 4);

  // flumeOriginX = new SC_DoubleLineEdit("flumeOriginX",0.0);
  // flumeOriginY = new SC_DoubleLineEdit("flumeOriginY",0.0);
  // flumeOriginZ = new SC_DoubleLineEdit("flumeOriginZ",0.0);
  // dimensionsBoxLayout->addWidget(new QLabel("Origin (X,Y,Z)"), numRow, 0);  
  // dimensionsBoxLayout->addWidget(flumeOriginX, numRow,1);
  // dimensionsBoxLayout->addWidget(flumeOriginY, numRow,2);
  // dimensionsBoxLayout->addWidget(flumeOriginZ, numRow,3);
  // dimensionsBoxLayout->addWidget(new QLabel("m"), numRow++, 4);  
  // fluidGeometryLayout->addWidget(dimensionsBox,3,0,2,5);

  // QStringList bathXZHeadings; bathXZHeadings << "Position Along Flume (X) [m]" << "Height (Y) [m]";
  // QStringList dataBathXZ; dataBathXZ << "35" << "0" << "42" << "1.75" << "56" << "2.5" << "105" << "2.5";
  // bathXZData = new SC_TableEdit("bathXZData",bathXZHeadings, 4, dataBathXZ);

  // fluidGeometryLayout->addWidget(new QLabel("Bathymetry"),5,0,1,4);    
  // fluidGeometryLayout->addWidget(bathXZData,6,0,1,4);  

  // // fluidGeometryLayout->setRowStretch(numRow,1);

  // // Connect the facility QComboBox to change entries to default values if selected
  // connect(facility, &QComboBox::currentTextChanged, [=](QString val) {
  //   if (val == "Hinsdale Large Wave Flume (OSU LWF)") {
  //     flumeLength->setText("104.0");
  //     flumeHeight->setText("4.6");
  //     flumeWidth->setText("3.658");
  //   } else if (val == "Hinsdale Directional Wave Basin (OSU DWB)") {
  //     flumeLength->setText("48.8");
  //     flumeWidth->setText("2.1");
  //     flumeHeight->setText("26.5");
  //   } else if (val == "Wind-Air-Sea Interaction Facility (UW WASIRF)") {
  //     flumeLength->setText("12.19");
  //     flumeHeight->setText("1.22");
  //     flumeWidth->setText("0.914");
  //   } else if (val == "Waseda University's Tsunami Wave Basin (WU TWB)") {
  //     flumeLength->setText("9.0");
  //     flumeHeight->setText("1.0");
  //     flumeWidth->setText("4.0");
  //   } else if (val == "U.S. Geo. Survey's Debris Flow Flume (USGS DFF)") {
  //     flumeLength->setText("90.0");
  //     flumeHeight->setText("2.0");
  //     flumeWidth->setText("2.0");
  //   } 
  // });


  // --- Material

  // QGridLayout *fluidMaterialLayout = new QGridLayout();
  // fluidMaterial->setLayout(fluidMaterialLayout);

  // numRow = 0;
  // QStringList fluidMaterialTypeList;fluidMaterialTypeList << "Water (Preset)" << "Custom";
  // fluidMaterialType = new SC_ComboBox("fluidMaterialType", fluidMaterialTypeList);
  // fluidMaterialLayout->addWidget(new QLabel("Material Type"),numRow, 0);
  // fluidMaterialLayout->addWidget(fluidMaterialType, numRow++, 1);

  // fluidDensity = new SC_DoubleLineEdit("fluidDensity", 1000.0);
  // fluidMaterialLayout->addWidget(new QLabel("Density"),numRow, 0);
  // fluidMaterialLayout->addWidget(fluidDensity, numRow, 1);
  // fluidMaterialLayout->addWidget(new QLabel("kg/m^3"),numRow++, 2);

  // fluidViscosity = new SC_DoubleLineEdit("fluidViscosity", 1.0);
  // fluidMaterialLayout->addWidget(new QLabel("Viscosity"),numRow, 0);
  // fluidMaterialLayout->addWidget(fluidViscosity, numRow, 1);
  // fluidMaterialLayout->addWidget(new QLabel("N*sec."),numRow++, 2);

  // fluidBulkModulus = new SC_DoubleLineEdit("fluidBulkModulus", 2.2e7);
  // fluidMaterialLayout->addWidget(new QLabel("Bulk Modulus"),numRow, 0);
  // fluidMaterialLayout->addWidget(fluidBulkModulus, numRow, 1);
  // fluidMaterialLayout->addWidget(new QLabel("Pa"),numRow++, 2);

  // fluidBulkModulusDerivative = new SC_DoubleLineEdit("fluidBulkModulusDerivative", 7.15);
  // fluidMaterialLayout->addWidget(new QLabel("Bulk Modulus Derivative"),numRow, 0);
  // fluidMaterialLayout->addWidget(fluidBulkModulusDerivative, numRow++, 1);
  // fluidMaterialLayout->setRowStretch(numRow,1);

  // --- Algorithm

  // QGridLayout *fluidAlgorithmLayout = new QGridLayout();
  // fluidAlgorithm->setLayout(fluidAlgorithmLayout);

  // numRow = 0;

  // QStringList fluidNumericalMethodList;fluidNumericalMethodList << "Particles" << "Mesh";
  // fluidNumericalMethod = new SC_ComboBox("fluidNumericalMethod", fluidNumericalMethodList);
  // fluidAlgorithmLayout->addWidget(new QLabel("Numerical Method"),numRow, 0);
  // fluidAlgorithmLayout->addWidget(fluidNumericalMethod, numRow++, 1);

  // fluidParticlesPerCell = new SC_DoubleLineEdit("fluidParticlesPerCell", 8.0);
  // fluidAlgorithmLayout->addWidget(new QLabel("Particles Per Cell"),numRow, 0);
  // fluidAlgorithmLayout->addWidget(fluidParticlesPerCell, numRow++, 1);

  // fluidUseASFLIP = new SC_CheckBox("fluidUseASFLIP");
  // fluidAlgorithmLayout->addWidget(new QLabel("Use ASFLIP?"),numRow, 0);
  // fluidAlgorithmLayout->addWidget(fluidUseASFLIP, numRow++, 1);

  // fluidASFLIP_alpha = new SC_DoubleLineEdit("fluidASFLIP_alpha", 0.0);
  // fluidAlgorithmLayout->addWidget(new QLabel("ASFLIP alpha"),numRow, 0);
  // fluidAlgorithmLayout->addWidget(fluidASFLIP_alpha, numRow++, 1);

  // fluidASFLIP_betaMin = new SC_DoubleLineEdit("fluidASFLIP_betaMin", 0.0);
  // fluidAlgorithmLayout->addWidget(new QLabel("ASFLIP betaMin"),numRow, 0);
  // fluidAlgorithmLayout->addWidget(fluidASFLIP_betaMin, numRow++, 1);

  // fluidASFLIP_betaMax = new SC_DoubleLineEdit("fluidASFLIP_betaMax", 0.0);
  // fluidAlgorithmLayout->addWidget(new QLabel("ASFLIP betaMax"),numRow, 0);
  // fluidAlgorithmLayout->addWidget(fluidASFLIP_betaMax, numRow++, 1);


  // fluidUseFBAR = new SC_CheckBox("fluidUseFBAR");
  // fluidAlgorithmLayout->addWidget(new QLabel("Use FBAR?"),numRow, 0);
  // fluidAlgorithmLayout->addWidget(fluidUseFBAR, numRow++, 1);

  // fluidFBAR_psi = new SC_DoubleLineEdit("fluidFBAR_psi", 0.0);
  // fluidAlgorithmLayout->addWidget(new QLabel("FBAR psi"),numRow, 0);
  // fluidAlgorithmLayout->addWidget(fluidFBAR_psi, numRow++, 1);

  // fluidUseFBAR_fusedG2P2G = new SC_CheckBox("fluidUseFBAR_fusedG2P2G");
  // fluidAlgorithmLayout->addWidget(new QLabel("Use FBAR with G2P2G kernel?"),numRow, 0);
  // fluidAlgorithmLayout->addWidget(fluidUseFBAR_fusedG2P2G, numRow++, 1);

  // fluidAlgorithmLayout->setRowStretch(numRow,1);
  
  // --- Partition


  // ------

  // QGridLayout *fluidPartitionLayout = new QGridLayout();
  // fluidPartition->setLayout(fluidPartitionLayout);

  // numRow = 0;




  //
  // instead of more classes lets just do simple tabbed widgets
  //

  /*
  // 1. initial conditions
  stillWaterLevel = new SC_DoubleLineEdit("stillWaterLevel",2.0);
  initVel = new SC_DoubleLineEdit("initVelocity",0.0);
  velFile = new SC_FileEdit("velocityFile");
  refPressure = new SC_DoubleLineEdit("refPressure",0.0);
  
  QGridLayout *initLayout = new QGridLayout();
  theObstacles->setLayout(initLayout);
  
  initLayout->addWidget(new QLabel("Still Water Level"),0,0);

  initLayout->addWidget(new QLabel("Initial Velocity"),1,0);
  initLayout->addWidget(new QLabel("Reference Pressure"),2,0);
  initLayout->addWidget(new QLabel("Velocity Time History File"),3,0);  
  initLayout->addWidget(new QLabel("meters"),0,2);
  initLayout->addWidget(new QLabel("meters/second"),1,2);
  initLayout->addWidget(new QLabel("Pascals"),2,2);
  initLayout->addWidget(stillWaterLevel,0,1);
  initLayout->addWidget(initVel,1,1);
  initLayout->addWidget(refPressure,2,1);
  initLayout->addWidget(velFile,3,1);
  initLayout->setRowStretch(4,1);
  */

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

  // QGridLayout *debrisLayout = new QGridLayout();
  // theDebris->setLayout(debrisLayout);

  // // Per-model body tabs
  // QTabWidget *modelDebrisTabWidget = new QTabWidget();
  // QWidget *theDebrisGeometry = new QWidget();
  // QWidget *theDebrisMaterial = new QWidget();
  // QWidget *theDebrisAlgorithm = new QWidget();
  // QWidget *theDebrisPartition = new QWidget();
  
  // modelDebrisTabWidget->addTab(theDebrisMaterial,"Material");  
  // modelDebrisTabWidget->addTab(theDebrisGeometry,"Geometry");
  // modelDebrisTabWidget->addTab(theDebrisAlgorithm,"Algorithm");
  // modelDebrisTabWidget->addTab(theDebrisPartition,"Partition");
  // debrisLayout->addWidget(modelDebrisTabWidget);
  // // -----------------

  // // --- Geometry
  // QGridLayout *debrisGeometryLayout = new QGridLayout();
  // theDebrisGeometry->setLayout(debrisGeometryLayout);

  // numRow = 0;
  // QStringList listDebris; listDebris << "Rectangular Prisms" << "Spheres" << "Cylinders" << "Car" << "Boat" << "Shipping Container" << "User Input";
  
  // debrisObjectType = new SC_ComboBox("debris_object",listDebris);
  // debrisGeometryLayout->addWidget(new QLabel("Object Type"),numRow,0);
  // debrisGeometryLayout->addWidget(debrisObjectType,numRow++,1);


  // // numRow = 2;
  // debrisLength = new SC_DoubleLineEdit("debris_spanX",0.5);
  // debrisHeight = new SC_DoubleLineEdit("debris_spanY",0.1);
  // debrisWidth = new SC_DoubleLineEdit("debris_spanZ",0.05);
  // debrisGeometryLayout->addWidget(new QLabel("Dimensions (X,Y,Z)"),numRow, 0);
  // debrisGeometryLayout->addWidget(debrisLength,numRow,1);
  // debrisGeometryLayout->addWidget(debrisHeight,numRow,2);
  // debrisGeometryLayout->addWidget(debrisWidth,numRow,3);
  // debrisGeometryLayout->addWidget(new QLabel("m"),numRow++, 4);


  // debrisOriginX = new SC_DoubleLineEdit("debris_offsetX",0.5);
  // debrisOriginY = new SC_DoubleLineEdit("debris_offsetY",0.1);
  // debrisOriginZ = new SC_DoubleLineEdit("debris_offsetZ",0.05);
  // debrisGeometryLayout->addWidget(new QLabel("Origin (X,Y,Z)"),numRow, 0);
  // debrisGeometryLayout->addWidget(debrisOriginX,numRow,1);
  // debrisGeometryLayout->addWidget(debrisOriginY,numRow,2);
  // debrisGeometryLayout->addWidget(debrisOriginZ,numRow,3);
  // debrisGeometryLayout->addWidget(new QLabel("m"),numRow++, 4);


  // debrisArrayX = new SC_IntLineEdit("debris_arrayX",3);
  // debrisArrayY = new SC_IntLineEdit("debris_arrayY",2);
  // debrisArrayZ = new SC_IntLineEdit("debris_arrayZ",4);
  // debrisGeometryLayout->addWidget(new QLabel("Array of Debris (X,Y,Z)"),numRow, 0);
  // debrisGeometryLayout->addWidget(debrisArrayX, numRow,1);
  // debrisGeometryLayout->addWidget(debrisArrayY,numRow,2);
  // debrisGeometryLayout->addWidget(debrisArrayZ,numRow,3);
  // debrisGeometryLayout->addWidget(new QLabel("#"),numRow++, 4);

  // debrisSpacingX = new SC_DoubleLineEdit("debrisSpacingX",0.6);
  // debrisSpacingY = new SC_DoubleLineEdit("debrisSpacingY",0.15);
  // debrisSpacingZ = new SC_DoubleLineEdit("debrisSpacingZ",0.2);
  // debrisGeometryLayout->addWidget(new QLabel("Array Center Spacing (X,Y,Z)"),numRow, 0);
  // debrisGeometryLayout->addWidget(debrisSpacingX,numRow,1);
  // debrisGeometryLayout->addWidget(debrisSpacingY,numRow,2);
  // debrisGeometryLayout->addWidget(debrisSpacingZ,numRow,3);
  // debrisGeometryLayout->addWidget(new QLabel("m"),numRow++, 4);

    
  // debrisGeometryFile = new SC_FileEdit("file");
  // debrisGeometryLayout->addWidget(new QLabel("Debris Geometry File"),numRow, 0);
  // debrisGeometryLayout->addWidget(debrisGeometryFile,numRow++, 1);  

  // debrisGeometryLayout->setRowStretch(numRow,1);

  // // --- Material
  // QGridLayout *debrisMaterialLayout = new QGridLayout();
  // theDebrisMaterial->setLayout(debrisMaterialLayout);

  // numRow = 0;

  // QStringList debrisMaterialTypeList;debrisMaterialTypeList << "Plastic (Preset)" << "Steel (Preset)" << "Concrete (Preset)" << "Wood (Preset)" << "Custom";  
  // debrisMaterialType = new SC_ComboBox("debris_constitutive", debrisMaterialTypeList);
  // debrisMaterialLayout->addWidget(new QLabel("Material Type"),numRow, 0);
  // debrisMaterialLayout->addWidget(debrisMaterialType, numRow++, 1);

  // debrisDensity = new SC_DoubleLineEdit("debris_density", 981);
  // debrisMaterialLayout->addWidget(new QLabel("Density"),numRow, 0);  
  // debrisMaterialLayout->addWidget(debrisDensity, numRow, 1);
  // debrisMaterialLayout->addWidget(new QLabel("kg/m^3"),numRow++, 2);

  // debrisYoungsModulus = new SC_DoubleLineEdit("debris_youngs_modulus", 2.2e7);
  // debrisMaterialLayout->addWidget(new QLabel("Young's Modulus"),numRow, 0);
  // debrisMaterialLayout->addWidget(debrisYoungsModulus, numRow, 1);
  // debrisMaterialLayout->addWidget(new QLabel("Pa"),numRow++, 2);

  // debrisPoissonsRatio = new SC_DoubleLineEdit("debris_poissons_ratio",0.4);
  // debrisMaterialLayout->addWidget(new QLabel("Poisson's Ratio"),numRow, 0);
  // debrisMaterialLayout->addWidget(debrisPoissonsRatio, numRow, 1);
  // debrisMaterialLayout->addWidget(new QLabel("[0, 0.5)"),numRow++, 2);

  // debrisMaterialLayout->setRowStretch(numRow,1);

  // debrisFrictionAngle = new SC_DoubleLineEdit("debrisFrictionAngle",30.0);
  // debrisMaterialLayout->addWidget(new QLabel("Friction Angle"),numRow, 0);
  // debrisGeometryLayout->addWidget(debrisFrictionAngle, numRow++, 1);

  // debrisDilationAngle = new SC_DoubleLineEdit("debrisDilationAngle",0.0);
  // debrisMaterialLayout->addWidget(new QLabel("Dilation Angle"),numRow, 0);
  // debrisGeometryLayout->addWidget(debrisDilationAngle, numRow++, 1);

  // debrisCohesion = new SC_DoubleLineEdit("debrisCohesion",0.0);
  // debrisMaterialLayout->addWidget(new QLabel("Cohesion"),numRow, 0);
  // debrisGeometryLayout->addWidget(debrisCohesion, numRow++, 1);


  // --- Algorithm



  // --- Partition



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


  // QGridLayout *structLayout = new QGridLayout();
  // theStruct->setLayout(structLayout);


  // // Per-model body tabs
  // QTabWidget *modelStructTabWidget = new QTabWidget();
  // QWidget *theStructGeometry = new QWidget();
  // QWidget *theStructMaterial = new QWidget();
  // QWidget *theStructAlgorithm = new QWidget();
  // QWidget *theStructPartition = new QWidget();
  
  // modelStructTabWidget->addTab(theStructMaterial,"Material");  
  // modelStructTabWidget->addTab(theStructGeometry,"Geometry");
  // modelStructTabWidget->addTab(theStructAlgorithm,"Algorithm");
  // modelStructTabWidget->addTab(theStructPartition,"Partition");
  // structLayout->addWidget(modelStructTabWidget);
  // // -----------------

  // // --- Geometry
  // QGridLayout *structGeometryLayout = new QGridLayout();
  // theStructGeometry->setLayout(structGeometryLayout);


  // numRow = 0;
  // QStringList listObject; listObject << "Orange Box (OSU LWF)" << "Grey Box (UW WASIRF)" << "Obstacles (OSU DWB)" << "Obstacles (WU TWB)" << "Shear Wall" << "Flap" <<  "Breakaway Panel" << "Rectangular Prism";  
  
  // structObjectType = new SC_ComboBox("structObjectType",listObject);
  // structGeometryLayout->addWidget(new QLabel("Object Type"),numRow,0);
  // structGeometryLayout->addWidget(structObjectType,numRow++,1);

  // numRow = 1;
  // structLength = new SC_DoubleLineEdit("structLength",1.016);
  // structHeight = new SC_DoubleLineEdit("structHeight",0.625);
  // structWidth = new SC_DoubleLineEdit("structWidth",1.016);
  // structGeometryLayout->addWidget(new QLabel("Dimensions (X,Y,Z)"),numRow, 0);
  // structGeometryLayout->addWidget(structLength,numRow,1);
  // structGeometryLayout->addWidget(structHeight,numRow,2);
  // structGeometryLayout->addWidget(structWidth,numRow,3);
  // structGeometryLayout->addWidget(new QLabel("m"),numRow++, 4);

  // originLength = new SC_DoubleLineEdit("structOriginX",45.8);
  // originHeight = new SC_DoubleLineEdit("structOriginY",2.0);
  // originWidth = new SC_DoubleLineEdit("structOriginZ",1.325);
  // structGeometryLayout->addWidget(new QLabel("Origin (X,Y,Z)"),numRow, 0);
  // structGeometryLayout->addWidget(originLength,numRow,1);
  // structGeometryLayout->addWidget(originHeight,numRow,2);
  // structGeometryLayout->addWidget(originWidth,numRow,3);
  // structGeometryLayout->addWidget(new QLabel("m"),numRow++, 4);

  // structApplyRotation = new SC_CheckBox("structApplyRotation");
  // structGeometryLayout->addWidget(new QLabel("Apply Rotation?"),numRow, 0);  
  // structGeometryLayout->addWidget(structApplyRotation,numRow++, 1);
  

  // QGroupBox *frictionBox = new QGroupBox("");
  // QGridLayout *frictionBoxLayout = new QGridLayout();
  // frictionBox->setLayout(frictionBoxLayout);
  // numRow = 0;
  
  // structRotateAngleX = new SC_DoubleLineEdit("structRotateAngleX",0.0);
  // structRotateAngleY = new SC_DoubleLineEdit("structRotateAngleY",0.0);
  // structRotateAngleZ = new SC_DoubleLineEdit("structRotateAngleZ",0.0);
  // frictionBoxLayout->addWidget(new QLabel("Rotation Angle on Axis (X,Y,Z)"),numRow, 0);
  // frictionBoxLayout->addWidget(structRotateAngleX,numRow,1);
  // frictionBoxLayout->addWidget(structRotateAngleY,numRow,2);
  // frictionBoxLayout->addWidget(structRotateAngleZ,numRow,3);
  // frictionBoxLayout->addWidget(new QLabel("deg."),numRow++, 4);

  // structRotateFulcrumX = new SC_DoubleLineEdit("structRotateFulcrumX",0.0);
  // structRotateFulcrumY = new SC_DoubleLineEdit("structRotateFulcrumY",0.0);
  // structRotateFulcrumZ = new SC_DoubleLineEdit("structRotateFulcrumZ",0.0);
  // frictionBoxLayout->addWidget(new QLabel("Fulcrum of Rotation (X,Y,Z)"),numRow, 0);
  // frictionBoxLayout->addWidget(structRotateFulcrumX,numRow,1);  
  // frictionBoxLayout->addWidget(structRotateFulcrumY,numRow,2);  
  // frictionBoxLayout->addWidget(structRotateFulcrumZ,numRow,3);  
  // frictionBoxLayout->addWidget(new QLabel("m"),numRow++, 4);

  // numRow = 4;
  // structGeometryLayout->addWidget(frictionBox, numRow, 0, 2, 5);
  

  // // --- Material
  // numRow = 0;
  // QGridLayout *structMaterialLayout = new QGridLayout();
  // theStructMaterial->setLayout(structMaterialLayout);


  // QStringList structMaterialTypeList;structMaterialTypeList << "Aluminum (Preset)" << "Plastic (Preset)" << "Steel (Preset)" << "Concrete (Preset)" << "Wood (Preset)" << "Custom";  
  // structMaterialType = new SC_ComboBox("structMaterialType", structMaterialTypeList);
  // structMaterialLayout->addWidget(new QLabel("Material Type"),numRow, 0);
  // structMaterialLayout->addWidget(structMaterialType, numRow++, 1);  

  // structDensity = new SC_DoubleLineEdit("structDensity", 2700.0);
  // structMaterialLayout->addWidget(new QLabel("Density"),numRow, 0);
  // structMaterialLayout->addWidget(structDensity, numRow, 1);
  // structMaterialLayout->addWidget(new QLabel("kg/m^3"),numRow++, 2);

  // structYoungsModulus = new SC_DoubleLineEdit("structYoungsModulus", 7.2e1);
  // structMaterialLayout->addWidget(new QLabel("Young's Modulus"),numRow, 0);
  // structMaterialLayout->addWidget(structYoungsModulus, numRow, 1);
  // structMaterialLayout->addWidget(new QLabel("Pa"),numRow++, 2);

  // structPoissonsRatio = new SC_DoubleLineEdit("structPoissonsRatio",0.33);
  // structMaterialLayout->addWidget(new QLabel("Poisson's Ratio"),numRow, 0);
  // structMaterialLayout->addWidget(structPoissonsRatio, numRow, 1);
  // structMaterialLayout->addWidget(new QLabel("[0, 0.5)"),numRow++, 2);

  // structMaterialLayout->setRowStretch(numRow,1);

  ///%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // Custom Bodies
  // MPM model-maker pipeline
  // Dynamically add bodies when user clicks "Add Body"
  // int numBodies = 0;
  // int MAX_NUM_BODIES = 12;
  // connect(addBodyButton, &QPushButton::clicked, [=]() {
  //   if (numBodies < MAX_NUM_BODIES) {
  //     customMaterial[numBodies] = new MaterialMPM();
  //     customGeometry[numBodies] = new GeometryMPM();
  //     customAlgorithm[numBodies] = new AlgorithmMPM();
  //     customPartition[numBodies] = new PartitionMPM();

  //     // Per-model body tabs
  //     QTabWidget *modelCustomTabWidget = new QTabWidget();
  //     modelCustomTabWidget->addTab(customMaterial[numBodies],"Material");  
  //     modelCustomTabWidget->addTab(customGeometry[numBodies],"Geometry");
  //     modelCustomTabWidget->addTab(customAlgorithm[numBodies],"Algorithm");
  //     modelCustomTabWidget->addTab(customPartition[numBodies],"Partition");
  //     theCustomLayout->addWidget(modelCustomTabWidget);

  //     numBodies++;
  //   }
  // });


  // for (int i=0; i<MAX_NUM_BODIES; i++) {
  //   customMaterial[i] = new MaterialMPM();
  //   customGeometry[i] = new GeometryMPM();
  //   customAlgorithm[i] = new AlgorithmMPM();
  //   customPartition[i] = new PartitionMPM();
  // }
  // customMaterial = new MaterialMPM();
  // customGeometry = new GeometryMPM();
  // customAlgorithm = new AlgorithmMPM();
  // customPartition = new PartitionMPM();

  // ///%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // QGridLayout *theCustomLayout = new QGridLayout();
  // theCustom->setLayout(theCustomLayout);

  // // Per-model body tabs
  // QTabWidget *modelCustomTabWidget = new QTabWidget();
  // modelCustomTabWidget->addTab(customMaterial,"Material");  
  // modelCustomTabWidget->addTab(customGeometry,"Geometry");
  // modelCustomTabWidget->addTab(customAlgorithm,"Algorithm");
  // modelCustomTabWidget->addTab(customPartition,"Partition");
  // theCustomLayout->addWidget(modelCustomTabWidget);



  // -----------------
  // structLayout->setRowStretch(numRow,1);

  /*
  // 3. Bathymetry .. getting a little more complicated!
  //    need to use ComboBox and StackedWidget
  QGridLayout *theFluidLayout = new QGridLayout();
  theFluid->setLayout(theFluidLayout);
  
  QStringList bathOptions; bathOptions << "Point List" << "STL File";
  bathymetryComboBox = new SC_ComboBox("bathType",bathOptions);
  
  QStringList bathXZHeadings; bathXZHeadings << "Position Along Flume (m)" << "Height (m)";
  QStringList dataBathXZ; dataBathXZ << "35" << "0" << "42" << "1.75" << "56" << "2.5" << "105" << "2.5";
  bathXZData = new SC_TableEdit("bathXZData",bathXZHeadings, 4, dataBathXZ);
  bathSTL = new SC_FileEdit("bathSTL");

  QWidget *ptWidget = new QWidget(); // going to add figure which is why the layout
  QGridLayout *ptLayout = new QGridLayout();
  ptLayout->addWidget(bathXZData, 0, 0);
  ptWidget->setLayout(ptLayout);

  QWidget *stlWidget = new QWidget();
  QGridLayout *stlLayout = new QGridLayout();
  stlLayout->addWidget(new QLabel("Surface File (stl)"),0,0);
  stlLayout->addWidget(bathSTL,0,1);
  stlLayout->setRowStretch(1,1);  
  stlWidget->setLayout(stlLayout);
  
  QStackedWidget *bathStack = new QStackedWidget();
  bathStack->addWidget(ptWidget);
  bathStack->addWidget(stlWidget);

  theFluidLayout->addWidget(new QLabel("Source Bathymetry"), 0,0);
  theFluidLayout->addWidget(bathymetryComboBox,0,1);
  theFluidLayout->addWidget(bathStack,1,0,1,2);

  // connext bathymetry to show correct widget
  connect(bathymetryComboBox, QOverload<int>::of(&QComboBox::activated),
	  bathStack, &QStackedWidget::setCurrentIndex);

  
  // 4. Wave Generation .. as complicated as previous!
  //    need to use ComboBox and StackedWidget
  QGridLayout *theWaveGenLayout = new QGridLayout();
  theDebris->setLayout(theWaveGenLayout);
  
  QStringList genOptions; genOptions << "Preset Paddle Motion" << "Paddle Generated Waves" << "Periodic Waves" << "No Waves";
  waveGenComboBox = new SC_ComboBox("waveType",genOptions);
  
  Debris Geometry File = new SC_FileEdit("paddleDispFile");
  waveMag = new SC_DoubleLineEdit("periodicWaveMagnitude",1.0);
  waveCelerity = new SC_DoubleLineEdit("periodicWaveCelerity",1.0);
  waveRepeatSpeed = new SC_DoubleLineEdit("periodicWaveRepeatPeriod",1.0);

  QWidget *paddleWidget = new QWidget();
  QGridLayout *paddleLayout = new QGridLayout();
  paddleLayout->addWidget(new QLabel("Paddle Displacement File"),0,0);
  paddleLayout->addWidget(Debris Geometry File,0,1);
  paddleLayout->setRowStretch(1,1);  
  paddleWidget->setLayout(paddleLayout);

  QWidget *periodicWidget = new QWidget();
  QGridLayout *periodicLayout = new QGridLayout();  
  periodicLayout->addWidget(waveMag,0,1);
  periodicLayout->addWidget(waveCelerity,1,1);
  periodicLayout->addWidget(waveRepeatSpeed,2,1);
  
  periodicLayout->addWidget(new QLabel("Height"),0,0);
  periodicLayout->addWidget(new QLabel("meter"),0,2);
  periodicLayout->addWidget(new QLabel("Celerity"),1,0);
  periodicLayout->addWidget(new QLabel("meters/sec"),1,2);
  periodicLayout->addWidget(new QLabel("Repeat Period"),2,0);
  periodicLayout->addWidget(new QLabel("sec."),2,2);
  periodicLayout->setRowStretch(4,1);
  periodicWidget->setLayout(periodicLayout);

  
  QStackedWidget *waveGenStack = new QStackedWidget();
  waveGenStack->addWidget(paddleWidget);
  waveGenStack->addWidget(periodicWidget);  

  theWaveGenLayout->addWidget(new QLabel("Generation Method"),0,0);
  theWaveGenLayout->addWidget(waveGenComboBox,0,1);
  theWaveGenLayout->addWidget(waveGenStack,1,0,1,2);
  
  // connext bathymetry to show correct widget
  connect(waveGenComboBox, QOverload<int>::of(&QComboBox::activated),
	  waveGenStack, &QStackedWidget::setCurrentIndex);
  */

}

ParticlesMPM::~ParticlesMPM()
{

}

bool
ParticlesMPM::outputToJSON(QJsonObject &jsonObject)
{
  // theOpenSeesPyScript->outputToJSON(jsonObject);
  // theSurfaceFile->outputToJSON(jsonObject);  
  fluidGeometry->outputToJSON(jsonObject);
  fluidMaterial->outputToJSON(jsonObject);
  fluidAlgorithm->outputToJSON(jsonObject);
  fluidPartition->outputToJSON(jsonObject);
  // fluidOutputs->outputToJSON(jsonObject);
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


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

#include "MaterialMPM.h"
#include <QLabel>
#include <QComboBox>
#include <QGroupBox>
#include <QGridLayout>
#include <QTabWidget>
#include <QStackedWidget>
#include <QDebug>

#include <SC_ComboBox.h>
#include <SC_DoubleLineEdit.h>
#include <SC_IntLineEdit.h>
#include <SC_StringLineEdit.h>
#include <SC_TableEdit.h>
#include <SC_FileEdit.h>
#include <SC_CheckBox.h>


MaterialMPM::MaterialMPM(QWidget *parent)
  :SimCenterWidget(parent)
{

  // --- Material
  QGridLayout *layout = new QGridLayout();
  this->setLayout(layout);

  int numRow = 0;


  QStringList fluidMaterialPresetList; fluidMaterialPresetList << "Water (Ocean)" << "Water (Pure)" << "Water (Soft)" << "Sand" << "Custom";  
  QStringList debrisMaterialPresetList; debrisMaterialPresetList << "Plastic" << "Rubber" <<  "Aluminum" << "Concrete" << "Wood" << "Custom";  
  QStringList structurePresetList; structurePresetList << "Aluminum" << "Concrete" << "Wood" << "Custom";  
  QStringList geotechPresetList; geotechPresetList << "Sand" << "Clay" << "Concrete" << "Wood" << "Water (Ocean)" << "Water (Pure)" << "Water (Soft)" << "Custom";  

  QStringList materialPresetList; materialPresetList << "Water (Ocean)" << "Water (Pure)" << "Water (Soft)" << "Plastic" << "Rubber" << "Aluminum" << "Concrete" << "Wood" << "Clay" << "Sand" << "Custom";  
  materialPreset = new SC_ComboBox("material_preset", materialPresetList);
  layout->addWidget(new QLabel("Material Preset"),numRow, 0);
  layout->itemAt(layout->count()-1)->setAlignment(Qt::AlignRight);
  layout->addWidget(materialPreset, numRow++, 1);

  QStringList constitutiveList; constitutiveList << "JFluid" << "FixedCorotated" << "NeoHookean" << "DruckerPrager" << "CamClay" << "VonMises" <<"CoupleUP" << "Custom";  
  constitutive = new SC_ComboBox("constitutive", constitutiveList);
  layout->addWidget(new QLabel("Constitutive Law"),numRow, 0);
  layout->itemAt(layout->count()-1)->setAlignment(Qt::AlignRight);
  layout->addWidget(constitutive, numRow++, 1);

  density = new SC_DoubleLineEdit("CFL", 0.5);
  layout->addWidget(new QLabel("Courant-Friedrich-Lewy Number"),numRow, 0);
  layout->itemAt(layout->count()-1)->setAlignment(Qt::AlignRight);
  layout->addWidget(density, numRow, 1);
  layout->addWidget(new QLabel(""),numRow++, 2);

  density = new SC_DoubleLineEdit("rho", 1000.0);
  layout->addWidget(new QLabel("Density"),numRow, 0);
  layout->itemAt(layout->count()-1)->setAlignment(Qt::AlignRight);
  layout->addWidget(density, numRow, 1);
  layout->addWidget(new QLabel("kg/m^3"),numRow++, 2);

  // ========================
  QStackedWidget *materialStack = new QStackedWidget();
  layout->addWidget(materialStack, numRow++, 0, 1, 3);
  layout->setRowStretch(numRow+1,1);

  // layout->setRowStretch(0,numRow+1);


  // --- JFluid
  QGroupBox *jfluidBox = new QGroupBox();
  QGridLayout *jfluidLayout = new QGridLayout();
  jfluidBox->setLayout(jfluidLayout);
  materialStack->addWidget(jfluidBox);

  numRow = 0;

  bulkModulus = new SC_DoubleLineEdit("bulk_modulus", 2.2e9);
  jfluidLayout->addWidget(new QLabel("Bulk Modulus"),numRow, 0);
  jfluidLayout->itemAt(jfluidLayout->count()-1)->setAlignment(Qt::AlignRight);
  jfluidLayout->addWidget(bulkModulus, numRow, 1);
  jfluidLayout->addWidget(new QLabel("Pa"),numRow++, 2);

  viscosity = new SC_DoubleLineEdit("viscosity", 0.001);
  jfluidLayout->addWidget(new QLabel("Viscosity"),numRow, 0);
  jfluidLayout->itemAt(jfluidLayout->count()-1)->setAlignment(Qt::AlignRight);
  jfluidLayout->addWidget(viscosity, numRow, 1);
  jfluidLayout->addWidget(new QLabel("Poise"),numRow++, 2);

  bulkModulusDerivative = new SC_DoubleLineEdit("gamma", 7.15);
  jfluidLayout->addWidget(new QLabel("Bulk Modulus Derivative"),numRow, 0);
  jfluidLayout->itemAt(jfluidLayout->count()-1)->setAlignment(Qt::AlignRight);
  jfluidLayout->addWidget(bulkModulusDerivative, numRow++, 1);
  jfluidLayout->setRowStretch(0,3);
  // jfluidLayout->setColumnStretch(0,1);


  // lambdaModulus = new SC_DoubleLineEdit("lambda_modulus", 2.2e7);
  // layout->addWidget(new QLabel("First Lamé Parameter"),numRow, 0);
  // layout->addWidget(youngsModulus, numRow, 1);
  // layout->addWidget(new QLabel("Pa"),numRow++, 2);

  // shearModulus = new SC_DoubleLineEdit("shear_modulus", 2.2e7);
  // layout->addWidget(new QLabel("Shear Modulus"),numRow, 0);
  // layout->addWidget(bulkModulus, numRow, 1);
  // layout->addWidget(new QLabel("Pa"),numRow++, 2);

  // --- Hyper-elastic (Fixed-Corotated, Neo-Hookean)
  QGroupBox *hyperElasticBox = new QGroupBox();
  QGridLayout *hyperElasticLayout = new QGridLayout();
  hyperElasticBox->setLayout(hyperElasticLayout);
  materialStack->addWidget(hyperElasticBox);

  numRow = 0;

  youngsModulus = new SC_DoubleLineEdit("youngs_modulus", 2.2e7);
  hyperElasticLayout->addWidget(new QLabel("Young's Modulus"),numRow, 0);
  hyperElasticLayout->itemAt(hyperElasticLayout->count()-1)->setAlignment(Qt::AlignRight);
  hyperElasticLayout->addWidget(youngsModulus, numRow, 1);
  hyperElasticLayout->addWidget(new QLabel("Pa"),numRow++, 2);

  poissonsRatio = new SC_DoubleLineEdit("poisson_ratio",0.4);
  hyperElasticLayout->addWidget(new QLabel("Poisson's Ratio"),numRow, 0);
  hyperElasticLayout->itemAt(hyperElasticLayout->count()-1)->setAlignment(Qt::AlignRight);
  hyperElasticLayout->addWidget(poissonsRatio, numRow, 1);
  hyperElasticLayout->addWidget(new QLabel("[0, 0.5)"),numRow++, 2);
  hyperElasticLayout->setRowStretch(0,2);
  // hyperElasticLayout->setColumnStretch(0,1);


  // --- Drucker-Prager
  QGroupBox *druckerPragerBox = new QGroupBox();
  QGridLayout *druckerPragerLayout = new QGridLayout();
  druckerPragerBox->setLayout(druckerPragerLayout);
  materialStack->addWidget(druckerPragerBox);

  numRow = 0;

  cohesion = new SC_DoubleLineEdit("cohesion",0.0001);
  druckerPragerLayout->addWidget(new QLabel("Cohesion"),numRow, 0);
  druckerPragerLayout->itemAt(druckerPragerLayout->count()-1)->setAlignment(Qt::AlignRight);
  druckerPragerLayout->addWidget(cohesion, numRow, 1);
  druckerPragerLayout->addWidget(new QLabel(""),numRow++, 2);

  frictionAngle = new SC_DoubleLineEdit("friction_angle",30.0);
  druckerPragerLayout->addWidget(new QLabel("Friction Angle"),numRow, 0);
  druckerPragerLayout->itemAt(druckerPragerLayout->count()-1)->setAlignment(Qt::AlignRight);
  druckerPragerLayout->addWidget(frictionAngle, numRow, 1);
  druckerPragerLayout->addWidget(new QLabel("deg."),numRow++, 2);

  useVolumeCorrection = new SC_CheckBox("SandVolCorrection");
  druckerPragerLayout->addWidget(new QLabel("Adjust Volume?"),numRow, 0);
  druckerPragerLayout->itemAt(druckerPragerLayout->count()-1)->setAlignment(Qt::AlignRight);
  druckerPragerLayout->addWidget(useVolumeCorrection, numRow++, 1);

  // beta = new SC_DoubleLineEdit("beta",0.8);
  // druckerPragerLayout->addWidget(new QLabel("Cohesion Coefficient"),numRow, 0);
  // druckerPragerLayout->addWidget(beta, numRow, 1);
  // druckerPragerLayout->addWidget(new QLabel(""),numRow++, 2);


  dilationAngle = new SC_DoubleLineEdit("dilation_angle",0.0);
  druckerPragerLayout->addWidget(new QLabel("Dilation Angle"),numRow, 0);
  druckerPragerLayout->itemAt(druckerPragerLayout->count()-1)->setAlignment(Qt::AlignRight);
  druckerPragerLayout->addWidget(dilationAngle, numRow, 1);
  druckerPragerLayout->addWidget(new QLabel("deg."),numRow++, 2);
  druckerPragerLayout->setRowStretch(0,4);
  // druckerPragerLayout->setColumnStretch(0,1);

  // logJp = new SC_DoubleLineEdit("logJp0", -0.01);
  // druckerPragerLayout->addWidget(new QLabel("Log. of Plastic Vol. Ratio"),numRow, 0);
  // druckerPragerLayout->addWidget(logJp, numRow, 1);
  // druckerPragerLayout->addWidget(new QLabel(""),numRow++, 2);


  // --- Non-Associative Cam-Clay (Wolper 2019, Gaume 2018, Klar 2016)
  QGroupBox *camClayBox = new QGroupBox();
  QGridLayout *camClayLayout = new QGridLayout();
  camClayBox->setLayout(camClayLayout);
  materialStack->addWidget(camClayBox);

  numRow = 0;

  beta = new SC_DoubleLineEdit("beta",0.5);
  camClayLayout->addWidget(new QLabel("Cohesion Coefficient"),numRow, 0);
  camClayLayout->itemAt(camClayLayout->count()-1)->setAlignment(Qt::AlignRight);
  camClayLayout->addWidget(beta, numRow, 1);
  camClayLayout->addWidget(new QLabel(""),numRow++, 2);

  Msqr = new SC_DoubleLineEdit("Msqr",5.57);
  camClayLayout->addWidget(new QLabel("Friction Coef. Squared."),numRow, 0);
  camClayLayout->itemAt(camClayLayout->count()-1)->setAlignment(Qt::AlignRight);
  camClayLayout->addWidget(Msqr, numRow, 1);
  camClayLayout->addWidget(new QLabel(""),numRow++, 2);

  useHardening = new SC_CheckBox("hardeningOn");
  camClayLayout->addWidget(new QLabel("Allow Material Hardening?"),numRow, 0);
  camClayLayout->itemAt(camClayLayout->count()-1)->setAlignment(Qt::AlignRight);
  camClayLayout->addWidget(useHardening, numRow++, 1);

  logJp = new SC_DoubleLineEdit("logJp0", -0.01);
  camClayLayout->addWidget(new QLabel("Log. of Plastic Vol. Ratio"),numRow, 0);
  camClayLayout->itemAt(camClayLayout->count()-1)->setAlignment(Qt::AlignRight);
  camClayLayout->addWidget(logJp, numRow, 1);
  camClayLayout->addWidget(new QLabel(""),numRow++, 2);

  xi = new SC_DoubleLineEdit("xi",0.8);
  camClayLayout->addWidget(new QLabel("Hardening Coefficient"),numRow, 0);
  camClayLayout->itemAt(camClayLayout->count()-1)->setAlignment(Qt::AlignRight);
  camClayLayout->addWidget(xi, numRow, 1);
  camClayLayout->addWidget(new QLabel(""),numRow++, 2);

  camClayLayout->setRowStretch(0,5);
  // camClayLayout->setColumnStretch(0,1);


  // --- Custom
  QGroupBox *customBox = new QGroupBox();
  QGridLayout *customLayout = new QGridLayout();
  customBox->setLayout(customLayout);
  materialStack->addWidget(customBox);
  // layout->setRowStretch(5,1);


  numRow = 0;

  customLayout->addWidget(new QLabel("The selected material's implementation in HydroUQ is still in-progress."),numRow++, 0);
  customLayout->itemAt(customLayout->count()-1)->setAlignment(Qt::AlignCenter);

  // Connect the material preset  QComboBox to change entries to default values if selected
  connect(materialPreset, &QComboBox::currentTextChanged, [=](QString val) {
    if (val == "Water (Pure)") {
      QStringList shortConstitutiveList;  shortConstitutiveList << "JFluid";
      constitutive->clear();
      constitutive->addItems(shortConstitutiveList);
      constitutive->setCurrentIndex(0); 
      density->setText("1000");
      bulkModulus->setText("2.1e9");
      bulkModulusDerivative->setText("7.15");
      viscosity->setText("1.0e-3");
    } else if (val == "Water (Ocean)" ) {
      QStringList shortConstitutiveList;  shortConstitutiveList << "JFluid";
      constitutive->clear();
      constitutive->addItems(shortConstitutiveList);
      constitutive->setCurrentIndex(0);      density->setText("1000");
      bulkModulus->setText("2.3e9");
      bulkModulusDerivative->setText("7.15");
      viscosity->setText("1.15e-3");
    } else if (val == "Water (Soft)") {
      QStringList shortConstitutiveList;  shortConstitutiveList << "JFluid";
      constitutive->clear();
      constitutive->addItems(shortConstitutiveList);
      constitutive->setCurrentIndex(0);
      density->setText("1000");
      bulkModulus->setText("2.2e7");
      bulkModulusDerivative->setText("7.15");
      viscosity->setText("1.0e-3");
    } else if (val == "Plastic") {
      QStringList shortConstitutiveList;  shortConstitutiveList << "FixedCorotated" << "NeoHookean";
      constitutive->clear();
      constitutive->addItems(shortConstitutiveList);
      constitutive->setCurrentIndex(0);
      density->setText("981");
      youngsModulus->setText("1e8");
      poissonsRatio->setText("0.3");
    } else if (val == "Rubber") {
      QStringList shortConstitutiveList;  shortConstitutiveList << "FixedCorotated" << "NeoHookean";
      constitutive->clear();
      constitutive->addItems(shortConstitutiveList);
      constitutive->setCurrentIndex(0);
      density->setText("950");
      youngsModulus->setText("1e5");
      poissonsRatio->setText("0.4");
    } else if (val == "Aluminum") {
      QStringList shortConstitutiveList;  shortConstitutiveList << "FixedCorotated" << "NeoHookean";
      constitutive->clear();
      constitutive->addItems(shortConstitutiveList);
      constitutive->setCurrentIndex(0);
      density->setText("2700");
      youngsModulus->setText("6.9e10");
      poissonsRatio->setText("0.4");
    } else if (val == "Wood") {
      QStringList shortConstitutiveList;  shortConstitutiveList << "FixedCorotated" << "NeoHookean" << "CamClay";
      constitutive->clear();
      constitutive->addItems(shortConstitutiveList);
      constitutive->setCurrentIndex(0);

      density->setText("750");
      youngsModulus->setText("2e9");
      poissonsRatio->setText("0.25");
      
      useHardening->setChecked(true);
      logJp->setText("-0.01");
      xi->setText("0.8");
      beta->setText("1.0");
      Msqr->setText("5.57");
    } else if (val == "Clay") {
      QStringList shortConstitutiveList;  shortConstitutiveList << "CamClay" << "DruckerPrager" << "FixedCorotated" << "NeoHookean" ;
      constitutive->clear();
      constitutive->addItems(shortConstitutiveList);
      constitutive->setCurrentIndex(0);      
      density->setText("1400");
      youngsModulus->setText("5e7");
      poissonsRatio->setText("0.25");
      useVolumeCorrection->setChecked(true);
      frictionAngle->setText("30.0");
      dilationAngle->setText("0.0");
      cohesion->setText("0.0");

      useHardening->setChecked(true);
      logJp->setText("-0.01");
      xi->setText("0.8");
      beta->setText("1.0");
      Msqr->setText("5.57");
    } else if (val == "Concrete") {
      QStringList shortConstitutiveList;  shortConstitutiveList << "CamClay" << "DruckerPrager" << "FixedCorotated" << "NeoHookean";
      constitutive->clear();
      constitutive->addItems(shortConstitutiveList);
      constitutive->setCurrentIndex(0);      
      density->setText("2400");
      youngsModulus->setText("2e7");
      poissonsRatio->setText("0.15");
      useVolumeCorrection->setChecked(true);
      frictionAngle->setText("30.0");
      dilationAngle->setText("0.0");
      cohesion->setText("0.0");

      useHardening->setChecked(true);
      logJp->setText("-0.01");
      xi->setText("0.8");
      beta->setText("1.0");
      Msqr->setText("5.57");
    } else if (val == "Sand") {
      QStringList shortConstitutiveList;  shortConstitutiveList << "DruckerPrager" << "CamClay" ;
      constitutive->clear();
      constitutive->addItems(shortConstitutiveList);
      constitutive->setCurrentIndex(0);      
      density->setText("1400");
      youngsModulus->setText("1e8");
      poissonsRatio->setText("0.2");
      useVolumeCorrection->setChecked(true);
      frictionAngle->setText("30.0");
      dilationAngle->setText("0.0");
      cohesion->setText("0.0");

      useHardening->setChecked(true);
      logJp->setText("-0.01");
      xi->setText("0.8");
      beta->setText("1.0");
      Msqr->setText("5.57");
    } else {
      QStringList shortConstitutiveList;  shortConstitutiveList << "JFluid" << "FixedCorotated" << "NeoHookean" << "DruckerPrager" << "CamClay" << "Custom";  
      constitutive->clear();
      constitutive->addItems(shortConstitutiveList);
      constitutive->setCurrentIndex(0);      density->setText("1400");
      
      bulkModulus->setText("2.1e9");
      bulkModulusDerivative->setText("7.15");
      viscosity->setText("1.0e-3");

      youngsModulus->setText("1e8");
      poissonsRatio->setText("0.2");

      useVolumeCorrection->setChecked(true);
      frictionAngle->setText("30.0");
      dilationAngle->setText("0.0");
      cohesion->setText("0.0");

      useHardening->setChecked(true);
      logJp->setText("-0.01");
      xi->setText("0.8");
      beta->setText("1.0");
      Msqr->setText("5.57");
    }
  });


  connect(constitutive, &QComboBox::currentTextChanged, [=](QString val) {
    if (val == "JFluid") {
      materialStack->setCurrentIndex(0);
    } else if (val == "FixedCorotated") {
      materialStack->setCurrentIndex(1);
    } else if (val == "NeoHookean") {
      materialStack->setCurrentIndex(1);
    } else if (val == "DruckerPrager") {
      materialStack->setCurrentIndex(2);
    } else if (val == "CamClay") {
      materialStack->setCurrentIndex(3);
    } else {
      materialStack->setCurrentIndex(4);
    } 
  });

  connect(useHardening, &QCheckBox::stateChanged, [=](int val) {
    if (val == 2) {
      xi->setEnabled(true);
      beta->setEnabled(true);
      Msqr->setEnabled(true);
      logJp->setEnabled(true);
    } else {
      xi->setEnabled(false);
      beta->setEnabled(false);
      Msqr->setEnabled(false);
      logJp->setEnabled(false);
    }
  });

  connect(useVolumeCorrection, &QCheckBox::stateChanged, [=](int val) {
    if (val == 2) {
      dilationAngle->setEnabled(true);
      logJp->setEnabled(true);
      beta->setEnabled(true);
    } else {
      dilationAngle->setEnabled(false);
      logJp->setEnabled(false);
      beta->setEnabled(false);
    }
  });

}

MaterialMPM::~MaterialMPM()
{

}

bool
MaterialMPM::outputToJSON(QJsonObject &jsonObject)
{
  // theOpenSeesPyScript->outputToJSON(jsonObject);
  // theSurfaceFile->outputToJSON(jsonObject);  
  return true;
}

bool
MaterialMPM::inputFromJSON(QJsonObject &jsonObject)
{
  // theOpenSeesPyScript->inputFromJSON(jsonObject);
  // theSurfaceFile->inputFromJSON(jsonObject);    
  return true;
}

bool
MaterialMPM::copyFiles(QString &destDir)
{
  // if (theOpenSeesPyScript->copyFile(destDir) != true)
  //   return false;
  // return theSurfaceFile->copyFile(destDir);    
  return true;
}


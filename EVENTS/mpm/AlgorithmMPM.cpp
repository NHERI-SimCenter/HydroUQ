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

#include "AlgorithmMPM.h"
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


AlgorithmMPM::AlgorithmMPM(QWidget *parent)
  :SimCenterWidget(parent)
{

  // --- Algorithm
  QGridLayout *layout = new QGridLayout();
  this->setLayout(layout);

  int numRow = 0;

  QStringList numericalMethodList; numericalMethodList << "Particles" << "Mesh" << "Grid";
  numericalMethod = new SC_ComboBox("NumericalMethod", numericalMethodList);
  layout->addWidget(new QLabel("Simulated Body Type"),numRow, 0);
  layout->itemAt(layout->count()-1)->setAlignment(Qt::AlignRight);
  layout->addWidget(numericalMethod, numRow++, 1);

  // --- Particles
  QGroupBox *particlesGroupBox = new QGroupBox();
  QGridLayout *particlesLayout = new QGridLayout();
  particlesGroupBox->setLayout(particlesLayout);
  layout->addWidget(particlesGroupBox, numRow++, 0, 1, 3);

  int numBodyRow = 0;
  particlesPerCell = new SC_DoubleLineEdit("ppc", 8);
  particlesLayout->addWidget(new QLabel("Particles-Per-Cell (PPC)"),numBodyRow, 0);
  particlesLayout->itemAt(particlesLayout->count()-1)->setAlignment(Qt::AlignRight);
  particlesLayout->addWidget(particlesPerCell, numBodyRow, 1);
  particlesLayout->addWidget(new QLabel("(0, 64]"),numBodyRow++, 2);


  useASFLIP = new SC_CheckBox("use_ASFLIP");
  useASFLIP->setChecked(true);
  particlesLayout->addWidget(new QLabel("Use ASFLIP Advection?"),numBodyRow, 0);
  particlesLayout->addWidget(useASFLIP, numBodyRow++, 1);

  QGroupBox *ASFLIPGroupBox = new QGroupBox();
  QGridLayout *ASFLIPLayout = new QGridLayout();
  ASFLIPGroupBox->setLayout(ASFLIPLayout);
  particlesLayout->addWidget(ASFLIPGroupBox, numBodyRow++, 0, 1, 3);
  ASFLIPGroupBox->setVisible(true);

  ASFLIP_alpha = new SC_DoubleLineEdit("alpha", 0.0);
  ASFLIPLayout->addWidget(new QLabel("Velocity Ratio, A"),numBodyRow, 0);
  ASFLIPLayout->itemAt(ASFLIPLayout->count()-1)->setAlignment(Qt::AlignRight);
  ASFLIPLayout->addWidget(ASFLIP_alpha, numBodyRow, 1);
  ASFLIPLayout->addWidget(new QLabel("[0, 1]"),numBodyRow++, 2);
  // ASFLIPLayout->addToolTip("alpha = 0.5 is a good starting point.");
  ASFLIP_betaMin = new SC_DoubleLineEdit("beta_min", 0.0);
  ASFLIPLayout->addWidget(new QLabel("Min. Position Ratio, Min(B)"),numBodyRow, 0);
  ASFLIPLayout->itemAt(ASFLIPLayout->count()-1)->setAlignment(Qt::AlignRight);
  ASFLIPLayout->addWidget(ASFLIP_betaMin, numBodyRow, 1);
  ASFLIPLayout->addWidget(new QLabel("[0, max(B)]"),numBodyRow++, 2);

  ASFLIP_betaMax = new SC_DoubleLineEdit("beta_max", 0.0);
  ASFLIPLayout->addWidget(new QLabel("Max Position Ratio, Max(B)"),numBodyRow, 0);
  ASFLIPLayout->itemAt(ASFLIPLayout->count()-1)->setAlignment(Qt::AlignRight);
  ASFLIPLayout->addWidget(ASFLIP_betaMax, numBodyRow, 1);
  ASFLIPLayout->addWidget(new QLabel("[min(B), 1], typ. < 0.250"),numBodyRow++, 2);

  useFBAR = new SC_CheckBox("use_FBAR");
  useFBAR->setChecked(true);
  particlesLayout->addWidget(new QLabel("Use F-Bar Antilocking?"),numBodyRow, 0);
  particlesLayout->addWidget(useFBAR, numBodyRow++, 1);

  QGroupBox *FBARGroupBox = new QGroupBox();
  QGridLayout *FBARLayout = new QGridLayout();
  FBARGroupBox->setLayout(FBARLayout);
  particlesLayout->addWidget(FBARGroupBox, numBodyRow++, 0, 1, 3);
  FBARGroupBox->setVisible(true);

  FBAR_psi = new SC_DoubleLineEdit("FBAR_ratio", 0.0);
  FBARLayout->addWidget(new QLabel("Vol. Antilocking Ratio"),numBodyRow, 0);
  FBARLayout->addWidget(FBAR_psi, numBodyRow, 1);
  FBARLayout->addWidget(new QLabel("[0, 1], typ. in [0.5, 0.99999]"),numBodyRow++, 2);

  useFBAR_fusedG2P2G = new SC_CheckBox("FBAR_fused_kernel");
  FBARLayout->addWidget(new QLabel("Use Fused MPM (G2P + P2G)?"),numBodyRow, 0);
  FBARLayout->addWidget(useFBAR_fusedG2P2G, numBodyRow++, 1);



  connect(useASFLIP, &QCheckBox::stateChanged, [=](int state) {
    if (state == Qt::Checked) {
      ASFLIPGroupBox->setVisible(true);
      
    } else {
      ASFLIPGroupBox->setVisible(false);
    }
  });


  connect(useFBAR, &QCheckBox::stateChanged, [=](int state) {
    if (state == Qt::Checked) {
      FBARGroupBox->setVisible(true);
    } else {
      FBARGroupBox->setVisible(false);
    }
  });

  connect(numericalMethod, &QComboBox::currentTextChanged, [=](QString val) {
    if (val == "Particles") {
      particlesGroupBox->setVisible(true);
    } else {
      particlesGroupBox->setVisible(false);
    }
  });


  layout->setRowStretch(numRow,1);

  // layout->setRowStretch(numRow, 2);
  layout->setColumnStretch(3, 1);

  // // Connect the material preset  QComboBox to change entries to default values if selected
  // connect(materialPreset, &QComboBox::currentTextChanged, [=](QString val) {
  //   if (val == "Water") {
  //     constitutive->setText("JFluid");
  //     density->setText("1000");
  //     bulkModulus->setText("2.2e9");
  //     bulkModulusDerivative->setText("7.15");
  //     viscosity->setText("1e-3");
  //   } else if (val == "Water (Soft)") {
  //     constitutive->setText("JFluid");
  //     density->setText("1000");
  //     bulkModulus->setText("2.2e7");
  //     bulkModulusDerivative->setText("7.15");
  //     viscosity->setText("1e-3");
  //   } else if (val == "Plastic") {
  //     constitutive->setText("FixedCorotated");
  //     density->setText("981");
  //     youngsModulus->setText("1e8");
  //     poissonsRatio->setText("0.3");
  //   } else if (val == "Rubber") {
  //     constitutive->setText("FixedCorotated");
  //     density->setText("950");
  //     youngsModulus->setText("1e5");
  //     poissonsRatio->setText("0.4");
  //   } else if (val == "Aluminum") {
  //     constitutive->setText("FixedCorotated");
  //     density->setText("2700");
  //     youngsModulus->setText("6.9e10");
  //     poissonsRatio->setText("0.4");
  //   } else if (val == "Wood") {
  //     constitutive->setText("FixedCorotated");
  //     density->setText("750");
  //     youngsModulus->setText("2e9");
  //     poissonsRatio->setText("0.25");
  //   } else if (val == "Clay") {
  //     constitutive->setText("CamClay");
  //     density->setText("1400");
  //     youngsModulus->setText("5e7");
  //     poissonsRatio->setText("0.25");
  //   } else if (val == "Concrete") {
  //     constitutive->setText("NACC");
  //     density->setText("2400");
  //     youngsModulus->setText("2e7");
  //     poissonsRatio->setText("0.15");
  //   } else if (val == "Sand") {
  //     constitutive->setText("DruckerPrager");
  //     density->setText("1400");
  //     youngsModulus->setText("1e8");
  //     poissonsRatio->setText("0.2");
  //   } 
  // });



  // Debris Geometry File = new SC_FileEdit("file");
  // debrisGeometryLayout->addWidget(new QLabel("Debris Geometry File"),numRow, 0);
  // debrisGeometryLayout->addWidget(Debris Geometry File,numRow++, 1);  


  // // connext bathymetry to show correct widget
  // connect(waveGenComboBox, QOverload<int>::of(&QComboBox::activated),
	//   waveGenStack, &QStackedWidget::setCurrentIndex);
  // */

}

AlgorithmMPM::~AlgorithmMPM()
{

}

bool
AlgorithmMPM::outputToJSON(QJsonObject &jsonObject)
{
  // theOpenSeesPyScript->outputToJSON(jsonObject);
  // theSurfaceFile->outputToJSON(jsonObject);  
  return true;
}

bool
AlgorithmMPM::inputFromJSON(QJsonObject &jsonObject)
{
  // theOpenSeesPyScript->inputFromJSON(jsonObject);
  // theSurfaceFile->inputFromJSON(jsonObject);    
  return true;
}

bool
AlgorithmMPM::copyFiles(QString &destDir)
{
  // if (theOpenSeesPyScript->copyFile(destDir) != true)
  //   return false;
  // return theSurfaceFile->copyFile(destDir);    
  return true;
}


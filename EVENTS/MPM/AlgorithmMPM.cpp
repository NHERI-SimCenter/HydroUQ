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
#include <QJsonObject>
#include <QJsonArray>

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
  int maxWidth = 1280;

  QStringList numericalMethodList; numericalMethodList << "particles" << "meshes";
  numericalMethod = new SC_ComboBox("NumericalMethod", numericalMethodList);
  layout->addWidget(new QLabel("Numerical Form"),numRow, 0, 1, 1, Qt::AlignRight);
  layout->addWidget(numericalMethod, numRow++, 1, 1, 2);
  layout->itemAt(layout->count()-1)->widget()->setMaximumWidth(maxWidth);
  // Set tooltip for each combobox item
  numericalMethod->setItemData(0, "Particles represents a material bodies volume with discrete, Lagrangian, points that hold individual material parameters and deformation states. Particles communicate their data with a background grid or neighboring particles in MPM and SPH respectively. See Bonus 2023 (Dissertation), Chapter 5 for more details.", Qt::ToolTipRole);

  numericalMethod->setItemData(1, "Meshes are lagrangian finite elements composed of elements that possess vertex nodes, edges, faces, volume, and discrete integration points which solve material laws and possess material parameters. Mesh element integration points communicate internal forces to vertices, which then contribute a lagrangian force to nearby background grid-nodes. After a global grid-update, vertices adopt the local grid velocity which they use to determine their motion and to send to the element integration points for determination of deformation and stress. Allows for interaction with 'Particles'. See Bonus 2023 (Dissertation), Chapter 5 for more details.", Qt::ToolTipRole);
  for (int i=0; i<2; ++i) layout->itemAt(layout->count()-(1+i))->widget()->setToolTip("Numerical form / representation of the material body in the simulation. See Bonus 2023 (Dissertation) for more details.");

  // --- Particles
  QGroupBox *particlesGroupBox = new QGroupBox("Particle Representation");
  QGridLayout *particlesLayout = new QGridLayout();
  particlesGroupBox->setLayout(particlesLayout);


  // particlesLayout->setRowStretch(numBodyRow,1);
  particlesLayout->setColumnStretch(1,1);
  int numBodyRow = 0;


  QGroupBox *ASFLIPGroupBox = new QGroupBox("ASFLIP Advection");
  QGridLayout *ASFLIPLayout = new QGridLayout();
  ASFLIPLayout->setColumnStretch(1,1);
  ASFLIPGroupBox->setLayout(ASFLIPLayout);

  ASFLIPGroupBox->setVisible(true);

  ASFLIP_alpha = new SC_DoubleLineEdit("alpha", 0.0);
  ASFLIPLayout->addWidget(new QLabel("Velocity Ratio, A"),numBodyRow, 0, 1, 1, Qt::AlignRight);
  ASFLIPLayout->addWidget(ASFLIP_alpha, numBodyRow, 1, 1, 2);
  ASFLIPLayout->itemAt(ASFLIPLayout->count()-1)->widget()->setMaximumWidth(maxWidth);
  ASFLIPLayout->addWidget(new QLabel("[0, 1]"),numBodyRow++, 3, 1, 1);
  for (int i=0; i<3; ++i) ASFLIPLayout->itemAt(ASFLIPLayout->count()-(1+i))->widget()->setToolTip("ASFLIP advection ratio, alpha. Mixes PIC particle velocity (damped) with FLIP velocity (noisey) to balance stability and advection accuracy. Value of zero is no advection, value of one is full advection. For stiff simulations, the range of 0.0 to 0.9 is generally recommended. See Bonus 2023 (Dissertation), Chapter 5, and Fei et al. 2021 (ASFLIP Paper) for more details.");

  // ASFLIPLayout->addToolTip("alpha = 0.5 is a good starting point.");
  ASFLIP_betaMin = new SC_DoubleLineEdit("beta_min", 0.0);
  ASFLIPLayout->addWidget(new QLabel("Min. Position Ratio, b"),numBodyRow, 0, 1, 1, Qt::AlignRight);
  ASFLIPLayout->addWidget(ASFLIP_betaMin, numBodyRow, 1, 1, 2);
  ASFLIPLayout->itemAt(ASFLIPLayout->count()-1)->widget()->setMaximumWidth(maxWidth);
  ASFLIPLayout->addWidget(new QLabel("[0, min(1,B)]"),numBodyRow++, 3, 1, 1);
  for (int i=0; i<3; ++i) ASFLIPLayout->itemAt(ASFLIPLayout->count()-(1+i))->widget()->setToolTip("ASFLIP advection position ratio maximum, Max(Beta). Upper-bound for the linear mix of PIC particle position (damped) with FLIP position (noisey) to balance stability, advection accuracy. Further, partially decouples particle motion from the filtered, sticky MPM grid when a condition is met (e.g. 2 percent volumetric tension on a near-surface particle). Can significantly improve contact between material bodies that are separating or sliding. Value of zero reverts to MPM's sticky contact, value of one fully applies PIC-FLIP velocity modes (throttled by velocity ratio, alpha) on individual particles to their position update. For material bodies that may need non-sticky contact, the range of 0.0 to 0.05 is reasonable but caution is recommended as there is a high-risk for instabilities and penetratative impacts. See Bonus 2023 (Dissertation), Chapter 5, and Fei et al. 2021 (ASFLIP Paper) for more details.");

  ASFLIP_betaMax = new SC_DoubleLineEdit("beta_max", 0.0);
  ASFLIPLayout->addWidget(new QLabel("Max. Position Ratio, B"),numBodyRow, 0, 1, 1, Qt::AlignRight);
  ASFLIPLayout->addWidget(ASFLIP_betaMax, numBodyRow, 1, 1, 2);
  ASFLIPLayout->itemAt(ASFLIPLayout->count()-1)->widget()->setMaximumWidth(maxWidth);
  ASFLIPLayout->addWidget(new QLabel("[max(0,b), 1]"),numBodyRow++, 3, 1, 1);
  for (int i=0; i<3; ++i) ASFLIPLayout->itemAt(ASFLIPLayout->count()-(1+i))->widget()->setToolTip("ASFLIP advection position ratio maximum, Max(Beta). Upper-bound for the linear mix of PIC particle position (damped) with FLIP position (noisey) to balance stability, advection accuracy. Further, partially decouples particle motion from the filtered, sticky MPM grid when a condition is met (e.g. 5 percent volumetric tension on a near-surface particle). Can significantly improve contact between material bodies that are separating or sliding. Value of zero reverts to MPM's sticky contact, value of one fully applies PIC-FLIP velocity modes (throttled by velocity ratio, alpha) on individual particles to their position update. For material bodies that may need non-sticky contact, the range of 0.0 to 0.25 is reasonable but caution is recommended as there is a high-risk for instabilities and penetratative impacts. See Bonus 2023 (Dissertation), Chapter 5, and Fei et al. 2021 (ASFLIP Paper) for more details.");
  ASFLIPLayout->setColumnStretch(1,1);

  useFBAR = new SC_CheckBox("use_FBAR");
  useFBAR->setChecked(true);
  particlesLayout->addWidget(new QLabel("Use F-Bar Antilocking?"),numBodyRow, 0, 1, 1, Qt::AlignRight);
  particlesLayout->addWidget(useFBAR, numBodyRow++, 1, 1, 2);
  for (int i=0; i<2; ++i) particlesLayout->itemAt(particlesLayout->count()-(1+i))->widget()->setToolTip("Antilocking technique for pressure-field smoothing. Helps to stabilize stiff simulations, improve fluid flow, and produce more reasonable pressure gradients. It does so by grid-averaging particle volumetric deformations used in the particle stress computation. Recommended to use FBAR for stiff fluid simulations. See Bonus 2023 (Dissertation), Chapter 5 and Zhao et al. 2023 for more details.");

  QGroupBox *FBARGroupBox = new QGroupBox("FBAR Antilocking");
  QGridLayout *FBARLayout = new QGridLayout();
  FBARGroupBox->setLayout(FBARLayout);
  FBARGroupBox->setVisible(true);


  FBAR_psi = new SC_DoubleLineEdit("FBAR_ratio", 0.0);
  FBARLayout->addWidget(new QLabel("Antilocking Ratio"),numBodyRow, 0, 1, 1, Qt::AlignRight);
  FBARLayout->addWidget(FBAR_psi, numBodyRow, 1, 1, 2);
  FBARLayout->itemAt(FBARLayout->count()-1)->widget()->setMaximumWidth(maxWidth);
  FBARLayout->addWidget(new QLabel("[0, 1]"),numBodyRow++, 3, 1, 1);
  for (int i=0; i<3; ++i) FBARLayout->itemAt(FBARLayout->count()-(1+i))->widget()->setToolTip("FBAR antilocking ratio, psi. Mixes standard particle deformation with antilocked deformation to balance stability and pressure-field smoothness. Value of zero is no antilocking, value of one is full antilocking. For stiff simulations, the range of 0.25 to 0.9999 is generally recommended. See Bonus 2023 (Dissertation), Chapter 5 for more details.");

  useFBAR_fusedG2P2G = new SC_CheckBox("FBAR_fused_kernel");
  FBARLayout->addWidget(new QLabel("Use G2P2G?"), numBodyRow, 0, 1, 1, Qt::AlignRight);
  FBARLayout->addWidget(useFBAR_fusedG2P2G, numBodyRow++, 1, 1, 2);
  for (int i=0; i<2; ++i) FBARLayout->itemAt(FBARLayout->count()-(1+i))->widget()->setToolTip("Traditional MPM uses separate Grid-to-Particle (G2P) and Particle-to-Grid (P2G) steps. This option fuses them into a single kernel (G2P2G, Wang et al. 2020) for MLS-MPM. G2P2G is faster, but may have some effect on FBAR antilocking stability. See Bonus 2023 (Dissertation), Chapters 2 and 5 for more details.");
  FBARLayout->setColumnStretch(1,1);


  numBodyRow = 0;
  particlesPerCell = new SC_DoubleLineEdit("ppc", 8.0);
  particlesLayout->addWidget(new QLabel("Particles-Per-Cell (PPC)"),numBodyRow, 0, 1, 1, Qt::AlignRight);
  particlesLayout->addWidget(particlesPerCell, numBodyRow, 1, 1, 2);
  particlesLayout->itemAt(particlesLayout->count()-1)->widget()->setMaximumWidth(maxWidth);
  particlesLayout->addWidget(new QLabel("(0, 64]"),numBodyRow++, 3, 1, 1);
  for (int i=0; i<3; ++i) particlesLayout->itemAt(particlesLayout->count()-(1+i))->widget()->setToolTip("Number of particles per 3D grid-cell (PPC). Particles are distributed according to Newton-Cotes (not Gauss-Seidel), i.e. initial uniform particle spacing of S = dx / PPC^(1/3), where dx is the grid-cell length, and an initial particle to nearest grid-node/cell-center of ([1.5 S]^2)^(0.5). Higher PPC values allow for fine-scaled resolution of stress, material state, etc. within grid-cells. However, large PPC values may be bottlenecked by the comparatively few grid-cells available to aggregate particle information, though ASFLIP advection and FBAR antilocking help to alleviate this. Raising PPC raises simulation memory usage and computational time proportionally. Ideally, have PPC = N^3 where N is a postive integer (1,2,3,...). PPC < 3 struggles to guarantee non-penetration of particle bodies. PPC = 8 is recommended for efficiency and reasonable accuracy, with 27 or 64 for refined analysis.");

  useASFLIP = new SC_CheckBox("use_ASFLIP");
  useASFLIP->setChecked(true);
  particlesLayout->addWidget(new QLabel("Use ASFLIP Advection?"),numBodyRow, 0, Qt::AlignRight);
  particlesLayout->addWidget(useASFLIP, numBodyRow++, 1);
  particlesLayout->itemAt(particlesLayout->count()-1)->widget()->setMaximumWidth(maxWidth);
  for (int i=0; i<2; ++i) particlesLayout->itemAt(particlesLayout->count()-(1+i))->widget()->setToolTip("Affine-Separable Fluid-Implicit-Particle (ASFLIP) advection is a particle advection technique (i.e. update of position and velocity) that reduces the loss of energy in stiff material simulations, improve general fluid flow, and allows particles to preserve velocity modes that may otherwise be filtered out (useful for coarse grid simulations which otherwise damp out fine-scale motion). It does so by grid-averaging particle velocities used in the particle stress computation. Recommended to use ASFLIP for stiff fluid simulations. See Bonus 2023 (Dissertation), Chapter 5 and Fei et al. 2021 (ASFLIP Paper) for more details.");
  particlesLayout->addWidget(ASFLIPGroupBox, numBodyRow++, 0, 1, 4);
  numBodyRow = numBodyRow + 1; // Spacer for detached group box title
  particlesLayout->addWidget(FBARGroupBox, numBodyRow++, 0, 1, 4);

  // --- Meshes
  QGroupBox *meshesGroupBox = new QGroupBox("Mesh Representation");
  QGridLayout *meshesLayout = new QGridLayout();
  meshesGroupBox->setLayout(meshesLayout);
  // layout->addWidget(meshesGroupBox, numRow++, 0, 1, 3);
  numBodyRow = 0;
  // meshesLayout->addWidget(new QLabel("To be re-implemented."),numBodyRow++, 0);
  meshesLayout->addWidget(new QLabel("Finite element meshes to be re-implemented soon."),numBodyRow++, 0,1,4, Qt::AlignCenter);
  meshesLayout->setRowStretch(1, 1);
  meshesLayout->setColumnStretch(0,1);
  QStackedWidget *stackedWidget = new QStackedWidget();
  stackedWidget->addWidget(particlesGroupBox);
  stackedWidget->addWidget(meshesGroupBox);
  layout->addWidget(stackedWidget, numRow++, 0, 1, 4);
  layout->setRowStretch(numRow, 1);
  layout->setColumnStretch(1,1);

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
    if (val == "Particles" || val == "particles") {
      particlesGroupBox->setVisible(true);
    } else {
      particlesGroupBox->setVisible(false);
    }

    if (val == "Meshes" || val == "meshes") {
      meshesGroupBox->setVisible(true);
    } else {
      meshesGroupBox->setVisible(false);
    }

  });


  connect(particlesPerCell, &QLineEdit::textChanged, [=](QString val) {
    if (val.toDouble() < 1.0) {
      particlesPerCell->setText("1.0");
    } else if (val.toDouble() > 64.0) {
      particlesPerCell->setText("64.0");
    }
  });

  connect(ASFLIP_alpha, &QLineEdit::textChanged, [=](QString val) {
    if (val.toDouble() < 0.0) {
      ASFLIP_alpha->setText("0.0");
    } else if (val.toDouble() > 1.0) {
      ASFLIP_alpha->setText("1.0");
    }
  });

  connect(ASFLIP_betaMin, &QLineEdit::textChanged, [=](QString val) {
    if (val.toDouble() < 0.0) {
      ASFLIP_betaMin->setText("0.0");
    } else if (val.toDouble() > ASFLIP_betaMax->text().toDouble()) {
      ASFLIP_betaMin->setText(ASFLIP_betaMax->text());
    }
  });

  connect(ASFLIP_betaMax, &QLineEdit::textChanged, [=](QString val) {
    if (val.toDouble() < ASFLIP_betaMin->text().toDouble()) {
      ASFLIP_betaMax->setText(ASFLIP_betaMin->text());
    } else if (val.toDouble() > 1.0) {
      ASFLIP_betaMax->setText("1.0");
    }
  });



}

AlgorithmMPM::~AlgorithmMPM()
{

}

bool
AlgorithmMPM::outputToJSON(QJsonObject &jsonObject)
{
  // theOpenSeesPyScript->outputToJSON(jsonObject);
  // theSurfaceFile->outputToJSON(jsonObject);  

  // Note: ClaymoreUW will also need these defined in the JSON model/body object, not just the nested JSON partition/device object
  // Future schema
  QJsonObject algorithmObject;
  algorithmObject["type"] = numericalMethod->currentText();
  algorithmObject["ppc"] = particlesPerCell->text().toDouble();
  algorithmObject["use_ASFLIP"] = useASFLIP->isChecked();
  algorithmObject["use_FBAR"] = useFBAR->isChecked();
  algorithmObject["FBAR_fused_kernel"] = useFBAR_fusedG2P2G->isChecked();
  algorithmObject["ASFLIP_alpha"] = ASFLIP_alpha->text().toDouble();
  algorithmObject["ASFLIP_beta_min"] = ASFLIP_betaMin->text().toDouble();
  algorithmObject["ASFLIP_beta_max"] = ASFLIP_betaMax->text().toDouble();
  algorithmObject["FBAR_psi"] = FBAR_psi->text().toDouble();
  jsonObject["algorithm"] = algorithmObject;

  // ClaymoreUW artifacts, Global algorithm settings. TODO: Deprecate
  // jsonObject["type"] = numericalMethod->currentText();
  // jsonObject["ppc"] = particlesPerCell->text().toDouble();
  // jsonObject["use_ASFLIP"] = useASFLIP->isChecked();
  // jsonObject["use_FBAR"] = useFBAR->isChecked();
  // jsonObject["FBAR_fused_kernel"] = useFBAR_fusedG2P2G->isChecked(); // TODO: Rename
  // jsonObject["alpha"] = ASFLIP_alpha->text().toDouble(); // TODO: Rename
  // jsonObject["beta_min"] = ASFLIP_betaMin->text().toDouble(); // TODO: Rename
  // jsonObject["beta_max"] = ASFLIP_betaMax->text().toDouble(); // TODO: Rename
  // jsonObject["FBAR_ratio"] = FBAR_psi->text().toDouble(); // TODO: Rename?

  return true;
}

bool
AlgorithmMPM::inputFromJSON(QJsonObject &jsonObject)
{


  if (jsonObject.contains("algorithm")) {
    QJsonObject algorithmObject = jsonObject["algorithm"].toObject();
    if (algorithmObject.contains("type")) {
      QString type = algorithmObject["type"].toString();
      int index = numericalMethod->findText(type);
      if (index != -1) {
        numericalMethod->setCurrentIndex(index);
      }
    }
    if (algorithmObject.contains("ppc")) {
      particlesPerCell->setText(QString::number(algorithmObject["ppc"].toDouble()));
    }
    if (algorithmObject.contains("use_ASFLIP")) {
      useASFLIP->setChecked(algorithmObject["use_ASFLIP"].toBool());
    }
    if (algorithmObject.contains("use_FBAR")) {
      useFBAR->setChecked(algorithmObject["use_FBAR"].toBool());
    }
    if (algorithmObject.contains("FBAR_fused_kernel")) {
      useFBAR_fusedG2P2G->setChecked(algorithmObject["FBAR_fused_kernel"].toBool());
    }
    if (algorithmObject.contains("ASFLIP_alpha")) {
      ASFLIP_alpha->setText(QString::number(algorithmObject["ASFLIP_alpha"].toDouble()));
    }
    if (algorithmObject.contains("ASFLIP_beta_min")) {
      ASFLIP_betaMin->setText(QString::number(algorithmObject["ASFLIP_beta_min"].toDouble()));
    }
    if (algorithmObject.contains("ASFLIP_beta_max")) {
      ASFLIP_betaMax->setText(QString::number(algorithmObject["ASFLIP_beta_max"].toDouble()));
    }
    if (algorithmObject.contains("FBAR_psi")) {
      FBAR_psi->setText(QString::number(algorithmObject["FBAR_psi"].toDouble()));
    }
  }

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

void AlgorithmMPM::enableFBAR(bool isChecked = true) {
  useFBAR->setChecked(isChecked);
}

void AlgorithmMPM::enableASFLIP(bool isChecked = true) {
  useASFLIP->setChecked(isChecked);
}

void AlgorithmMPM::enableFBAR_fusedG2P2G(bool isChecked = true) {
  useFBAR_fusedG2P2G->setChecked(isChecked);
}

void AlgorithmMPM::disableFBAR(bool isChecked = true) {
  useFBAR->setChecked(!isChecked);
}

void AlgorithmMPM::disableASFLIP(bool isChecked = true) {
  useASFLIP->setChecked(!isChecked);
}

void AlgorithmMPM::disableFBAR_fusedG2P2G(bool isChecked = true) {
  useFBAR_fusedG2P2G->setChecked(!isChecked);
}


void AlgorithmMPM::setFBAR_psi(double psi = 0.0) {
  psi = (psi < 0.0) ? 0.0 : (psi > 1.0) ? 1.0 : psi;
  FBAR_psi->setText(QString::number(psi));
}

void AlgorithmMPM::setASFLIP_alpha(double alpha = 0.0) {
  alpha = (alpha < 0.0) ? 0.0 : (alpha > 1.0) ? 1.0 : alpha;
  ASFLIP_alpha->setText(QString::number(alpha));
}

void AlgorithmMPM::setASFLIP_betaMin(double betaMin = 0.0) {
  betaMin = (betaMin < 0.0) ? 0.0 : (betaMin > ASFLIP_betaMax->text().toDouble()) ? ASFLIP_betaMax->text().toDouble() : betaMin;
  ASFLIP_betaMin->setText(QString::number(betaMin));
}

void AlgorithmMPM::setASFLIP_betaMax(double betaMax = 0.0) {
  betaMax = (betaMax < ASFLIP_betaMin->text().toDouble()) ? ASFLIP_betaMin->text().toDouble() : (betaMax > 1.0) ? 1.0 : betaMax;
  ASFLIP_betaMax->setText(QString::number(betaMax));
}

double AlgorithmMPM::getFBAR_psi() {
  return FBAR_psi->text().toDouble();
}

double AlgorithmMPM::getASFLIP_alpha() {
  return ASFLIP_alpha->text().toDouble();
}

double AlgorithmMPM::getASFLIP_betaMin() {
  return ASFLIP_betaMin->text().toDouble();
}

double AlgorithmMPM::getASFLIP_betaMax() {
  return ASFLIP_betaMax->text().toDouble();
}



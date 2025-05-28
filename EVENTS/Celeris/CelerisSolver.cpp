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

#include <CelerisSolver.h>
#include <QLabel>
#include <QString>
#include <QGridLayout>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <SC_FileEdit.h>
#include <SC_DoubleLineEdit.h>
#include <SC_IntLineEdit.h>
#include <SC_TableEdit.h>
#include <SimCenterPreferences.h>
#include <QPixmap>
#include <QDebug>
#include <QCoreApplication>
#include <QPushButton>
#include <QProcess>
#include <QStringList>
#include <RandomVariablesContainer.h>
#include <LineEditRV.h>
#include <QGroupBox>
#include <SC_ComboBox.h>
#include <SC_CheckBox.h>
CelerisSolver::CelerisSolver(RandomVariablesContainer* randomVariables, QWidget *parent)
  :SimCenterWidget(parent)
{
    // SC_IntLineEdit *NLSW_or_Bous;
    // SC_DoubleLineEdit *duration;
    // SC_DoubleLineEdit *Courant_num;
    // SC_DoubleLineEdit *whiteWaterDecayRate; // Turbulence decay rate for foam (visualization).
    // SC_DoubleLineEdit *whiteWaterDispersion; // Turbulence dispersion factor.
    // SC_DoubleLineEdit *dissipation_threshold; // Used for visualization (mark cells above certain foam/dissipation).
    // SC_DoubleLineEdit *delta_breaking; // Eddy viscosity coefficient in breaking zones.
    // SC_DoubleLineEdit *Theta; // Midmod limiter parameter (1.0 more dissipative, 2.0 less dissipative). (1.0 upwind, 2.0 centered). 
    // SC_DoubleLineEdit *Bcoef; // Dispersion parameter for Boussinesq model; default 1/15.
    // SC_IntLineEdit *timeScheme; // Time integration scheme: 0 -> Euler, 1 -> 3rd-order predictor, 2 -> 4th-order  predictor/corrector
    // SC_DoubleLineEdit *delta;
    // SC_DoubleLineEdit *epsilon;
    // SC_IntLineEdit *Px;
    // SC_IntLineEdit *Py;
    // SC_DoubleLineEdit *friction;
    // SC_IntLineEdit *useBreakingModel; // True if wave-breaking model is included.
    // SC_IntLineEdit *showBreaking; // If > 0, show wave breaking areas as foam. Defaults to 0.
    // SC_DoubleLineEdit *T_star_coef; // Timescale factor until breaking fully develops. Defaults to 5.0.
    // SC_DoubleLineEdit *dzdt_I_coef; // Start-breaking threshold. Defaults to 0.50.
    // SC_DoubleLineEdit *dzdt_F_coef; // End-breaking threshold. Defaults to 0.15.
    // SC_IntLineEdit *useSedTransModel; // True if sediment transport is included.
    // SC_DoubleLineEdit *sedC1_d50;
    // SC_DoubleLineEdit *sedC1_n;
    // SC_DoubleLineEdit *sedC1_psi;
    // SC_DoubleLineEdit *sedC1_criticalshields;
    // SC_DoubleLineEdit *sedC1_denrat;
    // SC_DoubleLineEdit *infiltrationRate; // Dry-beach infiltration rate. Defaults to 0.001.
    // SC_IntLineEdit *clearCon; // Clears concentration channel if 1. Defaults to 1.

  // NLSW_or_Bous = new SC_IntLineEdit("NLSW_or_Bous", 1);
  NLSW_or_Bous = new SC_ComboBox("NLSW_or_Bous", QStringList() << "NLSW" << "Boussinesq");
  NLSW_or_Bous->setCurrentIndex(1);
  NLSW_or_Bous->setToolTip("Select the type of model to use: NLSW or Boussinesq");
  duration = new LineEditRV(randomVariables);
  duration->setText("30.0");
  duration->setToolTip("Duration of the simulation in seconds");
  Courant_num = new LineEditRV(randomVariables);
  Courant_num->setText("0.2");
  Courant_num->setToolTip("Courant number for the simulation. Affects the stability of the simulation. A value of 0.1 to 0.2 is recommended.");
  whiteWaterDecayRate = new LineEditRV(randomVariables);
  whiteWaterDecayRate->setText("0.01");
  whiteWaterDecayRate->setToolTip("Turbulence decay rate for foam (visualization).");
  whiteWaterDispersion = new LineEditRV(randomVariables);
  whiteWaterDispersion->setText("0.1");
  whiteWaterDispersion->setToolTip("Turbulence dispersion factor.");
  dissipation_threshold = new LineEditRV(randomVariables);
  dissipation_threshold->setText("0.3");
  dissipation_threshold->setToolTip("Used for visualization (mark cells above certain foam/dissipation).");
  delta_breaking = new LineEditRV(randomVariables);
  delta_breaking->setText("2.0");
  delta_breaking->setToolTip("Eddy viscosity coefficient in breaking zones.");
  Theta = new LineEditRV(randomVariables);
  Theta->setText("2.0");
  Theta->setToolTip("Midmod limiter parameter (1.0 more dissipative, 2.0 less dissipative). (1.0 upwind, 2.0 centered).");
  Bcoef = new LineEditRV(randomVariables);
  Bcoef->setText("0.06666666666666667");
  Bcoef->setToolTip("Dispersion parameter for Boussinesq model; default 1/15.");
  // timeScheme = new SC_IntLineEdit("timeScheme", 2); // 
  timeScheme = new SC_ComboBox("timeScheme", QStringList() << "Euler" << "3rd-order predictor" << "4th-order predictor/corrector");
  timeScheme->setCurrentIndex(2);
  timeScheme->setToolTip("Time integration scheme: 0 -> Euler, 1 -> 3rd-order predictor, 2 -> 4th-order predictor/corrector");
  // delta = new SC_DoubleLineEdit("delta", 0.005); // Maybe don't provide to user. ti.min(0.005, self.base_depth / 5000.0) 
  // epsilon = new SC_DoubleLineEdit("epsilon", 0.000025); // Maybe don't provide to user. ti.pow(self.delta, 2)
  // Px = new SC_IntLineEdit("Px", 100); // Maybe don't provide to user. Tridiag related to domain, int(ti.ceil(ti.log(self.nx) / ti.log(2)))
  // Py = new SC_IntLineEdit("Py", 100); // Maybe don't provide to user. Tridiag related to domain, int(ti.ceil(ti.log(self.ny) / ti.log(2)))
  // friction = new LineEditRV(randomVariables);
  // friction->setText("0.001");
  useBreakingModel = new SC_CheckBox("useBreakingModel", 0);
  useBreakingModel->setToolTip("True if wave-breaking model is included.");
  showBreaking = new SC_CheckBox("showBreaking", 0);
  showBreaking->setToolTip("True if show wave breaking areas as foam. Defaults to false.");
  T_star_coef = new LineEditRV(randomVariables);
  T_star_coef->setText("5.0");
  T_star_coef->setToolTip("Timescale factor until breaking fully develops. Defaults to 5.0.");
  dzdt_I_coef = new LineEditRV(randomVariables);
  dzdt_I_coef->setText("0.5");
  dzdt_I_coef->setToolTip("Start-breaking threshold. Defaults to 0.50.");
  dzdt_F_coef = new LineEditRV(randomVariables);
  dzdt_F_coef->setText("0.15");
  dzdt_F_coef->setToolTip("End-breaking threshold. Defaults to 0.15.");
  useSedTransModel = new SC_CheckBox("useSedTransModel", 0);
  sedC1_d50 = new LineEditRV(randomVariables);
  sedC1_d50->setText("0.2");
  sedC1_d50->setToolTip("Sediment D50 size in mm. Default is 0.2 mm.");
  sedC1_n = new LineEditRV(randomVariables);
  sedC1_n->setText("0.4");
  sedC1_psi = new LineEditRV(randomVariables);
  sedC1_psi->setText("0.00005");
  sedC1_criticalshields = new LineEditRV(randomVariables);
  sedC1_criticalshields->setText("0.045");
  sedC1_denrat = new LineEditRV(randomVariables);
  sedC1_denrat->setText("2.65");
  infiltrationRate = new LineEditRV(randomVariables);
  infiltrationRate->setText("0.001");
  infiltrationRate->setToolTip("Dry-beach infiltration rate. Defaults to 0.001.");
  // clearCon = new SC_CheckBox("clearCon", 1);
  // clearCon->setToolTip("Clears concentration channel if true. Defaults to true.");
  int numRow = 0;
  QGridLayout *theLayout = new QGridLayout();

  int numRowAlgorithm = 0;
  QGroupBox *theAlgorithmGroupBox = new QGroupBox("Algorithm");
  QGridLayout *theAlgorithmLayout = new QGridLayout();
  theAlgorithmGroupBox->setLayout(theAlgorithmLayout);
  theAlgorithmLayout->addWidget(new QLabel("NLSW_or_Bous"), numRowAlgorithm, 0, 1, 2);
  theAlgorithmLayout->addWidget(NLSW_or_Bous, numRowAlgorithm, 2, 1, 3);
  numRowAlgorithm++;
  theAlgorithmLayout->addWidget(new QLabel("timeScheme"), numRowAlgorithm, 0, 1, 2);
  theAlgorithmLayout->addWidget(timeScheme, numRowAlgorithm, 2, 1, 3);
  numRowAlgorithm++;
  theAlgorithmLayout->addWidget(new QLabel("Theta"), numRowAlgorithm, 0, 1, 2);
  theAlgorithmLayout->addWidget(Theta, numRowAlgorithm, 2, 1, 3);
  numRowAlgorithm++;
  theAlgorithmLayout->addWidget(new QLabel("Bcoef"), numRowAlgorithm, 0, 1, 2);
  theAlgorithmLayout->addWidget(Bcoef, numRowAlgorithm, 2, 1, 3);
  numRowAlgorithm++;
  theLayout->addWidget(theAlgorithmGroupBox, numRow, 0, 1, 5);
  numRow++;

  int numRowTime = 0;
  QGroupBox *theTimeGroupBox = new QGroupBox("Time");
  QGridLayout *theTimeLayout = new QGridLayout();
  theTimeGroupBox->setLayout(theTimeLayout);
  theTimeLayout->addWidget(new QLabel("duration"), numRowTime, 0, 1, 2);
  theTimeLayout->addWidget(duration, numRowTime, 2, 1, 3);
  numRowTime++;
  theTimeLayout->addWidget(new QLabel("Courant_num"), numRowTime, 0, 1, 2);
  theTimeLayout->addWidget(Courant_num, numRowTime, 2, 1, 3);
  numRowTime++;
  theLayout->addWidget(theTimeGroupBox, numRow, 0, 1, 5);
  numRow++;

  int numRowWhiteWater = 0;
  QGroupBox *theWhiteWaterGroupBox = new QGroupBox("White Water");
  QGridLayout *theWhiteWaterLayout = new QGridLayout();
  theWhiteWaterGroupBox->setLayout(theWhiteWaterLayout);
  theWhiteWaterLayout->addWidget(new QLabel("whiteWaterDispersion"), numRowWhiteWater, 0, 1, 2);
  theWhiteWaterLayout->addWidget(whiteWaterDispersion, numRowWhiteWater, 2, 1, 3);
  numRowWhiteWater++;
  theWhiteWaterLayout->addWidget(new QLabel("whiteWaterDecayRate"), numRowWhiteWater, 0, 1, 2);
  theWhiteWaterLayout->addWidget(whiteWaterDecayRate, numRowWhiteWater, 2, 1, 3);
  numRowWhiteWater++;
  theWhiteWaterLayout->addWidget(new QLabel("dissipation_threshold"), numRowWhiteWater, 0, 1, 2);
  theWhiteWaterLayout->addWidget(dissipation_threshold, numRowWhiteWater, 2, 1, 3);
  numRowWhiteWater++;
  theLayout->addWidget(theWhiteWaterGroupBox, numRow, 0, 1, 5);
  numRow++;

  int numRowBreaking = 0;
  QGroupBox *theBreakingGroupBox = new QGroupBox("Wave Breaking");
  QGridLayout *theBreakingLayout = new QGridLayout();
  theBreakingGroupBox->setLayout(theBreakingLayout);
  theBreakingLayout->addWidget(new QLabel("useBreakingModel"), numRowBreaking, 0, 1, 2);
  theBreakingLayout->addWidget(useBreakingModel, numRowBreaking, 2, 1, 3);
  numRowBreaking++;
  theBreakingLayout->addWidget(new QLabel("showBreaking"), numRowBreaking, 0, 1, 2);
  theBreakingLayout->addWidget(showBreaking, numRowBreaking, 2, 1, 3);
  numRowBreaking++;
  theBreakingLayout->addWidget(new QLabel("delta_breaking"), numRowBreaking, 0, 1, 2);
  theBreakingLayout->addWidget(delta_breaking, numRowBreaking, 2, 1, 3);
  numRowBreaking++;
  theBreakingLayout->addWidget(new QLabel("T_star_coef"), numRowBreaking, 0, 1, 2);
  theBreakingLayout->addWidget(T_star_coef, numRowBreaking, 2, 1, 3);
  numRowBreaking++;
  theBreakingLayout->addWidget(new QLabel("dzdt_I_coef"), numRowBreaking, 0, 1, 2);
  theBreakingLayout->addWidget(dzdt_I_coef, numRowBreaking, 2, 1, 3);
  numRowBreaking++;
  theBreakingLayout->addWidget(new QLabel("dzdt_F_coef"), numRowBreaking, 0, 1, 2);
  theBreakingLayout->addWidget(dzdt_F_coef, numRowBreaking, 2, 1, 3);
  numRowBreaking++;
  theLayout->addWidget(theBreakingGroupBox, numRow, 0, 1, 5);
  numRow++;


  // theLayout->addWidget(new QLabel("delta"), numRow, 0, 1, 2);
  // theLayout->addWidget(delta, numRow, 2, 1, 3);
  // numRow++;
  // theLayout->addWidget(new QLabel("epsilon"), numRow, 0, 1, 2);
  // theLayout->addWidget(epsilon, numRow, 2, 1, 3);
  // numRow++;
  // theLayout->addWidget(new QLabel("Px"), numRow, 0, 1, 2);
  // theLayout->addWidget(Px, numRow, 2, 1, 3);
  // numRow++;
  // theLayout->addWidget(new QLabel("Py"), numRow, 0, 1, 2);
  // theLayout->addWidget(Py, numRow, 2, 1, 3);
  // numRow++;
  // theLayout->addWidget(new QLabel("friction"), numRow, 0, 1, 2);
  // theLayout->addWidget(friction, numRow, 2, 1, 3);
  // numRow++;

  theLayout->addWidget(new QLabel("infiltrationRate"), numRow, 0, 1, 2);
  theLayout->addWidget(infiltrationRate, numRow, 2, 1, 3);
  numRow++;

  int numRowSediment = 0;
  QGroupBox *theSedimentGroupBox = new QGroupBox("Sediment Transport");
  QGridLayout *theSedimentLayout = new QGridLayout();
  theSedimentGroupBox->setLayout(theSedimentLayout);
  theSedimentLayout->addWidget(new QLabel("useSedTransModel"), numRowSediment, 0, 1, 2);
  theSedimentLayout->addWidget(useSedTransModel, numRowSediment, 2, 1, 3);
  numRowSediment++;
  theSedimentLayout->addWidget(new QLabel("sedC1_d50"), numRowSediment, 0, 1, 2);
  theSedimentLayout->addWidget(sedC1_d50, numRowSediment, 2, 1, 3);
  numRowSediment++;
  theSedimentLayout->addWidget(new QLabel("sedC1_n"), numRowSediment, 0, 1, 2); 
  theSedimentLayout->addWidget(sedC1_n, numRowSediment, 2, 1, 3);
  numRowSediment++;
  theSedimentLayout->addWidget(new QLabel("sedC1_psi"), numRowSediment, 0, 1, 2);
  theSedimentLayout->addWidget(sedC1_psi, numRowSediment, 2, 1, 3);
  numRowSediment++;
  theSedimentLayout->addWidget(new QLabel("sedC1_criticalshields"), numRowSediment, 0, 1, 2);
  theSedimentLayout->addWidget(sedC1_criticalshields, numRowSediment, 2, 1, 3);
  numRowSediment++;
  theSedimentLayout->addWidget(new QLabel("sedC1_denrat"), numRowSediment, 0, 1, 2);
  theSedimentLayout->addWidget(sedC1_denrat, numRowSediment, 2, 1, 3);
  numRowSediment++;
  theLayout->addWidget(theSedimentGroupBox, numRow, 0, 1, 5);
  numRow++;

  // theLayout->addWidget(new QLabel("clearCon"), numRow, 0, 1, 2);
  // theLayout->addWidget(clearCon, numRow, 2, 1, 3);
  // numRow++;

  theLayout->setRowStretch(numRow, 1);

  this->setLayout(theLayout);
}

CelerisSolver::~CelerisSolver()
{

}

bool
CelerisSolver::outputToJSON(QJsonObject &jsonObject)
{

  QJsonObject configObj;
  configObj = jsonObject["config"].toObject();
  // NLSW_or_Bous->outputToJSON(configObj);
  configObj["NLSW_or_Bous"] = int(NLSW_or_Bous->currentIndex());
  duration->outputToJSON(configObj, QString("duration"));
  Courant_num->outputToJSON(configObj, QString("Courant_num"));
  whiteWaterDecayRate->outputToJSON(configObj, QString("whiteWaterDecayRate"));
  whiteWaterDispersion->outputToJSON(configObj, QString("whiteWaterDispersion"));
  dissipation_threshold->outputToJSON(configObj, QString("dissipation_threshold"));
  delta_breaking->outputToJSON(configObj, QString("delta_breaking"));
  Theta->outputToJSON(configObj, QString("Theta"));
  Bcoef->outputToJSON(configObj, QString("Bcoef"));
  // timeScheme->outputToJSON(configObj);
  configObj["timeScheme"] = int(timeScheme->currentIndex());
  // delta->outputToJSON(configObj);
  // epsilon->outputToJSON(configObj);
  // Px->outputToJSON(configObj);
  // Py->outputToJSON(configObj);
  // friction->outputToJSON(configObj, QString("friction"));
  // useBreakingModel->outputToJSON(configObj);
  configObj["useBreakingModel"] = useBreakingModel->isChecked() ? int(1) : int(0);
  // showBreaking->outputToJSON(configObj);
  configObj["showBreaking"] = showBreaking->isChecked() ? int(1) : int(0);
  T_star_coef->outputToJSON(configObj, QString("T_star_coef"));
  dzdt_I_coef->outputToJSON(configObj, QString("dzdt_I_coef"));
  dzdt_F_coef->outputToJSON(configObj, QString("dzdt_F_coef"));
  // useSedTransModel->outputToJSON(configObj);
  configObj["useSedTransModel"] = useSedTransModel->isChecked() ? int(1) : int(0);
  sedC1_d50->outputToJSON(configObj, QString("sedC1_d50"));
  sedC1_n->outputToJSON(configObj, QString("sedC1_n"));
  sedC1_psi->outputToJSON(configObj, QString("sedC1_psi"));
  sedC1_criticalshields->outputToJSON(configObj, QString("sedC1_criticalshields"));
  sedC1_denrat->outputToJSON(configObj, QString("sedC1_denrat"));
  infiltrationRate->outputToJSON(configObj, QString("infiltrationRate"));
  // clearCon->outputToJSON(configObj);
  // configObj["clearCon"] = clearCon->isChecked() ? int(1) : int(0);
  jsonObject["config"] = configObj;
  return true;
}

bool
CelerisSolver::inputFromJSON(QJsonObject &jsonObject)
{
  
  QJsonObject configObj;
  configObj = jsonObject["config"].toObject();
  // NLSW_or_Bous->inputFromJSON(configObj);
  NLSW_or_Bous->setCurrentIndex(configObj["NLSW_or_Bous"].toInt());
  duration->inputFromJSON(configObj, QString("duration"));
  Courant_num->inputFromJSON(configObj, QString("Courant_num"));
  whiteWaterDecayRate->inputFromJSON(configObj, QString("whiteWaterDecayRate"));
  whiteWaterDispersion->inputFromJSON(configObj, QString("whiteWaterDispersion"));
  dissipation_threshold->inputFromJSON(configObj, QString("dissipation_threshold"));
  delta_breaking->inputFromJSON(configObj, QString("delta_breaking"));
  Theta->inputFromJSON(configObj, QString("Theta"));
  Bcoef->inputFromJSON(configObj, QString("Bcoef"));
  // timeScheme->inputFromJSON(configObj);
  timeScheme->setCurrentIndex(configObj["timeScheme"].toInt());
  // delta->inputFromJSON(configObj);
  // epsilon->inputFromJSON(configObj);
  // Px->inputFromJSON(configObj);
  // Py->inputFromJSON(configObj);
  // friction->inputFromJSON(configObj, QString("friction"));
  // useBreakingModel->inputFromJSON(configObj);
  useBreakingModel->setChecked(configObj["useBreakingModel"].toInt() > 0);
  // showBreaking->inputFromJSON(configObj);
  showBreaking->setChecked(configObj["showBreaking"].toInt() > 0);
  T_star_coef->inputFromJSON(configObj, QString("T_star_coef"));
  dzdt_I_coef->inputFromJSON(configObj, QString("dzdt_I_coef"));
  dzdt_F_coef->inputFromJSON(configObj, QString("dzdt_F_coef"));
  // useSedTransModel->inputFromJSON(configObj);
  useSedTransModel->setChecked(configObj["useSedTransModel"].toInt() > 0);
  sedC1_d50->inputFromJSON(configObj, QString("sedC1_d50"));
  sedC1_n->inputFromJSON(configObj, QString("sedC1_n"));
  sedC1_psi->inputFromJSON(configObj, QString("sedC1_psi"));
  sedC1_criticalshields->inputFromJSON(configObj, QString("sedC1_criticalshields"));
  sedC1_denrat->inputFromJSON(configObj, QString("sedC1_denrat"));
  infiltrationRate->inputFromJSON(configObj, QString("infiltrationRate"));
  // clearCon->inputFromJSON(configObj);
  // clearCon->setChecked(configObj["clearCon"].toInt() > 0);
  jsonObject["config"] = configObj;
  return true;
}

bool
CelerisSolver::copyFiles(QString &destDir)
{
  return true;
}


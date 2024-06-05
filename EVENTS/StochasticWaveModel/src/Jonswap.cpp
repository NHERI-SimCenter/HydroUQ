/* *****************************************************************************
Copyright (c) 2016-2017, The Regents of the University of California (Regents).
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

// Written: JustinBonus
// Adapted from work of: mhgardner
#include <QComboBox>
#include <QDebug>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QLabel>
#include <QSpinBox>
#include <QString>
#include <QVBoxLayout>


#include <RandomVariablesContainer.h>
#include <SimCenterWidget.h>

#include <SC_IntLineEdit.h>

#include <StochasticWaveModel/include/Jonswap.h>

Jonswap::Jonswap(RandomVariablesContainer* randomVariables,
                                   QWidget* parent)
: SimCenterAppWidget(parent)
{


//     // Initialize member variables
  dragCoefficient = new LineEditRV(randomVariables);
  dragCoefficient->setText("2.1");

  dragArea = new LineEditRV(randomVariables);
  dragArea->setText("15.0");

  peakPeriod = new LineEditRV(randomVariables);
  peakPeriod->setText("12.0");

  significantWaveHeight = new LineEditRV(randomVariables);
  significantWaveHeight->setText("8.1");

  waterDepth = new LineEditRV(randomVariables);
  waterDepth->setText("30.0");

  recorderOriginX = new LineEditRV(randomVariables);
  recorderOriginX->setText("0.0");

  recorderCountZ = new SC_IntLineEdit("recorderCountZ", 2);

  timeStep = new LineEditRV(randomVariables);
  timeStep->setText("0.1");

  timeDuration = new LineEditRV(randomVariables);
  timeDuration->setText("3600.0");

//   exposureCategory = new QComboBox();
//   exposureCategory->addItem("JONSWAP");

//   seed = new QSpinBox();
//   seed->setMinimum(1);
//   seed->setMaximum(2147483647);
//   seed->setValue(500);  
//   seed->setEnabled(false);
//   useSeed = new QRadioButton("Provide seed value");
//   useSeed->setChecked(false);


//   exposureCategory = new QComboBox();
//   exposureCategory->addItem("JONSWAP");
// //   exposureCategory->addItem("Pierson-Moskowitz");
  QFormLayout *parameters = new QFormLayout();

  parameters->addRow(new QLabel(tr("Water Depth [ft]")), waterDepth);
  parameters->addRow(new QLabel(tr("Significant Wave Height [ft]")), significantWaveHeight);
  parameters->addRow(new QLabel(tr("Peak Wave Period [s]")), peakPeriod);
  parameters->addRow(new QLabel(tr("Time Step [s]")), timeStep);
  parameters->addRow(new QLabel(tr("Time Duration [s]")), timeDuration);
  parameters->addRow(new QLabel(tr("Load Recorder Origin [ft]")), recorderOriginX);
  parameters->addRow(new QLabel(tr("Load Recorder Count")), recorderCountZ);
  // parameters->addRow(new QLabel(tr("Wave Spectrum")), exposureCategory);
  parameters->addRow(new QLabel(tr("Drag Coefficient")), dragCoefficient);
  parameters->addRow(new QLabel(tr("Drag Area [ft^2]")), dragArea);




  // Initialize member variables
  // dragCoefficient = new LineEditRV(randomVariables);
  // dragCoefficient->setText("1.5");

  // gustWindSpeed = new LineEditRV(randomVariables);
  // gustWindSpeed->setText("50.0");

  // exposureCategory = new QComboBox();
  // exposureCategory->addItem("B");
  // exposureCategory->addItem("C");
  // exposureCategory->addItem("D");

  seed = new QSpinBox();
  seed->setMinimum(1);
  seed->setMaximum(2147483647);
  seed->setValue(500);  
  seed->setEnabled(false);
  useSeed = new QRadioButton("Set Random Seed");
  useSeed->setChecked(false);



  exposureCategory = new QComboBox();
  exposureCategory->addItem("NATO 5");
  exposureCategory->addItem("NATO 4");
  exposureCategory->addItem("NATO 3");
  exposureCategory->addItem("NATO 2");
  exposureCategory->addItem("NATO 1");

  // parameters->addRow(new QLabel(tr("Drag Coefficient")), dragCoefficient);
  parameters->addRow(new QLabel(tr("Sea State Category")), exposureCategory);

  // Align the labels to the right
  for (int i = 0; i < parameters->rowCount(); i++) {
    QLabel* label = qobject_cast<QLabel*>(parameters->itemAt(i, QFormLayout::LabelRole)->widget());
    label->setAlignment(Qt::AlignRight);
  }
  // parameters->addRow(new QLabel(tr("Gust Wind Speed (mph)")), gustWindSpeed);
  // gustWindSpeed->setToolTip("3 sec gust speed at height of 10m (33ft)");
  // Add description label
  modelDescription =
      new QLabel(tr("This model provides wave spectra using a "
                    "JONSWAP empirical distribution."));

  modelDescription =
      new QLabel(tr("The open-source welib library computes the JONSWAP"
                    "Morrison loads on the structure."));
  //model_description_->setStyleSheet("QLabel { color : gray; }");

  // Construct required layouts
  QVBoxLayout* layout = new QVBoxLayout();
  QHBoxLayout* seedLayout = new QHBoxLayout();
  QHBoxLayout* parametersLayout = new QHBoxLayout();

  // Add widgets to layouts and layouts to this
  seedLayout->addWidget(useSeed);
  seedLayout->addWidget(seed);
  seedLayout->addStretch();
  parametersLayout->addLayout(parameters);
  parametersLayout->addStretch();
  layout->addWidget(modelDescription);
  layout->addLayout(parametersLayout);
  layout->addLayout(seedLayout);
  layout->addStretch();
  this->setLayout(layout);

  // Connect slots
  connect(useSeed, &QRadioButton::toggled, this,
          &Jonswap::provideSeed);
}


bool Jonswap::outputAppDataToJSON(QJsonObject& jsonObject) {
  bool result = true;

  jsonObject["Application"] = "StochasticWave";
  jsonObject["EventClassification"] = "Hydro";

  // jsonObject["Application"] = "StochasticWindWittigSinha";
  // jsonObject["EventClassification"] = "Wind";

  // squirel in the application data selection text
  QJsonObject appData;
  jsonObject["ApplicationData"] = appData;

  return result;
}

bool Jonswap::inputAppDataFromJSON(QJsonObject& jsonObject) {
  Q_UNUSED(jsonObject);
  return true;
}

bool Jonswap::outputToJSON(QJsonObject& jsonObject) {
  bool result = true;

  jsonObject["type"] = "StochasticWave";
  jsonObject["EventClassification"] = "Hydro";

  // jsonObject["type"] = "StochasticWindWittigSinha";
  // jsonObject["EventClassification"] = "Wind";

  waterDepth->outputToJSON(jsonObject, QString("waterDepth"));
  significantWaveHeight->outputToJSON(jsonObject, QString("significantWaveHeight"));
  peakPeriod->outputToJSON(jsonObject, QString("peakPeriod"));
  recorderOriginX->outputToJSON(jsonObject, QString("recorderOriginX"));
  recorderCountZ->outputToJSON(jsonObject);
  timeStep->outputToJSON(jsonObject, QString("timeStep"));
  timeDuration->outputToJSON(jsonObject, QString("timeDuration"));
  dragCoefficient->outputToJSON(jsonObject, QString("dragCoefficient"));
  dragArea->outputToJSON(jsonObject, QString("dragArea"));


  // gustWindSpeed->outputToJSON(jsonObject, QString("gustSpeed"));
  jsonObject.insert("exposureCategory",exposureCategory->currentText());

  if (useSeed->isChecked()) {
    jsonObject.insert("seed", seed->value());
  } else {
    jsonObject.insert("seed", "None");
  }
  
  return result;
}

bool Jonswap::inputFromJSON(QJsonObject& jsonObject) {
  bool result = true;

  waterDepth->inputFromJSON(jsonObject, QString("waterDepth"));
  significantWaveHeight->inputFromJSON(jsonObject, QString("significantWaveHeight"));
  peakPeriod->inputFromJSON(jsonObject, QString("peakPeriod"));
  recorderOriginX->inputFromJSON(jsonObject, QString("recorderOriginX"));
  recorderCountZ->inputFromJSON(jsonObject);
  timeStep->inputFromJSON(jsonObject, QString("timeStep"));
  timeDuration->inputFromJSON(jsonObject, QString("timeDuration"));
  dragCoefficient->inputFromJSON(jsonObject, QString("dragCoefficient"));
  dragArea->inputFromJSON(jsonObject, QString("dragArea"));


  // gustWindSpeed->inputFromJSON(jsonObject, QString("gustSpeed"));

  if (jsonObject.contains("exposureCategory")) {

      QJsonValue theValue = jsonObject["exposureCategory"];
      if (theValue.isString()) {
        QString exposure  = theValue.toString();
        exposureCategory->setCurrentText(exposure);
      }
  }

  if (jsonObject.value("seed").isString()) {
    useSeed->setChecked(false);    
  } else {
    useSeed->setChecked(true);
    seed->setValue(jsonObject.value("seed").toInt());    
  }

  return result;
  }

  void Jonswap::provideSeed(const bool& checked) {
  if (checked) {
    seed->setEnabled(true);
  } else {
    seed->setEnabled(false);
    seed->setValue(500);
  }
  }
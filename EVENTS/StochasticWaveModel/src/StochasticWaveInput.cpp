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

// Written for similar event type: mhgardner
// Modified: JustinBonus (05/2024)
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
#include <StochasticWaveModel/include/StochasticWaveInput.h>
#include <StochasticWaveModel/include/Jonswap.h>


StochasticWaveInput::StochasticWaveInput(
    RandomVariablesContainer* random_variables, QWidget* parent)
    : SimCenterAppWidget(parent),
      rvInputWidget(random_variables) {
  // Construct required layouts
  QVBoxLayout* layout = new QVBoxLayout();
  QHBoxLayout* model_layout = new QHBoxLayout();
  parametersLayout = new QHBoxLayout();
  
  // Create label and add items to combo box for model selection 
  QLabel* selection_label = new QLabel(tr("Stochastic Loading Model"));
  //selection_label->setStyleSheet("font-weight: bold");
  modelSelection = new QComboBox();
  modelSelection->setObjectName("StochasticLoadingModel");
  modelSelection->addItem(tr("JONSWAP"));
  // Jonswap* theJonswap = new Jonswap(rvInputWidget, this); //, this);
  stochasticModel = new Jonswap(rvInputWidget); //, this);
  
  // Add widgets to layouts and layouts to this

  model_layout->addWidget(modelSelection);
  model_layout->addStretch();
  parametersLayout->addWidget(stochasticModel);
  parametersLayout->addStretch();
  layout->addWidget(selection_label);
  layout->addLayout(model_layout);
  layout->addLayout(parametersLayout);
  layout->addStretch();
  this->setLayout(layout);

  // Connect model selection slot
  connect(modelSelection, SIGNAL(currentTextChanged()), this, SLOT(modelSelectionChanged));
}


StochasticWaveInput::~StochasticWaveInput() {
  // if (stochasticModel != NULL) {
  //   delete stochasticModel;
  // }

  // if (parametersLayout != NULL) {
  //   delete parametersLayout;
  // }

  // if (modelSelection != NULL) {
  //   delete modelSelection;
  // }

  

}

// void StochasticWaveInput::clear(void)
// {
//   // if (stochasticModel != NULL) {
//   //   stochasticModel->clear();
//   // }

//   // if (parametersLayout != NULL) {  
//   //   delete parametersLayout;
//   // }

//   // if (modelSelection != NULL) {
//   //   delete modelSelection;
//   // }

//   // if (rvInputWidget != NULL) {
//   //   delete rvInputWidget;
//   // }

//   // if (stochasticModel != NULL) {

//   //   delete stochasticModel;
//   // }

//   // if (theJonswap != NULL) {

//   //   delete theJonswap;
//   // }


// }

bool StochasticWaveInput::outputToJSON(QJsonObject& jsonObject) {
  bool result = false;
  if (stochasticModel != NULL) 
    return stochasticModel->outputToJSON(jsonObject);
  else {
    qDebug() << "StocashicWaveInput::outputToJSON - NULL model";
  }

  return result;
}

bool StochasticWaveInput::inputFromJSON(QJsonObject& jsonObject) {

  bool result = false;

  if (stochasticModel != NULL) {
    stochasticModel->clear();

    SimCenterAppWidget *nextModel = NULL;
    QString model;
    if (!jsonObject.contains("StochasticLoadingModel")) {
      qDebug() << "ERROR: StochasticWaveInput::inputFromJSON: Missing selection\n";
      qDebug() << "Setting to default: StochasticWaveJonswap\n";
      model = "StochasticWaveJonswap";
      // return false;
    }
    else {
      model = jsonObject["StochasticLoadingModel"].toString();
    }
    if (model == "JONSWAP" || model == "StochasticWaveJonswap" || model == "StochasticWave") {
      nextModel = new Jonswap(rvInputWidget); //, this);
    } 
    // add more models here
    else {
      qDebug() << "ERROR: StochasticWaveInput::inputFromJSON: Unknown selection: " << model << "\n";
    }

    if (nextModel != NULL) {
      if (stochasticModel != NULL) {
        parametersLayout->replaceWidget(stochasticModel, nextModel);
        delete stochasticModel;
      }
      stochasticModel = nextModel;
    }

    return stochasticModel->inputFromJSON(jsonObject);
  }
  else {
    qDebug() << "StocashicWaveInput::inputToJSON - NULL model";
  }

  return result;
}

bool StochasticWaveInput::outputAppDataToJSON(QJsonObject& jsonObject) {

  bool result = false;
  if (stochasticModel != NULL) 
    return stochasticModel->outputAppDataToJSON(jsonObject);
  else {
    qDebug() << "StocashicWaveInput::outputAppDataToJSON - NULL model";
  }
  return result;
}


bool StochasticWaveInput::inputAppDataFromJSON(QJsonObject& jsonObject) {

  QString appName;
  appName = jsonObject.value("Application").toString();
  if (appName == "StochasticWaveJonswap" || appName == "JONSWAP" || appName == "StochasticWave") {  

    this->modelSelectionChanged(QString("JONSWAP"));
    stochasticModel->inputAppDataFromJSON(jsonObject); // no check for NULL as cannot be if i can write code!
  } 
  
  else {
    QString message = QString("StocashicWaveInput::inputAppDataFromJSON - unknown application string: ") + appName;
    //    qDebug() << message;
    emit errorMessage(message);
  }

  return true;
}

bool StochasticWaveInput::supportsLocalRun() {
  // TODO: Check if the selected model supports local run
  return true;
}

void StochasticWaveInput::modelSelectionChanged(const QString& model) {

  // Switch the model description and form layout based on model selection
  SimCenterAppWidget *nextModel = NULL;
  if (model == "JONSWAP" || model == "StochasticWaveJonswap" || model == "StochasticWave") {
    nextModel = new Jonswap(rvInputWidget); //, this);
    // if (stochasticModel == NULL) {
    //   if (nextModel != NULL) {
    //     delete nextModel;
    //   }
    //   if (theJonswap) {
    //     nextModel = theJonswap;
    //   } else {
    //     nextModel = new Jonswap(rvInputWidget); //, this);
    //   }
    // } else {
    //   if (theJonswap) {
    //     nextModel = theJonswap;
    //   } else {
    //     nextModel = new Jonswap(rvInputWidget); //, this);
    //   }
    //   parametersLayout->replaceWidget(stochasticModel, nextModel);
    //   delete stochasticModel;
    // }
    // nextModel = theJonswap;
  } else {
    qDebug() << "ERROR: StochasticWaveInput::modelSelectionChanged: Unknown selection: " << model << "\n";
  }
  
  if (nextModel != NULL) {
    if (stochasticModel != NULL) {
      parametersLayout->replaceWidget(stochasticModel, nextModel);
      delete stochasticModel;
      stochasticModel = nextModel;
    }
  }
}

void StochasticWaveInput::errorMessage(QString message) {
  emit sendErrorMessage(message);
}
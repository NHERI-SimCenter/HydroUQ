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
 OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
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

#include "TaichiEvent.h"
#include <QScrollArea>
#include <QLineEdit>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QJsonObject>
#include <QDebug>
#include <QString>
#include <BasicTaichiEvent.h>
// #include <CelerisTaichiEvent.h>

TaichiEvent::TaichiEvent(QWidget *parent)
    : SimCenterAppWidget(parent)
{
    int windowWidth = 800;

    QWidget     *mainGroup = new QWidget();
    QGridLayout *mainLayout = new QGridLayout();

    QLabel *generalDescriptionLabel = new QLabel("General Event - Taichi Lang High-Performance Numerical Simulations: "
                                                 "\n 1. Specify Settings for simulation. "						 
                                                 "\n 2. Define Bodies that are to be simulated. "
                                                 "\n 3. Specify Boundaries for simulation. "
                                                 "\n 4. Specify Sensors for recording. "
                                                 "\n 5. Visualize scene.");



    mainLayout->addWidget(generalDescriptionLabel, 0, 0);

    QTabWidget *theTabWidget = new QTabWidget();
    inputBasic = new BasicTaichiEvent();
    theTabWidget->addTab(inputBasic, "Basic");
    mainLayout->addWidget(theTabWidget, 1, 0);
    
    
    mainGroup->setLayout(mainLayout);
    mainGroup->setMaximumWidth(windowWidth);
    
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setLineWidth(1);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setWidget(mainGroup);
    scrollArea->setMaximumWidth(windowWidth + 25);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(scrollArea);
    this->setLayout(layout);
}


TaichiEvent::~TaichiEvent()
{

}


void TaichiEvent::clear(void)
{

}


bool TaichiEvent::inputFromJSON(QJsonObject &jsonObject)
{
  this->clear();
  
  inputBasic->inputFromJSON(jsonObject);

  return true;
}

bool TaichiEvent::outputToJSON(QJsonObject &jsonObject)
{
  jsonObject["EventClassification"] = "Hydro";
  jsonObject["Application"] = "TaichiEvent";

  inputBasic->outputToJSON(jsonObject); 
  
  return true;
}

bool TaichiEvent::outputAppDataToJSON(QJsonObject &jsonObject) {

    //
    // per API, need to add name of application to be called in Application
    // and all data to be used in ApplicationData
    //

    jsonObject["EventClassification"] = "Hydro";
    jsonObject["Application"] = "TaichiEvent";
    QJsonObject dataObj;
    jsonObject["ApplicationData"] = dataObj;

    return true;
}
bool TaichiEvent::inputAppDataFromJSON(QJsonObject &jsonObject) {

    Q_UNUSED(jsonObject);
    return true;
}


bool TaichiEvent::copyFiles(QString &destDir) {
  if (inputBasic->copyFiles(destDir) == false) {
    qDebug() << "TaichiEvent::copyFiles: failed to copy basic files";
    return false;
  }
  return true;
}

bool TaichiEvent::supportsLocalRun() {

  //
  // Allows use on local machines with Taichi Lang installed (python -m pip install taichi)
  //

  return true;
}

bool TaichiEvent::outputCitation(QJsonObject &jsonObject) {
  QJsonObject citeTaichi;

  citeTaichi["citation"] = "Yuanming Hu (2019). Taichi Lang.";
  citeTaichi["description"] = "HydroUQ applied Taichi for two-way coupled CFD-FEA, developed in this thesis as the Taichi software. It couples Boundaries and Bodies for the simulation of civil engineering structures subject to multi-hazards via the PreCICE coupling library.";

  jsonObject["Taichi"] = citeTaichi;
  return true;
}
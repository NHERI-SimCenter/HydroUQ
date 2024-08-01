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

// Written: fmk

#include "TaichiEvent.h"
#include <QScrollArea>
#include <QLineEdit>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QJsonObject>

#include <BasicTaichiEvent.h>
// #include <SettingsTaichiEvent.h>
// #include <VisualizeTaichiEvent.h>
// #include <BodiesTaichiEvent.h>
// #include <BoundariesTaichiEvent.h>
// #include <OutputsTaichiEvent.h>

TaichiEvent::TaichiEvent(QWidget *parent)
    : SimCenterAppWidget(parent)
{
    int windowWidth = 800;

    QWidget     *mainGroup = new QWidget();
    QGridLayout *mainLayout = new QGridLayout();

    QLabel *generalDescriptionLabel = new QLabel("General Event - Taichi High-Performance Numerical Simulation: "
                                                 "\n --> Specify Settings for simulation. "						 
                                                 "\n --> Define Bodies that are to be simulated. "
                                                 "\n --> Specify Boundaries for simulation. "
                                                 "\n --> Specify Sensors for recording. "
                                                 "\n --> Visualize scene.");



    mainLayout->addWidget(generalDescriptionLabel, 0, 0);

    QTabWidget *theTabWidget = new QTabWidget();
    inputBasic = new BasicTaichiEvent();
    theTabWidget->addTab(inputBasic, "Basic");
    // inputSettings = new SettingsTaichiEvent();
    // theTabWidget->addTab(inputSettings, "Settings");
    // inputBodies = new BodiesTaichiEvent();
    // theTabWidget->addTab(inputBodies, "Bodies");
    // inputBoundaries = new BoundariesTaichiEvent();
    // theTabWidget->addTab(inputBoundaries, "Boundaries");
    // inputOutputs = new OutputsTaichiEvent();
    // theTabWidget->addTab(inputOutputs, "Outputs");
    // inputVisualize = new VisualizeTaichiEvent();
    // theTabWidget->addTab(inputVisualize, "Visualization");    
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
  
  /*
    if (jsonObject.contains("buildingWidth")) {
    QJsonValue theValue = jsonObject["buildingWidth"];
    QString selection = theValue.toString();
    buildingWidthWidget->setText(selection);
    } else
    return false;
  */
  
  inputBasic->inputFromJSON(jsonObject);
  // inputSettings->inputFromJSON(jsonObject);
  // inputBodies->inputFromJSON(jsonObject);
  // inputBoundaries->inputFromJSON(jsonObject);
  // inputSensors->inputFromJSON(jsonObject);
  // inputOutputs->inputFromJSON(jsonObject);
  // inputVisualize->inputFromJSON(jsonObject);
  
  return true;
}

bool TaichiEvent::outputToJSON(QJsonObject &jsonObject)
{
  jsonObject["EventClassification"]="Hydro";
  jsonObject["Application"] = "TaichiEvent";

  inputBasic->outputToJSON(jsonObject); 
  // inputSettings->outputToJSON(jsonObject);
  // inputBodies->outputToJSON(jsonObject);
  // inputBoundaries->outputToJSON(jsonObject);
  // inputSensors->outputToJSON(jsonObject);
  // inputOutputs->outputToJSON(jsonObject);
  // inputVisualize->outputToJSON(jsonObject);
  
  /*
    if (jsonObject.contains("buildingWidth")) {
    QJsonValue theValue = jsonObject["buildingWidth"];
    QString selection = theValue.toString();
    buildingWidthWidget->setText(selection);
    } else
    return false;
  */
  
  return true;
}

bool TaichiEvent::outputAppDataToJSON(QJsonObject &jsonObject) {

    //
    // per API, need to add name of application to be called in Application
    // and all data to be used in ApplicationData
    //

    jsonObject["EventClassification"]="Hydro";
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
  return inputBasic->copyFiles(destDir);

  // Careful with combining these two functions, as the second one will not be called due to return above
  // if (inputBoundaries->copyFiles(destDir) == false)
  //   return false;
  // return inputBodies->copyFiles(destDir);
 }

bool TaichiEvent::supportsLocalRun() {
  // TODO: Check if the selected model supports local run
  return true;
}

bool TaichiEvent::outputCitation(QJsonObject &jsonObject) {
  QJsonObject citeTaichi;
  // QJsonObject citeBodies;
  // QJsonObject citeBoundaries;
  citeTaichi["citation"] = "Yuanming Hu (2019). Taichi Lang.";
  citeTaichi["description"] = "HydroUQ applied Taichi for two-way coupled CFD-FEA, developed in this thesis as the Taichi software. It couples Boundaries and Bodies for the simulation of civil engineering structures subject to multi-hazards via the PreCICE coupling library.";
  // citeBoundaries["citation"] = "Greenshields, Christopher. (2023). Boundaries v11 User Guide. Boundaries Foundation.";
  // citeBoundaries["description"] = "HydroUQ uses Boundaries for high-quality 3D Navier-Stokes solutions. Boundaries is a free, open-source software package for computational fluid dynamics (CFD) that is widely used in academia and industry. It is developed by the Boundaries Foundation, which is a non-profit organization that promotes the use of open-source software in engineering and science.";
  // citeBodies["citation"] = "McKenna, F., Scott, M. H., and Fenves, G. L. (2010) “Nonlinear finite-element analysis software architecture using object composition.” Journal of Computing in Civil Engineering, 24(1):95-107.";
  // citeBodies["description"] = "HydroUQ incorporates Bodies for defining structural models in the SimCenter workflow. Bodies is a software framework for developing applications to simulate the performance of structural and geotechnical systems subjected to earthquakes. It is developed by the Pacific Earthquake Engineering Research Center (PEER) at the University of California, Berkeley.";
  jsonObject["Taichi"] = citeTaichi;
  // jsonObject["MLS-MPM"] =  citeBoundaries;
  // jsonObject["Bodies"] =  citeBodies;
  return true;
}
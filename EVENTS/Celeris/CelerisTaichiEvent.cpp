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
#include <CelerisTaichiEvent.h>
#include <CelerisTaichi.h>

CelerisTaichiEvent::CelerisTaichiEvent(QWidget *parent)
    : SimCenterAppWidget(parent)
{
    int windowWidth = 800;

    QWidget     *mainGroup = new QWidget();
    QGridLayout *mainLayout = new QGridLayout();

    QLabel *generalDescriptionLabel = new QLabel("General Event - Celeris Wave-Solver: "
                                                 "\n 1. Select a SimCenter compatible backend application. (Flags: --filenameAIM --filenameEVENT --getRV)"						 
                                                 "\n 2. Choose the Celeris wave-solver's main script."
                                                 "\n 3. Specify the Celeris configuration file."
                                                 "\n 4. Define a bathymetry input file."
                                                 "\n 5. Set a sea-state input file.");



    mainLayout->addWidget(generalDescriptionLabel, 0, 0);

    QTabWidget *theTabWidget = new QTabWidget();
    inputCeleris = new CelerisTaichi();
    theTabWidget->addTab(inputCeleris, "Celeris");
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


CelerisTaichiEvent::~CelerisTaichiEvent()
{

}


void CelerisTaichiEvent::clear(void)
{

}


bool CelerisTaichiEvent::inputFromJSON(QJsonObject &jsonObject)
{
  this->clear();
  
  inputCeleris->inputFromJSON(jsonObject);

  return true;
}

bool CelerisTaichiEvent::outputToJSON(QJsonObject &jsonObject)
{
  jsonObject["EventClassification"] = "Hydro";
  jsonObject["Application"] = "Celeris";

  inputCeleris->outputToJSON(jsonObject);
  
  return true;
}

bool CelerisTaichiEvent::outputAppDataToJSON(QJsonObject &jsonObject) {

    //
    // per API, need to add name of application to be called in Application
    // and all data to be used in ApplicationData
    //

    jsonObject["EventClassification"] = "Hydro";
    jsonObject["Application"] = "Celeris";
    QJsonObject dataObj;
    jsonObject["ApplicationData"] = dataObj;

    return true;
}
bool CelerisTaichiEvent::inputAppDataFromJSON(QJsonObject &jsonObject) {

    Q_UNUSED(jsonObject);
    return true;
}


bool CelerisTaichiEvent::copyFiles(QString &destDir) {
  if (inputCeleris->copyFiles(destDir) == false) {
    qDebug() << "Celeris::copyFiles(): Failed to copy Celeris files";
    // return false;
  }
  return true;
}

bool CelerisTaichiEvent::supportsLocalRun() {

  //
  // Allows use on local machines with Taichi Lang installed (python -m pip install taichi)
  //

  return true;
}

bool CelerisTaichiEvent::outputCitation(QJsonObject &jsonObject) {
  QJsonObject citeTaichi;
  QJsonObject citeCeleris;

  citeTaichi["citation"] = "Yuanming Hu (2019). Taichi Lang.";
  citeTaichi["description"] = "HydroUQ applied Taichi for two-way coupled CFD-FEA, developed in this thesis as the Taichi software. It couples Boundaries and Bodies for the simulation of civil engineering structures subject to multi-hazards via the PreCICE coupling library.";
  
  citeCeleris["title"] = "Celeris Base: An interactive and immersive Boussinesq-type nearshore wave simulation software";
  citeCeleris["citation"] = "Sasan Tavakkol and Patrick Lynett (2020). Celeris Base: An interactive and immersive Boussinesq-type nearshore wave simulation software.";
  citeCeleris["description"] = "Celeris Advent enabled researchers and engineers for the first time to simulate nearshore waves with a Boussinesq-type model, faster than real-time and in an interactive environment. However, its development platform and implementation complexity hindered researchers from developing it further and made adding new features to the software a daunting task. The software used graphics shaders to solve scientific equations which could be confusing for many. The visualization environment was wired from scratch which made it very difficult to add features such as virtual reality. Solution method: A new software is developed completely from scratch following Celeris Advent, called Celeris Base. This software uses the same hybrid finite volume–finite difference scheme to solve the extended Boussinesq equations, but using a variant of shaders called compute shaders, removing possible barriers for other researchers to understand the code and develop it further. The software is developed in Unity3D, a popular game engine with a large and helpful community as well as thousands of ready to use plugins. Celeris Base is equipped with virtual reality and is the first nearshore simulation software to provide this feature.";
  citeCeleris["doi"] = "https://doi.org/10.1016/j.cpc.2019.106966.";
  citeCeleris["license"] = "MIT License";
  citeCeleris["keywords"] = "Celeris; Boussinesq; Wave modeling; Immersive; Interactive; GPU";
  citeCeleris["year"] = "2020";
  citeCeleris["author"] = "Sasan Tavakkol and Patrick Lynett";
  citeCeleris["journal"] = "Computer Physics Communications";

  jsonObject["Taichi"] = citeTaichi;
  jsonObject["Celeris"] =  citeCeleris;
  return true;
}
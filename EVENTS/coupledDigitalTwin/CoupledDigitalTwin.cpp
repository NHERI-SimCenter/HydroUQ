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

#include "CoupledDigitalTwin.h"
#include <QScrollArea>
#include <QLineEdit>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QJsonObject>


#include <SettingsDigitalTwin.h>
#include <VisualizeDigitalTwin.h>
#include <OpenSeesDigitalTwin.h>
#include <OpenFOAM_DigitalTwin.h>
#include <OutputsDigitalTwin.h>

CoupledDigitalTwin::CoupledDigitalTwin(QWidget *parent)
    : SimCenterAppWidget(parent)
{
    int windowWidth = 800;

    QWidget     *mainGroup = new QWidget();
    QGridLayout *mainLayout = new QGridLayout();

    QLabel *generalDescriptionLabel = new QLabel("Coupled Digital Twin Simulation of Structures within NHERI Experimental Facilities.: "
                                                 "\n --> Specify Simulation Settings "						 
                                                 "\n --> Define OpenSeesPy Model "
                                                 "\n --> Specify OpenFOAM Model and specify initial conditions. "
                                                 "\n --> Specify Alternative Outputs for Validation "
                                                 "\n --> Run Coupled Simulation & Visualize");



    mainLayout->addWidget(generalDescriptionLabel, 0, 0);

    QTabWidget *theTabWidget = new QTabWidget();
    inputSettings = new SettingsDigitalTwin();
    theTabWidget->addTab(inputSettings, "Settings");
    inputOpenSees = new OpenSeesDigitalTwin();
    theTabWidget->addTab(inputOpenSees, "OpenSees");
    inputOpenFOAM = new OpenFOAM_DigitalTwin();
    theTabWidget->addTab(inputOpenFOAM, "OpenFOAM");
    inputOutputs = new OutputsDigitalTwin();
    theTabWidget->addTab(inputOutputs, "Outputs");
    inputVisualize = new VisualizeDigitalTwin();
    theTabWidget->addTab(inputVisualize, "Visualization");    
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


CoupledDigitalTwin::~CoupledDigitalTwin()
{

}


void CoupledDigitalTwin::clear(void)
{
  inputSettings->clear();
  inputOpenSees->clear();
  inputOpenFOAM->clear();
  inputOutputs->clear();
  inputVisualize->clear();
}


bool CoupledDigitalTwin::inputFromJSON(QJsonObject &jsonObject)
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
  
  inputOutputs->inputFromJSON(jsonObject);
  inputOpenSees->inputFromJSON(jsonObject);
  inputOpenFOAM->inputFromJSON(jsonObject);
  inputVisualize->inputFromJSON(jsonObject);
  inputSettings->inputFromJSON(jsonObject);
  
  return true;
}

bool CoupledDigitalTwin::outputToJSON(QJsonObject &jsonObject)
{
  jsonObject["EventClassification"]="Hydro";
  jsonObject["Application"] = "CoupledDigitalTwin";
    
  inputOutputs->outputToJSON(jsonObject);
  inputOpenSees->outputToJSON(jsonObject);
  inputOpenFOAM->outputToJSON(jsonObject);
  inputVisualize->outputToJSON(jsonObject);
  inputSettings->outputToJSON(jsonObject);
  
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

bool CoupledDigitalTwin::outputAppDataToJSON(QJsonObject &jsonObject) {

    //
    // per API, need to add name of application to be called in Application
    // and all data to be used in ApplicationData
    //

    jsonObject["EventClassification"]="Hydro";
    jsonObject["Application"] = "CoupledDigitalTwin";
    jsonObject["type"] = "CoupledDigitalTwin";

    QJsonObject dataObj;
    jsonObject["ApplicationData"] = dataObj;

    return true;
}
bool CoupledDigitalTwin::inputAppDataFromJSON(QJsonObject &jsonObject) {

    Q_UNUSED(jsonObject);
    return true;
}


bool CoupledDigitalTwin::copyFiles(QString &destDir) {
  if (inputOpenFOAM->copyFiles(destDir) == false) {
    qDebug() << "CoupledDigitalTwin - failed to copy inputOpenFOAM files";
    // return false;
  }
  if (inputOpenSees->copyFiles(destDir) == false) {
    qDebug() << "CoupledDigitalTwin - failed to copy inputOpenSees files";
    // return false;
  }
  return true;
 }

bool CoupledDigitalTwin::outputCitation(QJsonObject &jsonObject) {
  QJsonObject citeFOAMySees;
  QJsonObject citeOpenSees;
  QJsonObject citeOpenFOAM;
  citeFOAMySees["citation"] = "Lewis, Nicolette S. (2023). Development of an Open-Source Methodology for Simulation of Civil Engineering Structures Subject to Multi-Hazards. ProQuest Dissertations Publishing.";
  citeFOAMySees["description"] = "HydroUQ applied FOAMySees for two-way coupled CFD-FEA, developed in this thesis as the FOAMySees software. It couples OpenFOAM and OpenSees for the simulation of civil engineering structures subject to multi-hazards via the PreCICE coupling library.";
  citeOpenFOAM["citation"] = "Greenshields, Christopher. (2023). OpenFOAM v11 User Guide. OpenFOAM Foundation.";
  citeOpenFOAM["description"] = "HydroUQ uses OpenFOAM for high-quality 3D Navier-Stokes solutions. OpenFOAM is a free, open-source software package for computational fluid dynamics (CFD) that is widely used in academia and industry. It is developed by the OpenFOAM Foundation, which is a non-profit organization that promotes the use of open-source software in engineering and science.";
  citeOpenSees["citation"] = "McKenna, F., Scott, M. H., and Fenves, G. L. (2010) “Nonlinear finite-element analysis software architecture using object composition.” Journal of Computing in Civil Engineering, 24(1):95-107.";
  citeOpenSees["description"] = "HydroUQ incorporates OpenSees for defining structural models in the SimCenter workflow. OpenSees is a software framework for developing applications to simulate the performance of structural and geotechnical systems subjected to earthquakes. It is developed by the Pacific Earthquake Engineering Research Center (PEER) at the University of California, Berkeley.";
  jsonObject["FOAMySees"] = citeFOAMySees;
  jsonObject["OpenFOAM"] =  citeOpenFOAM;
  jsonObject["OpenSees"] =  citeOpenSees;
  return true;
}
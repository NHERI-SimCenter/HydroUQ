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

#include <SettingsDigitalTwin.h>
#include <QLabel>
#include <QComboBox>
#include <QGroupBox>
#include <QGridLayout>
#include <SC_ComboBox.h>
#include <SC_DoubleLineEdit.h>
#include <SC_IntLineEdit.h>



SettingsDigitalTwin::SettingsDigitalTwin(QWidget *parent)
  :SimCenterWidget(parent)
{
  QGridLayout *layout = new QGridLayout();
  this->setLayout(layout);

  QGroupBox *simSettings = new QGroupBox("Simulation Settings");
  QGridLayout *simSettingsLayout = new QGridLayout();  
  simSettings->setLayout(simSettingsLayout);

  QStringList yesNo; yesNo << "Yes" << "No";  

  timeStep = new SC_DoubleLineEdit("SolutionDT", 1e-6);
  simulationLength = new SC_DoubleLineEdit("SimDuration", 10.0);
  preloadStructure = new SC_ComboBox("ApplyGravity", yesNo);
  runPreliminaryAnalysis = new SC_ComboBox("runPrelim",yesNo);

  simSettingsLayout->addWidget(new QLabel("Time Step"), 0, 0);
  simSettingsLayout->addWidget(new QLabel("sec."), 0, 2);  
  simSettingsLayout->addWidget(new QLabel("Duration"), 1, 0);
  simSettingsLayout->addWidget(new QLabel("sec."), 1, 2);
  simSettingsLayout->addWidget(new QLabel("Preload Stucture w/ Gravity"), 2, 0);
  simSettingsLayout->addWidget(new QLabel("Run Preliminary Structural Analysis"), 3, 0);    

  simSettingsLayout->addWidget(timeStep,0,1);
  simSettingsLayout->addWidget(simulationLength,1,1);
  simSettingsLayout->addWidget(preloadStructure,2,1);
  simSettingsLayout->addWidget(runPreliminaryAnalysis,3,1);      
  
  QGroupBox *foamSettings = new QGroupBox("OpenFOAM Settings");
  QGridLayout *foamSettingsLayout = new QGridLayout();
  foamSettings->setLayout(foamSettingsLayout);
  
  foamSettingsLayout->addWidget(new QLabel("Adjust Timestep"), 0, 0);
  foamSettingsLayout->addWidget(new QLabel("Turbulence"), 1, 0);
  foamSettingsLayout->addWidget(new QLabel("Number of Processsors"), 2, 0);
  foamSettingsLayout->addWidget(new QLabel("Start Event Recording Time"), 3, 0);    
  
  adjustTimestep = new SC_ComboBox("AdjustTimeStep", yesNo);
  turbulance = new SC_ComboBox("Turbulence", yesNo);
  numProcessors = new SC_IntLineEdit("numProcessors", 32);
  startEvent = new SC_DoubleLineEdit("start",0.0);
  
  foamSettingsLayout->addWidget(adjustTimestep, 0, 1);
  foamSettingsLayout->addWidget(turbulance, 1, 1);
  foamSettingsLayout->addWidget(numProcessors, 2, 1);
  foamSettingsLayout->addWidget(startEvent, 3, 1);  

  gravZ = new SC_DoubleLineEdit("g", -9.81);

  QGroupBox *couplingSettings = new QGroupBox("OpenCOUPLING Settings");
  QGridLayout *couplingSettingsLayout = new QGridLayout();
  couplingSettings->setLayout(couplingSettingsLayout);
  
  couplingSettingsLayout->addWidget(new QLabel("Coupling Scheme"), 0, 0);
  couplingSettingsLayout->addWidget(new QLabel("Coupling Data Acceleration Method"), 1, 0);
  couplingSettingsLayout->addWidget(new QLabel("Initial Relaxation Factor"), 2, 0);
  couplingSettingsLayout->addWidget(new QLabel("Maximum Coupling Iterations"), 3, 0);
  couplingSettingsLayout->addWidget(new QLabel("Coupling Iteration Convergence Tolerance"), 4, 0);
  couplingSettingsLayout->addWidget(new QLabel("Data Mapping Scheme"), 5, 0);
  couplingSettingsLayout->addWidget(new QLabel("Output Data From Coupling Iterations"), 6, 0);
  couplingSettingsLayout->addWidget(new QLabel("Coupling Iteration Output Data Frequency"), 7, 0);    

  QStringList couplingList; couplingList << "Implicit" << "Explicit";
  couplingScheme = new SC_ComboBox("CouplingScheme", couplingList);

  QStringList couplingMethod; couplingMethod << "Constant" << "Aitken" << "IQN-IMVJ" << "Broyden";  
  couplingDataMethod = new SC_ComboBox("couplingDataAccelerationMethod", couplingMethod);
  
  initialRelaxationFactor = new SC_DoubleLineEdit("initialRelaxationFactor", 0.6);
  maxCouplingIterations = new SC_IntLineEdit("maximumCouplingIterations", 100);
  maxCouplingIterationConvergence = new SC_DoubleLineEdit("couplingConvergenceTol", 1e-5);

  QStringList dataMapping; dataMapping << "Nearest Neighbor" << "rbf-thin-plate-splines";    
  dataMappingScheme = new SC_ComboBox("mapType", dataMapping);
  outputDataFromCoupling = new SC_ComboBox("outputDataFromCouplingIterations", yesNo);
  maxCouplingIterationDataFrequency = new SC_IntLineEdit("couplingIterationOutputDataFrequency", 100);

  couplingSettingsLayout->addWidget(couplingScheme,0,1);
  couplingSettingsLayout->addWidget(couplingDataMethod,1,1);
  couplingSettingsLayout->addWidget(initialRelaxationFactor,2,1);
  couplingSettingsLayout->addWidget(maxCouplingIterations,3,1);
  couplingSettingsLayout->addWidget(maxCouplingIterationConvergence,4,1);
  couplingSettingsLayout->addWidget(dataMappingScheme,5,1);
  couplingSettingsLayout->addWidget(outputDataFromCoupling,6,1);
  couplingSettingsLayout->addWidget(maxCouplingIterationDataFrequency,7,1);

  //  simSettings->setMaximumWidth(300);  
  layout->addWidget(simSettings,0,0);
  layout->addWidget(foamSettings,1,0);  
  layout->addWidget(couplingSettings,2,0);    
}

SettingsDigitalTwin::~SettingsDigitalTwin()
{

}

bool
SettingsDigitalTwin::outputToJSON(QJsonObject &jsonObject)
{
  numProcessors->outputToJSON(jsonObject);
  startEvent->outputToJSON(jsonObject);
  timeStep->outputToJSON(jsonObject);
  simulationLength->outputToJSON(jsonObject);
  preloadStructure->outputToJSON(jsonObject);
  runPreliminaryAnalysis->outputToJSON(jsonObject);

  adjustTimestep->outputToJSON(jsonObject);
  turbulance->outputToJSON(jsonObject);  

  gravZ->outputToJSON(jsonObject);    
  
  couplingScheme->outputToJSON(jsonObject);
  couplingDataMethod->outputToJSON(jsonObject);
  initialRelaxationFactor->outputToJSON(jsonObject);
  maxCouplingIterations->outputToJSON(jsonObject);
  maxCouplingIterationConvergence->outputToJSON(jsonObject);
  dataMappingScheme->outputToJSON(jsonObject);
  outputDataFromCoupling->outputToJSON(jsonObject);
  maxCouplingIterationDataFrequency->outputToJSON(jsonObject);
  
  return true;
}

bool
SettingsDigitalTwin::inputFromJSON(QJsonObject &jsonObject)
{
  numProcessors->inputFromJSON(jsonObject);
  startEvent->inputFromJSON(jsonObject);
  timeStep->inputFromJSON(jsonObject);
  simulationLength->inputFromJSON(jsonObject);
  preloadStructure->inputFromJSON(jsonObject);
  runPreliminaryAnalysis->inputFromJSON(jsonObject);

  adjustTimestep->inputFromJSON(jsonObject);
  turbulance->inputFromJSON(jsonObject);  

  gravZ->inputFromJSON(jsonObject);    
  
  couplingScheme->inputFromJSON(jsonObject);
  couplingDataMethod->inputFromJSON(jsonObject);
  initialRelaxationFactor->inputFromJSON(jsonObject);
  maxCouplingIterations->inputFromJSON(jsonObject);
  maxCouplingIterationConvergence->inputFromJSON(jsonObject);
  dataMappingScheme->inputFromJSON(jsonObject);
  outputDataFromCoupling->inputFromJSON(jsonObject);
  maxCouplingIterationDataFrequency->inputFromJSON(jsonObject);
  
  return true;
}


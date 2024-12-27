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


#include <OutputsDigitalTwin.h>
#include <QGroupBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QStringList>
#include <QJsonArray>
#include <QTabWidget>
#include <QDebug>

#include <QJsonObject>
#include <QJsonArray>

#include <SC_TableEdit.h>
#include <SC_ComboBox.h>
#include <SC_DoubleLineEdit.h>



OutputsDigitalTwin::OutputsDigitalTwin(QWidget *parent)
  :SimCenterWidget(parent)
{

  //
  // create all widgets
  //
  
  QStringList yesNo; yesNo << "Yes" << "No";
  
  vtkOS_Output = new SC_ComboBox("SeesVTKOUT",yesNo);  
  vtkOF_Output = new SC_ComboBox("interfaceSurfaceOutput", yesNo);;
  outputOS_Dt  = new SC_DoubleLineEdit("SeesVTKOUTRate", 0.1);
  outputOF_Dt  = new SC_DoubleLineEdit("writeDT", 0.1);
  
  outputOF_FM  = new SC_ComboBox("freeSurfOut", yesNo);
  outputOF_FSP = new SC_ComboBox("freeSurfProbes", yesNo);
  outputOF_FP  = new SC_ComboBox("fieldProbes", yesNo);
  outputOF_SC  = new SC_ComboBox("cutSurfaceOutput", yesNo);
  
  QStringList  listFSP; listFSP << "X" << "Y" << "Z" << "tag";
  QStringList  dataFSP; dataFSP << "0.05" << "0.2" << "0.5" << "WaveGauge1"
				<< "0.15" << "0.2" << "0.5" << "WaveGauge2"
				<< "0.25" << "0.2" << "0.5" << "WaveGauge3";
  freeSurfaceProbes = new SC_TableEdit("freeSurfProbeLocs",  listFSP, 3, dataFSP);
  
  QStringList  listFP; listFP << "X" << "Y" << "Z" << "tag"  << "Field(U,p, etc.)";
  QStringList  dataFP; dataFP << "0.1"  << "0.3" << "0.45"  << "PressureProbe1" << "p"
				<< "0.1"  << "0.3" << "0.425" << "PressureProbe1" << "p"
				<< "0.1"  << "0.3" << "0.4"   << "PressureProbe1" << "p"
				<< "0.05" << "0.2" << "0.4"   << "VelocityProbe1" << "u";			  

  fieldProbes  = new SC_TableEdit("fieldProbeLocs", listFP, 4, dataFP);
  
  QStringList  listSC; listSC << "X" << "Y" << "Z" << "X" << "Y" << "Z" << "tag" << "Field(U,p, etc.)";
  QStringList  dataSC; dataSC << "0" << "0.1" << "0.25" << "0" << "1" << "0" << "XSec1" << "p,U,alpha,water";  
  sectionCuts  = new SC_TableEdit("cutSurfaceLocsDirsFields", listSC, 1, dataSC);

  // 
  // now add the widgets to Group Boxes
  //

  QGroupBox *openseesBox = new QGroupBox("OpenSees Outputs");
  QGridLayout *openseesLayout = new QGridLayout();  
  openseesBox->setLayout(openseesLayout);

  openseesLayout->addWidget(new QLabel("Output VTK"),0,0);
  openseesLayout->addWidget(vtkOS_Output,0,1);  
  openseesLayout->addWidget(new QLabel("Time Interval"),1,0);
  openseesLayout->addWidget(outputOS_Dt,1,1);
  openseesLayout->addWidget(new QLabel("sec."),1,2);  
			    
  QGroupBox *openfoamBox = new QGroupBox("OpenFOAM Outputs");
  QGridLayout *openfoamLayout = new QGridLayout();  
  openfoamBox->setLayout(openfoamLayout);

  openfoamLayout->addWidget(new QLabel("Output VTK"),0,0);
  openfoamLayout->addWidget(vtkOF_Output,0,1);    
  openfoamLayout->addWidget(new QLabel("Time Interval"),1,0);
  openfoamLayout->addWidget(outputOF_Dt,1,1);
  openfoamLayout->addWidget(new QLabel("sec."),1,2);

  QWidget *fspWidget = new QWidget();
  QGridLayout *fspLayout = new QGridLayout();
  fspWidget->setLayout(fspLayout);
  
  fspLayout->addWidget(new QLabel("Free Surface Probes"),0,0);
  fspLayout->addWidget(outputOF_FSP,0,1);
  fspLayout->addWidget(freeSurfaceProbes,1,0,1,4);

  QWidget *fpWidget = new QWidget();
  QGridLayout *fpLayout = new QGridLayout();
  fpWidget->setLayout(fpLayout);
  
  fpLayout->addWidget(new QLabel("Field Probes"),0,0);
  fpLayout->addWidget(outputOF_FP,0,1);
  fpLayout->addWidget(fieldProbes,1,0,1,4);


  QWidget *scWidget = new QWidget();
  QGridLayout *scLayout = new QGridLayout();
  scWidget->setLayout(scLayout);
  
  scLayout->addWidget(new QLabel("Section Cuts"),0,0);
  scLayout->addWidget(outputOF_SC,0,1);
  scLayout->addWidget(sectionCuts,1,0,1,4);    

  QTabWidget *theTabWidget = new QTabWidget();
  theTabWidget->addTab(fspWidget, "Free Surface Probes");
  theTabWidget->addTab(fpWidget, "FieldProbes");
  theTabWidget->addTab(scWidget, "Section Cuts");  

  openfoamLayout->addWidget(theTabWidget,2,0,1,4);
  
  /*
  openfoamLayout->addWidget(new QLabel("Field Probes"),4,0);
  openfoamLayout->addWidget(outputOF_FP,4,1);
  openfoamLayout->addWidget(fieldProbes,5,0,1,4);  
  openfoamLayout->addWidget(new QLabel("Section Cuts"),6,0);
  openfoamLayout->addWidget(outputOF_SC,6,1);      
  openfoamLayout->addWidget(sectionCuts,7,0,1, 4);    
  */
  
  //
  // now boxes to this widget
  //
  
  QGridLayout *layout = new QGridLayout;
  layout->addWidget(openseesBox, 0,0);
  layout->addWidget(openfoamBox, 1,0);

  
  this->setLayout(layout);
}

OutputsDigitalTwin::~OutputsDigitalTwin()
{

}

void 
OutputsDigitalTwin::clear(void)
{
  vtkOS_Output->clear();
  vtkOF_Output->clear();
  outputOS_Dt->clear();
  outputOF_Dt->clear();
  outputOF_FM->clear();
  outputOF_FSP->clear();
  outputOF_FP->clear();
  outputOF_SC->clear();
  // freeSurfaceProbes->clear();
  // fieldProbes->clear();
  // sectionCuts->clear();
}

bool
OutputsDigitalTwin::outputToJSON(QJsonObject &jsonObject)
{
  vtkOS_Output->outputToJSON(jsonObject);  
  vtkOF_Output->outputToJSON(jsonObject);
  outputOS_Dt->outputToJSON(jsonObject);
  outputOF_Dt->outputToJSON(jsonObject);
  outputOF_FM->outputToJSON(jsonObject);
  outputOF_FSP->outputToJSON(jsonObject);
  outputOF_FP->outputToJSON(jsonObject);
  outputOF_SC->outputToJSON(jsonObject);
  freeSurfaceProbes->outputToJSON(jsonObject);
  fieldProbes->outputToJSON(jsonObject);
  sectionCuts->outputToJSON(jsonObject);
  
  return true;
}

bool
OutputsDigitalTwin::inputFromJSON(QJsonObject &jsonObject)
{
  this->clear();

  vtkOS_Output->inputFromJSON(jsonObject);  
  vtkOF_Output->inputFromJSON(jsonObject);
  outputOS_Dt->inputFromJSON(jsonObject);
  outputOF_Dt->inputFromJSON(jsonObject);
  outputOF_FM->inputFromJSON(jsonObject);
  outputOF_FSP->inputFromJSON(jsonObject);
  outputOF_FP->inputFromJSON(jsonObject);
  outputOF_SC->inputFromJSON(jsonObject);
  freeSurfaceProbes->inputFromJSON(jsonObject);
  fieldProbes->inputFromJSON(jsonObject);
  sectionCuts->inputFromJSON(jsonObject);
  
  return true;
}


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

#include <SensorsMPM.h>
#include <QLabel>
#include <QGridLayout>

#include <SC_FileEdit.h>

SensorsMPM::SensorsMPM(QWidget *parent)
  :SimCenterWidget(parent)
{

  theOpenSeesPyScript = new SC_FileEdit("openSeesPyScript");
  theSurfaceFile = new SC_FileEdit("interfaceSurface");

  QGridLayout *theLayout = new QGridLayout();
  theLayout->addWidget(new QLabel("OpenSeesPy Script"),0,0);
  theLayout->addWidget(theOpenSeesPyScript, 0,1);
  theLayout->addWidget(new QLabel("Surface File"),1,0);
  theLayout->addWidget(theSurfaceFile, 1,1);
  theLayout->setRowStretch(2,1);
  this->setLayout(theLayout);
    
}

SensorsMPM::~SensorsMPM()
{

}

bool
SensorsMPM::outputToJSON(QJsonObject &jsonObject)
{
  theOpenSeesPyScript->outputToJSON(jsonObject);
  theSurfaceFile->outputToJSON(jsonObject);  
  return true;
}

bool
SensorsMPM::inputFromJSON(QJsonObject &jsonObject)
{
  theOpenSeesPyScript->inputFromJSON(jsonObject);
  theSurfaceFile->inputFromJSON(jsonObject);    
  return true;
}

bool
SensorsMPM::copyFiles(QString &destDir)
{
  if (theOpenSeesPyScript->copyFile(destDir) != true)
    return false;
  return theSurfaceFile->copyFile(destDir);    
}


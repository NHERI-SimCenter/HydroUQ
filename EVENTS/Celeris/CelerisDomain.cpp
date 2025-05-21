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

#include <CelerisDomain.h>
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

CelerisDomain::CelerisDomain(RandomVariablesContainer* randomVariables, QWidget *parent)
  :SimCenterWidget(parent)
{
    // SC_IntLineEdit *WIDTH;
    // SC_IntLineEdit *HEIGHT;
    // LineEditRV *dx;
    // LineEditRV *dy;
    // LineEditRV *Courant_num;
    // LineEditRV *base_depth;
    // LineEditRV *friction;
    // SC_IntLineEdit *isManning;
    // SC_IntLineEdit *boundary_shift;
    // LineEditRV *seaLevel;
    // LineEditRV *north_seaLevel;
    // LineEditRV *south_seaLevel;
    // LineEditRV *east_seaLevel;
    // LineEditRV *west_seaLevel;
    // SC_IntLineEdit *WaveType;
    // LineEditRV *amplitude;
    // LineEditRV *period;
    // SC_IntLineEdit *BoundaryWidth;
    // SC_IntLineEdit *north_boundary_type;
    // SC_IntLineEdit *south_boundary_type;
    // SC_IntLineEdit *east_boundary_type;
    // SC_IntLineEdit *west_boundary_type;

  WIDTH = new SC_IntLineEdit("WIDTH", 873);
  HEIGHT = new SC_IntLineEdit("HEIGHT", 437);
  dx = new LineEditRV(randomVariables);
  dx->setText("0.05");
  dy = new LineEditRV(randomVariables);
  dy->setText("0.05");
  // Courant_num = new LineEditRV(randomVariables);
  // Courant_num->setText("0.2");
  base_depth = new LineEditRV(randomVariables);
  base_depth->setText("0.75202286");
  friction = new LineEditRV(randomVariables);
  friction->setText("0.001");
  isManning = new SC_IntLineEdit("isManning", 0);
  boundary_shift = new SC_IntLineEdit("boundary_shift", 4);
  seaLevel = new LineEditRV(randomVariables);
  seaLevel->setText("0.0");
  north_seaLevel = new LineEditRV(randomVariables);
  north_seaLevel->setText("0.0");
  south_seaLevel = new LineEditRV(randomVariables);
  south_seaLevel->setText("0.0");
  east_seaLevel = new LineEditRV(randomVariables);
  east_seaLevel->setText("0.0");
  west_seaLevel = new LineEditRV(randomVariables);
  west_seaLevel->setText("0.0");
  WaveType = new SC_IntLineEdit("WaveType", 3);
  amplitude = new LineEditRV(randomVariables);
  amplitude->setText("0.5");
  period = new LineEditRV(randomVariables);
  period->setText("20.0");
  BoundaryWidth = new SC_IntLineEdit("BoundaryWidth", 20);
  north_boundary_type = new SC_IntLineEdit("north_boundary_type", 0);
  south_boundary_type = new SC_IntLineEdit("south_boundary_type", 0);
  east_boundary_type = new SC_IntLineEdit("east_boundary_type", 0);
  west_boundary_type = new SC_IntLineEdit("west_boundary_type", 2);

  int numRow = 0;
  QGridLayout *theLayout = new QGridLayout();
  theLayout->addWidget(new QLabel("WIDTH"), numRow, 0, 1, 2);
  theLayout->addWidget(WIDTH, numRow, 2, 1, 3);
  numRow++;
  theLayout->addWidget(new QLabel("HEIGHT"), numRow, 0, 1, 2);
  theLayout->addWidget(HEIGHT, numRow, 2, 1, 3);
  numRow++;
  theLayout->addWidget(new QLabel("dx"), numRow, 0, 1, 2);
  theLayout->addWidget(dx, numRow, 2, 1, 3);
  numRow++;
  theLayout->addWidget(new QLabel("dy"), numRow, 0, 1, 2);
  theLayout->addWidget(dy, numRow, 2, 1, 3);
  numRow++;
  theLayout->addWidget(new QLabel("base_depth"), numRow, 0, 1, 2);
  theLayout->addWidget(base_depth, numRow, 2, 1, 3);
  numRow++;
  theLayout->addWidget(new QLabel("friction"), numRow, 0, 1, 2);
  theLayout->addWidget(friction, numRow, 2, 1, 3);
  numRow++;
  theLayout->addWidget(new QLabel("isManning"), numRow, 0, 1, 2);
  theLayout->addWidget(isManning, numRow, 2, 1, 3);
  numRow++;
  theLayout->addWidget(new QLabel("boundary_shift"), numRow, 0, 1, 2);
  theLayout->addWidget(boundary_shift, numRow, 2, 1, 3);
  numRow++;
  theLayout->addWidget(new QLabel("seaLevel"), numRow, 0, 1, 2);
  theLayout->addWidget(seaLevel, numRow, 2, 1, 3);
  numRow++;
  theLayout->addWidget(new QLabel("north_seaLevel"), numRow, 0, 1, 2);
  theLayout->addWidget(north_seaLevel, numRow, 2, 1, 3);
  numRow++;
  theLayout->addWidget(new QLabel("south_seaLevel"), numRow, 0, 1, 2);
  theLayout->addWidget(south_seaLevel, numRow, 2, 1, 3);
  numRow++;
  theLayout->addWidget(new QLabel("east_seaLevel"), numRow, 0, 1, 2);
  theLayout->addWidget(east_seaLevel, numRow, 2, 1, 3);
  numRow++;
  theLayout->addWidget(new QLabel("west_seaLevel"), numRow, 0, 1, 2);
  theLayout->addWidget(west_seaLevel, numRow, 2, 1, 3);
  numRow++;
  theLayout->addWidget(new QLabel("WaveType"), numRow, 0, 1, 2);
  theLayout->addWidget(WaveType, numRow, 2, 1, 3);
  numRow++;
  theLayout->addWidget(new QLabel("amplitude"), numRow, 0, 1, 2);
  theLayout->addWidget(amplitude, numRow, 2, 1, 3);
  numRow++;
  theLayout->addWidget(new QLabel("period"), numRow, 0, 1, 2);
  theLayout->addWidget(period, numRow, 2, 1, 3);
  numRow++;
  theLayout->addWidget(new QLabel("BoundaryWidth"), numRow, 0, 1, 2);
  theLayout->addWidget(BoundaryWidth, numRow, 2, 1, 3);
  numRow++;
  theLayout->addWidget(new QLabel("north_boundary_type"), numRow, 0, 1, 2);
  theLayout->addWidget(north_boundary_type, numRow, 2, 1, 3);
  numRow++;
  theLayout->addWidget(new QLabel("south_boundary_type"), numRow, 0, 1, 2);
  theLayout->addWidget(south_boundary_type, numRow, 2, 1, 3);
  numRow++;
  theLayout->addWidget(new QLabel("east_boundary_type"), numRow, 0, 1, 2);
  theLayout->addWidget(east_boundary_type, numRow, 2, 1, 3);
  numRow++;
  theLayout->addWidget(new QLabel("west_boundary_type"), numRow, 0, 1, 2);
  theLayout->addWidget(west_boundary_type, numRow, 2, 1, 3);
  numRow++;
  
  this->setLayout(theLayout);
}

CelerisDomain::~CelerisDomain()
{

}

bool
CelerisDomain::outputToJSON(QJsonObject &jsonObject)
{

  QJsonObject configObj;
  configObj = jsonObject["config"].toObject();

  WIDTH->outputToJSON(configObj);
  HEIGHT->outputToJSON(configObj);
  dx->outputToJSON(configObj, QString("dx"));
  dy->outputToJSON(configObj, QString("dy"));
  // Courant_num->outputToJSON(configObj, QString("Courant_num"));
  base_depth->outputToJSON(configObj, QString("base_depth"));
  friction->outputToJSON(configObj, QString("friction"));
  isManning->outputToJSON(configObj);
  boundary_shift->outputToJSON(configObj);
  seaLevel->outputToJSON(configObj, QString("seaLevel"));
  north_seaLevel->outputToJSON(configObj, QString("north_seaLevel"));
  south_seaLevel->outputToJSON(configObj, QString("south_seaLevel"));
  east_seaLevel->outputToJSON(configObj, QString("east_seaLevel"));
  west_seaLevel->outputToJSON(configObj, QString("west_seaLevel"));
  WaveType->outputToJSON(configObj);
  amplitude->outputToJSON(configObj, QString("amplitude"));
  period->outputToJSON(configObj, QString("period"));
  BoundaryWidth->outputToJSON(configObj);
  north_boundary_type->outputToJSON(configObj);
  south_boundary_type->outputToJSON(configObj);
  east_boundary_type->outputToJSON(configObj);
  west_boundary_type->outputToJSON(configObj);
  jsonObject["config"] = configObj;
  return true;
}

bool
CelerisDomain::inputFromJSON(QJsonObject &jsonObject)
{
  
  QJsonObject configObj;
  configObj = jsonObject["config"].toObject();

  WIDTH->inputFromJSON(configObj);
  HEIGHT->inputFromJSON(configObj);
  dx->inputFromJSON(configObj, QString("dx"));
  dy->inputFromJSON(configObj, QString("dy"));
  // Courant_num->inputFromJSON(configObj, QString("Courant_num"));
  base_depth->inputFromJSON(configObj, QString("base_depth"));
  friction->inputFromJSON(configObj, QString("friction"));
  isManning->inputFromJSON(configObj);
  boundary_shift->inputFromJSON(configObj);
  seaLevel->inputFromJSON(configObj, QString("seaLevel"));
  north_seaLevel->inputFromJSON(configObj, QString("north_seaLevel"));
  south_seaLevel->inputFromJSON(configObj, QString("south_seaLevel"));
  east_seaLevel->inputFromJSON(configObj, QString("east_seaLevel"));
  west_seaLevel->inputFromJSON(configObj, QString("west_seaLevel"));
  WaveType->inputFromJSON(configObj);
  amplitude->inputFromJSON(configObj, QString("amplitude"));
  period->inputFromJSON(configObj, QString("period"));
  BoundaryWidth->inputFromJSON(configObj);
  north_boundary_type->inputFromJSON(configObj);
  south_boundary_type->inputFromJSON(configObj);
  east_boundary_type->inputFromJSON(configObj);
  west_boundary_type->inputFromJSON(configObj);
  
  jsonObject["config"] = configObj;
  return true;
}


bool
CelerisDomain::copyFiles(QString &destDir)
{
  return true;
}


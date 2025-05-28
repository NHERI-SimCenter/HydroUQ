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
#include <QStringList>
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
#include <SC_ComboBox.h>
#include <SC_CheckBox.h>
#include <QGroupBox>

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
  // isManning = new SC_IntLineEdit("isManning", 0);
  isManning = new SC_CheckBox("isManning", 0);

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
  WaveType = new SC_ComboBox("WaveType", QStringList() << "File" << "Sine" << "Solitary");
  WaveType->setCurrentIndex(0);
  amplitude = new LineEditRV(randomVariables);
  amplitude->setText("0.5");
  period = new LineEditRV(randomVariables);
  period->setText("20.0");
  direction = new LineEditRV(randomVariables);
  direction->setText("0.0");
  phase = new LineEditRV(randomVariables);
  phase->setText("0.0");
  BoundaryWidth = new SC_IntLineEdit("BoundaryWidth", 20);
  north_boundary_type = new SC_ComboBox("north_boundary_type", QStringList() << "Solid Wall" << "Sponge Layer" << "Incoming Waves");
  north_boundary_type->setCurrentIndex(1);
  south_boundary_type = new SC_ComboBox("south_boundary_type", QStringList() << "Solid Wall" << "Sponge Layer" << "Incoming Waves");
  south_boundary_type->setCurrentIndex(0);
  east_boundary_type = new SC_ComboBox("east_boundary_type", QStringList() << "Solid Wall" << "Sponge Layer" << "Incoming Waves");
  east_boundary_type->setCurrentIndex(0);
  west_boundary_type = new SC_ComboBox("west_boundary_type", QStringList() << "Solid Wall" << "Sponge Layer" << "Incoming Waves");
  west_boundary_type->setCurrentIndex(2);


  int numRow = 0;
  QGridLayout *theLayout = new QGridLayout();

  int numRowDomain = 0;
  QGroupBox *theDomainGroupBox = new QGroupBox("Domain");
  QGridLayout *theDomainLayout = new QGridLayout();
  theDomainGroupBox->setLayout(theDomainLayout);
  theDomainLayout->addWidget(new QLabel("WIDTH"), numRowDomain, 0, 1, 2);
  theDomainLayout->addWidget(WIDTH, numRowDomain, 2, 1, 3);
  numRowDomain++;
  theDomainLayout->addWidget(new QLabel("HEIGHT"), numRowDomain, 0, 1, 2);
  theDomainLayout->addWidget(HEIGHT, numRowDomain, 2, 1, 3);
  numRowDomain++;
  theDomainLayout->addWidget(new QLabel("dx"), numRowDomain, 0, 1, 2);
  theDomainLayout->addWidget(dx, numRowDomain, 2, 1, 3);
  numRowDomain++;
  theDomainLayout->addWidget(new QLabel("dy"), numRowDomain, 0, 1, 2);
  theDomainLayout->addWidget(dy, numRowDomain, 2, 1, 3);
  numRowDomain++;
  theLayout->addWidget(theDomainGroupBox, numRow, 0, 1, 5);
  numRow++;

  int numRowBoundary = 0;
  QGroupBox *theBoundaryGroupBox = new QGroupBox("Boundary Conditions");
  QGridLayout *theBoundaryLayout = new QGridLayout();
  theBoundaryGroupBox->setLayout(theBoundaryLayout);
  theBoundaryLayout->addWidget(new QLabel("north_boundary_type"), numRowBoundary, 0, 1, 2);
  theBoundaryLayout->addWidget(north_boundary_type, numRowBoundary, 2, 1, 3);
  numRowBoundary++;
  theBoundaryLayout->addWidget(new QLabel("south_boundary_type"), numRowBoundary, 0, 1, 2);
  theBoundaryLayout->addWidget(south_boundary_type, numRowBoundary, 2, 1, 3);
  numRowBoundary++;
  theBoundaryLayout->addWidget(new QLabel("east_boundary_type"), numRowBoundary, 0, 1, 2);
  theBoundaryLayout->addWidget(east_boundary_type, numRowBoundary, 2, 1, 3);
  numRowBoundary++;
  theBoundaryLayout->addWidget(new QLabel("west_boundary_type"), numRowBoundary, 0, 1, 2);
  theBoundaryLayout->addWidget(west_boundary_type, numRowBoundary, 2, 1, 3);
  numRowBoundary++;
  theBoundaryLayout->addWidget(new QLabel("BoundaryWidth"), numRowBoundary, 0, 1, 2);
  theBoundaryLayout->addWidget(BoundaryWidth, numRowBoundary, 2, 1, 3);
  numRowBoundary++;
  theBoundaryLayout->addWidget(new QLabel("boundary_shift"), numRowBoundary, 0, 1, 2);
  theBoundaryLayout->addWidget(boundary_shift, numRowBoundary, 2, 1, 3);
  numRowBoundary++;
  theLayout->addWidget(theBoundaryGroupBox, numRow, 0, 1, 5);
  numRow++;

  int numRowWave = 0;
  QGroupBox *theWaveTypeGroupBox = new QGroupBox("Wave Type");
  QGridLayout *theWaveTypeLayout = new QGridLayout();
  theWaveTypeGroupBox->setLayout(theWaveTypeLayout);
  theWaveTypeLayout->addWidget(new QLabel("Wave Type"), numRowWave, 0, 1, 2);
  theWaveTypeLayout->addWidget(WaveType, numRowWave, 2, 1, 3);
  numRowWave++;
  theWaveTypeLayout->addWidget(new QLabel("amplitude"), numRowWave, 0, 1, 2);
  theWaveTypeLayout->addWidget(amplitude, numRowWave, 2, 1, 3);
  numRowWave++;
  theWaveTypeLayout->addWidget(new QLabel("period"), numRowWave, 0, 1, 2);
  theWaveTypeLayout->addWidget(period, numRowWave, 2, 1, 3);
  numRowWave++;
  theWaveTypeLayout->addWidget(new QLabel("direction"), numRowWave, 0, 1, 2);
  theWaveTypeLayout->addWidget(direction, numRowWave, 2, 1, 3);
  numRowWave++;
  theWaveTypeLayout->addWidget(new QLabel("phase"), numRowWave, 0, 1, 2);
  theWaveTypeLayout->addWidget(phase, numRowWave, 2, 1, 3);
  numRowWave++;
  theLayout->addWidget(theWaveTypeGroupBox, numRow, 0, 1, 5);
  numRow++;

  int numRowSea = 0;
  QGroupBox *theSeaLevelGroupBox = new QGroupBox("Sea Level");
  QGridLayout *theSeaLevelLayout = new QGridLayout();
  theSeaLevelGroupBox->setLayout(theSeaLevelLayout);
  theSeaLevelLayout->addWidget(new QLabel("seaLevel"), numRowSea, 0, 1, 2);
  theSeaLevelLayout->addWidget(seaLevel, numRowSea, 2, 1, 3);
  numRowSea++;
  theSeaLevelLayout->addWidget(new QLabel("north_seaLevel"), numRowSea, 0, 1, 2);
  theSeaLevelLayout->addWidget(north_seaLevel, numRowSea, 2, 1, 3);
  numRowSea++;
  theSeaLevelLayout->addWidget(new QLabel("south_seaLevel"), numRowSea, 0, 1, 2);
  theSeaLevelLayout->addWidget(south_seaLevel, numRowSea, 2, 1, 3);
  numRowSea++;
  theSeaLevelLayout->addWidget(new QLabel("east_seaLevel"), numRowSea, 0, 1, 2);
  theSeaLevelLayout->addWidget(east_seaLevel, numRowSea, 2, 1, 3);
  numRowSea++;
  theSeaLevelLayout->addWidget(new QLabel("west_seaLevel"), numRowSea, 0, 1, 2);
  theSeaLevelLayout->addWidget(west_seaLevel, numRowSea, 2, 1, 3);
  numRowSea++;
  theSeaLevelLayout->addWidget(new QLabel("base_depth"), numRowSea, 0, 1, 2);
  theSeaLevelLayout->addWidget(base_depth, numRowSea, 2, 1, 3);
  numRowSea++;
  theLayout->addWidget(theSeaLevelGroupBox, numRow, 0, 1, 5);
  numRow++;
  
  
  int numRowFriction = 0;
  QGroupBox *theFrictionGroupBox = new QGroupBox("Friction");
  QGridLayout *theFrictionLayout = new QGridLayout();
  theFrictionGroupBox->setLayout(theFrictionLayout);
  theFrictionLayout->addWidget(new QLabel("isManning"), numRowFriction, 0, 1, 2);
  theFrictionLayout->addWidget(isManning, numRowFriction, 2, 1, 3);
  numRowFriction++;
  theFrictionLayout->addWidget(new QLabel("friction"), numRowFriction, 0, 1, 2);
  theFrictionLayout->addWidget(friction, numRowFriction, 2, 1, 3);
  numRowFriction++;
  theLayout->addWidget(theFrictionGroupBox, numRow, 0, 1, 5);
  numRow++;

  theLayout->setRowStretch(numRow, 1);
  
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
  configObj["isManning"] = isManning->isChecked() ? int(1) : int(0);
  boundary_shift->outputToJSON(configObj);
  seaLevel->outputToJSON(configObj, QString("seaLevel"));
  north_seaLevel->outputToJSON(configObj, QString("north_seaLevel"));
  south_seaLevel->outputToJSON(configObj, QString("south_seaLevel"));
  east_seaLevel->outputToJSON(configObj, QString("east_seaLevel"));
  west_seaLevel->outputToJSON(configObj, QString("west_seaLevel"));
  // WaveType->outputToJSON(configObj);
  if (WaveType->currentText() == "File") {
    configObj["WaveType"] = int(-1);
  } else if (WaveType->currentText() == "Sine") {
    configObj["WaveType"] = int(2);
    QJsonArray sineWaveArray;

    amplitude->outputToJSON(configObj, QString("amplitude"));
    period->outputToJSON(configObj, QString("period"));
    direction->outputToJSON(configObj, QString("direction"));
    phase->outputToJSON(configObj, QString("phase"));
    if (configObj["amplitude"].isString()) {
      sineWaveArray.append(configObj["amplitude"].toString());
    } else if (configObj["amplitude"].isDouble()) {
      sineWaveArray.append(QString::number(configObj["amplitude"].toDouble()));
    }
    if (configObj["period"].isString()) {
      sineWaveArray.append(configObj["period"].toString());
    } else if (configObj["period"].isDouble()) {
      sineWaveArray.append(QString::number(configObj["period"].toDouble()));
    }
    if (configObj["direction"].isString()) {
      sineWaveArray.append(configObj["direction"].toString());
    } else if (configObj["direction"].isDouble()) {
      sineWaveArray.append(QString::number(configObj["direction"].toDouble()));
    }
    if (configObj["phase"].isString()) {
      sineWaveArray.append(configObj["phase"].toString());
    } else if (configObj["phase"].isDouble()) {
      sineWaveArray.append(QString::number(configObj["phase"].toDouble()));
    }
    configObj["sine_wave"] = sineWaveArray;

  } else if (WaveType->currentText() == "Solitary") {
    configObj["WaveType"] = int(3);
    amplitude->outputToJSON(configObj, QString("amplitude"));
    period->outputToJSON(configObj, QString("period"));
  }
  BoundaryWidth->outputToJSON(configObj);
  // north_boundary_type->outputToJSON(configObj);
  // south_boundary_type->outputToJSON(configObj);
  // east_boundary_type->outputToJSON(configObj);
  // west_boundary_type->outputToJSON(configObj);
  configObj["north_boundary_type"] = int(north_boundary_type->currentIndex());
  configObj["south_boundary_type"] = int(south_boundary_type->currentIndex());
  configObj["east_boundary_type"] = int(east_boundary_type->currentIndex());
  configObj["west_boundary_type"] = int(west_boundary_type->currentIndex());
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
  isManning->setChecked(configObj["isManning"].toInt() > 0);
  boundary_shift->inputFromJSON(configObj);
  seaLevel->inputFromJSON(configObj, QString("seaLevel"));
  north_seaLevel->inputFromJSON(configObj, QString("north_seaLevel"));
  south_seaLevel->inputFromJSON(configObj, QString("south_seaLevel"));
  east_seaLevel->inputFromJSON(configObj, QString("east_seaLevel"));
  west_seaLevel->inputFromJSON(configObj, QString("west_seaLevel"));
  // WaveType->inputFromJSON(configObj);
  if (configObj["WaveType"].toInt() == -1) {
    WaveType->setCurrentIndex(0);
    amplitude->inputFromJSON(configObj, QString("amplitude"));
    period->inputFromJSON(configObj, QString("period"));
  } else if (configObj["WaveType"].toInt() == 2 || configObj["WaveType"].toInt() == 1) {
    WaveType->setCurrentIndex(1);
    QJsonArray sineWaveArray = configObj["sine_wave"].toArray();
    if (sineWaveArray.size() > 0) {
      if (sineWaveArray[0].isString()) {
        amplitude->setText(sineWaveArray[0].toString());
      } else if (sineWaveArray[0].isDouble()) {
        amplitude->setText(QString::number(sineWaveArray[0].toDouble()));
      }
    }
    if (sineWaveArray.size() > 1) {
      if (sineWaveArray[1].isString()) {
        period->setText(sineWaveArray[1].toString());
      } else if (sineWaveArray[1].isDouble()) {
        period->setText(QString::number(sineWaveArray[1].toDouble()));
      }
    }
    if (sineWaveArray.size() > 2) {
      if (sineWaveArray[2].isString()) {
        direction->setText(sineWaveArray[2].toString());
      } else if (sineWaveArray[2].isDouble()) {
        direction->setText(QString::number(sineWaveArray[2].toDouble()));
      }
    }
    if (sineWaveArray.size() > 3) {
      if (sineWaveArray[3].isString()) {
        phase->setText(sineWaveArray[3].toString());
      } else if (sineWaveArray[3].isDouble()) {
        phase->setText(QString::number(sineWaveArray[3].toDouble()));
      }
    }
  } else if (configObj["WaveType"].toInt() == 3) {
    WaveType->setCurrentIndex(2);
    amplitude->inputFromJSON(configObj, QString("amplitude"));
    period->inputFromJSON(configObj, QString("period"));
  }

  BoundaryWidth->inputFromJSON(configObj);
  // north_boundary_type->inputFromJSON(configObj);
  // south_boundary_type->inputFromJSON(configObj);
  // east_boundary_type->inputFromJSON(configObj);
  // west_boundary_type->inputFromJSON(configObj);
  north_boundary_type->setCurrentIndex(configObj["north_boundary_type"].toInt());
  south_boundary_type->setCurrentIndex(configObj["south_boundary_type"].toInt());
  east_boundary_type->setCurrentIndex(configObj["east_boundary_type"].toInt());
  west_boundary_type->setCurrentIndex(configObj["west_boundary_type"].toInt());
  
  jsonObject["config"] = configObj;
  return true;
}


bool
CelerisDomain::copyFiles(QString &destDir)
{
  return true;
}


#ifndef BOUNDARIES_MPM_H
#define BOUNDARIES_MPM_H

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

/**
 *  @author  JustinBonus
 *  @date    1/2024
 *  @version 3.0
 *
 *  @section DESCRIPTION
 *
 *  This is the class providing the set of Boundaries for MPM
 */

#include <SimCenterWidget.h>

class QJsonObject;
class QJsonArray;
class SC_DoubleLineEdit;
class SC_IntLineEdit;
class SC_ComboBox;
class SC_TableEdit;
class SC_FileEdit;
class SC_CheckBox;
class SC_ComboBox;
class QStackedWidget;
class QGroupBox;

class BoundaryMPM;
class BoundariesMPM : public SimCenterWidget
{
public:
    BoundariesMPM(QWidget *parent = 0);
    virtual ~BoundariesMPM();
    bool outputToJSON(QJsonObject &jsonObject);
    bool inputFromJSON(QJsonObject &jsonObject);
    bool copyFiles(QString &dirName);  
    // bool setBoundaryType(int typeIdx);
    bool setDigitalTwin(int twinIdx);
    // bool setBoundary(int index, BoundaryMPM* theBoundary);
    int getNumBoundaries();
    bool getBoundary(int index, BoundaryMPM* &theBoundary);
    BoundaryMPM* getBoundary(int index);
    BoundaryMPM* getBoundary(QString name);
    int getStructureID();
    int getPaddleID();
    BoundaryMPM* getStructureBoundary();
    BoundaryMPM* getPaddleBoundary();

    double getDimensionX(BoundaryMPM* theBoundary);
    double getDimensionY(BoundaryMPM* theBoundary);
    double getDimensionZ(BoundaryMPM* theBoundary);
    SC_DoubleLineEdit* getDimensionXWidget(BoundaryMPM* theBoundary);
    SC_DoubleLineEdit* getDimensionYWidget(BoundaryMPM* theBoundary);
    SC_DoubleLineEdit* getDimensionZWidget(BoundaryMPM* theBoundary);

    double getOriginX(BoundaryMPM* theBoundary);
    double getOriginY(BoundaryMPM* theBoundary);
    double getOriginZ(BoundaryMPM* theBoundary);
    SC_DoubleLineEdit* getOriginXWidget(BoundaryMPM* theBoundary);
    SC_DoubleLineEdit* getOriginYWidget(BoundaryMPM* theBoundary);
    SC_DoubleLineEdit* getOriginZWidget(BoundaryMPM* theBoundary);


    // bool addBoundary(BoundaryMPM* theBoundary);
    // bool removeBoundary(int index);
    // bool removeBoundary(BoundaryMPM* theBoundary);
    // // bool clearBoundaries();
    // bool getBoundary(int index, BoundaryMPM* &theBoundary);
    // bool setBoundary(int index, BoundaryMPM* theBoundary);

// Whats the difference between signal and slot?
// https://stackoverflow.com/questions/3322153/what-is-the-difference-between-a-slot-and-a-signal

signals:
    // void structDimensionsChanged(void);
    // void structOriginChanged(void);
    // void structDimensionsChanged(QString val);
    // void structOriginChanged(QString val);

public slots:
    // void clear(void);
    // void structDimensionsChangedSlot(void);
    // void structOriginChangedSlot(void);

//     // void setBoundaryType(int typeIdx);
//     void setDigitalTwin(int twinIdx);
//     void setDimensionX(double value);
//     void setDimensionY(double value);
//     void setDimensionZ(double value);
//     void setOriginX(double value);
//     void setOriginY(double value);
//     void setOriginZ(double value);



private:
  int numReserveTabs = 8;
  int numAddedTabs = 0;
  int paddleID = 1;   
  int structureID = 2; // The specified design structure, 2 for default (3rd tab), -1 if the design structure is not specified / not a boundary (i.e. it is a body instead)
  QVector<BoundaryMPM*> addedBoundary {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
};

#endif // BOUNDARIES_MPM_H

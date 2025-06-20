#ifndef CELERIS_TAICHI_H
#define CELERIS_TAICHI_H

/* *****************************************************************************
Copyright (c) 2016-2024, The Regents of the University of California (Regents).
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
 *  @date    9/2024
 *  @version 4.0
 *
 *  @section CelerisTaichi simulates a hazard event (EVT) via the Celeris
 *  wave solver (nonlinear shallow water and Boussinesq equations) within the
 *  Taichi Lang framework. Taichi Lang is a domain-specific language for high-
 *  performance computation which abstracts the underlying hardware and data-
 *  parallelism in a Python-like syntax. The Celeris wave solver is a high-
 *  performance, open-source, and parallelized wave solver for simulating 
 *  nonlinear shallow water and Boussinesq equations. The Celeris wave solver
 *  includes various man-made and natural wave obstacles, such as mangroves,
 *  seawalls, and islands, and can simulate wave propagation and runup. The
 *  application includes sensors/recorders for measuring wave height, velocity,
 *  etc., and can visualize said quantities in near or faster-than-real-time.
 * 
 *  
 *
 *  This is the class providing the Celeris Tab for the TaichiEvent
 */

#include <SimCenterWidget.h>

class QJsonObject;
class SC_FileEdit;
class QCheckBox;
class SC_DoubleLineEdit;
class SC_TableEdit;
class QString;
class QLabel;
class SimCenterPreferences;

class CelerisTaichi : public SimCenterWidget
{
    Q_OBJECT
public:
    CelerisTaichi(QWidget *parent = 0);
    virtual ~CelerisTaichi();
    bool outputToJSON(QJsonObject &jsonObject);
    bool inputFromJSON(QJsonObject &jsonObject);
    bool inputFromConfigJSON(QJsonObject &jsonObject);
    bool copyFiles(QString &dirName);
    QString pyScriptsPath(void);
    QString examplesDirPath(void);
    void setConfigFile(QString &filename);
    void setWavesFile(QString &filename);
    void setBathymetryFile(QString &filename);
signals:
    void configFileChanged(void);

private:
  SC_FileEdit *theCelerisPyScript;
  SC_FileEdit *theSimulationScript;
  SC_FileEdit *theConfigurationFile;
  SC_FileEdit *theBathymetryFile;
  SC_FileEdit *theWaveFile;
  SC_TableEdit *theWaveGaugesTable;
  SC_DoubleLineEdit *theForceSensorBeginX;
  SC_DoubleLineEdit *theForceSensorBeginY;
  SC_DoubleLineEdit *theForceSensorEndX;
  SC_DoubleLineEdit *theForceSensorEndY;
  SC_DoubleLineEdit *theDx;
  SC_DoubleLineEdit *theDy;
  SC_DoubleLineEdit *long1Edit; /**< Longitude Lower-Left */
  SC_DoubleLineEdit *lat1Edit;  /**< Latitude Lower-Left */
  SC_DoubleLineEdit *long2Edit; /**< Longitude Upper-Right */
  SC_DoubleLineEdit *lat2Edit;  /**< Latitude Upper-Right */
  QCheckBox *theLatLongFSCheckBox; /**< Use Lat/Long for Force Sensor */
  QCheckBox *theLatLongWGCheckBox; /**< Use Lat/Long for Force Sensor and Bounding Box */
};

#endif // CELERIS_TAICHI_H


#ifndef CELERIS_DOMAIN_H
#define CELERIS_DOMAIN_H

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

class LineEditRV;
class RandomVariablesContainer;
class QJsonObject;
class SC_FileEdit;
class SC_DoubleLineEdit;
class SC_IntLineEdit;
class SC_TableEdit;
class QString;
class QLabel;
class SimCenterPreferences;
class SC_ComboBox;
class SC_CheckBox;

class CelerisDomain : public SimCenterWidget
{
    Q_OBJECT
public:
    explicit CelerisDomain(RandomVariablesContainer* random_variables, QWidget *parent = 0);
    virtual ~CelerisDomain();
    bool outputToJSON(QJsonObject &jsonObject);
    bool inputFromJSON(QJsonObject &jsonObject);
    bool copyFiles(QString &dirName);
signals:

private:
    SC_IntLineEdit *WIDTH;
    SC_IntLineEdit *HEIGHT;
    LineEditRV *dx;
    LineEditRV *dy;
    LineEditRV *Courant_num;
    LineEditRV *base_depth;
    LineEditRV *friction;
    SC_CheckBox *isManning;
    SC_IntLineEdit *boundary_shift;
    LineEditRV *seaLevel;
    LineEditRV *north_seaLevel;
    LineEditRV *south_seaLevel;
    LineEditRV *east_seaLevel;
    LineEditRV *west_seaLevel;
    SC_ComboBox *WaveType;
    LineEditRV *amplitude;
    LineEditRV *period;
    LineEditRV *direction;
    LineEditRV *phase;
    SC_IntLineEdit *BoundaryWidth;
    SC_ComboBox *north_boundary_type;
    SC_ComboBox *south_boundary_type;
    SC_ComboBox *east_boundary_type;
    SC_ComboBox *west_boundary_type;
};

#endif // CELERIS_TAICHI_H


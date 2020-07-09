/*********************************************************************************
**
** Copyright (c) 2020 University of California, Berkeley
**
** Redistribution and use in source and binary forms, with or without modification,
** are permitted provided that the following conditions are met:
**
** 1. Redistributions of source code must retain the above copyright notice, this
** list of conditions and the following disclaimer.
**
** 2. Redistributions in binary form must reproduce the above copyright notice, this
** list of conditions and the following disclaimer in the documentation and/or other
** materials provided with the distribution.
**
** 3. Neither the name of the copyright holder nor the names of its contributors may
** be used to endorse or promote products derived from this software without specific
** prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
** EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
** OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
** SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
** TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
** BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
** CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
** IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
** SUCH DAMAGE.
**
***********************************************************************************/

// Contributors:
// Ajay B Harish, Post-Doc @ SimCenter, UC Berkeley
// Dr. Frank McKenna, CTO of SimCenter, UC Berkeley
// Prof. Sanjay Govindjee, Director of SimCenter, UC Berkeley

#ifndef OPENFOAM_H
#define OPENFOAM_H

//*********************************************************************************
// Include user headers
//*********************************************************************************

#include "dependencies/Eigen/Dense"
#include "dependencies/rapidjson/document.h"
#include "dependencies/rapidjson/prettywriter.h"

//*********************************************************************************
// Include library headers
//*********************************************************************************
#include <QString>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <fstream>
#include <iostream>

class openfoam
{

public:

    // General files
    void runsh(QString finaldirpath);

    // System folder
    void genopenfoam(QString finaldirpath, QString jsonfilepath);
    void fvSchemegen(QDir fvScheme);
    void fvSolutiongen(QDir fvSolution);
    void controldictgen(QDir controldict);
    void decomposepargen(QDir decomposeParDict);
    void blockMeshgen(QDir blockMeshDict);
    void snappyHexMeshgen(QDir snappyHexMeshDict);

    // Constant folder
    void gravity(QDir grav);
    void waveprop(QDir waves);
    void turbulenceprop(QDir turbprop);
    void transportprop(QDir transprop);

    // Zero folder
    void Uboundary(QDir Uboundary);
    void alphaboundary(QDir alphaboundary);
    void Presboundary(QDir presboundary);

};

#endif // OPENFOAM_H

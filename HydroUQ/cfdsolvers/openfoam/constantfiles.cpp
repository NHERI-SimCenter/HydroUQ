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

//*********************************************************************************
// Include user headers
//*********************************************************************************
#include "openfoam.h"

//*********************************************************************************
//Generate files related to OpenFOAM and in constant folder
//*********************************************************************************

//*********************************************************************************
//Generate gravity information for OpenFOAM
//*********************************************************************************
void openfoam::gravity(QDir constdirs)
{
    // Create teh fvSchemes file
    QFile gravity(constdirs.filePath("g"));
    if(!gravity.open(QIODevice::ReadWrite))
    {
        //qDebug() << "File open error";
    }
    else
    {
        // Clear the original file content
        gravity.resize(0);

        // Create a text stream and start writing
        QTextStream stream(&gravity);

        // Add header
        stream << "FoamFile\n";
        stream << "{\tversion\t2.0;\n\tformat\tascii;\n\tclass\tuniformDimensionedVectorField;";
        stream << "\n\tlocation\t\"constant\";\n\tobject\tg;\n}\n\n";

        // Add information
        stream << "dimensions\t[0 1 -2 0 0 0 0 ];\n";
        stream << "value\t(0 0 -9.81);\n";
    }
}

//*********************************************************************************
//Generate turbulence properties for OpenFOAM
//*********************************************************************************
void openfoam::turbulenceprop(QDir constdirs)
{
    // Create teh fvSchemes file
    QFile turbprop(constdirs.filePath("turbulenceProperties"));
    if(!turbprop.open(QIODevice::ReadWrite))
    {
        //qDebug() << "File open error";
    }
    else
    {
        // Clear the original file content
        turbprop.resize(0);

        // Create a text stream and start writing
        QTextStream stream(&turbprop);

        // Add header
        stream << "FoamFile\n";
        stream << "{\tversion\t2.0;\n\tformat\tascii;\n\tclass\tdictionary;";
        stream << "\n\tlocation\t\"constant\";\n\tobject\tturbulenceProperties;\n}\n\n";

        // Add information
        stream << "simulationType\tRAS;\n\n";
        stream << "RAS\n{\n\t";
        stream << "RASModel\tkOmegaSST;\n\t";
        stream << "turbulence\ton;\n\t";
        stream << "printCoeffs\ton;\n}\n";
    }
}

//*********************************************************************************
//Generate transport properties for OpenFOAM
//*********************************************************************************
void openfoam::transportprop(QDir constdirs)
{
    // Create teh fvSchemes file
    QFile transportprop(constdirs.filePath("transportProperties"));
    if(!transportprop.open(QIODevice::ReadWrite))
    {
        //qDebug() << "File open error";
    }
    else
    {
        // Clear the original file content
        transportprop.resize(0);

        // Create a text stream and start writing
        QTextStream stream(&transportprop);

        // Add header
        stream << "FoamFile\n";
        stream << "{\tversion\t2.0;\n\tformat\tascii;\n\tclass\tdictionary;";
        stream << "\n\tlocation\t\"constant\";\n\tobject\ttransportProperties;\n}\n\n";

        // Add information
        stream << "phases (water air);\n\n";

        // Add information about water
        stream << "water\n{\n\t";
        stream << "transportModel\tNewtonian;\n\t";
        stream << "nu\tnu [0 2 -1 0 0 0 0 ] 1e-6;\n\t";
        stream << "rho\trho [1 -3 0 0 0 0 0 ] 1000;\n}\n\n";

        // Add information about air
        stream << "air\n{\n\t";
        stream << "transportModel\tNewtonian;\n\t";
        stream << "nu\tnu [0 2 -1 0 0 0 0 ] 1.48e-5;\n\t";
        stream << "rho\trho [1 -3 0 0 0 0 0 ] 1;\n}\n\n";

        // Surface tension
        stream << "sigma\t\tsigma [1 0 -2 0 0 0 0 ] 0.07;\n";
    }
}

//*********************************************************************************
//Generate wave properties for OpenFOAM
//*********************************************************************************
void openfoam::waveprop(QDir constdirs)
{
    // Create teh fvSchemes file
    QFile waves(constdirs.filePath("g"));
    if(!waves.open(QIODevice::ReadWrite))
    {
        //qDebug() << "File open error";
    }
    else
    {
        // Clear the original file content
        waves.resize(0);

        // Create a text stream and start writing
        QTextStream stream(&waves);

        // Add header
        stream << "FoamFile\n";
        stream << "{\tversion\t2.0;\n\tformat\tascii;\n\tclass\tdictionary;";
        stream << "\n\tlocation\t\"constant\";\n\tobject\twaveProperties;\n}\n\n";

        // Add information
        stream << "origin\t(0 0 0);\n";
        stream << "direction\t(1 0 0);\n";
        stream << "waves\n(\n\t";
        stream << "Airy\n\t{\n\t\t";
        stream << "length\t0.5;\n\t\t";
        stream << "amplitude\t0.25;\n\t\t";
        stream << "phase\t0;\n\t\t";
        stream << "angle\t0;\n\t}\n);\n\n";
        stream << "UMean\t(2 0 0);\n";
    }
}

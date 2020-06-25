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
//Generate files related to OpenFOAM and in zero folder
//*********************************************************************************

//*********************************************************************************
//Generate velocity boundary condition for OpenFOAM
//*********************************************************************************
void openfoam::Uboundary(QDir zerodirs)
{
    // Create teh fvSchemes file
    QFile uboundary(zerodirs.filePath("U"));
    if(!uboundary.open(QIODevice::ReadWrite))
    {
        //qDebug() << "File open error";
    }
    else
    {
        // Clear the original file content
        uboundary.resize(0);

        // Create a text stream and start writing
        QTextStream stream(&uboundary);

        // Add header
        stream << "FoamFile\n";
        stream << "{\tversion\t2.0;\n\tformat\tascii;\n\tclass\tvolVectorField;";
        stream << "\n\tlocation\t\"0\";\n\tobject\tU;\n}\n\n";

        // Add information
        stream << "dimensions\t[0 1 -1 0 0 0 0 ];\n\n";
        stream << "boundaryField\n{\n\t";
        stream << "#includeEtc \"caseDicts/setConstraintTypes\"\n\n\t";

        // Entry
        stream << "Entry\n\t{\n\t\ttype\twaveVelocity;\n\t}\n\n\t";

        // Exit
        stream << "Exit\n\t{\n\t\t";
        stream << "type\toutletPhaseMeanVelocity;\n\t\t";
        stream << "UnMean\t2;\n\t\t";
        stream << "alpha\talpha.water;";
        stream << "\n\t}\n\n";

        // Side01
        stream << "Side01\n\t{\n\t\t";
        stream << "type\tempty;";
        stream << "\n\t}\n\n";

        // Side02
        stream << "Side02\n\t{\n\t\t";
        stream << "type\tempty;";
        stream << "\n\t}\n\n";

        // Bottom
        stream << "Bottom\n\t{\n\t\t";
        stream << "type\tnoSlip;";
        stream << "\n\t}\n\n";

        //Top
        stream << "Top\n\t{\n\t\t";
        stream << "type\tpressureInletOutletVelocity;\n\t\t";
        stream << "value\tuniform (0.6 0 0);";
        stream << "\n\t}\n\n";

        // Buildings
        stream << "Buildings\n\t{\n\t\t";
        stream << "type\tempty;";
        stream << "\n\t}\n\n";

    }
}

//*********************************************************************************
//Generate alpha boundary condition for OpenFOAM
//*********************************************************************************
void openfoam::alphaboundary(QDir zerodirs)
{
    // Create teh fvSchemes file
    QFile alphaboundary(zerodirs.filePath("alpha"));
    if(!alphaboundary.open(QIODevice::ReadWrite))
    {
        //qDebug() << "File open error";
    }
    else
    {
        // Clear the original file content
        alphaboundary.resize(0);

        // Create a text stream and start writing
        QTextStream stream(&alphaboundary);

        // Add header
        stream << "FoamFile\n";
        stream << "{\tversion\t2.0;\n\tformat\tascii;\n\tclass\tvolScalarField;";
        stream << "\n\tlocation\t\"0\";\n\tobject\talpha;\n}\n\n";

        // Add information
        stream << "dimensions\t[0 0 0 0 0 0 0 ];\n\n";
        stream << "boundaryField\n{\n\t";
        stream << "#includeEtc \"caseDicts/setConstraintTypes\"\n\n\t";

        // Entry
        stream << "Entry\n\t{\n\t\t";
        stream << "type\twaveVelocity;\n\t";
        stream << "U\tU;\n\t";
        stream << "inletOutlet\ttrue;\n\t";
        stream << "\n\t}\n\n\t";

        // Exit
        stream << "Exit\n\t{\n\t\t";
        stream << "type\tzeroGradient;";
        stream << "\n\t}\n\n";

        // Side01
        stream << "Side01\n\t{\n\t\t";
        stream << "type\tzeroGradient;";
        stream << "\n\t}\n\n";

        // Side02
        stream << "Side02\n\t{\n\t\t";
        stream << "type\tzeroGradient;";
        stream << "\n\t}\n\n";

        // Bottom
        stream << "Bottom\n\t{\n\t\t";
        stream << "type\tzeroGradient;";
        stream << "\n\t}\n\n";

        //Top
        stream << "Top\n\t{\n\t\t";
        stream << "type\tinletOutlet;\n\t\t";
        stream << "inletValue\tuniform 0;\n\t\t";
        stream << "value\tuniform 0;";
        stream << "\n\t}\n\n";

        // Buildings
        stream << "Buildings\n\t{\n\t\t";
        stream << "type\tzeroGradient;";
        stream << "\n\t}\n\n";

    }
}

//*********************************************************************************
//Generate alpha boundary condition for OpenFOAM
//*********************************************************************************
void openfoam::Presboundary(QDir zerodirs)
{
    // Create teh fvSchemes file
    QFile presboundary(zerodirs.filePath("p_rgh"));
    if(!presboundary.open(QIODevice::ReadWrite))
    {
        //qDebug() << "File open error";
    }
    else
    {
        // Clear the original file content
        presboundary.resize(0);

        // Create a text stream and start writing
        QTextStream stream(&presboundary);

        // Add header
        stream << "FoamFile\n";
        stream << "{\tversion\t2.0;\n\tformat\tascii;\n\tclass\tvolScalarField;";
        stream << "\n\tlocation\t\"0\";\n\tobject\tp_rgh;\n}\n\n";

        // Add information
        stream << "dimensions\t[1 -1 -2 0 0 0 0 ];\n\n";
        stream << "boundaryField\n{\n\t";
        stream << "#includeEtc \"caseDicts/setConstraintTypes\"\n\n\t";

        // Entry
        stream << "Entry\n\t{\n\t\t";
        stream << "type\tfixedFluxPressure;\n\t";
        stream << "value\tuniform 0;";
        stream << "\n\t}\n\n\t";

        // Exit
        stream << "Exit\n\t{\n\t\t";
        stream << "type\tfixedFluxPressure;";
        stream << "\n\t}\n\n";

        // Side01
        stream << "Side01\n\t{\n\t\t";
        stream << "type\tfixedFluxPressure;";
        stream << "\n\t}\n\n";

        // Side02
        stream << "Side02\n\t{\n\t\t";
        stream << "type\tfixedFluxPressure;";
        stream << "\n\t}\n\n";

        // Bottom
        stream << "Bottom\n\t{\n\t\t";
        stream << "type\tfixedFluxPressure;";
        stream << "\n\t}\n\n";

        //Top
        stream << "Top\n\t{\n\t\t";
        stream << "type\ttotalPressure;\n\t\t";
        stream << "p0\tuniform 0;\n\t\t";
        stream << "U\tU;\n\t\t";
        stream << "phi\tphi;\n\t\t";
        stream << "rho\trho;\n\t\t";
        stream << "psi\tnone;\n\t\t";
        stream << "gamma\t1;\n\t\t";
        stream << "value\tuniform 0;";
        stream << "\n\t}\n\n";

        // Buildings
        stream << "Buildings\n\t{\n\t\t";
        stream << "type\tfixedFluxPressure;";
        stream << "\n\t}\n\n";

    }
}

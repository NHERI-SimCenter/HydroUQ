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
//Generate files related to OpenFOAM
//*********************************************************************************

//*********************************************************************************
//Generate fvSchemes file for OpenFOAM
//*********************************************************************************
void openfoam::fvSchemegen(QDir systdirs)
{
    // Create teh fvSchemes file
    QFile fvscheme(systdirs.filePath("fvSchemes"));
    if(!fvscheme.open(QIODevice::ReadWrite))
    {
        //qDebug() << "File open error";
    }
    else
    {
        // Clear the original file content
        fvscheme.resize(0);

        // Create a text stream and start writing
        QTextStream stream(&fvscheme);

        // Add header
        stream << "FoamFile\n";
        stream << "{\tversion\t2.0;\n\tformat\tascii;\n\tclass\tdictionary;";
        stream << "\n\tlocation\t\"system\";\n\tobject\tfvSchemes;\n}\n\n";

        //ddt Schemes
        stream << "ddtSchemes\n";
        stream << "{\n\tdefault\tGauss linear;\n}\n\n";

        // grad Schemes
        stream << "gradSchemes\n";
        stream << "{\n\tdefault\tGauss linear;\n}\n\n";

        // div Schemes
        stream << "divSchemes\n";
        stream << "{\n\tdiv(rhoPhi,U)\tGauss linearUpwind grad(U);\n";
        stream << "\tdiv(phi,alpha)\tGauss vanLeer;\n";
        stream << "\tdiv(phirb,alpha)\tGauss linear;\n";
        stream << "\tdiv(phi,k)\tGauss upwind;\n";
        stream << "\tdiv(phi,omega)\tGauss upwind;\n\n";
        stream << "\tdiv(((rho*nuEff)*dev2(T(grad(U)))))\tGauss linear;\n}\n\n";

        // laplacian Schemes
        stream << "laplacianSchemes\n";
        stream << "{\n\tdefault\tGauss linear corrected;\n}\n\n";

        // interpolation Schemes
        stream << "interpolationSchemes\n";
        stream << "{\n\tdefault\tlinear;\n}\n\n";

        // snGrad Schemes
        stream << "snGradSchemes\n";
        stream << "{\n\tdefault\tcorrected;\n}\n\n";

        // wallDist
        stream << "wallDist\n";
        stream << "{\n\tmethod\tmeshWave;\n}\n\n";

    }
}

//*********************************************************************************
//Generate fvSolution file for OpenFOAM
//*********************************************************************************
void openfoam::fvSolutiongen(QDir systdirs)
{
    // Create teh fvSchemes file
    QFile fvsolution(systdirs.filePath("fvSolution"));
    if(!fvsolution.open(QIODevice::ReadWrite))
    {
        //qDebug() << "File open error";
    }
    else
    {
        // Clear the original file content
        fvsolution.resize(0);

        // Create a text stream and start writing
        QTextStream stream(&fvsolution);

        // Add header
        stream << "FoamFile\n";
        stream << "{\tversion\t2.0;\n\tformat\tascii;\n\tclass\tdictionary;";
        stream << "\n\tlocation\t\"system\";\n\tobject\tfvSolution;\n}\n\n";

        // Add solvers
        stream << "solvers\n{\n";

        // For Alpha
        stream << "\t\"alpha.water.*\"\n\t{\n\t\t";
        stream << "nAlphaCorr\t1;\n\t\t";
        stream << "nAlphaSubCycles\t1;\n\t\t";
        stream << "ncAlpha\t1;\n\t\t";
        stream << "nMULESCorr\tyes;\n\t\t";
        stream << "nnLimiterIter\t3;\n\t\t";
        stream << "solver\tsmoothSolver;\n\t\t";
        stream << "smoother\tsymGaussSeidel;\n\t\t";
        stream << "tolerance\t1e-8;\n\t\t";
        stream << "relTol\t0;\n\t}\n\n";

        // pcorr
        stream << "\tpcorr\n\t{\n\t\t";
        stream << "solver\tPCG;\n\t\t";
        stream << "preconditioner\n\t\t{\n\t\t\t";
        stream << "preconditioner\tGAMG;\n\t\t\t";
        stream << "tolerance\t1e-5;\n\t\t\t";
        stream << "relTol\t0;\n\t\t\t";
        stream << "smoother\tGaussSeidel;\n\t\t\t";
        stream << "nPreSweeps\t0;\n\t\t\t";
        stream << "nPostSweeps\t2;\n\t\t\t";
        stream << "nFinestSweeps\t2;\n\t\t\t";
        stream << "cacheAgglomeration\ttrue;\n\t\t\t";
        stream << "nCellsInCoarsestLevel\t10;\n\t\t\t";
        stream << "agglomerator\tfaceAreaPair;\n\t\t\t";
        stream << "mergeLevels\t1;\n";
        stream << "\t\t}\n\t\t";
        stream << "tolerance\t1e-5;\n\t\t";
        stream << "relTol\t0;\n\t\t";
        stream << "maxIter\t50;\n\t}\n\n";

        // For p_rgh
        stream << "\tp_rgh\n\t{\n\t\t";
        stream << "solver\tGAMG;\n\t\t";
        stream << "tolerance\t5e-9;\n\t\t";
        stream << "relTol\t0.01;\n\t\t";
        stream << "smoother\tsymGaussSeidel;\n\t\t";
        stream << "nPreSweeps\t0;\n\t\t";
        stream << "nPostSweeps\t2;\n\t\t";
        stream << "cacheAgglomeration\ttrue;\n\t\t";
        stream << "nCellsInCoarsestLevel\t10;\n\t\t";
        stream << "agglomerator\tfaceAreaPair;\n\t\t";
        stream << "mergeLevels\t1;\n\t\t";
        stream << "maxIter\t50;\n\t};\n\n";

        // For p_rghFinal
        stream << "\tp_rghFinal\n\t{\n\t\t";
        stream << "$p_rgh;\n\t\t";
        stream << "tolerance\t5e-9;\n\t\t";
        stream << "relTol\t0;\n\t}\n\n";

        // For pcorrFinal
        stream << "\tpcorrFinal\n\t{\n\t\t";
        stream << "$pcorr;\n\t\t";
        stream << "tolerance\t5e-9;\n\t\t";
        stream << "relTol\t0;\n\t}\n\n";

        // For U|k|omega
        stream << "\t\"(U|k|omega).*\"\n\t{\n\t\t";
        stream << "solver\tsmoothSolver;\n\t\t";
        stream << "smoother\tsymGaussSeidel;\n\t\t";
        stream << "nSweeps\t1;\n\t\t";
        stream << "tolerance\t1e-6;\n\t\t";
        stream << "relTol\t0.1;\n\t};\n}\n\n";

        // PIMPLE
        stream << "PIMPLE\n{\n\t";
        stream << "momentumPredictor\tno;\n\t";
        stream << "nCorrectors\t2;\n\t";
        stream << "nNonOrthogonalCorrectors\t0;\n}\n\n";

        // relaxationFactors
        stream << "relaxationFactors\n{\n\t";
        stream << "fields\n\t{\n\t}\n\t";
        stream << "\tequations\n\t{\n\t\t\".*\" 1;\n\t}\n}";

    }
}

//*********************************************************************************
//Generate controlDict file for OpenFOAM
//*********************************************************************************
void openfoam::controldictgen(QDir systdirs)
{
    // Create teh fvSchemes file
    QFile controlDict(systdirs.filePath("controlDict"));
    if(!controlDict.open(QIODevice::ReadWrite))
    {
        //qDebug() << "File open error";
    }
    else
    {
        // Clear the original file content
        controlDict.resize(0);

        // Create a text stream and start writing
        QTextStream stream(&controlDict);

        // Add header
        stream << "FoamFile\n";
        stream << "{\tversion\t2.0;\n\tformat\tascii;\n\tclass\tdictionary;";
        stream << "\n\tlocation\t\"system\";\n\tobject\tcontrolDict;\n}\n\n";

        // Add information
        stream << "application\tinterFoam;\n\n";
        stream << "startFrom\tlatestTime;\n\n";
        stream << "startTime\t0;\n\n";
        stream << "stopAt\tendTime;\n\n";
        stream << "endTime\t20;\n\n";
        stream << "deltaT\t0.000001;\n\n";
        stream << "writeControl\tadjustableRunTime;\n\n";
        stream << "writeInterval\t0.1;\n\n";
        stream << "purgeWrite\t0;\n\n";
        stream << "writeFormat\tascii;\n\n";
        stream << "writePrecision\6t;\n\n";
        stream << "writeCompression\tuncompressed;\n\n";
        stream << "timeFormat\tgeneral;\n\n";
        stream << "timePrecision\t6;\n\n";
        stream << "runTimeModifiable\tyes;\n\n";
        stream << "adjustTimeStep\tyes;\n\n";
        stream << "maxCo\t1.0;\n\n";
        stream << "maxAlphaCo\t1.0;\n\n";
        stream << "maxDeltaT\t1;\n\n";

        stream << "libs\n(\n\t\"libwaves.so\"\n)";
    }

}

//*********************************************************************************
//Generate decomposeParDict file for OpenFOAM
//*********************************************************************************
void openfoam::decomposepargen(QDir systdirs)
{
    // Create teh fvSchemes file
    QFile decomposeParDict(systdirs.filePath("decomposeParDict"));
    if(!decomposeParDict.open(QIODevice::ReadWrite))
    {
        //qDebug() << "File open error";
    }
    else
    {
        // Clear the original file content
        decomposeParDict.resize(0);

        // Create a text stream and start writing
        QTextStream stream(&decomposeParDict);

        // Add header
        stream << "FoamFile\n";
        stream << "{\tversion\t2.0;\n\tformat\tascii;\n\tclass\tdictionary;";
        stream << "\n\tlocation\t\"system\";\n\tobject\tdecomposeParDict;\n}\n\n";

        // Add information
        stream << "numberOfSubdomains\t8;\n\n";
        stream << "method\tsimple;\n\n";

        // Simple
        stream << "simpleCoeffs\n{\n\t";
        stream << "n\t(2 2 2);\n\t";
        stream << "delta\t0.001;\n}\n\n";

        // Hierarchical
        stream << "hierarchicalCoeffs\n{\n\t";
        stream << "n\t(1 1 1);\n\t";
        stream << "delta\t0.001;\n\t";
        stream << "order\txyz;\n}\n\n";

        // Manual
        stream << "manualCoeffs\n{\n\t";
        stream << "dataFile\t\"cellDecomposition\";\n}\n";
    }

}

//*********************************************************************************
//Generate blockMeshDict file for OpenFOAM
//*********************************************************************************
void openfoam::blockMeshgen(QDir systdirs)
{
    // Create teh fvSchemes file
    QFile blockMeshDict(systdirs.filePath("blockMeshDict"));
    if(!blockMeshDict.open(QIODevice::ReadWrite))
    {
        //qDebug() << "File open error";
    }
    else
    {
        // Clear the original file content
        blockMeshDict.resize(0);

        // Create a text stream and start writing
        QTextStream stream(&blockMeshDict);

        // Add header
        stream << "FoamFile\n";
        stream << "{\tversion\t2.0;\n\tformat\tascii;\n\tclass\tdictionary;";
        stream << "\n\tobject\tblockMeshDict;\n}\n\n";

        // Conversion
        stream << "convertToMeters\t1;\n\n";

        // Vertices
        stream << "vertices\n(\n\t";
        stream << "(-10 -10 -10)\n\t";
        stream << "(150 -10 -10)\n\t";
        stream << "(150  10 -10)\n\t";
        stream << "(-10  10 -10)\n\t";
        stream << "(-10 -10  10)\n\t";
        stream << "(150 -10  10)\n\t";
        stream << "(150  10  10)\n\t";
        stream << "(-10  10  10)\n);\n\n";

        // Blocks
        stream << "blocks\n(\n\t";
        stream << "hex (0 1 2 3 4 5 6 7) (50 50 50) simpleGrading (1 1 1)\n);\n\n";

        // Edges
        stream << "edges\n(\n);\n\n";

        // Patches
        stream << "patches\n(\n\t";
        stream << "patch minX\n\t(\n\t\t(0 4 7 3)\n\t)\n";
        stream << "patch maxX\n\t(\n\t\t(2 6 5 1)\n\t)\n";
        stream << "patch minY\n\t(\n\t\t(1 5 4 0)\n\t)\n";
        stream << "patch maxY\n\t(\n\t\t(3 7 6 2)\n\t)\n";
        stream << "patch minZ\n\t(\n\t\t(0 3 2 1)\n\t)\n";
        stream << "patch maxZ\n\t(\n\t\t(4 5 6 7)\n\t)\n);\n\n";

        // Merge
        stream << "mergePatchPairs\n";
        stream << "(\n);\n";
    }
}

//*********************************************************************************
//Generate snappyHexMeshDict file for OpenFOAM
//*********************************************************************************
void openfoam::snappyHexMeshgen(QDir systdirs)
{
    // Create teh fvSchemes file
    QFile snappyHexMeshDict(systdirs.filePath("snappyHexMeshDict"));
    if(!snappyHexMeshDict.open(QIODevice::ReadWrite))
    {
        //qDebug() << "File open error";
    }
    else
    {
        // Clear the original file content
        snappyHexMeshDict.resize(0);

        // Create a text stream and start writing
        QTextStream stream(&snappyHexMeshDict);

        // Add header
        stream << "FoamFile\n";
        stream << "{\tversion\t2.0;\n\tformat\tascii;\n\tclass\tdictionary;";
        stream << "\n\tobject\tsnappyHexMeshDict;\n}\n\n";

        // Steps to run
        stream << "castellatedMesh\t true;";
        stream << "snap\tfalse";
        stream << "addLayers\tfalse;";

        // Geometry & surfaces
        stream << "geometry\n{\n\tbathymetry\n\t{\n\t\t";
        stream << "type\ttriSurfaceMesh;\n\t\t";
        stream << "file\t\"bathymetry.stl\"\n\t}\n};\n\n";

        // Castellated mesh controls
        stream << "castellatedMeshControls\n{\n\t";
        stream << "maxLocalCells\t1000000\n\t";
        stream << "maxGlobalCells\t5000000\n\t";
        stream << "minRefinementCells\t10\n\t";
        stream << "maxLoadUnbalance\t0.1\n\t";
        stream << "nCellsBetweenLegel\t3\n\t";

        // feature edge refinement
        stream << "features\n(\n\t\t{\n\t\t}\n\t);\n\n\t";

        // Surface based refinement
        stream << "refinementSurfaces\n\t{\n}\n\n\t";

        // Resolve sharp edges
        stream << "resolveFeatureAngle\t80;\n\n\t";

        // Refinement regions

        // Mesh selection
        stream << "locationInMesh (0 0 0);\n";

        // End of castellated mesh controls
        stream << "}\n\n";

        // Snap controls
        // Not used here in this work

        // Add layers
        // Not used here in this work

        // Generic mesh quality settings
        stream << "meshQualityControls\n{\n}\n\n";

        // Write flags
        stream << "writeFlags\n(\n\t";
        stream << "scalarLevels\n\tlayerSets\n\tlayerFields\n);\n\n";

        // Merge tolerance
        stream << "mergeTolerance\t1e-6;\n";


    }
}


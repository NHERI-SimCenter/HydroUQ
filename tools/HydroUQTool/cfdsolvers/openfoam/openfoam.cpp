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
// In this routines related to all generation of CFD files for openfoam
//*********************************************************************************

//*********************************************************************************
// Include user headers
//*********************************************************************************
#include "openfoam.h"
#include "server/stampede2/stampede2.h"

//*********************************************************************************
//Generate CFD files
//*********************************************************************************
void openfoam::genopenfoam(QString finaldirpath, QString jsonfilepath)
{

    // Change to get filepath from teh JSON file itself
    // Create openfoam files in defaulty path
    QString constant = QDir(finaldirpath).filePath("constant");
    QDir constdirs(constant);
    if (!constdirs.exists())
        constdirs.mkpath(".");
    QString system = QDir(finaldirpath).filePath("system");
    QDir systdirs(system);
    if (!systdirs.exists())
        systdirs.mkpath(".");
    QString zero = QDir(finaldirpath).filePath("0");
    QDir zerodirs(zero);
    if (!zerodirs.exists())
        zerodirs.mkpath(".");

    // Create fvSchemes file
    fvSchemegen(systdirs);

    // Create fvSolution file
    fvSolutiongen(systdirs);

    // Create gravity information
    gravity(constdirs);

    // Create string stream and open json file
    std::stringstream ss;
    std::ifstream file(jsonfilepath.toStdString());
    if (file)
    {
        ss << file.rdbuf();
        file.close();
    }
    else
    {
        throw std::runtime_error("!! Unable to open json file");
    }

    // Show error if something is wrong with document
    rapidjson::Document doc;
    if (doc.Parse<0>(ss.str().c_str()).HasParseError())
        qDebug() << "JSON parse error";

    // Start parsing JSON strings

    // Get header information
    std::string workdir, rundir, temp;
    std::string toolname = doc["toolName"].GetString();
    std::string version = doc["version"].GetString();
    std::string developer = doc["Developer"].GetString();
    std::string dispname = doc["displayName"].GetString();
    std::string intname = doc["internalName"].GetString();
    if((dispname == "Working directory") && (intname == "workdirUrl"))
        workdir = doc["value"].GetString();
    dispname = doc["displayName"].GetString();
    intname = doc["internalName"].GetString();
    if((dispname == "Run directory") && (intname == "notstored"))
        rundir = doc["value"].GetString();
    dispname = doc["displayName"].GetString();
    intname = doc["internalName"].GetString();
    if((dispname == "Project name") && (intname == "Led_AA_PName"))
        temp = doc["value"].GetString();

    // Create turbulence prop
    // At the start of JSON file
    turbulenceprop(constdirs);

    // Create STL files here
    // QString file01 =

    // Create blockMeshDict
    blockMeshgen(systdirs);

    // Create snappyHexMeshDict
    snappyHexMeshgen(systdirs);

    // Create transport properties
    // To be moved to material properties
    transportprop(constdirs);

    // Create zero-folder items
    // To be moved to initial conditions
    // Velocity
    Uboundary(zerodirs);
    // Pressure
    Presboundary(zerodirs);
    // Alpha
    alphaboundary(zerodirs);
    // Turbulence



    // Create waveProperties
    // To be moved to boundary conditions
    waveprop(constdirs);

    // Create control dict
    // To be moved to solver basic
    controldictgen(systdirs);

    // Create decomposepar
    // To be moved to solver advanced
    decomposepargen(systdirs);

    // Generate run.sh
    // Move to submit to TACC - last place
    stampede2 serverfiles;
    serverfiles.runsh(finaldirpath);



}





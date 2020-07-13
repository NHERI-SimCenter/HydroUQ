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
#include "stampede2.h"

//*********************************************************************************
//Generate server run script
//*********************************************************************************
void stampede2::runsh(QString path)
{
    // Create the run.sh files
    QFile runsh(QDir(path).filePath("run.sh"));
    if(!runsh.open(QIODevice::ReadWrite))
    {
        //qDebug() << "File open error";
    }
    else
    {
        // Clear the original file content
        runsh.resize(0);

        // Create a text stream and start writing
        QTextStream stream(&runsh);

        // Write the information
        stream << "#SBATCH -J TrialJob\n";
        stream << "#SBATCH -o TrialJob.o%j\n";
        stream << "#SBATCH -e TrialJob.e%j\n";
        stream << "#SBATCH -p normal\n";
        stream << "#SBATCH -N 1\n";
        stream << "#SBATCH -n 6\n";
        stream << "#SBATCH -t 48:00:00\n";
        stream << "#SBATCH --mail-user=ajaybh@berkeley.edu\n";
        stream << "#SBATCH --mail-type=all\n";
        stream << "#SBATCH -A DesignSafe-SimCenter\n\n";

        stream << "module load openfoam\n\n";
        stream << "blockMesh > log.blockmesh\n\n";
        stream << "ibrun snappyHexMesh -overwrite -parallel > log.snappy\n\n";
        stream << "setWaves > log.waves\n\n";
        stream << "decomposePar > log.decompose\n\n";
        stream << "ibrun interFOAM -parallel > log.interfoam\n\n";
        stream << "reconstructPar > log.reconstruct\n";

    }
}

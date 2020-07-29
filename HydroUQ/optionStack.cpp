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
// In this routines related to options stacked widget are considered
//*********************************************************************************

//*********************************************************************************
// Include user headers
//*********************************************************************************

#include "mainwindow.h"
#include "ui_mainwindow.h"

//*********************************************************************************
// Routine to control what happens when the page changes
//*********************************************************************************
void MainWindow::on_OptionsStack_currentChanged(int arg1)
{

    if(arg1 == 0) // Project settings
    {
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("Please set the project settings"
                                  " before proceeding ahead.");
    }
    else if(arg1 == 1) // Bathymetry
    {
        // Set the description of the description
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("Here, the bathymetry data related to the "
                                  "simulation is initialized. In this case, upload "
                                  "the shallow water solutions and bathymetry data. You can also choose "
                                  "from the pre-existing library or using a wave flume or a STL File. "
                                  "Bathymetry with maps coming soon.");
        // Show and hide elements based on type of simulation
        BathyHideShow();
    }
    else if(arg1 == 2) // SW-CFD Interface
    {
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("Provide the information of the interface between "
                                  "shallow-water and CFD domain either in the form of "
                                  "a table or as a .csv file. Double click to add interfaces.");
        // Show and hide elements based on type of simulation
        swcfdhideshow();

    }
    else if(arg1 == 3) // Buildings
    {
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("Add buildings in the CFD domain. Buildings are "
                                  "specified by giving the lowermost and the topmost points. "
                                  "At present, the buildings are considered to be of simple cuboid "
                                  "geometry only.");
        // Show and hide elements based on the type of simulation
        buildinghideshow();
    }
    else if(arg1 == 4) // Floating bodies
    {
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("We are working to enable this option to add floating bodies."
                                  " This option is not yet available. Watchout for updates. Exciting days ahead");
    }
    else if(arg1 == 5) // Meshing
    {
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("Setup the mesh either using the in-built meshing tool. "
                                  "For the in-built tool, five degrees are allowed. In addition, "
                                  "regional refinements can be specified to refine particular regions. "
                                  "Alternatively upload the mesh or mesh dictionaries.");
    }
    else if(arg1 == 6) // Bathymetry (from Maps)
    {
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("This option is not yet available. Watchout for updates.");
    }
    else if(arg1 == 7) // Bathymetry (from surrogate models)
    {
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("This option is not yet available. Watchout for updates.");
    }
    else if(arg1 == 8) // Add buildings
    {
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("Add buildings in the CFD domain. Buildings are "
                                  "specified by giving the lowermost and the topmost points. "
                                  "At present, the buildings are considered to be of simple cuboid "
                                  "geometry only.");
    }
    else if(arg1 == 9) // Add floating bodies
    {
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("");
    }
    else if(arg1 == 10) // Mesh settings
    {
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("Setup the mesh either using the in-built meshing tool. "
                                  "For the in-built tool, five degrees are allowed. In addition, "
                                  "regional refinements can be specified to refine particular regions. "
                                  "Alternatively upload the mesh or mesh dictionaries.");
    }
    else if(arg1 == 11) // Material properties
    {
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("The material properties considered for the simulation are the "
                                  "kinematic viscosity and density of the two fluids. In addition "
                                  "the surface tension between the fluids is considered.");
    }
    else if(arg1 == 12) // Initial conditions
    {
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("Initial conditions of the two fluids in consideration are provided here. "
                                  "They include the velocity, pressure and the phase of the fluids. In addition, "
                                  "specific regions can be added with particular conditions.");

        // Show and hide items depending on the type of simulation
        if((ui->CmB_AA_SimType->currentIndex() == 1) || (ui->CmB_AA_SimType->currentIndex() == 2))
        {
            ui->Lbl_GA_Notice->show();
            ui->Lbl_GA_Vel->hide();
            ui->Led_GA_Vx->hide();
            ui->Led_GA_Vy->hide();
            ui->Led_GA_Vz->hide();

            ui->Lbl_GA_Pressure->hide();
            ui->Led_GA_Pressure->hide();

            ui->Lbl_GA_Alpha->hide();
            ui->Led_GA_Alpha->hide();

            ui->Lbl_GA_Regions->hide();
            ui->Tbl_GA_IniCondTable->hide();
            ui->Btn_GA_AddRegion->hide();
            ui->Btn_GA_RemRegion->hide();
        }
        else
        {
            ui->Lbl_GA_Notice->hide();
            ui->Lbl_GA_Vel->show();
            ui->Led_GA_Vx->show();
            ui->Led_GA_Vy->show();
            ui->Led_GA_Vz->show();

            ui->Lbl_GA_Pressure->show();
            ui->Led_GA_Pressure->show();

            ui->Lbl_GA_Alpha->show();
            ui->Led_GA_Alpha->show();

            ui->Lbl_GA_Regions->show();
            ui->Tbl_GA_IniCondTable->show();
            ui->Btn_GA_AddRegion->show();
            ui->Btn_GA_RemRegion->show();
        }

    }
    else if(arg1 == 13) // BC with SW solutions
    {
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("The initial conditions need not be specified but will be directly extracted "
                                  "using the shallow-water solutions specified.");
    }
    else if(arg1 == 14) // BC for user bathymetry
    {
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("In the case, where a bathymetry file is used for simulation, "
                                  "the boundary conditions can be specified for the four sides. "
                                  "Velocity boundary conditions can be specified as wave inputs, constant"
                                  " or time-varying uniform / non-uniform conditions. Default pressure condition "
                                  "automatically help choose appropriate boundary conditions based on velocity inputs.");
    }
    else if(arg1 == 15) // BC for flume
    {
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("In the case, where the simulation is done on a wave flume, "
                                  "the velocity and pressure boundary conditions can be specified "
                                  "for the exit and entry of the flume. All other boundaries are automatically specified."
                                  "Velocity boundary conditions can be specified as wave inputs, constant"
                                  " or time-varying uniform / non-uniform conditions. Default pressure condition "
                                  "automatically help choose appropriate boundary conditions based on velocity inputs.");
    }
    else if(arg1 == 16) // BC for STL file
    {
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("This option is not yet available. Watchout for updates.");
    }
    else if(arg1 == 17) // BC for Maps
    {
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("This option is not yet available. Watchout for updates.");
    }
    else if(arg1 == 18) // BC for surrogate
    {
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("This option is not yet available. Watchout for updates.");
    }
    else if(arg1 == 19) // Basic solver settings
    {
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("Basic solver settings include start and stop times, time and write increments. "
                                  "If the solver facilitates restarting the simulations, then solution files from "
                                  "the previous time step can be uploaded. At the moment OpenFOAM is the supported "
                                  "solver.");
    }
    else if(arg1 == 20) // Advanced solver settings
    {
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("Advanced solver settings include domain decomposition for parallelization.");
    }
    else if(arg1 == 21) // Submit to TACC
    {
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("TACC settings helps to generate the job scripts required to run the jobs on TACC "
                                  "Stampede2 server. This includes job name, total wall time or computing time, "
                                  "email address to which job statis can be emailed.");
    }
    else if(arg1 == 22) // Post-processing
    {
        ui->Lbl_Descript->setWordWrap(true);
        ui->Lbl_Descript->setText("This option is not yet available. Watchout for updates.");
    }



}

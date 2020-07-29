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
// In this routines related to all generation of JSON and CFD files
//*********************************************************************************

//*********************************************************************************
// Include user headers
//*********************************************************************************
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cfdsolvers/openfoam/openfoam.h"

//*********************************************************************************
//When generate files button is clicked
//*********************************************************************************
void MainWindow::on_Btn_JA_GenFiles_clicked()
{

    // Create JSON files using RAPIDJSON
    genJsonRJ();

    // Create CFD files
    if(ui->Cmb_IA_Solver->currentText() == "OpenFOAM")
    {
        // Get JSON file name
        QString pname = ui->Lbl_ProjTitle->text();
        QString finaldirpath = QDir(workdirUrl.toString()).filePath(pname);
        QUrl finaldirpathUrl(finaldirpath);
        finaldirpath = finaldirpathUrl.toLocalFile();
        QDir fildirs(finaldirpath);
        QString jsonfilepath = fildirs.filePath(pname+".json");

        // Create an object for openfoam
        openfoam ofwrite;
        ofwrite.genopenfoam(finaldirpath,jsonfilepath);
    }

}

//*********************************************************************************
// Generate the JSON file using RapidJson
//*********************************************************************************
void MainWindow::genJsonRJ()
{
    // Get project name
    QString pname = ui->Lbl_ProjTitle->text();

    // Concatenate to get new dir path where files will be written
    QString finaldirpath = QDir(workdirUrl.toString()).filePath(pname);
    QUrl finaldirpathUrl(finaldirpath);
    finaldirpath = finaldirpathUrl.toLocalFile();

    // Create a directory if it does not exist
    // All files to be written to this directory
    QDir fildirs(finaldirpath);
    if (!fildirs.exists())
        fildirs.mkpath(".");

    // Create the JSON file to write to
    QFile jsonfile(fildirs.filePath(pname+".json"));
    if(!jsonfile.open(QIODevice::ReadWrite))
    {
        //qDebug() << "File open error";
    }
    else
    {
        //qDebug() <<"File open!";
    }
    // Clear the original file content
    jsonfile.resize(0);

    // Create teh string buffer
    rapidjson::StringBuffer s;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
    writer.StartObject();

    // Writer header
    writer.Key("toolName");
    writer.String(toolname.c_str());
    writer.Key("version");
    writer.String(version.c_str());
    writer.Key("Developer");
    writer.String("SimCenter, UC Berkeley (USA)");

    // Get project details
    writer.Key("displayName");
    writer.String("Working directory");
    writer.Key("internalName");
    writer.String("workdirUrl");
    writer.Key("value");
    writer.String(workdirUrl.toLocalFile().toStdString().c_str());
    writer.Key("displayName");
    writer.String("Run directory");
    writer.Key("internalName");
    writer.String("notstored");
    writer.Key("value");
    writer.String(finaldirpath.toStdString().c_str());
    writer.Key("displayName");
    writer.String("Project name");
    writer.Key("internalName");
    writer.String("Led_AA_PName");
    writer.Key("value");
    writer.String(ui->Led_AA_PName->text().toStdString().c_str());
    writer.Key("displayName");
    writer.String("Project name");
    writer.Key("internalName");
    writer.String("Led_AA_PDesc");
    writer.Key("value");
    writer.String(ui->Led_AA_PDesc->toPlainText().toStdString().c_str());
    writer.Key("displayName");
    writer.String("Project name");
    writer.Key("internalName");
    writer.String("CmB_AA_SimType");
    writer.Key("value");
    int value = ui->CmB_AA_SimType->currentIndex();
    Eigen::MatrixXi writermap;
    writermap = optionmap.col(value).transpose();
    std::stringstream ss;
    ss << writermap;
    writer.String(ss.str().c_str());

    // Different stages
    writer.Key("stages");
    writer.StartArray();
    writer.StartObject();

    // Loop over all objects to write items
    for (int ind = 0; ind < writermap.size(); ind++)
    {
        // Get the page number
        int pgno = writermap(ind);

        // If condition to check for each page
        if (pgno == 0) // Project data
        {
            writer.Key("displayName");
            writer.String("Project Settings");
            writer.Key("internalName");
            writer.String("AA_ProjSettings");
            writer.Key("vars");
            writer.StartArray();
            writer.StartObject();
                writer.Key("displayName");
                writer.String("Turbulence model");
                writer.Key("internalName");
                writer.String("CmB_AA_TurbModel");
                writer.Key("value");
                writer.String(ui->CmB_AA_TurbModel->currentText().toStdString().c_str());
            writer.EndObject();
            writer.EndArray();
        }
        else if(pgno == 1) // Bathymetry (with SW solutions)
        {
            writer.Key("displayName");
            writer.String("Bathymetry settings");
            writer.Key("internalName");
            writer.String("BA_Bathy01_Usual");
            writer.Key("vars");
            writer.StartArray();
            writer.StartObject();
                writer.Key("displayname");
                writer.String("Bathymetry files");
                writer.Key("internalName");
                writer.String("bathfilenames");
                writer.Key("value");
                writer.StartArray();
                for(int ii=0; ii<bathfilenames.size(); ++ii)
                {
                    writer.String(bathfilenames.at(ii).toStdString().c_str());
                }
                writer.EndArray();
                writer.Key("displayname");
                writer.String("Bathymetry file type");
                writer.Key("internalName");
                writer.String("CmB_BA_FileType");
                writer.Key("value");
                writer.String(ui->CmB_BA_FileType->currentText().toStdString().c_str());
                writer.Key("displayname");
                writer.String("SW solution files");
                writer.Key("internalName");
                writer.String("solfilenames");
                writer.Key("value");
                writer.StartArray();
                for(int ii=0; ii<solfilenames.size(); ++ii)
                {
                    writer.String(solfilenames.at(ii).toStdString().c_str());
                }
                writer.EndArray();
                writer.Key("displayname");
                writer.String("SW solution format");
                writer.Key("internalName");
                writer.String("CmB_BA_SolFormat");
                writer.Key("value");
                writer.String(ui->CmB_BA_SolFormat->currentText().toStdString().c_str());
                writer.Key("displayname");
                writer.String("SW-CFD interface type");
                writer.Key("internalName");
                writer.String("ChB_BA_UploadBox");
                writer.Key("value");
            writer.EndObject();
            writer.EndArray();
        }
        else if(pgno == 2) // Bathymetry selected from library
        {
            writer.Key("displayName");
            writer.String("Bathymetry settings");
            writer.Key("internalName");
            writer.String("BB_Bathy02_Library");
            writer.Key("vars");
            writer.StartArray();
            writer.StartObject();
                writer.Key("displayname");
                writer.String("SW Library");
                writer.Key("internalName");
                writer.String("CmB_BB_Library");
                writer.Key("value");
                writer.String(ui->CmB_BA_Library->currentText().toStdString().c_str());
                writer.Key("displayname");
                writer.String("SW-CFD interface type");
                writer.Key("internalName");
                writer.String("ChB_BB_UploadFile");
                writer.Key("value");
                if(ui->ChB_CA_UploadFile->isChecked())
                {
                    writer.String("Checked");
                    writer.Key("displayname");
                    writer.String("SW-CFD interface");
                    writer.Key("internalName");
                    writer.String("intefilenames");
                    writer.Key("value");
                    writer.StartArray();
                    for(int ii=0; ii<intefilenames.size(); ++ii)
                    {
                        writer.String(intefilenames.at(ii).toStdString().c_str());
                    }
                    writer.EndArray();
                }
                else
                {
                    writer.String("Unchecked");
                    // Entry interface
                    writer.Key("displayname");
                    writer.String("SW-CFD Entry interface");
                    writer.Key("internalName");
                    writer.String("Tbl_BB_EntryIntePt");
                    writer.Key("value");
                    /*writer.StartArray();
                    if(ui->Tbl_BB_EntryIntePt->rowCount() > 0)
                    {
                        QString data = "n," + ui->Led_BB_EntryNx->text() +
                                    "," + ui->Led_BB_EntryNy->text() +
                                    "," + ui->Led_BB_EntryNz->text();
                        writer.String(data.toStdString().c_str());
                        for(int ii=0; ii<ui->Tbl_BB_EntryIntePt->rowCount(); ++ii)
                        {
                            data = QString::number(ii) + 
                                    "," + ui->Tbl_BB_EntryIntePt->item(ii,0)->text() +
                                    "," + ui->Tbl_BB_EntryIntePt->item(ii,1)->text();
                            writer.String(data.toStdString().c_str());
                        }
                    }
                    writer.EndArray();*/
                    // Exit interface
                    writer.Key("displayname");
                    writer.String("SW-CFD Exit interface");
                    writer.Key("internalName");
                    writer.String("Tbl_BB_ExitIntePt");
                    writer.Key("value");
                    /*writer.StartArray();
                    if(ui->Tbl_BB_ExitIntePt->rowCount() > 0)
                    {
                        QString data = "n," + ui->Led_BB_ExitNx->text() +
                                    "," + ui->Led_BB_ExitNy->text() +
                                    "," + ui->Led_BB_ExitNz->text();
                        writer.String(data.toStdString().c_str());
                        for(int ii=0; ii<ui->Tbl_BB_ExitIntePt->rowCount(); ++ii)
                        {
                            data = QString::number(ii) + 
                                    "," + ui->Tbl_BB_ExitIntePt->item(ii,0)->text() +
                                    "," + ui->Tbl_BB_ExitIntePt->item(ii,1)->text();
                            writer.String(data.toStdString().c_str());
                        }
                    }
                    writer.EndArray();*/
                    // Side01 interface
                    writer.Key("displayname");
                    writer.String("SW-CFD Side01 interface");
                    writer.Key("internalName");
                    writer.String("Tbl_BB_S01IntePt");
                    writer.Key("value");
                    /*writer.StartArray();
                    if(ui->Tbl_BB_S01IntePt->rowCount() > 0)
                    {
                        QString data = "n," + ui->Led_BB_S01Nx->text() +
                                    "," + ui->Led_BB_S01Ny->text() +
                                    "," + ui->Led_BB_S01Nz->text();
                        writer.String(data.toStdString().c_str());
                        for(int ii=0; ii<ui->Tbl_BB_S01IntePt->rowCount(); ++ii)
                        {
                            data = QString::number(ii) + 
                                    "," + ui->Tbl_BB_S01IntePt->item(ii,0)->text() +
                                    "," + ui->Tbl_BB_S01IntePt->item(ii,1)->text();
                            writer.String(data.toStdString().c_str());
                        }
                    }
                    writer.EndArray();*/
                    // Side02 interface
                    writer.Key("displayname");
                    writer.String("SW-CFD Side02 interface");
                    writer.Key("internalName");
                    writer.String("Tbl_BB_S02IntePt");
                    writer.Key("value");
                    /*writer.StartArray();
                    if(ui->Tbl_BB_S02IntePt->rowCount() > 0)
                    {
                        QString data = "n," + ui->Led_BB_S02Nx->text() +
                                    "," + ui->Led_BB_S02Ny->text() +
                                    "," + ui->Led_BB_S02Nz->text();
                        writer.String(data.toStdString().c_str());
                        for(int ii=0; ii<ui->Tbl_BB_S02IntePt->rowCount(); ++ii)
                        {
                            data = QString::number(ii) + 
                                    "," + ui->Tbl_BB_S02IntePt->item(ii,0)->text() +
                                    "," + ui->Tbl_BB_S02IntePt->item(ii,1)->text();
                            writer.String(data.toStdString().c_str());
                        }
                    }
                    writer.EndArray();*/
                }
            writer.EndObject();
            writer.EndArray();
        }
        else if(pgno == 3) // User bathymetry
        {
            writer.Key("displayName");
            writer.String("Bathymetry settings");
            writer.Key("internalName");
            writer.String("BC_Bathy03_GenBathy");
            writer.Key("vars");
            writer.StartArray();
            writer.StartObject();
                writer.Key("displayname");
                writer.String("Bathymetry files");
                writer.Key("internalName");
                writer.String("bathfilenames");
                writer.Key("value");
                writer.StartArray();
                    for(int ii=0; ii<bathfilenames.size(); ++ii)
                    {
                        writer.String(bathfilenames.at(ii).toStdString().c_str());
                    }
                writer.EndArray();
            writer.EndObject();
            writer.EndArray();
        }
        else if(pgno == 4) // Wave flume
        {
            writer.Key("displayName");
            writer.String("Bathymetry settings");
            writer.Key("internalName");
            writer.String("BD_Bathy04_WaveFlume");
            writer.Key("vars");
            writer.StartArray();
            writer.StartObject();
                writer.Key("displayname");
                writer.String("Depth of water");
                writer.Key("internalName");
                writer.String("Led_BD_Depth");
                //writer.Key("value");
                //writer.String(ui->Led_BD_Depth->text().toStdString().c_str());
                writer.Key("displayname");
                writer.String("Breadth of wave flume");
                writer.Key("internalName");
                writer.String("Led_BD_Breadth");
                //writer.Key("value");
                //writer.String(ui->Led_BD_Breadth->text().toStdString().c_str());
                writer.Key("displayname");
                writer.String("Segments along flume");
                writer.Key("internalName");
                writer.String("Tbl_BD_Segments");
                writer.Key("value");
                writer.StartArray();
                if(ui->Tbl_BA_Segments->rowCount() > 0)
                {
                    for(int ii=0; ii<ui->Tbl_BA_Segments->rowCount(); ++ii)
                    {
                        QString data = QString::number(ii) + 
                            "," + ui->Tbl_BA_Segments->item(ii,0)->text() +
                            "," + ui->Tbl_BA_Segments->item(ii,1)->text();
                        writer.String(data.toStdString().c_str());
                    }
                }
                writer.EndArray();
            writer.EndObject();
            writer.EndArray();
        }
        else if(pgno == 8) // Buildings
        {
            writer.Key("displayName");
            writer.String("Building settings");
            writer.Key("internalName");
            writer.String("CA_BuildingsAdd");
            writer.Key("vars");
            writer.StartArray();
            /*writer.StartObject();
                if(ui->Tbl_CA_Building->rowCount() > 0)
                {
                    writer.Key("displayname");
                    writer.String("Building table");
                    writer.Key("internalName");
                    writer.String("Tbl_CA_Building");
                    writer.Key("value");
                    writer.StartArray();
                    for(int ii=0; ii<ui->Tbl_CA_Building->rowCount(); ++ii)
                    {
                        QString data = QString::number(ii) + 
                            "," + ui->Tbl_CA_Building->item(ii,0)->text() +
                            "," + ui->Tbl_CA_Building->item(ii,1)->text();
                        writer.String(data.toStdString().c_str());
                    }
                    writer.EndArray();
                }
            writer.EndObject();*/
            writer.EndArray();
        }
        else if(pgno == 10) // Meshing
        {
            writer.Key("displayName");
            writer.String("Mesh settings");
            writer.Key("internalName");
            writer.String("EA_Mesh");
            writer.Key("vars");
            writer.StartArray();
            writer.StartObject();
                writer.Key("displayname");
                writer.String("Meshing method");
                writer.Key("internalName");
                writer.String("Cmb_EAMeshType");
                writer.Key("value");
                writer.String(ui->Cmb_EAMeshType->currentText().toStdString().c_str());
                if(ui->Btn_EA_UploadMesh->isVisible())
                {
                    writer.Key("displayname");
                    writer.String("Mesh files");
                    writer.Key("internalName");
                    writer.String("meshfiles");
                    writer.Key("value");
                    writer.StartArray();
                    for(int ii=0; ii<meshfiles.size(); ++ii)
                    {
                        writer.String(meshfiles.at(ii).toStdString().c_str());
                    }
                    writer.EndArray();
                }
                else
                {
                    writer.Key("displayname");
                    writer.String("Fineness of mesh");
                    writer.Key("internalName");
                    writer.String("HSl_EA_MeshSize");
                    writer.Key("value");
                    writer.String(QString::number(ui->HSl_EA_MeshSize->value()).toStdString().c_str());
                    if(ui->Tbl_EA_Regions->rowCount() > 0)
                    {
                        writer.Key("displayName");
                        writer.String("Region refinements");
                        writer.Key("internalName");
                        writer.String("Tbl_EA_Regions");
                        writer.Key("value");
                        writer.StartArray();
                        for(int ii=0; ii<ui->Tbl_EA_Regions->rowCount(); ++ii)
                        {
                            QString data = QString::number(ii) +
                                    "," + ui->Tbl_EA_Regions->item(ii,0)->text() +
                                    "," + ui->Tbl_EA_Regions->item(ii,1)->text() +
                                    "," + ui->Tbl_EA_Regions->item(ii,2)->text();
                            writer.String(data.toStdString().c_str());
                        }
                        writer.EndArray();
                    }
                }
            writer.EndObject();
            writer.EndArray();
        }
        else if(pgno == 11) // Material properties
        {
            writer.Key("displayName");
            writer.String("Material properties");
            writer.Key("internalName");
            writer.String("FA_Material");
            writer.Key("vars");
            writer.StartArray();
            writer.StartObject();
                writer.Key("displayname");
                writer.String("Kin viscosity of water");
                writer.Key("internalName");
                writer.String("Led_FA_WaterVisc");
                writer.Key("value");
                writer.String(ui->Led_FA_WaterVisc->text().toStdString().c_str());
                writer.Key("displayname");
                writer.String("Density of water");
                writer.Key("internalName");
                writer.String("Led_FA_WaterDen");
                writer.Key("value");
                writer.String(ui->Led_FA_WaterDen->text().toStdString().c_str());
                writer.Key("displayname");
                writer.String("Kin viscosity of air");
                writer.Key("internalName");
                writer.String("Led_FA_AirVisc");
                writer.Key("value");
                writer.String(ui->Led_FA_AirVisc->text().toStdString().c_str());
                writer.Key("displayname");
                writer.String("Density of air");
                writer.Key("internalName");
                writer.String("Led_FA_AirDen");
                writer.Key("value");
                writer.String(ui->Led_FA_AirDen->text().toStdString().c_str());
                writer.Key("displayname");
                writer.String("Surface tension");
                writer.Key("internalName");
                writer.String("Led_FA_SurfTen");
                writer.Key("value");
                writer.String(ui->Led_FA_SurfTen->text().toStdString().c_str());
            writer.EndObject();
            writer.EndArray();
        }
        else if(pgno == 12) // initial conditions
        {
            writer.Key("displayName");
            writer.String("Initial conditions");
            writer.Key("internalName");
            writer.String("GA_Initial");
            writer.Key("vars");
            writer.StartArray();
            writer.StartObject();
                writer.Key("displayname");
                writer.String("Initial velocity");
                writer.Key("internalName");
                writer.String("Led_GA_Vel");
                writer.Key("value");
                QString data = ui->Led_GA_Vx->text() +
                        "," + ui->Led_GA_Vy->text() +
                        "," + ui->Led_GA_Vz->text();
                writer.String(data.toStdString().c_str());
                writer.Key("displayname");
                writer.String("Initial pressure");
                writer.Key("internalName");
                writer.String("Led_GA_Pressure");
                writer.Key("value");
                writer.String(ui->Led_GA_Pressure->text().toStdString().c_str());
                writer.Key("displayname");
                writer.String("Initial alpha");
                writer.Key("internalName");
                writer.String("Led_GA_Alpha");
                writer.Key("value");
                writer.String(ui->Led_GA_Alpha->text().toStdString().c_str());
                if(ui->Tbl_GA_IniCondTable->rowCount() > 0)
                {
                    writer.Key("displayName");
                    writer.String("Region refinements");
                    writer.Key("internalName");
                    writer.String("Tbl_EA_Regions");
                    writer.Key("value");
                    writer.StartArray();
                    for(int ii=0; ii<ui->Tbl_GA_IniCondTable->rowCount(); ++ii)
                    {
                        QString data = QString::number(ii) +
                                "," + ui->Tbl_GA_IniCondTable->item(ii,0)->text() +
                                "," + ui->Tbl_GA_IniCondTable->item(ii,1)->text() +
                                "," + ui->Tbl_GA_IniCondTable->item(ii,2)->text() +
                                "," + ui->Tbl_GA_IniCondTable->item(ii,3)->text();
                        writer.String(data.toStdString().c_str());
                    }
                    writer.EndArray();
                }
            writer.EndObject();
            writer.EndArray();
        }
        else if(pgno == 14) // BC for user bathymetry
        {
            writer.Key("displayName");
            writer.String("Boundary conditions (User bathymetry)");
            writer.Key("internalName");
            writer.String("HB_BoundaryBathy");
            writer.Key("vars");
            writer.StartArray();
            writer.StartObject();
                //North interface
                writer.Key("displayname");
                writer.String("North Boundary");
                writer.Key("internalName");
                writer.String("Pg1_HB_North");
                writer.Key("value");
                writer.StartArray();
                    writer.Key("displayname");
                    writer.String("Velocity");
                    writer.Key("internalName");
                    writer.String("Cmb_HB_NorthVelBC");
                    writer.Key("value");
                    writer.String(ui->Cmb_HB_NorthVelBC->currentText().toStdString().c_str());
                    if(ui->Btn_HB_NorthUploadFile->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Boundary files");
                        writer.Key("internalName");
                        writer.String("boundfiles01");
                        writer.Key("value");
                        writer.StartArray();
                        for(int ii=0; ii<boundfiles01.size(); ++ii)
                        {
                            writer.String(boundfiles01.at(ii).toStdString().c_str());
                        }
                        writer.EndArray();
                    }
                    if(ui->Cmb_HB_NorthWaveType->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Wave type");
                        writer.Key("internalName");
                        writer.String("Cmb_HB_NorthWaveType");
                        writer.Key("value");
                        writer.String(ui->Cmb_HB_NorthWaveType->currentText().toStdString().c_str());
                    }
                    if(ui->Lbl_HB_NorthU->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Velocity");
                        writer.Key("internalName");
                        writer.String("Led_HB_NorthU");
                        writer.Key("value");
                        writer.StartArray();
                            if(ui->Led_HB_NorthUx->isVisible())
                            {
                                writer.String(ui->Led_HB_NorthUx->text().toStdString().c_str());
                            }
                            if(ui->Led_HB_NorthUy->isVisible())
                            {

                                QString data = "," + ui->Led_HB_NorthUy->text();
                                writer.String(data.toStdString().c_str());
                            }
                            if(ui->Led_HB_NorthUz->isVisible())
                            {

                                QString data = "," + ui->Led_HB_NorthUz->text();
                                writer.String(data.toStdString().c_str());
                            }
                        writer.EndArray();
                    }
                    if(ui->Lbl_HB_NorthOrigin->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Origin of wave");
                        writer.Key("internalName");
                        writer.String("Led_HB_NorthOrigin");
                        writer.Key("value");
                        QString data = ui->Led_HB_NorthOriginX->text() +
                                "," + ui->Led_HB_NorthOriginY->text() +
                                "," + ui->Led_HB_NorthOriginZ->text();
                        writer.String(data.toStdString().c_str());
                    }
                    if(ui->Lbl_HB_NorthVec->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Direction of wave");
                        writer.Key("internalName");
                        writer.String("Led_HB_NorthVec");
                        writer.Key("value");
                        QString data = ui->Led_HB_NorthVecX->text() +
                                "," + ui->Led_HB_NorthVecY->text() +
                                "," + ui->Led_HB_NorthVecZ->text();
                        writer.String(data.toStdString().c_str());
                    }
                    if(ui->Lbl_HB_NorthPara->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Wave parameters");
                        writer.Key("internalName");
                        writer.String("Led_HB_NorthPara");
                        writer.Key("value");
                        writer.String(ui->Led_HB_NorthPara->text().toStdString().c_str());
                    }
                    writer.Key("displayname");
                    writer.String("Pressure boundary type");
                    writer.Key("internalName");
                    writer.String("Cmb_HB_NorthPresBC");
                    writer.Key("value");
                    writer.String(ui->Cmb_HB_NorthPresBC->currentText().toStdString().c_str());
                    if(ui->Lbl_HB_NorthPres->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Pressure value");
                        writer.Key("internalName");
                        writer.String("Led_HB_NorthPres");
                        writer.Key("value");
                        writer.String(ui->Led_HB_NorthPres->text().toStdString().c_str());
                    }
                writer.EndArray();

                //South interface
                writer.Key("displayname");
                writer.String("South Boundary");
                writer.Key("internalName");
                writer.String("Pg2_HB_South");
                writer.Key("value");
                writer.StartArray();
                    writer.Key("displayname");
                    writer.String("Velocity");
                    writer.Key("internalName");
                    writer.String("Cmb_HB_SouthVelBC");
                    writer.Key("value");
                    writer.String(ui->Cmb_HB_SouthUBC->currentText().toStdString().c_str());
                    if(ui->Btn_HB_SouthUploadFile->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Boundary files");
                        writer.Key("internalName");
                        writer.String("boundfiles02");
                        writer.Key("value");
                        writer.StartArray();
                        for(int ii=0; ii<boundfiles02.size(); ++ii)
                        {
                            writer.String(boundfiles02.at(ii).toStdString().c_str());
                        }
                        writer.EndArray();
                    }
                    if(ui->Cmb_HB_SouthWaveType->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Wave type");
                        writer.Key("internalName");
                        writer.String("Cmb_HB_SouthWaveType");
                        writer.Key("value");
                        writer.String(ui->Cmb_HB_SouthWaveType->currentText().toStdString().c_str());
                    }
                    if(ui->Lbl_HB_SouthU->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Velocity");
                        writer.Key("internalName");
                        writer.String("Led_HB_SouthU");
                        writer.Key("value");
                        writer.StartArray();
                            if(ui->Led_HB_SouthUx->isVisible())
                            {
                                writer.String(ui->Led_HB_SouthUx->text().toStdString().c_str());
                            }
                            if(ui->Led_HB_SouthUy->isVisible())
                            {

                                QString data = "," + ui->Led_HB_SouthUy->text();
                                writer.String(data.toStdString().c_str());
                            }
                            if(ui->Led_HB_SouthUz->isVisible())
                            {

                                QString data = "," + ui->Led_HB_SouthUz->text();
                                writer.String(data.toStdString().c_str());
                            }
                        writer.EndArray();
                    }
                    if(ui->Lbl_HB_SouthOrigin->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Origin of wave");
                        writer.Key("internalName");
                        writer.String("Led_HB_SouthOrigin");
                        writer.Key("value");
                        QString data = ui->Led_HB_SouthOriginX->text() +
                                "," + ui->Led_HB_SouthOriginY->text() +
                                "," + ui->Led_HB_SouthOriginZ->text();
                        writer.String(data.toStdString().c_str());
                    }
                    if(ui->Lbl_HB_SouthVec->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Direction of wave");
                        writer.Key("internalName");
                        writer.String("Led_HB_SouthVec");
                        writer.Key("value");
                        QString data = ui->Led_HB_SouthVecX->text() +
                                "," + ui->Led_HB_SouthVecY->text() +
                                "," + ui->Led_HB_SouthVecZ->text();
                        writer.String(data.toStdString().c_str());
                    }
                    if(ui->Lbl_HB_SouthPara->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Wave parameters");
                        writer.Key("internalName");
                        writer.String("Led_HB_SouthPara");
                        writer.Key("value");
                        writer.String(ui->Led_HB_SouthPara->text().toStdString().c_str());
                    }
                    writer.Key("displayname");
                    writer.String("Pressure boundary type");
                    writer.Key("internalName");
                    writer.String("Cmb_HB_SouthPresBC");
                    writer.Key("value");
                    writer.String(ui->Cmb_HB_SouthPresBC->currentText().toStdString().c_str());
                    if(ui->Lbl_HB_SouthPres->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Pressure value");
                        writer.Key("internalName");
                        writer.String("Led_HB_SouthPres");
                        writer.Key("value");
                        writer.String(ui->Led_HB_SouthPres->text().toStdString().c_str());
                    }
                writer.EndArray();

                //East interface
                writer.Key("displayname");
                writer.String("East Boundary");
                writer.Key("internalName");
                writer.String("Pg3_HB_East");
                writer.Key("value");
                writer.StartArray();
                    writer.Key("displayname");
                    writer.String("Velocity");
                    writer.Key("internalName");
                    writer.String("Cmb_HB_EastVelBC");
                    writer.Key("value");
                    writer.String(ui->Cmb_HB_EastUBC->currentText().toStdString().c_str());
                    if(ui->Btn_HB_EastUploadFile->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Boundary files");
                        writer.Key("internalName");
                        writer.String("boundfiles03");
                        writer.Key("value");
                        writer.StartArray();
                        for(int ii=0; ii<boundfiles03.size(); ++ii)
                        {
                            writer.String(boundfiles03.at(ii).toStdString().c_str());
                        }
                        writer.EndArray();
                    }
                    if(ui->Cmb_HB_EastWaveType->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Wave type");
                        writer.Key("internalName");
                        writer.String("Cmb_HB_EastWaveType");
                        writer.Key("value");
                        writer.String(ui->Cmb_HB_EastWaveType->currentText().toStdString().c_str());
                    }
                    if(ui->Lbl_HB_EastU->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Velocity");
                        writer.Key("internalName");
                        writer.String("Led_HB_EastU");
                        writer.Key("value");
                        writer.StartArray();
                            if(ui->Led_HB_EastUx->isVisible())
                            {
                                writer.String(ui->Led_HB_EastUx->text().toStdString().c_str());
                            }
                            if(ui->Led_HB_EastUy->isVisible())
                            {

                                QString data = "," + ui->Led_HB_EastUy->text();
                                writer.String(data.toStdString().c_str());
                            }
                            if(ui->Led_HB_EastUz->isVisible())
                            {

                                QString data = "," + ui->Led_HB_EastUz->text();
                                writer.String(data.toStdString().c_str());
                            }
                        writer.EndArray();
                    }
                    if(ui->Lbl_HB_EastOrigin->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Origin of wave");
                        writer.Key("internalName");
                        writer.String("Led_HB_EastOrigin");
                        writer.Key("value");
                        QString data = ui->Led_HB_EastOriginX->text() +
                                "," + ui->Led_HB_EastOriginY->text() +
                                "," + ui->Led_HB_EastOriginZ->text();
                        writer.String(data.toStdString().c_str());
                    }
                    if(ui->Lbl_HB_EastVec->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Direction of wave");
                        writer.Key("internalName");
                        writer.String("Led_HB_EastVec");
                        writer.Key("value");
                        QString data = ui->Led_HB_EastVecX->text() +
                                "," + ui->Led_HB_EastVecY->text() +
                                "," + ui->Led_HB_EastVecZ->text();
                        writer.String(data.toStdString().c_str());
                    }
                    if(ui->Lbl_HB_EastPara->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Wave parameters");
                        writer.Key("internalName");
                        writer.String("Led_HB_EastPara");
                        writer.Key("value");
                        writer.String(ui->Led_HB_EastPara->text().toStdString().c_str());
                    }
                    writer.Key("displayname");
                    writer.String("Pressure boundary type");
                    writer.Key("internalName");
                    writer.String("Cmb_HB_EastPresBC");
                    writer.Key("value");
                    writer.String(ui->Cmb_HB_EastPresBC->currentText().toStdString().c_str());
                    if(ui->Lbl_HB_EastPres->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Pressure value");
                        writer.Key("internalName");
                        writer.String("Led_HB_EastPres");
                        writer.Key("value");
                        writer.String(ui->Led_HB_EastPres->text().toStdString().c_str());
                    }
                writer.EndArray();

                //West interface
                writer.Key("displayname");
                writer.String("West Boundary");
                writer.Key("internalName");
                writer.String("Pg3_HB_West");
                writer.Key("value");
                writer.StartArray();
                    writer.Key("displayname");
                    writer.String("Velocity");
                    writer.Key("internalName");
                    writer.String("Cmb_HB_WestVelBC");
                    writer.Key("value");
                    writer.String(ui->Cmb_HB_WestUBC->currentText().toStdString().c_str());
                    if(ui->Btn_HB_WestUploadFile->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Boundary files");
                        writer.Key("internalName");
                        writer.String("boundfiles04");
                        writer.Key("value");
                        writer.StartArray();
                        for(int ii=0; ii<boundfiles04.size(); ++ii)
                        {
                            writer.String(boundfiles04.at(ii).toStdString().c_str());
                        }
                        writer.EndArray();
                    }
                    if(ui->Cmb_HB_WestWaveType->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Wave type");
                        writer.Key("internalName");
                        writer.String("Cmb_HB_WestWaveType");
                        writer.Key("value");
                        writer.String(ui->Cmb_HB_WestWaveType->currentText().toStdString().c_str());
                    }
                    if(ui->Lbl_HB_WestU->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Velocity");
                        writer.Key("internalName");
                        writer.String("Led_HB_WestU");
                        writer.Key("value");
                        writer.StartArray();
                            if(ui->Led_HB_WestUx->isVisible())
                            {
                                writer.String(ui->Led_HB_WestUx->text().toStdString().c_str());
                            }
                            if(ui->Led_HB_WestUy->isVisible())
                            {

                                QString data = "," + ui->Led_HB_WestUy->text();
                                writer.String(data.toStdString().c_str());
                            }
                            if(ui->Led_HB_WestUz->isVisible())
                            {

                                QString data = "," + ui->Led_HB_WestUz->text();
                                writer.String(data.toStdString().c_str());
                            }
                        writer.EndArray();
                    }
                    if(ui->Lbl_HB_WestOrigin->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Origin of wave");
                        writer.Key("internalName");
                        writer.String("Led_HB_WestOrigin");
                        writer.Key("value");
                        QString data = ui->Led_HB_WestOriginX->text() +
                                "," + ui->Led_HB_WestOriginY->text() +
                                "," + ui->Led_HB_WestOriginZ->text();
                        writer.String(data.toStdString().c_str());
                    }
                    if(ui->Lbl_HB_WestVec->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Direction of wave");
                        writer.Key("internalName");
                        writer.String("Led_HB_WestVec");
                        writer.Key("value");
                        QString data = ui->Led_HB_WestVecX->text() +
                                "," + ui->Led_HB_WestVecY->text() +
                                "," + ui->Led_HB_WestVecZ->text();
                        writer.String(data.toStdString().c_str());
                    }
                    if(ui->Lbl_HB_WestPara->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Wave parameters");
                        writer.Key("internalName");
                        writer.String("Led_HB_WestPara");
                        writer.Key("value");
                        writer.String(ui->Led_HB_WestPara->text().toStdString().c_str());
                    }
                    writer.Key("displayname");
                    writer.String("Pressure boundary type");
                    writer.Key("internalName");
                    writer.String("Cmb_HB_WestPresBC");
                    writer.Key("value");
                    writer.String(ui->Cmb_HB_WestPresBC->currentText().toStdString().c_str());
                    if(ui->Lbl_HB_WestPres->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Pressure value");
                        writer.Key("internalName");
                        writer.String("Led_HB_WestPres");
                        writer.Key("value");
                        writer.String(ui->Led_HB_WestPres->text().toStdString().c_str());
                    }
                writer.EndArray();

            writer.EndObject();
            writer.EndArray();
        }
        else if(pgno == 15) // BC for wave flume
        {
            writer.Key("displayName");
            writer.String("Boundary conditions (Wave Flume)");
            writer.Key("internalName");
            writer.String("HCBoundaryFlume");
            writer.Key("vars");
            writer.StartArray();
            writer.StartObject();
                //Entry interface
                writer.Key("displayname");
                writer.String("Entry Boundary");
                writer.Key("internalName");
                writer.String("Pg1_HC_Entry");
                writer.Key("value");
                writer.StartArray();
                    writer.Key("displayname");
                    writer.String("Velocity");
                    writer.Key("internalName");
                    writer.String("Cmb_HC_EntryUBC");
                    writer.Key("value");
                    writer.String(ui->Cmb_HC_EntryUBC->currentText().toStdString().c_str());
                    if(ui->Btn_HC_EntryUploadFile->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Boundary files");
                        writer.Key("internalName");
                        writer.String("boundfiles01");
                        writer.Key("value");
                        writer.StartArray();
                        for(int ii=0; ii<boundfiles01.size(); ++ii)
                        {
                            writer.String(boundfiles01.at(ii).toStdString().c_str());
                        }
                        writer.EndArray();
                    }
                    if(ui->Cmb_HC_EntryWaveType->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Wave type");
                        writer.Key("internalName");
                        writer.String("Cmb_HC_EntryWaveType");
                        writer.Key("value");
                        writer.String(ui->Cmb_HC_EntryWaveType->currentText().toStdString().c_str());
                    }
                    if(ui->Lbl_HC_EntryU->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Velocity");
                        writer.Key("internalName");
                        writer.String("Led_HC_EntryU");
                        writer.Key("value");
                        writer.StartArray();
                            if(ui->Led_HC_EntryUx->isVisible())
                            {
                                writer.String(ui->Led_HC_EntryUx->text().toStdString().c_str());
                            }
                            if(ui->Led_HC_EntryUy->isVisible())
                            {

                                QString data = "," + ui->Led_HC_EntryUy->text();
                                writer.String(data.toStdString().c_str());
                            }
                            if(ui->Led_HC_EntryUz->isVisible())
                            {

                                QString data = "," + ui->Led_HC_EntryUz->text();
                                writer.String(data.toStdString().c_str());
                            }
                        writer.EndArray();
                    }
                    if(ui->Lbl_HC_EntryOrigin->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Origin of wave");
                        writer.Key("internalName");
                        writer.String("Led_HC_EntryOrigin");
                        writer.Key("value");
                        QString data = ui->Led_HC_EntryOriginX->text() +
                                "," + ui->Led_HC_EntryOriginY->text() +
                                "," + ui->Led_HC_EntryOriginZ->text();
                        writer.String(data.toStdString().c_str());
                    }
                    if(ui->Lbl_HC_EntryVec->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Direction of wave");
                        writer.Key("internalName");
                        writer.String("Led_HC_EntryVec");
                        writer.Key("value");
                        QString data = ui->Led_HC_EntryVecX->text() +
                                "," + ui->Led_HC_EntryVecY->text() +
                                "," + ui->Led_HC_EntryVecZ->text();
                        writer.String(data.toStdString().c_str());
                    }
                    if(ui->Lbl_HC_EntryPara->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Wave parameters");
                        writer.Key("internalName");
                        writer.String("Led_HC_EntryPara");
                        writer.Key("value");
                        writer.String(ui->Led_HC_EntryPara->text().toStdString().c_str());
                    }
                    writer.Key("displayname");
                    writer.String("Pressure boundary type");
                    writer.Key("internalName");
                    writer.String("Cmb_HC_EntryPresBC");
                    writer.Key("value");
                    writer.String(ui->Cmb_HC_EntryPresBC->currentText().toStdString().c_str());
                    if(ui->Lbl_HC_EntryPres->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Pressure value");
                        writer.Key("internalName");
                        writer.String("Led_HC_EntryPres");
                        writer.Key("value");
                        writer.String(ui->Led_HC_EntryPres->text().toStdString().c_str());
                    }
                writer.EndArray();
                //Exit interface
                writer.Key("displayname");
                writer.String("Exit Boundary");
                writer.Key("internalName");
                writer.String("Pg2_HC_Exit");
                writer.Key("value");
                writer.StartArray();
                    writer.Key("displayname");
                    writer.String("Velocity");
                    writer.Key("internalName");
                    writer.String("Cmb_HC_ExitUBC");
                    writer.Key("value");
                    writer.String(ui->Cmb_HC_ExitUBC->currentText().toStdString().c_str());
                    if(ui->Btn_HC_ExitUploadFile->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Boundary files");
                        writer.Key("internalName");
                        writer.String("boundfiles02");
                        writer.Key("value");
                        writer.StartArray();
                        for(int ii=0; ii<boundfiles02.size(); ++ii)
                        {
                            writer.String(boundfiles02.at(ii).toStdString().c_str());
                        }
                        writer.EndArray();
                    }
                    if(ui->Cmb_HC_ExitWaveType->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Wave type");
                        writer.Key("internalName");
                        writer.String("Cmb_HC_ExitWaveType");
                        writer.Key("value");
                        writer.String(ui->Cmb_HC_ExitWaveType->currentText().toStdString().c_str());
                    }
                    if(ui->Lbl_HC_ExitU->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Velocity");
                        writer.Key("internalName");
                        writer.String("Led_HC_ExitU");
                        writer.Key("value");
                        writer.StartArray();
                            if(ui->Led_HC_ExitUx->isVisible())
                            {
                                writer.String(ui->Led_HC_ExitUx->text().toStdString().c_str());
                            }
                            if(ui->Led_HC_ExitUy->isVisible())
                            {

                                QString data = "," + ui->Led_HC_ExitUy->text();
                                writer.String(data.toStdString().c_str());
                            }
                            if(ui->Led_HC_ExitUz->isVisible())
                            {

                                QString data = "," + ui->Led_HC_ExitUz->text();
                                writer.String(data.toStdString().c_str());
                            }
                        writer.EndArray();
                    }
                    if(ui->Lbl_HC_ExitOrigin->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Origin of wave");
                        writer.Key("internalName");
                        writer.String("Led_HC_ExitOrigin");
                        writer.Key("value");
                        QString data = ui->Led_HC_ExitOriginX->text() +
                                "," + ui->Led_HC_ExitOriginY->text() +
                                "," + ui->Led_HC_ExitOriginZ->text();
                        writer.String(data.toStdString().c_str());
                    }
                    if(ui->Lbl_HC_ExitVec->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Direction of wave");
                        writer.Key("internalName");
                        writer.String("Led_HC_ExitVec");
                        writer.Key("value");
                        QString data = ui->Led_HC_ExitVecX->text() +
                                "," + ui->Led_HC_ExitVecY->text() +
                                "," + ui->Led_HC_ExitVecZ->text();
                        writer.String(data.toStdString().c_str());
                    }
                    if(ui->Lbl_HC_ExitPara->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Wave parameters");
                        writer.Key("internalName");
                        writer.String("Led_HC_ExitPara");
                        writer.Key("value");
                        writer.String(ui->Led_HC_ExitPara->text().toStdString().c_str());
                    }
                    writer.Key("displayname");
                    writer.String("Pressure boundary type");
                    writer.Key("internalName");
                    writer.String("Cmb_HC_ExitPresBC");
                    writer.Key("value");
                    writer.String(ui->Cmb_HC_ExitPresBC->currentText().toStdString().c_str());
                    if(ui->Lbl_HC_ExitPres->isVisible())
                    {
                        writer.Key("displayname");
                        writer.String("Pressure value");
                        writer.Key("internalName");
                        writer.String("Led_HC_ExitPres");
                        writer.Key("value");
                        writer.String(ui->Led_HC_ExitPres->text().toStdString().c_str());
                    }
                writer.EndArray();

            writer.EndObject();
            writer.EndArray();
        }
        else if(pgno == 19) // Basic solver settings
        {
            writer.Key("displayName");
            writer.String("Solver settings (Basic)");
            writer.Key("internalName");
            writer.String("IA_SolverBasic");
            writer.Key("vars");
            writer.StartArray();
            writer.StartObject();
                writer.Key("displayname");
                writer.String("Start time");
                writer.Key("internalName");
                writer.String("Led_IA_Start");
                writer.Key("value");
                writer.String(ui->Led_IA_Start->text().toStdString().c_str());
                writer.Key("displayname");
                writer.String("End time");
                writer.Key("internalName");
                writer.String("Led_IA_End");
                writer.Key("value");
                writer.String(ui->Led_IA_End->text().toStdString().c_str());
                writer.Key("displayname");
                writer.String("Time interval");
                writer.Key("internalName");
                writer.String("Led_IA_DeltaT");
                writer.Key("value");
                writer.String(ui->Led_IA_DeltaT->text().toStdString().c_str());
                writer.Key("displayname");
                writer.String("Write interval");
                writer.Key("internalName");
                writer.String("Led_IA_WriteT");
                writer.Key("value");
                writer.String(ui->Led_IA_WriteT->text().toStdString().c_str());
                if(ui->ChB_IA_Restart->isChecked())
                {
                    writer.Key("displayname");
                    writer.String("Restart files");
                    writer.Key("internalName");
                    writer.String("restartfiles");
                    writer.Key("value");
                    writer.StartArray();
                    for(int ii=0; ii<restartfiles.size(); ++ii)
                    {
                        writer.String(restartfiles.at(ii).toStdString().c_str());
                    }
                    writer.EndArray();
                }
                writer.Key("displayname");
                writer.String("CFD solver");
                writer.Key("internalName");
                writer.String("Cmb_IA_Solver");
                writer.Key("value");
                writer.String(ui->Cmb_IA_Solver->currentText().toStdString().c_str());
            writer.EndObject();
            writer.EndArray();
        }
        else if(pgno == 20) // Advanced solver settings
        {
            writer.Key("displayName");
            writer.String("Solver settings (Advanced)");
            writer.Key("internalName");
            writer.String("IB_SolverAdv");
            writer.Key("vars");
            writer.StartArray();
            writer.StartObject();
                writer.Key("displayname");
                writer.String("Decomposition type");
                writer.Key("internalName");
                writer.String("Cmb_IB_Decomp");
                writer.Key("value");
                writer.String(ui->Cmb_IB_Decomp->currentText().toStdString().c_str());
                writer.Key("displayname");
                writer.String("Subdomains");
                writer.Key("internalName");
                writer.String("Led_IB_Subdomains");
                writer.Key("value");
                QString data = ui->Led_IB_SubdomainsX->text() +
                        "," + ui->Led_IB_SubdomainsY->text() +
                        "," + ui->Led_IB_SubdomainsZ->text();
                writer.String(data.toStdString().c_str());
            writer.EndObject();
            writer.EndArray();
        }
        else if(pgno == 21) // Submit to TACC
        {
            writer.Key("displayName");
            writer.String("Submit to TACC");
            writer.Key("internalName");
            writer.String("JA_SubmitTACC");
            writer.Key("vars");
            writer.StartArray();
            writer.StartObject();
                writer.Key("displayname");
                writer.String("Job name");
                writer.Key("internalName");
                writer.String("Led_JA_Jobname");
                writer.Key("value");
                writer.String(ui->Led_JA_Jobname->text().toStdString().c_str());
                writer.Key("displayname");
                writer.String("Server type");
                writer.Key("internalName");
                writer.String("Cmb_JA_ServerType");
                writer.Key("value");
                writer.String(ui->Cmb_JA_ServerType->currentText().toStdString().c_str());
                writer.Key("displayname");
                writer.String("Queue type");
                writer.Key("internalName");
                writer.String("Cmb_JA_QType");
                writer.Key("value");
                writer.String(ui->Cmb_JA_QType->currentText().toStdString().c_str());
                writer.Key("displayname");
                writer.String("Number of cores");
                writer.Key("internalName");
                writer.String("Led_JA_Cores");
                writer.Key("value");
                writer.String(ui->Led_JA_Cores->text().toStdString().c_str());
                writer.Key("displayname");
                writer.String("Wall time");
                writer.Key("internalName");
                writer.String("Led_JA_WallTime");
                writer.Key("value");
                QString data = ui->Led_JA_WallTimeHH->text() +
                        "," + ui->Led_JA_WallTimeMM->text() +
                        "," + ui->Led_JA_WallTimeSS->text();
                writer.String(data.toStdString().c_str());
                writer.Key("displayname");
                writer.String("Email address");
                writer.Key("internalName");
                writer.String("Led_JA_Email");
                writer.Key("value");
                writer.String(ui->Led_JA_Email->text().toStdString().c_str());
            writer.EndObject();
            writer.EndArray();
        }
        // End of all if conditions
    }
    // End of loop over all objects

    // End of different stages
    writer.EndObject();
    writer.EndArray();

    // End object & file
    writer.EndObject();

    // Write to file and close the file
    QTextStream out(&jsonfile);
    out << s.GetString();
    jsonfile.close();
}

//*********************************************************************************
// Generate the CFD files for OpenFOAM
//*********************************************************************************


//*********************************************************************************
// Generate the JSON file using QJson
//*********************************************************************************
void MainWindow::genJsonQT(QJsonDocument doc)
{

    // Get project name
    QString pname = ui->Lbl_ProjTitle->text();

    // Concatenate to get new dir path where files will be written
    QString finaldirpath = QDir(workdirUrl.toString()).filePath(pname);
    QUrl finaldirpathUrl(finaldirpath);
    finaldirpath = finaldirpathUrl.toLocalFile();

    // Create a directory if it does not exist
    // All files to be written to this directory
    QDir fildirs(finaldirpath);
    if (!fildirs.exists())
        fildirs.mkpath(".");

    // Create the JSON file to write to
    QFile jsonfile(fildirs.filePath(pname+".json"));
    if(!jsonfile.open(QIODevice::ReadWrite))
    {
        //qDebug() << "File open error";
    }
    else
    {
        //qDebug() <<"File open!";
    }
    // Clear the original file content
    jsonfile.resize(0);

    // Write json file
    QByteArray data_json = doc.toJson();
    jsonfile.write(data_json);

}

// Trial for QJson
/*
// Create a JSON Document
//QJsonDocument doc;

// Create a JSON Object
QJsonObject obj;

obj["value4"] = "Ajay";
obj["value5"] = "Ashwini";
obj["value6"] = "Harish";

// Add array
QJsonArray plot_array,plot_array2;
auto data1 = QJsonObject(
{
qMakePair(QString("min"), QJsonValue(17)),
qMakePair(QString("max"), QJsonValue(35)),
qMakePair(QString("mean"), QJsonValue(20))
});



//    plot_array.push_back(QJsonValue(data1));

plot_array.append(data1);

auto data2 = QJsonObject(
{
qMakePair(QString("min"), QJsonValue(17)),
qMakePair(QString("max"), QJsonValue(35)),
qMakePair(QString("mean"), QJsonValue(20)),
qMakePair("Wlott", plot_array)
});

plot_array2.append(data2);

obj["Wlotdata"] = plot_array2;


obj["value1"] = "Ajay";
obj["value2"] = "Ashwini";
obj["value3"] = "Harish";

obj["Wlotdata2"] = plot_array;

// INsert array into object
//obj.insert(QString("plottingData"), QJsonValue(plot_array));

QJsonDocument doc(obj);

// Generate the JSON files
genJsonQT(doc);*/

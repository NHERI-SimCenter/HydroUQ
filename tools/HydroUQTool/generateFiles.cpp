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

//*********************************************************************************
//When generate files button is clicked
//*********************************************************************************
void MainWindow::on_Btn_JA_GenFiles_clicked()
{

    // Create JSON files using RAPIDJSON
    genJsonRJ();

    // Create JSON files using QJSON
    //genJsonQT(QJsonDocument doc)

    // Create CFD files
    //genOpenFOAM();

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
                    writer.String("SW solver type");
                    writer.Key("internalName");
                    writer.String("Cmb_BA_Solver");
                    writer.Key("value");
                    writer.String(ui->Cmb_BA_Solver->currentText().toStdString().c_str());
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
                    if(ui->ChB_BA_UploadBox->isChecked()) 
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
                        writer.String("Tbl_BA_EntryIntePt");
                        writer.Key("value");
                        writer.StartArray();
                        if(ui->Tbl_BA_EntryIntePt->rowCount() > 0)
                        {
                            QString data = "n," + ui->Led_BA_EntryNx->text() +
                                    "," + ui->Led_BA_EntryNy->text() +
                                    "," + ui->Led_BA_EntryNz->text();
                            writer.String(data.toStdString().c_str());
                            for(int ii=0; ii<ui->Tbl_BA_EntryIntePt->rowCount(); ++ii)
                            {
                                data = QString::number(ii) + "," + ui->Tbl_BA_EntryIntePt->item(ii,0)->text() +
                                        "," + ui->Tbl_BA_EntryIntePt->item(ii,1)->text() +
                                        "," + ui->Tbl_BA_EntryIntePt->item(ii,2)->text();
                                writer.String(data.toStdString().c_str());
                            }
                        }
                        writer.EndArray();
                        // Exit interface
                        writer.Key("displayname");
                        writer.String("SW-CFD Exit interface");
                        writer.Key("internalName");
                        writer.String("Tbl_BA_ExitIntePt");
                        writer.Key("value");
                        writer.StartArray();
                        if(ui->Tbl_BA_ExitIntePt->rowCount() > 0)
                        {
                            QString data = "n," + ui->Led_BA_ExitNx->text() +
                                    "," + ui->Led_BA_ExitNy->text() +
                                    "," + ui->Led_BA_ExitNz->text();
                            writer.String(data.toStdString().c_str());
                            for(int ii=0; ii<ui->Tbl_BA_ExitIntePt->rowCount(); ++ii)
                            {
                                data = QString::number(ii) + "," + ui->Tbl_BA_ExitIntePt->item(ii,0)->text() +
                                        "," + ui->Tbl_BA_ExitIntePt->item(ii,1)->text() +
                                        "," + ui->Tbl_BA_ExitIntePt->item(ii,2)->text();
                                writer.String(data.toStdString().c_str());
                            }
                        }
                        writer.EndArray();
                        // Side 01 interface
                        writer.Key("displayname");
                        writer.String("SW-CFD Side01 interface");
                        writer.Key("internalName");
                        writer.String("Tbl_BA_S01IntePt");
                        writer.Key("value");
                        writer.StartArray();
                        if(ui->Tbl_BA_S01IntePt->rowCount() > 0)
                        {
                            QString data = "n," + ui->Led_BA_S01Nx->text() +
                                    "," + ui->Led_BA_S01Ny->text() +
                                    "," + ui->Led_BA_S01Nz->text();
                            writer.String(data.toStdString().c_str());
                            for(int ii=0; ii<ui->Tbl_BA_S01IntePt->rowCount(); ++ii)
                            {
                                data = QString::number(ii) + "," + ui->Tbl_BA_S01IntePt->item(ii,0)->text() +
                                        "," + ui->Tbl_BA_S01IntePt->item(ii,1)->text() +
                                        "," + ui->Tbl_BA_S01IntePt->item(ii,2)->text();
                                writer.String(data.toStdString().c_str());
                            }
                        }
                        writer.EndArray();
                        // Side 02 interface
                        writer.Key("displayname");
                        writer.String("SW-CFD Side02 interface");
                        writer.Key("internalName");
                        writer.String("Tbl_BA_S02IntePt");
                        writer.Key("value");
                        writer.StartArray();
                        if(ui->Tbl_BA_S02IntePt->rowCount() > 0)
                        {
                            QString data = "n," + ui->Led_BA_S02Nx->text() +
                                    "," + ui->Led_BA_S02Ny->text() +
                                    "," + ui->Led_BA_S02Nz->text();
                            writer.String(data.toStdString().c_str());
                            for(int ii=0; ii<ui->Tbl_BA_S02IntePt->rowCount(); ++ii)
                            {
                                data = QString::number(ii) + "," + ui->Tbl_BA_S02IntePt->item(ii,0)->text() +
                                        "," + ui->Tbl_BA_S02IntePt->item(ii,1)->text() +
                                        "," + ui->Tbl_BA_S02IntePt->item(ii,2)->text();
                                writer.String(data.toStdString().c_str());
                            }
                        }
                        writer.EndArray();
                    }
                writer.EndObject();
                writer.EndArray();
        }
        else if(pgno == 2)
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
                    writer.String(ui->CmB_BB_Library->currentText().toStdString().c_str());
                    writer.String("SW-CFD interface type");
                    writer.Key("internalName");
                    writer.String("ChB_BA_UploadBox");
                    writer.Key("value");
                    if(ui->ChB_BB_UploadFile->isChecked())
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
                writer.Key("displayname");
                writer.String("Bathymetry file type");
                writer.Key("internalName");
                writer.String("Cmb_BC_BathFileType");
                writer.Key("value");
                writer.String(ui->Cmb_BC_BathFileType->currentText().toStdString().c_str());
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
                writer.Key("value");
                writer.String(ui->Led_BD_Depth->text().toStdString().c_str());
                writer.Key("displayname");
                writer.String("Breadth of wave flume");
                writer.Key("internalName");
                writer.String("Led_BD_Breadth");
                writer.Key("value");
                writer.String(ui->Led_BD_Breadth->text().toStdString().c_str());
                writer.Key("displayname");
                writer.String("Segments along flume");
                writer.Key("internalName");
                writer.String("Tbl_BD_Segments");
                writer.Key("value");
                writer.StartArray();
                if(ui->Tbl_BD_Segments->rowCount() > 0)
                {
                    for(int ii=0; ii<ui->Tbl_BD_Segments->rowCount(); ++ii)
                    {
                        QString data = QString::number(ii) + "," + ui->Tbl_BD_Segments->item(ii,0)->text() +
                            "," + ui->Tbl_BD_Segments->item(ii,1)->text();
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
            writer.StartObject();
                writer.Key("displayname");
                writer.String("Building table");
                writer.Key("internalName");
                writer.String("Tbl_CA_Building");
                writer.Key("value");
                writer.StartArray();
                if(ui->Tbl_CA_Building->rowCount() > 0)
                {
                    for(int ii=0; ii<ui->Tbl_CA_Building->rowCount(); ++ii)
                    {
                        QString data = QString::number(ii) + "," + ui->Tbl_CA_Building->item(ii,0)->text() +
                            "," + ui->Tbl_CA_Building->item(ii,1)->text();
                        writer.String(data.toStdString().c_str());
                    }
                }
                writer.EndArray();
            writer.EndObject();
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
                    writer.String("bathfilenames");
                    writer.Key("value");
                    writer.StartArray();
                    for(int ii=0; ii<meshfiles.size(); ++ii)
                    {
                        writer.String(bathfilenames.at(ii).toStdString().c_str());
                    }
                    writer.EndArray();
                }
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

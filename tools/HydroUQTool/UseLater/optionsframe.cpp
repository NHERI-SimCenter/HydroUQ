#include "optionsframe.h"
#include "ui_optionsframe.h"
#include <dependencies/rapidjson/document.h>
#include <dependencies/rapidjson/prettywriter.h>
#include <iostream>
#include <string>
//#include <fstream>
//#include <sstream>
#include <sys/stat.h>

#include <QDebug>
#include <QFile>
#include <QJsonObject> // For QJsonObject


OptionsFrame::OptionsFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::OptionsFrame)
{
    ui->setupUi(this);
}

OptionsFrame::~OptionsFrame()
{
    delete ui;
}

void OptionsFrame::Listen()
{
    qDebug() << "Listening";
    ui->OptionsStack->setCurrentIndex(5);
    qDebug() << ui->OptionsStack->currentIndex();
    this->repaint();
}

// Generate files
void OptionsFrame::on_But_GenFiles_clicked()
{
    // Open the Json file in the working directory for reading and writing
    // If the file does not exist, it will be created automatically.
    QFile file("/Users/ajaybh/Desktop/trial.json");
    if(!file.open(QIODevice::ReadWrite))
    {
        qDebug() << "File open error";
    }
    else
    {
        qDebug() <<"File open!";
    }

    // Clear the original file content
    file.resize(0);

    // Add a value using QJsonArray and write to the file
    /*time_t t = time(0);
    struct tm * now = localtime(&t);
    int year = now->tm_year + 1900;
    int month = now->tm_mon + 1;
    int day = now->tm_mday;*/

    QJsonObject Headerjson;
    Headerjson.insert("toolName","Hydro-UQ");


    /*
    std::stringstream ss_date;
    time_t t = time(0);
    struct tm * now = localtime(&t);
    ss_date << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-'
            << now->tm_mday;
    rapidjson::StringBuffer s;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
    writer.StartObject();

    // Writer header
    writer.Key("toolName");
    writer.String("Hydro-UQ");
    writer.Key("version");
    writer.String("0.0.1");
    writer.Key("Developer");
    writer.String("SimCenter, UC Berkeley (USA)");

    // Project settings
    writer.Key("displayName");
    writer.String("Project name");
    writer.Key("internalName");
    writer.String("Led_AA_PName");
    writer.Key("value");
    writer.String("Trial Project 01"); //Change

    writer.Key("displayName");
    writer.String("Project description");
    writer.Key("internalName");
    writer.String("Led_AA_PDesc");
    writer.Key("value");
    writer.String("This is a trial project to test the JSON file writing"); //Change

    writer.Key("displayName");
    writer.String("Simulation type");
    writer.Key("internalName");
    writer.String("CmB_AA_SimType");
    writer.Key("value");
    writer.String("CFD to resolve SW (Using SW results)"); //Change

    writer.Key("displayName");
    writer.String("Turbulence model");
    writer.Key("internalName");
    writer.String("CmB_AA_TurbModel");
    writer.Key("value");
    writer.String("Laminar"); //Change

    // Different stages
    writer.Key("stages");
        writer.StartArray();
        writer.StartObject();

        // Bathymetry data
        writer.Key("displayName");
        writer.String("Bathymetry Settings");
        writer.Key("internalName");
        writer.String("BA_Bathy01_Usual");
        writer.Key("vars");
            writer.StartArray();
            writer.StartObject();

            writer.Key("displayName");
            writer.String("Select bathymetry files");
            writer.Key("internalName");
            writer.String("ChB_BA_UploadBox");
            writer.Key("values");
            writer.StartArray();
                writer.String("/Users/ajay/Desktop/SCfort.q0000");
                writer.String("/Users/ajay/Desktop/SCfort.q0001");
                writer.String("/Users/ajay/Desktop/SCfort.q0002");
                writer.String("/Users/ajay/Desktop/SCfort.t0000");
                writer.String("/Users/ajay/Desktop/SCfort.t0001");
                writer.String("/Users/ajay/Desktop/SCfort.t0002 ");
            writer.EndArray();

            writer.Key("displayName");
            writer.String("Bathymetric data file type");
            writer.Key("internalName");
            writer.String("CmB_BA_FileType");
            writer.Key("choice");
            writer.Key("GeoClaw (Type II)");

            writer.Key("displayName");
            writer.String("Shallow water solver");
            writer.Key("internalName");
            writer.String("CmB_BA_Solver");
            writer.Key("choice");
            writer.Key("GeoClaw");

            writer.Key("displayName");
            writer.String("SW solutions file format");
            writer.Key("internalName");
            writer.String("CmB_BA_SolFormat");
            writer.Key("choice");
            writer.Key("GeoClaw format");

            writer.Key("displayName");
            writer.String("SW-CFD interface definition");
            writer.Key("internalName");
            writer.String("ChB_BA_UploadBox");
            writer.Key("checked");
            writer.String("Yes");

            writer.Key("displayName");
            writer.String("Entry into CFD Domain");
            writer.Key("internalName");
            writer.String("Data_BA_EntryInter");
            writer.Key("values");
            writer.StartArray();
                writer.String("1,1");
                writer.String("2,1");
                writer.String("3,1");
                writer.String("4,1");
            writer.EndArray();

            writer.Key("displayName");
            writer.String("Exit from CFD Domain");
            writer.Key("internalName");
            writer.String("Data_BA_ExitInter");
            writer.Key("values");
            writer.StartArray();
                writer.String("1,4");
                writer.String("2,4");
                writer.String("3,4");
                writer.String("4,4");
            writer.EndArray();


            writer.EndObject();
            writer.EndArray();


            // Begin Building settings
            writer.Key("displayName");
            writer.String("Building Settings");
            writer.Key("internalName");
            writer.String("CA_BuildingsAdd");
            writer.Key("vars");
                writer.StartArray();
                writer.StartObject();
                    writer.Key("displayName");
                    writer.String("Building table");
                    writer.Key("internalName");
                    writer.String("Tbl_CA_BuildTable");
                    writer.Key("values");
                    writer.StartArray();
                        writer.String("1,(1,2,0),(2,3,1)");
                        writer.String("2,(3,2,0),(4,3,1)");
                    writer.EndArray();
                writer.EndObject();
                writer.EndArray();


        // End of different stages
        writer.EndObject();
        writer.EndArray();

    // End of file
    writer.EndObject();
    std::ofstream of("/Users/ajaybh/Desktop/trial.json");
    of << s.GetString();

    */
}

void OptionsFrame::on_But_AA_WDir_clicked()
{
    ui->OptionsStack->setCurrentIndex(6);
}

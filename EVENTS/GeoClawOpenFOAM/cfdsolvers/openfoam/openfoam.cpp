#include "openfoam.h"

//*********************************************************************************
// OpenFOAM class
//*********************************************************************************
void openfoam::genopenfoam(QString wdir,QString pname)
{
    // Concatenate to get new dir path where files will be written
    QString finaldirpath = QDir(wdir).filePath(pname);

    // Get the filename to open the JSON file
    QUrl finaldirpathUrl(finaldirpath);
    QDir fildirs(finaldirpath);
    QFile jsonfile(fildirs.filePath(pname+".json"));
//    if(!jsonfile.open(QIODevice::ReadOnly)){
//        qDebug() << "Failed to open" << jsonfile;
//        exit(1);
//    }

    // Convert to a format to search
    QTextStream file_text(&jsonfile);
    QString json_string;
    json_string = file_text.readAll();
    jsonfile.close();
    QByteArray json_bytes = json_string.toLocal8Bit();
    auto json_doc = QJsonDocument::fromJson(json_bytes);
    QJsonObject json_obj=json_doc.object();
    QVariantMap json_map = json_obj.toVariantMap();

    // Create openfoam directories
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

    // Generate the system folder files
    // fvschemes
    fvSchemegen(systdirs);
    // fvsolution
    fvSolutiongen(systdirs);
    // Controldict
    QStringList data = {json_map["Start time"].toString(),
                       json_map["End time"].toString(),
                       json_map["Time interval"].toString(),
                       json_map["Write interval"].toString()};
    controldictgen(systdirs,data); // Controldict
    data.clear();
    // decomposeparDict
    data << json_map["Decomposition method"].toString();
    QStringList elements = json_map["Domain decomposition"].toString().split(',');
    int nx = elements[0].split(" ")[0].toInt();
    int ny = elements[1].split(" ")[0].toInt();
    int nz = elements[2].split(" ")[0].toInt();
    data << QString::number(nx*ny*nz) << QString::number(nx) << QString::number(ny) << QString::number(nz);
    decomposepargen(systdirs,data);
    data.clear();
    // Toposetdict - Buildings
    data << json_map["Parametric Build"].toString();
    int flag = data[0].split(" ")[0].toInt();
    if(flag == 1) // Parametric definition
    {
        data << json_map["Number of building in X"].toString();
        data << json_map["Number of building in Y"].toString();
        data << json_map["Building distance along X"].toString();
        data << json_map["Building distance along Y"].toString();
        data << json_map["Distance from coast"].toString();
        data << json_map["OffsetX for coast"].toString();
        data << json_map["OffsetY for coast"].toString();
        data << json_map["Building distribution"].toString();
        data << json_map["Building size"].toString();
    }
    else if (flag == 0) // Definition from table
    {
        data << "This option is not yet available";
    }
    toposetdictgen(systdirs,data);
    data.clear();

    // Set fields dictionary file
    int simty = json_map["Simulation type"].toString().split(" ")[0].toInt();
    //qDebug() << "Simulation type is: " << simty;
    if((simty !=1) || (simty != 2))
    {
        data << json_map["Initial alpha global"].toString();
        data << json_map["Initial pressure global"].toString();
        QStringList initvel = json_map["Initial velocity global"].toString().split(',');
        double inivx = initvel[0].split(" ")[0].toDouble();
        double inivy = initvel[1].split(" ")[0].toDouble();
        double inivz = initvel[2].split(" ")[0].toDouble();
        data << QString::number(inivx) << QString::number(inivy) << QString::number(inivz);
        setFieldsDictgen(systdirs,data);
    }

    // setFieldsDict - For those from shallow water solutions

    // Generate constant folder files


    // Generate 0 folder files


}

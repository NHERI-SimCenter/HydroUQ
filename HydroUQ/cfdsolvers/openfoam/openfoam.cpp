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
    if(!jsonfile.open(QIODevice::ReadOnly)){
        qDebug() << "Failed to open" << jsonfile;
        exit(1);
    }

    // Convert to a format to search
    QTextStream file_text(&jsonfile);
    QString json_string;
    json_string = file_text.readAll();
    jsonfile.close();
    QByteArray json_bytes = json_string.toLocal8Bit();
    auto json_doc = QJsonDocument::fromJson(json_bytes);
    QJsonObject json_obj=json_doc.object();
    QVariantMap json_map = json_obj.toVariantMap();

    // Get each item
    //qDebug() << json_map["End time"].toString();

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
    fvSchemegen(systdirs); // fvschemes

    // Generate constant folder files


    // Generate 0 folder files


}

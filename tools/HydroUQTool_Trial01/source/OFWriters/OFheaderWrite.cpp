//*****************************************************************************
// Write the header for openfoam files
//*****************************************************************************

#include "../mainwindow.h"
#include "../OFWriter.h"
#include "ui_mainwindow.h"
#include <vector>
#include <fstream>
#include <QMessageBox>
#include <QFileDialog>
#include <QUrl>

void OFWriters::OFheaderWrite(QString path)
{

    //std::string filepth = path.toStdString();
    //std::fstream file;
    //file.open(filepth,std::fstream::out);
    //file << "Write something";

    // Create a File URL
    QFile fileUrl(path);

    //
    if( fileUrl.open(QIODevice::ReadWrite | QIODevice::Text) )
        {
            QTextStream out(&fileUrl);
            out << "/*--------------------------------*- C++ -*----------------------------------*\\" << endl;
            out << "a" << endl;
        }
}

#include "hydroerror.h"

//*********************************************************************************
// Hydroerror main
//*********************************************************************************
Hydroerror::Hydroerror()
{
    //std::cout >> "Hydroerror entered";
}


//*********************************************************************************
// Display error message
//*********************************************************************************
void Hydroerror::errormessage(QString csMsg, QString csTitle)
{
    //const QString csMsg("LIDAR files not provided!");
    //const QString csTitle("Critical error");
    QMessageBox msgBox;
    msgBox.critical(nullptr, csTitle, csMsg);
}

//*********************************************************************************
// Display warning message
//*********************************************************************************
void Hydroerror::warnerrormessage(QString csMsg)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Warning");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText(csMsg);
    msgBox.exec();
}

//*********************************************************************************
// Display critical error message
//*********************************************************************************
void Hydroerror::criterrormessage(QString csMsg)
{
    const QString csTitle("Critical error");
    QMessageBox msgBox;
    msgBox.critical(nullptr, csTitle, csMsg);
}

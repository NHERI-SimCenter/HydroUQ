#include "geoclaw.h"
#include "H20utilities/h20utilities.h"

//*********************************************************************************
// GeoClaw starts here
//*********************************************************************************
geoclaw::geoclaw(int flag, QStringList data)
{
    // If needed to reach the topo information
    if(flag == 1)
    {
        QString topofilepath = data[0];
        QString destination = data[1];
        readtopo();
    }
    // Get total number of timesteps
    if(flag == 2)
    {
        // data[0] - file path to working directory
        int totaltimesteps = gclawtotaltime(data[0]);
    }
}


//*********************************************************************************
// Read the Geoclaw file
//*********************************************************************************
void geoclaw::readtopo()
{

}

//*********************************************************************************
// Get total timesteps in the Geoclaw file
//*********************************************************************************
int geoclaw::gclawtotaltime(QString filepath)
{
    // Local temporary variables
    int ii = 1;
    int checkt = 0;
    int checkq = 0;

    do {

        // Get filepaths for t-files
        QString tfilename = getfilename(filepath,ii,1);

        // Get filepaths for q-files
        QString qfilename = getfilename(filepath,ii,2);

        // Check for existence of files
        H20Utilities utility;
        checkt = utility.fileexistance(tfilename.toStdString());
        checkq = utility.fileexistance(qfilename.toStdString());

        // If both files exist, use up to that time step
        // Else produce an error accordingly
        if ((checkt == 0) && (checkq == 0)) ii = ii + 1;
        else ii = ii - 1;

    } while((checkt == 0) && (checkq == 0));

    // Return the flag
    int totaltimesteps =ii;
    return totaltimesteps;

}

//*********************************************************************************
// Get filename of the GeoClaw file
//*********************************************************************************
QString geoclaw::getfilename(QString path, int timestep, int flag)
{
    QString fullpath;

    if(flag == 1) //For t-files
    {
        if((timestep >= 0) && (timestep < 10)) fullpath = path + "/fort.t000" + QString::number(timestep);
        else if((timestep > 9) && (timestep < 100)) fullpath = path + "/fort.t00" + QString::number(timestep);
        else if((timestep > 99) && (timestep < 1000)) fullpath = path + "/fort.t0" + QString::number(timestep);
        else if((timestep > 999) && (timestep < 10000)) fullpath = path + "/fort.t" + QString::number(timestep);

    }
    else if(flag == 2)
    {
        if((timestep >= 0) && (timestep < 10)) fullpath = path + "/fort.q000" + QString::number(timestep);
        else if((timestep > 9) && (timestep < 100)) fullpath = path + "/fort.q00" + QString::number(timestep);
        else if((timestep > 99) && (timestep < 1000)) fullpath = path + "/fort.q0" + QString::number(timestep);
        else if((timestep > 999) && (timestep < 10000)) fullpath = path + "/fort.q" + QString::number(timestep);
    }

    return fullpath;
}

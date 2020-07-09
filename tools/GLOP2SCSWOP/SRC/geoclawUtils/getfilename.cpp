// Include the header files
#include <iostream>

// Include the namespaces
using namespace std;

// Routine to get filenames for GeoClaw outputs
string getfilename(string path, int timestep, int flag)
{

    string fullpath;

    if(flag == 1) //For t-files
    {
        if((timestep >= 0) && (timestep < 10)) fullpath = path + "/fort.t000" + to_string(timestep);
        else if((timestep > 9) && (timestep < 100)) fullpath = path + "/fort.t00" + to_string(timestep);
        else if((timestep > 99) && (timestep < 1000)) fullpath = path + "/fort.t0" + to_string(timestep);
        else if((timestep > 999) && (timestep < 10000)) fullpath = path + "/fort.t" + to_string(timestep);

    }
    else if(flag == 2)
    {
        if((timestep >= 0) && (timestep < 10)) fullpath = path + "/fort.q000" + to_string(timestep);
        else if((timestep > 9) && (timestep < 100)) fullpath = path + "/fort.q00" + to_string(timestep);
        else if((timestep > 99) && (timestep < 1000)) fullpath = path + "/fort.q0" + to_string(timestep);
        else if((timestep > 999) && (timestep < 10000)) fullpath = path + "/fort.q" + to_string(timestep);
    }

    return fullpath;

}
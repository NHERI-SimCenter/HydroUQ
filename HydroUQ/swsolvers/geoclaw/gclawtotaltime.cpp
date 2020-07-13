// Include the header files
#include "../include/genutilities.h"
#include "../include/geoclaw.h"
#include <fstream>
#include <iostream>
#include <sys/stat.h>

// Include the namespaces
using namespace std;

// Routine to check if the time-0 exists
int gclawtotaltime(string opfilespath)
{

    int ii = 1;
    int checkt = 0;
    int checkq = 0;
    //string tfortname,qfortname;
    do {        
        
        // Get filepaths for t-files
        string tfilename = getfilename(opfilespath,ii,1);

        // Get filepaths for q-files
        string qfilename = getfilename(opfilespath,ii,2);

        // Check for existence of files
        checkt = fileexistance(tfilename);
        checkq = fileexistance(qfilename);

        // If both files exist, use up to that time step
        // Else produce an error accordingly
        if ((checkt == 0) && (checkq == 0)) ii = ii + 1;
        else
        {
            ii = ii - 1;
            if( (checkt != 0) && (checkq != 0) ) gclawerrors(5,to_string(ii));
            else if (checkt != 0) gclawerrors(4,tfilename);
            else if (checkq != 0) gclawerrors(4,qfilename);
        }

    } while((checkt == 0) && (checkq == 0));

    // Return the flag
    return ii;
}
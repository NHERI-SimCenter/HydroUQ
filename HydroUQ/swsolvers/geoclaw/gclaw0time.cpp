// Include the header files
#include "../include/genutilities.h"
#include <fstream>
#include <sys/stat.h>

// Include the namespaces
using namespace std;

// Routine to check if the time-0 exists
int gclaw0time(string opfilespath)
{
	
    // Check for the time-0 files
    string tfilename = opfilespath + "/fort.t0000";
    string qfilename = opfilespath + "/fort.q0000";
    int checkt = fileexistance(tfilename); // Check for t-file
    int checkq = fileexistance(qfilename); // Check for q-file

    // Check if files exists. Else give error message
    if ((checkt < 0) && (checkq < 0)) return 1;
    else if (checkt < 0) return 2;
    else if (checkq < 0) return 3;

    // Return the flag
    return 0;
}
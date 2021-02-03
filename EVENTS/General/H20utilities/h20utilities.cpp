#include "h20utilities.h"

//*********************************************************************************
// General utilities created for Hydro-UQ
//*********************************************************************************
H20Utilities::H20Utilities()
{

}

//*********************************************************************************
// Check if a file exists
//*********************************************************************************
int H20Utilities::fileexistance(std::string fullpath)
{
    // Check if the t and q files for time-0 exists
    struct stat buffer;
    int check = stat (fullpath.c_str(), &buffer);

    // Return the flag
    return check;
}

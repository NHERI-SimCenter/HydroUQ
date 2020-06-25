// Include the header files
#include <fstream>
#include <sys/stat.h>

// Include the namespaces
using namespace std;

// Routine to resize 1D arrays
int fileexistance(string fullpath)
{
	
    // Check if the t and q files for time-0 exists
    struct stat buffer;   
    int check = stat (fullpath.c_str(), &buffer);

    // Return the flag
    return check;
}
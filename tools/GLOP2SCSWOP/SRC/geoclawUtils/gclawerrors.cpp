// Include the header files
#include <iostream>

// Include the namespaces
using namespace std;

// Routine to write out errors for GeoClaw
void gclawerrors(int errorcodes, string info)
{
	
    switch (errorcodes)
    {
    case 0:
        cout << "Shallow-water solver outputs written in SimCenter format successfully" << endl;
        break;
    case 1:
        cout << "GeoClaw output files fort.t0000 and fort.q0000 missing" << endl;
        break;
    case 2:
        cout << "GeoClaw output files fort.t0000 missing" << endl;
        break;
    case 3:
        cout << "GeoClaw output files fort.q0000 missing" << endl;
        break;
    case 4:
        cout << "GeoClaw output files " << info << " missing. Hence processing of output files has been stopped here." << endl;
    case 5:
        cout << "GeoClaw output files found up to: fort.t/q - " << info << endl;
    //default:
    //    cout << "Error code not found. Please contact the developer : " << errorcodes << " and " << info << endl;
    }

}



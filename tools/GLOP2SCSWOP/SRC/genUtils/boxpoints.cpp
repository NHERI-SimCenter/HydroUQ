// Include the header files
#include <vector>
#include <iostream>

// Include the namespaces
using namespace std;

// Routine to resize 1D arrays
vector<double> boxpoints(double xlow,double ylow,double dx,double dy,int mx,int my)
{

    cout << mx << "," << my << "," << dx << "," << dy << "," << xlow << "," << ylow << endl;

	// Create the four corner points of the grid
    vector<double> BoxXc;
    BoxXc.resize(8);
    BoxXc[0] = xlow;
    BoxXc[1] = xlow + mx*dx;
    BoxXc[2] = xlow + mx*dx;
    BoxXc[3] = xlow;
    BoxXc[4] = ylow;
    BoxXc[5] = ylow;
    BoxXc[6] = ylow + my*dy;
    BoxXc[7] = ylow + my*dy;

    cout << "Box points are: " << BoxXc[0] << "," << BoxXc[1] << "," << BoxXc[2] << "," << BoxXc[3] << endl;
    cout << "Box points are: " << BoxXc[4] << "," << BoxXc[5] << "," << BoxXc[6] << "," << BoxXc[7] << endl;
    
    // Return the flag
    return BoxXc;
}
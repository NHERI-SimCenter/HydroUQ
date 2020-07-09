// Include the header files
#include <vector>
#include <iostream>

// Include the namespaces
using namespace std;

// Routine to resize 1D arrays
bool boxandline(vector<double> boxpoints,double slope, double cnst)
{
    bool exist = "false";
    double xtemp, ytemp;
    int values[4];
    int sum = 0;

    // Loop over all the 4 points of the box
    for (int ii = 0; ii < 4; ii++)
    {
        xtemp = boxpoints[ii]; //x-coordinate of box point
        ytemp = boxpoints[ii+4];//y-coordinate of box point
        //Check on which side of the line the point is
        if((ytemp - slope*xtemp - cnst) < 0) 
        {
            values[ii] = 0;
        }
        else
        {
            values[ii] = 1;
        }
        sum = sum + values[ii];
    }

    // If all points are not on the same side
    // return there is an intersection
    if((sum > 0) && (sum < 4))
    {
        exist = "true";
        return exist;
    }

    // If there is no intersection, 
    // Return the standard exist as false
    return exist;
    
}
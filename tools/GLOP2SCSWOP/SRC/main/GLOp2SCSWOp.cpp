/*************************************************************/
/*                                                           */
/* GLOp2SCSWOp				                                 */
/*                                                           */
/* Main driver routine for converter of GeoClaw output to    */
/* SimCenter's standard shallow water solver output          */
/*                                                           */
/* Copyright (C) 2020, Ajay Bangalore Harish & SimCenter     */
/*                                                           */
/*************************************************************/

// Declare the standard headers
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <iostream>

// Include the other headers
#include "../include/geoclaw.h"

// Using the namespace
using namespace std;

// Main subroutine
int main(int argc, char* argv[])
{

	// Format is ./exec output-zip-file topo-file
	// Reading inputs: Check if we have enough inputs
	if ( argc != 3 )
    {
        std::cout << "Error in input format." << endl;
        return 1;
	}
	// If the number of inputs are sufficient, then check for program etc.
	else
	{
		// Program used by user
		string userprogram = argv[1];

		// Folder path for results
		string opfilespath = argv[2];

		// Equation of the line
		double slope, cnst;
		int locpoint;
		cout << "Enter the slope (m) of the boundary line (y = mx + c): ";
		cin >> slope;
		cout << "Enter the intercept (c) of the boundary line (y = mx + c): ";
		cin >> cnst;

		// Which side the xlow of the zero-grid in
		// OpenFoam or GeoClaw domain?
		cout << "Where is the point xlower/ylower located? 1 - GeoClaw, 2 - OpenFOAM? ";
		cin >> locpoint;

		// If user used GeoClaw
		// Call the GeoClaw routines
		if(userprogram == "GeoClaw")
		{
			// Create a flag for error codes based on the return value
			int flag = gclawopreader(opfilespath,slope,cnst);
			cout << "Flag is: " << flag << endl;

			// Write our success or failure messages
			gclawerrors(flag,to_string(0));
		}
	}

	// Return
	return 0;

} // End of main routine
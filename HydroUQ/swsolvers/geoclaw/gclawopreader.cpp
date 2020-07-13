// Include the header files
#include "../include/geoclaw.h"
#include "../include/genutilities.h"
#include "../include/Eigen/Sparse"
#include <iostream>
#include <fstream>

// Include the namespaces
using namespace std;

// To readh the GeoClaw o/p files
int gclawopreader(string opfilespath, double slope, double cnst)
{

    // Check if the time-0 files exist
    // Return flag if they do not exist
    int flag = gclaw0time(opfilespath);
    if (flag > 0) return flag;

    // Now that the zero files exist, we will check 
    // how many files / timesteps are available
    // Check for files to get the number of timesteps
    int timesteps = gclawtotaltime(opfilespath);
    //cout << "Number of timesteps:" << timesteps << endl;

    // Declare other variables used below
    int gridnumber, mx, my;
    double xlow, ylow, dx, dy;
    string temp;
    double time;
    int nequations,ngrids;
    vector<double> BoxXc;

    // Loop over each file
    for (int ii = 1; ii < 2; ii++) //timesteps+1
    {
        // Get the filename for the t-file
        string tfilename = getfilename(opfilespath,ii,1);
        ifstream tfstream(tfilename);

        // Read the t-file to get timestep, number of equations and number of grids
        tfstream >> time; //Get the time
        getline(tfstream,temp); // Move to next line
        tfstream >> nequations; // Get number of equations
		getline(tfstream,temp); // Move to next line
		tfstream >> ngrids; // Get number of grids
		getline(tfstream,temp); // Move to next line
        tfstream.close(); // Close the filestream for t-file
        cout << "Data obtained for file: " << tfilename << " are " << time << ", " << nequations << ", " << ngrids << ". " << endl;

        // Get the filename/path of the corresponding q-file 
        string qfilename = getfilename(opfilespath,ii,2);
        ifstream qfstream(qfilename);

        // Create a filestream for the output JSON file for the timestep
        // string opfilename = opfilespath + "/Time" + to_string(ii) + ".json";
        // ofstream jsonfile (opfilename);
        // jsonfile << "[" << endl;

        // Variable to count the number of grids read from the q-file
        //int gridFlag = 0;
        
        // LOOP OVER NUMBER OF GRIDS TO BEGIN HERE
        for(int jj = 1; jj <= ngrids; jj++) //
        {
            // Read the q-file to get gridding information
            qfstream >> gridnumber;
            getline(qfstream,temp);
            getline(qfstream,temp);
            qfstream >> mx;
            getline(qfstream,temp);
            qfstream >> my;
            getline(qfstream,temp);
            qfstream >> xlow;
            getline(qfstream,temp);
            qfstream >> ylow;
            getline(qfstream,temp);
            qfstream >> dx;
            getline(qfstream,temp);
            qfstream >> dy;
            getline(qfstream,temp);
            getline(qfstream,temp); // Blank line

            // Get the corners of the grid
            //vector<double> BoxXc(8, 0.0);
            BoxXc = boxpoints(xlow,ylow,dx,dy,mx,my);

            // Check if there is an intersection between the box and line
            bool exist = boxandline(BoxXc,slope,cnst);

            // If there is no intersection, then
            // Jump mx*my + 1 lines
            if(exist == "false")
            {
                for (int kk = 1; kk < mx*my+1; kk++)
                {
                    getline(qfstream,temp);
                }
            }
            else
            {
                //
            }
            

            
        


        // // Initialize vectors for storing coordinates
        // Xc.resize(mx);
        // Yc.resize(my);

        // // Store x-coordinates of all points for the grid
        // for (int kk = 0; kk < mx; kk++)
        // {
        //     Xc[kk] = xlow + kk*dx;
        // }

        // // Store y-coordinates of all points for the grid
        // for (int kk = 0; kk < my; kk++)
        // {
        //     Yc[kk] = ylow + kk*dy;
        // }

        // // Read the averaged velocities for the gridpoi ts
        // for (int kk = 0; kk < mx; kk++)
        // {
        //     tempx = Xc[kk];
        //     for (int mm = 0; mm < my; mm++)
        //     {
        //         tempy = Yc[mm];
        //         qfstream >> temp1 >> temp2 >> temp3;
        //         cout << "Averaged vel are: " << temp1 << "," << temp2 << "," << temp3 << "." << endl;
        //         jsonfile << "{" << endl;
        //         jsonfile << "\t \"x\": " << tempx << "," << endl;
        //         jsonfile << "\t \"y\": " << tempy << "," << endl;
        //         jsonfile << "\t \"v1\": " << temp1 << "," << endl;
        //         jsonfile << "\t \"v2\": " << temp2 << "," << endl;
        //         jsonfile << "\t \"v3\": " << temp3 << "\n" << "}," << endl;
        //     }
        //     if(ii==0) getline(qfstream,temp); // Blank line
        // }
        //     jsonfile << "Going to next grid" << gridnumber << endl;
        //     gridFlag = gridFlag + 1;
        // }
        // jsonfile << "]" << endl;

        // END THE LOOP OVER ALL GRIDS

        // PRINT OUT ERRORS IF SOME GRIDS WERE MISSING

        // cout << "mx value is: " << mx << endl;
        // cout << "my value is: " << my << endl;
        // cout << "my value is: " << xlow << endl;
        // cout << "my value is: " << ylow << endl;
        // cout << "my value is: " << dx << endl;
        // cout << "my value is: " << dy << endl;
        // cout << "Gridflag is: " << gridFlag << endl;

        }

    }

    // Return default (if all was executed well)
    return 0;
}
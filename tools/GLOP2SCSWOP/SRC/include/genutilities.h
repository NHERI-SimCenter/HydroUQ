#ifndef genutilities_h
#define genutilities_h

#include <string>

using namespace std;

int fileexistance(string fullpath);
vector<double> boxpoints(double xlow,double ylow,double dx,double dy,int mx,int my);
bool boxandline(vector<double> boxpoints,double slope, double cnst);

#endif

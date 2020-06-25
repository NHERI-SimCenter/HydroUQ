#ifndef geoclaw_h
#define geoclaw_h

#include <string>

using namespace std;

int gclawopreader(string opfilespath, double m, double c);
int gclaw0time(string opfilespath);
int gclawtotaltime(string opfilespath);
void gclawerrors(int errorcode, string info);
string getfilename(string path,int timestep,int flag);

#endif

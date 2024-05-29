#!/usr/bin/env python3

import sys
import re

EDPs = ['Disp_1_1', 'RMSA_1_1', 'Force_1_1']

inputArgs = sys.argv

with open ('dispEnvelope.out', 'rt', encoding="utf-8") as inFile:
    numDisp = sum(1 for line in inFile)    
    line = inFile.readline()
    clean_line = line.strip()
    displ = clean_line.split().copy()
    # remove any empty strings
    displ = list(filter(None, displ))
    print('numDisp: ', numDisp)
    print('Displ: ', displ)
    # numNode = len(displ)

inFile.close()

with open ('accelEnvelope.out', 'rt', encoding="utf-8") as inFile:
    numAccel = sum(1 for line in inFile)
    line = inFile.readline()
    clean_line = line.strip()
    accel = clean_line.split().copy()
    print('numAccel: ', numAccel)
    print('Accel: ', accel)
    # numNode = len(accel)

inFile.close()

with open ('forcesEnvelope.out', 'rt', encoding="utf-8") as inFile:
    numForces = sum(1 for line in inFile)
    line = inFile.readline()
    clean_line = line.strip()
    forces = clean_line.split().copy()
    print('numForces: ', numForces)
    print('Forces: ', forces)
    
    # numNode = len(forces)

inFile.close()

numNode = 1
numNode = max(numNode, numDisp)
numNode = max(numNode, numAccel)
numNode = max(numNode, numForces)
print('numNode: ', numNode)

#
# now process the input args and write the results file
#

outFile = open('results.out', 'w', encoding='utf-8')

#
# note for now assuming no ERROR in user data
#

for i in EDPs[0:]:
    print(i)
    theList=i.split('_')
    print('Deliminted EDP: ', theList)

    if (theList[0] == 'Disp' or theList[0] == 'Displacement' or theList[0] == 'Drift' or theList[0] == 'Position'):
        tag = int(theList[1])
        if (tag > 0): # and tag <= numDisp):
            if (theList[2] == '1' or theList[2] == 1 or theList[2] == 'X'):
                val = max(displ, default=0.0)
                print('Max Disp: ', val)
                # val = displ[len(displ)-2]
                # nodeDisp = displ[nodeTag-1] # If transpose
                outFile.write(val)
                outFile.write(' ')
            else:
                outFile.write('0. ')
        else:
            outFile.write('0. ')
            
    elif (theList[0] == 'Accel' or theList[0] == 'Acceleration' or theList[0] == 'RMSA' or theList[0] == 'RMS'):
        tag = int(theList[1])
        if (tag > 0): # and tag <= numAccel):
            if (theList[2] == '1' or theList[2] == 1 or theList[2] == 'X'):
                print('Accel: ', accel)
                val = max(accel, default=0.0)
                print('Max Accel: ', val)
                # val = accel[len(accel)-2]
                # nodeDisp = displ[nodeTag-1] # If transpose
                outFile.write(val)
                outFile.write(' ')
            else:
                outFile.write('0. ')
        else:
            outFile.write('0. ')

    elif (theList[0] == 'Force' or theList[0] == 'Forces' or theList[0] == 'Load'):
        tag = int(theList[1])
        if (tag > 0): # and tag <= numForces):
            if (theList[2] == '1' or theList[2] == 1 or theList[2] == 'X'):
                print('Forces: ', forces)
                val = max(forces, default=0.0)
                print('Max Force: ', val)
                # val = forces[len(forces)-2]
                # nodeDisp = displ[nodeTag-1] # If transpose
                outFile.write(val)
                outFile.write(' ')
            else:
                outFile.write('0. ')
        else:
            outFile.write('0. ')
            
    else:
        outFile.write('0. ')

outFile.close()



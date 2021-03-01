############################################################################
# This python routine forms the backend where all the files are generated
# to run the OpenFOAM / OlaFlow simulation
#############################################################################
import json
import datetime
import os
import shutil
import sys

####################################################################
# To extract an element from a nested JSON object
####################################################################
def extract_element_from_json(obj, path):
    '''
    Extracts an element from a nested dictionary or
    a list of nested dictionaries along a specified path.
    If the input is a dictionary, a list is returned.
    If the input is a list of dictionary, a list of lists is returned.
    obj - list or dict - input dictionary or list of dictionaries
    path - list - list of strings that form the path to the desired element
    '''
    def extract(obj, path, ind, arr):
        '''
            Extracts an element from a nested dictionary
            along a specified path and returns a list.
            obj - dict - input dictionary
            path - list - list of strings that form the JSON path
            ind - int - starting index
            arr - list - output list
        '''
        key = path[ind]
        if ind + 1 < len(path):
            if isinstance(obj, dict):
                if key in obj.keys():
                    extract(obj.get(key), path, ind + 1, arr)
                else:
                    arr.append(None)
            elif isinstance(obj, list):
                if not obj:
                    arr.append(None)
                else:
                    for item in obj:
                        extract(item, path, ind, arr)
            else:
                arr.append(None)
        if ind + 1 == len(path):
            if isinstance(obj, list):
                if not obj:
                    arr.append(None)
                else:
                    for item in obj:
                        arr.append(item.get(key, None))
            elif isinstance(obj, dict):
                arr.append(obj.get(key, None))
            else:
                arr.append(None)
        return arr
    if isinstance(obj, dict):
        return extract(obj, path, 0, [])
    elif isinstance(obj, list):
        outer_arr = []
        for item in obj:
            outer_arr.append(extract(item, path, 0, []))
        return outer_arr

####################################################################
# Create the general header for the Hydro files
####################################################################
def general_header():

  header = """/*--------------------------*- NHERI SimCenter -*----------------------------*\ 
  |       |    |
  |       | Y  | HydroUQ: Water-based Natural Hazards Modeling Application
  |=======| D  | Website: https://simcenter.designsafe-ci.org/research-tools/hydro-uq
  |       | R  | Version: 1.00
  |       | O  |
\*---------------------------------------------------------------------------*/ 
"""

  return header

####################################################################
# Create the header for the openfoam input files
# Inputs: location (of the openfoam dictionary file being written)
#         filename (of the openfoam dictionary file being written)
####################################################################
def openfoam_header(location,filename,OFclass):

  header = """/*--------------------------*- NHERI SimCenter -*----------------------------*\ 
  |       |    |
  |       | Y  | HydroUQ: Water-based Natural Hazards Modeling Application
  |=======| D  | Website: https://simcenter.designsafe-ci.org/research-tools/hydro-uq
  |       | R  | Version: 1.00
  |       | O  |
\*---------------------------------------------------------------------------*/ 
FoamFile
{{
    version   2.0;
    format    ascii;
    class     {};
    location  "{}";
    object    {};
}}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
""".format(OFclass,location,filename)

  return header

####################################################################
# Create the OpenFOAM directories
####################################################################
def openfoam_dircreate():
    # Create directories for openfoam dictionaries
    # Access: Only owner can read and write
    access_rights = 0o700
    # Create 0-directory
    if(os.path.exists("0.org")):
        shutil.rmtree("0.org")
        os.mkdir("0.org",access_rights)
    else:
        os.mkdir("0.org",access_rights)
    #Create constant-directory
    if(os.path.exists("constant")):
        shutil.rmtree("constant")
        os.mkdir("constant",access_rights)
    else:
        os.mkdir("constant",access_rights)
    #Create system-directory
    if(os.path.exists("system")):
        shutil.rmtree("system")
        os.mkdir("system",access_rights)
    else:
        os.mkdir("system",access_rights)

####################################################################
# Create the controldict file
####################################################################
def controlDict(data,solver):

    # Get required data
    startT = ''.join(extract_element_from_json(data, ["Events","Start time"]))
    endT = ''.join(extract_element_from_json(data, ["Events","End time"]))
    deltaT = ''.join(extract_element_from_json(data, ["Events","Time interval"]))
    writeT = ''.join(extract_element_from_json(data, ["Events","Write interval"]))

    # Create the controlDict file
    cdict = open("system/controldict","w")

    # Write the dictionary file
    ofheader = openfoam_header("system","controlDict","dictionary")
    cdict.write(ofheader)
    cdict.write('\napplication \t %s;\n\n' % (solver))
    cdict.write('startFrom \t latestTime;\n\n')
    cdict.write('startTime \t %s;\n\n' % (startT))
    cdict.write('stopAt \t endTime;\n\n')
    cdict.write('endTime \t %s;\n\n' % (endT))
    cdict.write('deltaT \t %s;\n\n' % (deltaT))
    cdict.write('writeControl \t adjustableRunTime;\n\n')
    cdict.write('writeInterval \t %s;\n\n' % (writeT))
    cdict.write('purgeWrite \t 0;\n\n')
    cdict.write('writeFormat \t ascii;\n\n')
    cdict.write('writePrecision \t t;\n\n')
    cdict.write('writeCompression \t uncompressed;\n\n')
    cdict.write('timeFormat \t general;\n\n')
    cdict.write('timePrecision \t 6;\n\n')
    cdict.write('runTimeModifiable \t yes;\n\n')
    cdict.write('adjustTimeStep \t yes;\n\n')
    cdict.write('maxCo \t 1.0;\n\n')
    cdict.write('maxAlphaCo \t 1.0;\n\n')
    cdict.write('maxDeltaT \t 1;\n\n')
    cdict.write('libs\n(\n\t"libwaves.so"\n)\n')

    # Close the controlDict file
    cdict.close()

####################################################################
# Create the fvSchemes file
####################################################################
def fvSchemesDict(data):

    # Create the fvSchemes file
    fvSch = open("system/fvSchemes","w")

    # Write data
    # Header
    ofheader = openfoam_header("system","fvSchemes","dictionary")
    fvSch.write(ofheader)
    # Other data
    # ddt 
    fvSch.write('\nddtSchemes\n{\n\tdefault\tEuler;\n}\n\n')
    # grad 
    fvSch.write('gradSchemes\n{\n\tdefault\tGauss linear;\n}\n\n')
    # div 
    fvSch.write('\ndivSchemes\n{\n\t')
    fvSch.write('div(rhoPhi,U)\tGauss limitedLinearV 1;\n\t')
    fvSch.write('div(U)\tGauss linear;\n\t')
    fvSch.write('div((rhoPhi|interpolate(porosity)),U)\tGauss limitedLinearV 1;\n\t')
    fvSch.write('div(rhoPhiPor,UPor)\tGauss limitedLinearV 1;\n\t')
    fvSch.write('div(rhoPhi,UPor)\tGauss limitedLinearV 1;\n\t')
    fvSch.write('div(rhoPhiPor,U)\tGauss limitedLinearV 1;\n\t') 
    fvSch.write('div(phi,alpha)\tGauss vanLeer;\n\t')
    fvSch.write('div(phirb,alpha)\tGauss interfaceCompression;\n\t')
    fvSch.write('div((muEff*dev(T(grad(U)))))\tGauss linear;\n\t')
    fvSch.write('div(phi,k)\tGauss upwind;\n\t')
    fvSch.write('div(phi,epsilon)\tGauss upwind;\n\t')
    fvSch.write('div((phi|interpolate(porosity)),k)\tGauss upwind;\n\t')
    fvSch.write('div((phi*interpolate(rho)),k)\tGauss upwind;\n\t')
    fvSch.write('div((phi|interpolate(porosity)),epsilon)\tGauss upwind;\n\t')
    fvSch.write('div(phi,omega)\tGauss upwind;\n\t')
    fvSch.write('div((phi|interpolate(porosity)),omega)\tGauss upwind;\n\t')
    fvSch.write('div((phi*interpolate(rho)),omega)\tGauss upwind;\n\t')
    fvSch.write('div((phi*interpolate(rho)),epsilon)\tGauss upwind;\n')
    fvSch.write('}\n\n')
    # laplacian
    fvSch.write('laplacianSchemes\n{\n\tdefault\tGauss linear corrected;\n}\n\n')
    # interpolation
    fvSch.write('interpolationSchemes\n{\n\tdefault\tlinear;\n}\n\n')
    # snGrad
    fvSch.write('snGradSchemes\n{\n\tdefault\tcorrected;\n}\n\n')
    # flux
    fvSch.write('fluxRequired\n{\n\t')
    fvSch.write('default\tno;\n\t')
    fvSch.write('p_rgh;\n\t')
    fvSch.write('pcorr;\n\t')
    fvSch.write('alpha.water;\n')
    fvSch.write('}\n')

    # Close the fvSchemes file
    fvSch.close()

####################################################################
# Create the decomposeParDict file
####################################################################
def decomposeParDict(data):

    # Get required data
    procs = ', '.join(extract_element_from_json(data, ["Events","Domain decomposition"]))
    method = ''.join(extract_element_from_json(data, ["Events","Decomposition method"]))

    # Find total number of processors
    procs = procs.replace(',', ' ')
    nums = [int(n) for n in procs.split()]
    totalprocs = nums[0]*nums[1]*nums[2]

    # Create the decomposeParDict file
    depdict = open("system/decomposeParDict","w")

    # Write the dictionary file
    ofheader = openfoam_header("system","decomposeParDict","dictionary")
    depdict.write(ofheader)
    depdict.write('\nnumberOfSubdomains \t %s;\n\n' % (totalprocs))
    depdict.write('numberOfSubdomains \t %s;\n\n' % (method))
    depdict.write('simpleCoeffs \n{\n\tn\t(%s); \n\tdelta\t0.001;\n}\n\n' % (procs))
    depdict.write('hierarchicalCoeffs \n{\n\tn\t(%s); \n\tdelta\t0.001;\n\torder\txyz;\n}\n' % (procs))

    # Close the decomposeParDict file
    depdict.close()

####################################################################
# Create the transportProperties file
####################################################################
def transportProperties(data):

    # Create the transportProperties file
    tprop = open("constant/transportProperties","w")

    # Get the properties necessary to print
    nuwater = ', '.join(extract_element_from_json(data, ["Events","Water viscosity"]))
    nuwaterexp = ', '.join(extract_element_from_json(data, ["Events","Water viscosity exponent"]))
    rhowater = ', '.join(extract_element_from_json(data, ["Events","Water density"]))
    nuair = ', '.join(extract_element_from_json(data, ["Events","Air viscosity"]))
    nuairexp = ', '.join(extract_element_from_json(data, ["Events","Air viscosity exponent"]))
    rhoair = ', '.join(extract_element_from_json(data, ["Events","Air density"]))
    sigma = ', '.join(extract_element_from_json(data, ["Events","Surface tension"]))

    # Write the dictionary file
    # Header
    ofheader = openfoam_header("constant","transportProperties","dictionary")
    tprop.write(ofheader)
    # Water properties
    tprop.write('\nphases (water air);\n\n')
    tprop.write('water\n{\n\ttransportModel\tNewtonian;\n')
    tprop.write('\tnu\t%se%s;\n' %(nuwater,nuwaterexp))
    tprop.write('\trho\t%s;\n}\n\n' %(rhowater))
    # Air properties
    tprop.write('air\n{\n\ttransportModel\tNewtonian;\n')
    tprop.write('\tnu\t%se%s;\n' %(nuair,nuairexp))
    tprop.write('\trho\t%s;\n}\n\n' %(rhoair))
    # Surface tension
    tprop.write('sigma\t%s;\n' %(sigma))

    # Close the transportProperties file
    tprop.close()

####################################################################
# Create the turbulenceProperties file
####################################################################
def turbulenceProperties(data):

    # Create the turbulenceProperties file
    tprop = open("constant/turbulenceProperties","w")

    # Get the properties necessary to print
    turb = ', '.join(extract_element_from_json(data, ["Events","Turbulence model"]))

    # Write the dictionary file
    # Header
    ofheader = openfoam_header("constant","turbulenceProperties","dictionary")
    tprop.write(ofheader)
    # Other content
    if int(turb) == 0:
        tprop.write('\nsimulationType\tlaminar;\n\n')
    else:
        tprop.write('\nsimulationType\tRAS;\n\n')
        tprop.write('RAS\n{\n\tRASModel\t')
        if int(turb) == 1:
            tprop.write('kEpsilon;\n\n')
        elif int(turb) == 2:
            tprop.write('kOmegaSST;\n\n')
        tprop.write('\tturbulence\ton;\n\n')
        tprop.write('\tprintCoeffs\ton;\n}')
        
    # Close the turbulenceProperties file
    tprop.close()

####################################################################
# Create the g-file
# Need to be updated later by getting direction of gravity
####################################################################
def gfile(data):

    # Create the gfile file
    gfile = open("constant/g","w")

    # Write the dictionary file
    # Header
    ofheader = openfoam_header("constant","g","uniformDimensionedVectorField")
    gfile.write(ofheader)
    # Other content
    gfile.write('\ndimensions\t[0 1 -2 0 0 0 0];\n\n')
    gfile.write('value\t(0 0 -9.81);\n')

    # Cloase the g-file
    gfile.close()

####################################################################
# Create the wavemakerMovementDict-file
####################################################################
def wMakerfile(data):

    # Create the wmakerfile file
    wmakerfile = open("constant/wavemakerMovementDict","w")

    # Write the dictionary file
    # Header
    ofheader = openfoam_header("constant","wavemakerMovementDict","dictionary")
    wmakerfile.write(ofheader)
    # Other content
    wmakerfile.write('\nreread\tfalse;\n\n')
    wmakerfile.write('#include "wavemakerMovement.txt"')
    
    # Close the wmakerfile file
    wmakerfile.close()

####################################################################
# Create the dynamicMeshDict-file
####################################################################
def dynmeshfileFlume(data):

    # Create the dynamic mesh file file
    dynmeshfile = open("constant/dynamicMeshDict","w")

    # Write the dictionary file
    # Header
    ofheader = openfoam_header("constant","dynamicMeshDict","dictionary")
    dynmeshfile.write(ofheader)
    # Other content
    dynmeshfile.write('\ndynamicFvMesh\tdynamicMotionSolverFvMesh;\n\n')
    dynmeshfile.write('motionSolverLibs\t("libfvMotionSolvers.so");\n\n')
    dynmeshfile.write('solver\tdisplacementLaplacian;\n\n')
    dynmeshfile.write('displacementLaplacianCoeffs\n{\n\tdiffusivity inversePointDistance (inlet);\n}\n');

    # Close the file
    dynmeshfile.close()

####################################################################
# MAIN ROUTINE
####################################################################
def main():

    # Get the system argument
    for arg in sys.argv[1:]:
        print arg

    # Open the JSON file
    # Load all the objects to the data variable
    # with open('dakota.json') as f:
    with open(arg) as f:
        data = json.load(f)

    # Get the project name
    projname = extract_element_from_json(data, ["Events","Project name"])
    projname = ', '.join(projname)
    logID = 0
    # Open a log file to write the outputs
    # Use project name for the log file
    # If no project name is specified, call it Untitled
    if projname != "":
        flog = open(''.join(projname.split())+".h20log","w")
    else:
        flog = open("Untitled.h20log","w")

    # Start the log file with header and time and date
    logfiletext = general_header()
    flog.write(logfiletext)
    logID += 1
    flog.write('%d (%s): This log has started.\n' % (logID,datetime.datetime.now()))

    # Get the event type
    simtype = extract_element_from_json(data, ["Events","Simulation type"])

    # This is only for the processing
    # Get the simulation type
    # Depending on the simulation type, we will run different events
    simtypeval = ''.join(simtype)
    logID += 1
    if int(simtypeval) == 0:
        flog.write('%d (%s): Error in simulation type! Simulation type not selected.\n' % (logID,datetime.datetime.now()))
        exit(0)
    else:
        flog.write('%d (%s): Simulation type found to be: %s.\n' % (logID,datetime.datetime.now(),simtypeval))

    # Create openfoam directories
    openfoam_dircreate()
    logID += 1
    flog.write('%d (%s): HydroUQ directories have been created.\n' % (logID,datetime.datetime.now()))

    # Initialize the solver
    solver = "olaDyMFlow"
    logID += 1
    flog.write('%d (%s): HydroUQ solver set to be %s.\n' % (logID,datetime.datetime.now(),solver))

    # Initialize some flags
    wMakerDictflag = 0
    dynmeshDictflag = 0
    logID += 1
    flog.write('%d (%s): Flags initialized.\n' % (logID,datetime.datetime.now()))

    # Simulation type 01 (SH - CFD coupling with user results)

    # Simulation type 01 (SH - CFD coupling with SimLibrary)

    # Simulation type 03 (CFD with Bathymetry)
    
    # Simulation type 04 (Wave flume)
    if int(simtypeval) == 4:
        wMakerDictflag = 1
        dynmeshDictflag = 1

    # Simulation type 05 (CFD with STL)

    # Simulation type 06 (CFD with Maps)

    # Simulation type 07 (CFD with Surrogate solver)

    # Start writing the OF dictionary files
    logsubID = 0
    # SYSTEM DIRECTORY
    # Write the controldict file
    controlDict(data,solver)
    logID += 1
    logsubID += 1
    flog.write('%d.%d (%s): HydroUQ dictionary controDict created.\n' % (logID,logsubID,datetime.datetime.now()))
    # Write the fvSchemes file
    fvSchemesDict(data)
    logID += 1
    logsubID += 1
    flog.write('%d.%d (%s): HydroUQ dictionary fvSchemes created.\n' % (logID,logsubID,datetime.datetime.now()))
    # Write the decomposeParDict file
    decomposeParDict(data)
    logsubID += 1
    flog.write('%d.%d (%s): HydroUQ dictionary decomposeParDict created.\n' % (logID,logsubID,datetime.datetime.now()))
    # fvSolution, blockMesh, snappyHexMesh
    # setFields (initial), topoSetDict (buildings)
    # Importing different meshes
    

    # CONSTANT DIRECTORY
    # Write the transportProperties file
    transportProperties(data)
    logsubID += 1
    flog.write('%d.%d (%s): HydroUQ dictionary transportProperties created.\n' % (logID,logsubID,datetime.datetime.now()))
    # Write the turbulence properties file
    turbulenceProperties(data)
    logsubID += 1
    flog.write('%d.%d (%s): HydroUQ dictionary turbulenceProperties created.\n' % (logID,logsubID,datetime.datetime.now()))
    # Write the gravity properties file
    gfile(data)
    logsubID += 1
    flog.write('%d.%d (%s): HydroUQ dictionary g created.\n' % (logID,logsubID,datetime.datetime.now()))
    # Write the wave maker file
    if wMakerDictflag == 1:
        wMakerfile(data)
        logsubID += 1
        flog.write('%d.%d (%s): HydroUQ dictionary wavemakeMovementDict created.\n' % (logID,logsubID,datetime.datetime.now()))
    # Write the dynamic mesh file
    if dynmeshDictflag == 1:
        dynmeshfileFlume(data)
        logsubID += 1
        flog.write('%d.%d (%s): HydroUQ dictionary dynamicMeshDict for wave Flume created.\n' % (logID,logsubID,datetime.datetime.now()))

####################################################################
# Primary function call
####################################################################
if __name__ == "__main__":
    main()
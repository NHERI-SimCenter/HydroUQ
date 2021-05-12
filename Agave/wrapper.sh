# NHERI SimCenter Hydro-UQ Backend v 1.0.0
echo "Welcome to HydroUQ application"

# Set basic information
set -x
${AGAVE_JOB_CALLBACK_RUNNING}

# Change to input directory
cd "${inputDirectory}"
pwd
ls -al

# unzip template dir
unzip templatedir.zip
rm templatedir.zip
cd ..
echo "Template directory unzipped"

#Unzip utils
cd utils
unzip '*.zip'
rm *.zip
cd ..
echo "Utilities unzipped"

#Add utils to PATH
export PATH=$PATH:$PWD/utils
chmod +x utils/*

# Set the paths for: (a) Input file (b) Input directories
# (c) Any external libraries
export BIM=${inputDirectory}/templatedir/dakota.json
export HYDROPATH=${inputDirectory}/templatedir
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/OpenFOAMExtensions
echo "New variables to folders have been created"

# Get the location of the SimCenter Backend Applications
SIMBACKEND=$(jq -r .remoteAppDir $BIM)

# Set paths for the HydroUQ at the simcenter backend
HYDROBRAIN=$SIMBACKEND/applications/createEVENT/GeoClawOpenFOAM
echo "Path to HydroBrain initialized"

# Load the OpenFoam module
module load intel/18.0.2
module load impi/18.0.2
module load openfoam/7.0
module load python3
echo "Modules have been loaded on Stampede2"

# Install necessary 
python3 -m pip install --user -r $HYDROBRAIN/requirements.txt
echo "Necessary python modules installed for the user"

# Export the paths to load OpenFOAM
export FOAM_USER_LIBBIN=/work/projects/wma_apps/stampede2/openfoam7/lib
export FOAM_USER_APPBIN=/work/projects/wma_apps/stampede2/openfoam7/bin
export PATH=$PATH:${FOAM_USER_APPBIN}
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${FOAM_USER_LIBBIN}
echo "OpenFOAM paths loaded"

echo "HydroUQ pre-processing has started"
python3 $HYDROBRAIN/Processor.py -b $BIM -I ${inputDirectory} -L $LD_LIBRARY_PATH -P $PATH -i ${inputFile} -d ${driverFile}
echo "HydroUQ pre-processing complete"

echo "HydroUQ processing started using caserun"
chmod +x caserun.sh
./caserun.sh

echo "HydroUQ run complete"
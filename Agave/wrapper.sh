# NHERI SimCenter Hydro-UQ Backend v 1.0.0

# What is this doing?
set -x
${AGAVE_JOB_CALLBACK_RUNNING}

#pause() {
#	read -n1 -rsp $'Press any key to continue or Ctrl+C to exit...\n'
#}

# Temporarily defining variables here
#inputDirectory="/work/07231/ajaybh/stampede2/trywrapper01"
#EVENTAPP="GeoClawOpenFOAM"

# Change to input directory
cd "${inputDirectory}"
pwd
ls -al
echo ${inputDirectory}

# unzip template dir
unzip templatedir.zip
rm templatedir.zip
cd ..
echo "Templatedir unzipped"

#Unzip utils
cd utils
unzip '*.zip'
rm *.zip
cd ..
echo "utils unzipped"

#Add utils to PATH
export PATH=$PATH:$PWD/utils
chmod +x utils/*

# Set the BIM file path to use
export BIM=${inputDirectory}/templatedir/dakota.json
echo $BIM

echo "Extracting EVENT app using jq"
#Extracting the first event app
EVENTAPP=$(jq -r .Events[0].Application $BIM)
echo "Event application detected is $EVENTAPP"
echo $EVENTAPP

if [[ $EVENTAPP == "GeoClawOpenFOAM" ]]; then
	echo "Event is processing"

	# Run the processing file
	# This will generate all the OpenFOAM dictionaries
	# by reading the dakota.json file
	python Processor.py ${inputDirectory}/templatedir/dakota.json

	# Load the OpenFoam module
	module load intel/18.0.2
	module load impi/18.0.2
	module load openfoam/7.0
	echo "Modules have been loaded on Stampede2"

	# Export the paths to load olaFoam
	export FOAM_USER_LIBBIN=/work/projects/wma_apps/stampede2/openfoam7/lib
	export FOAM_USER_APPBIN=/work/projects/wma_apps/stampede2/openfoam7/bin
	export PATH=$PATH:${FOAM_USER_APPBIN}
	export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${FOAM_USER_LIBBIN}
	echo "olafoam paths loaded"
	echo "Testing successfully complete"

elif [[ $EVENTAPP == "Preprocess" ]]; then
	echo "Event is pre-processing"
elif [[ $EVENTAPP == "Postprocess" ]]; then
	echo "Event is post-processing"
fi



# # Get the type of meshing
# meshing=$(jq -r .Events[0].meshing $BIM)
# echo "Meshing is: "
# echo $meshing

# # Get the number of processors to be used
# nProcessors=$(jq -r .Events[0].processors $BIM)
# echo "Number of processors is: "
# echo $nProcessors
# pause

# Run the meshing utility
# if [[ $meshing == "User" ]]; then
# 	echo 'User provided mesh, meshing skipped.'
# elif [[ $meshing == "blockMesh" ]]; then
# 	blockMesh >blockMesh.log
# elif [[ $meshing == "snappyHexMesh" ]]; then
# 	blockMesh >blockMesh.log
# 	snappyHexMesh >snappyHexMesh.log
# else
# 	echo 'Unknown meshing: $meshing'
# fi

# Copy the zero folder
# echo 'Preparing the 0-folder'
# cp -r 0.org 0

# # Set the fields
# echo 'Setting the fields'
# setFields >setFields.log

# # Decompose for a parallel run
# echo 'Decomposing the domain for parallel run'
# decomposePar >decomposePar.log

# # Start olaflow job
# echo 'Starting the olaflow run'
# # ibrun -n $nProcessors -o 0 ${OpenFOAMSolver} -parallel > ${OpenFOAMSolver}.log
# mpirun -np $nProcessors ${OpenFOAMSolver} -parallel >${OpenFOAMSolver}.log
# cd ..

# # Why is this necessary?
# #echo "OpenFOAM EVENT will be copied to templatedir"
# #cp -f EVENT.json ${inputDirectory}/templatedir/EVENT.json
# #cp -f EVENT.json ${inputDirectory}/templatedir/evt.j

# # Compress the OpenFOAM case
# cp ${OpenFOAMCase}/*.log .
# tar zcBf ${OpenFOAMCase}.tar.gz ${OpenFOAMCase}
# rm -fr ${OpenFOAMCase}

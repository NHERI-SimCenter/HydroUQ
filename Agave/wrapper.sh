# NHERI SimCenter Hydro-UQ Backend v 1.0.0

# What is this doing?
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

# Set the paths for: (a) Input file (b) Input directors
# (c) Any external libraries
export BIM=${inputDirectory}/templatedir/dakota.json
export HYDROPATH=${inputDirectory}/templatedir
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/OpenFOAMExtensions
echo "New variables to folders have been created"

# Get the location of the SimCenter Backend Applications
SIMBACKEND=$(jq -r .remoteAppDir $BIM)

# Set paths for the HydroUQ at the simcenter backend
HYDROBRAIN=$SIMBACKEND/applications/createEVENT/GeoClawOpenFOAM
echo "Path to HydroBrain initialize"

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

# Get information about EVENT
echo "Starting to extracting EVENT app using jq"

# Extracting the first event app
EVENTAPP=$(jq -r .Events[0].Application $BIM)
echo "Event application detected is $EVENTAPP"

# GeoClawOpenFOAM event
if [[ $EVENTAPP == "GeoClawOpenFOAM" ]]
then
	
	# Start event processing
	echo "GeoClawOpenFOAM event processing has started"

	# Run the processing file
	# This will generate all the OpenFOAM dictionaries
	# by reading the dakota.json file
	# python Processor.py ${inputDirectory}/templatedir/dakota.json
	# python Processor.py $BIM
	python3 $HYDROBRAIN/Processor.py $BIM

	# Meshing with OpenFOAM (or conversion)
	MESHTYPE=$(jq -r .Events[0].MeshType $BIM)
	if [[ $MESHTYPE == "0" ]]; then
		# Log in the event
		echo "Hydro-UQ mesher is being used"
		# Run blockmesh and snappyHexMesh
		# This is default for hydromesher
		blockMesh > blockMesh.log
		snappyHexMesh > snappyHexMesh.log
		# Log in the event
		echo "blockMesh and snappyHexMesh complete"
	elif [[ $MESHTYPE == "1" ]]; then
		# Log in the event
		echo "Mesh being imported from other software"
		# Get which software
		MESHSOFT=$(jq -r .Events[0].MeshSoftware $BIM)
		# Get the file name
		MESHSOFTFILE=$(jq -r .Events[0].MeshFile $BIM)
		# Get the path of the file exactle
		MESHFILE=${inputDirectory}/templatedir/$MESHSOFTFILE
		# Create the mesh files using the mesh
		# that have been imported from other softwares
		if [[ $MESHSOFT == "0" ]]; then
			fluentMeshToFoam $MESHFILE > fluentMeshToFoam.log
		elif [[ $MESHSOFT == "1" ]]; then
			ideasToFoam $MESHFILE > ideasToFoam.log
		elif [[ $MESHSOFT == "2" ]]; then
			cfx4ToFoam $MESHFILE > cfx4ToFoam.log
		elif [[ $MESHSOFT == "3" ]]; then
			gambitToFoam $MESHFILE > gambitToFoam.log
		elif [[ $MESHSOFT == "4" ]]; then
			gmshToFoam $MESHFILE > gmshToFoam.log
		fi
		# Log in the event
		echo "Mesh import complete"
	elif [[ $MESHTYPE == "2" ]]; then
		# Log in the event
		echo "Mesh being read from dictionaries"
		# Check what dictionary files are uploaded
		blockmeshfile=blockMeshDict
		snappymeshfile=snappyHexMeshDict
		if [[ -f "$blockmeshfile" ]]; then
			# Copy the files to system folder
			mv templatedir/blockMeshDict system/blockMeshDict
			# Run the command
			blockMesh > blockMesh.log
			# Log in the event
			echo "blockMesh complete"
			# Check if snappy needed
			if [[ -f "$snappymeshfile" ]]; then
				# Copy the files to system folder
				mv templatedir/snappyHexMeshDict system/snappyHexMeshDict
				# Run the command
				snappyHexMesh > snappyHexMesh.log
				# Log in the event
				echo "snappyHexMesh complete"
			fi
		else
			# Provide an error message
			echo "Error: Could not find blockMeshDict"
		fi
	fi

	# Create the 0-folder
	rm -fr 0
	cp -r 0.org 0

	# Setting up the fields
	setFields > setFields.log
	echo "Fields have been set successfully"

	# Decomposte for parallel processing
	decomposePar > decomposePar.log
	echo "Domain has been decomposed"

	# Starting CFD simulations
	ibrun olaDyMFlow -parallel > olaDyMFlow.log



elif [[ $EVENTAPP == "Preprocess" ]]; then
	echo "Event is pre-processing"
elif [[ $EVENTAPP == "Postprocess" ]]; then
	echo "Event is post-processing"
fi


.. _hdro-0002:

====================================================================================
Validation - Multiple Debris Impacts on a Raised Structure - Digital Twin (OSU LWF) 
====================================================================================

+---------------+----------------------------------------------+
| Problem files | :github:`Github <Examples/hdro-0002/>`       |
+---------------+----------------------------------------------+


.. contents:: Table of Contents
   :local:
   :backlinks: none


.. _hdro-0002-overview:

Overview
--------

In this digital twin validation example, debris-field wave-flume tests at a NHERI facility, Oregon State University's Large Wave Flume (OSU LWF), are briefly summarized before demonstrating the use of HydroUQ's OSU LWF digital twin paired with the Material Point Method (MPM).

.. figure:: figures/HydroUQ_MPM_3DViewPort_OSULWF_2024.04.25.gif
   :align: center
   :alt: Screenshot of a computer application, possibly a hydraulic simulation software named Hydro-UQ with various interface panels. On the left side, there's a user interface with several tabs such as "Event Type," "Materials," and "FEM." It includes input fields and a case directory path, along with a digital photo of what appears to be water overflowing a dam. On the right side, there's a 3D graphical representation of a blue, slender structural model with sensors or measurement points highlighted in yellow and red.
   :width: 600
   :figclass: align-center
   
   HydroUQ's desktop GUI for the NHERI OSU LWF digital wave-flume twin.

Details for the experiments are available in various publications. Namely, the work of Andrew Winter [Winter2020]_ [Winter2019]_, Krishnendu Shekhar [Shekhar2020]_ and Dakota Mascarenas [Mascarenas2022]_ [Mascarenas2022PORTS]_.  The simulations replicated in this example appeared originally in Bonus 2023 [Bonus2023Dissertation]_.

Experiments were performed in the NHERI OSU LWF, a 100 meter long flume with adjustable bathymetry, in order to quantify stochastic impact loads of ordered and disordered debris-fields on effectively rigid, raised structure. 

.. figure:: figures/OSU_Flume_Schematic_Dakota_Alam.png
   :align: center
   :alt: Schematic diagrams of an experimental wave flume setup with measurements and equipment notations. Image (a) shows a side view with dimensional markers, a piston-type wave maker, multiple sensors such as wave gauges (WG), ultrasonic wave gauges (USWG), and velocimeters (ADV), and a specimen at the end of the flume. The slope changes are labeled 1:12 and 1:24 referencing incline ratios. Image (b) is a top-down view of the flume, marking the locations of the sensors, the specimen, and bay sections, with distance measurements in numbers along the bottom of the diagram.
   :width: 600
   :figclass: align-center
   
   NHERI OSU LWF facilty's experimental schematic used in this example. Adapted from Winter 2019 [Winter2019]_, and Mascarenas 2022 [Mascarenas2022]_.

This example may help to produce a robust database (numerical and physical) from which to eventually be able to extract both the first-principals of wave-driven debris-field phenomena and design guidelines on induced forces. 

We validate against two very similar (but not identical) physical studies done in the OSU LWF by [Shekhar2020]_ and [Mascarenas2022]_, indicating high accuracy of our model and low bias to minor experiment specifications. 

Results for free surface elevation and streamwise structural loads are to be recorded for validation at a specified interval. 

Qualitatively, an MPM simulation of debris impacts on a raised structure in the OSU LWF is shown below.

.. figure:: figures/OSU_LWF_MPM_32L_Impact_3Photos.png
   :align: center
   :alt: A triptych of images showing the simulation of fluid flow around a cube-shaped obstacle. The left image displays the initial smooth laminar flow with neatly aligned flow lines in blue and orange before hitting the obstacle. The middle image captures the moment of disruption as the flow encounters the obstacle, creating complex patterns and vortices in varying shades of blue, indicating turbulence. The right image shows the aftermath with turbulent, chaotic flow patterns swirling past the obstacle, highlighted in intense shades of blue, suggesting dynamic fluid behavior.
   :width: 600
   :figclass: align-center

   OSU LWF debris impact photos from HydroUQ's MPM simulations.

It appears similar in the mechanism of debris impact, stalling, and deflection relative to the structure and flow for a similar case in Mascarenas 2022 [Mascarenas2022]_.

.. figure:: figures/OSU_LWF_Dakota_8L_Impact_3Photos.PNG
   :align: center
   :alt: A triptych of dark, grainy images showing a sheet of material being progressively printed with a series of decorated tiles. There is a green mechanical element with a sun-like emblem at the top; underneath, the sheet, printed with square patterns, moves through a red-colored machine element, showing different stages of the printing process in each panel. The surrounding area is mostly dark, with some reflections suggesting a metallic or wet surface.
   :width: 600
   :figclass: align-center

   OSU LWF debris impact photos from Mascarenas 2022 [Mascarenas2022]_ experiments.


The experiments by Shekhar et al. 2020 [Shekhar2020]_ are also shown below for comparison. These tests had a slightly different configuartion, primarily the debris were located 0.5 meters further upstream from the box and the water level was 0.10-0.15 meters lower than the 2.0 meter datum used in the simulations and Mascarenas 2022 [Mascarenas2022]_ experiments.

.. figure:: figures/OSU_LWF_Krish_Debris_8L_3Panel_Impacts_Photograph_Shekhar2020.PNG
   :align: center
   :alt: A sequence of four images depicting a debris trial with progressive stages of obstruction in front of an orange and grey structure, possibly for scientific research. In the first image, there is a single white rectangular object on a dark wet surface. Each subsequent image shows an additional piece of debris; the second has two such objects, the third shows three white objects, and the fourth displays a large cylindrical brown object in addition to the other items. The wet surface reflects light and creates a ripple effect around the debris. The reference "Shekhar et al. (2020)" suggests this is a figure from a research study or publication.
   :width: 600
   :figclass: align-center

   OSU LWF debris impact photos from Shekhar et al. 2020 [Shekhar2020]_ experiments.

Similar figures can be made for the whole range of order debris-array experiments done at the OSU LWF. However, this example focuses on teaching you how to replicate the above results.


.. _hdro-0002-setup:

Set-Up
------

A step-by-step walkthrough on replicating an MPM simulation result from Bonus 2023 [Bonus2023Dissertation]_ is provided below.

Open ``Settings``. Here we set the simulation time, the time step, and the number of processors to use, among other pre-simulation decisions.

.. figure:: figures/GUI_Settings.PNG
   :align: center
   :alt: Screenshot of a simulation settings interface with various parameters. Categories include Ambient, Spatial, Temporal, Scaling Laws, and Computer. Values are assigned to parameters such as CFL Number, Gravity, Grid Cell Size, Max Time Step, Dominant Law, and computer specifications like Computing Facility, Queue, Maximum Number of GPUs, GPU Name, and GPU Global Memory. The interface contains fields for input and selection with checkboxes, dropdown menus, and numerical inputs.
   :width: 600
   :figclass: align-center

   HydroUQ Settings GUI


Open ``Bodies`` / ``Fluid`` / ``Material``. Here we set the material properties of the fluid and the debris.

.. figure:: figures/GUI_Bodies_Fluid_Material.PNG
   :align: center
   :alt: Screenshot of a user interface from a simulation software showing configuration options for a fluid body. There are tabs for Settings, Bodies, Boundaries, Sensors, Outputs, and Results at the top. Below are options to 'Create Body' and 'Remove Body', with fluid, debris, and structure checkboxes. The 'Fluid' checkbox is checked and details such as 'Enable Body', 'Velocity', and 'Material Preset' with 'Water (Fresh)' selected are visible. The section also includes parameters like 'CFL Number', 'Density', and 'Constitutive Law Properties' with values for 'Bulk Modulus', 'Viscosity', and 'Bulk Derivative'.
   :width: 600
   :figclass: align-center

   HydroUQ Bodies Fluid Material GUI

Open ``Bodies`` / ``Fluid`` / ``Geometry``. Here we set the geometry of the flume, the debris, and the raised structure. 

.. figure:: figures/GUI_Bodies_Fluid_Geometry.PNG
   :align: center
   :alt: A screenshot of a software interface for creating and configuring geometrical bodies, likely for simulation purposes. The interface includes options for setting the body type, dimensions, and material properties. Sections like "Create Body," "Remove Body," "Create Geometry," and "Remove Geometry" are visible, as well as input fields for specifying dimensions and other parameters such as velocity, origin, and operation on prior geometry. The section labeled "Digital Twin Geometry" lists parameters for a facility named "Hinsdale Large Wave Flume (OSU LWF)" with dimensions and a table for filling in "Joint Position" coordinates.
   :width: 600
   :figclass: align-center

   HydroUQ Bodies Fluid Geometry GUI


Open ``Algorithm``. Here we set the algorithm parameters for the simulation. We choose to apply F-Bar antilocking to aid in the pressure field's accuracy on the fluid. The associated toggle must be checked, and the antilocking ratio set to 0.9, loosely.

.. figure:: figures/GUI_Bodies_Fluid_Algorithm.PNG
   :align: center
   :alt: Screenshot of a user interface from a simulation software showing settings for a computational body with options related to fluids, debris, and structures. The interface includes parameters for enabling the body, setting velocity, choosing material, geometry, algorithm, and particle representation, with specific fields for particle-per-cell value, ASFLIP advection options, and F-BAR anti-locking settings.
   :width: 600
   :figclass: align-center

   HydroUQ Bodies Fluid Algorithm GUI

Open ``Bodies`` / ``Fluid`` / ``Partitions``. Here we set the number of partitions for the simulation. This is the domain decomposition across discrete hardware units, i.e. Multi-GPUs. These may be kept as there default values. 

.. figure:: figures/GUI_Bodies_Fluid_Partitions.PNG
   :align: center
   :alt: Screenshot of a user interface from a simulation software, with various tabs like Settings, Bodies, Boundaries, Sensors, Outputs, and Results. The 'Bodies' tab is selected, showing options for creating and removing bodies categorized as Fluid, Debris, and Structures. The interface includes settings to enable body, set velocity, choose material, geometry, algorithm, and manage partitions with options to create and remove a partition, and configure related parameters such as GPU device ID, body ID, and partition dimensions.
   :width: 600
   :figclass: align-center

   HydroUQ Bodies Fluid Partitions GUI

Moving onto the creation of an ordered debris-array, we set the debris properties in the ``Bodies`` / ``Debris`` / ``Material`` tab. We will assume debris are made of HDPE plastic, as in experiments by Mascarenas 2022 [Mascarenas2022]_ and Shekhar et al. 2020 [Shekhar2020]_.

.. figure:: figures/GUI_Bodies_Debris_Material.PNG
   :align: center
   :alt: Screenshot of a software interface with options for simulating physical bodies in a virtual environment. The interface includes tabs such as Settings, Bodies, Boundaries, Sensors, Outputs, and Results. There is a section for creating or removing a body, with checkboxes for fluid, debris, and structures. The selected options display settings related to a body's physics, including switches to enable the body, input fields for velocity in XYZ coordinates, material presets, constitutive law, CFL number, density, and elastic properties like Young's Modulus and Poisson's Ratio. The interface is designed for configuring simulations with a focus on the material and physical characteristics of a body within the simulation.
   :width: 600
   :figclass: align-center

   HydroUQ Bodies Debris Material GUI

Open ``Bodies`` / ``Debris`` / ``Geometry``. Here we set the debris properties, such as the number of debris, the size of the debris, and the spacing between the debris. Rotation is another option, though not used in this example. We've elected to use an 8 x 4 grid of debris (longitudinal axis parallel to long-axis of the flume).

.. figure:: figures/GUI_Bodies_Debris_Geometry.PNG
   :align: center
   :alt: Screenshot of a software interface used for creating and manipulating geometrical objects, likely for simulation purposes. The interface includes sections labeled "Settings," "Bodies," "Boundaries," "Sensors," "Outputs," and "Results" at the top. The main focus is on a section for creating a new body, with options to enable/disable the body, set velocity, and choose material. There is a subsection titled "Create Geometry" with fields for defining an object named "Custom 1," with parameters such as Body Preset (Debris), Object Type (Sphere), Origin, Dimensions, Radius, and other geometric configurations. It appears to be designed for users to input specific values to define a spherical object for a simulation model.
   :width: 600
   :figclass: align-center

   HydroUQ Bodies Debris Geometry GUI

The ``Bodies`` / ``Debris`` / ``Algorithm`` and ``Debris`` / ``Partitions`` tabs are not used in this example, but are available for more advanced users.

Open ``Bodies`` / ``Structures``. Uncheck the box that enables this body, if it is checked. We will not model the structure as a body in this example, instead, we will modify it as a boundary later.

.. figure:: figures/GUI_Bodies_Structure_Disabled.PNG
   :align: center
   :alt: Screenshot of a user interface from a software application with a toolbar at the top displaying various categories such as Settings, Bodies, Boundaries, Sensors, Outputs, and Results. The highlighted tab is Bodies, with two main options presented: "Create Body" and "Remove Body," both with blue button styling. Below these options, there is a set of toggle switches labeled "Fluid," "Debris," and "Structures," with "Fluid" and "Debris" enabled, indicated by a checkmark, and "Structures" disabled with a crossed-out mark. To the left, there is an unchecked checkbox next to the text "Enable Body." The overall color scheme of the interface consists of shades of blue, gray, and white.
   :width: 600
   :figclass: align-center
   
   HydroUQ Bodies Structures GUI

Open ``Boundaries`` / ``Wave Flume``. We will set the boundary to be a rigid body, with a fixed separable velocity condition, that is faithful to the digital tiwn of the NHERI OSU LWF. Bathmyetry joint points should be indetical to the ones used in ``Bodeis`` / ``FLuid``.

.. figure:: figures/GUI_Boundaries_Flume.PNG
   :align: center
   :alt: Screenshot of a software interface with various buttons and settings related to hydrodynamic modeling. At the top, there are buttons labeled "Create Boundary" and "Remove Boundary." There are tabs for "Flume Facility," "Wave Generator," "Rigid Structure," and "Rigid Walls." The open tab displays settings for a "Flume Facility" with dimensions and origin points listed, as well as a "Point List" section where 'Joint Position (X)' and 'Joint Position (Y)' values are specified, with options to add or delete entries.
   :width: 600
   :figclass: align-center

   HydroUQ Boundaries Wave Flume Facility GUI

Open ``Boundaries`` / ``Wave Generator``. Fill in the appropriate file-path for the wave generator paddle motion. It is designed to produce near-solitary like waves.

.. figure:: figures/GUI_Boundaries_WaveGenerator.PNG
   :align: center
   :alt: Screenshot of a software interface for setting up simulation parameters related to wave generation. The interface includes options to 'Create Boundary' or 'Remove Boundary' and toggles for 'Flume Facility,' 'Wave Generator,' 'Rigid Structure,' and 'Rigid Walls.' The selected 'Boundary Preset' is 'Wave Generator,' and various details such as 'Wave Generation Method,' 'Contact Type,' 'Dimensions,' and 'Origin' are visible with fields for numerical input. A file path for a 'Paddle Motion File' is provided at the bottom with an option to 'Choose' the file.
   :width: 600
   :figclass: align-center
   
   HydroUQ Boundaries Wave Generator GUI

Open ``Boundaries`` / ``Rigid Structure``. This is where we will specify the raised structure as a boundary condition. By doing so, we can determine exact loads on the rigid boundary grid-nodes, which may then be mapped to the FEM tab for nonlinear UQ structural response analysis.

.. figure:: figures/GUI_Boundaries_RigidStructure.PNG
   :align: center
   :alt: Screenshot of a graphical user interface for simulation software, showing a section for defining a "Rigid Structure" boundary. The interface includes fields for object type selection, contact type, load-cell face, dimensions, origin coordinates, and options for applying Coulomb friction with input fields for static and dynamic friction on faces. Buttons for "Create Boundary" and "Remove Boundary" are visible, along with tabs for "Flume Facility," "Wave Generator," and "Rigid Walls" settings.
   :width: 600
   :figclass: align-center

   HydroUQ Boundaries Rigid Structure GUI

Open ``Boundaries`` / ``RigidWalls``.

.. figure:: figures/GUI_Boundaries_RigidWalls.PNG
   :align: center
   :alt: Screenshot of a software interface used for simulation or modeling, showing options related to setting up boundaries. The top menu includes tabs labeled Settings, Bodies, Boundaries, Sensors, Outputs, and Results. There are buttons for "Create Boundary" and "Remove Boundary," and check boxes for "Flume Facility," "Wave Generator," "Rigid Structure," and "Rigid Walls" settings. Under "Boundary Preset," "Rigid Walls" is selected with options for "Contact Type," "Dimensions (X,Y,Z)," "Origin (X,Y,Z)," "Apply Coulomb Friction," and fields for "Static Friction on Walls (X,Y,Z)" and "Dynamic Friction on Walls (X,Y,Z)." There is also a checkbox for "Apply Inlet/Outlet?"
   :width: 600
   :figclass: align-center

   HydroUQ Boundaries Wave-Flume Facility GUI

Open ``Sensors`` / ``Wave Gauges``. Set the ``Use these sensor?`` box to ``True`` so that the simulation will output results for the instruments we set on this page.

Three wave gauges will be defined. The first is located prior to the bathymetry ramps, the second partially up the ramps, and the third near the the bathymetry crest, debris, and raised structure. 

Set the origins and dimensions of each wave as in the table below. To match experimental conditions, we also apply a 120 Hz sampling rate to the wave gauges, meaning they record data every 0.0083 seconds. 

.. figure:: figures/GUI_Sensors_WaveGauges.PNG
   :align: center
   :alt: Screenshot of a user interface for sensor configuration within a simulation software. The highlighted tab is "Wave-Gauges" within a row of sensor options like "Velocity-Meters" and "Load-Cells." Options within the Wave-Gauges tab include toggles and dropdowns for sensor presets, application on specific entities such as 'particles,' attribute measurement like 'Elevation,' and sampling frequency. There's also a table listing individual wave gauges with their respective Origin X, Y, Z coordinates, dimensions, and controls for adding or deleting entries.
   :width: 600
   :figclass: align-center
   
   HydroUQ Sensors Wave-Gauge GUI

These wave gauges will read all numerical bodies (i.e. particles) within their defined regions every sampling step, and will report the highest elevation value (Position Y) of a contained body as the free-surface elevation at that gauge. The results is written into our sensor results files.


Open ``Sensors`` / ``Load Cells``. Set the ``Use these sensor?`` box to ``True`` so that the simulation will output results for the instruments we set on this page.

.. figure:: figures/GUI_Sensors_LoadCells.PNG
   :align: center
   :alt: Screenshot of an engineering software interface with a focus on sensor configuration settings. The "Create Sensor" and "Remove Sensor" buttons are at the top, followed by check boxes for different sensor types like Wave-Gauges, Velocity-Meters, Load-Cells, and Piezo-Meters. Below, a section labeled "Sensor Preset" is set to "Load-Cells" with options to specify the sensor usage, including drop-down menus for applying the sensor, measuring attribute, operation to perform, and sampling frequency. There is also an input table for defining a sensor named "LoadCell1," with fields for its origin coordinates and dimensions along the X, Y, and Z axes, and "Add" and "Del" buttons for managing the sensor list.
   :width: 600
   :figclass: align-center
   
   HydroUQ Sensors Load-Cells GUI


Open ``Outputs``. Here we set the non-physical output parameters for the simulation, e.g. attributes to save per frame and file extension types. The particle bodies' output frequency is set to 10 Hz (0.1 seconds), meaning the simulation will output results every 0.1 seconds. This is decent for animations without taking too much space. Fill in the rest of the data in the figure into your GUI to ensure all your outputs match this example.

.. figure:: figures/GUI_Outputs.PNG
   :align: center
   :alt: A screenshot of a software interface related to simulation or data processing, showing settings for outputting data related to "Bodies," "Checkpoint-Resume State," "Boundaries," "Sensors," and "Energies." The "Bodies" section includes options for Output File Type, Output Frequency, and different Output Attributes such as Pressure, Velocity (X, Y, Z), and Von Mises Stress. Other sections allow specifying file types such as BGEO, OBJ, TXT, and CSV, with their respective output frequencies. The interface includes checkboxes for "Only Save Exterior," "Output Kinetic," "Output Gravity," and "Output Strain," along with "Add" and "Delete" buttons for managing output attributes.
   :width: 600
   :figclass: align-center
   
   HydroUQ Outputs GUI



.. _hdro-0002-simulation:

Simulation
----------

We assume that 2 hours are reserved for your simulation. For those using the reduce fluid bulk modulus or reduced resolution, this may be more than neccesary.

This simulation was ran on the TACC Lonestar6 system. It uesd three NVIDIA A100 GPUs on a single node in the ``gpu-a100`` queue. Real time to complete was 2 hours. Simulated time in the digital twin is 26 seconds.

In order to retrieve results from the analysis, the analysis must complete and postprocess the model output files into an appropriate format before the end of the allotted submission time. 

.. important::
   Provide a large amount of time for the ``Max Run Time`` field in HydroUQ when submitting a job to ensure the model completes before the time allotted runs out! We recommend 2 hours in this example. 

.. warning::
   Only ask for what you need in terms of sensor size, count, and output sampling rate. Otherwise you will end up with massive amounts of data which can slow simulations due to I/O constraints.


.. _hdro-0002-analysis:

Analysis
--------

When the simulation job has completed, the results will be available on the remote system for retrieval or remote post-processing.

Retrieving the ``results.zip`` folder from the ``Tools & Applications`` Page of Design Safe starts by navigating to the designsafe-ci.org website. Login and go to ``Use DesignSafe`` / ``Tools & Applications``

.. figure:: figures/DSToolsAndAppsJobsStatus.PNG
   :align: center
   :alt: Screenshot of a user interface for an application named "TOOLS & APPLICATIONS" featuring three main sections. On the left, there is a 'DATA DEPOT BROWSER' allowing the user to select a data source and displays a list with items such as 'Trash', 'archive', and 'Hydro-UQ'. In the center, a large heading reads 'SELECT AN APP' with text below inviting users to select an application from the tray above, and describing the type of simulations and analyses that can be performed with different tools. On the right, a 'JOBS STATUS' panel lists several jobs related to 'HydroUQ' with their status such as 'RUNNING' or 'FINISHED', along with links to 'More info'. There are tabs across the top labeled 'Simulation', 'SimCenter Tools', 'Visualization', 'Analysis', 'Hazard Apps', 'Utilities', and 'My Apps'.
   :width: 600
   :figclass: align-center
   
   Locating the job files on DesignSafe


Check if the job has finished in the right-side vertical drawer by clicking the refresh icon. If it has, click ``More info``.  

.. figure:: figures/DSToolsAndAppsJobsStatusFinished.PNG
   :align: center
   :alt: Screenshot of a user interface element showing the word "FINISHED" in bold with a green background and a button next to it labeled "More info" featuring an information icon.
   :width: 600
   :figclass: align-center
   
   Job status is finished on DesignSafe


Once the job is finished, the output files should be available in the directory which the analysis results were sent to

Find the files by clicking ``View``. 
	
.. figure:: figures/DSToolsAndAppsJobsStatusViewFiles.PNG
   :align: center
   :alt: The image shows a user interface with details of a completed job. The application name is 'simcenter-openfoam-frontera-1.0.0' and the Job ID is provided. The job status indicates 'FINISHED', with submission and finish timestamps listed. The last status message states "Transitioning from status ARCHIVING to FINISHED in phase ARCHIVING." There is a highlighted button labeled 'View' under 'Output' and another button labeled 'Delete' under 'Actions'. A 'Close' button is at the bottom.
   :width: 600
   :figclass: align-center
   
   Viewing the job files on DesignSafe

Move the ``results.zip`` to somewhere in ``My Data/``. Use the Extractor tool available on DesignSafe.  Unzip the results.zip folder. 

.. figure:: figures/extractonDS.PNG
   :align: center
   :alt: Screenshot of a software interface with a menu bar containing tabs such as "Simulation," "SimCenter Tools," "Visualization," "Analysis," "Hazard Apps," "Utilities," and "My Apps." There are two highlighted options underneath the "Utilities" tab: "Compress Files" with an icon of a file being compressed, and "Extract Compressed File" with an icon of a file being unzipped, which is currently selected. The interface has a dark theme.
   :width: 600
   :figclass: align-center
    
   Extracting the ``results.zip`` folder on DesignSafe


OR Download the ``results.zip`` folder to your PC and unzip to look at the model results. 

.. figure:: figures/downloadResults.PNG
   :align: center
   :alt: "Screenshot of a web-based file management interface with a directory listing of files, including a .log, two .err, and two .out files, as well as a highlighted 'results.zip' file. The interface includes features such as a search bar, buttons for actions like 'Rename', 'Move', 'Copy', 'Preview', 'Preview Images', 'Download', and 'Move to Trash'. The 'Download' button is encircled in red, indicating an action or focus on the option to download files."
   :width: 600
   :figclass: align-center

   Download button on DesignSafe shown in red


Download the results to look at the geometry files of the analysis.

Extract the ``results.zip`` folder either on DesignSafe or on your local machine. You will likely want to have a free Side FX Houdini Apprentice installation to view ``BGEO`` files.

.. figure:: figures/resultsZip.png
   :align: center
   :alt: A screenshot of a file directory with a list of files. The file "results.zip" is highlighted with a file size of 962.1 MB and a last modified date of 10/8/23 at 10:36 AM. Other files in the list include logs, error outputs, and another zip file, all with differing file sizes and the same modification date.
   :width: 600
   :figclass: align-center
   
   File-system view of results zip folder on DesignSafe.


Locate the zip folder and extract it somewhere convenient. The local or remote work directory on your computer is a good option, but note that these files may be erased if another simulation is set-up in HydroUQ, so keep a backup somewhere outside the working directories.
	
HydroUQ's sensor / probe / instrument output is available in ``{your_path_to_HydroUQ_WorkDir}/HydroUQ/RemoteWorkDir/results/`` as ``CSV`` files.

Particle geometry files often have a ``BGEO`` extension, open Side FX Houdini Apprentice (free to use) to look at MPM results in high-detail.

Once complete, the simulation data at the three wave gauges (WG1, WG2, and WG3, left-to-right) is as showm below when plotted against experimental trials of Mascarenas 2022 [Mascarenas2022]_ for the "unbroken" solitary wave case.

.. figure:: figures/OSU_LWF_Wave_Gauges_Hydro_2D_Plots3_2023.10.31.png
   :align: center
   :alt: This image contains three line graphs labeled (a) Wave-Gauge[1], (b) Wave-Gauge[2], and (c) Wave-Gauge[3], each displaying water elevation change over time elapsed in seconds. The graphs compare different trials labeled as 'MPM - Bonus 2023', 'EXP - Trial 7', 'EXP - Trial 5', 'EXP - Trial 2', and a reference line for 'Still Water'. All graphs show a similar pattern of peaked curves, rising sharply then falling back down, with slight variations among the trials.
   :width: 600
   :figclass: align-center
   
   OSU LWF simulated free-surface elevation wave gauges vs. experimental data from Mascarenas 2022 [Mascarenas2022]_.


The simulation data at the load-cell is as shown below when plotted against experimental trials of Mascarenas 2022 [Mascarenas2022]_ for the "unbroken" solitary wave case. The experimental streamwise load is the combination of "LC5" and "LC8" in Mascarenas 2022 [Mascarenas2022]_, as both measured streamwise load on the box to reduce errors from position / slight box apparatus out-of-plane rotation.

.. figure:: figures/OSU_LWF_Load_Cells_Hydro_2023.10.31.png
   :align: center
   :alt: A line graph displaying "Streamwise Force on Structure [Newtons]" versus "Time Elapsed [seconds]". There are five lines representing different trials or methods: a red dashed line labeled "MPM - Bonus 2023 - Stabilized", a black dashed line labeled "MPM - Bonus 2023 - Original", and three solid lines in shades of gray to blue representing "EXP - Mascarenas 2022 - Trial 7", "Trial 5", and "Trial 2". The lines show a general increase in force over time, peaking around 36 seconds before gradually declining. The graph ranges from 30 to 45 seconds on the x-axis and from 0 to 300 Newtons on the y-axis.
   :width: 600
   :figclass: align-center
   
   OSU LWF simulated streamwise load-cells vs. experimental data from Mascarenas 2022 [Mascarenas2022]_.


Though only one case was considered here, if many experimental debris-field cases are ran (10+) we can use HydroUQ to perform a sensitivity analysis on the debris-field parameters. This isn't pursued here-in. 

However, the following box-and-whisker charts demonstrates the strengh of the numerical replication, as most points fall within experimental interquartile ranges and never outside of the experimental envelope for impact loads.

.. figure:: figures/OSU_U_FirstPeak_BoxAndWhiskers_KrishExpOnly_31072023.png
   :align: center
   :alt: A detailed scatter plot with box-and-whisker elements showing the impact force (N) relative to debris count ordered by array. Data points are differentiated by color and shape, representing different studies and types of simulations or experiments. Red and blue circles indicate "Longitudinal" and "Transverse" simulations from Bonus 2023. Black and gray circles denote "Total" force from experiments by Mascarenas 2022, while green triangles and inverted triangles are associated with Shekhar 2018's "Total" and "Debris" experiments, respectively. The impact force values range from 0 to 3000 N, with varying debris count configurations along the x-axis.
   :width: 600
   :figclass: align-center
   
   OSU LWF simulated first peak debris impact loads vs. experimental data from Mascarenas 2022 [Mascarenas2022]_.


This complete our HydroUQ validation example for multiple debris impacts on a raised structure in the OSU LWF, Bonus 2023 [Bonus2023Dissertation]_.


.. _hdro-0002-references:

References
----------

.. [Winter2019] Winter, A. (2019). "Effects of Flow Shielding and Channeling on Tsunami-Induced Loading of Coastal Structures." PhD thesis. University of Washington, Seattle.

.. [Winter2020] Andrew O Winter, Mohammad S Alam, Krishnendu Shekhar, Michael R Motley, Marc O Eberhard, Andre R Barbosa, Pedro Lomonaco, Pedro Arduino, Daniel T Cox (2019). "Tsunami-Like Wave Forces on an Elevated Coastal Structure: Effects of Flow Shielding and Channeling." Journal of Waterway, Port, Coastal, and Ocean Engineering.

.. [Shekhar2020] Shekhar, K., Mascarenas, D., and Cox, D. (2020). "Wave-Driven Debris Impact on a Raised Structure in the Large Wave Flume." 17th International Conference on Hydroinformatics, Seoul, South Korea.

.. [Mascarenas2022] Mascarenas, Dakota. (2022). "Quantification of Wave-Driven Debris Impact on a Raised Structure in a Large Wave Flume." Masters thesis. University of Washington, Seattle.

.. [Mascarenas2022PORTS] Mascarenas, Dakota, Motley, M., Eberhard, M. (2022). "Wave-Driven Debris Impact on a Raised Structure in the Large Wave Flume." Journal of Waterway, Port, Coastal, and Ocean Engineering.

.. [Bonus2023Dissertation] Bonus, Justin (2023). "Evaluation of Fluid-Driven Debris Impacts in a High-Performance Multi-GPU Material Point Method." PhD thesis. University of Washington, Seattle.



.. _hdro-0003:

=======================================================================================
Cylinder Half-Submerged in Flow  -  UW WASIRF Twin  -  FOAMySees (OpenFOAM + OpenSees)
=======================================================================================

+---------------+------------------------------------------------------------------------------------------------------+
| Problem files | :github:`Github <Examples/hdro-0003/>`                                                               |
+---------------+------------------------------------------------------------------------------------------------------+


.. contents:: Table of Contents
   :local:
   :backlinks: none

.. _hdro-0003-overview:

Overview
--------

This example demonstrates how to run a coupled **OpenSees-OpenFOAM** simulation (**FOAMySees**) to determine floor loads on a building caused by strongly-coupled, two-way fluid-structure interaction. 
You can then perform an **OpenSees** simulation of the building assuming uncertainties in the building properties. 

A truncated digital twin of the UW WASIRF wave flume contains a simple cantilevered cylinder. The cylinder, our structure, is half-submerged. The flow around the cylinder is calculated for a given period of time in order to determine a simulated structural response time-series under wave loading. 

Outputs of the **EVT** simulation will include results, sampled at specified frequenies, for the:

#. Fluid flow's free surface elevation at wave gauges
#. Flow velocity at velocimeter locations
#. Fluid pressure at piezometers locations
#. FSI forces and moments at the structural interface 
#. Cross-section cuts of the OpenFOAM continuum

As the **EVT** and **FEM** functionality are effectively fused for FOAMySees, the **FEM** tab will be envisioned as providing additional results in the form of:

#. Time-series motion of any structural nodes with defined *recorders* in the **OpenSees** model.

The **EDP** tab will then process these results.

#. Displacement of the cylinder tip from rest, peak relative-floor displacement (PFD)
#. Displacement of the cylinder tip relative to its base or supporting , peak inter-story drift (PID)
#. Peak floor acceleration (PFA)


.. _hdro-0003-setup:

Set-Up
------

The case is set up in the HydroUQ tool on DesignSafe.  You can select the case from the list of available examples off of the HydroUQ menubar, i.e. ``Examples / hdro-0003``. The case is set up as follows.

The flume is 1 meter wide (from Y=-0.5m to Y=0.5 m), 1 meter tall (Z=0.0m to Z=1.0m), and 4 meters long (X=0.0m to X=4.0m). The cardinal direction Z+ is vertical, X+ is downstream, and Y+ is crossflow. Gravity is -9.81 m / s^2 in the Z direction.

The case is initialized with a still water level of 0.25 meters. The velocity at the inlet is given a time history boundary condition, ``src/VelTime.csv``. 

This structure is a simple cylinder. It has a diameter 0.1 meters and it is located at X=1.5, Y=0.0, Z=0.0. The length of the cylinder is 0.5 meters in Z+. 

The cylinder is represented in OpenSees by a cantilevered beam, with an elastic section, modelled with displacement-action controlled beam elements. The bottom of the cantilevered beam is fixed at Z=0.0.

The constrained node is removed from the coupled solution, by omitting it from the list *coupledNodes* in the OpenSees model file. 

The interface surface file is ``'src/interface.stl'``. 



.. _hdro-0003-fig-schematic:

.. figure:: figures/hdro-0003 example.png
   :align: center
   :width: 600
   :figclass: align-center

   Schematic of the digital twin example in the UW WASIRF truncated flume

Probe positions in the digital flume are set at the following locations:
	
.. figure:: figures/hdro-0003 example probeLoc.png
   :align: center
   :width: 600
   :figclass: align-center

   Instrumentation locations in theUW WASIRF truncated digital flume    

Inlet Velocity Time History (U(t)) for the truncated digital twin is given by the following function in OpenFOAM:

.. figure:: figures/inletVTH.png
   :align: center
   :alt: A line graph titled "Inlet Velocity TH" showing a progressive increase in velocity (y-axis) over time (x-axis). The vertical y-axis is labeled "Velocity [m/s]" with values ranging from 0 to 0.6 m/s in increments of 0.1, and the horizontal x-axis is labeled "Time [s]" with values ranging from 0 to 12 seconds in increments of 2. The line starts at the origin and shows a curved increase, plateauing slightly as it approaches 0.6 m/s near the 10-second mark. The curve suggests a smooth and consistent acceleration of velocity over time.
   :width: 600
   :figclass: align-center

   Inlet Velocity Time History for the UW WASIRF digital twin
    

We now have a coupled simulation configured for fluid flow around, and the structural response of, a cylinder. Next, we will run the simulation on a remote TACC high-performance computing system.


.. _hdro-0003-simulation:

Simulation
----------

Login to DesignSafe and submit the job to run remotely on a TACC system, either *Frontera* or *Stampede3*.

Simulation time for 1 second in the digital flume took 1 hour and 20 minutes. This was using one computational node on TACC Frontera, possessing 56 cores.

The case can be run for as long as desired, but mind that the longer the case runs, the longer the postprocessing routines will be.

In order to retrieve results from the analysis, the job must complete and postprocess the model output files into a VTK format before the end of the allotted submission time. 

.. important::
   Provide a large amount of time for the *Max Run Time* field in HydroUQ when submitting a job to ensure the model completes before the time allotted runs out!

.. note::
   Be aware that the smaller the OpenFOAM Outputs and OpenSees Outputs *Time Interval* value is, the longer the post processing of the case will take after analysis has completed, 
   and the larger the ``results.zip`` folder will be. 

.. warning:: 
   Be modest when requesting simulation outputs across many recording probes or full geometry snapshots. 
   Only ask for what you need, or your simulation will become slow due to I/O constraints and the output data will be too large to effecitvely post-process or host on your local machine.




.. _hdro-0003-results:

Results
-----------

First, we must retrieve the ``results.zip`` folder from the DesignSafe file storage. This zip file will contain all our    from the Tools and Applications Page of Design Safe

.. figure:: figures/DSToolsAndAppsJobsStatus.PNG
   :align: center
   :alt: Screenshot of a web interface for a simulation platform titled 'TOOLS & APPLICATIONS'. On the top are tabs labeled 'Simulation', 'SimCenter Tools', 'Visualization', 'Analysis', 'Hazard Apps', 'Utilities', and 'My Apps'. To the left is a 'DATA DEPOT BROWSER' showing directories and files with names like 'Trash', 'archive', and 'Hydro-UQ'. The center section states 'SELECT AN APP' and describes how to pick an application from the tabs above, mentioning tools like OpenSees, ADCIRC, OpenFOAM, Jupyter, MATLAB, Paraview, and VisIt. To the right is a 'JOBS STATUS' section showing a list of tasks with names like 'HydroUQ: hdra-0003Short' and 'HydroUQ: Example002Shorter', indicating their statuses as 'RUNNING' or 'FINISHED'.
   :width: 600
   :figclass: align-center
   
   Locating the job files on DesignSafe

Check if the job has finished. If it has, click 'More info'.  

.. figure:: figures/DSToolsAndAppsJobsStatusFinished.PNG
   :align: center
   :alt: A graphical user interface element showing a status tag with the word "FINISHED" next to a button labeled "More info" which includes an information icon consisting of a lowercase "i" within a circle.
   :width: 600
   :figclass: align-center
   
   Once the job is finished, the output files should be available in the directory which the analysis results were sent to

Find the files by clicking 'View'. 
	
.. figure:: figures/DSToolsAndAppsJobsStatusViewFiles.PNG
   :align: center
   :alt: A screenshot of a computer interface showing the details of a completed job in an application. The Application name is "simcenter-openfoam-frontera-1.0.0," and there is a unique Job ID provided. The status indicates "FINISHED," and the submission and completion times are listed as "Oct 8, 2023 7:53:52 AM" and "Oct 8, 2023 10:36:54 AM" respectively. The Last Status Message states "Transitioning from status ARCHIVING to FINISHED in phase ARCHIVING." There are buttons for "View" with an arrow indicating it, and "Delete" under the Output and Actions sections. There is also a "Close" button at the bottom right corner.
   :width: 600
   :figclass: align-center
   
   Directory shown on DesignSafe contains the ``results.zip`` output for a HydroUQ EVT simulation. Download the results.zip folder to your local machine to view the model results.
	

Move the ``results.zip`` to somewhere in ``My Data/``. Use the Extractor tool available on DesignSafe.  Unzip the ``results.zip`` folder. 

.. figure:: figures/extractonDS.PNG
   :align: center
   :alt: Screenshot of a software interface with tabs labeled "Simulation," "SimCenter Tools," "Visualization," "Analysis," "Hazard Apps," "Utilities," and "My Apps." Under the "SimCenter Tools" tab, two options are shown: "Compress Files" with a symbol representing compression, and "Extract Compressed File" highlighted in blue with a corresponding symbol of a file being extracted. Below is a button with the text "RUN EXTRACT COMPRESSED FILE."
   :width: 600
   :figclass: align-center
    
	
OR Download the ``results.zip`` folder to your PC and unzip to look at the model results. 

.. figure:: figures/downloadResults.PNG
   :align: center
   :alt: Screenshot of a data management interface showing a directory listing with files and folders. At the top, there are search and action buttons like "Rename," "Move," "Copy," "Preview," "Preview Images," "Download," and "Move to Trash." The "Download" button is encircled, highlighting it. The main panel lists files such as "agave.log," "hydroqu-example002shorter-*-out," and "results.zip," with details on file size and the date of last modification. The file "results.zip" is selected with a green checkmark.
   :width: 600
   :figclass: align-center
   
   Download the results to look at the VTK files of the analysis. This will include OpenFOAM and OpenSees field data and model geometry

Extract the Zip folder either on DesignSafe or on your local machine. You will need Paraview to view the model data.

.. figure:: figures/resultsZip.png
   :align: center
   :alt: A screenshot of a file directory interface highlighting a file named "results.zip." The directory contains other files with names like "agave.log," and files starting with "hydroqu-example002shorter," each with different file extensions such as .log, .err, and .out. The selected "results.zip" file is encircled in red, indicating its importance or selection. File sizes and last modified dates are visible next to each file, with the dates showing 10/8/23 and times ranging from 10:35 AM to 10:36 AM.
   :width: 600
   :figclass: align-center
   
   Locate the zip folder and extract it to somewhere convenient
	
The results folder should look something like this. 
	
.. figure:: figures/results.png
   :align: center
   :alt: Screenshot of a computer file explorer window showing a directory listing within the 'results' folder. There are three folders named 'postProcessing', 'SeesOutput', and 'VTK', all modified on '10/8/2023 10:30 AM'. Below the folders, there is a PVD file named 'OpenSeesOutput.pvd' with the same modification date and a size of 13 KB.
   :width: 600
   :figclass: align-center
   
   This is the output of the model
	


.. _hdro-0003-analysis:

Analysis
--------

Paraview files have a .PVD extension. Open VTK/Fluid.vtm.series to look at OpenFOAM results.
Open OpenSeesOutput.pvd to look at OpenSees results.

.. figure:: figures/Paraview.PNG
   :align: center
   :alt: Screenshot of a scientific visualization software interface displaying a 3D model of a simulation. The main window shows a long, rectangular object with a gradient color scale indicating displacement magnitude, from blue (no displacement) to red (maximum displacement). A small portion is highlighted with a spectrum of colors showing increased displacement. Two scale bars, one for displacement magnitude and one for a variable labelled as 'alpha.water', are visible on the right side. The software's graphical user interface, including the pipeline browser, properties, and animation view panels, frames the model display.
   :width: 600
   :figclass: align-center
   
   This is the model output data as seen from ParaView

OpenSees Displacements And Reactions 


.. figure:: figures/TipDisplacement.png
   :align: center
   :alt: "A graph titled 'Tip Displacement VS Time' with the X-axis representing time in seconds and the Y-axis representing displacement in meters. The graph displays a line plot showing the tip displacement labeled as 'Tip Displacement_X (originalId=16 block=2)' with values starting at zero displacement, then rising sharply around 2 seconds and displaying fluctuating but generally increasing values up to around 0.0055 meters by 12 seconds."
   :width: 600
   :figclass: align-center
   
   This is the model output data as seen from ParaView

.. figure:: figures/ReactionForces.png
   :align: center
   :alt: The image depicts a line graph titled "OpenSees Reaction Forces" with the y-axis labeled "Force (N)" and the x-axis showing an unlabeled numerical scale from 0 to 10. There are three distinct lines representing 'Base Reaction_X,' 'Base Reaction_Y,' and 'Base Reaction_Z,' each annotated with '(originalId=0 block=2)' in red, green, and blue respectively. The 'Base Reaction_X' in red shows a sinusoidal pattern with amplitude decreasing over time. The 'Base Reaction_Y' in green demonstrates a more consistent, slightly undulating pattern. The 'Base Reaction_Z' in blue displays a high-frequency oscillating pattern with relatively steady amplitude. The lines overlap and intersect at various points throughout the graph.
   :width: 600
   :figclass: align-center
   
   This is the model output data as seen from ParaView


OpenFOAM probe and function object output is available in ``results/postProcessing/``. OpenFOAM output is currently unorganized. An example Matlab script is provided in the ``src/`` directory to post process the OpenFOAM output for this particular case and output. 
This file can be modified to work for any case. The names of the data folders will need to be changed according to the name of the probe given in HydroUQ.

.. figure:: figures/MatlabScriptCopyToLocation.PNG
   :align: center
   :alt: Screenshot of a computer file explorer window with a list of directories and files inside a folder named 'postProcessing.' Most items are folders named with different labels such as 'baseForces,' 'freeSurfaceVTK,' 'interface,' and several 'PressureProbe' and 'WaveGauge' folders, all modified on '10/8/2023 10:30 AM.' One file named 'plotData.m,' identified as MATLAB Code and sized 5 KB, has a red arrow pointing to it, highlighting its size. The breadcrumb navigation path at the top indicates the 'postProcessing' folder is inside the 'results' folder, which is within another 'results' folder in the 'Downloads' directory.
   :width: 600
   :figclass: align-center
    In the /src/ folder in the hrdo-0003 folder, an example matlab script is provided to look at time history data of the output probes	
	
	
OpenFOAM Calculated Story Forces are 

.. figure:: figures/storyForces.png
   :align: center
   :alt: A set of three line graphs titled "Story Forces", with each graph depicting force over time in seconds for three stories (levels) of a structure, along the X, Y, and Z axes. The top chart shows forces in the X direction, with lines for Story 1 X Force, Story 2 X Force, and Story 3 X Force, oscillating and diverging slightly. The middle chart depicts forces in the Y direction with similar oscillating patterns. The bottom chart shows forces in the Z direction, with the lines for Story 1 Z Force and Story 2 Z Force remaining almost constant and close to zero, while the Story 3 Z Force shows minor oscillation. Each force is measured in Newtons (N) and the time spans from 0 to 10 seconds.
   :width: 600
   :figclass: align-center
   
   Story Forces in OpenFOAM
	
OpenFOAM Calculated Coupled Interface Forces are visualized in the following figure

.. figure:: figures/Forces.png
   :align: center
   :alt: A line graph titled "FSI Interface Forces" displaying three differently colored lines representing force in the X, Y, and Z directions over a period of 10 seconds. The X-force (blue) exhibits a significant increase and fluctuations, peaking just below 7 N. The Y-force (orange) shows smaller, regular oscillations around 0 N. The Z-force (yellow) shows minor activity around 0 N with no significant peaks. The time in seconds is on the x-axis and the force in Newtons is on the y-axis.
   :width: 600
   :figclass: align-center
   
   Coupled Interface Forces in OpenFOAM-OpenSees
 
OpenFOAM calculated, coupled interface moments at the structural surface are
 
.. figure:: figures/Moments.png
   :align: center
   :alt: A line graph titled "FSI Interface Moments" displaying three different moment components (Mxx, Myy, Mzz) over time, measured in seconds, from 0 to 10. The Mxx component is represented by an orange line oscillating and decreasing over time. The Myy component is a blue oscillating line that becomes stable after an initial drop. The Mzz component is depicted by a yellow line that remains mostly flat across the time period. The moments are measured in Newton-meters (N*m) ranging from 0.1 to -0.7 on the y-axis.
   :width: 600
   :figclass: align-center
   
   Coupled Interface Moments in OpenFOAM-OpenSees

OpenFOAM calculated pressure probe values throughout the flume are

.. figure:: figures/Pressures.png
   :align: center
   :alt: A line graph titled "Pressure Sensors" plotting the pressure readings from four different sensors, P1 through P4, over a time period of 10 seconds. The y-axis is labeled "Pressure [Pa]" and ranges from -2000 to 3000 Pa, while the x-axis is labeled "Time [s]" and ranges from 0 to 10 seconds. The P1 sensor reading starts at approximately 2500 Pa and decreases slightly over time, represented by a blue line. The P2 reading is an orange line starting around 1700 Pa and also decreases. The P3 reading, in a yellow line, begins just under 1000 Pa and follows the same downward trend. The P4 sensor reading is a purple line that remains flat close to 0 Pa throughout the period. All lines show a smooth and gradual decline except P4, which is constant.
   :width: 600
   :figclass: align-center
   Pressure Probe Values in OpenFOAM

OpenFOAM calculated fluid velocity probe values throughout the flume are

.. figure:: figures/Velocities.png
   :align: center
   :alt: A line graph titled "Velocity Probe" with the X-axis labeled "Time [s]" ranging from 0 to 10 seconds, and the Y-axis labeled "Velocity [m/s]" ranging from -0.1 to 0.6 meters per second. There are three lines representing velocity components in X, Y, and Z directions. The X component shows a rising curve starting from zero and approaching approximately 0.6 m/s. The Y and Z components are relatively flat, hovering near zero throughout the graph. A legend in the upper right corner matches the X component with blue, the Y component with orange, and the Z component with grey, indicating the velocity in each respective axis.
   :width: 600
   :figclass: align-center
   
   Velocity Probe Values in OpenFOAM


OpenFOAM calculated wave gauge free-surface values at key locations in the facility are 

.. figure:: figures/WaveGauges.png
   :align: center
   :alt: A line graph titled "Wave Gauges" tracking free surface elevation (in meters) against time (in seconds) from 0 to 10 seconds. Seven different lines representing wave gauges WG1 through WG7 exhibit various oscillating patterns with a notable spike and subsequent oscillations starting at approximately 3.5 seconds. The legend in the upper right corner associates each wave gauge with a different color line on the graph.
   :width: 600
   :figclass: align-center
   
   Wave Gauge Free-Surface Probe Values in OpenFOAM

This completes the analysis of the model. In validation of any flume experimental case, a similar process may be employed with an added step of comparison to experimental data.



.. _hdro-0003-references:

References
----------

.. [Lewis2023]
   Lewis, N. (2023). Development of An Open-Source Methodology for Simulation of Civil Engineering Structures Subject to Multi-Hazards. *PhD thesis*, University of Washington, Seattle, WA. ISBN: 979-8-381408-69-0.

.. [OpenFOAM] 
   OpenFOAM. OpenFOAM Foundation. https://www.openfoam.com/

.. [OpenSees]
   OpenSees. Pacific Earthquake Engineering Research Center. http://opensees.berkeley.edu/

.. [Paraview] 
   Paraview. Kitware. https://www.paraview.org/

.. [DesignSafe]
   DesignSafe**. DesignSafe-CI. https://www.designsafe-ci.org/

.. [TACC] 
   TACC. Texas Advanced Computing Center. https://www.tacc.utexas.edu/

.. [Frontera] 
   Frontera. Texas Advanced Computing Center. https://frontera-portal.tacc.utexas.edu/

.. [Stampede3] 
   Stampede3. Texas Advanced Computing Center. https://stampede2.tacc.utexas.edu/








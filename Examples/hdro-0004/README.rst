.. _hdro-0004:

===============================================================================
Tsunami Debris Motion Through a Scaled Port Setting - WU TWB Digital Twin - MPM
===============================================================================

+---------------+----------------------------------------------+
| Problem files | :github:`Github <Examples/hdro-0004/>`       |
+---------------+----------------------------------------------+

.. contents:: Table of Contents
   :local:
   :backlinks: none

.. _hdro-0004-overview:

Outline
-------

Example to demonstrate how to run a MPM simulation to determine loads on an array of port buildings during a tsunami with respect to debris impacts and damming. After, we perform
an OpenSees simulation of one building assuming uncertainties in the building properties.

The Waseda University Tsunami Wave Basin (WU TBW) flume is 4 meter wide (from X=-2m to X=2 m), 1 meter tall (Z=0.0m to Z=1.0m), and 9 meters long (Y=0.0m to Y=9.0m). 

The case is initialized with a still water level of 0.23 meters. 

Results for free surface, velocity, and pressure, as well as structural load forces are output at a specified interval to match experimental instruments. 



.. figure:: figures/TOKYO_BoreFrontImage_Debris3_o5x1_Frame20_29072023.png
   :align: center
   :alt: A digital simulation of fluid dynamics showing wave patterns interacting with a series of solid objects. The simulated water has a clear blue gradient, and the waves are visualized as lines that bend and spread around the brown cuboid objects. There are also dark shadows beneath the objects, suggesting depth in the water. In the foreground, there's a noticeable rectangular outline representing a boundary or a measurement tool. The image has a watermark with the text "Houdini," indicating that the simulation was likely created using the Houdini visual effects software.
   :width: 600
   :figclass: align-center

   Simulation of MPM debris impacts on one row of five obstacles


.. figure:: figures/B4_Flume_Schematic.png
   :align: center
   :alt: Technical diagrams depicting the top-down (plain) and side (profile) views of a wave propagation testing setup with labeled components such as flow direction, air valves, wave markers (WG1, WG2), electronic current meters (ECM1), cameras (CAM1, CAM2), locators, debris, fixed obstacles, and a harbor apron area. The diagrams include measurements for spacing and sizes of components in millimeters, and depth specifications for the testing section.
   :width: 600
   :figclass: align-center
    
   Schematic of the flume and sensor locations

	
.. figure:: figures/B4_Debris_Picture.PNG
   :align: center
   :alt: The image depicts two panels, labeled (a) and (b), showing a green plastic object with specific dimensions. In panel (a), two identical green plastic casings with a rectangular base and two cylindrical towers on one end are presented alongside small black components. One casing has a black switch or button installed. In panel (b), a close-up view of one green casing is shown, featuring two holes on its surface, with a scale indicating a length of 0.15 meters, and measurement markers for depth at 0.05 meters on the side.
   :width: 600
   :figclass: align-center
    
   Smart debris used in experiments


.. _hdro-0004-simulation:

Simulation
----------

Simulation Time: 6 seconds - Ran on TACC Lonestar6, 56 processors, 3 NVIDIA A100 GPUs, 1 node -> Real Time: 1hr, 20 minutes

The case can be run for as long as desired, but mind that the longer the case runs, the longer the postprocessing routines will be.

In order to retrieve results from the analysis, the analysis must complete and postprocess the model output files into a VTK format before the end of the allotted submission time. 

Provide a large amount of time for the 'Max Run Time' field in HydroUQ when submitting a job to ensure the model completes before the time allotted runs out!

Be aware that the smaller the OpenFOAM Outputs and OpenSees Outputs 'Time Interval' value is, the longer the post processing of the case will take after analysis has completed, and the larger the results.zip folder will be. 

.. warning::
   Use caution when requesting sensors and using high sampling rates. Only ask for what you need, or you will end up will massive amounts of data.



.. _hdro-0004-analysis:

Analysis
--------

Retrieving the results.zip folder from the Tools and Applications Page of Design Safe.. 

.. figure:: figures/DSToolsAndAppsJobsStatus.PNG
   :align: center
   :alt: Screenshot of a software interface labeled "TOOLS & APPLICATIONS" with several sections. On the left, there is a "DATA DEPOT BROWSER" with a list of items including Trash, archive, and Hydro-UQ. In the center, a large heading says "SELECT AN APP," followed by a description of the Tools & Applications space capabilities, mentioning simulation codes like OpenSees, ADCIRC, OpenFOAM, and visualization tools like Jupyter, MATLAB, Paraview, and VisIt. On the right, there is a "JOBS STATUS" section listing several jobs related to HydroUQ with statuses like 'RUNNING' and 'FINISHED.' The top navigation tabs include Simulation, SimCenter Tools, Visualization, Analysis, Hazard Apps, Utilities, and My Apps.
   :width: 600
   :figclass: align-center
   
   Locating the job files on DesignSafe

Check if the job has finished. If it has, click 'More info'.  

.. figure:: figures/DSToolsAndAppsJobsStatusFinished.PNG
   :align: center
   :alt: A screenshot of a button with the word "FINISHED" in bold lettering next to a clickable link or button labeled "More info" with an information icon, which is placed on a light green background.
   :width: 600
   :figclass: align-center
   
   Once the job is finished, the output files should be available in the directory which the analysis results were sent to

Find the files by clicking 'View'. 
	
.. figure:: figures/DSToolsAndAppsJobsStatusViewFiles.PNG
   :align: center
   :alt: Screenshot of a job status interface showing that a computational job has finished. It includes the application name 'simcenter-openfoam-frontera-1.0.0', a unique Job ID, the status 'FINISHED', submission and finish timestamps, and a last status message indicating a transition from 'ARCHIVING' to 'FINISHED'. There is an 'Output' section with a 'View' button indicated by a red arrow, and an 'Actions' section with a 'Delete' button. A 'Close' button is also visible at the bottom right corner.
   :width: 600
   :figclass: align-center
   
   Locating this directory is easy. 
	

Move the results.zip to somewhere in My Data/. Use the Extractor tool available on DesignSafe.  Unzip the results.zip folder. 

.. figure:: figures/extractonDS.PNG
   :align: center
   :alt: Screenshot of a computer interface with menu tabs labeled Simulation, SimCenter Tools, Visualization, Analysis, Hazard Apps, Utilities, and My Apps. Two options are displayed under the SimCenter Tools tab: "Compress Files" with an icon of a file being compressed and "Extract Compressed File" highlighted in blue with an icon of a file being extracted.
   :width: 600
   :figclass: align-center
    
	
OR Download the results.zip folder to your PC and unzip to look at the model results. 

.. figure:: figures/downloadResults.PNG
   :align: center
   :alt: A screenshot of a file management interface displaying a list of files within a directory labeled "archive / jobs / job-3c316421-dfe5-47bc-98b2-f339e08d9a19-007." The files shown include 'agave.log,' 'hydroqu-example002shorter._____.err,' 'hydroqu-example002shorter._____.out,' and 'results.zip,' with 'results.zip' being selected. File sizes and last modified dates are visible next to each file. Above the file list, there are toolbar options including 'Rename,' 'Move,' 'Copy,' 'Preview,' 'Preview Images,' 'Download,' and 'Move to Trash,' with the 'Download' button encircled presumably to indicate its function.
   :width: 600
   :figclass: align-center
   
   Download the results to look at the VTK files of the analysis. This will include OpenFOAM and OpenSees field data and model geometry

Extract the Zip folder either on DesignSafe or on your local machine. You will need Paraview to view the model data.

.. figure:: figures/resultsZip.png
   :align: center
   :alt: Screenshot of a file manager window with a directory listing including files such as "agave.log," "hydrouq-example002shorter-3c316421.err," "hydrouq-example002shorter-3c316421.out," and a highlighted file named "results.zip." The "results.zip" file is 962.1 MB in size and was last modified on 10/8/23 at 10:36 AM. Other files vary in size and share similar modification times.
   :width: 600
   :figclass: align-center
   
   Locate the zip folder and extract it to somewhere convenient


.. The results folder should look something like this. 
	
.. .. figure:: figures/results.png
..    :align: center
   :alt: Screenshot of a file explorer window showing a directory named 'results' within a larger 'results' folder. There are three subfolders named 'postProcessing,' 'SeesOutput,' and 'VTK,' and one PVD file named 'OpenSeesOutput.pvd,' all with the 'Date modified' timestamp of '10/8/2023 10:30 AM.' The 'Size' is visible only for the 'OpenSeesOutput.pvd' file, which is 13 KB.
..    :width: 600
..    :figclass: align-center
   
..    This is the output of the model
	
.. Paraview files have a .PVD extension. Open VTK/Fluid.vtm.series to look at OpenFOAM results.
.. Open OpenSeesOutput.pvd to look at OpenSees results.

.. .. figure:: figures/Paraview.PNG
..    :align: center
   :alt: Screenshot of a scientific visualization software interface displaying a 3D model of a fluid simulation. The model shows a color gradient representing displacement magnitude on a rectangular domain with a central vertical structure experiencing more displacement, indicated by a column of red and orange colors. Two legend bars illustrate the range of displacement magnitudes and water volume fraction (alpha.water) values. The interface contains various toolbars, a pipeline browser, properties panel, and an animation timeline view.
..    :width: 600
..    :figclass: align-center
   
..    This is the model output data as seen from ParaView

.. OpenSees Displacements And Reactions 

.. .. figure:: figures/TipDisplacement.png
..    :align: center
   :alt: A line graph titled "Tip Displacement VS Time" with the x-axis representing time and the y-axis representing displacement in meters. The line, labeled "Tip Displacement_X (originalId=16 block=2)", shows a fluctuating increase in displacement from approximately 0 to just over 0.006 meters as time progresses from -2 to 12 units. The graph line is colored in brown with a distinct zigzag pattern indicating varying displacement over time.
..    :width: 600
..    :figclass: align-center
   
..    This is the model output data as seen from ParaView

.. .. figure:: figures/ReactionForces.png
..    :align: center
   :alt: A line graph titled "OpenSees Reaction Forces," plotting three separate lines representing base reaction forces in the X, Y, and Z directions, each identified by different colors: red for X, green for Y, and blue for Z. The force values are measured in newtons (N) and the X-axis appears to be a time or step index ranging from 0 to 10. The red X-direction line shows large oscillations that increase in amplitude over time, the green Y-direction line shows smaller, consistent oscillations, and the blue Z-direction line shows medium oscillations with increasing amplitude but less regular than the X-direction.
..    :width: 600
..    :figclass: align-center
   
..    This is the model output data as seen from ParaView


.. OpenFOAM probe and function object output is available in results/postProcessing/.

.. OpenFOAM output is messy. An example Matlab script is provided in the /src/ directory to post process the OpenFOAM output for this particular case and output. 
.. This file can be modified to work for any case. The names of the data folders will need to be changed according to the name of the probe given in HydroUQ.

.. .. figure:: figures/MatlabScriptCopyToLocation.PNG
..    :align: center
   :alt: Screenshot of a computer file explorer window focused on the 'postProcessing' directory, which contains several file folders and a MATLAB code file named 'plotData.m' listed with details such as name, date modified, type, and size. One of the items, 'plotData.m,' is highlighted, and an arrow points to its size (5 KB) indicating a smaller file amongst the folders. All folders and files have a last modified date of '10/8/2023 10:30 AM', except for 'plotData.m' which was modified on '10/8/2023 9:49 AM'.
..    :width: 600
..    :figclass: align-center
..     In the /src/ folder in the hdro-0004 folder, an example matlab script is provided to look at time history data of the output probes	
	
	
.. OpenFOAM Calculated Story Forces

.. .. figure:: figures/storyForces.png
..    :align: center
   :alt: A series of three line graphs titled "Story Forces," plotted on a grid, representing forces over time in seconds for three different stories (levels). The first graph depicts X Forces, the second graph shows Y Forces, and the third graph illustrates Z Forces, each with lines representing Story 1, Story 2, and Story 3. The X and Y Forces show oscillatory patterns, while Z Forces remain relatively flat. Each story's force is color-coded: Story 1 in blue, Story 2 in orange, and Story 3 in gray. The time axis ranges from 0 to 10 seconds, and the force axis for each graph is scaled in Newtons (N) with varying ranges.
..    :width: 600
..    :figclass: align-center
   
..    Story Forces	
	
.. OpenFOAM Calculated Coupled Interface Forces

.. .. figure:: figures/Forces.png
..    :align: center
   :alt: A line graph titled "FSI Interface Forces" displaying three different force components over time measured in seconds (s) on the x-axis and force in newtons (N) on the y-axis. The blue line represents force in the X direction, the orange line represents force in the Y direction, and the brown line represents force in the Z direction. The blue line shows a rising sawtooth pattern starting from 0 and reaching approximately 6 N at 10 seconds. The orange line fluctuates around 0 N with small amplitude oscillations. The brown line also shows minor fluctuations with a slight downward trend towards -1 N by the end of the 10-second interval.
..    :width: 600
..    :figclass: align-center
   
..    Forces
 
.. OpenFOAM Calculated Coupled Interface Moments
 
.. .. figure:: figures/Moments.png
..    :align: center
   :alt: A line graph titled "FSI Interface Moments" plotting three different moments (Mxx, Myy, Mzz) over time in seconds on the x-axis and moment in Newton-meters (N*m) on the y-axis. The Mxx curve is a constant line near 0, Myy shows oscillating decay, and Mzz shows a steady decrease with some oscillations. The time range is from 0 to 10 seconds and the moment range is from 0.1 to -0.7 N*m.
..    :width: 600
..    :figclass: align-center
   
..    Moments

.. OpenFOAM Calculated Pressure Probe Values

.. .. figure:: figures/Pressures.png
..    :align: center
   :alt: A line graph titled "Pressure Sensors" displaying pressure readings in pascals from four sensors (P1, P2, P3, P4) over time in seconds. P1 starts highest, above 3000 Pa and slightly decreases over 10 seconds. P2 starts around 2250 Pa and also decreases. P3 and P4 start at approximately 1500 Pa and 250 Pa, respectively, both showing a slight downward trend. The time on the x-axis ranges from 0 to 10 seconds, and the pressure on the y-axis ranges from -2000 to 3000 Pa. Each sensor's line is color-coded: P1 in blue, P2 in orange, P3 in yellow, and P4 in purple.
..    :width: 600
..    :figclass: align-center
   
..    Pressures

.. OpenFOAM Calculated Velocity Probe Values

.. .. figure:: figures/Velocities.png
..    :align: center
   :alt: A line graph titled "Velocity Probe" plotting velocity in meters per second (m/s) on the y-axis against time in seconds (s) on the x-axis. Three lines, labeled X, Y, and Z, represent distinct velocity components. The X-component shows a steady increase in velocity, reaching approximately 0.6 m/s at the 10-second mark. The Y and Z components are relatively flat lines hovering near zero throughout the 10-second time span.
..    :width: 600
..    :figclass: align-center
..     Velocities


.. OpenFOAM Calculated Free Surface Values 

.. .. figure:: figures/WaveGauges.png
..    :align: center
   :alt: A line graph titled "Wave Gauges" with free surface elevation in meters on the y-axis and time in seconds on the x-axis. Multiple lines representing different wave gauges labeled WG1 through WG7 show fluctuations in surface elevation over a period of 10 seconds. The lines exhibit a pattern of waves with varying amplitudes and frequencies, with one line in particular showing a larger amplitude with a descending oscillation.
..    :width: 600
..    :figclass: align-center
   
..    Wave Gauges


.. _hdro-0004-references:

References
----------





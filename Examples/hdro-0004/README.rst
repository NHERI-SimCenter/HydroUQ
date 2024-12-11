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

Example to demonstrate how to run a MPM simulation to determine loads on an array of port buildings during a tsunami with respect to debris impacts and damming. Replicates at low resolution the comparative analysis paper results of [Bonus2025]_.

.. figure:: figures/TOKYO_MPM_ObstacleEffect_AllCases_y0.25to0.375_Persp_2024.04.03.png
   :align: center
   :width: 600
   :figclass: align-center

   Simulation of three MPM tsunami debris simulations on zero, one, and two rows of five obstacles replicating a port-setting at a Froude scale of 1:40.

Stochastic experiments were performed at the Waseda University Tsunami Wave Basin (WU TBW) flume. Here we replicate it in a simple digital twin with HydroUQ's MPM module. The flume is 4 meters wide (from X=-2m to X=2 m), 1 meter tall (Z=0.0m to Z=1.0m), and 9 meters long (Y=0.0m to Y=9.0m). The case is initialized with a still water level of 0.23 meters. 

.. figure:: figures/TOKYO_Flume_Schematic_2024.04.05.png
   :align: center
   :width: 600
   :figclass: align-center
    
   Schematic of Waseda University's Tsunami Wave Basin (WU TWB) and sensor locations

"Smart" debris were used in the experiments, shown below. In MPM they are modeled as fixed-corotated debris.

.. figure:: figures/B4_Debris_Picture.PNG
   :align: center
   :width: 600
   :figclass: align-center
    
   Smart debris used in experiments



.. _hdro-0004-setup:

Set-Up
----------

To configure the digital twin case in HydroUQ, the following settings will be specified.

.. _hdro-0004-simulation:

Simulation
----------

Simulation Time: 6 seconds - Ran on TACC Lonestar6, 56 processors, 3 NVIDIA A100 GPUs, 1 node -> Real Time: 1hr, 20 minutes

The case can be run for as long as desired, but mind that the longer the case runs, the longer the postprocessing routines will be.

In order to retrieve results from the analysis, the analysis must complete and postprocess the model output files into a VTK format before the end of the allotted submission time. 

Provide a large amount of time for the 'Max Run Time' field in HydroUQ when submitting a job to ensure the model completes before the time allotted runs out!

Be aware that the smaller the OpenFOAM Outputs and OpenSees Outputs 'Time Interval' value is, the longer the post-processing of the case will take after analysis has been completed, and the larger the results.zip folder will be. 

.. warning::
   Use caution when requesting sensors and using high sampling rates. Only ask for what you need, or you will end up with massive amounts of data.



.. _hdro-0004-analysis:

Analysis
--------

Retrieving the results.zip folder from the Tools and Applications Page of Design Safe.. 

.. figure:: figures/DSToolsAndAppsJobsStatus.PNG
   :align: center
   :width: 600
   :figclass: align-center
   
   Locating the job files on DesignSafe

Check if the job has finished. If it has, click 'More info'.  

.. figure:: figures/DSToolsAndAppsJobsStatusFinished.PNG
   :align: center
   :width: 600
   :figclass: align-center
   
   Once the job is finished, the output files should be available in the directory to which the analysis results were sent

Find the files by clicking 'View'. 
	
.. figure:: figures/DSToolsAndAppsJobsStatusViewFiles.PNG
   :align: center
   :width: 600
   :figclass: align-center
   
   Locating this directory is easy. 
	

Move the results.zip to somewhere in My Data/. Use the Extractor tool available on DesignSafe.  Unzip the results.zip folder. 

.. figure:: figures/extractonDS.PNG
   :align: center
   :width: 600
   :figclass: align-center
    
	
OR Download the results.zip folder to your PC and unzip to look at the model results. 

.. figure:: figures/downloadResults.PNG
   :align: center
   :width: 600
   :figclass: align-center
   
   Download the results to look at the VTK files of the analysis. This will include OpenFOAM and OpenSees field data and model geometry

Extract the Zip folder either on DesignSafe or on your local machine. You will need Paraview to view the model data.

.. figure:: figures/resultsZip.png
   :align: center
   :width: 600
   :figclass: align-center
   
   Locate the zip folder and extract it to somewhere convenient



Comparative results between the Material Point Method (MPM, HydroUQ), Smoothed Particle Hydrodynamics (SPH, DualSPHysics), and the Finite Volume Method (FVM, STAR-CCM+).:
	

.. figure:: figures/Benchmark4_Wave_Gauge_Plots4_2024.04.27.png
   :align: center
   :width: 600
   :figclass: align-center
   
   Comparative results for wave gauge free-surface measurements

.. figure:: figures/Benchmark4_Debris_Displacement_BoxAndWhiskers_2024.04.27.png
   :align: center
   :width: 600
   :figclass: align-center
   
   Comparative results for debris displacement


.. figure:: figures/Benchmark4_Debris_Spread_BoxAndWhiskers_2024.04.27.png
   :align: center
   :width: 600
   :figclass: align-center
   
   Comparative results for debris spreading angle


.. figure:: figures/Benchmark4_Obstacle_Load_Plots3_2024.04.27.png
   :align: center
   :width: 600
   :figclass: align-center
   
   Comparative results for debris-structure loads


.. The results folder should look something like this. 
	
.. .. figure:: figures/results.png
..    :align: center
..    :width: 600
..    :figclass: align-center
   
..    This is the output of the model
	
.. Paraview files have a .PVD extension. Open VTK/Fluid.vtm.series to look at OpenFOAM results.
.. Open OpenSeesOutput.pvd to look at OpenSees results.

.. .. figure:: figures/Paraview.PNG
..    :align: center
..    :width: 600
..    :figclass: align-center
   
..    This is the model output data as seen from ParaView

.. OpenSees Displacements And Reactions 

.. .. figure:: figures/TipDisplacement.png
..    :align: center
..    :width: 600
..    :figclass: align-center
   
..    This is the model output data as seen from ParaView

.. .. figure:: figures/ReactionForces.png
..    :align: center
..    :width: 600
..    :figclass: align-center
   
..    This is the model output data as seen from ParaView


.. OpenFOAM probe and function object output is available in results/postProcessing/.

.. OpenFOAM output is messy. An example Matlab script is provided in the /src/ directory to post process the OpenFOAM output for this particular case and output. 
.. This file can be modified to work for any case. The names of the data folders will need to be changed according to the name of the probe given in HydroUQ.

.. .. figure:: figures/MatlabScriptCopyToLocation.PNG
..    :align: center
..    :width: 600
..    :figclass: align-center
..     In the /src/ folder in the hdro-0004 folder, an example matlab script is provided to look at time history data of the output probes	
	
	
.. OpenFOAM Calculated Story Forces

.. .. figure:: figures/storyForces.png
..    :align: center
..    :width: 600
..    :figclass: align-center
   
..    Story Forces	
	
.. OpenFOAM Calculated Coupled Interface Forces

.. .. figure:: figures/Forces.png
..    :align: center
..    :width: 600
..    :figclass: align-center
   
..    Forces
 
.. OpenFOAM Calculated Coupled Interface Moments
 
.. .. figure:: figures/Moments.png
..    :align: center
..    :width: 600
..    :figclass: align-center
   
..    Moments

.. OpenFOAM Calculated Pressure Probe Values

.. .. figure:: figures/Pressures.png
..    :align: center
..    :width: 600
..    :figclass: align-center
   
..    Pressures

.. OpenFOAM Calculated Velocity Probe Values

.. .. figure:: figures/Velocities.png
..    :align: center
..    :width: 600
..    :figclass: align-center
..     Velocities


.. OpenFOAM Calculated Free Surface Values 

.. .. figure:: figures/WaveGauges.png
..    :align: center
..    :width: 600
..    :figclass: align-center
   
..    Wave Gauges


.. _hdro-0004-references:

References
----------

[Bonus2025] Justin Bonus, Felix Spröer, Andrew Winter, Pedro Arduino, Clemens Krautwald, Michael Motley, Nils Goseberg (2025). "Tsunami Debris Motion and Loads in a Scaled Port Setting: Comparative Analysis of Three State-of-the-Art Methods Against Experiments." Coastal Engineering. Volume 197. https://doi.org/10.1016/j.coastaleng.2024.104672.



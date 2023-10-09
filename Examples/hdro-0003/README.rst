.. _hydro-0003:

Coupled Digital Twin Example - Simple Cantilevered Cylinder Half-Submerged in Crossflow
============================

Example to demonstrate how to run a coupled OpenSees-OpenFOAM simulation to determine floor loads on a building and then perform
an OpenSees simulation of the building assuming uncertainties in the building properties.

The flume is 1 meter wide (from Y=-0.5m to Y=0.5 m), 1 meter tall (Z=0.0m to Z=1.0m), and 4 meters long (X=0.0m to X=4.0m). 

The case is initialized with a still water level of 0.25 meters. The velocity at the inlet is given a time history boundary condition (src/VelTime.csv). 

This structure is a simple cylinder, with diameter 0.1 meters, located at X=1.5, Y=0.0, Z=0.0. The interface surface file is 'src/interface.stl'. 

The cylinder is represented in OpenSees by a cantilevered beam, with an elastic section, modelled with displacement-action controlled beam elements. The bottom of the cantilevered beam is fixed at Z=0.0.

The constrained node is removed from the coupled solution, by omitting it from the list 'coupledNodes' in the OpenSees model file. 

The length of the cylinder is 0.5 meters. 

The flow around the cylinder is calculated for a given period of time. 

Outputs:
Results for free surface, velocity, and pressure, as well as interface forces and moments and a cut section of the case at a specified interval. 


Overview of case


.. figure:: figures/hdro-0003 example.png
   :align: center
   :width: 600
   :figclass: align-center
    

Probe locations
	
.. figure:: figures/hdro-0003 example probeLoc.png
   :align: center
   :width: 600
   :figclass: align-center
    

Inlet Velocity Time History (U(t))

.. figure:: figures/inletVTH.png
   :align: center
   :width: 600
   :figclass: align-center
    

CASE RUN TIME
---------------

Simulation Time: 1 second on TACC Frontera, 56 processors, 1 node -> Real Time: 1hr, 20 minutes

Submitted
Oct 8, 2023 1:14:37 PM
Finished
Oct 8, 2023 2:34:10 PM

The case can be run for as long as desired, but mind that the longer the case runs, the longer the postprocessing routines will be.

In order to retrieve results from the analysis, the analysis must complete and postprocess the model output files into a VTK format before the end of the allotted submission time. 

Provide a large amount of time for the 'Max Run Time' field in HydroUQ when submitting a job to ensure the model completes before the time allotted runs out!

Be aware that the smaller the OpenFOAM Outputs and OpenSees Outputs 'Time Interval' value is, the longer the post processing of the case will take after analysis has completed, and the larger the results.zip folder will be. 

USE CAUTION WHEN REQUESTING OUTPUT! Only ask for what you need, or you will end up will massive amounts of data.


Post Processing
-------------------------------------------------------------------

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
    Once the job is finished, the output files should be available in the directory which the analysis results were sent to

Find the files by clicking 'View'. 
	
.. figure:: figures/DSToolsAndAppsJobsStatusViewFiles.PNG
   :align: center
   :width: 600
   :figclass: align-center
    Locating this directory is easy. 
	

Move the results.zip to somewhere in My Data/. Use the Extractor tool available on DesignSafe.  Unzip the results.zip folder. 

.. figure:: figures/extractonDS.png
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
	
The results folder should look something like this. 
	
.. figure:: figures/results.png
   :align: center
   :width: 600
   :figclass: align-center
    This is the output of the model
	
Paraview files have a .PVD extension. Open VTK/Fluid.vtm.series to look at OpenFOAM results.
Open OpenSeesOutput.pvd to look at OpenSees results.

.. figure:: figures/Paraview.png
   :align: center
   :width: 600
   :figclass: align-center
    This is the model output data as seen from ParaView


OpenFOAM probe and function object output is available in results/postProcessing/.

OpenFOAM output is messy. An example Matlab script is provided in the /src/ directory to post process the OpenFOAM output for this particular case and output. 
This file can be modified to work for any case. The names of the data folders will need to be changed according to the name of the probe given in HydroUQ.

.. figure:: figures/MatlabScriptCopyToLocation.PNG
   :align: center
   :width: 600
   :figclass: align-center
    In the /src/ folder in the hrdo-0003 folder, an example matlab script is provided to look at time history data of the output probes	
	
	
OpenFOAM Calculated Story Forces

.. figure:: figures/StoryForces.png
   :align: center
   :width: 600
   :figclass: align-center
    Story Forces	
	
OpenFOAM Calculated Coupled Interface Forces

.. figure:: figures/Forces.png
   :align: center
   :width: 600
   :figclass: align-center
    Forces
 
OpenFOAM Calculated Coupled Interface Moments
 
.. figure:: figures/Moments.png
   :align: center
   :width: 600
   :figclass: align-center
    Moments

OpenFOAM Calculated Pressure Probe Values

.. figure:: figures/Pressures.png
   :align: center
   :width: 600
   :figclass: align-center
    Pressures

OpenFOAM Calculated Velocity Probe Values

.. figure:: figures/Velocities.png
   :align: center
   :width: 600
   :figclass: align-center
    Velocities


OpenFOAM Calculated Free Surface Values 

.. figure:: figures/WaveGauges.png
   :align: center
   :width: 600
   :figclass: align-center
    Wave Gauges





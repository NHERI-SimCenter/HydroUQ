.. _lblSimulationApp:

Simulation Applications
=======================

The **simulation application** specifies parameters and executes the script for the response simulation. These parameters may include the integrator scheme, convergence tolerance, step size, etc. of the numerical analysis.
It takes as input the :ref:`BIM file <lblBuildingApp>`, the :ref:`EVENT file <lblEventApp>`, the :ref:`SAM file <lblModelingApp>`, and the :ref:`EDP file <lblEDPApp>`.
After response simulation is completed, the "EDP.json" file is populated with the resulting EDPs and saved in the **simulation working directory**. Note that the "SIM.json" file is not saved in the directory.


.. figure:: _static/images/backendapps_Simulation.png
   :align: center
   :figclass: align-center


The following options for simulation applications vary in the type of finite element program or procedure used for EDPs estimation.


.. rendre:: cli-gallery
   :data-file: $SIMCENTER_DEV/SimCenterBackendApplications/meta/backends.cache.json
   :load-defaults: $SIMCENTER_DEV/SimCenterBackendApplications/meta/index.yaml#/$SIMDOC_APP

   :include-exclusive: %./categories:performSIMULATION



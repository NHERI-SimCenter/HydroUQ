.. _lbl-projsett:

***********************************************
Project settings
***********************************************

The first step is to setup the project as shown in :numref:`EVTSettings`. All of these settings, except ``Simulation type``, are optional. However, setting them makes the future steps easier.

.. _ProjSettings:

.. figure:: figures/Project/ProjSett01.png
   :align: center
   :figclass: align-center
   :height: 400px

   Project settings for ``Hydro`` event

1. **Project name and description**: This is an *optional* parameter primarily meant for the user to identify and differentiate between projects.



2. **Simulation type**: This is *mandatory* and without a selection of the type, no other options can be set. The various simulation types available in ``Hydro`` event are as shown in :numref:`SimType`. The differences between different simulation types are as given below.

   .. _SimType:

   .. figure:: figures/Project/SimulationType.png
      :align: center
      :height: 200px
      :figclass: align-center

      Simulation types available in ``Hydro`` event

   a. **CFD to resolve SW (Using SW results)**: This setting facilitates the user to import solutions from pre-run two-dimensional shallow water solver. The user can select small portions of the shallow-water domain and setup high-fidelity three-dimensional CFD on these selected areas. For example: If one had a GeoClaw simulation for an earthquake on the Alaska fault and one is interested in the inundation in Cresant City, CA (USA). Then, the user can bring in the GeoClaw solutions and resolve the near-coast using a full three-dimensional CFD simulation. 

   b. **CFD using bathymetry data**: This simulation type allows the user to setup a CFD simulation using the geometry defined through the bathymetry data of the ocean floor. 

   c. **CFD using STL file**: This simulation type allows the users to setup the CFD simulation using STL files to define the geometry of the domain.

   d. **CFD of wave flume**: This simulation type allows the user to access the ``Wave Flume Digital Twin``.

3. **Turbulence model**:

   .. _TurbModel:

   .. figure:: figures/Project/TurbSett.png
      :align: center
      :height: 100px
      :figclass: align-center

      Turbulence settings available for ``Hydro`` event

   Hydro-UQ presently supports two different turbulence models as shown in :numref:`TurbModel`. The available options include:

   a. Laminar
   
   b. k-Epsilon

   c. k-Omega SST

   By default, the flow is assumed to be laminar if no turbulence model is selected. More information about the turbulence wall models is available in the technical manual (CFD solvers / Turbulence models). 
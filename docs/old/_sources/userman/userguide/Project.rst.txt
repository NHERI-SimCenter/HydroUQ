.. _lbl-projsett:

***********************************************
Project settings
***********************************************

The first step is to setup the project as shown in :numref:`EVTSettings`. All of these settings, except ``Simulation type``, are optional. However, setting them makes the future steps easier.

.. _ProjSettings:

.. figure:: figures/Project/ProjSett01.png
   :align: center
   :figclass: align-center

   Project settings for ``Hydro`` event

1. **Working directory**: It is recommended to copy all the project files into a particular directory, i.e. the working directory. However, this is *optional*. When file selection is required, the tool will automatically use the working directory as default. The selected directory is shown below the ``Set working directory`` button.

2. **Project name and description**: This is an *optional* parameter primarily meant for the user to identify and differentiate between projects.

.. _SimType:

.. figure:: figures/Project/SimulationType.png
   :align: center
   :height: 200px
   :figclass: align-center

   Simulation types available in ``Hydro`` event

3. **Simulation type**: This is *mandatory* and without a selection of the type, no other options can be set. The various simulation types available in ``Hydro`` event are as shown in :numref:`SimType`. The differences between different simulation types are as given below.

    a. **CFD to resolve SW (Using SW results)**: This setting facilitates the flow to allow the user to import pre-run two-dimensional shallow water solutions. Further, the user can select small areas to run high-fidelity three-dimensional CFD solutions. For example: If one would run a GeoClaw simulation for an earthquake on the Alaska fault and one is interested in the inundation in Cresant City, CA (USA). Then, a GeoClaw simulation can be run for the entire domain up to the coast. Near the coast, the region can be resolved to run a full three-dimensional CFD simulation. 

    b. **CFD to resolve SW (Using SimCenter library)**: This option is not available in ``v1.0.0``. This allows the users to use existing shallow-water solutions that have been run by the SimCenter and collaborators. The user can use these run to select areas of interest for a full CFD simulation.

    c. **CFD using bathymetry data**: This simulation type allows the user to setup a CFD simulation . 

    d. **CFD of wave flume**: This simulation type allows the user to access the ``Wave Flume Digital Twin``.  

    e. **CFD using STL file**: This option is not available in ``v1.0.0``. More details are coming soon.

    f. **CFD using maps**: This option is not available in ``v1.0.0``. More details are coming soon.

    g. **CFD using Surrogate solver**: This option is not available in ``v1.0.0``. More details are coming soon.

   .. _TurbModel:

.. figure:: figures/Project/TurbSett.png
   :align: center
   :height: 100px
   :figclass: align-center

   Turbulence settings available for ``Hydro`` event

3. **Turbulence model**:


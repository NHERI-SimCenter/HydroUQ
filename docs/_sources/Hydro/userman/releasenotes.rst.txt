.. _lbl-release:

***************************
Release Notes
***************************

Version 1.0
=================

Version 1.0.0
----------------

**Release date:** Mar 31st, 2021

#. Supports run on DesignSafe only. Local run on user's desktop is not supported.

#. ``Hydro-UQ v1.0.0`` currently only supports SI (m, kg, s, K) units.

#. Supports two-phase isothermal flows only. Water and air are considered as the two primary phases. However, this can be modified in the material properties to accommodate any other alternative two-phases instead.

#. **Simulation types**:
    a. CFD to resolve SW (Using SW results), CFD using bathymetry data, CFD of wave flume are supported.
    b. CFD to resolve SW (Using SimCenter library), CFD with STL geometry, with maps and surrogate solver are currently not supported in ``v1.0.0``
    c. For simulation type with SW-CFD coupling, ``v1.0.0`` considers one point on the interface. However, more flexibility will be made available in the future versions.
#. **Geometry**: 
    a. Geometry can be imported as Bathymetry files (GeoClaw format - type 1 / 2 / 3). Wave flume geometry is generated using the in-build Hydro-Flume digital twin tool. Import of geometry in STL file format is not supported in ``v1.0.0``
    b. Shallow-water to CFD interface can be imported as a ``.csv`` file only.
    c. Buildings of rectangular / square shapes are supported in ``v1.0.0``. These can be provided in the table or can be generated parametrically. Importing buildings as a ``.csv`` file is not currently supported in ``v1.0.0`` but will be added to upcoming versions. More complicated shapes will be added in the upcoming versions.
    d. Floating bodies are not supported in ``v1.0.0``. Support will be added in upcoming versions.
#. **Meshing**: 
    a. Supports blockMesh and snappyHexMesh for internal meshing
    b. Suports import for the following mesh formats: Ansys Fluent (.msh), Ansys I-DEAS (.ans), CFX mesh (.geo), GAMBIT mesh (.neu), Gmsh mesh (.msh)
    c. Supports import of OpenFOAM / OlaFlow mesh dictionaries, namely the blockMeshDict and snappyHexMeshDict
#. **Materials**: 
    a. Supports Newtonian materials only.
    b. Supports kinematic viscosity and density of the two phases in addition to the surface-tension between the fluids.
#. **Initial conditions**: 
    a. For CFD simulations that resolve the shallow-water solutions, the initial conditions are derived from the shallow-water solutions.
    b. For all other simulation types, the user-specified initial conditions include velocity, pressure and phase. 
#. **Boundary conditions**: 
    a. The boundary conditions can be selected based using standard or mesh-based. Here standard patches include (entry / exit / inlet / outlet / left / right. Mesh-based is based on patch names provided in the STL / mesh-dictionary files used to define the geometry / mesh.
    b. Standard velocity 
    c. Wave maker input conditions are supported for input velocity
    d. Outlet velocity conditions supported are
    e. **TO BE COMPLETED**
#. **Domain decomposition**: 
    a. Allows simple and hierarchial decomposition techniques from OpenFOAM.
    b. Can set start and end times for simulation
    c. Can set time interval and the write intervals
    d. Restarting facility is supported
#. **Turbulence**:
    a. Presently only RANS is supported for turbulence modeling. LES will be added to the upcoming versions. 

Version 1.0.1
----------------

**Release date:** Apr 30th, 2021

Version 1.0.2
----------------

**Release date:** May 31st, 2021

Version 1.0.3
----------------

**Release date:** Jun 30th, 2021

Version 1.0.4
----------------

**Release date:** Jul 31st, 2021

Version 1.0.5
----------------

**Release date:** Aug 31st, 2021
# HydroUQ 

|Build OS|Windows|MacOS|Linux|
|---|---|---|---|
|Status|

### Water-borne Natural Hazards Engineering with Uncertainty Quantification ###

Hydro-UQ app forms a critical aspect of the research simulation tools and workflow aimed at predicting the response of coastal communities prone to water-borne natural hazard events. In particular, the tool aims to provide an open-source and inter-changeable modular framework for modeling of tsunami and storm surge events.

Today, researchers in the areas of tsunami and storm-surge event modeling rely on shallow-water solvers. While shallow-water solver are extremely fast, they do not allow accurate determination of the building response due to wave loading. Alternatively, high-fidelity 3-D CFD simulations are computationally prohibitive for simulation of communities beyond a few buildings. Even with commercial CFD solvers, the geometries of building/bridges that can be modeled is significantly limited. Thus, there is a need for a more coupled solution.

Hydro-UQ (alpha) brings about a coupled modular workflow that interfaces 2-D shallow water solvers with 3-D CFD solvers. The tool allows users to bring in existing 2-D shallow-water solutions and resolve areas of interest using 3-D CFD. Alternatively, SimCenter also provides a shallow-water library from where one can choose from a set of pre-computed solutions. The tool automatically calculates and sets up the boundary conditions at the shallow-water-to-CFD interface. Besides, the users can also add buildings and floating bodies to study the flow fields around them. At present, the tool supports input of data (input/output) from GeoClaw shallow-water solver and support for AdCirc as planned in the future releases. However, owing to the modular nature of the workflow, other solvers can be easily interfaced with. A unique feature of the tool is its ability to model wave flume experiments particularly. Most tsunami/storm-surge tests are conducted in wave flume (like the Oregon wave flume). The tool facilitates direct usage of parameters from the wave flume for simulations. The tool is generic enough to enable simulation using any STL / OBJ CAD files. In the upcoming release, it is also planned to have bathymetry selection using maps.

Such computations can be prohibitively expensive to perform on a user's local computer. The user can quickly set up the calculations remotely on the Stampede2 supercomputer using Agave APIs. Stampede2 is located at the Texas Advanced Computing Center (TACC) and made available to the user through NHERI DesignSafe, the cyberinfrastructure provider for the distributed NSF funded Natural Hazards in Engineering Research Infrastructure (NHERI) facility.

### Important links

- Download the installer from [HydroUQ Research Tool webpage](https://simcenter.designsafe-ci.org/research-tools/hydro-uq)
- Write to us for help and feature requests on [HydroUQ message board](http://simcenter-messageboard.designsafe-ci.org/smf/index.php?board=17.0)
- Help file and documentation from [HydroUQ help pages](https://nheri-simcenter.github.io/HydroUQ)

### Upcoming features

In the upcoming versions, it is planned for the Hydro-UQ to also be interfaced with OpenSees. This will help obtain building response. Other significant features expected in the future releases include:

**(a)	Uncertainty quantification in building response:**

The application is focused on quantifying the uncertainties in the predicted response, given the that the properties of the buildings and the initiation events are not known precisely, and that both the simulation software and the user make simplifying assumptions in the numerical modeling of that structure. In this application, the user is required to characterize the uncertainties in the input. After utilizing the users' selected sampling method, the app will provide information that describes the uncertainties in the computed response measures.

**(b)	Computational speed-up using forward UQ & surrogate models:**

Such models are computationally intensive and not feasible to be run on a standard PC. Thus, this requires the usage of HPC resources and days of computational waiting time. However, owing to the rise of surrogate learning algorithms, models will be trained to make real-time predictions on building responses due to varying initiation conditions.

### How to build HydroUQ?

Coming soon

### Release information

Hydro-UQ is released as an open-source research application under a [BSD 3-Clause License] (https://github.com/NHERI-SimCenter/HydroUQ/blob/master/LICENSE)

### Acknowledgement

This material is based upon work supported by the National Science Foundation under Grant No. 1612843.

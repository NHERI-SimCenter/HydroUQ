# HydroUQ 


[![Build status](https://ci.appveyor.com/api/projects/status/k1cfrfmjsq14akso?svg=true)](https://ci.appveyor.com/project/fmckenna/hydrouq)

### Water-borne Natural Hazards Engineering with Uncertainty Quantification ###

For help and information about using HydroUQ tool or additional feature requests / bug reports, please write to us on the [SimCenter HydroUQ message board](http://simcenter-messageboard.designsafe-ci.org/smf/index.php?board=17.0). 

HydroUQ app forms a critical aspect of the research simulation tools and workflow aimed at predicting the response of coastal communities prone to water-borne natural hazard events. In particular, the tool aims to provide an open-source and inter-changeable modular framework for modeling of tsunami and storm surge events.

Today, researchers in the areas of tsunami and storm-surge event modeling rely on shallow-water solvers. While shallow-water solver are extremely fast, they do not allow accurate determination of the building response due to wave loading. Alternatively, high-fidelity 3-D CFD simulations are computationally prohibitive for simulation of communities beyond a few buildings. Even with commercial CFD solvers, the geometries of building/bridges that can be modeled is significantly limited. Thus, there is a need for a more coupled solution.

HydroUQ (alpha) brings about a coupled modular workflow that interfaces 2-D shallow water solvers with 3-D CFD solvers. The tool allows users to bring in existing 2-D shallow-water solutions and resolve areas of interest using 3-D CFD. Alternatively, SimCenter also provides a shallow-water library from where one can choose from a set of pre-computed solutions. The tool automatically calculates and sets up the boundary conditions at the shallow-water-to-CFD interface. Besides, the users can also add buildings to study the flow fields around them. At present, the tool supports input of data (input/output) from GeoClaw shallow-water solver and support for AdCirc as planned in the future releases. However, owing to the modular nature of the workflow, other solvers can be easily interfaced with.

A unique feature of the tool is its ability to model wave flume experiments particularly using the digital twin module. Most tsunami/storm-surge tests are conducted in wave flume (like the Oregon wave flume). The tool facilitates direct usage of parameters from the wave flume for simulations. The tool is generic enough to enable simulation using any STL CAD files.

The tool also facilitates uncertainty quantification in structural response due to wave loading. Such computations can be prohibitively expensive to perform on a user's local computer. The user can quickly set up the calculations remotely on the Stampede2 supercomputer using Agave APIs. Stampede2 is located at the Texas Advanced Computing Center (TACC) and made available to the user through NHERI DesignSafe, the cyberinfrastructure provider for the distributed NSF funded Natural Hazards in Engineering Research Infrastructure (NHERI) facility.

### Important links

- Download the installer from [HydroUQ Research Tool webpage](https://simcenter.designsafe-ci.org/research-tools/hydro-uq)
- Write to us for help and feature requests on [HydroUQ message board](http://simcenter-messageboard.designsafe-ci.org/smf/index.php?board=17.0)
- Help file and documentation from [HydroUQ help pages](https://nheri-simcenter.github.io/HydroUQ)

### How to build HydroUQ?

Instructions to build HydroUQ is now available in the documentation at [HydroUQ Build Documentation](https://nheri-simcenter.github.io/HydroUQ/Hydro/devman/build.html)

### Release information

HydroUQ is released as an open-source research application under a [BSD 3-Clause License](https://github.com/NHERI-SimCenter/HydroUQ/blob/master/LICENSE)

### Acknowledgement

This material is based upon work supported by the National Science Foundation under Grant No. 1612843.

### Contact

NHERI-SimCenter nheri-simcenter@berkeley.edu \
Ajay B Harish ajaybh@berkeley.edu \
Frank McKenna fmckenna@berkeley.edu

# HydroUQ 


[![Build status](https://ci.appveyor.com/api/projects/status/k1cfrfmjsq14akso?svg=true)](https://ci.appveyor.com/project/fmckenna/hydrouq)

### Water-borne Natural Hazards Engineering with Uncertainty Quantification ###

For help and information about using HydroUQ tool or additional feature requests / bug reports, please write to us on the [SimCenter HydroUQ message board](http://simcenter-messageboard.designsafe-ci.org/smf/index.php?board=17.0). We would be glad to accept feature requests.

The HydroUQ Application is open-source software that provides researchers a tool to assess the performance of a building subjected to wave loading due to tsunami and storm surge. The tool facilitates a multiscale coupling by resolving areas of interest by coupling two-dimensional shallow water solver (GeoClaw) with three-dimensional CFD solver (OpenFOAM) through an interchangeable workflow.

The tool facilitates researchers to consider:

Bathymetry/topography of the ocean floor
Shallow-water solutions as boundary conditions
User-defined buildings
UQ methods like forward propagation, sensitivity and reliability analysis
Building models include MDOF, steel building model and OpenSees models
In addition, the tool specifically allows for modeling of experiments from wave flumes (for example, the [NHERI Experimental Facility at Oregon State University](https://oregonstate.designsafe-ci.org)). The outputs of the HydroUQ include probabilistic building responses, velocities and pressure at any point in the fluid domain.

These simulations are computationally demanding and thus, users have the option to perform the computations on the Stampede2 supercomputer. Stampede2 is located at the Texas Advanced Computing Center and made available to the user through NSF's NHERI DesignSafe, the cyberinfrastructure provider for NHERI.

### Important links

- Download the installer from [HydroUQ Research Tool webpage](https://simcenter.designsafe-ci.org/research-tools/hydro-uq)
- Write to us for help and feature requests on [HydroUQ message board](http://simcenter-messageboard.designsafe-ci.org/smf/index.php?board=17.0)
- Help file and documentation from [HydroUQ help pages](https://nheri-simcenter.github.io/Hydro-Documentation)

### How to build HydroUQ?

Instructions to build HydroUQ is now available in the documentation at [HydroUQ Build Documentation](https://nheri-simcenter.github.io/Hydro-Documentation/Hydro/devman/build.html)

### How to contribute to HydroUQ?

We would be very happy if you are interested in contributing to the HydroUQ project. You can find more information about it on the [HydroUQ Contribution](https://github.com/NHERI-SimCenter/HydroUQ/blob/master/CONTRIBUTING.md)

### Release information

HydroUQ is released as an open-source research application under a [BSD 2-Clause License](https://nheri-simcenter.github.io/Hydro-Documentation/common/front-matter/license.html)

### Acknowledgement

This material is based upon work supported by the National Science Foundation under Grant No. 1612843.

### Contact

NHERI-SimCenter nheri-simcenter@berkeley.edu \
Ajay B Harish ajaybh@berkeley.edu \
Frank McKenna fmckenna@berkeley.edu

# HydroUQ 

[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.10902090.svg)](https://doi.org/10.5281/zenodo.10902090) [![GitHub release](https://img.shields.io/github/v/release/NHERI-SimCenter/HydroUQ)]( [![GitHub license](https://img.shields.io/github/license/NHERI-SimCenter/HydroUQ)]( [![Build status](https://ci.appveyor.com/api/projects/status/k1cfrfmjsq14akso?svg=true)](https://ci.appveyor.com/project/fmckenna/hydrouq)

---

### Water-borne Natural Hazards Engineering with Uncertainty Quantification ###

The HydroUQ Application is an open-source software for simulating the performance of a building subjected to water-borne natural hazards (e.g. tsunamis and hurricane storm surges) while quantifying the uncertainties in the simulation results. HydroUQ supports multiscale coupling by resolving areas of interest by with a two-dimensional shallow water solver (e.g., GeoClaw) and/or a three-dimensional computational fluid dynamics (CFD) solver (e.g., OpenFOAM) and coupling them at an interface. The applications interchangeable workflow allows users to perform uncertainty quantification (UQ) methods like forward propagation, sensitivity and reliability analysis on previously deterministic models. Modular design allows users to drop-in their own building models, event types, engineering demand parameters, and more while maintaining full-workflow UQ capabilities.

### Important Links
- [Download Application](https://www.designsafe-ci.org/data/browser/public/designsafe.storage.community/SimCenter/Software/HydroUQ)
- [Step-by-Step Examples](https://nheri-simcenter.github.io/Hydro-Documentation/common/user_manual/examples/desktop/examples)
- [Documentation & Guides](https://nheri-simcenter.github.io/Hydro-Documentation)
- [Overview Web-Page](https://simcenter.designsafe-ci.org/research-tools/hydro-uq)
- [Forum & Feature Requests](http://simcenter-messageboard.designsafe-ci.org/smf/index.php?board=17.0)

The HydroUQ application is part of the SimCenter library of tools developed by the NHERI SimCenter. 

---

### Capabilities

- Uncertainty quantification (UQ) methods like forward propagation, sensitivity and reliability analysis
- Modeling experiments from wave flume digital twins (for example, the [NHERI Experimental Facility at Oregon State University](https://oregonstate.designsafe-ci.org))
- Bathymetry/topography of the ocean floor
- Shallow-water solutions as boundary conditions
- User-defined buildings for wave loading and structural response
- Design structures including Multi-degree-of-freedom (MDOF) model, steel building model, OpenSees models, and OpenSeesPy models
- Output probabilistic building responses, velocities and pressure at any point in the fluid domain

---

### Download [![Download HydroUQ](https://img.shields.io/badge/Download-HydroUQ-blue)](https://www.designsafe-ci.org/data/browser/public/designsafe.storage.community/SimCenter/Software/HydroUQ)

The HydroUQ desktop application is available for download on Windows and Mac operating systems from the DesignSafe-CI website. [Download Application](https://www.designsafe-ci.org/data/browser/public/designsafe.storage.community/SimCenter/Software/HydroUQ)

---

### Install 

The executable desktop application is available for Windows and Mac operating systems. The installation instructions are available in the [HydroUQ Documentation](https://nheri-simcenter.github.io/Hydro-Documentation/common/user_manual/installation/desktop/installation.html)



---

### Build from Source Code

The HydroUQ application can be built from source code on Windows, Mac, and Linux operating systems. The source code is available in this repository. 

Clone the repository using the following command if the Github CLI is installed on your system:
```
git clone https://github.com/NHERI-SimCenter/HydroUQ.git
```

Otherwise, you can clone the repository on this page by clicking on the green "Code" button and then clicking on "Download ZIP". Extract the downloaded ZIP file to a location on your system.

Instructions on building the HydroUQ application from downloaded source code are available in the [HydroUQ How-To-Build Guide](https://nheri-simcenter.github.io/Hydro-Documentation/common/developer_manual/how_to_build/desktop/how_to_build.html)


---

### Launch Application

The HydroUQ application can be run by executing the `Hydro_UQ` executable file. The instructions to run the HydroUQ application are available in the [HydroUQ Documentation](https://nheri-simcenter.github.io/Hydro-Documentation/common/user_manual/running/desktop/running.html)


---

### Run Application Remotely

3D CFD simulations can be computationally demanding and thus, users have the option to perform the computations on the Frontera, Lonestar6, and Stampede3 supercomputer. Systems are located Texas Advanced Computing Center and made available to the user through NSF's NHERI DesignSafe, the cyberinfrastructure provider for NHERI. 

[Sign-up for a DesignSafe account](https://www.designsafe-ci.org/account/register/) to run HydroUQ simulations remotely.


---

### Try the SimCenter Eco-System

The HydroUQ application is part of the SimCenter library of tools. The SimCenter library of tools is a collection of research applications that are developed by the NHERI SimCenter. The SimCenter library of tools is available for download on the DesignSafe-CI website. The SimCenter library of tools includes the following applications:

- Quantified Uncertainty with Optimization for the Finite Element Method Application (quoFEM)
[quoFEM Download](https://www.designsafe-ci.org/data/browser/public/designsafe.storage.community/SimCenter/Software/quoFEM)  [quoFEM Github](https://github.com/NHERI-SimCenter/quoFEM)
- Earthquake Engineering with Uncertainty Quantification Application (EE-UQ) 
[EE-UQ Download](https://www.designsafe-ci.org/data/browser/public/designsafe.storage.community/SimCenter/Software/EE_UQ)  [EE-UQ Github](https://github.com/NHERI-SimCenter/EE-UQ)
- Wind Engineering with Uncertainty Quantification Application (WE-UQ) 
[WE-UQ Download](https://www.designsafe-ci.org/data/browser/public/designsafe.storage.community/SimCenter/Software/WE_UQ)  [WE-UQ Github](https://github.com/NHERI-SimCenter/WE-UQ)
- Water-Borne Natural Hazards Engineering with Uncertainty Quantification Application (HydroUQ)
[HydroUQ Download](https://www.designsafe-ci.org/data/browser/public/designsafe.storage.community/SimCenter/Software/HydroUQ)  [HydroUQ Github](https://github.com/NHERI-SimCenter/HydroUQ)
- Performance-Based Engineering Application 
[PBE Download](https://www.designsafe-ci.org/data/browser/public/designsafe.storage.community/SimCenter/Software/PBE)  [PBE Github](https://github.com/NHERI-SimCenter/PBE)
- Regional Resilience Determination Application (R2D)
[R2DTool](https://www.designsafe-ci.org/data/browser/public/designsafe.storage.community/SimCenter/Software/R2Dt)  [R2DTool Github](https://github.com/NHERI-SimCenter/R2DTool)


---


### Contribute

We would be very happy if you are interested in contributing to the HydroUQ project. You can find more information about it on the [HydroUQ Contribution](https://github.com/NHERI-SimCenter/HydroUQ/blob/master/CONTRIBUTING.md)

### Release Information

HydroUQ is released as an open-source research application under a [BSD 2-Clause License](https://nheri-simcenter.github.io/Hydro-Documentation/common/front-matter/license.html)

### Acknowledgement

This material is based upon work supported by the National Science Foundation under Grant No. 1612843.

### Contact

Justin Bonus bonusj@uw.edu \
Frank McKenna fmckenna@berkeley.edu \
Ajay B Harish ajay.harish@manchester.ac.uk \
NHERI-SimCenter nheri-simcenter@berkeley.edu 
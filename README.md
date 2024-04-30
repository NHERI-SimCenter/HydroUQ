
<div style="display: flex; justify-content: center;">
    <a href="https://github.com/NHERI-SimCenter/HydroUQ/"><img height="250" src="https://raw.githubusercontent.com/NHERI-SimCenter/HydroUQ/master/icons/NHERI-HydroUQ-Icon.png" align="left" /></a>
    <span style="display:inline-block; width: 50px;"></span>
    <div style="border-left: 2px solid black; height: 250px;"></div>
    <span style="display:inline-block; width: 50px;"></span>
    <div>
        <p> <h1 class="title">HydroUQ - Desktop Application</h1> </p>
        <p> <h2 class="subtitle">Water-borne Natural Hazards Engineering with Uncertainty Quantification </h2> </p>
        <p> <h3 class="subtitle">Developed by the NHERI SimCenter</h3> </p> 
    </div>
</div>

<span style="display:block; height: 20px;"></span>

<div style="border-bottom: 2px solid black; width: 100%; margin-top: 0px;"></div>

<br>

[![Latest Release](https://img.shields.io/github/v/release/NHERI-SimCenter/HydroUQ?color=blue&label=Latest%20Release)](https://github.com/NHERI-SimCenter/HydroUQ/releases/latest) [![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.10902090.svg)](https://doi.org/10.5281/zenodo.10902090) [![Build status](https://ci.appveyor.com/api/projects/status/k1cfrfmjsq14akso?svg=true)](https://ci.appveyor.com/project/fmckenna/hydrouq) [![License](https://img.shields.io/badge/License-BSD%202--Clause-blue)](https://raw.githubusercontent.com/NHERI-SimCenter/HydroUQ/master/LICENSE) [![LinkedIn Follow](https://img.shields.io/badge/@nheri--simcenter-%230077B5.svg?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/company/nheri-simcenter) [![YouTube Subscribe](https://img.shields.io/badge/@DesignSafe-%23FF0000.svg?style=for-the-badge&logo=YouTube&logoColor=white)](https://www.youtube.com/channel/DesignSafe) [![GitHub](https://img.shields.io/badge/@NHERI--SimCenter-%23121011.svg?style=for-the-badge&logo=github&logoColor=white)](https://github.com/NHERI-SimCenter)

<!-- [![Twitter Follow](https://img.shields.io/twitter/follow/NHERISimCenter?style=social)](https://twitter.com/NHERI_SimCenter)  -->

<div style="border-bottom: 2px solid black; width: 100%; margin-top: 0px;"></div>

<br>

<div style="display: flex; justify-content: center;">
  <img src="./images/NHERI_SimCenter_DamBreakAnimation_VelocityPressureVisualized_2.5MParticles_res0.05m_23012023.gif" alt="Dam Break Animation" height="400" />
    <span style="display:inline-block; width: 50px;"></span>
  <img src="./images/HydroUQ_MPM_3DViewPort_OSULWF_2024.04.25.gif" alt="HydroUQ MPM 3D ViewPort OSULWF" height="400" />
</div>

<br>

<div style="border-bottom: 2px solid black; width: 100%; margin-top: 0px;"></div>

# HydroUQ

## Overview

The ``HydroUQ`` desktop application is a free, open-source software for simulating a building's engineering performance with quantified uncertainty during water-borne natural hazard loading (e.g. tsunamis and hurricane storm surges). The application's interchangeable workflow allows users to swap between popular uncertainty quantification methods to apply on previously deterministic models. Further, the modular design lets users drop-in their own building models (SIM), event types (EVT), nonlinear structural analysis (FEM), engineering demand parameters (EDP), and more while maintaining the full-workflow's UQ capabilities. 


## Capabilities

- Drop-in uncertainty quantification (UQ) methods like forward propagation, sensitivity, and reliability analysis onto previously deterministic CFD models using ``SimCenter UQ`` and/or ``Dakota`` backends
- Model experiments from validated wave flume digital twin
    - [NHERI Oregon State University Large Wave Flume](https://oregonstate.designsafe-ci.org) ``OSU LWF`` 
    - [Waseda University Tsunami Wave Basin](https://shibayama.w.waseda.jp/lab_en.html) ``WU TWB`` 
- Bathymetry/topography of the ocean floor and land surface for accurate wave propagation
- Shallow-water solutions (e.g., ``GeoClaw``) as boundary conditions to 3D CFD (e.g., ``OpenFOAM``)
- User-defined buildings for wave loading input and structural response output
- Design structures including Multi-degree-of-freedom (``MDOF``) model, steel building model, ``OpenSees`` models, and ``OpenSeesPy`` models
- Output probabilistic building responses, velocities and pressure at any point in the fluid domain
- Supports multiscale coupling by resolving areas of interest by with a two-dimensional shallow water solver (e.g., ``GeoClaw``) and/or a three-dimensional computational fluid dynamics (CFD) solver (e.g., ``OpenFOAM``) and coupling them at an interface.


## Quick Links

- [Download Application](https://www.designsafe-ci.org/data/browser/public/designsafe.storage.community/SimCenter/Software/HydroUQ)
- [Step-by-Step Examples](https://nheri-simcenter.github.io/Hydro-Documentation/common/user_manual/examples/desktop/examples)
- [Documentation & Guides](https://nheri-simcenter.github.io/Hydro-Documentation)
- [Overview Web-Page](https://simcenter.designsafe-ci.org/research-tools/hydro-uq)
- [Forum & Feature Requests](http://simcenter-messageboard.designsafe-ci.org/smf/index.php?board=17.0)


## Citing HydroUQ

If you use the ``HydroUQ`` application [![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.10902090.svg)](https://doi.org/10.5281/zenodo.10902090) in your research, please cite our as:

```bibtex
@misc{McKennaBonusHarishLewis2024,
  author = {Frank McKenna and Justin Bonus and Ajay Harish and Nicolette Lewis},
  title = {HydroUQ},
  year = {2024},
  month = {4},
  note = {NHERI-SimCenter/HydroUQ: Version 3.1.0 (v3.1.0). Zenodo.},
  url = {https://zenodo.org/records/10902090},
  doi = {10.5281/zenodo.10902090}
}
```

and include the NHERI SimCenter's workflow architecture [![DOI](https://img.shields.io/badge/10.3389--fbuil.2020.558706-blue?label=DOI)](https://www.frontiersin.org/articles/10.3389/fbuil.2020.558706) using:

```bibtex
@Article{Deierlein2020,
  author={Deierlein, Gregory G. and McKenna, Frank and Zsarnóczay, Adam and Kijewski-Correa, Tracy and Kareem, Ahsan and Elhaddad, Wael and Lowes, Laura and Schoettler, Matthew J. and Govindjee, Sanjay},   
  title={A Cloud-Enabled Application Framework for Simulating Regional-Scale Impacts of Natural Hazards on the Built Environment},      
  journal={Frontiers in Built Environment},      
  volume={6},           
  year={2020},      
  url={https://www.frontiersin.org/articles/10.3389/fbuil.2020.558706},       
  doi={10.3389/fbuil.2020.558706},      
  issn={2297-3362},   
}
```

---

## SimCenter Eco-System

The challenges of natural hazards engineering are addressed by the NHERI SimCenter through a suite of applications that provide cutting-edge tools for researchers, practitioners, and stakeholders. The applications are designed to work together to provide a comprehensive solution for natural hazards engineering. A puzzle-piece diagram of the SimCenter ecosystem is shown below:

<a href="https://github.com/NHERI-SimCenter/"><img height="250" src="https://raw.githubusercontent.com/NHERI-SimCenter/HydroUQ/master/images/SimCenter_PuzzlePieces_Horizontal.png" align="left" /></a>

In reality, this is a software workflow representation of the PEER Performance-Based Earthquake Engineering (PBEE) framework that has been extended to include other natural hazards:

<a href="https://github.com/NHERI-SimCenter/"><img height="350" src="https://raw.githubusercontent.com/NHERI-SimCenter/HydroUQ/master/images/SimCenter_PEER_PBE.png" align="left" /></a>

``HydroUQ`` is just one part of the [NHERI SimCenter](https://simcenter.designsafe-ci.org) ecosystem that provides cutting-edge open-source tools for natural hazards engineering. See the hierarchy of the the full ecosystem below:

<a href="https://github.com/NHERI-SimCenter/HydroUQ/"><img height="450" src="https://raw.githubusercontent.com/NHERI-SimCenter/HydroUQ/master/images/SimCenter_Hierarchy.png" align="left" /></a>

All applications are free, open-source, and available for download:

<style>
  table {
    border-collapse: collapse;
    border: none;
  }
  th {
    border: none !important;
    border-collapse: collapse;
    background-color: #C0C0C0;
    border-top: none;
    border-bottom: none;
    border-left: none;
    border-right: none;
  }
  tr {
    border-top: 1px solid black;
  }
  tr:nth-child(9n) {
    background-color: #f2f2f2;
  }
  tr:nth-child(even) {
    background-color: #f9f9f9;
  }
  tr:first-child {
    border-top: 1px solid black;
  }
  td {
    border: none !important;
  }
</style>


| Application | Full Title | Download | GitHub | Version |
|:-----------:|:-----------|:--------:|:------:|:-------:|
| ``quoFEM`` | Quantified Uncertainty with Optimization for the Finite Element Method Application | [![Download quoFEM](https://img.shields.io/badge/Download-quoFEM-blue)](https://www.designsafe-ci.org/data/browser/public/designsafe.storage.community/SimCenter/Software/quoFEM) | [![GitHub quoFEM](https://img.shields.io/badge/github-%23121011.svg?style=for-the-badge&logo=github&logoColor=white)](https://github.com/NHERI-SimCenter/quoFEM) |  [![GitHub Latest Release](https://img.shields.io/github/v/release/NHERI-SimCenter/quoFEM)]() |
| ``EE-UQ`` | Earthquake Engineering with Uncertainty Quantification Application | [![Download EE-UQ](https://img.shields.io/badge/Download-EE--UQ-blue)](https://www.designsafe-ci.org/data/browser/public/designsafe.storage.community/SimCenter/Software/EE_UQ) | [![GitHub EE-UQ](https://img.shields.io/badge/github-%23121011.svg?style=for-the-badge&logo=github&logoColor=white)](https://github.com/NHERI-SimCenter/EE-UQ) | [![GitHub Latest Release](https://img.shields.io/github/v/release/NHERI-SimCenter/EE-UQ)]() |
| ``WE-UQ`` | Wind Engineering with Uncertainty Quantification Application | [![Download WE-UQ](https://img.shields.io/badge/Download-WE--UQ-blue)](https://www.designsafe-ci.org/data/browser/public/designsafe.storage.community/SimCenter/Software/WE_UQ) | [![GitHub WE-UQ](https://img.shields.io/badge/github-%23121011.svg?style=for-the-badge&logo=github&logoColor=white)](https://github.com/NHERI-SimCenter/WE-UQ)  | [![GitHub Latest Release](https://img.shields.io/github/v/release/NHERI-SimCenter/WE-UQ)]() |
| ``HydroUQ`` | Water-Borne Natural Hazards Engineering with Uncertainty Quantification Application | [![Download HydroUQ](https://img.shields.io/badge/Download-HydroUQ-blue)](https://www.designsafe-ci.org/data/browser/public/designsafe.storage.community/SimCenter/Software/HydroUQ) | [![GitHub HydroUQ](https://img.shields.io/badge/github-%23121011.svg?style=for-the-badge&logo=github&logoColor=white)](https://github.com/NHERI-SimCenter/HydroUQ)  | [![GitHub Latest Release](https://img.shields.io/github/v/release/NHERI-SimCenter/HydroUQ)]() |
| ``PBE`` | Performance-Based Engineering Application | [![Download PBE](https://img.shields.io/badge/Download-PBE-blue)](https://www.designsafe-ci.org/data/browser/public/designsafe.storage.community/SimCenter/Software/PBE) | [![GitHub PBE](https://img.shields.io/badge/github-%23121011.svg?style=for-the-badge&logo=github&logoColor=white)](https://github.com/NHERI-SimCenter/PBE) | [![GitHub Latest Release](https://img.shields.io/github/v/release/NHERI-SimCenter/PBE)]() |
| ``R2D`` | Regional Resilience Determination Application | [![Download R2D](https://img.shields.io/badge/Download-R2D-blue)](https://www.designsafe-ci.org/data/browser/public/designsafe.storage.community/SimCenter/Software/R2Dt) | [![GitHub R2D](https://img.shields.io/badge/github-%23121011.svg?style=for-the-badge&logo=github&logoColor=white)](https://github.com/NHERI-SimCenter/R2DTool) | [![GitHub Latest Release](https://img.shields.io/github/v/release/NHERI-SimCenter/R2DTool)]() |



---

## Getting Started

The ``HydroUQ`` application can be [downloaded](https://www.designsafe-ci.org/data/browser/public/designsafe.storage.community/SimCenter/Software/HydroUQ), [installed](https://img.shields.io/badge/Install-HydroUQ-blue) (https://nheri-simcenter.github.io/Hydro-Documentation/common/user_manual/installation/desktop/installation.html), [built](https://nheri-simcenter.github.io/Hydro-Documentation/common/developer_manual/how_to_build/desktop/how_to_build.html), and [launched](https://nheri-simcenter.github.io/Hydro-Documentation/common/user_manual/running/desktop/running.html) on Windows, Mac, and Linux operating systems. With a [free DesignSafe account](https://www.designsafe-ci.org/account/register/), users can run HydroUQ simulations remotely on powerful supercomputers including the ``Frontera``, ``Lonestar6``, and ``Stampede3`` systems.



### Download HydroUQ

The ``HydroUQ`` desktop application is available for download on Windows and Mac operating systems from the DesignSafe-CI website at the [HydroUQ Download Link](https://www.designsafe-ci.org/data/browser/public/designsafe.storage.community/SimCenter/Software/HydroUQ)


### Install HydroUQ

[![Install HydroUQ](https://img.shields.io/badge/Install-HydroUQ-blue)](https://nheri-simcenter.github.io/Hydro-Documentation/common/user_manual/installation/desktop/installation.html)

The ``HydroUQ`` executable desktop application is available for Windows and Mac operating systems. The installation instructions are available in the [HydroUQ Documentation](https://nheri-simcenter.github.io/Hydro-Documentation/common/user_manual/installation/desktop/installation.html)



### Build HydroUQ

The ``HydroUQ`` application can be built from source code on Windows, Mac, and Linux operating systems. The source code is available in this repository. 

Clone the repository using the following command if the Github CLI is installed on your system:
```
git clone https://github.com/NHERI-SimCenter/HydroUQ.git
```

Otherwise, you can clone the repository on this page by clicking on the green "Code" button and then clicking on "Download ZIP". Extract the downloaded ZIP file to a location on your system.

Instructions on building the HydroUQ application from downloaded source code are available in the [HydroUQ How-To-Build Guide](https://nheri-simcenter.github.io/Hydro-Documentation/common/developer_manual/how_to_build/desktop/how_to_build.html)


### Launch HydroUQ

The ``HydroUQ`` application can be run by executing the ``Hydro_UQ`` executable file. The instructions to run the HydroUQ application are available in the [HydroUQ Documentation](https://nheri-simcenter.github.io/Hydro-Documentation/common/user_manual/running/desktop/running.html)



### Run HydroUQ Remotely

Users with a free DesignSafe account can use the `HydroUQ` desktop app to launch a remote job to run simulations on powerful supercomputers with ease.

[Sign-up for DesignSafe](https://www.designsafe-ci.org/account/register/)

Available systems are the ``Frontera``, ``Lonestar6``, and ``Stampede3`` supercomputers. Systems are located at the Texas Advanced Computing Center (TACC) and made available to the user through NSF's NHERI DesignSafe-CI, the cyberinfrastructure provider for NHERI. 


---

## Get Involved

``HydroUQ`` is an open-source project developed for practitioners, researchers, students, and stakeholders by our team of experts at the NHERI SimCenter. We welcome contributions from the community to help improve the application and add new features.


### Contributing to HydroUQ

Interested in contributing to the HydroUQ project? Find out how in the [HydroUQ Contribution Guide](https://github.com/NHERI-SimCenter/HydroUQ/blob/master/CONTRIBUTING.md).



### Contact Us

Message us on the [SimCenter Message Board](http://simcenter-messageboard.designsafe-ci.org/smf/index.php?board=17.0) for any questions, feature requests, or issues.

| Developer | Email | Role |
|:----|:-----|:----|
| Justin Bonus | bonus@berkeley.edu | [![Email](https://img.shields.io/badge/Main%20Dev-blue)](mailto:bonus@berkeley.edu) | 
| Frank McKenna | fmckenna@berkeley.edu | [![Email](https://img.shields.io/badge/Senior%20Dev-blue)](mailto:fmckenna@berkeley.edu) | 
| Ajay Harish | ajay.harish@manchester.ac.uk | [![Email](https://img.shields.io/badge/Former%20Dev-blue)](mailto:ajay.harish@manchester.ac.uk) |
| NHERI SimCenter | nheri-simcenter@berkeley.edu | [![Email](https://img.shields.io/badge/SimCenter-blue)](mailto:nheri-simcenter@berkeley.edu) |


### Sign-up for Updates

Stay up-to-date with the latest news, updates, and releases with the [NHERI Newsletter](https://4407eb04.sibforms.com/serve/MUIEAIae4IGtEQHh04xSx9x2pNIIb4m-IjUaN83IpiIrwDW4CtpySmL9ec5ASFjgZSBYRNfgSLwXl1B8sLFSgVYB3Hc2JJP6ORmrNoj9ouHNiX8zAZVmsM1_A18STCEKs3cRP6OXJZGdvUfR7PZd5G0VN_DKVhibD3g9aRAWY7wkEfrCVeJnclbaTXMV8YuGf0KFMZQxOntb5M7Z) and the [SimCenter Newsletter](https://simcenter.designsafe-ci.org/survey/?_gl=1*1mn7c1n*_ga*MTMxNzc2NjI2MC4xNzA5MDIyOTAx*_ga_D96RT1T24K*MTcxNDQ0NDAwOS4xNC4xLjE3MTQ0NDU4NzAuMC4wLjA) newsletters.



---

## Release License
[![License](https://img.shields.io/badge/License-BSD%202--Clause-blue)](https://raw.githubusercontent.com/NHERI-SimCenter/HydroUQ/master/LICENSE)

HydroUQ is released as an open-source research application under a [BSD 2-Clause License](https://nheri-simcenter.github.io/Hydro-Documentation/common/front-matter/license.html)



## Acknowledgement


This material is based upon work supported by the National Science Foundation under Grant [No. 1612843](https://www.nsf.gov/awardsearch/showAward?AWD_ID=1612843) and [No. 2131111](https://www.nsf.gov/awardsearch/showAward?AWD_ID=2131111). Any opinions, findings, conclusions or recommendations expressed in this material are those of the author(s) and do not necessarily reflect the views of the U.S. National Science Foundation.

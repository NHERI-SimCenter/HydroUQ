---
title: 'CFD Notebooks: Learning OpenFOAM for HPC'
tags:
- Python
- CFD
- OpenFOAM
- numerical methods
- finite differences
authors:
- name: Ajay B. Harish
  orcid: 0000-0001-5234-7047
  affiliation: "1, 2"
- name: Sanjay Govindjee
  orcid: 0000-0003-0711-3633
  affiliation: "1, 2"
- name: Frank McKenna
  affiliation: 2

affiliations:
- name: Department of Civil and Environmental Engineering, University of California, Berkeley, CA (USA)
  index: 1
- name: NHERI SimCenter, University of California, Berkeley, CA (USA)
  index: 2
date: 18 Jun 2021
bibliography: paper.bib
---

# Introduction

The **HydroUQ** is an open-source cloud-based application that provides researchers a tool to assess the performance of a building or specimen subjected to wave loading during natural hazard events, namely tsunami and storm surge. The recent works in the area of natural hazards, in review [@StateArtRepo2021],  software overviews [@SCPaper2020] and research needs and challenges [@RAPID2020], discuss the need for high-difelity tools to better characterize the hazard events and their impact on the urban environment. The disaster reconnaissance investigations of previous events have provided ways to understand and improve the scientific understanding of these extreme events. However, the grand challenge of being able to model hazards to determine the probabilistic


The tool facilitates a multiscale coupling by resolving areas of interest by coupling two-dimensional shallow water solver (GeoClaw) with three-dimensional CFD solver (OpenFOAM) through an interchangeable workflow.

The tool facilitates researchers to consider:

Bathymetry/topography of the ocean floor
Shallow-water solutions as boundary conditions
User-defined buildings
UQ methods like forward propagation, sensitivity and reliability analysis
Building models include MDOF, steel building model and OpenSees models
In addition, the tool specifically allows for modeling of experiments from wave flumes (for example, the NHERI Experimental Facility at Oregon State University). The outputs of the HydroUQ include probabilistic building responses, velocities and pressure at any point in the fluid domain.

These simulations are computationally demanding and thus, users have the option to perform the computations on the Stampede2 supercomputer. Stampede2 is located at the Texas Advanced Computing Center and made available to the user through NSF's NHERI DesignSafe, the cyberinfrastructure provider for NHERI.




is a set of Jupyter notebooks aimed at senior undergraduate and early graduate students interested in learning OpenFOAM. It aims to allow the learner to get started with the open-source CFD tool OpenFOAM and run it on Designsafe. It provides a foundation for all aspects of OpenFOAM, from running cases to programming, so it is useful to both new users and existing users wishing to broaden their basic knowledge of OpenFOAM. The learners are exposed to running exercises and simulating OpenFOAM cases using an HPC computing platform, accessed directly through the Jupyter notebook. The Jupyter notebooks consist of video tutorials, DIY examples, and general reading materials. This learning tool is truly platform-independent and leverages the power of HPC. At present, CFD Notebooks are hosted and uses Designsafe's supercomputing infrastructure at the Texas Advanced Computing Center, particularly the Stampede2 and Frontera clusters.

The notebooks are broken up into various editions, each with four lessons: Beginner / Intermediate / Expert / Professional. At present, only the beginner edition is available. The beginner edition of the notebook includes four lessons:

* Lesson 1 (Introduction to OpenFOAM and Designsafe): Introduces the learner to the basic structure of OpenFOAM and Designsafe cyberinfrastructure. 

* Lesson 2 (Different solvers in OpenFOAM and which to use?): Helps learners identify different types of solvers in OpenFOAM (laminar vs. turbulent; steady-state vs. transient).

* Lesson 3 (Boundary conditions in OpenFOAM): While the number of boundary conditions is several, the lesson introduces the learner to the basic boundary conditions and their meaning.

* Lesson 4 (Meshing in OpenFOAM (blockMesh)): The lesson introduces the learner to blockMesh utility basics in OpenFOAM.

Additionally, CFD-Notebooks are accompanied by an extensive theoretical [documentation](https://nheri-simcenter.github.io/CFD-Notebooks/) and [user forum](http://simcenter-messageboard.designsafe-ci.org/smf/index.php?board=11.0) to provide hands-on support.

# Statement of need



There are several tutorials available on Youtube, particularly concerning the usage of OpenFOAM for CFD. The CFD Notebooks are not an alternative to these video tutorials but as a complementary to the conventional classroom and online Computational Fluid Dynamics (CFD) courses like ''CFD Python: the 12 steps to Navier-Stokes equations'' [@Barba2019]; and computational fluid mechanics textbooks [@moukalled2015]. The most attractive aspect of the CFD Notebooks is its interface with HPC facilities that are often unavailable with other tutorials and tools.

Today, OpenFOAM is one of the widely used open-source tools for CFD modeling and simulation and in this regard. While the documentation is comprehensive, most often forums like [CFD Online](https://www.cfd-online.com/) and [Quora](https://www.quora.com) are widely used to get personalized help and support. However, despite the several tutorials available out there, CFD Notebooks emphasizes a structured module to help students learn OpenFOAM in a coherent and orderly fashion. This includes hands-on help through the [user forum](http://simcenter-messageboard.designsafe-ci.org/smf/index.php?board=11.0). 

The module is broken into multiple sections as beginner/intermediate/expert, and thus, it caters to all categories of learners. At present, only the beginner section is published and only caters to beginner users. However, as an open-source educational tool, this provides a foundation and structure to solicit contributions for newer updated modules from the community as well, alongside our own development.

Most importantly, OpenFOAM simulations are, most often, prohibitively expensive to perform on a user’s local computer. However, it is hard for many student users to access HPC facilities, particularly command-line access (CLI) that provides full flexibility to use OpenFOAM. CFD Notebooks are seamlessly integrated to facilitate the learners to perform the computations remotely on the Teas Advanced Computing Center (TACC) supercomputing facility. The CFD Notebooks users have access to the Stampede and Frontera clusters of the TACC through a Designsafe account. Today, Stampede and Frontera are among the top 20 supercomputers in the world. The access to the [Texas Advanced Computing Center (TACC)](https://www.tacc.utexas.edu) is made available to the user through [NHERI DesignSafe](https://www.designsafe-ci.org), the cyberinfrastructure provider for the distributed NSF funded Natural Hazards in Engineering Research Infrastructure (NHERI) facility. Designsafe automatically provides 50GB of storage and 2000 node hours for all registered users. This is roughly equivalent to the use of a single processor core for one year. However, researchers and teachers in US institutions can request higher allocations. They can be allocated up to 100,000 node-hours and 100TB and 1TB, respectively, contingent on a positive review of their needs. The additional allocation is also possible for non-US researchers through a collaborative project with a US-based PI. Additionally, Designsafe also allows easy access to data through cloud storage (Box / Dropbox / Google drive), making it easy to copy case directories and results to and from the HPC facility. CFD Notebooks helps learners of OpenFOAM to leverage this access to HPC resources. 

Fluid mechanics form a part of the core curriculum for both mechanical and aerospace engineers. However, civil engineering students have much less exposure to fluid mechanics and particularly CFD. However, CFD is a critical aspect of several areas related to civil and geotechnical engineering like modeling water/wind/fire borne natural hazards. This module addresses this need for easier access to fluid mechanics tools and HPC for civil engineering students, particularly those interested in natural hazards engineering. The developed module is funded through the NSF NHERI to ensure that this is a stepping stone to use CFD-based research tools like [Hydro-UQ](https://simcenter.designsafe-ci.org/research-tools/hydro-uq/), [WE-UQ](https://simcenter.designsafe-ci.org/research-tools/we-uq/), etc.

# Features and design

THE CFD Notebooks are a series of Jupyter notebooks that include video tutorials, DIY examples, and exercises. Furthermore, sample problems are also provided on the [documentation](https://nheri-simcenter.github.io/CFD-Notebooks/) site.

Four primary aspects facilitate the learner to access and use OpenFOAM on DesignSafe. This starts with login and authentication. Designsafe account acts as authentication to access the HPC resources at TACC. This is achieved through an Agave API client. 

```python
from agavepy.agave import Agave
ag = Agave.restore()
ag.profiles.get()
```

Once authenticated, the learners can access all the apps and software available for public users on TACC. TACC classifies software (or `apps`) as `public` and `private`. `private` refers to the custom `apps` created by users and can be accessed only if permitted by the user who has created it. In contrast, `public` refers to those that are accessible to all users. The learners can access the list of `apps` and choose the particular version of OpenFOAM of interest. This reduces the requirement to install OpenFOAM on the local computer and facilitates access to the same version anytime. This is achieved again through the Agave API client's usage, which loads the OpenFOAM version of interest.

```python
ag.apps.list()
app = ag.apps.get(appId = 'openfoam-7.0u3')
app.parameters

```

Once the OpenFOAM version of interest is loaded, the job parameters can be provided in a JSON format shown below. This helps TACC HPC automatically generate a runtime script to submit, run, and facilitate the job.

```python
jobdetails = {
	"name": "OpenFOAM-Demo", #Name of job
	"appId": "openfoam-7.0u3", #OpenFOAM version to be used
	"maxRunTime": "00:02:00", #Clock time to run the job
	"nodeCount": 1, #Number of nodes
	"processorsPerNode": 1, #Number of processors (Max 64 per node)
	"archive": True, #To add results to archive folder
	"archiveSystem": "designsafe.storage.default",
	"parameters": {
        "mesh": "On", #Use blockMesh or snappyHexMesh?
        "decomp": "Off", #Use parallelization?
        "solver": "simpleFoam" #Solver to be used?
    },
	"inputs": {
		"inputDirectory": "agave://designsafe.storage.published// \
                       PRJ-2915/examples/pitzDaily" 
                      #Where are the care directories located?
		}
}
job = ag.jobs.submit(body=jobdetails)
```

The OpenFOAM simulation can be monitored both on the [Designsafe-ci](https://www.designsafe-ci.org/) dashboard or through the CFD Jupyter Notebook. Using the status commands, it can be easily determined with a job has been `QUEUED`, `ACCEPTED`, `RUNNING` or `COMPLETED`.

```python
from agavepy.async import AgaveAsyncResponse
asrp = AgaveAsyncResponse(ag,job)
asrp.status
```


# Conclusions

HydroUQ provides a novel architecture for the hazards engineering community to 

# Acknowledgements

The SimCenter was financially supported by the National Science Foundation under Grant CMMI-1612843. Any opinions, findings, and conclusions or recommendations expressed in this material are those of the authors and do not necessarily reflect the views of the National Science Foundation. We would like to acknowledge (1) the contributions and collaboration with many faculty, post-doctoral researchers, students and staff who have contributed to the SimCenter’s work, and (2) the support and close collaboration with DesignSafe, which facilitates access to high-performance computing and information technologies for SimCenter tools.

# References

.. _lbl-about:

About
=========

Hydro-UQ is an open-source research application available at `Hydro-UQ Github page <https://github.com/NHERI-SimCenter/HydroUQ>`_, and released under a **BSD Clause 2** license. The Hydro-UQ app is used to predict the response of a building and/or community(ies) subjected to water-borne hazard events. The application aims to help researchers to:

* Couple shallow-water solvers with high-fidelity 3D CFD solvers
* Use CFD solvers to resolve shallow-water solutions
* Obtain inundation heights during tsunami and storm surges scenarios
* Determine velocity and flow conditions around buildings and communities
* Obtain building response through coupling with OpenSees
* Use surrogate models to quantify uncertainity 
* Use forward UQ to develop lightning quick CFD solutions

.. figure:: images/Hydro_UQ_01.png
    :width: 400px
    :align: center
    :alt: alternate text
    :figclass: align-center

This is an open-source research application, which is available at `Hydro-UQ Github page <https://github.com/NHERI-SimCenter/HydroUQ>`_, is released under a **BSD Clause 2** license. The Hydro-UQ app can be used to predict the response of a building and/or communitiy(ies) subjected to water-borne hazard events. The application is focused on quantifying the uncertainties in the predicted response, given the that the properties of the buildings and the initiation events are not known exactly, and that both the simulation software and the user make simplifying assumptions in the numerical modeling of that structure. In this application, the user is required to characterize the uncertainties in the input. The application will, after utilizing the users selected sampling method, provide information that characterizes the uncertainties in the computed response measures. As the computations to make these determinations can be prohibitively expensive to perform on a user’s local computer, the user has the option to perform the computations remotely on the Stampede2 supercomputer. Stampede2 is located at the Texas Advanced Computing Center (TACC) and made available to the user through NHERI DesignSafe, the cyberinfrastructure provider for the distributed NSF funded Natural Hazards in Engineering Research Infrastructure (NHERI) facility.

The computations are performed, as will be discussed in Technical Manual, in a workflow application. That is, the numerical simulations are actually performed by a number of different applications. The Hydro-UQ app backend software runs these different applications for the user, taking the outputs from some programs and providing them as inputs to others. The design of the Hydro-UQ app application is such that researchers are able to modify the backend application to utilize their own application in the workflow computations. This will ensure researchers are not limited to using the default applications we provide and will be enthused to provide their own applications for others to use.

This document covers Alpha Version 0.1 of the tool. Users are encouraged to comment on what additional features and capabilities they would like to see in this application. These requests and feedback can be submitted through the `Message Board <https://simcenter-messageboard.designsafe-ci.org/smf/index.php?board=6.0>`_ we greatly appreciate any input you have. If there are features you want, chances are many of your colleagues also would benefit from them. Users are encouraged to review **REQUIREMENTS** to see what features are planned for this application.


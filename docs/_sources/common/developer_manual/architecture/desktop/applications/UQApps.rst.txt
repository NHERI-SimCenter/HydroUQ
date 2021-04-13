.. _lblUQApp:

UQ Applications
===============

The **UQ application** is used to sample *random variables* (RV) specified in any of the workflow steps (Event, Modeling, EDP, Simulation) for the purpose of uncertainty quantification, then to run commands written in the **driver file** which call on the backend applications to execute the R2D Workflow.
It first populates values for the RVs, sampled from specified probability distributions, in the corresponding files (EVENT.json, SAM.json, EDP.json, SIM.json) for each simulation before executing the workflow.
If no RVs are specified, then the UQ application directly runs commands in the driver file without random sampling.


.. figure:: _static/images/backendapps_UQ.png
   :align: center
   :figclass: align-center


The following options for UQ applications vary in the software package used to perform uncertainty quantification.


.. rendre:: cli-gallery
   :data-file: $SIMCENTER_DEV/SimCenterBackendApplications/meta/backends.cache.json
   :load-defaults: $SIMCENTER_DEV/SimCenterBackendApplications/meta/index.yaml#/$SIMDOC_APP

   :include-exclusive: %./categories:performUQ



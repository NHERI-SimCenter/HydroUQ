.. _lblDLApp:

DL Applications
===============

The **DL application** performs the damage and loss assessment for the buildings subject to the regional event(s).
It takes as input the building properties used for determining damages and losses (e. g. building occupancy, structure type, replacement cost, number of stories),
specified in the :ref:`BIM file <lblBuildingApp>`, as well as the response simulation output recorded in the :ref:`EDP file <lblEDPApp>`.
It returns damage probabilities in a "DM.csv" file and decision variable estimates in a "DV.csv" for each simulation, saved in its corresponding
**simulation working directory**.


.. figure:: _static/images/backendapps_DL.png
   :align: center
   :figclass: align-center


The following options for DL applications vary in the software package used to perform the damage and loss assessment.



.. rendre:: cli-gallery
   :data-file: $SIMCENTER_DEV/SimCenterBackendApplications/meta/backends.cache.json
   :load-defaults: $SIMCENTER_DEV/SimCenterBackendApplications/meta/index.yaml#/$SIMDOC_APP

   :include-exclusive: %./categories:performDL


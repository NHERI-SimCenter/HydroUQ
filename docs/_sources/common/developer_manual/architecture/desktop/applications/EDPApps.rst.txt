.. _lblEDPApp:

EDP Applications
================

The **EDP application** specifies the types of *engineering demand parameters* (EDP) expected as output from the response simulation.
It determines the EDP type from building properties in the :ref:`BIM file <lblBuildingApp>`, the type of event in the :ref:`EVENT file <lblEventApp>`, and the model information from the :ref:`SAM file <lblModelingApp>`.
It writes the type, location, and direction (DOF) of each EDP for a simulation in an ``EDP.json`` file in, located in its corresponding **simulation working directory**.
Note that in the EDP file, DOF=1,2 are assumed to correspond to perpendicular horizontal directions, and DOF=3 corresponds to the vertical direction.


.. figure:: _static/images/backendapps_EDP.png
   :align: center
   :figclass: align-center



The following options for EDP applications vary in the type of EDPs identified for the simulation output.



.. rendre:: cli-gallery
   :data-file: $SIMCENTER_DEV/SimCenterBackendApplications/meta/backends.cache.json
   :load-defaults: $SIMCENTER_DEV/SimCenterBackendApplications/meta/index.yaml#/$SIMDOC_APP

   :include-exclusive: %./categories:createEDP




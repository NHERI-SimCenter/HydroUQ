.. _lblBuildingApp:

Building Applications
=====================


The **building application** creates *building information model* (BIM) files for each building. It takes as input the range of asset IDs selected for simulation (expressed as "min" and "max" ID, specified in the :ref:`configuration file <lblUserDefInputs>`) and the building-specific parameters for each simulation (specified in the :ref:`building source file <lblUserDefInputs>`).
The inputs are parsed into ``#-BIM.json`` files in the **results** folder.

.. figure:: _static/images/backendapps_Building.png
   :align: center
   :figclass: align-center


The following options for building applications vary in the file type of the input building source file it processes.



.. rendre:: cli-gallery
   :data-file: $SIMCENTER_DEV/SimCenterBackendApplications/meta/backends.cache.json
   :load-defaults: $SIMCENTER_DEV/SimCenterBackendApplications/meta/index.yaml#/$SIMDOC_APP

   :include-exclusive: %./categories:createBIM

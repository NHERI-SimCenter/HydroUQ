.. _lblbackendApps:


.. 
    .. _term1:: component applications


*********************
Backend Applications
*********************


The backend applications are categorized by function into the following workflow |term1| which create and populate *intermediate files* used to propagate information from one component application to the next. The |term1| and their intermediate files are as follows:


.. |term1| replace:: modules


.. |createBIM| replace:: :ref:`Building Applications <lblBuildingApp>` - create the BIM files for every building asset, containing building properties.

.. |performRegionalMap| replace:: :ref:`Regional Mapping Applications <lblRegionalMapApp>` - map an intensity measure (IM) or time series for the hazard event to each building asset site.

.. |createEVENT| replace:: :ref:`Event Applications <lblEventApp>` - create the EVENT files for every building asset, containing loads corresponding to the hazard event(s).

.. |createSAM| replace:: :ref:`Modeling Applications <lblmodelingApp>` - create the Structural Analysis Model (SAM) files for every building asset, containing structural model parameters.

.. |createEDP| replace:: :ref:`Engineering Demand Parameter (EDP) Applications <lblEDPApp>` - create the EDP files for every building asset, containing expected response outputs of the structural model.

.. |performSIMULATION| replace:: :ref:`Simulation (SIM) Applications <lblSimulationApp>` - create the SIM files for every building asset, containing analysis settings for response simulation.

.. |performUQ| replace:: :ref:`Uncertainty Quantification (UQ) Applications <lblUQApp>` - execute all steps in the workflow, with the option to quantify uncertainty with experiments using random variables.

.. |performDL| replace:: :ref:`Damage and Loss (DL) Applications <lblDLApp>` - estimate expected damages and losses from the EDP application's output.


.. only:: quoFEM_app
    
    .. toctree::
        :maxdepth: 1

        applications/preprocFEM
        applications/preprocUQ


.. only:: WEUQ_app

    #. |createEVENT|
    #. |createSAM|
    #. |createEDP|
    #. |performSIMULATION|
    #. |performUQ|

    .. toctree::
        :maxdepth: 1
        :hidden:

        applications/eventApps
        applications/modelingApps
        applications/EDPApps
        applications/simulationApps
        applications/UQApps


.. only:: EEUQ_app

    #. |createEVENT|
    #. |createSAM|
    #. |createEDP|
    #. |performSIMULATION|
    #. |performUQ|

    .. toctree::
        :maxdepth: 1
        :hidden:

        applications/eventApps
        applications/modelingApps
        applications/EDPApps
        applications/simulationApps
        applications/UQApps


.. only:: PBE_app

    #. |createBIM|
    #. |createEVENT|
    #. |createSAM|
    #. |createEDP|
    #. |performSIMULATION|
    #. |performUQ|
    #. |performDL|

    .. toctree::
        :maxdepth: 1
        :hidden:

        applications/buildingApps
        applications/eventApps
        applications/modelingApps
        applications/EDPApps
        applications/simulationApps
        applications/UQApps
        applications/DLApps


.. only:: R2D_app

    #. |createBIM|
    #. |performRegionalMap|
    #. |createEVENT|
    #. |createSAM|
    #. |createEDP|
    #. |performSIMULATION|
    #. |performUQ|
    #. |performDL|
    
    .. toctree::
        :maxdepth: 1
        :hidden:

        applications/buildingApps
        applications/regionalMapApps
        applications/eventApps
        applications/modelingApps
        applications/EDPApps
        applications/simulationApps
        applications/UQApps
        applications/DLApps


These applications make up the "backbone" of SimCenter workflow systems, with each one calling on a different subset of the component applications.

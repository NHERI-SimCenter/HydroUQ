.. _lblhurricaneAssessment_2:


*********************
Hurricane Assessment
*********************

This example is a small-scale regional hurricane risk assessment which performs damage/loss estimation for a group of 20 wood buildings in Atlantic City under the Sandy Storm. The buildings are subject to two types of hazards: wind, measured by peak wind speed (PWS), and flooding, measured by flood water depth (FWD). This example does not use response simulation; rather, an **IMasEDP** application translates the IMs directly to the DL application and uses IM-based component fragility functions to estimate damage.
The distribution of the buildings' structural types and stories are illustrated below.


.. figure:: figures/SandyWindFlood.png
   :align: center
   :figclass: align-center

   Peak wind speed and floor water depth maps of the Sandy Storm

Inputs
==========

The example input files can be downloaded here: :download:`example_hu.zip <files/example_hu.zip>`. For more information about required input files, refer to :ref:`Inputs <lblUserDefInputs>`.


1. **Configuration file**: The configuration file specifies all simulation settings, including the application types, input file names, units, and type of outputs.

.. literalinclude:: files/rWHALE_config_hu.json
   :language: python
   :linenos:

2. **Building Application**: This example uses the :ref:`CSV_to_BIM <lblBuildingApp>` building application. In the configuration file, the Max and Min parameters are set to run the full set of 20 buildings, and the name of the building source file is provided as "input_params.csv". In the :ref:`building source file <lblUserDefInputs>`, input parameters for the DL assessment (e.g., ``NumberofStories``, ``YearBuilt``, ``OccupancyClass``, ``StructureType``, ``PlanArea``, ``ReplacementCost``) are specified.

**Building source file:**

.. csv-table:: input_params.csv
   :file: files/input_params_hu.csv
   :header-rows: 1
   :align: center

3. **Regional Mapping Application**: This example uses the :ref:`NearestNeighborEvents <lblregionalMapApp>` regional mapping application. From the parameters set in the configuration file, the algorithm is set to randomly select 10 samples of wind/flooding IMs from the 4 nearest neighbors for each building asset.



4. **Event Application**: This example uses the :ref:`SimCenterEvents <lblEventApp>` event application. It takes as input the EventGrid.csv and corresponding site files, which each have one instance of the intensity measures PWS and FWD assigned to the event site.

**Event grid file:**

.. csv-table:: EventGrid.csv
   :file: files/EventGrid_hu.csv
   :header-rows: 1
   :align: center

**Site file:**

.. csv-table:: 1596.csv
   :file: files/1596.csv
   :header-rows: 1
   :align: center


5. This example does not use a **Modeling**, **EDP**, **Simulation**, or **UQ** application because EDPs are not simulated with structural analysis.


6. **DL Application**: This example uses the :ref:`pelicun <lblDLApp>` DL application. From the :ref:`building source file <lblUserDefInputs>`, since the DL method selected is "HAZUS MH HU", damage/loss estimation is performed using the HAZUS loss assessment method based on hurricane IMs. Custom IM-based vulnerability functions are specified in the :download:`auto_HU_NJ.py <files/auto_HU_NJ.py>`.



Run Workflow
============

The workflow can be executed by uploading the appropriate files to :ref:`DesignSafe <lblrunRemote>`, or by running the example on your :ref:`local desktop <lblrunLocal>`, using the following *initialization command* in the terminal:

.. code-block::

      python "C:/rWHALE/applications/Workflow/R2D_workflow.py" "C:/rWHALE/hurricane_example/rWHALE_config_hu.json" --registry "C:/rWHALE/applications/Workflow/WorkflowApplications.json" --referenceDir "C:/rWHALE/hurricane_example/input_data/" -w "C:/rWHALE/hurricane_example/results"



This command locates the backend applications in the folder "applications", and the input files in a directory "hurricane_example". Please ensure that the paths in the command appropriately identify the locations of the files in your directory.

::

   applications
   hurricane_example
   ├── rWHALE_config_hu.json          # configuration file
   └── input_data
      ├── IMs
          ├── EventGrid.csv           # event grid file
          ├── 1596.csv                # event IM files
          .
          .
          .
          └── 3500.csv
      ├── auto_HU_NJ.py               # DL autoscript
      └── input_params.csv            # building source file



Outputs
==========

The example output files can be downloaded here: :download:`output_data_hu.zip <files/output_data_hu.zip>`. For more information about the output files produced, refer to :ref:`Outputs <lblOutputs>`.

1. **EDP_1-20.csv**: reports statistics on EDP results, where the hazard IM is used as the EDP. As in HAZUS, the statistics reported are the median and lognormal standard deviation of peak wind speed (PWS) and flood water depth (FWD).

.. csv-table:: EDP_1-20.csv
   :file: files/EDP_1-20.csv
   :header-rows: 1
   :align: center


2. **DM_1-20.csv**: reports collapse probability and damage state probability for each building asset. In the table below the "DSG_DS" values 0, 1_1, 2_1, 3_1, and 4_1 are four wind-induced damage states (from minor to severe), while the rest are the flood-induced damage states.

.. csv-table:: DM_1-20.csv
   :file: files/DM_1-20.csv
   :header-rows: 1
   :align: center


2. **DV_1-20.csv**: reports decision variable estimates (i.e., repair cost) for each building asset.

.. csv-table:: DV_1-20.csv
   :file: files/DV_1-20.csv
   :header-rows: 1
   :align: center

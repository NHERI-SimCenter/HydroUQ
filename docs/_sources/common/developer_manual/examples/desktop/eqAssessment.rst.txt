.. _lbleqAssessment:

*********************
Earthquake Assessment
*********************

This example is a small-scale regional earthquake risk assessment which performs response simulation and damage/loss estimation for a group of 20 buildings. The buildings are modeled as elastic-perfectly plastic single-degree-of-freedom (SDOF) systems defined by three input model parameters: the weight ``W``, yield strength ``f_yield``, and fundamental period ``T1``. The buildings are distributed in space in a 4x5 grid, within a 3x3 grid of event sites. At each event site, 5 ground motion records of similar intensity are assigned.


.. figure:: figures/regionalearthquakeexample.png
   :align: center
   :figclass: align-center


Inputs
==========

The example input files can be downloaded here: :download:`example_eq.zip <files/example_eq.zip>`. For more information about required input files, refer to :ref:`Inputs <lblUserDefInputs>`.


1. **Configuration file**: The configuration file specifies all simulation settings, including the application types, input file names, units, and type of outputs.

.. literalinclude:: files/rWHALE_config_eq.json
   :language: python
   :linenos:

2. **Building Application**: This example uses the :ref:`CSV_to_BIM <lblBuildingApp>` building application. In the configuration file, the Max and Min parameters are set to run the full set of 20 buildings, and the name of the building source file is provided as "input_params.csv". In the :ref:`building source file <lblUserDefInputs>`, input parameters for (a) the response simulation (weight ``W``, yield strength ``f_yield``, and fundamental period ``T1``) and for (b) the DL assessment (e.g., ``NumberofStories``, ``YearBuilt``, ``OccupancyClass``, ``StructureType``, ``PlanArea``, ``ReplacementCost``) are specified.

**Building source file:**

.. csv-table:: input_params.csv
   :file: files/input_params_eq.csv
   :header-rows: 1
   :align: center

3. **Regional Mapping Application**: This example uses the :ref:`NearestNeighborEvents <lblregionalMapApp>` regional mapping application. From the parameters set in the configuration file, the algorithm is set to randomly select 5 samples of ground motion records from the 4 nearest neighbors for each building asset.


.. figure:: figures/regionalearthquakeexample_annot.png
   :align: center
   :figclass: align-center

4. **Event Application**: This example uses the :ref:`SimCenterEvents <lblEventApp>` event application. It takes as input the EventGrid.csv, event files with the ground motion intensity measures, and the site files which specify the five ground motions assigned to each event site.

**Event grid file:**

.. csv-table:: EventGrid.csv
   :file: files/EventGrid_eq.csv
   :header-rows: 1
   :align: center

**Site file:**

.. csv-table:: site0.csv
   :file: files/site0.csv
   :header-rows: 1
   :align: center


5. **Modeling Application**: This example uses the :ref:`OpenSeesPyInput <lblModelingApp>` modeling application. The buildings are modeled as elastic-perfectly plastic single-degree-of-freedom (SDOF) systems defined by three input model parameters: the weight ``W``, yield strength ``f_yield``, and fundamental period ``T1``. Functions are included which record the peak response as EDPs for each of the EDP types specified in the EDP_specs.json file.

**Model file:**

.. literalinclude:: files/cantilever.py
   :language: python
   :linenos:

6. **EDP Application**: This example uses the :ref:`UserDefinedEDP <lblEDPApp>` EDP application. Custom EDPs are specified in the EDP specifications file. The EDP types are peak interstory drift (PID) and peak floor acceleration (PFA), recorded at the base and top node of the structural model in two horizontal directions (1,2).

**EDP specifications file:**

.. literalinclude:: files/EDP_specs.json
   :language: python
   :linenos:

7. **Simulation Application**: This example uses the :ref:`OpenSeesPySimulation <lblSimulationApp>` simulation application, which corresponds to the **OpenSeesPyInput** modeling application. It reads the ``build_model`` and ``run_analysis`` functions from the model file to perform the response simulation.



8. **UQ Application**: This example uses the :ref:`Dakota-UQ <lblUQApp>` UQ application to run the response simulation. In the configuration file, the number of samples specified for the UQ application should match the number of ground motion samples per building asset specified for the RegionalMapping application.



9. **DL Application**: This example uses the :ref:`pelicun <lblDLApp>` DL application. From the :ref:`building source file <lblUserDefInputs>`, since the DL method selected is "HAZUS MH EQ", damage/loss estimation is performed using the HAZUS loss assessment method based on earthquake EDPs produced from the response simulation.


Run Workflow
============

The workflow can be executed by uploading the appropriate files to :ref:`DesignSafe <lblrunRemote>`, or by running the example on your :ref:`local desktop <lblrunLocal>`, using the following *initialization command* in the terminal:

.. code-block::

    python "C:/rWHALE/applications/Workflow/R2D_workflow.py" "C:/rWHALE/cantilever_example/rWHALE_config_eq.json" --registry "C:/rWHALE/applications/Workflow/WorkflowApplications.json" --referenceDir "C:/rWHALE/cantilever_example/input_data/" -w "C:/rWHALE/cantilever_example/results"



This command locates the backend applications in the folder "applications", and the input files in a directory "cantilever_example". Please ensure that the paths in the command appropriately identify the locations of the files in your directory.

::

    applications
    cantilever_example
    ├── rWHALE_config_eq.json              # configuration file
    └── input_data
        ├── model
            ├── cantilever.py           # model file
        ├── records
            ├── EventGrid.csv           # event grid file
            ├── RSN30.json              # event IM files
            ├── RSN63.json
            .
            .
            .
            ├── site0.csv               # site files
            ├── site1.csv
            .
            .
            .
            └── site8.csv
        ├── EDPspecs.json               # EDP specifications file
        └── input_params.csv            # building source file



Outputs
==========

The example output files can be downloaded here: :download:`output_data_eq.zip <files/output_data_eq.zip>`. For more information about the output files produced, refer to :ref:`Outputs <lblOutputs>`.

1. **EDP_1-19.csv**: reports statistics on the EDP results from simulating 5 ground motions for each building asset. The statistics reported are the median and lognormal standard deviation of peak interstory drift (PID) and peak floor acceleration (PFA) in two directions.

.. csv-table:: EDP_1-19.csv
   :file: files/EDP_1-19.csv
   :header-rows: 1
   :align: center


2. **DM_1-19.csv**: reports collapse probability and damage state probability for each building asset.

.. csv-table:: DM_1-19.csv
   :file: files/DM_1-19.csv
   :header-rows: 1
   :align: center


2. **DV_1-19.csv**: reports decision variable estimates (repair cost, repair time, injuries) for each building asset.

.. csv-table:: DV_1-19.csv
   :file: files/DV_1-19.csv
   :header-rows: 1
   :align: center

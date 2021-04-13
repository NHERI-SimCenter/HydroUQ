.. _lblrunLocal:

Run Locally on Your Desktop
===========================

Running applications locally on a personal desktop is convenient for running small-scale jobs and debugging. For larger jobs, the applications are available on DesignSafe for utilizing high-performance computing resources.

1. Follow the directions in :ref:`How to Build <lblHowtoBuild>` to install the backend applications on your local desktop. Move the applications folder to a separate directory (such as ``C:/rWHALE/``).

2. Prepare the input files in a folder called ``input_data``, then zip the folder. You may use this example input file set (:download:`input_data_eq.zip <files/input_data_eq.zip>`) as a template.

3. Prepare workflow settings in the configuration file. You may use the example configuration file (:download:`rWHALE_config_eq.json <files/rWHALE_config_eq.json>`) as a template.


    - Set ``'runDir'`` to the path containing the ``input_data`` folder. If the configuration file is in the same directory, set ``'remoteDir'='...'``.
    - Set ``'localAppDir'`` to the path containing the applications folder (such as ``C:/rWHALE/``).
    - Specify applications for each workflow step and their inputs. For more details on the format of the configuration file, see :ref:`Inputs <lblUserDefInputs>`.


3. The workflow is run through the command window by calling on Python and specifying paths to the application files, input files, and desired location for the results folder. The following is an example of the **initialization command**:

.. code-block::

    python <path to R2D_workflow.py> <path to rWHALE_config.json> --registry <path to WorkflowApplications.json> --referenceDir <path to input_data folder> -w <path to output results folder>


where:
    - **<path to R2D_workflow.py>** is the full path to the file "R2D_workflow.py" in the applications folder
    - **<path to rWHALE_config.json>** is the full path to the provided file "rWHALE_config.json"
    - **<path to WorkflowApplications.json>** is the full path to the file "WorkflowApplications.json" in the applications folder
    - **<path to input_data folder>** is the full path to the folder with all input files
    - **<path to output results folder>** is the full path to where a "results" folder will be created to contain the output files



4. A results folder is produced, which contains both the aggregated output files (EDP_{min id}_{max id}.csv, DM_{min id}_{max id}.csv, DV_{min id}_{max id}.csv), as well as the individual output files (EDP.csv, DM.csv, DV.csv) for each built asset in their respective folders.

::

   results
   ├── 1                            # folder for building asset 1
      ├── templatedir               # folder of template files
      ├── workdir.1                 # working directory for each event simulation
      ├── workdir.2
      ├── workdir.3
      .
      .
      .
      ├── dakota.err                # dakota files
      ├── dakota.in
      ├── dakota.out
      ├── DL_summary.csv            # damage/loss summary
      ├── DM.csv                    # individual building asset output files
      ├── DV.csv
      ├── EDP.csv
      └── response.csv
   ├── 2
   .
   .
   .
   ├── 1-BIM                       # BIM files for each building asset
   ├── 2-BIM
   .
   .
   .
   ├── DM_{min id}_{max id}.csv    # aggregated results
   ├── DV_{min id}_{max id}.csv
   ├── EDP_{min id}_{max id}.csv
   └── log.txt                     # log file

.. _lblreadingLog:

********************
Reading the Log File
********************

The sequence of tasks carried out by the backend applications is outlined in the **log file** produced by the workflow. For :ref:`local runs <lblrunLocal>`, this log is displayed in the command terminal and is reproduced in a file named ``log.txt`` in the ``results/`` directory. For :ref:`remote runs <lblrunRemote>` through Tapis, this log file is called ``launcher.out`` in the job archive folder on DesignSafe. This guide will explain how to understand the statements printed in the log file.

The following is an example log file for a successful workflow run. The workflow can be broken down into the following sections:

I. **Read the configuration file:**

    - **lines 12-13**: Identifies the path to the :ref:`configuration file <lblUserDefInputs>`, which specifies the job details, and the *application registry file*, which specifies all available applications.

    - **line 16-62**: Reads the application registry file and displays all available applications.

    - **line 64-85**: Reads the configuration file and displays the units, local application directory, remote application directory, reference directory, and the applications chosen for each workflow step. Any workflow steps which are skipped (excluded from the configuration file) are also listed here.

II. **Pre-process building and event data:**

    - **line 93**: Python command for executing the :ref:`Building <lblBuildingApp>` application, creating the BIM files for each building asset.

        ::

            python "C:/rWHALE/applications/createBIM/CSV_to_BIM/CSV_to_BIM.py" "--buildingFile" "C:/rWHALE/earthquake_example/results/buildings1-2.json" "--Min" "1" "--Max" "2" "--buildingSourceFile" "C:/rWHALE/earthquake_example/input_data/input_params.csv" "--getRV"


    - **line 103**: Python command for executing the :ref:`RegionalMapping <lblRegionalMapApp>` application, assigning events to each of the building assets.

        ::

            python "C:/rWHALE/applications/performRegionalMapping/NearestNeighborEvents/NNE.py" "--buildingFile" "C:/rWHALE/earthquake_example/results/buildings1-2.json" "--filenameEVENTgrid" "C:/rWHALE/earthquake_example/input_data/records/EventGrid.csv" "--samples" "2" "--neighbors" "1"


III. **Set up and run simulations for each building asset:**

    - **line 111**: Starts with the first building asset. In this first pass, the EVENT, SAM, EDP, SIM files corresponding to "1-BIM.json" are created.

    - **line 118**: Python command for executing the :ref:`Event <lblEventApp>` application, creating the EVENT file for the building asset.

        ::

            python "C:/rWHALE/applications/createEVENT/SimCenterEvent/SimCenterEvent.py" "--filenameBIM" "1-BIM.json" "--filenameEVENT" "EVENT.json" "--pathEventData" "C:/rWHALE/earthquake_example/input_data/records/" "--getRV"


    - **line 126**: Python command for executing the :ref:`Modeling <lblModelingApp>` application, creating the SAM file for the built  asset.

        ::

            python "C:/rWHALE/applications/createSAM/openSeesPyInput/OpenSeesPyInput.py" "--filenameBIM" "1-BIM.json" "--filenameEVENT" "EVENT.json" "--filenameSAM" "SAM.json" "--mainScript" "cantilever.py" "--modelPath" "C:/rWHALE/earthquake_example/input_data/model/" "--ndm" "3" "--dofMap" "1,2,3" "--getRV"


    - **line 134**: Python command for executing the :ref:`EDP <lblEDPApp>` application, creating the EDP file for the building asset.

        ::

            python "C:/rWHALE/applications/createEDP/userEDP_R/UserDefinedEDP.py" "--filenameBIM" "1-BIM.json" "--filenameEVENT" "EVENT.json" "--filenameSAM" "SAM.json" "--filenameEDP" "EDP.json" "--EDPspecs" "C:/rWHALE/earthquake_example/input_data/EDP_specs.json" "--getRV"


    - **line 142**: Python command for executing the :ref:`Simulation <lblSimulationApp>` application, creating the SIM file for the building asset.

        ::

            python "C:/rWHALE/applications/performSIMULATION/openSeesPy/OpenSeesPySimulation.py" "--filenameBIM" "1-BIM.json" "--filenameSAM" "SAM.json" "--filenameEVENT" "EVENT.json" "--filenameEDP" "EDP.json" "--filenameSIM" "SIM.json" "--getRV"


    - **lines 153-157**: Commands which are written to the *workflow driver file*. In a "second pass" through the workflow, these commands are executed by running the workflow driver file.

        ::

            python "C:/rWHALE/applications/createBIM/CSV_to_BIM/CSV_to_BIM.py" "--buildingFile" "C:/rWHALE/earthquake_example/results/buildings1-2.json" "--Min" "1" "--Max" "2" "--buildingSourceFile" "C:/rWHALE/earthquake_example/input_data/input_params.csv"
            python "C:/rWHALE/applications/createEVENT/SimCenterEvent/SimCenterEvent.py" "--filenameBIM" "1-BIM.json" "--filenameEVENT" "EVENT.json" "--pathEventData" "C:/rWHALE/earthquake_example/input_data/records/"
            python "C:/rWHALE/applications/createSAM/openSeesPyInput/OpenSeesPyInput.py" "--filenameBIM" "1-BIM.json" "--filenameEVENT" "EVENT.json" "--filenameSAM" "SAM.json" "--mainScript" "cantilever.py" "--modelPath" "C:/rWHALE/earthquake_example/input_data/model/" "--ndm" "3" "--dofMap" "1,2,3"
            python "C:/rWHALE/applications/createEDP/userEDP_R/UserDefinedEDP.py" "--filenameBIM" "1-BIM.json" "--filenameEVENT" "EVENT.json" "--filenameSAM" "SAM.json" "--filenameEDP" "EDP.json" "--EDPspecs" "C:/rWHALE/earthquake_example/input_data/EDP_specs.json"
            python "C:/rWHALE/applications/performSIMULATION/openSeesPy/OpenSeesPySimulation.py" "--filenameBIM" "1-BIM.json" "--filenameSAM" "SAM.json" "--filenameEVENT" "EVENT.json" "--filenameEDP" "EDP.json" "--filenameSIM" "SIM.json"


    - **line 165**: Python command for executing the :ref:`UQ <lblUQApp>` application, which executes the commands in the workflow driver file to sample random variables and perform the response simulation. This command creates the EDP output file for the building asset.

        ::

            python "C:/rWHALE/applications/performUQ/dakota/DakotaFEM.py" "--filenameBIM" "1-BIM.json" "--filenameSAM" "SAM.json" "--filenameEVENT" "EVENT.json" "--filenameEDP" "EDP.json" "--filenameSIM" "SIM.json" "--driverFile" "driver" "--method" "LHS" "--samples" "2" "--type" "UQ" "--concurrency" "1" "--keepSamples" "True" "--runType" "run"


    - **line 189**: dakota command which calls on DAKOTA to execute the UQ application.

        ::

            running Dakota:  dakota -input dakota.in -output dakota.out -error dakota.err


    - **line 198**: Python command for executing the :ref:`DL <lblDLApp>` application, which outputs the DM.csv and DV.csv for the building asset.

        ::

            python "C:/rWHALE/applications/performDL/pelicun/DL_calculation.py" "--filenameDL" "1-BIM.json" "--filenameEDP" "response.csv" "--outputEDP" "EDP.csv" "--outputDM" "DM.csv" "--outputDV" "DV.csv" "--DL_Method" "HAZUS MH EQ" "--Realizations" "2" "--detailed_results" "False" "--log_file" "True" "--coupled_EDP" "True" "--event_time" "off" "--ground_failure" "False"


    - **line 213**: Continues to the second building asset ("2-BIM.json") and repeats the same workflow steps.


IV. **Aggregate outputs for all building assets:**

    - **line 315**: Aggregates results to create the EDP, DM, and DV output files.

        ::

            -----------------------------------------------------------
            Collecting damage and loss results
            Damage and loss results collected successfully.
            -----------------------------------------------------------


The full log file is shown below:

.. literalinclude:: _static/log.txt
    :linenos:
    :emphasize-lines: 12,13,16,64,93,103,111,118,126,134,142,153,154,155,156,157,165,189,198,213,315

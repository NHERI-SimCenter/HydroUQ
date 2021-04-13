.. _lbltroubleshooting:

Troubleshooting Errors
===========================

If the workflow does not run successfully, the first and best method for troubleshooting is by reading error messages output in the **log file**. For an example log file, refer to the page :ref:`Backend Applications <lblbackendApps>`.


For troubleshooting with the log file, the following steps are recommended:
    - **Identify which application failed in the workflow**. Read through the log file until an ERROR message appears after one of the Python commands.
    - **Verify that the paths to all workflow files are correct.** These paths are specified in the :ref:`initialization command <lblrunLocal>` when run locally, or in the :ref:`job script <lblrunRemote>` when run remotely.
    - **Check that the "ApplicationData" for each application in the configuration file are correct.** The workflow will fail if an application does not have all of its required application-specific inputs, or if inputs are provided with an incorrect data type. See the individual pages for the :ref:`Backend Applications <lblArchitecture>` for more details on application-specific inputs.
    - **Check that there are no JSON serialization errors in the configuration file.** Mistakes in unclosed brackets or incorrect indentation in the JSON file will cause errors.
    - **Check that the user-defined input files are in the correct format.** Mistakes in the header labels or formatting of CSV and JSON input files will cause errors.
    - **To view print messages in the model script during response simulation, rerun Dakota.** By default, any print messages in input files are suppressed in the log file. In order to view the messages and debug issues with the model script, navigate to the results folder for one of the building assets in the command window (i. e. "results/1"). You should find three files: dakota.in, dakota.err, and dakota.out. Running the following command will re-execute the UQ application for that particular building asset:

        ``dakota -input dakota.in -output dakota.out -error dakota.err``


If problems still persist, you are encouraged to read previously posted questions or post your own at `SimCenter Forum <https://simcenter-messageboard.designsafe-ci.org/smf/index.php>`_. A member of the SimCenter developer team will respond to your question on the platform.

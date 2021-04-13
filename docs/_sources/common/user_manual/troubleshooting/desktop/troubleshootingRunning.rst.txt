.. _troubleshootingRunning:

Issues While Running
--------------------

The |app| is a complicated tool and it will not always run. Causes of failure include incorrect set up, non-functioning or poorly functioning websites, user error, and possible bugs in the software. To discover the errors it is useful to understand how the user interface and the backend work when the user submits to run a job. A number of things occur when the Submit button is clicked:

#. The UI creates a folder in the working dir location specified called ``tmp.SimCenter`` and in that folder creates another folder called ``templatedir``.
#. The UI then iterates through all the widgets chosen and these widgets place all needed files for the computation into the ``templatedir`` directory.
#. A Python script is run in this ``templatedir`` directory that creates the input file for the UQ Engine. For example, using Dakota the input file ``dakota.in`` is created and placed in the ``tmp.SimCenter`` folder.
#. The UQ engine is then started and runs using the ``dakota.in`` input file.
#. As the UQ engine runs, it creates folders in ``tmp.SimCenter``, one folder for each deterministic run.
#. When completed the UQ engine leaves the results files in the ``tmp.SimCenter`` folder.
#. The results files are then processed by the front-end and presented to the user in the **RES** tab.


The following is a list of things that we have observed go wrong when the user interface informs the user of a failure and steps the user can take to fix the problem:

#.  **Could not create working dir**: The user does not have permission to create the ``tmp.SimCenter`` folder in working dir location. Change the **Local Jobs Directory** and the **Remote Jobs Directory** in the application's **Preferences** menu option. 

#. **No Script File**: The user has changed the Local Applications directory location in Preferences, or the applications folder that accompanies the installation has been modified. Either set the correct directory location or re-install the tool.
#. **Dakota failed to finish**: This can occur for a number of reasons. Go to the ``tmp.SimCenter`` folder and have a look for the ``dakota.err`` file. If no file exists then dakota did not start, if the file exists look at it's contents to see if there are any errors.

   #. **No dakota.err file and no dakota.in file**: the Python script in ``templatedir`` failed to create the necessary files. Have a look at the workflow log file in the ``templatedir`` folder to see what the error is as it could indicate an error in your input. If no workflow log file exists, it means Python failed to start. Check the installation of Python.

   #. **No dakota.err and dakota.in exists**: Dakota failed to run. Check installation of Dakota and Python. NOTE: Sometimes if Python starts, it is not using the version of Python you specified in the environment variables when setting up Python (this is due to fact that many applications install their own version of Python). If Dakota is installed correctly, set the location of the Python executable in Preferences.

   #. **dakota.err file exists**: Open the file and see what the error is.  For example if it says **Error: at least one variable must be specified.** This means no random variables have been specified. You have only one deterministic event or you have not specified any random variables in the EDP.

   #. **dakota.err file exists but is empty**: This means that Dakota ran but there was a problem with the simulation. Go to one of the ``workdir`` locations. There is a file workflow driver that can be run. Run it and see what the errors are.

   #. **You ran at DesignSafe and no dakota.out files come back**: Go to your data depot folder at DesignSafe using your browser. Go to archive/jobs and use the job number shown in table that pops up when you ask to get the job from DesignSafe. Study both the ``.err`` and ``.out`` files in that directory for a clues to as what went wrong.

   #. **No results and you used the Site Response to create the event**. You must run a simulated event in the Site Response Widget before you can submit a job to run.


If problems persist please post them on the |messageBoard|

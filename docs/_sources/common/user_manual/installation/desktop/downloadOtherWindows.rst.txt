.. _lblDownloadOtherWindows:

Windows Users
-------------

Install Location
^^^^^^^^^^^^^^^^

.. only:: notQuoFEM

   The following set of instructions assumes all files will be placed in a **C:\\SimCenter** folder. You can of course place them anywhere you want, you just need to make appropriate changes to the **env PATH** settings. If you wish to follow our placement strategy, inside the **C:\\SimCenter** folder create **2** additional folders named **dakota** and **OpenSees**.


.. only:: quoFEM

   The following set of instructions assumes all files will be placed in a **C:\\SimCenter** folder. You can of course place them anywhere you want, you just need to make appropriate changes to the **env PATH** settings. If you wish to follow our placement strategy, inside the **C:\\SimCenter** folder create **3** additional folders named **dakota**, **OpenSees** and **FEAPpv**.

.. note::

   The choice of **C:\\SimCenter** was made as opposed to typical **C:\\Program Files** location as there is no uninstallers provided for the different software packages we provide. To remove the software you only need to remove the **SimCenter** folder.

Python
^^^^^^

If you have not yet installed Python 3.7, we recommend installing Python 3.7 from 
`Python.org <https://www.python.org/downloads/windows>`_. We recommend installing using the 
**Windowsx86 64-bit executable installer**.  

.. note::

   Allow the installer to change yur system environment variables so that the directory containing the executable is on your path. This requires checking the small box asking for this when the installer starts. The box is located at bottom of installer application window.

.. warning::
   The latest version of Python is 3.8.3 At time of writing Python 3.8.3 was no working with the current **numpy** package.

Once Python is installed, you need to extend it by installing the following packages: **numpy**, **scipy**, and **pandas**. To install these packages, start a `terminal window as an Admin user <https://www.howtogeek.com/194041/how-to-open-the-command-prompt-as-administrator-in-windows-8.1/>`_ and in that window type the following instructions:

.. code-block:: python

      pip install numpy
      pip install scipy
      pip install pandas
      pip install tables
      pip install hdf5

.. note::
   
   As an alternative, you can install the SimCenter's pelicun module, which will include all three of the above

   .. code-block:: python

      pip install pelicun

Dakota
^^^^^^
|DakotaLink| is the default UQ engine used by the |app| that is publicly available from the |DakotaDownload| page. The download page offers an extensive list of downloadable files. You can narrow this down to the file to be selected by selecting **Windows** in the `Platform`, **6.10** (**6.10** was latest at time of writing, select newer of course if available) in the `Release`, and **Command Line Only** for the `interface type`. In the `Public` area you should now only have a single option, click on the link to download |Dakota|. When you extract the files that you download, they will all be contained in a single folder, we suggest renaming it **dakota-6.10.0** (the last **.0** was the number in the download, sometimes developers issue minor updates and identify them through the last number). When you have renamed the folder move that folder to the **C:\\SimCenter\\dakota\\** folder.

.. note::

   We place **dakota-6.10.0** inside **dakota** folder to be able to have multiple versions installed. This is a useful practice, as software developers make tweaks that can effect the results of past simulations. It is useful to be able to compare different versions of an application to ensure results stay the same.

OpenSees
^^^^^^^^

|OpenSeesLink| is the default FEM engine used by the |app| that is publicly available from the |OpenSeesDownload| page. To download the **OpenSees** you have to enter your email address, which may also require you to register (that requirement is going away and may be gone by time you read this). At the bottom of the page, under section **Windows Version** is the download link for the current executable, currently **3.2.2** Follow the link to download the application. It is in the form of a **.zip** file. The zip file contains a folder and in the bin directory is the **OpenSees.exe** application. The other files and folders are needed by the application and must be kept. Rename the folder to **OpenSees-3.2.2** and move the folder to the **C:\\SimCenter\\OpenSees** folder.

Modify the Environment Variables
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

You now need to make some changes to your environment variables as neither OpenSees or Dakota includes an installer which typically performs this task.

1. Open the Start Search, type in “env”, and choose “Edit the system environment variables”
2. Click the **Environment Variables…** button at the bottom right of the application that pop up.
3. Now we are going to edit the  **PATH** variable. Select the Path variable row to highlight it and then press the **Edit** button.
4. to the variables value you want to **APPEND** the following:

.. code-block:: none
   
   C:\\SimCenter\\OpenSees\\OpenSees-3.2.2\\bin;C:\\SimCenter\\dakota\\dakota-6.10.0\\bin

5. Press the **OK** button.
6. Now we are going to create a new variable, **PYTHONPATH** variable. Press the **NEW** button.
7. For the variable name enter: **PYTHONPATH**.
8. For the variable path enter

.. code-block:: none

   C:\\SimCenter\\dakota\\share\\dakota\\Python

9. Press the **OK** button.
10. Press now the **Apply** button and exit the SystemProperties application


Test the Install of Python, OpenSees & Dakota
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Steps to Test:
   1. Open a command window window(type `cmd` in search)
   2. Type `python3` in the application that starts (this should bring up python interpreter)
   3. Enter the following to test the install of the modules and quit the application:
   
   .. code-block:: python

      import numpy
      import scipy
      import pandas
      quit()

   4. Type `OpenSees` in the command window (this should bring up the OpenSees interpreter)

   5. Enter the following to exit this program:
   
   .. code-block:: tcl

      exit

   6. Type ``dakota`` in the command window (this should start the dakota application which should give some error messages)

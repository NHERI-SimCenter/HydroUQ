.. _lblInstallWindows:

Install on Windows 10
=====================

.. only:: R2D_app

   Install Java
   ^^^^^^^^^^^^

   .. note::
      Java is needed to use OpenSHA to characterize the regional seismic hazard (see :ref:`ground_motion_tool`). If you do not plan to use that feature, you can skip this step of the installation.

   If you have not yet installed Java, please download the latest installer from `java.com <https://java.com/en/download/>`_ , run it, and follow the on-screen instructions to install Java.

   .. note::
      The Java website should automatically detect your operating system and offer the corresponding installer for you to download. Make sure you see "64-bit Java for Windows" at the top of the page before downloading the installer.

Download the Application
^^^^^^^^^^^^^^^^^^^^^^^^

To download the |app|, first navigate to the |appLink| page. As shown in |figDownloadWin|, to get to the download page, you need to click on the link **Download app and User Manual** in the application page. The download page contains a list of downloadable files and directories.


.. only:: R2D_app

   .. _figDownloadWin-R2D:

   .. figure:: figures/R2DDownload.png
      :align: center
      :figclass: align-center

      R2DTool download page.

.. only:: PBE_app

   .. _figDownloadWin-PBE:

   .. figure:: figures/pbeDownload.png
      :align: center
      :figclass: align-center

      PBE download page.

.. only:: EEUQ_app

   .. _figDownloadWin-EE:

   .. figure:: figures/eeDownload.png
      :align: center
      :figclass: align-center

      EE-UQ download page.

.. only:: WEUQ_app

   .. _figDownloadWin-WE:

   .. figure:: figures/weDownload.png
      :align: center
      :figclass: align-center

      WE-UQ download page.


.. only:: quoFEM_app

   .. _figDownloadWin-quoFEM:

   .. figure:: figures/quoFEMDownload.png
      :align: center
      :figclass: align-center

      quoFEM download page.

Click on the file with a name ending with **Windows_Download.zip** to download the |app|. In the pop-up window, click on the **Download** button in the bottom right corner. After the download completed, extract the zip archive to a location in your filesystem.

We suggest placing the directory in the **C:\\SimCenter** folder. Once here, you can create a shortcut to the application and move this shortcut to your Desktop.


Test the Installation
^^^^^^^^^^^^^^^^^^^^^

Once the installation procedure has been completed, it is a good practice to run some basic checks. Navigate to the location where you placed the application and open it by running the |short tool id|.exe executable. You should see the user interface shown in |figUI|. The installation can be tested by running the example problem |test example|.

.. note::

   Since the SimCenter is not recognized as a Windows vendor, our applications are not recognized by the operating system as being signed. Consequently, you may receive a warning message when you start the |short tool name| application for the first time.

.. only:: R2D_app

   .. _figUI-R2D:

   .. figure:: figures/PBE.png
    :align: center
    :figclass: align-center

    R2DTool on startup.

.. only:: PBE_app

   .. _figUI-PBE:

   .. figure:: figures/PBE.png
    :align: center
    :figclass: align-center

    PBE application on startup.

.. only:: EEUQ_app

   .. _figUI-EE:

   .. figure:: figures/EE-UQ.png
    :align: center
    :figclass: align-center

    EE-UQ application on startup.

.. only:: WEUQ_app

   .. _figUI-WE:

   .. figure:: figures/WE-UQ.png
    :align: center
    :figclass: align-center

    WE-UQ application on startup.

.. only:: quoFEM_app

   .. _figUI-quoFEM:

   .. figure:: figures/quoFEM.png
    :align: center
    :figclass: align-center

    quoFEM application on startup.


.. _lblTroubleshootingStartup:

Startup Issues
--------------

On Windows operating systems, if you receive an error when starting the application with the message that MSVCP140.dll is missing as shown in |figMissingCRT|, it is caused by a missing Visual C/C++ runtime library. You can fix this error by running the installer for the Visual C/C++ redistributable package **vc_redist.x64.exe** which is included with the application.


.. only:: PBE_app

   .. _figMissingCRT-PBE:

   .. figure:: figures/PBE-MissingCRT.png
      :align: center
      :figclass: align-center

      Error message for missing Visual C/C++ runtime library.

.. only:: EEUQ_app

   .. _figMissingCRT-EE:

   .. figure:: figures/EE-UQ-MissingCRT.png
      :align: center
      :figclass: align-center

      Error message for missing Visual C/C++ runtime library.


.. only:: WEUQ_app

   .. _figMissingCRT-WE:

   .. figure:: figures/WE-UQ-MissingCRT.png
      :align: center
      :figclass: align-center

      Error message for missing Visual C/C++ runtime library.


.. only:: R2D_app

   .. _figMissingCRT:

   .. figure:: figures/MissingCRT.png
      :align: center
      :figclass: align-center

      Error message for missing Visual C/C++ runtime library.


   

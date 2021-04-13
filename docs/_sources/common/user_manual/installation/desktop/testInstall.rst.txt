.. _lblTestInstall:

Test the Application
=====================

.. only:: PBE_app

    Before running any simulations, we recommend testing the application and the simulation environment on your computer by running a test calculation.

    We have prepared a test workflow that you can load from the ``Examples/E0_Test`` folder in the application directory. Open the ``E0_test_input.json`` file with the PBE application. It should automatically populate the settings in the user interface. Without changing anything, click on the **Run** button in the bottom left corner of the application. Running the simulation should not take more than a few minutes and the results should be displayed in the end automatically. If you see a scatter plot of results in the end, your environment is set up appropriately and you are ready to start running your own simulations.

.. only:: R2D_app

    Before running any simulations, we recommend testing the R2DTool by running the following example problem: :ref:`lbl-r2dt-0006`.

.. only:: quoFEM_app

   Follow the following steps to test the install:

    #. Create a folder test in your Desktop.
    #. Create a file ``test.tcl`` in this folder with the following contents.

    .. literalinclude:: test.tcl
           :language: tcl

    #. Start the application. Select the **FEM** tab and for the **Input Script** entry, press the **Choose** button and navigate to the **test** directory and select the ``test.tcl`` file. Now press **Open**.

    #. Select the **RV** tab. Press the **Add** button twice to add two random variables. Name one ``a`` and the other ``b``. For both change the distribution type to **Uniform** and enter min and max values for both of **0** and **1**, i.e. both points will be somewhere between **0** and **1**.
    #. Select the **QoI** panel. Press the **Add** button once and enter the name **D**.

    #. Press the **Run** button. After pressing this button some numbers should show up in the **RES** tab that are close to **1/3** and **1/6**.

        .. note::

        For those interested, we are using quoFEM to answer the question of what is the distance between two random points (assumed independent and uniformly distributed) located on the line segment (0,1).The mean distance given by the exact solution is **1/3** with a standard deviation of **1/6**.

.. only:: EEUQ_app

   Follow the following steps to test the install:
          1. Start the |app| by double-clicking on it. This will bring up the application, which as shown will present the user with the **UQ** tab
              2. In the panel set the ``# samples`` to 10
              3. Select the **EVT** panel, by clicking on the **EVT** letters on the left side of the application, this will bring up the Stochastic Motion event, which is the default event application
              4. In this panel set **moment magnitude** entry to **mag**, ``Closest to Site Rupture Distance`` to 30, and ``Average Shear Wave Velocity`` to **300.0**
              5. Select the **RV** panel, by clicking on the **RV** letters on the left side of application, this will bring up the Random  Variables panel
              6. For the **mean** and **Standard Dev** quantities for the **mag** random variable, enter **7.0** and **0.1** respectively
              7. Select the **Run** button at the bottom left of the screen
              8. After a number of dialog boxes pop up showing status, the **RES** tab will be displayed. There should be some results in it

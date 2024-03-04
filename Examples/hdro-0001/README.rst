.. _hdro-0001:

Coupled Digital Twin Example
============================

+---------------+----------------------------------------------+
| Problem files | :github:`Github <Examples/hdro-0001/>`       |
+---------------+----------------------------------------------+

Outline 
-------
This example uses a NHERI wave-flume digital twin, the OSU LWF, to simulate a scaled structure during wave loading in HydroUQ. Two-way coupled OpenFOAM-OpenSees is configured to simulate the scenario. 

You will define a Waterborne Event (EVT) to determine the engineering demand parameters (EDP) on a specified structure, i.e. EVT --> EDP,  with the following steps:

1. Configure a FOAMySees simulation. This is a two-way coupling of OpenFOAM Finite Volume Method (FVM) for Computational Fluid Dynamics (CFD) and OpenSees Finite Element Analaysis (FEA) for Computational Structural Dynamics (CSD). 

2. Next, the coupled model will determine floor loads on the building, also known as intensity measures (IM) in performance based engineering (PBE). 

3. Then, perform an OpenSees finite element analysis (FEA) simulation of the building by taking IMs as inputs. 

4. Finally, recieve engineering demand parameters (EDP) of the structural response. Though beyond this example, you can use these EDPs to perform a fragility analysis of the structure.


Data
----
The dataset used presented in this example originates from experimental tests conducted in the Hinsdale Wave Research Laboratory's Large Wave Flume at Oregon State University (OSU LWF), Corvallis, in 2020. Refer to Lewis 2023 [Lewis2023]_ and Bonus 2023 [Bonus2023]_ for details.

.. _figCoupled:

.. figure:: figures/Coupled.png
   :align: center
   :figclass: align-center
   :width: 400

   Coupled Digital Twin Illustration

Model
-----

This model is characterized by the parameters:
- Youngs modulus :math:`E_0`for elastic behavior,
- Initial yield stress and strain hardening ratio :math:`(f_y, b)` for plastic behavior,

Files required
--------------

.. warning::
   Do NOT place the files in your root, downloads, or desktop folder as when the application runs it will copy the contents on the directories and subdirectories containing these files multiple times. If you are like us, your root, Downloads or Documents folders contain a lot of files.

UQ workflow
-----------

The inputs needed to run this example can be loaded into the HydroUQ user interface by selecting the ``Coupled Digital Twin`` example from the ``Examples`` menu.

The inputs can also be set up manually through the following steps:

1. Start the application and the **UQ** panel will be highlighted. In the **UQ Method** drop-down menu, select the **Bayesian Calibration** option. In the **UQ Engine** dropdown menu select **UCSD-UQ** option. In the **Model** dropdown, select the **Hierarchical** option. Enter the values in this panel as shown in the figure below. A brief explanation of the different user input fields can be found in the :ref:`User Manual <lblUCSDHierarchical>`. 

.. _figHBMUQ:

.. figure:: figures/UQ.png
   :align: center
   :figclass: align-center
   :width: 600
   
   Inputs in the UQ panel

2. Next in the **FEM** panel , select **OpenSees** and populate the **Input Script** field by choosing the path to the model file.

.. .. _figHBMFEM:

.. .. figure:: figures/FEM.png
..    :align: center
..    :figclass: align-center
..    :width: 600
   
..    Inputs in the FEM panel

3. Select the **RV** tab from the input panel. This panel should be pre-populated with the names of the variables that were defined in the model scripts. If not, press the **Add** button to create a new field to define the input random variable. Enter the same variable name, as required in the model script. For this example, choose the Normal probability distribution for all the random variables and enter the parameter values for each distribution as shown in the figures below:

.. _figHBMRV:

.. figure:: figures/RV.png
   :align: center
   :figclass: align-center
   :width: 600

.. .. _figHBMRV1:

.. .. figure:: figures/RV1.png
..    :align: center
..    :figclass: align-center
..    :width: 600

.. .. _figHBMRV2:

.. .. figure:: figures/RV2.png
..    :align: center
..    :figclass: align-center
..    :width: 600
   
..    Inputs in the RV panel


4. In the **EDP** panel create the output quantities corresponding to each of the experiments with a descriptive name, as shown in the figures below:

.. .. _figHBMEDP1:

.. .. figure:: figures/EDP1.png
..    :align: center
..    :figclass: align-center
..    :width: 600

.. .. _figHBMEDP2:

.. .. figure:: figures/EDP2.png
..    :align: center
..    :figclass: align-center
..    :width: 600
   
..    Inputs in the EDP panel


5. Click on the **Run** button. This will create the necessary input files to perform a Bayesian calibration of the hierarchical model, run the analysis, and display the results when the analysis is completed. The results produced are sample values drawn from the distribution that represents the aleatory uncertainty in the estimated material parameters from each of the datasets. 

The **Summary** tab shows the mean, standard deviation, and coefficient of variation of each of the seven parameters of the material model that were inferred in this example.

.. .. _figHBMRES1:

.. .. figure:: figures/RES1.png
..    :align: center
..    :figclass: align-center
..    :width: 600

.. .. _figHBMRES2:

.. .. figure:: figures/RES2.png
..    :align: center
..    :figclass: align-center
..    :width: 600

   Results in the RES panel summary tab


In the **Data Values** tab of the **RES** panel, a chart and a table with all the sample values are shown. By clicking on the data inside the columns of the chart with the left or right mouse button, different chart types are created and shown in the chart area on the left. 

.. .. _figHBMRES3:

.. .. figure:: figures/RES3.png
..    :align: center
..    :figclass: align-center
..    :width: 600

.. .. _figHBMRES4:

.. .. figure:: figures/RES4.png
..    :align: center
..    :figclass: align-center
..    :width: 600

   .. Data values tab in the RES panel


.. _lblHBMRestart:

Files for restarting the analysis
---------------------------------

In addition to the results displayed in the RES panel in HydroUQ, JSON files with the state of the chain at every step of the sampling algorithm are saved in a directory called ``sampling_results`` within the ``tmp.SimCenter`` directory inside the jobs directory specified in the HydroUQ Preferences menu. Any of these files can be used to resume the sampling, by copying the file to the directory containing the model files and specifying its name in the Restart File Name field in the UQ panel.

.. warning::
   The ``tmp.SimCenter`` directory is cleared every time the ``RUN`` button is clicked in HydroUQ. So, if you want to restart the analysis using one of the sampling results files outlined above, make sure to copy the results file to a location outside the ``tmp.SimCenter`` directory at the end of the analysis.

.. [Lewis2023]
   Lewis, N. (2023). Development of An Open-Source Methodology for Simulation of Civil Engineering Structures Subject to Multi-Hazards. *PhD thesis*, University of Washington, Seattle, WA. ISBN: 979-8-381408-69-0.

.. [Bonus2023]
   Bonus, J. (2023). Evaluation of Fluid-Driven Debris Impacts in a High-Performance Multi-GPU Material Point Method [University of Washington]. In ProQuest Dissertations and Theses. ISBN: 979-8-381406-66-5. https://www.proquest.com/dissertations-theses/evaluation-fluid-driven-debris-impacts-high/docview/2915819774/se-2?accountid=14784


   
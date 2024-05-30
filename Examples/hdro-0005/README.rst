.. _hdro-0005:

====================================================================================
Feature - Stochastic Wave Loading on a Simple Structure - Stochastic Wave Spectra 
====================================================================================

+---------------+----------------------------------------------+
| Problem files | :github:`Github <Examples/hdro-0005/>`       |
+---------------+----------------------------------------------+


.. contents:: Table of Contents
   :local:
   :backlinks: none


.. _hdro-0005-overview:

Overview
--------

.. figure:: figures/hdro-0005_WaveTimeSeries.png
   :align: center
   :alt: The image displays two charts related to "Wave Generation." The top chart is a time series graph showing "Wave Elevation (m)" over "Time [s]" with values ranging from roughly -5 to 5 meters, fluctuating over a period of 0 to 3500 seconds in a noisy, seemingly random pattern. The bottom chart is a spectral density graph, plotting "Spectral density [m^2/s]" from 0 to 150 against "Frequency [Hz]" from 0 to 0.4 Hz. There are two overlapping curves on this graph: one labeled "Generated," which is a line plot that peaks near 0.1 Hz and tapers off, and another labeled "Jonswap," which seems to be a reference plot closely tracking the "Generated" curve but with some minor deviations. Both charts are colored in shades of blue, with a white background and axis labels in black text.
   :width: 600
   :figclass: align-center
   
   Stochastic JONSWAP wave spectra produced in HydroUQ, applying the welib Python package.

In this local workflow example, basic uncertainty quantification methods (Forward, Sensitivity, Reliability) are applied to the response of a simple structure loaded by a stochastic wave spectra.


Set-Up
------

.. figure:: figures/hdro-0005_UQ.png
   :align: center
   :alt: A screenshot of a software interface with a section labeled "UQ Method" displaying settings for uncertainty quantification. The UQ Engine is set to "Dakota" with options for "Forward Propagation." Checkboxes for "Parallel Execution" and "Save Working dirs" are ticked. Under Method, "LHS" (Latin Hypercube Sampling) is selected from a dropdown menu with inputs for "# Samples" set at 5 and "Seed" also set at 5. The left sidebar shows tabs labeled UQ, GI, SIM, EVT, FEM, EDP, RV, and RES, indicating different modules or sections of the software.
   :width: 600
   :figclass: align-center
   
   HydroUQ's desktop GUI for the NHERI OSU LWF digital wave-flume twin.

Details for the experiments are available in various publications. Namely, the work of Andrew Winter [Winter2020]_ [Winter2019]_, Krishnendu Shekhar [Shekhar2020]_ and Dakota Mascarenas [Mascarenas2022]_ [Mascarenas2022PORTS]_.  The simulations replicated in this example appeared originally in Bonus 2023 [Bonus2023Dissertation]_.

Experiments were performed in the NHERI OSU LWF, a 100 meter long flume with adjustable bathymetry, in order to quantify stochastic impact loads of ordered and disordered debris-fields on effectively rigid, raised structure. 

.. figure:: figures/hdro-0005_GI.png
   :align: center
   :alt: Screenshot of a building information form with fields for name, properties, location, and units. Under properties, it includes 'Year Built' as 1990, '# Stories' as 4, 'Struct. Type' as RM1, 'Height' as 576, 'Width' as 360, 'Depth' as 360, and 'Plan Area' as 129600. Location details show 'Latitude' as 37.8715 and 'Longitude' as -122.273. Units selected are 'Force' in Kips, 'Length' in Inches, and 'Temperature' in Celsius. There is a menu on the left side with various tabs such as UQ, GI, SIM, EVT, FEM, EDP, RV, and RES.
   :width: 600
   :figclass: align-center
   
   NHERI OSU LWF facilty's experimental schematic used in this example. Adapted from Winter 2019 [Winter2019]_, and Mascarenas 2022 [Mascarenas2022]_.

This example may help to produce a robust database (numerical and physical) from which to eventually be able to extract both the first-principals of wave-driven debris-field phenomena and design guidelines on induced forces. 

We validate against two very similar (but not identical) physical studies done in the OSU LWF by [Shekhar2020]_ and [Mascarenas2022]_, indicating high accuracy of our model and low bias to minor experiment specifications. 

Results for free surface elevation and streamwise structural loads are to be recorded for validation at a specified interval. 

Qualitatively, an MPM simulation of debris impacts on a raised structure in the OSU LWF is shown below.

.. figure:: figures/hdro-0005_SIM.png
   :align: center
   :alt: A screenshot of a user interface for a "Building Model Generator" with a dropdown menu set to "OpenSees". The interface contains fields for "Input Script" with a file path provided, "Centroid Nodes", "Response Nodes" with the value 1,3 entered, "Spatial Dimension" with the value 2, "# DOF at Nodes" with the value 3, and "Damping Ratio" with the value 0.02. On the left side, a vertical menu shows tabs for UQ, GI, SIM, EVT, and FEM, with the SIM tab currently selected. There is also a "Choose" button on the right side of the "Input Script" field.
   :width: 600
   :figclass: align-center

   OSU LWF debris impact photos from HydroUQ's MPM simulations.

It appears similar in the mechanism of debris impact, stalling, and deflection relative to the structure and flow for a similar case in Mascarenas 2022 [Mascarenas2022]_.

.. figure:: figures/hdro-0005_EVT.png
   :align: center
   :alt: Screenshot of a software interface with various input fields related to "Stochastic Wave Loading". A dropdown menu for "Event Type" is set to "Stochastic Wave Loading", and another dropdown for "Stochastic Loading Model" is set to "JONSWAP". There are multiple input fields with values for parameters such as "Water Depth", "Significant Wave Height", "Peak Period", and others related to the simulation of wave conditions. At the bottom, an option for "Provide seed value" with a numerical input box is visible. The interface has a tabbed layout with tabs labeled UQ, GI, SIM, EVT, FEM, EDP, RV, and RES at the top. The current view is under the "EVT" tab, indicating event-specific parameters are being configured.
   :width: 600
   :figclass: align-center

   OSU LWF debris impact photos from Mascarenas 2022 [Mascarenas2022]_ experiments.


The experiments by Shekhar et al. 2020 [Shekhar2020]_ are also shown below for comparison. These tests had a slightly different configuartion, primarily the debris were located 0.5 meters further upstream from the box and the water level was 0.10-0.15 meters lower than the 2.0 meter datum used in the simulations and Mascarenas 2022 [Mascarenas2022]_ experiments.

.. figure:: figures/hdro-0005_EDP.png
   :align: center
   :alt: Screenshot of a software interface with a vertical navigation menu on the left side showing various abbreviated menu items such as "UQ," "GI," "SIM," "EVT," "FEM," with "EDP" highlighted. The main area displays the header "Engineering Demand Parameters Generator" with a dropdown menu set to "Standard." The rest of the main area is blank.
   :width: 600
   :figclass: align-center

   OSU LWF debris impact photos from Shekhar et al. 2020 [Shekhar2020]_ experiments.

Similar figures can be made for the whole range of order debris-array experiments done at the OSU LWF. However, this example focuses on teaching you how to replicate the above results.


.. _hdro-0005-setup:



A step-by-step walkthrough on replicating an MPM simulation result from Bonus 2023 [Bonus2023Dissertation]_ is provided below.

Open ``Settings``. Here we set the simulation time, the time step, and the number of processors to use, among other pre-simulation decisions.

.. figure:: figures/hdro-0005_RV.png
   :align: center
   :alt: Screenshot of a software interface for inputting random variables with an 'Add' button at the top. Three variables are listed—fc, fy, and E—with each set to a 'Normal' distribution and respective mean and standard deviation values. Each variable has an option to 'Show PDF'. Menu options for UQ, GI, SIM, EVT, FEM, EDP, RV, and RES are visible on the left side, with 'RV' highlighted. 'Clear All', 'Correlation Matrix', 'Export', and 'Import' options are available at the top right corner of the input section.
   :width: 600
   :figclass: align-center

   HydroUQ Settings GUI


Open ``Bodies`` / ``Fluid`` / ``Material``. Here we set the material properties of the fluid and the debris.

.. figure:: figures/hdro-0005_RES_Summary_Forward.png
   :align: center
   :alt: Screenshot of a software interface displaying statistical data values for different items categorized under labels UQ, SIM, EVT, FEM, and EDP. Each category shows a name such as 1-PFA-1-1, and values for Mean, StdDev, Skewness, and Kurtosis. The data presented is numerical, with values like 12.7422 for Mean under UQ and varying standard deviations and other statistical measures for each item. The interface has a tab selection with "Summary" and "Data Values" as options; "Data Values" is highlighted.
   :width: 600
   :figclass: align-center

   HydroUQ Bodies Fluid Material GUI

Open ``Bodies`` / ``Fluid`` / ``Geometry``. Here we set the geometry of the flume, the debris, and the raised structure. 

.. figure:: figures/hdro-0005_RES_Scatter.png
   :align: center
   :alt: Screenshot of "HydroUQ: Water-borne Hazards Engineering with Uncertainty Quantification" software interface displaying a scatter plot with several data points and a correlation coefficient of -0.95. On the right side of the screen, there is a table with multiple columns showing engineering data like "Run #," "fc," "fy," "E," and several columns with labeling consistent with engineering nomenclature such as "1-RMSA-1-1," "1-PDF-1-1," and "1-PID-1-1." The user interface has tabs for "Summary" and "Data Values" and buttons such as "Save Table," "Save Columns Separately," "Save RVs," and "Save QoIs" at the top right. At the bottom, there are buttons for "RUN," "RUN at DesignSafe," "GET from DesignSafe," and "Exit." The interface suggests a tool for engineering analysis and simulation with focus on uncertainty quantification.
   :width: 600
   :figclass: align-center

   HydroUQ Bodies Fluid Geometry GUI


Open ``Algorithm``. Here we set the algorithm parameters for the simulation. We choose to apply F-Bar antilocking to aid in the pressure field's accuracy on the fluid. The associated toggle must be checked, and the antilocking ratio set to 0.9, loosely.

.. figure:: figures/hdro-0005_RES_Cumulative_Forward.png
   :align: center
   :alt: Screenshot of a data analysis software interface showing a cumulative frequency distribution chart on the left and a detailed data table on the right. The chart depicts a step-like increase, representing a cumulative probability distribution. The table includes numerical values for various parameters including 'Run #', 'fc', 'fy', 'E', and several probability values. Color-coded buttons for saving and exiting the table are visible at the bottom.
   :width: 600
   :figclass: align-center

   HydroUQ Bodies Fluid Algorithm GUI

Open ``Bodies`` / ``Fluid`` / ``Partitions``. Here we set the number of partitions for the simulation. This is the domain decomposition across discrete hardware units, i.e. Multi-GPUs. These may be kept as there default values. 

.. figure:: figures/hdro-0005_RES_HistogramForward.png
   :align: center
   :width: 600
   :figclass: align-center

   HydroUQ Bodies Fluid Partitions GUI

Moving onto the creation of an ordered debris-array, we set the debris properties in the ``Bodies`` / ``Debris`` / ``Material`` tab. We will assume debris are made of HDPE plastic, as in experiments by Mascarenas 2022 [Mascarenas2022]_ and Shekhar et al. 2020 [Shekhar2020]_.

.. figure:: figures/hdro-0005_RV_Sensitivity.png
   :align: center
   :alt: Screenshot of an interface with tabs on the left which include "UQ", "GI", "SIM", "EVT", "FEM", "EDP", "RV", and "RES". The main panel is titled "Input Random Variables" and has three options: "Add", "Clear All", and "Correlation Matrix", along with "Export" and "Import" buttons on the right. Below this, there are three entries of random variables listed with their corresponding distribution, mean, and standard deviation values. The first variable "fc" has a normal distribution with a mean of 6.0 and a standard deviation of 0.6. The second variable "fy" has a constant distribution with a constant value of 60.0. The third variable "E" also has a normal distribution with a mean of 30000 and a standard deviation of 3000. Each variable entry has a button labeled "Show PDF". The background is light with a color scheme of blues and grays.
   :width: 600
   :figclass: align-center

   HydroUQ Bodies Debris Material GUI

Open ``Bodies`` / ``Debris`` / ``Geometry``. Here we set the debris properties, such as the number of debris, the size of the debris, and the spacing between the debris. Rotation is another option, though not used in this example. We've elected to use an 8 x 4 grid of debris (longitudinal axis parallel to long-axis of the flume).

.. figure:: figures/hdro-0005_RES_Summary_Sensitivity.png
   :align: center
   :alt: Screenshot of the "HydroUQ: Water-borne Hazards Engineering with Uncertainty Quantification" web interface, showing tables and bar graphs of Sobol' indices for different random variables 'fc' and 'E'. The interface features four sets of indices: 1-PFA-1-1 Sobol', 1-RMSA-1-1 Sobol', 1-PFD-1-1 Sobol', and 1-PID-1-1 Sobol'. Each set includes numerical values and corresponding bar graphs with green bars representing 'Main' effects and blue bars representing 'Total' effects. The numerical values range from negative to positive, indicating varying degrees of sensitivity or influence of the variables on a particular model or system. The page has a navigation sidebar on the left with options such as UQ, GI, SIM, EVT, FEM, EDP, RV, and RES highlighted. There are "Cite" and "Login" buttons at the top right corner.
   :width: 600
   :figclass: align-center

   HydroUQ Bodies Debris Geometry GUI

The ``Bodies`` / ``Debris`` / ``Algorithm`` and ``Debris`` / ``Partitions`` tabs are not used in this example, but are available for more advanced users.

Open ``Bodies`` / ``Structures``. Uncheck the box that enables this body, if it is checked. We will not model the structure as a body in this example, instead, we will modify it as a boundary later.

.. figure:: figures/hdro-0005_RES_Scatter_Sensitivity.png
   :align: center
   :alt: Screenshot of a software application titled "HydroUQ: Water-borne Hazards Engineering with Uncertainty Quantification". The left side of the screen shows a navigation menu with various categories such as UQ, GI, SIM, EVT, and others highlighted in blue. The main area displays a scatter plot with the label "Samples" and numerous blue dots representing data points, along with a correlation coefficient value of -0.95 displayed below the plot. On the right side, there is a data table with columns titled "Run #", "fc", "E", "fy", and several others with numerical data, and options to save or export the data are provided above the table. There is a button labeled "GET from DesignSafe" at the bottom right corner.
   :width: 600
   :figclass: align-center
   
   HydroUQ Bodies Structures GUI

Open ``Boundaries`` / ``Wave Flume``. We will set the boundary to be a rigid body, with a fixed separable velocity condition, that is faithful to the digital tiwn of the NHERI OSU LWF. Bathmyetry joint points should be indetical to the ones used in ``Bodeis`` / ``FLuid``.

.. figure:: figures/hdro-0005_RES_Summary_Reliability.png
   :align: center
   :alt: A complex graphical interface displaying a graph titled "HydroUQ: Water-borne Hazards Engineering with Uncertainty Quantification." The graph maps a curved line ascending from left to right representing a probability level on the Y-axis and a 1-RMSA-1-1 index on the X-axis. Below the graph, several numerical data entries are visible, correlating the RMSA index to probability levels. There's a top navigation bar with the options "Cite" and "Login." Also, there's a left navigation bar with various options including UQ, GI, SIM, EVT, FEM, EDP, RV, and RES highlighted in blue.
   :width: 600
   :figclass: align-center

   HydroUQ Boundaries Wave Flume Facility GUI

Open ``Boundaries`` / ``Wave Generator``. Fill in the appropriate file-path for the wave generator paddle motion. It is designed to produce near-solitary like waves.

.. figure:: figures/hdro-0005_forces.png
   :align: center
   :alt: The image displays eight line graphs in a 2x4 grid format, illustrating changes in inline force (measured in kN/m) versus depth (measured in meters) at different normalized time intervals of a cyclical process, denoted as t/T, where T is the period. Each time interval (0, 1/8, 1/4, 3/8, 1/2, 5/8, 3/4, 7/8) is represented above its respective graph. Three types of forces are plotted in each graph: 'finertia' in blue, 'fdrag' in black, and 'ftot' in red, each showing varying patterns of force distribution with depth. The forces exhibit dynamic behavior, alternating direction and magnitude as time progresses.
   :width: 600
   :figclass: align-center
   
   HydroUQ Boundaries Wave Generator GUI

Open ``Boundaries`` / ``Rigid Structure``. This is where we will specify the raised structure as a boundary condition. By doing so, we can determine exact loads on the rigid boundary grid-nodes, which may then be mapped to the FEM tab for nonlinear UQ structural response analysis.

.. figure:: figures/hdro-0005_moments.png
   :align: center
   :alt: The image displays a series of eight graphs arranged in a two-row, four-column grid, each depicting curves that represent inline moment in kilonewton-meters per meter (kNm/m) plotted against depth in meters (m). Each graph is labeled with a fractional time value (t/T) ranging from 0 to 7/8 incrementally. Two types of curves are shown in each graph: 'dMtot with Wheeler' represented by solid lines and 'dMtot no-correction' indicated by plus signs. The shapes of the curves vary across the different time steps, mainly describing negative sloped lines that illustrate the relationship between the inline moment and depth at the given time fractions. The overall presentation suggests an analysis of structural or mechanical data over time, with Wheeler correction applied in one scenario and omitted in the other.
   :width: 600
   :figclass: align-center

   HydroUQ Boundaries Rigid Structure GUI

Open ``Boundaries`` / ``RigidWalls``.

.. figure:: figures/hdro-0005_IntegratedPileLoads.png
   :align: center
   :alt: A set of three line graphs plotted against Dimensionless Time, t/T, on the x-axis, ranging from 0 to 1. The top graph shows Cumulative Elevation in meters ranging from -4 to 4, the middle graph shows Scaled Moment [kNm/m] ranging from -3 to 3, and the bottom graph shows Scaled Moment [kNm/m] ranging from -40 to 20. Each graph has two lines representing 'Standard' and 'Wheeler Correction'. All lines show a wave-like pattern with peaks and troughs. The 'Standard' line is represented in blue and the 'Wheeler Correction' in black, with the middle graph showing a larger amplitude in the curves than the bottom graph.
   :width: 600
   :figclass: align-center

   HydroUQ Boundaries Wave-Flume Facility GUI

Open ``Sensors`` / ``Wave Gauges``. Set the ``Use these sensor?`` box to ``True`` so that the simulation will output results for the instruments we set on this page.

Three wave gauges will be defined. The first is located prior to the bathymetry ramps, the second partially up the ramps, and the third near the the bathymetry crest, debris, and raised structure. 

Set the origins and dimensions of each wave as in the table below. To match experimental conditions, we also apply a 120 Hz sampling rate to the wave gauges, meaning they record data every 0.0083 seconds. 



.. Open ``Sensors`` / ``Load Cells``. Set the ``Use these sensor?`` box to ``True`` so that the simulation will output results for the instruments we set on this page.

.. .. figure:: figures/GUI_Sensors_LoadCells.PNG
..    :align: center
..    :width: 600
..    :figclass: align-center
   
..    HydroUQ Sensors Load-Cells GUI


.. Open ``Outputs``. Here we set the non-physical output parameters for the simulation, e.g. attributes to save per frame and file extension types. The particle bodies' output frequency is set to 10 Hz (0.1 seconds), meaning the simulation will output results every 0.1 seconds. This is decent for animations without taking too much space. Fill in the rest of the data in the figure into your GUI to ensure all your outputs match this example.

.. .. figure:: figures/GUI_Outputs.PNG
..    :align: center
..    :width: 600
..    :figclass: align-center
   
..    HydroUQ Outputs GUI



.. _hdro-0005-simulation:

Simulation
----------

We assume most computers will be able to run this simulation within a few minutes if samples are kept below 100.

.. warning::
   Only ask for what you need in terms of recorder count, time-step size, random variables, and UQ samples. Otherwise you will end up with massive amounts of data which can slow simulations due to I/O constraints.


.. _hdro-0005-analysis:

Analysis
--------


This complete our HydroUQ validation example for stocahstic wave-loading on a simple frame structure.


.. _hdro-0005-references:

References
----------

.. [Winter2019] Winter, A. (2019). "Effects of Flow Shielding and Channeling on Tsunami-Induced Loading of Coastal Structures." PhD thesis. University of Washington, Seattle.

.. [Winter2020] Andrew O Winter, Mohammad S Alam, Krishnendu Shekhar, Michael R Motley, Marc O Eberhard, Andre R Barbosa, Pedro Lomonaco, Pedro Arduino, Daniel T Cox (2019). "Tsunami-Like Wave Forces on an Elevated Coastal Structure: Effects of Flow Shielding and Channeling." Journal of Waterway, Port, Coastal, and Ocean Engineering.

.. [Shekhar2020] Shekhar, K., Mascarenas, D., and Cox, D. (2020). "Wave-Driven Debris Impact on a Raised Structure in the Large Wave Flume." 17th International Conference on Hydroinformatics, Seoul, South Korea.

.. [Mascarenas2022] Mascarenas, Dakota. (2022). "Quantification of Wave-Driven Debris Impact on a Raised Structure in a Large Wave Flume." Masters thesis. University of Washington, Seattle.

.. [Mascarenas2022PORTS] Mascarenas, Dakota, Motley, M., Eberhard, M. (2022). "Wave-Driven Debris Impact on a Raised Structure in the Large Wave Flume." Journal of Waterway, Port, Coastal, and Ocean Engineering.

.. [Bonus2023Dissertation] Bonus, Justin (2023). "Evaluation of Fluid-Driven Debris Impacts in a High-Performance Multi-GPU Material Point Method." PhD thesis. University of Washington, Seattle.



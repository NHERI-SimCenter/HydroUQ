.. _lbl-example_rdt_srt:

Regional Site Response Assessment
=============================================================

Problem Statement
---------------------------------------------
Site response analysis is commonly performed to analyze the propagation of seismic wave through soil. As shown in :numref:`fig_siteResponse`, 
one-dimensional response analyses, as a simplified method, assume that all boundaries are horizontal and that the response of a soil deposit is
predominately caused by SH-waves propagating vertically from the underlying bedrock. Ground surface response is usually the major output from
these analyses, together with profile plots such as peak horizontal acceleration along the soil profile. When liquefiable soils are presenting,
maximum shear strain and excess pore pressure ratio plots are also important.

.. _fig_siteResponse:
.. figure:: ./figures/siteResponse.png
   :scale: 50%
   :align: center
   :figclass: align-center

   Simplified 1D site response analysis (courtesy of Pedro Arduino)


This example demonstrates a small-scale regional earthquake risk assessment which performs site response simulation for a group of 20 sites
located in the San Francisco Bay area. The sites are distributed in space in a 4x5 grid, within a 3x3 grid of event sites. At each event site,
5 ground motion records of similar intensity are assigned.

.. _figContext:

.. figure:: ./figures/example.png
   :scale: 20%
   :align: center
   :figclass: align-center

   Location of testbed sites

Methodology
---------------------------------------------

In this example, the coordinates of a list of sites are known and peak ground accelerations at these sites are of interest. A summary of the RDT
procedure for the site response analysis is summarized here:

1. Assemble required information for interested sites. These data include site locations, input motions, and site geological data, e.g., Vs30 (the time-averaged shear-wave velocity to 30 m depth) and depth to bedrock
2. If the input motions are not provided, use OpenSHA to obtain proper input motions
3. If the Vs30 data are not known, use SimCenter **EQHazard** to obtain proper Vs30 data
4. If the depth to bedrock data are not known, they can be obtained from SoilGrid250 database 
5. Use Sediment Velocity Model (SVM) to generate soil shear wave velocity profile 
6. Generate material input for site response analysis based on predefined model calibration methods
7. Perform site response analysis using RDT and obtain acceleration response at the surface of soil columns defined for each site

In this example, a total of twenty sites and their input motions have been pre-selected. Details of selected sits are summarized in :numref:`tab_inputs`. The directory structure for inputs is:

::

    srt_example
    ├── rWHALE_config_SRT.json
    └── input_data
        ├── model
            ├── getVs30.py
            ├── Scenario.json
            ├── FreeField3D_Dry.tcl
        ├── records
            ├── EventGrid.csv
            ├── RSN30.json
            ├── RSN63.json
            .
            .
            .
            ├── site0.csv
            ├── site1.csv
            .
            .
            .
            └── site8.csv
        └── input_params.csv


Obtaining Vs30 Data
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Vs30 data can be obtained using **EQHazard** tool. EQHazard is a console application developed by the SimCenter to facilitate performing seismic hazard analysis(SHA) for regional earthquake simulations.
The application makes use of OpenSHA to perform deterministic SHA. This application is developed using Java to facilitate the use of OpenSHA Java library. It is worth noting that this tool is most suitable
for research applications where SHA needs to be performed for many sites given a single earthquake scenario, such as using a grid of sites for regional simulations. Several site data sources have been included in EQHazard, such as CGS/Wills VS30 Map (2015),
Global Vs30 from Topographic Slope (Wald & Allen 2008), and more.

Using EQHazard is simple, the EQHazard tool is distributed as a jar file and can executed directly using:

.. code-block:: java

   java -jar EQHazard Scenario.json Output.json

Scenario.json is the name of the input file and output.json is the name to be used for the resulting output file.

.. note::
   Java is required to run EQHazard

Python script **getVs30.py** provides a wrapper for EQHazard. It uses the site coordinates from input_params.csv and
a template scenario file, *Scenario.json*, to obtain Vs30 data. An updated input file, *input_params_srt.csv*, is then created with Vs30 data populated as shown in :numref:`tab_inputs_srt`. In this case, CGS/Wills VS30 Map (2015) is used.

.. _tab_inputs_srt:
.. csv-table:: Input Parameters with Vs30 Data Obtained Using EQHazard 
   :file: input_params_srt.csv
   :header-rows: 1


Obtaining Depth to Bedrock
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The depth to bedrock can be obtained using several datasets. For example, SoilGrid250 map provides absolute depth to bedrock (in cm) predicted using the global compilation of soil ground observations.
Accuracy assessment of the maps is available in Hengl :cite:`Hengl2017` and can be downloaded :download:`here <https://data.isric.org/geonetwork/srv/eng/catalog.search#/metadata/f36117ea-9be5-4afd-bb7d-7a3e77bf392a>`.
In this dataset, the depth to bedrock is considered as "depth (in cm) from the ground surface to the contact with coherent (continuous) bedrock."
It should be noted that the definition of bedrock in this database is based on lithology rather than shear wave velocity. Hence, depending on the geological condition, bedrock may imply
different shear wave velocity and it might vary dramatically, e.g., western U.S. vs. eastern U.S.. Assumption is required for modeling purposes. In this example, the shear wave velocity of bedrock is assumed to be
760 m/s, as the sites are located in western U.S..

.. _fig_DtR:
.. figure:: ./figures/US_Depth_To_Rock.png
   :align: center
   :figclass: align-center

   Depth to bedrock (Cropped from SoilGrid250 to show continental U.S., 10 km resolution)

Example python script to obtain the data is shown below:

.. code-block:: python  

   import rioxarray as rxr
   import pandas as pd
   from pyproj import Transformer

   soil250 = rxr.open_rasterio('BDTICM_M_250m_ll.tif')
   inputs = pd.read_csv('input_params_srt.csv')
   for index, row in inputs.iterrows():
      lon = row['longitude']
      lat = row['latitude']
      transformer = Transformer.from_crs("EPSG:4326", soil250.rio.crs, always_xy=True)
      xx, yy = transformer.transform(lon, lat)
      depth_To_Rock = soil250.sel(x=xx, y=yy, method="nearest").values[0]
      print('depth to rock is {:.2f} m'.format(depth_To_Rock/100))

Generating Soil Profile Using SVM
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Once the depth to rock is obtained, the next step is to generate soil profile based on Vs30. Amplitude, frequency content and duration of ground shaking are important parameters in ground motion modeling and are
heavily dependent on crustal material properties. The Sediment Velocity Model (SVM) “translates VS30 and a proxy which describes stiffness of the near surface sediments into a 1D velocity profile” (Shi and Asimaki, 2018, :cite:`Shi2018`). 

Datasets of soil parameters only exist for specific locations and there is no way to collect adequate data on all regions. For this reason, there is a need for a method which can determine these crustal
material properties such as wave velocity and mass density for those regions which we do not have physically collected data. One such method, called the Community Velocity Models (CVMs),
which was developed by the Southern California Earthquake Center (SCEC), is used to provide 3D seismic velocity information for Southern California. However, CVMs have their limitations.
There exist two sub-models of the CVM which are the CVM-SCEC (CVM-S) and CVM-Harvard (CVM-H). Both sub-models rely on the spatial resolution of the available datasets and thus result in crude velocity profiles.
Moreover, the CVM-H has an optional geotechnical layer (GTL) option which replaces the soft sediments in the top 350 m of soil, smoothing the velocity profile and obscuring basin edges which cause strong velocity impedance. 

The SVM method was developed to get more accurate soil profiles as a function of VS30 which can be easily obtained from maps. It further allows for determination of basin depths based on crustal velocity models and preserves basin edges.

The Shi and Asimaki :cite:`Shi2018` Sediment Velocity Model (SVM) is used in this example because of its ability to predict a soil velocity profile based solely on VS30. From this profile we are able to determine ground motion wavelengths and set
a constraint for a minimum number of points needed to fully describe a soil column. Gmax at depth is also obtained from this shear wave velocity profile. The results of the test case are presented in :numref:`fig_Vs`. 

.. _fig_Vs:
.. figure:: ./figures/Vs.png
   :align: center
   :figclass: align-center

   Generated shear wave velocity profile based on SVM  

Including Soil Nonlinearity
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
By default, `elastic isotropic material <https://opensees.berkeley.edu/wiki/index.php/Elastic_Isotropic_Material>`_ is assigned to the soil column due to limited available information. However, Nonlinearity can be incorporated into workflow by switching the constitutive model to other nonlinear model, for example, 
the multiaxial cyclic plasticity model proposed by Borja and Amies :cite:`Borja1994`. This simple total stress-based bounding surface plasticity model for clays was developed to accommodate multiaxial stress reversals. The model was constructed based on the idea
of a vanishing elastic region undergoing pure translation inside a bounding surface, and an interpolation function for hardening modulus which varies with stress distance of the elastic region from the unloading point.
The model can be applied to cohesive soils undergoing undrained stress reversals and cyclic loading. :numref:`fig_BA94` illustrates behaviors of this model under cyclic loading. More information regarding the implementation of this model in OpenSees can be found
`here <https://opensees.berkeley.edu/wiki/index.php/J2CyclicBoundingSurface_Material>`_. 

.. _fig_BA94:
.. figure:: ./figures/CTC_Fig3_Comparison.png
   :align: center
   :scale: 30%
   :figclass: align-center

   Example behavior of Borja and Amies model


.. csv-table:: Input for elastic material
   :header: "id", "longitude", "latitude", "...", "Model"
   :widths: 10, 20, 20, 10, 10

   0, -122.182, 37.422, ..., "Elastic"   

The example input parameters for using Borja and Amies are summarized in the following table:

.. csv-table:: Input for multiaxial cyclic plasticity model for clays (Borja and Amies, :cite:`Borja2018`)
   :header: "id", "longitude", "latitude", "...", "Model", "Su_rat", "Den", "h/G", "m", "h0", "chi"
   :widths: 10, 20, 20, 10, 10, 10, 10, 10, 10, 10, 10
   
   0, -122.182, 37.422, ...,  BA ,   0.26 ,  2 ,  1 ,  1 ,  0.2,    0   

where ``Su_rat`` is the ratio between undrain shear strength and initial vertical stress.   

Adding Surface Structural Model
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
A structure model can also be added to the workflow. In this case, the structure model uses the :ref:`OpenSeesPyInput <lblModelingApp>` modeling application as discussed in :ref:`Earthquake Assessment <lbleqAssessment>`.
The buildings are modeled as elastic-perfectly plastic single-degree-of-freedom (SDOF) systems defined by three input model parameters: the weight ``W``, yield strength ``f_yield``, and fundamental period ``T1``.
Functions are included which record the peak response as EDPs for each of the EDP types specified in the EDP_specs.json file.


.. code-block:: JSON

   "Modeling": {
   "Application": "OpenSeesInputSRT",
   "ApplicationData": {
      "mainScript": "FreeField3D_Dry.tcl",
      "modelPath": "model/",
      "ndm": 3,
      "includeStructureModel": true,
      "SimulationApplication": "OpenSeesPy-Simulation",
      "structureModel": "cantilever.py"
   }

Performing Analysis
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Configurations for RDT workflow are defined in **rWHALE_config_SRT.json**. In this example, the application for Modeling and Simulation is OpenSeesInputSRT and OpenSees-Simulation-SRT, respectively.

For each site, two additional input files for OpenSees are created during analysis: **freefield_config.tcl** and **freefield_material.tcl**. **freefield_config.tcl** defines the discretization of the profile and applied input motion(s). 


.. literalinclude:: freefield_config.tcl
  :language: tcl
  :linenos:

**freefield_material.tcl** defines material inputs based on predefined calibration procedure based on Vs profile created from previous step. Input motion(s) is converted from records for each evaluation,
for example, xInput.vel and xInput.time defiles velocity and time series, respectively, for one component of the motion.

.. literalinclude:: freefield_material.tcl
  :language: tcl
  :linenos:

The working/results directory structure is:

::

   results
      └── 0
         ├── templatedir
            ├── bim.j
            ├── edb.j
            |── evt.j
            ├── sam.j
            ├── workflow_driver.bat
         ├── workdir.1
            ├── FreeField3D_Dry.tcl
            ├── freefield_config.tcl
            ├── freefield_material.tcl
            ├── xInput.vel
            ├── xInput.time
            ├── yInput.vel
            ├── yInput.time
            .
            .
            .
         ├── workdir.2
         .
         .
         ├── workdir.5
         └── response.csv
      └── 1
      .
      .
      └── 19
   
**EDP_1-19.csv**: reports statistics on the EDP results from simulating 5 ground motions for each building asset.
The statistics reported are the median and lognormal standard deviation of peak ground acceleration (shown as PFA) in two directions.

.. _tab_edp_results:
.. csv-table:: EDP Results
   :file: EDP_0-19.csv
   :header-rows: 1


Under Windows system, the commands can be summarized as:

.. literalinclude:: run.bat
  :language: bash


Appendix
---------------------------------------------
Configurations for RDT workflow:

.. literalinclude:: rWHALE_config_SRT.json
  :language: json
  :linenos:
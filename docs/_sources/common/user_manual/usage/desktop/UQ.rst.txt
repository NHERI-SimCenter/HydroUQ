
UQ: Uncertainty Quantification
==============================

The first selection panel the user must select from and enter data into is the **UQ** tab. It is in this panel where the user selects the **UQ Engine** to use for performing the uncertainty quantification calculations.

.. only:: quoFEM_app
	  
	  Presently the **UQ Engine** option supports Dakota, SimCenterUQ, UCSD and users own custom UQ engines.

.. only:: notQuoFEM
	  
	  Presently the only **UQ Engine** option is Dakota.


Dakota UQ Engine
----------------

This UQ engine utilizes the `Dakota Software <https://dakota.sandia.gov/>`_, a state-of-the-art research application that is robust and provides many methods for optimization and UQ, a selection of which we utilize in this application. **Dakota** provides the user with a large number of different methods. For this reason we have divided the methods into categories though a pull-down menu, as shown in :numref:`figDakota`. Once the category has been selected, a number of different methods are made available to the user.

.. _figDakota:

.. figure:: figures/dakotaUQ.png
   :align: center
   :figclass: align-center

   Dakota engine and category selection.

The following categories are available:

.. toctree-filt::
   :maxdepth: 1

   DakotaSampling
   :EEUQ:DakotaSensitivity
   :EEUQ:DakotaReliability
   :quoFEM:DakotaSensitivity
   :quoFEM:DakotaReliability
   :quoFEM:DakotaParameterEstimation
   :quoFEM:DakotaInverseProblems

.. only:: quoFEM_app
	   
	  SimCenter UQ Engine
	  -------------------
	  
	  This is an in-house developed UQ engine of SimCenter that accommodates different UQ methods. Currently the option is limited to global sensitivity analysis:

	  .. toctree-filt::
	     :maxdepth: 1

             SimCenterUQSensitivity

	  UCSD UQ Engine
	  --------------

	  This is a module developed at UCSD. This module currently offers support for Bayesian calibration using the Transitional Markov chain Monte Carlo (TMCMC) algorithm, which is also known as the Sequential Monte Carlo algorithm:

	  .. toctree-filt::
	     :maxdepth: 1

	     UCSD_UQ_TMCMC

	  Custom UQ Engine
	  ----------------
	  
	  This option enables users to switch out the UQ engine in the quoFEM workflow such
	  that different methods and tools can be applied within the SimCenter
	  framework with minimal effort on the part of the user. In order to do so,
	  two steps are required:

	  * Configure UQ tab to accept the required inputs
	  * Adding UQ engine to customized UQ backend

	  These steps are described in more detail below.
	  	  
	  Configuring UQ tab
	  ******************

	  The quoFEM interface can be customized to accept the required inputs for
	  user-specified UQ engines. The "CustomUQ" option should be selected, as shown in
	  :numref:`CustomUQInput`. The UQ application name should then be input as "Other-UQ" as
          this will direct quoFEM to invoke the customized UQ backend where users can plug
	  in their own functionality.	    

	  .. _customUQInput:
	  .. figure:: figures/CustomUQEngine.png
		  
	     Custom UQ Engine Configuration

	  Next, users must configure the interface to accept inputs required to run their
	  UQ engine. This is done through a JSON configuration file that is specified
	  through "Configuration Input File". Once this file is input, the user interface
	  will be automatically updated to accept the inputs specified in the JSON
	  configuration. An example JSON configuration is shown :ref:`below <jsonInput>`. This
	  configuration file generates the interface shown in :numref:`CustomUQInput`.

	  .. _jsonInput:
	  .. literalinclude:: JsonWidgetConfig.json

	  Currently, users are able to specify the following types of inputs:

	  #.  **ComboBox**: Allows selection of a particular option from a specified set
  
	  #.  **Spin Box**: Used to input integer values
  
	  #.  **Double Spin Box**: Used to input floating point numbers
  
	  #.  **File Input**: Used for inputting file locations
  
	  #.  **Line Edit**: Used to input text values	  

	  Lastly, users must specify the UQ driver name. This is required to direct the
	  customized UQ backend to the correct UQ driver. The driver name must correspond
	  the name provided in the customized backend, as described below.

	  Adding UQ Engine to Customized Backend	  
	  **************************************

	  In addition to configuring the user interface to accept the required inputs, it is necessary
	  to make the custom UQ engine accessible to the customized UQ backend in quoFEM. This is achieved
	  by providing a UQ runner class in Python that follows the defined interface. Users must create
	  a UQ runner class that inherits from the *UqRunner* class, which is shown :ref:`below <uqRunner>`

	  .. _uqRunner:
	  .. literalinclude:: uqRunner.py
	     :language: python

	  This runner class only needs to provide a *runUQ* method and a factory class
	  that creates an instance of this class. The *runUQ* method is where the
	  customized inputs from the user interface can be accessed and passed to the
	  custom UQ driver.

	  .. note::

	     The parameters generated by the UQ engine must be stored in a file named
	     ``params.in`` and placed in the current working directory. The file must
	     follow the format shown in the example ``params.in`` file shown :ref:`below
	     <paramsIn>`. The first line specifies the number of random variables while
	     the subsequent lines first contain the name of the random variable and the
	     value of the current realization separated by a space.

	     .. _paramsIn:
	     .. literalinclude:: params.in   


	  As an example, **UQpy** has been implemented in the customized
	  backend--the source code for the customized *UqRunner* class can be found in the
	  quoFEM repository in the ``repositoryRoot/applications/performUQ/other``
	  directory.

	  Lastly, the name of the UQ driver needs to be added to *configureAndRunUQ.py* in
	  the list of UQ driver options--this corresponds to the UQ driver name provided
	  in the customized user interface. The *configureAndRunUQ.py* file is also
	  located in *repositoryRoot/applications/performUQ/other*. With the derived UQ
	  runner class and the name of the UQ driver added to the list of UQ driver
	  options, the custom UQ engine has been plugged into the quoFEM backend and can
	  now be invoked from the quoFEM user interface

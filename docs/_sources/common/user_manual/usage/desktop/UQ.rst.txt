
UQ: Uncertainty Quantification
==============================

The first selection panel the user must select from and enter data into is the **UQ** tab. It is in this panel where the user selects the **UQ Engine** to use for performing the uncertainty quantification calculations. Presently the **UQ Engine** option supports Dakota and SimCenterUQ engine.

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

	  :quoFEM:SimCenterUQSensitivity


UCSD UQ Engine
--------------

This is a module developed at UCSD. This module currently offers support for Bayesian calibration using the Transitional Markov chain Monte Carlo (TMCMC) algorithm, which is also known as the Sequential Monte Carlo algorithm:

.. toctree-filt::
   :maxdepth: 1

   :quoFEM:UCSD_UQ_TMCMC

Custom UQ Engine
----------------
This option allows the user to plug different UQ engines into the quoFEM workflow such that different uncertainty quantification
methods and tools can be easily applied within the SimCenter framework.

.. toctree-filt::
   :maxdepth: 1

   :quoFEM:CustomUQ

.. _lblUCSDTMCMC:


Transitional Markov chain Monte Carlo (TMCMC) algorithm
*******************************************************

This is an algorithm which is used to draw samples from the posterior probability distribution of random variables when performing Bayesian estimation. To use the TMCMC algorithm, select the **UCSD_UQ** engine in the **UQ** panel. Currently, only the TMCMC method is available with the **UCSD_UQ** engine. In the **Log Likelihood Script** field, the user needs to provide the path to a Python script which contains a function called ``log_likelihood`` that returns the log-likelihood value. The user also needs to specify the number of samples that is desired to be drawn from the posterior probability distribution of the unknown parameters. 

.. figure:: figures/TMCMC_UQ_Engine.png
	:align: center
	:figclass: align-center

  	TMCMC algorithm input panel.


Defining the log-likelihood function
====================================

By allowing users to define a ``log_likelihood`` function in the **Log Likelihood Script**, the workflow provides users full control in defining the log-likelihood model they desire to use. 
The ``log_likelihood`` function is called internally during the execution of the TMCMC algorithm, and this function must compute and return the log-likelihood value at a point in the parameter space. The function must take four arguments as shown: ``log_likelihood(particleNum, par, variables, resultsLocation)``. Here, ``particleNum`` is the sample index, which is an integer between ``0`` and ``# Samples - 1``; ``par`` is the corresponding vector of parameter values at which the log-likelihood must be evaluated; ``variables`` is a dictionary that contains information required to define the prior probability distribution of the parameters; and ``resultsLocation`` is a string that defines the path to the directory where the analysis is conducted. These arguments are passed to the log-likelihood function internally by the TMCMC algorithm. 

The **Log Likelihood Script** must import a function called``runFEM`` from the ``runFEM`` module, and call this function within the body of the ``log_likelihood`` function as follows: ``runFEM(ParticleNum, par, variables, resultsLocation)``. The ``runFEM`` function evaluates the model using the parameter values passed in as the ``par`` argument, and writes the results to a file called ``results.out``. The results of the model evaluation must be read from this file and used to evaluate the log-likelihood. The data required to evaluate the log-likelihood is also defined within the **Log Likelihood Script**. 

An example **Log Likelihood Script** is shown below:

.. literalinclude:: postProcessing.py
   :language: python

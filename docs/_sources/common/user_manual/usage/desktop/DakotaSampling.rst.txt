
.. _lblDakotaForward:

Forward Propagation Methods
***************************
 
The forward propagation analysis provides probabilistic understanding of output variables by producing sample realizations and statistical moments (mean, standard deviation, skewness, and kurtosis). Currently five sampling methods are available: Monte Carlo Sampling (MCS), Latin Hypercube Sampling (LHS), Importance Sampling (IS), and sampling based on surrogate models, including Gaussian Process Regression (GPR) and Polynomial Chaos Expansion (PCE). Depending on the option selected, the user must specify the appropriate input parameters. For instance, for MCS, the number of samples specifies the number of simulations to be performed, and providing a random seed allows the user to reproduce the sampling results multiple times. The user selects the sampling method from the dropdown ``Methods`` menu. Additional information regarding sampling techniques offered in Dakota can be found `here <https://dakota.sandia.gov//sites/default/files/docs/6.9/html-ref/method-sampling.html>`_. 

Monte Carlo Sampling (MCS) 
^^^^^^^^^^^^^^^^^^^^^^^^^^

MCS is among the most robust and universally applicable sampling methods. Moreover, the convergence rate of MCS methods are independent of the problem dimensionality, albeit the convergence rate of such MCS methods is relatively slow at :math:`N^{-1/2}`. In MCS, a sample drawn at any step is independent of all previous samples. 

:numref:`figMCS` shows the input panel corresponding to the Monte Carlo Sampling setting. Two input parameters need to be specified: the number of samples to be executed, and the random seed.

.. _figMCS:

.. figure:: figures/fwMC.png
	:align: center
	:figclass: align-center

  	Monte Carlo Sampling input panel.


Latin Hypercube Sampling (LHS)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Latin hypercube sampling (LHS) is a pseudo-random, stratified sampling approach. To achieve a better convergence, LHS evenly spreads out the samples to cover the whole range of the input domain. Each sample from LHS effectively represents each of N equal probability intervals of a cumulative density function.  

:numref:`figLHS` shows the input panel corresponding to the Latin hypercube sampling (LHS) scheme. Two input parameters need to be specified: the number of samples to be executed and the random seed.


.. _figLHS:

.. figure:: figures/fwLHS.png
	:align: center
	:figclass: align-center

	Latin Hypercube Sampling input panel.


Importance Sampling (IS)
^^^^^^^^^^^^^^^^^^^^^^^^

For problems where one is interested in the rare events rather than the whole distribution of output, such as earthquake or storm surge events, conventional sampling methods may require an excessively large number of simulations to obtain an accurate estimation of tail distribution. For such problems, importance sampling (IS) provides a bypass to conventional sampling methods (MCS or LHS), whereby an alternative sampling distribution is introduced around the tail part of the original distribution so that the generated samples have a better resolution at the domain of interest.

:numref:`figIS` shows the input panel for IS scheme. Similar to MCS and LHS, IS requires both the number of samples to be executed and the corresponding seed for generating such random samples. In addition, IS algorithm can be performed via three different approaches, as specified by the third input method:

1.  **Basic Sampling**: A sampling density is constructed in the failure region based on an initial LHS sampling, followed by generation of importance samples and weights and evaluation of the Cumulative Distribution Function.  
2. **Adaptive Sampling**: The basic sampling procedure is repeated iteratively until a convergence in failure probability is achieved. 
3. **Multimodal Adaptive Sampling**: A multimodal sampling density is constructed based on samples in the failure and the adaptive sampling procedure is used.


.. _figIS:

.. figure:: figures/fwIS.png
	:align: center
	:figclass: align-center

	Importance Sampling input panel.


For more information on each, please refer to the Dakota manual. 


Gaussian Process Regression (GPR)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

For the problems which computationally expensive models are involved, conventional sampling schemes such as LHS and MCS can be extremely time-consuming. In such case, surrogate model can be constructed based on fewer number of simulation runs, and then the surrogate model can be used to efficiently generate required number of samples replacing the expensive simulations.

Gaussian Process Regression (GPR), also known as Kriging is one of the well-established surrogate techniques, which constructs an approximated response surface based on Gaussian process modeling and covariance matrix optimizations. :numref:`figGPR` shows the input panel for the GPR model that consists of training and sampling panels. 


.. _figGPR:

.. figure:: figures/fwGP.png
	:align: center
	:figclass: align-center

  	GPR forward propagation input panel.


Polynomial Chaos Expansion (PCE)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Response surface can be approximated using Polynomial Chaos Expansion (PCE) model as well. Similar to the input GPR panel, input panel for PCE model shown in :numref:`figPCE` consists of training and sampling parts. The input parameters in the *surrogate training data* set specify the dataset used for training the surrogate model, while the parameters in the *surrogate sampling data* are related to the samples generated using the surrogate. Extreme care must be taken in specifying the parameters of the training dataset to results in an accurate response surface approximation. 


.. _figPCE:

.. figure:: figures/fwPCE.png
	:align: center
	:figclass: align-center

	PCE forward propagation input panel.


If the user is not familiar with the training parameters of the surrogates, it is recommended to refrain from using the surrogates (PCE in particular) and instead use conventional sampling such as MCS and LHS, even at a higher computational cost. 



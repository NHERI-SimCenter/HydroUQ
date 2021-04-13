

Methods in UCSD UQ Engine 
*************************

Transtitional Markov chain Monte Carlo
======================================

TMCMC is a numerical method used to obtain samples of the target posterior PDF. This algorithm is flexible, applicable in general settings, and parallelizable. Thus, it can be used to effectively sample the posterior PDF, when the likelihood function involves a computationally expensive FE model evaluation, using high-performance computing (HPC) resources.


In Bayesian inference, the posterior probability distribution of the unknown quantities, represented by the vector :math:`\mathbf{\theta}`, is obtained by applying Bayes' rule as follows:

.. math::
   p (\mathbf{\theta \ | \ y}) = \frac{p (\mathbf{y \ | \ \theta}) \times p(\mathbf{\theta})}{\int p (\mathbf{y \ | \ \theta}) \times p(\mathbf{\theta}) \ d\mathbf{\theta}}


The idea behind TMCMC is to avoid sampling directly from the target posterior PDF :math:`p(\mathbf{\theta \ | \ y})`,
but to sample from a series of simpler intermediate probability distributions that converge to the target posterior PDF. To achieve this, the TMCMC sampler proceeds through a series of stages, starting from the prior PDF until the posterior PDF. These intermediate probability distributions (called tempered posterior PDFs) are controlled by the tempering parameter :math:`\beta_j` as 

.. math::
   p(\theta|y)_j \propto p(y | \theta)^{\beta_j} \times p(\theta); \quad j = 0, 1, \ldots, m; \quad 0 = \beta_0 < \beta_1 < \ldots < \beta_m = 1

Index :math:`j` denotes the stage number, :math:`m` denotes the total number of stages, and :math:`p (\mathbf{\theta \ | \ y})_j` is the tempered posterior PDF at stage :math:`j` controlled by the parameter :math:`\beta_j`. At the initial stage :math:`(j = 0)`, parameter :math:`\beta_0 = 0`, the tempered distribution :math:`p(\mathbf{\theta \ | \ y})_{j=0}` is just the
prior joint PDF :math:`p(\theta)`. The TMCMC sampler progresses by monotonically increasing the value of :math:`\beta_j` , at each stage :math:`j`, until it reaches the value of 1. At the final stage :math:`(j = m)`, parameter :math:`\beta_m = 1`, the tempered distribution :math:`p(\mathbf{\theta \ | \ y})_{j = m}` is the target posterior joint PDF :math:`p(\mathbf{\theta \ | \ y})`. 


TMCMC represents the tempered posterior PDF at every stage by a set of weighted samples (known as particles). TMCMC approximates the :math:`j^{th}` stage tempered posterior PDF :math:`p(\mathbf{\theta \ | \ y})_j`  by weighing, resampling, and perturbing the particles of the :math:`j-1^{th}` stage intermediate joint PDF :math:`p(\mathbf{\theta \ | \ y})_{j-1}` . For details about the TMCMC algorithm, the interested reader is referred to Ching and Chen [Ching2007]_, Minson et. al. [Minson2013]_.


.. [Ching2007] 
   J. Ching and Y.-C. Chen, “Transitional Markov Chain Monte Carlo Method for Bayesian Model Updating, Model Class Selection, and Model Averaging”, *Journal of Engineering Mechanics*, 133(7), 816-832, 2007.
   
.. [Minson2013] 
   S. E. Minson, M. Simons, and J. L. Beck, “Bayesian Inversion for Finite Fault Earthquake Source Models I-Theory and Algorithm”, *Geophysical Journal International*, 194(3), 1701- 1726, 2013.
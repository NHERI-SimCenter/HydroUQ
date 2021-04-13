

Methods in SimCenterUQ Engine 
*****************************

Nataf Transform
================

Nataf transform is introduced to convert the samples in the standardized normal space (U-space) into physical space (X-space) and vise versa ([Liu86]_). The SimCenterUQ engine contains a part of the program developed by [ERA19]_ to generate the samples of the random variables.

.. [Liu86]
   Liu, Pei-Ling and Armen Der Kiureghian (1986) Multivariate distribution models with prescribed marginals and covariances. *Probabilistic Engineering Mechanics* 1(2), 105-112

.. [ERA19]
   Engineering Risk Analysis Group, Technische Universität München: https://www.bgu.tum.de/era/software/eradist/ (Matlab, python programs and documentations)



Variance-based global sensitivity indices
=========================================

Global sensitivity analysis is performed to quantify the contribution of each input variable to the uncertainty in QoI. Using the global sensitivity indices, users can set preferences between random variables considering both inherent randomness and its propagation through the model. Global sensitivity analysis helps users to understand the overall impact of different sources of uncertainties, as well as to accelerate UQ computations by focusing on dominant dimensions or screening out trivial input variables.

.. _figSensitivity1:

.. figure:: figures/SimCenterSensitivity1.png
   :align: center
   :figclass: align-center

   Concept of global sensitivity analysis
	
	
Sobol indices are widely used variance-based global sensitivity measures. It has two types: main effect and total effect sensitivity indices. The **main effect index** quantifies the fraction of variance in QoI that can be attributed to specific input random variable(s) but without considering interactive effect with other input variables. The **total effect index**, on the other hand, additionally takes the interactions into account.

Given the output of model :math:`y=g(\boldsymbol{x})` and input random variables :math:`\boldsymbol{x}=\{x_1,x_2, \cdots ,x_d\}`, the first-order main and total effect indices of each input variable is defined as


.. math::
	:label: Si
	
	S_i=\frac{\text{Var}_{x_i}[\text{E}_{\boldsymbol{x}_{\sim i}}[y|x_i]]}{\text{Var}[y]}, \qquad i=1, \cdots ,d
	
   
.. math::
	:label: SiT

	S_i^T=\frac{\text{E}_{\boldsymbol{x}_{\sim i}}[\text{Var}_{x_i}[y|\boldsymbol{x}_{\sim i}]]}{\text{Var}[y]},  \qquad  i=1, \cdots ,d


respectively, where :math:`\boldsymbol{x}_{\sim i}` indicates the set of all input variables except :math:`x_i`. It is noteworthy that in both equations, the variance operator :math:`\text{Var}_{x_i}[\cdot]` captures only the part of uncertainty associated with :math:`x_i`, while the mean operator :math:`\text{E}_{\boldsymbol{x}_{\sim i}}[\cdot]` averages out all remaining uncertainties. From the definitions, two indices theoretically have values between zero and one. Eq. :eq:`Si` can also be understood intuitively. For example, if the QoI is insensitive to :math:`x_i`, the term inside :math:`\text{Var}_{x_i}[\cdot]` is nearly constant and :math:`S_i` approaches zero. On the other hand, when one single variable :math:`x_i` dominates QoI, inside :math:`\text{Var}_{x_i}[\cdot]` is approximately the same as :math:`y`, and thus :math:`S_i` approaches one. Eq. :eq:`SiT` can be understood in similar ways. The second-order main effect index that provides the pair-wise interaction effect is defined as

.. math::
	:label: Sij

	S_{ij}=\frac{\text{Var}_{x_i,x_j}[\text{E}_{\boldsymbol{x}\sim ij}[y|x_i,x_j]]}{\text{Var}[y]} - S_i - S_j,  \qquad  i,j=1, \cdots ,d
	
where :math:`\boldsymbol{x}_{\sim ij}` indicates the set of all input variables except :math:`x_i` and :math:`x_j`. The higher-order indices are derived likewise. Theoretically, When all the input variables are uncorrelated to each other, the following equality holds.

.. math::

	\sum^d_{i=1} S_i + \sum^d_{i<j} S_{ij} + \cdots + S_{12 \cdots d} = 1 


Estimation of Sobol indices
=============================

Global sensitivity analysis is typically computationally expensive. High computation cost attributes to the multiple integrations (:math:`d`-dimensional) associated with the variance and expectation operations shown in Eqs. :eq:`Si` and :eq:`SiT`. To reduce the computational cost, efficient Monte Carlo methods, stochastic expansion methods, or meta model-based methods can be employed. Among different approaches, the SimCenterUQ engine supports the probability model-based global sensitivity analysis (PM-GSA) framework developed by [Hu19]_. 

The framework first conducts ordinary MCS to obtain input-output data pairs. Then by extracting only a subset dimension of the dataset, it approximates the probability distribution of a reduced dimension which is required for estimating the Sobol index. Among different probability models introduced in [Hu19]_ to approximate this lower dimension distribution, the Gaussian mixture model is implemented. For example, to identify 1st order main Sobol index for a variable :math:`x_i`, a bivariate Gaussian mixture model is fitted for the joint probability distribution of :math:`x_i` and :math:`y`, i.e.

.. math::
	:label: GM

	f_{x_i,y}(x_i,y) \simeq f_{x_i,y}^{GM} (x_i,y)
	

using expectation-maximization (EM) algorithm. The mean operation Eq. :eq:`Si` is then derived analytically derived using Gaussian mixture model, while variance is approximated by the sample variance. Therefore, the accuracy of the method depends on the quality of the base samples as well as the fitness of the mixture model. The below figure summarizes the procedure of Gaussian mixture model-based PM-GSA introduced in [Hu19]_. The number of mixture components is optimized along with the mixture parameters during expectation-maximization iterations. 

.. _figSensitivity2:

.. figure:: figures/SimCenterSensitivity2.png
	:align: center
	:figclass: align-center

  	Data-driven global sensitivity analysis by Hu and Mahadevan (2019)

.. [Hu19]
   Hu, Z. and Mahadevan, S. (2019). Probability models for data-driven global sensitivity analysis. *Reliability Engineering & System Safety*, 187, 40-57.




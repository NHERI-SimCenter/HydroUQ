.. _lblDakotaSensitivity:


Global Sensitivity Analysis
***************************

Global sensitivity analysis is used to quantify contribution of each input variable to the uncertainty in QoI. Using the global sensitivity indices, users can set preferences between random variables considering both inherent randomness and its propagation through the model. Global sensitivity analysis helps users to understand the overall impact of different sources of uncertainties and their intersections, as well as to accelerate UQ computations by focusing on dominant dimensions or screening out trivial input variables. This can also be useful identifying the input variables for which extra experimentation/research may be useful in reducing the uncertainty in the initial specification.

**Sobol indices** are widely used variance-based global sensitivity measures which has two types: main effect and total effect sensitivity indices. The **main effect index** quantifies the fraction of variance in QoI that can be attributed to specific input random variable(s) but without considering interactive effect with other input variables. The **total effect index**, on the other hand, additionally takes the interactions into account.

Given an output of a model :math:`y=g(\boldsymbol{x})` and input random variables :math:`\boldsymbol{x}=\{x_1,x_2, \cdots ,x_d\}`, the first-order main and total effect indices of each input variable :math:`x_i` is defined as

	
.. math::
	:label: Si
	
	S_i=\frac{\text{Var}_{x_i}[\text{E}_{\boldsymbol{x}_{\sim i}}[y|x_i]]}{\text{Var}[y]}, \qquad i=1, \cdots ,d
	
.. math::
	:label: SiT

	S_i^T=\frac{\text{E}_{\boldsymbol{x}_{\sim i}}[\text{Var}_{x_i}[y|\boldsymbol{x}_{\sim i}]]}{\text{Var}[y]},  \qquad  i=1, \cdots ,d


respectively, where :math:`\boldsymbol{x}_{\sim i}` indicates the set of all input variables except :math:`x_i`. From the definitions, two indices theoretically have values between zero and one. The second-order main effect index that provides the pair-wise interaction effect is defined as

.. math::
	:label: Sij

	S_{ij}=\frac{\text{Var}_{x_i,x_j}[\text{E}_{\boldsymbol{x}\sim ij}[y|x_i,x_j]]}{\text{Var}[y]} - S_i - S_j,  \qquad  i,j=1, \cdots ,d
	
where :math:`\boldsymbol{x}_{\sim ij}` indicates the set of all input variables except :math:`x_i` and :math:`x_j`. The higher-order indices are derived likewise. When all the input variables are uncorrelated to each other, the following equality holds.

.. math::
	:label: Sbound

	\sum^d_{i=1} S_i + \sum^d_{i<j} S_{ij} + \cdots + S_{12 \cdots d} = 1 

When the variables are correlated to each other, the summation may be greater or smaller than one.


First-order Sobol indices
^^^^^^^^^^^^^^^^^^^^^^^^^

In the SimCenterUQ engine, Sensitivity indices are estimated by Gaussian mixture model-based probability distribution approximation framework presented in Hu and Mahadevan (2019) [Hu19]_. To run this sensitivity analysis, the user has to specify the number of samples and a random seed. The framework can handle correlated random variables as well.

.. _figSimSensitivity:

.. figure:: figures/SensitivityAnalysisSimUQ.png
	:align: center
	:figclass: align-center

  	Sensitivity analysis input panel.

.. note::

   - The numerical results of global sensitivity analysis may show negative values due to the sampling variability.
   - The numerical results of Eq. :eq:`Sbound` for uncorrelated inputs may not hold due to the sampling variability and approximation errors. If this error is very high, the sensitivity index may not be reliable. However, the sensitivity rank between variables is relatively robust.
   - When a constant variable is defined, the sensitivity analysis algorithm will ignore the variable.

Group-wise Sobol indecies
^^^^^^^^^^^^^^^^^^^^^^^^^^^

By default, the analysis results are first-order sensitivity indices of each random variable. User may activate the option to specify advanced outputs at the bottom of the **QoI** tab. Using this option, the user can manually provide groups of relevant random variables to get so-called group-wise Sobol indices.

.. _figSimSensitivity2:

.. figure:: figures/SensitivityAnalysis2SimUQ.png
   :align: center
   :figclass: align-center

   Group-wise Sobol indicies
	
The group-wise Sobol indices are useful when the user wants to obtain a sensitivity measure corresponding to a categorical group of input variables, for example, to compare the relative sensitivity between structural parameters and excitation parameters. In particular, when there are non-causal correlations between some random variables or when the user expects interactive contributions of the random variables that are in nature inseparable, one can introduce the group index. The group-wise Sobol index for joint variables :math:`x_i` and :math:`x_j` is defined as

.. math::
	:label: GroupSij

	S_{ij}^G=\frac{\text{Var}_{x_i,x_j}[\text{E}_{\boldsymbol{x}\sim ij}[y|x_i,x_j]]}{\text{Var}[y]},  \qquad  i,j=1, \cdots ,d


In order to associate more input variables, the set {:math:`x_i,x_j`} can be simply replaced by a larger set, e.g. {:math:`x_i,x_j,x_k`}. Results of Eq. :eq:`GroupSij` can be post-processed to obtain higher-order Sobol indices presented in Eq. :eq:`Sij`, i.e. it is obtained by subtracting the lower-order interaction terms from the group index. 

.. note::

   - When multiple outputs are considered, global sensitivity analysis is performed separately for each QoI, but the base Monte Carlo samples are can be re-used for different QoIs. 
   - When random variables defined in **RV** tab is not exhaustive, i.e. if the model contains *unexplained* randomness, total Sobol index value may be underestimated by omitting the interaction with the missing variables.


.. [Hu19]
   Hu, Z. and Mahadevan, S. (2019). Probability models for data-driven global sensitivity analysis. *Reliability Engineering & System Safety*, 187, 40-57.


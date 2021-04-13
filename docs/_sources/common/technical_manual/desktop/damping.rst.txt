.. _lblDamping:

Damping Options
===============

The standard equations that are solved in the nonlinear analysis of structures subjected to dynamic forces are:

.. math::
   
   M \ddot{U}(t) + C \dot{U}(t)  + Fs(U(t)) = P(t)

where :math:`U(t), \dot{U}(t), \ddot{U}(t)` are the vectors of displacements, velocities, and accelerations for the degrees of freedom, :math:`M` and :math:`C` are the mass and damping matrices, respectively, and the vector :math:`Fs(U)` represents the nonlinear relation between resisting forces and deformations, which includes both material and geometric nonlinearities, and :math:`P(t)` the time-varying applied load due to the event of interest. 

Energy is dissipated by the structure as it deforms, which is why it to come to rest when the force is removed. The :math:`Fs(U(t))` term captures the **hysteretic** energy dissipated through the nonlinear behavior of the structural members. The :math:`C \dot{U}(t)` term, the **viscous** damping term, attempts to capture energy dissipated through other  mechanisms present in the structure, e.g. thermal effects from repeated elastic straining of structural materials, repeated straining of nonstructural elements—partition walls, mechanical equipment, fire proofing, and so on—friction at steel connections, opening and closing of microcracks in concrete, friction between the structure itself and nonstructural elements, and other mechanisms, some of which are even difficult to identify. Damping for such is often quantified in terms of **modal** damping ratios, and are typically of the order of 1% (steel buildings) to 5% (concrete buildings). These the values have been obtained from field testing and system identification, albeit they have mostly been obtained from buildings undergoing low levels of vibration.

It is the formulation of the :math:`C` matrix that is of interest here. There are two damping options presented to the user as inputs to the :ref:`FEM <lblFEM>` panel: 1) Rayleigh Damping Options and 2) Modal Damping options. This is a brief overview of the theory behind both.


Rayleigh Damping
----------------

A classical damping matrix can be assembled as a linear combination of the mass and stiffness matrices:

.. math::
   
   C = a_0 M + a_1 K

is known as **Rayleigh damping** , is the most common—almost pervasive—model in nonlinear analysis of structures. The damping ratio for the nth mode of such a system is

.. math::

   \zeta_n = \frac{a_0}{2}\frac{1}{\omega_n} + \frac{a_1}{2}\omega_n

The coefficients :math:`a_0` and :math:`a_1` are typically determined by specifying the damping ratios at one or two modes :math:`\zeta_1` and :math:`\zeta_2`. There are a number of options:

#. **Mass Proportional Damping**, :math:`C = a_0 M` 

   .. math::

      \zeta_n = \frac{a_0}{2}\frac{1}{\omega_n}

      a_0 = 2 \zeta_n \omega_n

   In mass proportional damping, the damping matrix is inversely proportional to the natural frequency. The coefficient is chosen to represent the period at a single mode, modes with a higher frequency will have less damping, and modes with a smaller frequency will have more damping.

#. **Stiffness Proportional Damping**, :math:`C = a_1 K`

   .. math::

      \zeta_n = \frac{a_1}{2}\omega_n

      a_1 = \frac{2 * \zeta_n}{\omega_n}

   In stiffness proportional damping, the damping is proportional to the natural frequency, increasing linearly as the natural frequency increases. The coefficient is again chosen to represent the period at a single mode, modes with a higher frequency will have more damping, and modes with a smaller frequency will have less damping.


#. **Traditional Rayleigh Damping**, :math:`C = a_0 M + a_1 K`

   .. math::

      \zeta_n = \frac{a_0}{2}\frac{1}{\omega_n} + \frac{a_1}{2}\omega_n

   Two coefficients are determined by the user specifying the damping at two different modes given by :math:`\omega_i` and :math:`\omega_j` [Rayleigh45]_:

   .. math::

      \frac{1}{2} \begin{bmatrix} 
               1/\omega_i & \omega_i \\
            1/\omega_j & \omega_j \\
            \end{bmatrix} 
            \begin{bmatrix}
            a_0 \\
            a_1
            \end{bmatrix} 
            = 
            \begin{bmatrix}
            \zeta_i \\
            \zeta_j
            \end{bmatrix}

   as the damping at these two modes is usually specified to be the same, i.e. :math:`\zeta_i = \zeta_j = \zeta`, this matrix equation can  be solved for :math:`a_0` and :math:`a_1` 

   .. math::

      a_0 = \zeta \frac{2 \omega_i \omega_j}{w_i + w_j} ; a_1 = \zeta \frac{2}{w_i + w_j}


.. note:: 
   
   In the tool the user has the option of specifying which of the stiffness matrices (the current linearized stiffness matrix or the initial tangent stiffness matrix). Opinion in the literature is divided, the default is set to the initial stiffness as the possible inclusion of negative damping (should the descending branch of yield curve be reached), the possibility of including zero damping (should elastic perfectly plastic materials yield), and the very fact that the damping is tied to the hysteretic behavior given why it is included in the first place, makes little physical sense.

   Different approaches are of course possible, e.g. where user explicitly models damping. These must be specified by the user in the optional analysis script they provide.



Modal Damping
---------------

In modal damping the eigenvectors :math:`\Phi` of the :math:`N` degree-of-freedom system are used to create the :math:`C` matrix.

.. math::

   C = M \left ( \sum_{m=1}^{N} \frac{2 \zeta_m \omega_m}{M_m} \phi_m \phi_m^TC \dot{U} \right ) M

where the :math:`m`'th term is the contribution of the :math:`m`'th mode. The resulting damping matrix has not been popular in practical analyses because it is a fully populated matrix and its construction requires all frequencies and modes. However many FEM applications approximate this by limiting number of modes to first :math:`n` modes, not including those components outside the sparsity pattern of the :math:`K` matrix, **AND** including all terms in the calculation of the resisting forces to ensure that convergence to correct numerical solution occurs, albeit at a slower rate of convergence.

.. math:: 

   C = M \left ( \sum_{m=1}^{n} \frac{2 \zeta_m \omega_m}{M_m} \phi_m \phi_m^TC \dot{U} \right ) M

.. note:: 

   A drawback of this practical implementation is that higher modes are undamped. To overcome this, FEM applications that permit modal damping also permit it to be combined with **stiffness proportional damping**, where at the last mode of interest, :math:`n`, a damping ratio is specified for the calculation of tangent stiffness rayleigh damping. That is the purpose of the additional damping ratio to be provided by the user for the last mode specified, :math:`\zeta_{nT}`, which by default in the tool is set to 0.0. If specified to be non-zero, the damping matrix provided is:

   .. math::

      C = M \left ( \sum_{m=1}^{n} \frac{2 \zeta_m \omega_m}{M_m} \phi_m \phi_m^TC \dot{U} \right ) M + a_1 K_0

   where :math:`a_1 = \frac{2 * \zeta_{nT}}{\omega_{n}}`


.. [Rayleigh45]

   Rayleigh L. Theory of Sound, 1. Dover: New York, NY, 1945.

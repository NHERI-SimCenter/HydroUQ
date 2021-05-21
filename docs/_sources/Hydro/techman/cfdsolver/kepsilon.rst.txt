k-Epsilon model
==================
 
k-:math:`\epsilon` model was originally proposed by [LaSp1974]_. It is one of the most common model used for simulation of turbulent flow conditions. The model introduces two variable transport equation related to:

- Turbulence kinetic energy (k)

- Rate of dissipation of turbulence kinetic energy(:math:`\epsilon`)

The k-:math:`\epsilon` model is one of the most popular models and widely used for a range of applications from industrial to environmental flows. This popularity can be attributed to the fact that it remains one of the simplest turbulence models, has good convergence properties and lower memory requirements. It is also often used to provide an initial estimate for more complex turbulent wall models. This model is not recommended for unconfined flows, flow cases involving strong curvatures, rotating flows etc.

k-:math:`\epsilon` model focuses on the mechanisms that affect the turbulent kinetic energy. The underlying assumtion is that the turbulent viscosity is isotropic. This imples that the ratio between the Reynolds' stress and the mean rate of deformation is same in all directions. The standard k-:math:`\epsilon` model proposed by [LaSp1974]_ includes additional transport equations given as

- For turbulent kinetic energy :math:`(k)`

    .. math::

        \underbrace{\frac{\partial \left(\rho k\right)}{\partial t}}_{T1} + \underbrace{\frac{\partial \left(\rho k u_i\right)}{\partial x_i}}_{T2} = \underbrace{\frac{\partial}{\partial x_j} \left[ \frac{\mu_t}{\sigma_k} \frac{\partial k}{\partial x_j} \right]}_{T3} + \underbrace{2\mu_i E_{ij} E_{ij}}_{T4} - \underbrace{\rho \epsilon}_{T5}

- For dissipation (:math:`\epsilon`)

    .. math::

        \underbrace{\frac{\partial \left(\rho \epsilon\right)}{\partial t}}_{T1} + \underbrace{\frac{\partial \left(\rho \epsilon u_i\right)}{\partial x_i}}_{T2} = \underbrace{\frac{\partial}{\partial x_j} \left[ \frac{\mu_t}{\sigma_{\epsilon}} \frac{\partial \epsilon}{\partial x_j} \right]}_{T3} + \underbrace{C_{1\epsilon} \frac{\epsilon}{k} 2\mu_t E_{ij} E_{ij}}_{T4} - \underbrace{C_{2\epsilon} \rho \frac{\epsilon^2}{k}}_{T5}

where :math:`u_i` represent the velocity components, :math:`E_{ij}` represent the component of rate of deformation, :math:`\mu_t = \rho C_{\mu} \frac{k^2}{\epsilon}` represents the eddy viscosity. The other constants :math:`\sigma_{k}, \sigma_{\epsilon}, C_{1\epsilon}, C_{2\epsilon}` are adjustable constants.

The physical interpretation of the various terms in the above equation are as follows:

- **T1**: Rate of change of :math:`k/\epsilon` in time

- **T2**: Transport of :math:`k/\epsilon` by advection

- **T3**: Transport of :math:`k/\epsilon` by diffusion

- **T4**: Rate of production of :math:`k/\epsilon` 

- **T5**: Rate of destruction of :math:`k/\epsilon`



References
------------

.. [LaSp1974] B.E. Launder and D.B. Spalding, "The numerical computation of turbulent flows," Computer Methods in Applied Mechanics and Engineering, vol. 3(2), pp. 269 - 289 (1974)
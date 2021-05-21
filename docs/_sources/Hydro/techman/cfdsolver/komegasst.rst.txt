k-Omega SST model
===============================

The k-:math:`\omega` Shear Stress Transport (SST) turbulence model was originally proposed by [Me1994]_ as a two-equation eddy-viscosity model. The version available in Hydro-UQ is based on the implementation of [MeKuLa2003]_ which is available through OpenFOAM.

The standard k-:math:`\omega` model is well suited for simulating the flow in the sub-viscous layer while the k-:math:`\epsilon` model is ideal for predicting the flow slightly away from the wall. Further on, the standard k-:math:`\omega` is more suitable for low-Reynolds number flows, highly nonlinear, often sensitive to the initial guess and thus more difficult to converge. 

Alternatively, the k-:math:`\omega` SST is a hybrid model that combines the advantages of the k-:math:`\omega` and k-:math:`\epsilon` models by switching between them. The k-:math:`\omega` SST model uses the k-:math:`\omega` model is used near the wall and switches to the k-:math:`\epsilon` model as it approaches the free-stream. The SST models are generally less sensitive to the free-stream conditions and avoid build-up of excessive turbulent kinetic energy near `stagnation points <https://en.wikipedia.org/wiki/Stagnation_point>`_ as compared to the usual k-:math:`\epsilon` models.

The governing equations of the k-:math:`\omega` SST model are based on the turbulence kinetic energy :math:`(k)` and the turbulence specific dissipation rate :math:`(\omega)`. They are

- For turbulence kinetic energy :math:`(k)`

    .. math::

        \frac{D}{Dt} \left(\rho k\right) = \nabla \cdot \left( \rho D_k \nabla k \right) + \rho G - \frac{2}{3} \rho k \left(\nabla \cdot \mathbf{u}\right) - \rho \beta^{*} \omega k + S_k

- For turbulence specific dissipation rate :math:`(\omega)`

    .. math::

        \frac{D}{Dt} \left(\rho \omega\right) = \nabla \cdot \left( \rho D_k \nabla \omega \right) + \frac{\rho \gamma G}{\nu} - \frac{2}{3} \rho \gamma \omega \left(\nabla \cdot \mathbf{u}\right) - \rho \beta \omega^2 - \rho \left(F_1 - 1 \right) CD_{k\omega} + S_{\omega}

The turbulence viscosity is obtained as

.. math::

    \nu_t = a_1 \frac{k}{\text{max} \left( a_1, \omega, b_1, F_{23} \right)}


References
------------

.. [Me1994] F.R. Menter, "Two-equation eddy-viscosity turbulence models for engineering applications," AIAA Journal, vol. 32(8), pp. 1598-1605 (1994)

.. [MeKuLa2003] F.R. Menter, M. Kuntz, and R. Langtry, "Ten years of industrial experience with the SST turbulence model," In Proceedings of the fourth international symposium on turbulence, heat and mass transfer, pages 625–632, Antalya, Turkey, 2003. Begell House

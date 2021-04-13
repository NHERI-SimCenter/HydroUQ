.. _lbl-bestpractices:

*********************
Best Practices
*********************

Froude number
=================

#. One of the important non-dimensional number that describes diffrent flow regimes for open channel flow. It is a dimensionless quantity that is a ratio of the inertial and gravitational forces as :math:`Fr = \frac{V}{\sqrt{gD}}`. Here ``V`` is the water velocity, ``D`` is the hydraulic depth across the cross-sectional area of the flow and ``g`` is the gravity. 

#. It is important to calculate if the flow is sub-critical (Fr < 1) or critical (Fr = 1) or supercritical (Fr > 1). Critical flows are often unstable and sets up standing waves between sub and supercritical flows. 

#. It is necessary to consider both the Froude number and Reynolds number to determine separation effects like breaking waves etc.

Meshing
==========

#. Mesh checking is always important. ``Hydro-UQ`` performs a mesh check and the log is available for review after the simulation is complete. It is much recommended to review this.

#. Mesh convergence study is critical to ensuring good and reliable results using CFD simulations. 

Boundary conditions
======================

SW-CFD domain sizes
=======================

#. Note that each degree of latitude is approximately 69 miles (111 kms apart). At Equator, the distance is 68.703 miles (110.567 kms), at Tropic of Cancer and Capricon it is 68.94 miles (110.948 kms) and at the poles it is 69.94 miles (111.699 kms).

#. 60 minutes = 1 degree

#. For a 1-minute grid used in the SW-solver, this is approximately 2 x 2 kms grid (in terms of distances). Depending on the topography and bathymetry, this could still be a very large domain for the CFD simulation.

#. If the simulation type is SW-CFD coupling, then there can be wave reflections. Such wave-reflections can lead to unphysical fluid accumulation at the boundary. 

Turbulence modeling
======================

#. Compute the Reynolds number to determine if the flow is turbulent. Do not use turbulent  models for laminar flows

#. Estimate the y+ and the thickness of the first cell layer. The ideal distance of the first node from the wall :math:`\Delta y` can be estimated to be

    .. math::
        \Delta y = L \cdot y^{+} \cdot \sqrt{74} \cdot {Re}_{L}^{-13/14}

    where :math:`L` is the characteristic length scale, :math:`y^{+}` is the desired values, :math:`{Re}_{L}` is the Reynolds number. The non-dimensionalised velocity (:math:`u^{+}`) and distance from the wall (:math:`y^{+}`), the velocity profile of the boundary layers takes on the form, as shown below by the red line in  :numref:`yplusform`.

    .. _yplusform:

    .. figure:: figures/yplus.png
        :align: center
        :height: 400px
        :figclass: align-center

        The variation of non-dimensional velocity and distance

#. There are various online calculators that can be used to calculate the value of :math:`y^{+}`. Some examples of apps include: `Google Play Store <https://play.google.com/store/apps/details?id=com.pointwise.ypluscalculator>`_ or `Apple store <https://apps.apple.com/us/app/y-calculator/id650011524>`_ .

#. If the flow is believed to be viscous, then the viscous sub-layers need to be resolved as shown in :numref:`Viscousyplus`. When meshed correctly, a value of :math:`y^{+} \approx 1` is desired. Alternatively, a wall model can be used bu having the first element in the region :math:`y^{+} > 30`. It is a good practice to avoid a :math:`y^{+}` value between these values. 

    .. _Viscousyplus:

    .. figure:: figures/Viscousyplus.png
        :align: center
        :height: 300px
        :figclass: align-center

        Resolution of the viscous sub-layer

#. High Reynolds number flows (like aircraft, ships etc.) will experience boundary layers that extends to several thousand :math:`y^{+}` units. However, for flows with low Reynolds numbers, the upper limit can be as little as 100 :math:`y^{+}` units. Thus, it is necessary to ensure that the first node does not fall outside this range. 

#. ``Hydro-UQ v1.0.0`` supports :math:`k-\epsilon` and :math:`k-\omega` SST models. These are both good choices for general applications. The :math:`k-\epsilon` model is very reliable and can often be used to get initial values for more sophisticated models.

#. ``Hydro-UQ v1.0.0`` presently supports only RANS simulations for turbulent modeling. In the future versions, LES simulation will also be supported.
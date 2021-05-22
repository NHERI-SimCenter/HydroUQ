Modeling storm surge
========================

Storm surge models are important in predicting and planning for future events. Most storm surge models are two-dimensional, do not resolve the variation with depth but can provide an accurate estimate of the abnormal rise in water level. However, for applications like transportation of pollutants, debris etc., a three-dimensional model is necessary.

Some of the common recipies for a storm surge model are:

- Bathymetry of the area of interest

- Computational mesh that covers the area of interest

- Hurrican information including storm track, wind strength, atmospheric pressure

- Tidal information

Modeling tools and features
------------------------------
Some of the noteworthy models used in modeling storm surge events are 

* SLOSH (Sea, Lake and Overland Surges from Hurricanes) was developed by the National Weather Service in the 1990's [Jeetal1992]_ and is still widely used by the National Hurrican Center owing to its computational efficiency. The SLOSH model separates the US Atlantic and Gulf of Mexico coastline into 32 basins . These model basins are particularly centered around vulnerable features like inlets, low-lying areas, ports etc. Each mesh resolves the ocean bathymetry and land features but does not extend to the open ocean. SLOSH uses a structured grid and finite difference method. More information can be found on `SLOSH website <https://slosh.nws.noaa.gov/slosh/>`_.

* AdCirc (Advanced Circulation) was developed at University of North Carolina by Dr. Rick Luettich. It is capable of resolving very detailed bathymetry in the coastal region. It is often used by FEMA to produce flood insurance rate maps (FIRM's) in several coastal regions. More information can be found on the `AdCirc website <https://adcirc.org/>`_.

* CH3D-SMSS (Storm Surge Modeling System with Curvilinear-grid Hydrodynamics in 3D) uses a horizontally boundary-fitted curvilinear grid and a vertically sigma grid, and hence is suitable for application to coastal and nearshore waters with complex shoreline and bathymetry. More information can be found on the `CH3D website <https://aces.coastal.ufl.edu/CH3D/>`_.


References
-------------

.. [Jeetal1992] C. P. Jelesnianski, J. Chen, and W. A. Shaffer, "SLOSH: Sea, lake, and overland surges from hurricanes," NOAA Technical Report NWS 48, National Oceanic and Atmospheric Administration, U. S. Department of Commerce (1992)

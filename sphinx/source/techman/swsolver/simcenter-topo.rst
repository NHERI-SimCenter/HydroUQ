.. _lbl-simcentertopo:

Topography: SimCenter
=======================

One of the primary inputs for a shallow-water solver includes the bathymetric data. In the SimCenter format for the topography files, the surface of water is considered for references as :math:`z=0`.

The data in the SimCenter 



The topography is assumed as a value of :math:`z` (relative to a particular reference level) at each point :math:`(x,y)`. Most often the water surface is considered as :math:`z=0` for reference. In addition, GeoClaw recognizes only uniformly spaced rectangular topography grids.

It should also be noted here that GeoClaw allows for multiple files to be input for the topography. A bilinear interpolation is used to stitch the files to obtain the domain for the simulation. In regions of intersections, the best available information is used. This is further used to obtain a single top value related to the cell and used in the computations for solving the shallow water equations.

There are four formats supported by GeoClaw and SimCenter presently supports three of these formats as inputs to the Hydro-UQ tool. These formats are highlighted below.



.. code-block:: latex

    x1 y1 z1
    x2 y2 z2
    ...
    xn yn zn

.. figure:: images/Topo01.png
    :width: 400px
    :align: center
    :alt: alternate text
    :figclass: align-center

    Ordering of points as recorded in the files of type 01.

The points are ordered as illustrated in the above figure. The points start from the North-west part of the domain and progress east across the rows and later down. 

Topo type 02
--------------

The second format, known as *topotype = 2* is slightly more compact and stores only the :math:`(z)` value of all the points in the domain. Other data related to the relative :math:`(x,y)` points are derived from the header information. The information includes

.. code-block:: latex

    value   mx
    value   my
    value   xlower / xllcenter / xllcorner
    value   ylower / yllcenter / yllcorner
    value   cellsize
    value   nodataval
    z1
    z2
    ...

Here *mx* and *my* represent the number of points in the *x-* and *y-* directions. *cellsize* represent the size of the cellsize. It is possible to have two values for the cell size, i.e. *dx* and *dy*. If there is a value of depth is not known at a particular point :math:`(x,y)` on the grid, then the value specified at *nodataval* is given.

However, there are two aspects that can lead to ambiguity in reading the files, namely

* The order of *value* and *label* can be in any order. Either it can be *value* followed by *label* or otherwise.

* The third and fourth lines can either represent the value of the lower left corner specified with labels *xlower, ylower* or *xllcorner, yllcorner*. This is the lower left corner of the SW-most cell. Alternatively, it can also specify the center of this SW-most cell and represented by the labels *xllcenter, yllcenter*

.. figure:: images/Topo02.png
    :width: 400px
    :align: center
    :alt: alternate text
    :figclass: align-center

    Ordering of points as recorded in the files of type 02.

The points are ordered as illustrated in the above figure and is similar as that defined for the *topo type 01* but here only the :math:`(z)` values are stored in the file. The points start from the North-west part of the domain and progress east across the rows and later down. 

Topo type 03
--------------

The third format, known as *topotype = 3* is same as the `ESRI ASCII Raster format <http://resources.esri.com/help/9.3/arcgisengine/java/GP_ToolRef/spatial_analyst_tools/esri_ascii_raster_format.htm>`_ .

The first six lines with the header for type 03 is same as for type 02. This is followed by *my* lines. Each of these lines contain *mx* values of :math:`z_i` .
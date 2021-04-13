.. _lbl-geoclaw:

Shallow Water Solvers
=======================

There are several shallow water solvers available. In this work, we have focused on two of the primary ones of interest to the community: GeoClaw and AdCirc.

GeoClaw
-----------

GeoClaw is a part of Clawpacky that was originally developed in 1994 by Prof. Randall LeVeque and co-workers. It is available as a part of the clawpack package that uses finite volume methods for to solve linear and nonlinear hyperbolic systems. It employs high-resolution Godunov0type methods with limiters in a general framework applicable to wave-related problems and thus often used for tsunami modeling. More information can be found on the website of `Clawpack <https://www.clawpack.org>`_.

In this documentation, we will discuss aspects of particular importance to the Hydro-UQ platform that includes the input and output formats of the GeoClaw files. The Hydro-UQ tool allows the users to upload their own GeoClaw input files. 

.. toctree::
   :maxdepth: 1

   geoclaw-theory
   geoclaw-topo
   geoclaw-runtime
   geoclaw-output


AdCirc 
--------

AdCirc is often used for modeling storm surges.

SimCenter formats
--------------------

Development of file standards can help in the sustainable growth of community projects. SimCenter proposes the below formats for storing information related to the shallow water solvers.

.. toctree::
   :maxdepth: 1

   simcenter-topo


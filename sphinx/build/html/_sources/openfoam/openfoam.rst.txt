.. _lbl-openfoam:

OpenFOAM
=========

In this section, we will discuss OpenFOAM and various aspects related to it.

Solvers in OpenFOAM
---------------------

Unlike other commercial solvers, OpenFOAM is not just one solver but more like a collection of solvers. It has separate solver for each genre of problem and this decision is made by the user. The solvers available in the OpenFOAM version, in the folder ``$FOAM_SOLVERS``,  can be found using the command::

   >> app

The directory has further sub-directories that represent the category of continuum mechanics like incompressible, compressible, heat transfer, multiphase, combustion. Among the different solvers available in OpenFOAM, the usual directly relevance are shown in Fig below

.. figure:: images/OpenFOAM_Solvers.jpg
   :width: 600px
   :alt: solvers of interest to Hydro-UQ project
   :align: center

Solver descriptions
^^^^^^^^^^^^^^^^^^^^^

* ``simpleFoam``: This is a steady-state incompressible turbulent solver and uses the SIMPLE (Semi-Implicit Method for Pressure Linked Equations) algorithm. 

* ``pimpleFoam``: This is transient incompressible turbulent solver and also allowes for mesh and topology changes. This uses a combination of SIMPLE and PISO (Pressure Implicit with Splitting of Operators) algorithm. A detailed discussion on the PISO algorithm can be found in `OpenFOAM Wiki <https://openfoamwiki.net/index.php/OpenFOAM_guide/The_PISO_algorithm_in_OpenFOAM>`_.

Input file formats
--------------------

The first important aspect is to understand the input file structure. The input file is in the form of three directories / folders, namely (a) ``time`` or ``0`` (b) ``system`` (c) ``constant``

.. toctree::
   :maxdepth: 1

   OF-inputfolder01
   OF-inputfolder02
   OF-inputfolder03

Running OpenFOAM on TACC
--------------------------

The OpenFOAM jobs can either be run in parallel or in serial. Most often, CFD jobs require significant computational power and anything realistic needs to be run in parallel. 


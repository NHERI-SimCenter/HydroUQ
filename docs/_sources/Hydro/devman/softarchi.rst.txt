.. _lbl-softarchi:

*********************
Software Architecture
*********************

The SimCenter is developing a software framework for building applications that run scientific workflow applications to perform computational simulations in field of NHE at both building level scale and regional scale. It is releasing a number of applications built using this framework. The Hydro-UQ app is one of those applications which have been released (EE-UQ, WE-UQ, Hydro-UQ, PBE, R2D). The applications that the SimCenter are developing are limited scientific workflow systems. This chapter presents the software architecture for the framework and the Hydro-UQ app built using it using the C4 model. The following sections present the architecture to level 3:

.. note:: 

   1. **Workflow**: A sequence of steps involved in moving from a beginning state to an ending state.

   2. **Scientific Workflow Application**: An application that automates a workflow process through software, with each step in the workflow being performed by a separate “scientific” software application.

   3. **Scientific Workflow System**: software providing an infrastructure for the set-up, scheduling, running, and monitoring of a user defined scientific workflow application.

Level 1: A Context for SimCenter Applications
=============================================

A Level 1 diagram showing the system context for the SimCenter applications, i.e. how it fits in the world,  is shown in :numref:`figContext`. It shows SimCenter applications (EE-UQ, WE-UQ, Hydro-UQ, PBE, RDT) as a box in the center surrounded by the user and the systems it and the user interact with. The SimCenter applications allows user to create and run scientific workflow applications, the data for the applications may be obtained from the web or DataDepot. For now, the workflow application, Hydro-UQ, can only be run on the HPC at DesignSafe. In the upcoming versions, the ability to run locally will also be added.

.. _figContext:

.. figure:: figures/context.png
   :align: center
   :figclass: align-center

   System context diagram for SimCenter applications.

Level 2:  The Components of a SimCenter Application
===================================================

Given how SimCenter applications fit in with the environment, a level 2 diagrams now demonstrates how the SimCenter applications are broken into high level components. The SimCenter applications are, as shown in :numref:`figContainer`, broken into two components: A front end UI and a back end application that runs the workflow. The front end applications are desktop applications written using the cross-platform Qt framework. The back end is an application that processes the input from the front end, which comes in the form of a JSON file, creates a workflow and runs it. The workflow applications, written in Python and C++, run on a HPC utilizing resources made available to NHE community through DesignSafe. In the upcoming versions, Hydro-UQ will also facilitate running the workflow locally using the already installed applications on the user's desktop.

.. _figContainer:

.. figure:: figures/container.png
   :align: center
   :figclass: align-center

   System container diagram for SimCenter applications.

Level 3: Container Diagrams for the Front and Back End Components
=================================================================

Two level 3 diagrams are now presented which break up the two containers into the major building blocks or components in C4 terminology. In :numref:`figComponentFront` the component diagram for the front end UI is presented. It outlines the interaction between the user and the individual graphical elements (widgets) of the UI. Given the analogy of a jigsaw puzzle, the user selects which piece of the jigsaw puzzle they are working on in the component selection widget. The widget for the jigsaw piece will then be displayed on the desktop. The user for each jigsaw piece then selects which application to run for that piece, and for the chosen application, they provide the inputs. When the inputs are all provided, the user can select to run the simulations remotely. The user can download and review previously run simulations. As seen the widgets may subsequently interact with web services through HTTPS requests, or with DesignSafe utilizing TAPIS Restful API through the RemoteService container.

.. _figComponentFront:

.. figure:: figures/componentFront.png
   :align: center
   :figclass: align-center

   Component diagram for front end UI.

The component diagram for the backend application shown in :numref:`figComponentBack`, shows that the backend is made up of a number of components, all applications. The application ``femUQ.py`` is the application that parses the input from the front end, sets up the workflow and launches the UQ engine. Which UQ Engine and which applications to run in the workflow, is determined from the data passed from the UI and information contained in a WorkflowApplication.json file. A file is used to allow the researchers to modify the applications that may be run in the workflow w/o the need to recompile the application. Control is then passed to a UQ engine, which repeatedly runs the workflow to generate the results. In running the workflow some of the applications will invoke applications not developed to meet the API. For such applications pre- and post-processors are provided. The figure shows the backend application running remotely on a HPC at DesignSafe.
 
.. _figComponentBack:

.. figure:: figures/componentBack.png
   :align: center
   :figclass: align-center

   Component diagram for backend application.
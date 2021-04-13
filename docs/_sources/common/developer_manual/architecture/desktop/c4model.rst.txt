.. _lblc4model:

**********************************
C4 Model of Software Architecture
**********************************

The SimCenter workflow systems are aimed at facilitating the use, reuse and extension of common workflows encountered in NHE by a broad range of natural hazards engineering researchers with varying levels of software skills. In order to encourage this use and adoption, this chapter presents the software architecture for the SimCenter framework and |app| using the `C4 model <https://c4model.com>`_. The C4 model is graphical approach for documenting software architecture through diagrams that describe and communicate the software architecture at different levels of abstraction. It is a top-down approach which starts at a high level (level 1) showing how a user would interact with the software and drills down through three more levels, with level 4 containing the typical UML diagrams. The choice of the **C4** model was made to provide NHE researchers with a diverse range of software architecture knowledge an understanding of the software architecture behind SimCenter applications that fits their skill level. The four levels:


Level 1: Context Diagram
------------------------

A Level 1 diagram in :numref:`figContext` shows the system context for the SimCenter applications, i.e. how it fits in the world. In the diagram:
- the SimCenter computational applications (EE-UQ, WE-UQ, PBE, R2D) are shown in the center surrounded by the user and the systems it interacts with.
- input data for the SimCenter applications can be obtained either from NHERI datasets accessible on the DesignSafe `Data Depot <https://www.designsafe-ci.org/data/browser/public/designsafe.storage.community/>`_, shown to the right, or from web-based databases, shown to the left.
- the SimCenter applications can then be run in conjunction with open-source software applications (such as Dakota, FEAP, OpenSees, Python, OpenFOAM, etc.) either on a local desktop, shown below, or using HPC resources on |DesignSafe|, shown to the right.


.. figure:: figures/context.png
   :name: figContext
   :align: center
   :width: 800
   :figclass: align-center

   System context diagram for SimCenter applications.


Level 2: Container Diagram
--------------------------

A Level 2 diagram in :numref:`figContainer` demonstrates how the SimCenter applications are broken into high-level containers (applications, databases, etc.). Each of the SimCenter applications broken into two components: A front-end UI and a back-end application that runs the workflow. The front-end is a desktop application written using the cross-platform `Qt framework <https://www.qt.io/product/framework>`_. The back-end is an application that processes the input from the front-end, which comes in the form of a JSON file, creates a workflow and runs it. The workflow applications, written in Python, C, or C++, utilize existing applications were possible and run on either the local desktop machine or on a HPC utilizing resources made available to NHE community through DesignSafe.

.. figure:: figures/container.png
   :name: figContainer
   :align: center
   :width: 800
   :figclass: align-center

   System container diagram for SimCenter applications.


Level 3: Component Diagram
--------------------------

Two level 3 diagrams are now presented which break up the two containers into the major building blocks or components in C4 terminology. In :numref:`figComponentFront` the component diagram for the front end UI is presented. It outlines the interaction between the user and the individual graphical elements (widgets) of the UI. Given the analogy of a jigsaw puzzle, the user selects which piece of the jigsaw puzzle they are working on in the component selection widget. The widget for the jigsaw piece will then be displayed on the desktop. The user for each jigsaw piece then selects which application to run for that piece, and for the chosen application, they provide the inputs. When the inputs are all provided, the user can select to run the simulations locally or remotely. For jobs that run remotely, the user can download and review previously run simulations. As seen the widgets may subsequently interact with web services through HTTPS requests, or with DesignSafe utilizing TAPIS Restful API through the RemoteService container.

.. figure:: figures/componentFront.png
   :name: figComponentFront
   :align: center
   :width: 800
   :figclass: align-center

   Component diagram for front end UI.


The component diagram for the backend application shown in :numref:`figComponentBack`, shows that the backend is made up of a number of component applications. The application ``femUQ.py`` is the application that parses the input from the front end, sets up the workflow by creating a ``workflow_driver`` script and then launches the UQ engine. Which UQ Engine and which applications to run in the workflow, is determined from the data passed from the UI and information contained in a file, ``WorkflowApplication.json``. The ``WorkflowApplication.json`` file is a file that maps the applications specified in the output from the UI with a specific application contained on the users local machine or at the remote HPC resource, as such it allow the researchers to modify the applications that may be run in the workflow w/o the need to recompile the application. Once the ``workflow_driver`` file is created, control is passed to a UQ engine, which repeatedly runs the ``workflow_driver`` to generate the results. In running the workflow some of the applications will invoke applications not developed to meet the API. For such applications pre- and post-processors are provided. The figure shows the backend application running locally or remotely on a HPC at DesignSafe.


.. figure:: figures/componentBack.png
   :name: figComponentBack
   :align: center
   :width: 800
   :figclass: align-center

   Component diagram for Backend Application.



Level 4: Code Diagram
--------------------------

To facilitate the development of the different SimCenter applications and to encourage their reuse and extension by other NHE researchers, the SimCenter is providing the NHE community with a software framework for building such applications. From this framework the SimCenter is building the applications, of which |app| is but one, that it releases. These individual applications are built from the components of the framework. The components of the SimCenter are grouped, as shown in  figure below, into the following components:

#. **Cloud**: applications/libraries for communicating with remote web services to launch and monitor applications on HPC resources and to upload and download files from the filesystems of such resources.

#. **UQ**: applications for performing sampling, sensitivity, reliability and optimization methods.

#. **SAM**: applications for creating a finite element model of the building asset.

#. **EVENT**: applications for creating loads on the building asset given a natural hazard event.

#. **FEM**: application for determining the response parameter of the building asset given applied loads.

#. **DL**: application to determine the damage & loss to the building asset given the event.

#. **EDP**: application to determine the response parameter given the event, building asset, and damage and loss application.





.. note::

   ``femUQ.py`` is the backend application for the EE-UQ, WE-UQ, Hydro-UQ, and the PBE applications. For R2D the backend application is ``R2D_Workflow.py``.

The interaction between the frontend and the backend is best understood by looking at the sequence of events that occurs when the user presses the ``Run`` button. As shown in the figure below, the UI application will first perform a number of steps:

1. It will create a temporary directory in the Documents folder named ``tmp.SimCenter``, and inside ``tmp.SimCenter`` will create another dircetory ``templatedir``.

2. It will then run through all the currently selected widgets and on each invoke the ``copyFiles()`` method, telling these widgets to copy all files that will be needed during the workflow to the ``templatedir`` directory.

3. It will then create a JSON file and will run through the currenly selected widgets and on each invoke the methods ``outputToJSON()`` and ``outputAppDataToJSON``, these telling the application to augment the JSOIN file with the inputs the user has provided in the widget and also the name of the widget.

4. The UI will now start the backend application and will spin until the backend application returns with a completion signal.

Now that the UI has handed over to the backend application, the backend application will perform the following:

5. Open the output file from the UI and parse it to obtain the name of the application to run and the arguments to run the application with. Open up another file, the ``WorkflowApplications.json`` file, contained with the application, to determine given the application name the full path to the executable to be invoked. It will the create in ``templatedir`` a file named ``workflow_driver``. This file is a script file that when run by the UQ engine will generate a file named ``results.out``. ``results.out`` when the ``workflow_driver`` script has completed will contain a single line of space separated values, one value for each EDP.

6.  It will invoke each of the applications with supplied arguments and an additional command line argument, ``--getRV``, to inform the application to process the input file, and to create any additional random variables and input files needed before the workflow runs.

7. It will then launch the UQengine. The UQ engine, is typically a pre- and post- processor to an existing UQ engine.

8. The pre-processor takes the json input file and creates an input file needed by the actual UQ engine.

9. The preprocessor will launch the UQ application. This application will typically run the ``workflow_driver`` many times, passing as input to the workflow a file ``\params`` and obtaining as output from the ``workflow_driver`` a file ``results.out``.

10. When done the engine will output its results.

11. The UQengine will notify the UQpreprocessor that it is done.

12. The UQpreprocessor will notify the femUQ application that it is done.

13. The femUQ application will notify the UI that it is done.

14. The UI will read in the reuslts and present them to the user.



.. figure:: figures/sequenceLocal.png
   :name: figSequenceLocal
   :align: center
   :width: 800
   :figclass: align-center

   Sequence diagram showing what happens when a workflow runs locally.


That is for the case where the computations are performed on the local computer. When the somputations are performed remotely the steps are different. The first 8 steps are the same. But now the UQwrapper will not start the UQ engine. Instead, control is returned to the UI. The UI will, as shown in the following: (111) Compress the temporary folder. (12) Send the compressed folder to the remote HPC, shown in the figure DesignSafe. (13) Start an application to perform the computations. All the remote data transfer and application invocation is down through a cloud service, in the figure presented the `TACC tapis <https://tapis-project.org/>`_ interface is being used and provides SimCenter users with access to the TACC HPC resources through DesignSafe portal.


.. figure:: figures/sequenceRemote.png
   :name: figSequenceRemote
   :align: center
   :width: 800
   :figclass: align-center

   Sequence diagram showing what happens when a workflow runs remotely.

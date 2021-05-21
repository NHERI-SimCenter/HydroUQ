.. _lbl-uguide:

*********************
User Guide
*********************

The Hydro-UQ app, as will be discussed in :ref:`lbl-softarchi`, is an hazard event application. In addition to the hazard event, the workflow also includes other aspects, like UQ and FEM engine. Each of these workflow elements can involve multiple different backend applications. Once the Hydro-UQ app is started, the user is presented with the user interface shown in :numref:`primaryGUI`. It is in this UI where the user selects the applications to run in a workflow, inputs the necessary parameters for each of these applications, starts the workflow either locally or remotely, and finally views the simulation results. The main window of the UI is divided into several separate areas. Each of these areas are discussed in the upcoming sections.

.. _primaryGUI:

.. figure:: figures/EVT_Tab.png
   :align: center
   :figclass: align-center

   The Hydro-UQ app user interface

1. Login button: 

The **Login** button is at the top right of the user interface. Before the user can launch any jobs on DesignSafe, they must first login to DesignSafe using their DesignSafe login and password. Pressing the login button will open up the login window for users to enter this information. Users can register for an account on the `DesignSafe-CI <https://www.designsafe-ci.org/account/register>`_ website.

2. Action buttons:

The action buttons consists of possible action button. This includes:

    a. **RUN**: This button is used to setup and run the jobs locally on the user's computer. However, presently, the Hydro-UQ application does not facilitate local runs. This will be made available in the coming versions.

    b. **RUN at DesignSafe**: Process the information, and send to DesignSafe. The simulation will be run there on a supercomputer, and results will be stored in the user’s DesignSafe jobs folder.

    c. **GET from DesignSafe**: Obtain the list of jobs for the user from DesignSafe and select a job to download from that list.

    d. **Exit**: Exit the application.

3. Input panel selection: 

The ribbon on the left side provides the user with a selection of buttons to choose from (e.g. **UQ**, **EVT**, **RV**, **FEM**, **RES**). Selecting any of these buttons will change what is displayed in the central input panel. Each panel, with exception of **RV** panel,  will present the user with an option for which application to choose for that part of the workflow, and will then present the users for inputs for that application. Of particular interest here is the **EVT** where all flow-parameters are assigned. At present, the other inputs have not been integrated into the Hydro-UQ application. More information will be provided as and when the other inputs are integrated.

.. toctree::
    :maxdepth: 1

    UQ
    GI
    SIM
    EVT
    FEM
    EDP
    RV
    RES

5. Event parameter pPanel: 

The input panel is the large central area of the UI where the user provides input for the application chosen and where they can view the results. For example, if the user had selected **RV** in the input panel selection, it is in this panel that the user would provide details on the distributions associated with each random variable. In the following sections each of the panels that is presented to the user when the buttons in the input panel selection are reviewed:

6. Graphics panel:

The graphics window is not available in v.1.0.0 but will be added into the upcoming versions. The graphics window will help users to select boundary conditions graphically.
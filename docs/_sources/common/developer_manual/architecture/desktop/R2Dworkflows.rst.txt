.. _lblR2Dworkflows:

R2D Workflows
===============

This section is specific to implementations of R2D for quantifying regional risk and resilience to natural hazards. 

Choosing Component Applications
-------------------------------

A user's choice of :ref:`component applications <lblbackendApps>` for R2D depends on the hazard type, available data, and user preferences. All currently supported component applications and possible workflows are summarized in :numref:`figWorkflowDiagram`.


.. figure:: figures/workflow_diagram.png
   :name: figWorkflowDiagram
   :align: center
   :figclass: align-center




**Workflow 1** (EQ, HU, W): This workflow is appropriate for implementations where only intensity measures (IM) of earthquake, hurricane, or wind hazards are known. IM-based fragility functions must be used in the DL application, as no structural response is simulated. The required inputs are shown in the first orange panel.

.. figure:: figures/workflow_diagram_1.png
   :name: figWorkflowDiagram1
   :align: center
   :figclass: align-center


**Workflow 2** (EQ): This workflow is appropriate for implementations where ground motion records are loaded on an auto-generated multi-degree-of-freedom (MDOF) model, which is simulated in OpenSees. The required inputs are shown in the first orange panel.

.. figure:: figures/workflow_diagram_2.png
   :name: figWorkflowDiagram2
   :align: center
   :figclass: align-center


**Workflow 3** (EQ): This workflow is appropriate for implementations where ground motion records are loaded on an user-created structural model in OpenSees. The OpenSees model script must be included as an additional input.

.. figure:: figures/workflow_diagram_3.png
   :name: figWorkflowDiagram3
   :align: center
   :figclass: align-center


**Workflow 4** (EQ): This workflow is appropriate for implementations where ground motion records are loaded on an user-created structural model in OpenSeesPy. The OpenSeesPy model script must be included as an additional input.

.. figure:: figures/workflow_diagram_4.png
   :name: figWorkflowDiagram4
   :align: center
   :figclass: align-center


**Workflow 5** (EQ, HU, W): This workflow is appropriate for implementations where response is simulated on an user-created structural model in OpenSeesPy, and the user defines custom types and locations of EDPs to record on the model. The OpenSeesPy model script and the EDP specifications file must be included as additional inputs.

.. figure:: figures/workflow_diagram_5.png
   :name: figWorkflowDiagram5
   :align: center
   :figclass: align-center


**Workflow 6** (W): This workflow is appropriate for implementations where wind loads are applied to an auto-generated multi-degree-of-freedom (MDOF) model, which is simulated in OpenSees. The required inputs are shown in the first orange panel.

.. figure:: figures/workflow_diagram_6.png
   :name: figWorkflowDiagram6
   :align: center
   :figclass: align-center


**Workflow 7** (W): This workflow is appropriate for implementations where wind loads are applied to a user-created structural model in OpenSees. The OpenSees model script must be included as an additional input.

.. figure:: figures/workflow_diagram_7.png
   :name: figWorkflowDiagram7
   :align: center
   :figclass: align-center


**Workflow 8** (W): This workflow is appropriate for implementations where wind loads are applied to a user-created structural model in OpenSeesPy. The OpenSeesPy model script must be included as an additional input.

.. figure:: figures/workflow_diagram_8.png
   :name: figWorkflowDiagram8
   :align: center
   :figclass: align-center

.. _lblAbout:

******
About
******

This open-source research application, which is available at |tool github link|, is released under the **2-Clause BSD** license (see :ref:`lblLicense`).

The Regional Resilience Determnation (R2D) tool is an extensible scientific workflow system that can be used to quantify the effects of hazards on regional communities. The tool incorporates the same workflow components used in the WE-UQ, EE-UQ, and PBE tools, extended to consider multiple asssets and regionally distributed hazards. Version 1 allows users to predict the performance of the buildings in the region when subjected to earthquake events. Version 2, due May 2021, will allow researchers to study the effects given a Hurricane event. Future version will allow users to study effects of lifelines and interdependencies. A focus of the tool is on propogating uncertainties through the workflow.

Whether running locally or remotely, the computations are performed,
as will be discussed in the :ref:`lbl-technical-manual`, by an application called rWHALE. rWHALE runs the scientific workflow specified by invoking and running a number of different applications, taking the outputs from some programs and providing them as inputs to others. The design of the R2D and rWhale applications is such that researchers are able to include their own application in the workflow. This will ensure researchers are not limited to using
the default applications we provide and will be enthused to provide
their own applications for others to use.

As the computations can be prohibitively expensive to perform on a user's local computer, especially considering uncertaintanty quantification is involved,
the user has the option to perform the computations remotely on the
Stampede2 supercomputer. Stampede2 is located at the Texas Advanced
Computing Center (TACC) and made available to the user through NHERI
DesignSafe, the cyberinfrastructure provider for the distributed NSF
funded Natural Hazards in Engineering Research Infrastructure (NHERI)
facility.      


This document covers Version |tool version|  of the tool. Users are encouraged to comment on what additional features and capabilities
they would like to see in this application. These requests and feedback can be submitted through the |messageBoard| we greatly appreciate any input you have. If there are features you want, chances are many of your colleagues also would benefit from them. Users are encouraged to review |requirements| to see what features are planned for this application.

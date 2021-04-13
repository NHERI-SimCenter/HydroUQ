.. _lbl-errors:

************************
Troubleshooting
************************

Some of the common tips and tricks for troubleshooting include:

**Know the objective**

Before starting the simulation, it is essential to understand the intended goal of the project. This will help setup appropriate inputs. ``Hydro-UQ`` workflows already helps with this to the best extent possible. Yet, user's understanding of the physics is much necessary.

**Mesh quality**

Most often quality of the mesh can be the reason for the simulation failure. Check the mesh quality. ``Hydro-UQ`` has an in-built mesher and we continue to optimize its performance. However, this is limited and might not serve the needs of advanced researchers. It is then recommended to use external meshing tools and directly import the mesh. If the tool you used for meshing is not available, please submit a feature request at :ref:`lbl-featurereq`.

**Units**

Check that the units are consistent. At present, ``Hydro-UQ`` supports only SI units. 


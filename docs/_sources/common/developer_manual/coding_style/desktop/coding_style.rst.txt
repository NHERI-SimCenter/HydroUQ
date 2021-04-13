.. _lblCodingStyle:

************
Coding Style
************

The SimCenter frontend applications are written in **C++**. The applications that run in the backend are written in a mixture of languages: **Python**, **C**, and **C++**. The SimCenter strives to use a common style across the applications. This section outlines that style. Consistency is the most important aspect of style. The second most important aspect is following a style that the average programmer is used to reading. Not all code will follow th guide, 

Python Style
============

For code written in Python SimCenter programmers follow the widely used
`Guide PEP 8 <https://www.python.org/dev/peps/pep-0008/>`_

C/C++ Style
===========

Unlike Python, C/C++ do not have a widely accepted style guideline. Some guidelines of note include the `Google Style <https://google.github.io/styleguide/cppguide.html>`_, the `C++ Core Guidelines <http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines.html>`_ (edited by Stroustrup and Sutter), and an older
C++ 

Comments
--------

It goes without saying that you must use them. Try to use :code:`//` as opposed to :code:`/* */`, as it makes it easier to comment out a block of code when debugging.

Naming Conventions
------------------

All names should be meaningful and Follow a camel case approach. For classes the names start with an uppercase letter, all class methods, functions, and variables shall start with a lowercase letter. The exception is constant variables, which should be all uppercase, e.g. :code:`const double PI=3.14159265358979323;`

Files
-----

#. Use a ``.cpp`` extension for code files and a ``.h`` extension for interface files.
#. All files should include at the start the :ref:`lblLicense`
#. All file should contain some comments about what the file contains, and the name of the developers who worked substantially on the code.
#. Use indentation to make the code easier to read, the **Qt** editor has a nice feature that will auto indent code for you.
#. In addition, when writing header files:

   #. Never ever ever use ``using namespace`` in a header.
   #. All header files should additionally include documentation as the the purpose of the class and the methods. The returns and args to the functions should be documented. 
   #. Header files **MUST** contain a distinctly-named include guard to avoid problems with including the same header multiple times and to prevent conflicts with headers from other projects.
   #. The comments should be in a `Doxygen format <http://www.doxygen.nl/manual/docblocks.html>`_.
   #. Assign default values with ``=`` or ``{}``, a C++11 feature.
   #. All variables defined in the header must be private.

An example header file.

.. literalinclude:: SimCenterWidget.h
   :language: c++

Variables
---------

#. Initialize all variables
#. When initializing float and double variables with values that could be read as integer always include a ``.0``, e.g. :code:`double a = 1.0;`


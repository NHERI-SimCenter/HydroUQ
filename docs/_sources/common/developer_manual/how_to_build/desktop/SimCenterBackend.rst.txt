*****************
Build the Backend
*****************

    SimCenterBackendApplications contains a number of applications written in C++, C and Python that are needed by all SimCenter User Interfaces. To build the backend you will need to follow tht follwoting steps:

    1. Clone the `SimCenterBackendApplications repository <https://github.com/NHERI-SimCenter/SimCenterBackendApplications>`_. 
    2. Build SimCenterBackendApplications using the following steps:

        2.1. Create a build directory for the build output, this can be done in the terminal using the command ``mkdir build``.

        2.2. Install the backend dependencies using Conan. You can do this by going to the newly created build directory and running the command:

            ``conan install .. --build missing``

            This will install all the dependencies and will build dependencies from their source code as needed.
        
        2.3. Run CMake configuration this can be done using the command ``cmake ..``. Depending on your build environment, especially if you have multiple compiler, you may need to select a specific CMake generator. For instance on Window using Visual Studio 2017, you can configure CMake as follows:

            ``cmake .. -G Visual Studio 15 2017 Win64``

        2.4. Build the release version of the backend, this can be done using the generated build system. For instance, on Unix based systems when using make files this can be achieved using the command ``make`` or ``make release``. When using an IDE like Visual Studio on Window or XCode on Mac, the generated project can opened in the IDE and used to build the code. In addition, this can also be done from the terminal using CMake the command:

            ``cmake --build . --config Release``

    3. Install the backend applications to a local folder. This can be done by building the ``install target``. When using make on Unix based system. This can also be from IDE (e.g.) by selecting the install target or project and building it. In addition, this can be done from the terminal using the command:
        
        ``cmake --build . --target install`` or ``cmake --install`` if you have CMake 3.15 or later. If building and installation were successful you should find a folder called ``applications`` in the repository with all the applications inside of it.

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps
from conan.tools.files import copy
import os

class HYDROUQ(ConanFile):
    name = "HydroUQ"
    version = "4.2.0"
    license = "BSD-3-Clause"
    author = "NHERI SimCenter"
    url = "https://github.com/NHERI-SimCenter/HydroUQ"
    description = "NHERI SimCenter Water-Borne Hazard Engineering with Uncertainty Quantification Tool"
    settings = "os", "arch", "compiler", "build_type"

    # Define dependencies
    def requirements(self):
        self.requires("jansson/2.14")
        self.requires("zlib/1.3.1")
        self.requires("eigen/3.4.0")
        if self.settings.os != "Linux":
            self.requires("libcurl/8.12.1")        

    def generate(self):
        # Creates 'XXXX-config.cmake' files for find_package()
        deps = CMakeDeps(self)
        deps.generate()

        # Creates 'conan_toolchain.cmake' to pass settings to CMake
        tc = CMakeToolchain(self)
        tc.generate()

        # to address "DLL not found" error during local development .. why seperate generate function rather than typical generators = "CMakeDeps", "CMakeToolchain"
        if self.settings.os == "Windows":
            # For CMake, the binary usually ends up in build/Release or build/Debug
            bindir = os.path.join(self.build_folder, str(self.settings.build_type))
            for dep in self.dependencies.values():
                copy(self, "*.dll", dep.cpp_info.bindirs[0], bindir)        


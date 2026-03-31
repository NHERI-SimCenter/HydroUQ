from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, cmake_layout

class HYDROUQ(ConanFile):
    name = "HydroUQ"
    version = "4.2.0"
    license = "BSD-3-Clause"
    author = "NHERI SimCenter"
    url = "https://github.com/NHERI-SimCenter/HydroUQ"
    description = "NHERI SimCenter Water-Borne Hazard Engineering with Uncertainty Quantification Tool"

    settings = "os", "compiler", "build_type", "arch"

    # Define dependencies
    def requirements(self):
        self.requires("jansson/2.14")
        self.requires("libcurl/7.88.1")
        self.requires("zlib/1.3.1")
        self.requires("eigen/3.4.0")

    def layout(self):
        # This sets up the standard folder structure for CMake
        # Build files go to 'build/', generators go to 'build/generators'
        cmake_layout(self)

    def generate(self):
        # Creates 'XXXX-config.cmake' files for find_package()
        deps = CMakeDeps(self)
        deps.generate()

        # Creates 'conan_toolchain.cmake' to pass settings to CMake
        tc = CMakeToolchain(self)
        tc.generate()

    def configure(self):
        # Handle libcurl options if necessary
        self.options["libcurl"].shared = False
        self.options["libcurl"].with_ssl = "openssl"
        
        # Example from your snippet:
        if self.settings.os == "Windows":
            # Note: lapack isn't in your 'requires' above, 
            # but if you add it, this is where options go:
            # self.options["lapack"].visual_studio = True
            pass

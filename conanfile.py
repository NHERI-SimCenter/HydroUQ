from conan import ConanFile
from conan.tools.files import copy
import os

class HYDROUQ(ConanFile):
    name = "HydroUQ"
    license = "BSD"
    author = "NHERI SimCenter"
    url = "https://github.com/NHERI-SimCenter/HydroUQ"
    description = "NHERI SimCenter Water-Borne Hazard Engineering with Uncertainty Quantification Tool"

    settings = "os", "compiler", "build_type", "arch"    

    requires = ( "jansson/2.14", \
               "libcurl/7.88.1", \
               "zlib/1.3.1", \
               "eigen/3.4.0"
    )

    def layout(self):
        self.folders.build = "build"
        self.folders.generators = "conan"
        
    def generate(self):
        # Generate a .pri file that contains include and lib paths for each dependency.
        pri_dir = self.generators_folder  # Already equals "build/conan"
        os.makedirs(pri_dir, exist_ok=True)
        pri_path = os.path.join(pri_dir, "conan_generated.pri")
        libs_found = set()
        with open(pri_path, "w") as f:
            for dep in self.dependencies.host.values():
                self.output.info(f"DEPENDENCY {dep.cpp_info}")
                for inc in dep.cpp_info.includedirs:
                    f.write(f"INCLUDEPATH += {inc}\n")
                for libdir in dep.cpp_info.libdirs:
                    f.write(f"LIBS += -L{libdir}\n")
                for lib in dep.cpp_info.libs:
                    f.write(f"LIBS += -l{lib}\n")
                    libs_found.add(lib)

        # If libcurl is missing, add it manually!!!!
        if "curl" not in libs_found:
            with open(pri_path, "a") as f:
                f.write("LIBS += /Users/fmckenna/.conan2/p/b/libcub62433f05fbb2/p/lib/libcurl.a \n")
                self.output.info("Manually added -lcurl to PRI file")
                    
        self.output.info(f"Generated .pri at: {pri_path}")
        
    #generators = "CMakeDeps", "CMakeToolchain"
    # maybe go back to zlib 1.2.11

    build_policy = "missing"

    def configure(self):
        if self.settings.os == "Windows":
            self.options["lapack"].visual_studio = True
            self.options["lapack"].shared = True

    def imports(self):
        if self.settings.os == "Windows":
            output = './%s' % self.settings.build_type
            self.copy("lib*.dll", dst=output, src="bin")
            self.copy("*", dst='{}/resources'.format(output), src="resources")

        appsDestination = "./applications"
        if self.settings.os == "Windows":
            appsDestination = './%s/applications' % self.settings.build_type
        elif self.settings.os == "Macos":
            appsDestination = './HydroUQ.app/Contents/MacOS/applications'
        elif self.settings.os == "Linux":
            appsDestination = './applications'
        else:
            appsDestination = './applications'

        self.copy("createEVENT/multiple*", dst=appsDestination, src="bin")
        self.copy("createEVENT/siteRes*", dst=appsDestination, src="bin")
        self.copy("createEVENT/stochasticGroundMotion*", dst=appsDestination, src="bin")
        self.copy("createEVENT/*wind*", dst=appsDestination, src="bin")
        self.copy("createEVENT/*Wind*", dst=appsDestination, src="bin")
        self.copy("createEVENT/EmptyDomainCFD*", dst=appsDestination, src="bin")
        self.copy("createEVENT/IsolatedBuildingCFD*", dst=appsDestination, src="bin")
        self.copy("createEVENT/CFDEvent*", dst=appsDestination, src="bin")
        self.copy("createEVENT/multipleSimCenter*", dst=appsDestination, src="bin")
        self.copy("createEVENT/SimCenterEvent*", dst=appsDestination, src="bin")
        self.copy("createEVENT/*wave*", dst=appsDestination, src="bin")
        self.copy("createEVENT/*Wave*", dst=appsDestination, src="bin")
        self.copy("createEVENT/*GeoClaw*", dst=appsDestination, src="bin")
        self.copy("createEVENT/*DigitalTwin*", dst=appsDestination, src="bin")
        self.copy("createEVENT/*MPM*", dst=appsDestination, src="bin")
        self.copy("createEVENT/*stochasticWave*", dst=appsDestination, src="bin")
        self.copy("createEVENT/*Taichi*", dst=appsDestination, src="bin")
        #self.copy("createEVENT/*Celeris*", dst=appsDestination, src="bin")
        #self.copy("createEVENT/*GNS*", dst=appsDestination, src="bin")

        self.copy("createSAM/*", dst=appsDestination, src="bin")
        self.copy("createEDP/*", dst=appsDestination, src="bin")
        self.copy("performSIMULATION/*", dst=appsDestination, src="bin")
        self.copy("performUQ/*", dst=appsDestination, src="bin")
        self.copy("Workflow/*", dst=appsDestination, src="bin")
        self.copy("*", dst="{}/opensees".format(appsDestination), src="opensees")
        self.copy("*", dst="{}/dakota".format(appsDestination), src="dakota")

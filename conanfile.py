from conans import ConanFile

class HYDROUQ(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    version = "4.0.0"
    license = "BSD"
    author = "NHERI SimCenter"
    url = "https://github.com/NHERI-SimCenter/HydroUQ"
    description = "NHERI SimCenter Water-Borne Hazard Engineering with Uncertainty Quantification Tool"
    settings = "os", "compiler", "build_type", "arch"
    generators = "qmake"
    requires = "jansson/2.13.1", \
               "libcurl/8.1.1", \
               "zlib/1.2.12", \
               "openssl/3.2.2"

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

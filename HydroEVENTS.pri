INCLUDEPATH += $$PWD/EVENTS
INCLUDEPATH += EVENTS
# INCLUDEPATH += $$PWD/EDP
# INCLUDEPATH += EDP
# INCLUDEPATH += ../SimCenterCommon/Common
INCLUDEPATH += $$PWD/EVENTS/GeoClawOpenFOAM
INCLUDEPATH += $$PWD/EVENTS/WaveDigitalFlume
INCLUDEPATH += $$PWD/EVENTS/coupledDigitalTwin
INCLUDEPATH += $$PWD/EVENTS/MPM
INCLUDEPATH += $$PWD/EVENTS/MPMEvent
INCLUDEPATH += $$PWD/EVENTS/TaichiEvent
INCLUDEPATH += $$PWD/EVENTS/Celeris

#INCLUDEPATH += $$PWD/EVENTS/CelerisWebGPU
#INCLUDEPATH += $$PWD/EVENTS/CelerisWebGPU/js

INCLUDEPATH += $$PWD/EVENTS/NOAA
INCLUDEPATH += $$PWD/EVENTS/StochasticWaveModel
INCLUDEPATH += $$PWD/EVENTS/StochasticWaveModel/include
INCLUDEPATH += $$PWD/EVENTS/StochasticWaveModel/src
INCLUDEPATH += $$PWD/EVENTS/Common
INCLUDEPATH += $$PWD/SlidingStackedWidget

SOURCES += \
    $$PWD/EVENTS/HydroEventSelection.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/hydroerror.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/GeoClawOpenFOAM.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/H20utilities/h20utilities.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/boundary.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/boundarydata.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/buildings.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/cfdsolvers/openfoam/openfoam.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/cfdsolvers/openfoam/systemfiles.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/floatingbds.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/initialconalpha.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/initialconpres.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/initialconvel.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/materials.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/meshing.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/qt3dframe.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/scenemodifier.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/solver.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/swcfdint.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/swsolvers/geoclaw/geoclaw.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/postprocess.cpp \
    $$PWD/EVENTS/coupledDigitalTwin/CoupledDigitalTwin.cpp \
    $$PWD/EVENTS/coupledDigitalTwin/SettingsDigitalTwin.cpp \
    $$PWD/EVENTS/coupledDigitalTwin/OutputsDigitalTwin.cpp \
    $$PWD/EVENTS/coupledDigitalTwin/OpenSeesDigitalTwin.cpp \
    $$PWD/EVENTS/coupledDigitalTwin/OpenFOAM_DigitalTwin.cpp \
    $$PWD/EVENTS/coupledDigitalTwin/VisualizeDigitalTwin.cpp \
    $$PWD/EVENTS/MPM/MPM.cpp \
    $$PWD/EVENTS/MPM/BoundaryMPM.cpp \
    $$PWD/EVENTS/MPM/BoundariesMPM.cpp \
    $$PWD/EVENTS/MPM/OutputsMPM.cpp \
    $$PWD/EVENTS/MPM/SensorsMPM.cpp \
    $$PWD/EVENTS/MPM/SensorMPM.cpp \
    $$PWD/EVENTS/MPM/BodiesMPM.cpp \
    $$PWD/EVENTS/MPM/SettingsMPM.cpp \
    $$PWD/EVENTS/MPM/MaterialMPM.cpp \
    $$PWD/EVENTS/MPM/GeometriesMPM.cpp \
    $$PWD/EVENTS/MPM/GeometryMPM.cpp \
    $$PWD/EVENTS/MPM/AlgorithmMPM.cpp \
    $$PWD/EVENTS/MPM/PartitionsMPM.cpp \
    $$PWD/EVENTS/MPM/PartitionMPM.cpp \
    $$PWD/EVENTS/MPM/ResultsMPM.cpp \
    $$PWD/EVENTS/MPM/GeometryAI.cpp \
    $$PWD/EVENTS/MPM/SPH.cpp \
    $$PWD/EVENTS/MPM/CaseSPH.cpp \
    $$PWD/EVENTS/MPM/ExecutionSPH.cpp \
    $$PWD/EVENTS/MPMEvent/MPMEvent.cpp \
    $$PWD/EVENTS/MPMEvent/BasicMPMEvent.cpp \
    $$PWD/EVENTS/TaichiEvent/TaichiEvent.cpp \
    $$PWD/EVENTS/TaichiEvent/BasicTaichiEvent.cpp \
    $$PWD/EVENTS/Celeris/CelerisDomain.cpp \
    $$PWD/EVENTS/Celeris/CelerisSolver.cpp \
    $$PWD/EVENTS/Celeris/CelerisTaichi.cpp \
    $$PWD/EVENTS/Celeris/CelerisTaichiEvent.cpp \
    # $$PWD/EVENTS/CelerisWebGPU/Celeris.cpp \
    # $$PWD/EVENTS/CelerisWebGPU/WebGPU.cpp \
    # $$PWD/EVENTS/CelerisWebGPU/volumetric.cpp \
    $$PWD/EVENTS/NOAA/DigitalCoast.cpp \
    $$PWD/EVENTS/StochasticWaveModel/src/StochasticWaveInput.cpp \
    $$PWD/EVENTS/StochasticWaveModel/src/Jonswap.cpp \
    $$PWD/EVENTS/WaveDigitalFlume/WaveDigitalFlume.cpp \
    $$PWD/EVENTS/Common/projectsettings.cpp \
    $$PWD/EVENTS/Common/bathymetry.cpp
    # $$PWD/SlidingStackedWidget/slidingstackedwidget.cpp


HEADERS += \
    $$PWD/EVENTS/HydroEventSelection.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/hydroerror.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/H20utilities/h20utilities.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/boundary.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/boundarydata.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/buildings.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/floatingbds.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/initialconalpha.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/initialconpres.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/initialconvel.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/GeoClawOpenFOAM.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/materials.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/meshing.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/qt3dframe.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/scenemodifier.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/solver.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/swcfdint.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/swsolvers/geoclaw/geoclaw.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/cfdsolvers/openfoam/openfoam.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/postprocess.h \
    $$PWD/EVENTS/coupledDigitalTwin/CoupledDigitalTwin.h \
    $$PWD/EVENTS/coupledDigitalTwin/SettingsDigitalTwin.h \
    $$PWD/EVENTS/coupledDigitalTwin/OutputsDigitalTwin.h \
    $$PWD/EVENTS/coupledDigitalTwin/OpenSeesDigitalTwin.h \
    $$PWD/EVENTS/coupledDigitalTwin/OpenFOAM_DigitalTwin.h \
    $$PWD/EVENTS/coupledDigitalTwin/VisualizeDigitalTwin.h \
    $$PWD/EVENTS/MPM/MPM.h \
    $$PWD/EVENTS/MPM/BoundaryMPM.h \
    $$PWD/EVENTS/MPM/BoundariesMPM.h \
    $$PWD/EVENTS/MPM/OutputsMPM.h \
    $$PWD/EVENTS/MPM/SensorsMPM.h \
    $$PWD/EVENTS/MPM/SensorMPM.h \
    $$PWD/EVENTS/MPM/BodiesMPM.h \
    $$PWD/EVENTS/MPM/SettingsMPM.h \   
    $$PWD/EVENTS/MPM/MaterialMPM.h \
    $$PWD/EVENTS/MPM/GeometriesMPM.h \
    $$PWD/EVENTS/MPM/GeometryMPM.h \
    $$PWD/EVENTS/MPM/AlgorithmMPM.h \
    $$PWD/EVENTS/MPM/PartitionsMPM.h \   
    $$PWD/EVENTS/MPM/PartitionMPM.h \  
    $$PWD/EVENTS/MPM/ResultsMPM.h \
    $$PWD/EVENTS/MPM/GeometryAI.h \
    $$PWD/EVENTS/MPM/SPH.h \
    $$PWD/EVENTS/MPM/CaseSPH.h \
    $$PWD/EVENTS/MPM/ExecutionSPH.h \
    $$PWD/EVENTS/MPMEvent/MPMEvent.h \
    $$PWD/EVENTS/MPMEvent/BasicMPMEvent.h \
    $$PWD/EVENTS/TaichiEvent/TaichiEvent.h \
    $$PWD/EVENTS/TaichiEvent/BasicTaichiEvent.h \
    $$PWD/EVENTS/Celeris/CelerisDomain.h \
    $$PWD/EVENTS/Celeris/CelerisSolver.h \
    $$PWD/EVENTS/Celeris/CelerisTaichi.h \
    $$PWD/EVENTS/Celeris/CelerisTaichiEvent.h \
    # $$PWD/EVENTS/CelerisWebGPU/Celeris.h \
    # $$PWD/EVENTS/CelerisWebGPU/WebGPU.h \
    # $$PWD/EVENTS/CelerisWebGPU/volumetric.h \
    $$PWD/EVENTS/NOAA/DigitalCoast.h \
    $$PWD/EVENTS/StochasticWaveModel/include/StochasticWaveInput.h \
    $$PWD/EVENTS/StochasticWaveModel/include/Jonswap.h \
    $$PWD/EVENTS/WaveDigitalFlume/WaveDigitalFlume.h \
    $$PWD/EVENTS/Common/projectsettings.h \
    $$PWD/EVENTS/Common/bathymetry.h 
    # $$PWD/SlidingStackedWidget/slidingstackedwidget.h

FORMS += \
    $$PWD/EVENTS/GeoClawOpenFOAM/GeoClawOpenFOAM_copy.ui \
    $$PWD/EVENTS/GeoClawOpenFOAM/boundary.ui \
    $$PWD/EVENTS/GeoClawOpenFOAM/boundarydata.ui \
    $$PWD/EVENTS/GeoClawOpenFOAM/boundarydata_copy.ui \
    $$PWD/EVENTS/GeoClawOpenFOAM/buildings.ui \
    $$PWD/EVENTS/GeoClawOpenFOAM/floatingbds.ui \
    $$PWD/EVENTS/GeoClawOpenFOAM/initialconalpha.ui \
    $$PWD/EVENTS/GeoClawOpenFOAM/initialconpres.ui \
    $$PWD/EVENTS/GeoClawOpenFOAM/initialconvel.ui \
    $$PWD/EVENTS/GeoClawOpenFOAM/GeoClawOpenFOAM.ui \
    $$PWD/EVENTS/GeoClawOpenFOAM/materials.ui \
    $$PWD/EVENTS/GeoClawOpenFOAM/meshing.ui \
    $$PWD/EVENTS/GeoClawOpenFOAM/projectsettings_old.ui \
    $$PWD/EVENTS/GeoClawOpenFOAM/solver.ui \
    $$PWD/EVENTS/GeoClawOpenFOAM/swcfdint.ui \
    $$PWD/EVENTS/GeoClawOpenFOAM/postprocess.ui \
    $$PWD/EVENTS/WaveDigitalFlume/WaveDigitalFlume.ui \
    $$PWD/EVENTS/Common/projectsettings.ui \
    $$PWD/EVENTS/Common/bathymetry.ui


#    
#    $$PWD/EVENTS/coupledDigitalTwin/SettingsDigitalTwin.h \    


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

INCLUDEPATH += \
    $$PWD/EVENTS/dependencies/Eigen

DISTFILES += \
    $$PWD/EVENTS/dependencies/Eigen/CMakeLists.txt

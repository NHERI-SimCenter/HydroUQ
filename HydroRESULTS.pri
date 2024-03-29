#-------------------------------------------------
#
# Project created by JustinBonus
#
#-------------------------------------------------

#message($$_PRO_FILE_PWD_)
#message($$PWD)

INCLUDEPATH += $$PWD/EVENTS
INCLUDEPATH += $$PWD/GeoClawOpenFOAM
INCLUDEPATH += $$PWD/WaveDigitalFlume
INCLUDEPATH += $$PWD/coupledDigitalTwin
INCLUDEPATH += $$PWD/MPM
INCLUDEPATH += $$PWD/RESULTS


SOURCES += \
    $$PWD/RESULTS/HydroResults.cpp 


HEADERS  += \
    $$PWD/RESULTS/HydroResults.h 

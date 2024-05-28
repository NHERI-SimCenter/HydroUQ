#-------------------------------------------------
#
# Project created by JustinBonus
#
#-------------------------------------------------

#message($$_PRO_FILE_PWD_)
#message($$PWD)

INCLUDEPATH += $$PWD/EVENTS
INCLUDEPATH += $$PWD/EVENTS/GeoClawOpenFOAM
INCLUDEPATH += $$PWD/EVENTS/WaveDigitalFlume
INCLUDEPATH += $$PWD/EVENTS/coupledDigitalTwin
INCLUDEPATH += $$PWD/EVENTS/MPM
INCLUDEPATH += $$PWD/EVENTS/Celeris
INCLUDEPATH += $$PWD/EVENTS/NOAA
INCLUDEPATH += $$PWD/EVENTS/StochasticWaveModel
INCLUDEPATH += $$PWD/EVENTS/StochasticWaveModel/include
INCLUDEPATH += $$PWD/EVENTS/StochasticWaveModel/src
INCLUDEPATH += $$PWD/RESULTS


SOURCES += \
    $$PWD/RESULTS/HydroResults.cpp 


HEADERS  += \
    $$PWD/RESULTS/HydroResults.h 

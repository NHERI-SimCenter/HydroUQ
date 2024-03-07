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
INCLUDEPATH += $$PWD/EVENTS/CoupledDigitalTwin
INCLUDEPATH += $$PWD/EVENTS/MPM
INCLUDEPATH += $$PWD/RESULTS


SOURCES += \
    $$PWD/RESULTS/HydroResults.cpp \


HEADERS  += \
    $$PWD/RESULTS/HydroResults.h \

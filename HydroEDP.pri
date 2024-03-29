#-------------------------------------------------
#
# Project created by JustinBonus
#
#-------------------------------------------------

#message($$_PRO_FILE_PWD_)
#message($$PWD)

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/EDP
INCLUDEPATH += EDP

SOURCES += \
    $$PWD/EDP/HydroEDP_Selection.cpp \
    $$PWD/EDP/StandardHydroEDP.cpp \
    $$PWD/EDP/StandardTsunamiEDP.cpp \
    $$PWD/EDP/StandardStormSurgeEDP.cpp 

HEADERS  += \
    $$PWD/EDP/HydroEDP_Selection.h \
    $$PWD/EDP/StandardHydroEDP.h \
    $$PWD/EDP/StandardTsunamiEDP.h \
    $$PWD/EDP/StandardStormSurgeEDP.h 

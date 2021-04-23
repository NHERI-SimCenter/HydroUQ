#-------------------------------------------------
#
# Project created by QtCreator 2017-06-06T06:31:52
#
#-------------------------------------------------

include($$PWD/ConanHelper.pri)

QT += core gui charts concurrent network qml
QT += webchannel webenginewidgets webengine 
QT += 3dcore 3drender 3dextras charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Hydro_UQ
TEMPLATE = app

DEFINES += _GRAPHICS_Qt3D

VERSION=1.0.0
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

win32 {
    LIBS +=  -lAdvapi32
    RC_ICONS = icons/NHERI-HydroUQ-Icon.ico
} else {
    mac {
    ICON = icons/NHERI-HydroUQ-Icon.icns
    QMAKE_INFO_PLIST=$$PWD/Info.plist    
    }
}

include(./HydroEVENTS.pri)
include(../SimCenterCommon/Common/Common.pri)
include(../SimCenterCommon/Workflow/Workflow.pri)
include(../SimCenterCommon/RandomVariables/RandomVariables.pri)
include(../SimCenterCommon/InputSheetBM/InputSheetBM.pri)


SOURCES += main.cpp \   
    WorkflowAppHydroUQ.cpp \
    RunWidget.cpp

HEADERS  += \
    WorkflowAppHydroUQ.h\
    RunWidget.h 

RESOURCES += \
    images.qrc \
    $$PWD/styles.qrc

DISTFILES += \
    resources/docs/textAboutHydroUQ.html

#FORMS    += mainwindow.ui

RESOURCES += \
    $$PWD/images.qrc \
    $$PWD/Resources.qrc \   
    $$PWD/styles.qrc
       





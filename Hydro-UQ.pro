#-------------------------------------------------
#
# Project created by QtCreator 2017-06-06T06:31:52
#
#-------------------------------------------------

QT += core gui charts concurrent network qml webenginewidgets webengine webchannel 3dcore 3drender 3dextras charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Hydro_UQ
TEMPLATE = app

DEFINES += _GRAPHICS_Qt3D

VERSION=0.0.3
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

win32 {
    RC_ICONS = icons/NHERI-EEUQ-Icon.ico
} else {
    mac {
    ICON = icons/NHERI-EEUQ-Icon.icns
    }
}

macos:LIBS += /usr/lib/libcurl.dylib
win32:LIBS += C:\Users\SimCenter\libCurl-7.59.0/lib/libcurl.lib
linux:LIBS += /usr/lib/x86_64-linux-gnu/libcurl.so

win32:INCLUDEPATH += "..\jansson\build\include"
win32:LIBS += "..\jansson\build\lib\release\jansson.lib"

include(../SimCenterCommon/Common/Common.pri)
include(../SimCenterCommon/Workflow/Workflow.pri)
include(../SimCenterCommon/RandomVariables/RandomVariables.pri)
include(../SimCenterCommon/InputSheetBM/InputSheetBM.pri)
include(./HydroEvents.pri)

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
    resources/docs/textAboutEEUQ.html

#FORMS    += mainwindow.ui

#RESOURCES += \
#    schema.qrc




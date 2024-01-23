#-------------------------------------------------
#
# Project created by QtCreator 2017-06-06T06:31:52
#
#-------------------------------------------------

#include($$PWD/ConanHelper.pri)

CONFIG += conan_basic_setup
include($$OUT_PWD/conanbuildinfo.pri)

QT += core gui charts concurrent network qml svg
QT += webchannel webenginewidgets
QT += 3dcore 3drender 3dextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets 
greaterThan(QT_MAJOR_VERSION, 6): QT += core5compat

TARGET = Hydro_UQ
TEMPLATE = app


CONFIG += c++17

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
include(./SlidingStackedWidget/SlidingStackedWidget.pri)

SOURCES += main.cpp \
    EVENTS/H20plotwindow.cpp \
    WorkflowAppHydroUQ.cpp \
    RunWidget.cpp

HEADERS  += \
    EVENTS/H20plotwindow.h \
    WorkflowAppHydroUQ.h\
    RunWidget.h 

RESOURCES += \
    images.qrc \
    resources.qrc \
    $$PWD/styles.qrc

DISTFILES += \
    resources/docs/textAboutHydroUQ.html

#FORMS    += mainwindow.ui

RESOURCES += \
    $$PWD/images.qrc \
    $$PWD/resources.qrc \   
    $$PWD/styles.qrc
       

FORMS += \
    EVENTS/H20plotwindow.ui





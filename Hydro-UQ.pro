#-------------------------------------------------
#
# Project created by QtCreator 2017-06-06T06:31:52
#
#-------------------------------------------------

#include($$PWD/ConanHelper.pri)

CONFIG += conan_basic_setup
include($$OUT_PWD/conanbuildinfo.pri)

QT += core gui charts concurrent network sql qml 3dcore 3drender 3dextras printsupport quick opengl
QT += webengine webenginewidgets 
QT += webenginecore
QT += webchannel 
QT += websockets

QT += svg multimedia
QT += 3dinput 
QT += 3dlogic 
QT += 3dquick 
QT += 3dquickextras 
QT += datavisualization 

# QT += quickcontrols
# QT += quickcontrols2



# QT += wayland
# QT += x11extras
# QT += webglplugin-no-lgpl 
# QT += webglplugin
# QT += webkit webview 
# QT += webkitwidgets
# QT += webkit webkitwidgets
# QT += tools
# QT += declarative

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets 
greaterThan(QT_MAJOR_VERSION, 6): QT += core5compat

CONFIG += c++17


# The following define makes your compiler emit warnings if you use features
# of Qt which have been deprecated.
# DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


# The following define makes your compiler emit warnings if you use 
MOC_DIR = $$OUT_PWD/.moc
UI_DIR = $$OUT_PWD/.ui
OBJECTS_DIR = $$OUT_PWD/.obj
RCC_DIR = $$OUT_PWD/.rcc


TARGET = Hydro_UQ
TEMPLATE = app

VERSION = 3.2.1
# VERSTR = '\"$${VERSION}\"'
# DEFINES += APP_VERSION ="$${VERSTR}"
DEFINES += APP_VERSION=\\\"$$VERSION\\\"
DEFINES += NOINTERNALFEM
# DEFINES += _GRAPHICS_Qt3D

QMAKE_APPLE_DEVICE_ARCHS="x86_64"
# QTWEBENGINE_CHROMIUM_FLAGS+= --ignore-gpu-blacklist \
#                              --enable-gpu-rasterization 

# Some tools use web-apps with WebGPU, flags are often needed to make Qt properly use your GPU in a Chromium process
# They can be OS dependent, and GPU manufacture dependent (e.g. NVIDIA)

# include($$PWD/ConanHelper.pri)

# VTK setup ported from Abiy's work in WE-UQ for advanced 3D visualization
# May need to adjust paths. Need version 9.2 for now
# https://vtk.org/Wiki/VTK/Configure_and_Build
# INCLUDEPATH += $$PWD/../VTK/include/vtk-9.2
# INCLUDEPATH += /usr/local/include/vtk-9.2               



# Add  flags, environement variables, etc. for each operating system we support
win32 {
    LIBS = $$replace(LIBS, .dll.lib, .dll)
    LIBS += -lAdvapi32
    LIBS +=CRYPT32.lib
    LIBS +=Ws2_32.lib
    LIBS +=User32.lib
    DEFINES += CURL_STATICLIB
} else {
#    DEFINES += _GRAPHICS_Qt3D
    mac {
        LIBS += -L/usr/local/lib
        # LIBS += -framework WebKit
        # LIBS += -framework WebKitWidgets
        # LIBS += -framework WebCore
        # LIBS += -framework JavaScriptCore
        # LIBS += -framework WebKitLegacy
        
    } else {
        # Presumably Ubuntu 18.04 LTS
        LIBS += -L/usr/local/lib
        DEFINES += CURL_STATICLIB
    }
}


win32 {
    RC_ICONS = icons/NHERI-HydroUQ-Icon.ico

} else {
    mac {
        ICON = icons/NHERI-HydroUQ-Icon.icns
        QMAKE_INFO_PLIST=$$PWD/Info.plist    

    } else {

    }
}


include(../SimCenterCommon/Common/Common.pri)
include(../SimCenterCommon/Workflow/Workflow.pri)
include(../SimCenterCommon/RandomVariables/RandomVariables.pri)
include(../SimCenterCommon/InputSheetBM/InputSheetBM.pri)
include(./HydroEVENTS.pri)
include(./SlidingStackedWidget/SlidingStackedWidget.pri)
include(./HydroRESULTS.pri)
include(./HydroEDP.pri)

SOURCES += main.cpp \
    WorkflowAppHydroUQ.cpp \
    RunWidget.cpp \
    EVENTS/H20plotwindow.cpp 

HEADERS  += \
    WorkflowAppHydroUQ.h\
    EVENTS/H20plotwindow.h \
    RunWidget.h 
    

RESOURCES += \
    images.qrc \
    resources.qrc \
    objects.qrc \
    styles.qrc \
    EVENTS/Celeris/volumetric.qrc \
    $$PWD/images.qrc \
    $$PWD/resources.qrc \   
    $$PWD/styles.qrc \
    $$PWD/objects.qrc \
    $$PWD/scripts.qrc 


DISTFILES += \
    resources/docs/textAboutHydroUQ.html
       

FORMS += \
    EVENTS/H20plotwindow.ui


# OTHER_FILES azure-pipelines.yml

# OTHER_FILES += conanfile.py


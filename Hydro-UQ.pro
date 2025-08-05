#-------------------------------------------------
#
# Project created by QtCreator 2017-06-06T06:31:52
#
#-------------------------------------------------

win32 {
    # QTDIR = 
} else {
    mac {
        # QtDir =    
    } else {
        # Presumably Ubuntu 18.04 LTS
        # Modify QTDIR to point to your desired Qt installation
        QTDIR = /opt/qt515/
        PATH += ${QTDIR}/bin/
        LIBS += -L${QTDIR}/lib/
        QT_PLUGIN_PATH += ${QTDIR}/plugins/
        QMAKESPEC += ${QTDIR}/mkspecs/linux-g++/
        QML_IMPORT_PATH += ${QTDIR}/qml/
        PKG_CONFIG_PATH +=${QTDIR}/lib/pkgconfig/
    }
}

# Note: ConanHelper.pri will call conan_basic_setup and include the conanbuildinfo.pri file 
include($$PWD/ConanHelper.pri)
# CONFIG += conan_basic_setup
# include($$OUT_PWD/conanbuildinfo.pri)

QT += core gui charts concurrent network sql qml 3dcore 3drender 3dextras printsupport quick opengl
QT += webengine webenginewidgets 
QT += webenginecore
QT += webchannel 
QT += svg 
QT += 3dinput 
QT += 3dlogic 
QT += 3dquick 
QT += 3dquickextras 
QT += datavisualization 


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets 
greaterThan(QT_MAJOR_VERSION, 6): QT += core5compat

CONFIG += c++17

# Disable m64 flag on windows
# win32:QMAKE_CXXFLAGS -= -m64 #TODO: This seems to be cause by smelt Conan package

# The following define makes your compiler emit warnings if you use features
# of Qt which have been deprecated.
# DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


# The following define makes your compiler emit warnings if you use 
# MOC_DIR = $$OUT_PWD/.moc
# UI_DIR = $$OUT_PWD/.ui
# OBJECTS_DIR = $$OUT_PWD/.obj
# RCC_DIR = $$OUT_PWD/.rcc


TARGET = Hydro_UQ
TEMPLATE = app
VERSION = 4.1.0
# VERSTR = '\"$${VERSION}\"'
# DEFINES += APP_VERSION ="$${VERSTR}"
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

win32 {
    DEFINES += NOINTERNALFEM
    DEFINES += _GRAPHICS_Qt3D
    # DEFINES += NO_MPM_QT3D
} else {
    mac {
        DEFINES += NOINTERNALFEM
        DEFINES += _GRAPHICS_Qt3D
        # DEFINES += NO_MPM_QT3D
    } else {
        DEFINES += NOINTERNALFEM
        DEFINES += _GRAPHICS_Qt3D
        # DEFINES += NO_MPM_QT3D
    }
}

# QMAKE_APPLE_DEVICE_ARCHS="x86_64"

# Some tools use web-apps with WebGPU, flags are often needed to make Qt properly use your GPU in a Chromium process
# They can be OS dependent, and GPU manufacture dependent (e.g. NVIDIA)
# QTWEBENGINE_CHROMIUM_FLAGS+= --ignore-gpu-blacklist \
#                              --enable-gpu-rasterization 


INCLUDEPATH += EVENTS/StochasticWaveModel/include
# INCLUDEPATH += $$PWD/../VTK/include/vtk-9.2
# INCLUDEPATH += /usr/local/include/vtk-9.2
# https://vtk.org/Wiki/VTK/Configure_and_Build


# Add  flags, environement variables, etc. for each operating system we support
win32 {
    LIBS = $$replace(LIBS, .dll.lib, .dll)
    LIBS += -lAdvapi32
    LIBS +=CRYPT32.lib
    LIBS +=Ws2_32.lib
    LIBS +=User32.lib
    # LIBS +=Advapi32.lib
    DEFINES += CURL_STATICLIB
} else {
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
    # DEFINES += USE_SIMCENTER_PYTHON
} else {
    mac {
        ICON = icons/NHERI-HydroUQ-Icon.icns
        QMAKE_INFO_PLIST=$$PWD/Info.plist    
    } else {
        LIBS += -lglut -lGLU -lGL
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
    RunWidget.h \
    EVENTS/H20plotwindow.h
    

RESOURCES += \
    images.qrc \
    resources.qrc \
    objects.qrc \
    styles.qrc \
    EVENTS/CelerisWebGPU/volumetric.qrc \
    $$PWD/images.qrc \
    $$PWD/resources.qrc \
    $$PWD/styles.qrc \
    $$PWD/objects.qrc \
    $$PWD/scripts.qrc 


DISTFILES += \
    resources/docs/textAboutHydroUQ.html \ 
    GA4.html
       

FORMS += \
    EVENTS/H20plotwindow.ui


# OTHER_FILES azure-pipelines.yml

# OTHER_FILES += conanfile.py


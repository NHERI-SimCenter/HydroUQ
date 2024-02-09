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

VERSION=3.0.0
DEFINES += APP_VERSION=\\\"$$VERSION\\\"


# VTK setup ported from Abiy's work in WE-UQ for advanced 3D visualization
# May need to adjust paths. Need version 9.2 for now
# https://vtk.org/Wiki/VTK/Configure_and_Build
# INCLUDEPATH += $$PWD/../VTK/include/vtk-9.2
# INCLUDEPATH += /usr/local/include/vtk-9.2               

# Add  flags, environement variables, etc. for each operating system we support
win32 {
    # Windows
    LIBS +=  -lAdvapi32
    RC_ICONS = icons/NHERI-HydroUQ-Icon.ico
    DEPENDPATH += $$PWD/../VTK/Release/bin
    INCLUDEPATH += $$PWD/../VTK/Release/include/vtk-9.2
    LIBS += -L$$PWD/../VTK/Release/lib \
    -lvtkViewsCore-9.2 \
    -lvtkFiltersCore-9.2 \
    -lvtkFiltersSources-9.2 \
    -lvtkCommonCore-9.2 \
    -lvtkCommonColor-9.2 \
    -lvtkFiltersGeometry-9.2 \
    -lvtkRenderingCore-9.2 \
    -lvtkInteractionStyle-9.2\
    -lvtkCommonTransforms-9.2\
    -lvtkInteractionWidgets-9.2\
    -lvtkRenderingContextOpenGL2-9.2 \
    -lvtkRenderingFreeType-9.2 \
    -lvtkRenderingGL2PSOpenGL2-9.2 \
    -lvtkRenderingAnnotation-9.2 \
    -lvtkCommonExecutionModel-9.2 \
    -lvtkCommonDataModel-9.2 \
    -lvtkGUISupportQt-9.2 \
    -lvtkRenderingOpenGL2-9.2 \
    -lvtkIOGeometry-9.2 \
    -lvtkViewsQt-9.2 \
    -lvtkImagingCore-9.2 \
    -lvtkIOImage-9.2 \
    -lvtkIOLegacy-9.2 \
    -lvtksys-9.2

} else {

    mac {
        # Mac
        ICON = icons/NHERI-HydroUQ-Icon.icns
        QMAKE_INFO_PLIST=$$PWD/Info.plist    
    #    DEPENDPATH += $$PWD/../VTK/lib
    #    DEPENDPATH += $$PWD/../VTK/Release/bin
    #    INCLUDEPATH += $$PWD/../VTK/Release/include/vtk-9.2
        INCLUDEPATH += $$PWD/../VTK/include/vtk-9.2
        INCLUDEPATH += /usr/local/include/vtk-9.2
        LIBS += -L$$PWD/../VTK/lib 
        LIBS += -L/usr/local/lib \
        -lvtkViewsCore-9.2 \
        -lvtkFiltersCore-9.2 \
        -lvtkFiltersSources-9.2 \
        -lvtkCommonCore-9.2 \
        -lvtkCommonColor-9.2 \
        -lvtkFiltersGeometry-9.2 \
        -lvtkRenderingCore-9.2 \
        -lvtkInteractionStyle-9.2\
        -lvtkCommonTransforms-9.2\
        -lvtkInteractionWidgets-9.2\
        -lvtkRenderingContextOpenGL2-9.2 \
        -lvtkRenderingFreeType-9.2 \
        -lvtkRenderingGL2PSOpenGL2-9.2 \
        -lvtkRenderingAnnotation-9.2 \
        -lvtkCommonExecutionModel-9.2 \
        -lvtkCommonDataModel-9.2 \
        -lvtkGUISupportQt-9.2 \
        -lvtkRenderingOpenGL2-9.2 \
        -lvtkIOGeometry-9.2 \
        -lvtkViewsQt-9.2 \
        -lvtkImagingCore-9.2 \
        -lvtkIOImage-9.2 \
        -lvtkIOLegacy-9.2 \
        -lvtksys-9.2
    } else {
        # Presumably Ubuntu 18.04 LTS
        # INCLUDEPATH += /usr/local/include/vtk-9.2
        LIBS += -L/usr/local/lib \
        #-lvtkViewsCore-9.2 \
        #-lvtkFiltersCore-9.2 \
        #-lvtkCommonColor-9.2 \
        #-lvtkFiltersSources-9.2 \
        #-lvtkCommonCore-9.2 \
        #-lvtkFiltersGeometry-9.2 \
        #-lvtkRenderingCore-9.2 \
        #-lvtkInteractionStyle-9.2\
        #-lvtkCommonTransforms-9.2\
        #-lvtkInteractionWidgets-9.2\
        #-lvtkRenderingAnnotation-9.2 \
        #-lvtkRenderingContextOpenGL2-9.2 \
        #-lvtkRenderingFreeType-9.2 \
        #-lvtkRenderingGL2PSOpenGL2-9.2 \
        #-lvtkCommonExecutionModel-9.2 \
        #-lvtkCommonDataModel-9.2 \
        #-lvtkGUISupportQt-9.2 \
        #-lvtkRenderingOpenGL2-9.2 \
        #-lvtkIOGeometry-9.2 \
        #-lvtkViewsQt-9.2 \
        #-lvtkImagingCore-9.2 \
        #-lvtkIOImage-9.2 \
        #-lvtkIOLegacy-9.2 \
        #-lvtksys-9.2
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
    objects.qrc \
    $$PWD/styles.qrc

DISTFILES += \
    resources/docs/textAboutHydroUQ.html

#FORMS    += mainwindow.ui

RESOURCES += \
    $$PWD/images.qrc \
    $$PWD/resources.qrc \   
    $$PWD/styles.qrc \
    $$PWD/objects.qrc
       

FORMS += \
    EVENTS/H20plotwindow.ui





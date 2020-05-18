QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Buttons/T1aSetWorkDirBut.cpp \
    Buttons/T1bSelectBathFileBut.cpp \
    Buttons/T1cAcceptBathDataBut.cpp \
    Buttons/T1dInterfaceConfBut.cpp \
    Buttons/T1eTab1Reset.cpp \
    Buttons/T1fTab1Accept.cpp \
    Buttons/T2aNumBuildingsBut.cpp \
    Buttons/T2bNumSegmentsBut.cpp \
    Buttons/T2dAddBuildingBut.cpp \
    Buttons/T2eRemoveBuildingBut.cpp \
    Buttons/T3aSolutionFilesBut.cpp \
    Buttons/T3cBCAcceptBut.cpp \
    Buttons/T4a1ConfTurbBut.cpp \
    Buttons/T4a2ResetTurbBut.cpp \
    Buttons/T4b1ParallelConfBut.cpp \
    Buttons/T4b2ResetParall.cpp \
    Buttons/T4c1ConfMeshingBut.cpp \
    Buttons/T4c2ResetMesh.cpp \
    Buttons/T4d1TimeSetConfBut.cpp \
    Buttons/T4d2ResetTime_But.cpp \
    Buttons/T4e1TransportConfBut.cpp \
    Buttons/T4e2ResetTransBut.cpp \
    Buttons/T4f1ClusterConfBut.cpp \
    Buttons/T4f2ResetClustBut.cpp \
    Buttons/T4g1AccCFDSolBut.cpp \
    Buttons/T4g2ResetSolvBut.cpp \
    Buttons/T4h1GenFilesBut.cpp \
    Combobox/T1BathType.cpp \
    Graphics/plotbathy.cpp \
    Graphics/qcustomplot.cpp \
    OFWriters/OFheaderWrite.cpp \
    Process/processfail.cpp \
    Readers/SCBathFileReader.cpp \
    Writers/HydroBCSW2CFD.cpp \
    Writers/HydroHeader.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Graphics/qcustomplot.h \
    OFWriter.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Images/SimCenterLogo.png \
    Images/SimCenter_H2O_logo.png

RESOURCES += \
    Resources.qrc

INCLUDEPATH += \
    dependencies/Eigen

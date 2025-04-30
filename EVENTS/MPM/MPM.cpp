/* *****************************************************************************
Copyright (c) 2016-2017, The Regents of the University of California (Regents).
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of the FreeBSD Project.

REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED HEREUNDER IS
PROVIDED "AS IS". REGENTS HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT,
UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

*************************************************************************** */

// Written: fmk, JustinBonus

#include "MPM.h"
#include <SettingsMPM.h>
#include <BodiesMPM.h>
#include <BoundariesMPM.h>
#include <SensorsMPM.h>
#include <OutputsMPM.h>
#include <ResultsMPM.h>
#include <QVector>
#include <QScrollArea>
#include <QLineEdit>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QJsonObject>
#include <QJsonArray>
#include <QSvgWidget>
#include <QString>
#include <QIcon>
#include <QPixmap>
#include <QToolButton>
#include <QStackedWidget>
#include <QCoreApplication>
#include "slidingstackedwidget.h"

#include <SC_DoubleLineEdit.h>
#include <SC_IntLineEdit.h>
#include <Utils/FileOperations.h>
// #include <QJsonDocument>

#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QConeMesh>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QPhongAlphaMaterial>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DRender/QMesh>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DRender/QCamera>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QEntity>
#include <QQuaternion>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DRender/QAttribute>
#include <Qt3DRender/QBuffer>
#include <Qt3DRender/QGeometry>
#include <Qt3DRender/QGeometryRenderer>


// #include <QOpenGLWidget>
#include "QVector3D"
#include <qcustomplot.h>
#include <QJsonDocument>
#include <QFileDialog>
#include <SectionTitle.h>
#include <QFileInfo>
#include <QMovie>
#include <QPixmap>
#include <RandomVariablesContainer.h>
#include <QRadioButton>
#include <QButtonGroup>
#include <QComboBox>
#include <QSpinBox>
#include <QGroupBox>
#include <QVector>
#include <LineEditRV.h>
#include <QDebug>
#include <SimCenterPreferences.h>
#include <GeneralInformationWidget.h>
#include <QProcess>
#include <QDir>
#include <QTextEdit>
#include <QFormLayout>

#include <QUrl> 


MPM::MPM(RandomVariablesContainer *theRandomVariableIW, QWidget *parent)
    :  SimCenterAppWidget(parent), theRandomVariablesContainer(theRandomVariableIW)
{

// MPM::MPM(QWidget *parent)
//     :  SimCenterAppWidget(parent)
// {
    int windowWidth = 800;
    int windowWidthMin = 250;
    QWidget     *mainGroup = new QWidget();
    mainLayout = new QGridLayout();

    mainWindowLayout = new QHBoxLayout(); // WE-UQ


    // ==================== Digital Twin Description and Selection ====================
    QStackedWidget *parentStackedWidget = new QStackedWidget();

    SlidingStackedWidget *stackedWidget = new SlidingStackedWidget(parentStackedWidget);
    stackedWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    stackedWidget->setMinimumWidth(windowWidthMin);
    stackedWidget->setMaximumWidth(windowWidth);
    stackedWidget->setStyleSheet("QStackedWidget {background-color:  rgb(79, 83, 89); color: #000000; border: 1px solid #000000; border-radius: 0px;}"
                                 "QStackedWidget:disabled {background-color:  rgb(79, 83, 89); color: #000000; border: 1px solid #000000; border-radius: 0px;}");
    QWidget *page1 = new QWidget();
    QWidget *page2 = new QWidget();
    QWidget *page3 = new QWidget();
    QWidget *page4 = new QWidget();
    QWidget *page5 = new QWidget();
    stackedWidget->addWidget(page1);
    stackedWidget->addWidget(page2);
    stackedWidget->addWidget(page3);
    stackedWidget->addWidget(page4);
    stackedWidget->addWidget(page5);
    stackedWidget->setCurrentIndex(0); // Open to OSU LWF

    // Each page gets a different image pixmap and description of the digital twin in photo
    QPixmap page1Pixmap(":/images/OSU_LWF_Pic_MTS_HighRes.png");
    QPixmap page2Pixmap(":/images/OSU_DWB_Pic_Square.png");
    QPixmap page3Pixmap(":/images/UW_WASIRF_Pic_Square.png");
    QPixmap page4Pixmap(":/images/Waseda_Flume_Picture.jpg");
    QPixmap page5Pixmap(":/images/USGS_Iverson_2020_RFI.PNG");
    uint minWidthDigitalTwinPhoto  = 200;
    uint minHeightDigitalTwinPhoto = 200;
    uint maxWidthDigitalTwinPhoto  = 275;
    uint maxHeightDigitalTwinPhoto = 275;

    // OSU LWF (Winter 2019, Shekhar et al 2020, Mascarenas 2022, Bonus 2023)
    QLabel *page1Label = new QLabel();
    page1Label->setPixmap(page1Pixmap);
    page1Label->setScaledContents(true);
    page1Label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    page1Label->setMinimumHeight(minHeightDigitalTwinPhoto);
    page1Label->setMinimumWidth(minWidthDigitalTwinPhoto);
    page1Label->setMaximumHeight(maxHeightDigitalTwinPhoto);
    page1Label->setMaximumWidth(maxWidthDigitalTwinPhoto);
    page1Label->setAlignment(Qt::AlignCenter);
    QLabel *page1DescriptionLabel = new QLabel(" Oregon State University's Large Wave Flume - OSU LWF"
                                               "\n Supported by NSF Award No. 2037914 and the Pacific Marine Energy Center."
                                               "\n "
                                               "\n Largest of its kind in North America, operating in high Reynolds regimes"
                                               "\n The flume is ideally suited for:"
                                               "\n > Wave runup, reflection, and overtopping"
                                               "\n > Wave forces on offshore and coastal structures"
                                               "\n > Nearshore hydrodynamics, wave breaking, swash, and undertow"
                                               "\n > Tsunami inundation and overland flow"
                                               "\n > Tsunami structure impact, debris, and scour"
                                               "\n "
                                               "\n Wave Flume Size: 104 m (342ft), 3.7 m (12ft), 4.6 m (15ft)"
                                               "\n Bathymetry:    Movable and adjustable"
                                               "\n Max depth: 2 m (6.5 ft) for tsunami, 2.7 m (9 ft) for wind/storm waves"
                                               "\n Wave Maker:    Piston-type, Hydraulic Actuator Assembly"
                                               "\n Wave Types:    Regular, Irregular, Tsunami, and User-Defined"
                                               "\n Max Wave:      1.7 m (5.6 ft) @ 5 sec in max 2.7 m water"
                                               "\n Max Tsunami:   1.4 m (3.9ft) in max 2.0 m water"
                                               "\n Max Stroke:    4 m (13.1 ft) at 4 m/s (13.1 ft/s)."
                                               "\n Period Range: 0.8 to 12+ seconds");
                                              //  "\n > Cross-shore sediment suspension and transport, pollutant mixing and transport"
                                              //  "\n > Scour, pipeline stability, outfalls, liquefaction, and cohesive sediments"
    
    page1DescriptionLabel->setWordWrap(true);
    page1DescriptionLabel->setStyleSheet("QLabel {background-color:  rgb(79, 83, 89); color: #ffffff; border: 0px solid #000000; border-radius: 0px;}"
                                         "QLabel:disabled {background-color:  rgb(79, 83, 89); color: #ffffff; border: 0px solid #000000; border-radius: 0px;}");
    
    // OSU DWB (Park et al. 2021)
    QLabel *page2Label = new QLabel();
    page2Label->setPixmap(page2Pixmap);
    page2Label->setScaledContents(true);
    page2Label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    page2Label->setMinimumHeight(minHeightDigitalTwinPhoto);
    page2Label->setMinimumWidth(minWidthDigitalTwinPhoto);
    page2Label->setMaximumHeight(maxHeightDigitalTwinPhoto);
    page2Label->setMaximumWidth(maxWidthDigitalTwinPhoto);
    page2Label->setAlignment(Qt::AlignCenter);
    QLabel *page2DescriptionLabel = new QLabel(" Oregon State University's Directional Wave Basin - OSU DWB"
                                               "\n Supported by NSF Award No. 2037914 and the Pacific Marine Energy Center."
                                               "\n "
                                               "\n Generate directional waves with a wide range of wave periods and heights."
                                               "\n The flume is ideally suited for:"
                                               "\n > Wave runup, reflection, and overtopping"
                                               "\n > Wave forces on offshore and coastal structures"
                                               "\n > Nearshore hydrodynamics, wave breaking, swash, and undertow"
                                               "\n > Tsunami inundation and overland flow"
                                               "\n > Tsunami structure impact, debris, and scour"
                                               "\n "
                                               "\n Wave Flume Size: 48.8 m long, 26.5 m wide, 2.7 m deep." 
                                               "\n Wave maker: 2 m wide, 1.2 m high piston-type wavemaker.");
    page2DescriptionLabel->setWordWrap(true);
    page2DescriptionLabel->setStyleSheet("QLabel {background-color:  rgb(79, 83, 89); color: #ffffff; border: 0px solid #000000; border-radius: 0px;}"
                                         "QLabel:disabled {background-color:  rgb(79, 83, 89); color: #ffffff; border: 0px solid #000000; border-radius: 0px;}");
    
    // UW WASIRF (Lewis 2023)
    QLabel *page3Label = new QLabel();
    page3Label->setPixmap(page3Pixmap);
    page3Label->setScaledContents(true);
    page3Label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    page3Label->setMinimumHeight(minHeightDigitalTwinPhoto);
    page3Label->setMinimumWidth(minWidthDigitalTwinPhoto);
    page3Label->setMaximumHeight(maxHeightDigitalTwinPhoto);
    page3Label->setMaximumWidth(maxWidthDigitalTwinPhoto);
    page3Label->setAlignment(Qt::AlignCenter);
    QLabel *page3DescriptionLabel = new QLabel(" University of Washington's Wind-Air-Sea Interatction Research Facility - UW WASIRF"
                                               "\n "
                                               "\n Steady and Quasi-Steady State Flows of Water and Wind with Stochastic Reproducibility."
                                               "\n "
                                               "\n Wave Flume Size: 12 m long, 1.2 m wide, 0.9 m deep"
                                               "\n Wave Maker: Circulated, reversible, pump-driven flow");
    page3DescriptionLabel->setWordWrap(true);
    page3DescriptionLabel->setStyleSheet("QLabel {background-color:  rgb(79, 83, 89); color: #ffffff; border: 0px solid #000000; border-radius: 0px;}"
                                         "QLabel:disabled {background-color:  rgb(79, 83, 89); color: #ffffff; border: 0px solid #000000; border-radius: 0px;}");

    // WU TWB (Goseberg et al 2016, Nistor 2016)
    QLabel *page4Label = new QLabel();
    page4Label->setPixmap(page4Pixmap);
    page4Label->setScaledContents(true);
    page4Label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    page4Label->setMinimumHeight(minHeightDigitalTwinPhoto);
    page4Label->setMinimumWidth(minWidthDigitalTwinPhoto);
    page4Label->setMaximumHeight(maxHeightDigitalTwinPhoto);
    page4Label->setMaximumWidth(maxWidthDigitalTwinPhoto);
    page4Label->setAlignment(Qt::AlignCenter);
    QLabel *page4DescriptionLabel = new QLabel(" Waseda University's Tsunami Wave Basin - WU TWB"
                                               "\n "
                                               "\n Vacuum-Pump Controlled Reservoir Tank for Tsunami-Like Wave Generation."
                                               "\n "
                                               "\n Wave Flume Size: 9 m long, 4 m wide, 1 m deep"
                                               "\n Wave Maker: Vacuum-Pump Controlled Reservoir Tank."
                                               "\n Includes a frictional harbor apron, quay wall, and square columns.");
    page4DescriptionLabel->setWordWrap(true);
    page4DescriptionLabel->setStyleSheet("QLabel {background-color:  rgb(79, 83, 89); color: #ffffff; border: 0px solid #000000; border-radius: 0px;}"
                                         "QLabel:disabled {background-color:  rgb(79, 83, 89); color: #ffffff; border: 0px solid #000000; border-radius: 0px;}");

    // USGS DFF (Iverson 2020)
    QLabel *page5Label = new QLabel();
    page5Label->setPixmap(page5Pixmap);
    page5Label->setScaledContents(true);
    page5Label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    page5Label->setMinimumHeight(minHeightDigitalTwinPhoto);
    page5Label->setMinimumWidth(minWidthDigitalTwinPhoto);
    page5Label->setMaximumHeight(maxHeightDigitalTwinPhoto);
    page5Label->setMaximumWidth(maxWidthDigitalTwinPhoto);
    page5Label->setAlignment(Qt::AlignCenter);
    QLabel *page5DescriptionLabel = new QLabel(" United States Geological Survey's Debris Flow Flume - USGS DFF"
                                               "\n "
                                               "\n Large slope flume for studying granular flows and run-out."
                                               "\n "
                                               "\n Flow Flume Size: 100 m long, 2 m wide, 2 m deep"
                                               "\n Flow Maker: Gravity-Driven after retaining gates release."
                                               "\n Includes a 31 degree slope, swing gates, and run-out plane.");
    page5DescriptionLabel->setWordWrap(true);
    page5DescriptionLabel->setStyleSheet("QLabel {background-color:  rgb(79, 83, 89); color: #ffffff; border: 0px solid #000000; border-radius: 0px;}"
                                         "QLabel:disabled {background-color:  rgb(79, 83, 89); color: #ffffff; border: 0px solid #000000; border-radius: 0px;}");

    page1->setLayout(new QHBoxLayout());
    page2->setLayout(new QHBoxLayout());
    page3->setLayout(new QHBoxLayout());
    page4->setLayout(new QHBoxLayout());
    page5->setLayout(new QHBoxLayout());
    page1->layout()->addWidget(page1Label);
    page2->layout()->addWidget(page2Label);
    page3->layout()->addWidget(page3Label);
    page4->layout()->addWidget(page4Label);
    page5->layout()->addWidget(page5Label);
    page1->layout()->addWidget(page1DescriptionLabel);
    page2->layout()->addWidget(page2DescriptionLabel);
    page3->layout()->addWidget(page3DescriptionLabel);
    page4->layout()->addWidget(page4DescriptionLabel);
    page5->layout()->addWidget(page5DescriptionLabel);

    // -- Previous slide button
    QToolButton *prev = new QToolButton();
    // prev->setText("Prev");
    // prev->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    prev->setArrowType(Qt::LeftArrow);
    prev->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    prev->setMinimumSize(25, 50);
    prev->setMaximumSize(25, 50);
    prev->setStyleSheet("QToolButton {background-color: #ffffff; color: #000000; border: 1px solid #000000; border-radius: 5px; font-size: 16px; font-weight: bold;}"
                        "QToolButton:disabled {background-color: #d3d3d3; color: #000000; border: 1px solid #000000; border-radius: 5px; font-size: 16px; font-weight: bold;}");
    
    // -- Next slide button
    QToolButton *next = new QToolButton();
    // next->setText("Next");
    // next->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    next->setArrowType(Qt::RightArrow);
    next->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    next->setMinimumSize(25, 50);
    next->setMaximumSize(25, 50);
    next->setStyleSheet("QToolButton {background-color: #ffffff; color: #000000; border: 1px solid #000000; border-radius: 5px; font-size: 16px; font-weight: bold;}"
                        "QToolButton:disabled {background-color: #d3d3d3; color: #000000; border: 1px solid #000000; border-radius: 5px; font-size: 16px; font-weight: bold;}");
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(prev);
    buttonLayout->addWidget(stackedWidget);
    buttonLayout->addWidget(next);
    buttonLayout->setAlignment(Qt::AlignCenter);
    buttonLayout->setSpacing(0);
    buttonLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addLayout(buttonLayout, 1, 0);

    
    stackedWidget->setAnimation(QEasingCurve::Type::OutQuart);
    stackedWidget->setSpeed(500);

    QLabel *aboveTabs = new QLabel("\nSelect a NHERI SimCenter Digital Twin Above To Begin\n");
    aboveTabs->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(aboveTabs, 2, 0);
    // aboveTabs->setStyleSheet("QLabel {background-color:  rgb(79, 83, 89); color: #ffffff; border: 0px solid #000000; border-radius: 0px;}"
    //                          "QLabel:disabled {background-color:  rgb(79, 83, 89); color: #ffffff; border: 0px solid #000000; border-radius: 0px;}");

    // ==================== Results-View Set-Up ====================
    // QWidget* resultsWidget = new QWidget();
    // QVBoxLayout* resultsLayout  = new QVBoxLayout();
    // resultsWidget->setLayout(resultsLayout);

    // ==================== CFD Results-View Set-Up ====================
    // cfdResultsGroup = new QGroupBox("CFD Results", this);
    // cfdResultsLayout = new QGridLayout();
    // cfdResultsGroup->setLayout(cfdResultsLayout);

    // ==================== Simulation Set-Up ====================
    mpmSettings = new SettingsMPM();
    mpmBodies = new BodiesMPM();
    mpmBoundaries = new BoundariesMPM();
    mpmSensors = new SensorsMPM();
    mpmOutputs = new OutputsMPM();
    // mpmResults = new ResultsMPM(this);

    // ==================== Results-View Set-Up Part II ====================
    // resultsLayout->addWidget(mpmResults);
    // resultsLayout->addStretch();


    // theTabWidget = new QTabWidget();
    theTabWidget = new QTabWidget(this);
    theTabWidget->addTab(mpmSettings, QIcon(QString(":/icons/settings-black.svg")), "Settings");
    theTabWidget->addTab(mpmBodies, QIcon(QString(":/icons/deform-black.svg")), "Bodies");
    theTabWidget->addTab(mpmBoundaries, QIcon(QString(":/icons/man-door-black.svg")), "Boundaries");
    theTabWidget->addTab(mpmSensors, QIcon(QString(":/icons/dashboard-black.svg")), "Sensors");
    theTabWidget->addTab(mpmOutputs, QIcon(QString(":/icons/file-settings-black.svg")), "Outputs");   
    // theTabWidget->addTab(resultsWidget, QIcon(QString(":/icons/flag-black.svg")), "Results");   

    int sizePrimaryTabs =20;
    theTabWidget->setIconSize(QSize(sizePrimaryTabs,sizePrimaryTabs));
    // theTabWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

// #define NO_MPM_QT3D true
#if ( ( defined(_WIN32) || defined(__linux__) || defined(linux) || defined(WIN32) ) && !defined(__APPLE__) ) && !defined(NO_MPM_QT3D)
// #ifdef _WIN32
    // Only allow 3D visualization on Windows and Linux for now, Mac had issues with Qt3D 
    // Try to check the most reliable set of preprocessor definitions to detect the OS on common OS
    // https://stackoverflow.com/questions/5919996/how-to-detect-reliably-mac-os-x-ios-linux-windows-in-c-preprocessor
    // -----------------------------------------------------------------------------------
    // Create a 3D window and container widget and set the 3D window as its layout
    // Based on code by Alex44, 2018; https://stackoverflow.com/questions/23231012/how-to-render-in-qt3d-in-standard-gui-application)

    auto rootEntity = new Qt3DCore::QEntity();
    // auto view = new Qt3DExtras::Qt3DWindow();
    view = new Qt3DExtras::Qt3DWindow();
    container = QWidget::createWindowContainer(view);
    this->hideVisualization();
    

    // background color
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0xFFFFFF)));

    // Create a camera and set its position
    // auto camera = new Qt3DRender::QCamera(rootEntity);
    auto cameraEntity = view->camera();
    cameraEntity->setUpVector(QVector3D(0, 1.f, 0));
    cameraEntity->setPosition(QVector3D(-45.0f, 20.0f, 25.0f));
    cameraEntity->setViewCenter(QVector3D(25.0f, 2.0f, 2.0f));
    cameraEntity->viewAll();
    
    // Create a cube mesh
    // Qt3DExtras::QCuboidMesh *cubeMesh = new Qt3DExtras::QCuboidMesh();
    // Qt3DExtras::QCuboidMesh *cubeMesh[16][2][16];
    constexpr int maxCubeX = 16;
    constexpr int maxCubeY = 16;
    constexpr int maxCubeZ = 16;
    constexpr int maxDebrisX = 16;
    constexpr int maxDebrisY = 16;
    constexpr int maxDebrisZ = 16;
    constexpr int maxSensors = 32;

    QVector < QVector < QVector < Qt3DExtras::QCuboidMesh* > > > cubeMesh(maxDebrisX,
              QVector < QVector < Qt3DExtras::QCuboidMesh* > > (maxDebrisY,
                        QVector < Qt3DExtras::QCuboidMesh* > (maxDebrisZ, nullptr)));
    QVector < QVector < QVector < Qt3DExtras::QCuboidMesh* > > > debrisMesh(maxCubeX,
              QVector < QVector < Qt3DExtras::QCuboidMesh* > > (maxCubeY,
                        QVector < Qt3DExtras::QCuboidMesh* > (maxCubeZ, nullptr)));
    QVector < Qt3DExtras::QCuboidMesh* > sensorMesh(maxSensors, nullptr);

    for (int i = 0; i < maxDebrisX; i++) {
        for (int j = 0; j < maxDebrisY; j++) {
            for (int k = 0; k < maxDebrisZ; k++) {
              debrisMesh[i][j][k] = new Qt3DExtras::QCuboidMesh();
            }
        }
    }

    for (int i = 0; i < maxCubeX; i++) {
        for (int j = 0; j < maxCubeY; j++) {
            for (int k = 0; k < maxCubeZ; k++) {
              cubeMesh[i][j][k] = new Qt3DExtras::QCuboidMesh();
            }
        }
    }
        
    for (int i = 0; i < maxSensors; i++) {
        sensorMesh[i] = new Qt3DExtras::QCuboidMesh();
    }

    

    Qt3DExtras::QSphereMesh *originMesh = new Qt3DExtras::QSphereMesh();
    Qt3DExtras::QCylinderMesh *cylinderXMesh = new Qt3DExtras::QCylinderMesh();
    Qt3DExtras::QCylinderMesh *cylinderYMesh = new Qt3DExtras::QCylinderMesh();
    Qt3DExtras::QCylinderMesh *cylinderZMesh = new Qt3DExtras::QCylinderMesh();
    Qt3DExtras::QConeMesh *coneXMesh = new Qt3DExtras::QConeMesh();
    Qt3DExtras::QConeMesh *coneYMesh = new Qt3DExtras::QConeMesh();
    Qt3DExtras::QConeMesh *coneZMesh = new Qt3DExtras::QConeMesh();
    Qt3DExtras::QCuboidMesh *fluidMesh = new Qt3DExtras::QCuboidMesh();
    Qt3DExtras::QCuboidMesh *pistonMesh = new Qt3DExtras::QCuboidMesh();
    Qt3DRender::QMesh *twinMesh = new Qt3DRender::QMesh();

    QString bathymetryMesh = QCoreApplication::applicationDirPath() + QDir::separator() + "Examples" + QDir::separator() + "Bathymetry" + QDir::separator() + "OSU_LWF_Bathymetry.obj";
    twinMesh->setSource(QUrl::fromLocalFile(bathymetryMesh));
    // twinMesh->setSource(QUrl(QStringLiteral("qrc:/OSU_LWF_Bathymetry.obj")));
    // Qt3DRender::QMesh *hydroMesh = new Qt3DRender::QMesh();
    // hydroMesh->setSource(QUrl(QStringLiteral("qrc:/HydroUQ_Icon_Color.obj")));

    Qt3DExtras::QCuboidMesh *reservoirMesh = new Qt3DExtras::QCuboidMesh();
    Qt3DExtras::QCuboidMesh *harborMesh = new Qt3DExtras::QCuboidMesh();
    Qt3DExtras::QCuboidMesh *floorMesh = new Qt3DExtras::QCuboidMesh();
    Qt3DExtras::QCuboidMesh *gateMesh = new Qt3DExtras::QCuboidMesh();
    // Create a transform and set its scale
    // auto cubeTransform = new Qt3DCore::QTransform();
    // Qt3DCore::QTransform *cubeTransform[16][2][16];
    QVector < QVector < QVector < Qt3DCore::QTransform* > > > cubeTransform(16,
              QVector < QVector < Qt3DCore::QTransform* > > (16,
                        QVector < Qt3DCore::QTransform* > (16, nullptr)));
    QVector < QVector < QVector < Qt3DCore::QTransform* > > > debrisTransform(16,
              QVector < QVector < Qt3DCore::QTransform* > > (16,
                        QVector < Qt3DCore::QTransform* > (16, nullptr)));    
    QVector < Qt3DCore::QTransform* > sensorTransform(maxSensors, nullptr);
    // Qt3DCore::QTransform *sensorTransform[32];
    
    auto originTransform = new Qt3DCore::QTransform();
    auto cylinderXTransform = new Qt3DCore::QTransform();
    auto cylinderYTransform = new Qt3DCore::QTransform();
    auto cylinderZTransform = new Qt3DCore::QTransform();
    auto coneXTransform = new Qt3DCore::QTransform();
    auto coneYTransform = new Qt3DCore::QTransform();
    auto coneZTransform = new Qt3DCore::QTransform();

    auto fluidTransform = new Qt3DCore::QTransform();
    auto pistonTransform = new Qt3DCore::QTransform();
    auto twinTransform = new Qt3DCore::QTransform();
    // auto hydroTransform = new Qt3DCore::QTransform();
    auto reservoirTransform = new Qt3DCore::QTransform();
    auto harborTransform = new Qt3DCore::QTransform();
    auto floorTransform = new Qt3DCore::QTransform();
    // auto gateTransform = new Qt3DCore::QTransform();
    
    for (int i = 0; i < 16; i++) {
      for (int j = 0; j < 16; j++) {
        for (int k = 0; k < 16; k++) {
          cubeTransform[i][j][k] = new Qt3DCore::QTransform();
          cubeMesh[i][j][k]->setXExtent(1.0f);
          cubeMesh[i][j][k]->setYExtent(0.615f);
          cubeMesh[i][j][k]->setZExtent(1.0f);
          cubeTransform[i][j][k]->setScale(1.f);
          cubeTransform[i][j][k]->setTranslation(QVector3D(45.8f+1.0f/2.f, 2.0f+0.615f/2.f, 1.825f)); 
          cubeTransform[i][j][k]->setRotation(QQuaternion::fromAxisAndAngle(1.f, 1.f, 1.f, 0.f));
          
          debrisTransform[i][j][k] = new Qt3DCore::QTransform();
          debrisMesh[i][j][k]->setXExtent(0.5f);
          debrisMesh[i][j][k]->setYExtent(0.05f);
          debrisMesh[i][j][k]->setZExtent(0.1f);
          debrisTransform[i][j][k]->setScale(1.f);
          debrisTransform[i][j][k]->setTranslation(QVector3D((42.8f + 0.5f/2.f - 0.5f*4 - 0.1f*3) + i*(0.5f + 0.1f), 2.0f+0.05f/2.f + (0.05f + 0.1f)*j, (3.65f - 0.1f*(8) - 0.1f*(7))/2 + (0.1f+.1f)*(k))); 
          debrisTransform[i][j][k]->setRotation(QQuaternion::fromAxisAndAngle(1.f, 1.f, 1.f, 0.f));
        }
      }
    }
    for (int i = 0; i < maxSensors; i++) {
        sensorTransform[i] = new Qt3DCore::QTransform();
        sensorMesh[i]->setXExtent(0.1f);
        sensorMesh[i]->setYExtent(1.0f);
        sensorMesh[i]->setZExtent(0.1f);
        sensorTransform[i]->setScale(1.f);
        sensorTransform[i]->setTranslation(QVector3D(1.0f * i, 0.0f, 0.0f)); // Set the translation of each sensor mesh
        sensorTransform[i]->setRotation(QQuaternion::fromAxisAndAngle(1.f, 1.f, 1.f, 0.f));
        // sensorTransform[i]->setRotation(QQuaternion::fromEulerAngles(90.f, 0.f, 0.f));
    }                    
    // cubeMesh->setXExtent(1.016f);
    // cubeMesh->setYExtent(0.615f);
    // cubeMesh->setZExtent(1.016f);
    // cubeTransform->setScale(1.f);
    // cubeTransform->setTranslation(QVector3D(45.8f+1.016f/2.f, 2.0f+0.615f/2.f, 1.825f));
    // cubeTransform->setRotation(QQuaternion::fromAxisAndAngle(1.f, 1.f, 1.f, 0.f));

    originMesh->setRadius(0.15f);
    originTransform->setScale(1.f);
    originTransform->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));
    originTransform->setRotation(QQuaternion::fromAxisAndAngle(1.f, 1.f, 1.f, 0.f));

    cylinderXMesh->setRadius(0.05f);
    cylinderXMesh->setLength(1.0f);
    cylinderXTransform->setScale(1.f);
    cylinderXTransform->setRotation(QQuaternion::fromAxisAndAngle(0.f, 0.f, 1.f, 90.f));
    cylinderXTransform->setTranslation(QVector3D(0.5f, 0.0f, 0.0f));
    // cylinderXTransform->setRotation(QQuaternion::fromEulerAngles(90.f, 0.f, 0.f));

    coneXMesh->setTopRadius(0.0f);
    coneXMesh->setBottomRadius(0.1f);
    coneXMesh->setLength(0.25f);
    coneXTransform->setScale(1.f);
    coneXTransform->setTranslation(QVector3D(1.125f, 0.0f, 0.0f));
    coneXTransform->setRotation(QQuaternion::fromAxisAndAngle(0.f, 0.f, 1.f, 270.f));
    // coneXTransform->setRotation(QQuaternion::fromEulerAngles(90.f, 0.f, 0.f));


    cylinderYMesh->setRadius(0.05f);
    cylinderYMesh->setLength(1.0f);
    cylinderYTransform->setScale(1.f);
    cylinderYTransform->setRotation(QQuaternion::fromAxisAndAngle(0.f, 0.f, 1.f, 0.f));
    cylinderYTransform->setTranslation(QVector3D(0.0f, 0.5f, 0.0f));
    // cylinderYTransform->setRotation(QQuaternion::fromEulerAngles(0.f, 90.f, 0.f));

    coneYMesh->setTopRadius(0.0f);
    coneYMesh->setBottomRadius(0.1f);
    coneYMesh->setLength(0.25f);
    coneYTransform->setScale(1.f);
    coneYTransform->setRotation(QQuaternion::fromAxisAndAngle(0.f, 1.f, 0.f, 90.f));
    coneYTransform->setTranslation(QVector3D(0.0f, 1.125f, 0.0f));
    // coneYTransform->setRotation(QQuaternion::fromEulerAngles(0.f, 90.f, 0.f));

    cylinderZMesh->setRadius(0.05f);
    cylinderZMesh->setLength(1.0f);
    cylinderZTransform->setScale(1.f);
    cylinderZTransform->setRotation(QQuaternion::fromAxisAndAngle(1.f, 0.f, 0.f, 90.f));
    cylinderZTransform->setTranslation(QVector3D(0.0f, 0.0f, 0.5f));
    // cylinderZTransform->setRotation(QQuaternion::fromEulerAngles(0.f, 0.f, 90.f));

    coneZMesh->setTopRadius(0.0f);
    coneZMesh->setBottomRadius(0.1f);
    coneZMesh->setLength(0.25f);
    coneZTransform->setScale(1.f);
    coneZTransform->setRotation(QQuaternion::fromAxisAndAngle(1.f, 0.f, 0.f, 90.f));
    coneZTransform->setTranslation(QVector3D(0.0f, 0.0f, 1.125f));
    // coneZTransform->setRotation(QQuaternion::fromEulerAngles(0.f, 0.f, 90.f));

    fluidMesh->setXExtent(84.0f);
    fluidMesh->setYExtent(2.0f);
    fluidMesh->setZExtent(3.65f);
    fluidTransform->setScale(1.f);
    fluidTransform->setTranslation(QVector3D(42.0f+1.915f, 1.0f, 1.825f));
    fluidTransform->setRotation(QQuaternion::fromAxisAndAngle(1.f, 1.f, 1.f, 0.f));

    pistonMesh->setXExtent(0.25f);
    pistonMesh->setYExtent(4.6f);
    pistonMesh->setZExtent(3.65f);
    pistonTransform->setScale(1.f);
    pistonTransform->setTranslation(QVector3D(1.9f-0.25f/2.f, 4.6f/2.f, 3.65f/2.f));
    pistonTransform->setRotation(QQuaternion::fromAxisAndAngle(1.f, 1.f, 1.f, 0.f));


    twinTransform->setScale(1.f);
    twinTransform->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));
    twinTransform->setRotation(QQuaternion::fromAxisAndAngle(1.f, 1.f, 1.f, 0.f));
    twinTransform->setRotation(QQuaternion::fromEulerAngles(90.f, 0.f, 0.f));

    // hydroTransform->setScale(120.f);
    // hydroTransform->setTranslation(QVector3D(30.0f, 5.0f, -10.0f));
    // hydroTransform->setRotation(QQuaternion::fromAxisAndAngle(1.f, 1.f, 1.f, 0.f));
    // hydroTransform->setRotation(QQuaternion::fromEulerAngles(90.f, 0.f, 0.f));


    reservoirMesh->setXExtent(0.5f);
    reservoirMesh->setYExtent(0.67f);
    reservoirMesh->setZExtent(4.0f);
    reservoirTransform->setScale(1.f);
    reservoirTransform->setTranslation(QVector3D(0.5f/2.f, 0.23f + 0.67f/2.f, 4.0f/2.f));
    reservoirTransform->setRotation(QQuaternion::fromAxisAndAngle(1.f, 1.f, 1.f, 0.f));


    harborMesh->setXExtent(4.55f);
    harborMesh->setYExtent(0.255f);
    harborMesh->setZExtent(4.0f);
    harborTransform->setScale(1.f);
    harborTransform->setTranslation(QVector3D(4.45f + 4.55/2.f, 0.255f/2.f, 4.0f/2.0f));
    harborTransform->setRotation(QQuaternion::fromAxisAndAngle(1.f, 1.f, 1.f, 0.f));

    floorMesh->setXExtent(9.0f);
    floorMesh->setYExtent(0.125f);
    floorMesh->setZExtent(4.0f);
    floorTransform->setScale(1.f);
    floorTransform->setTranslation(QVector3D(9.0f/2.f, -0.125f/2.f, 4.0f/2.f));
    floorTransform->setRotation(QQuaternion::fromAxisAndAngle(1.f, 1.f, 1.f, 0.f));



    // Allow for camera controls
    auto camController = new Qt3DExtras::QOrbitCameraController(rootEntity);
    camController->setCamera(cameraEntity);


    // Create a material and set its color
    // auto cubeMaterial = new Qt3DExtras::QPhongMaterial();
    // Qt3DExtras::QPhongMaterial *cubeMaterial[16][2][16];
    QVector < QVector < QVector < Qt3DExtras::QPhongMaterial* > > > cubeMaterial(16,
              QVector < QVector < Qt3DExtras::QPhongMaterial* > > (16,
                        QVector < Qt3DExtras::QPhongMaterial* > (16, nullptr)));

    QVector < QVector < QVector < Qt3DExtras::QPhongMaterial* > > > debrisMaterial(16,
              QVector < QVector < Qt3DExtras::QPhongMaterial* > > (16,
                        QVector < Qt3DExtras::QPhongMaterial* > (16, nullptr)));
    
    QVector < Qt3DExtras::QPhongAlphaMaterial* > sensorMaterial(maxSensors, nullptr);


    auto originMaterial = new Qt3DExtras::QPhongAlphaMaterial();
    auto cylinderXMaterial = new Qt3DExtras::QPhongAlphaMaterial();
    auto cylinderYMaterial = new Qt3DExtras::QPhongAlphaMaterial();
    auto cylinderZMaterial = new Qt3DExtras::QPhongAlphaMaterial();
    auto coneXMaterial = new Qt3DExtras::QPhongAlphaMaterial();
    auto coneYMaterial = new Qt3DExtras::QPhongAlphaMaterial();
    auto coneZMaterial = new Qt3DExtras::QPhongAlphaMaterial();


    auto fluidMaterial = new Qt3DExtras::QPhongAlphaMaterial();
    auto pistonMaterial = new Qt3DExtras::QPhongMaterial();
    auto twinMaterial = new Qt3DExtras::QPhongMaterial();
    // auto hydroMaterial = new Qt3DExtras::QPhongMaterial();
    auto reservoirMaterial = new Qt3DExtras::QPhongAlphaMaterial();
    auto harborMaterial = new Qt3DExtras::QPhongMaterial();
    auto floorMaterial = new Qt3DExtras::QPhongMaterial();


    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            for (int k = 0; k < 16; k++) {
                cubeMaterial[i][j][k] = new Qt3DExtras::QPhongMaterial();
                cubeMaterial[i][j][k]->setDiffuse(QColor(QRgb(0xCC5500))); // orange

                debrisMaterial[i][j][k] = new Qt3DExtras::QPhongMaterial();
                debrisMaterial[i][j][k]->setDiffuse(QColor(QRgb(0x00FF00))); // green
            }
        }
    }
    for (int i = 0; i < maxSensors; i++) {
        sensorMaterial[i] = new Qt3DExtras::QPhongAlphaMaterial();
        sensorMaterial[i]->setDiffuse(QColor(QRgb(0xD40000))); // red
        // sensorMaterial[i]->setDiffuse(QColor(QRgb(0xBFBF2A))); // dark-yellow
        sensorMaterial[i]->setAlpha(0.4f); // set transparency
    }
    // cubeMaterial->setDiffuse(QColor(QRgb(0xCC5500)));
    // twinMaterial->setDiffuse(QColor(QRgb(0xFFFFFF)));

    // X axis will be red, Y axis will be green, Z axis will be blue. Origin will be black
    originMaterial->setDiffuse(QColor(QRgb(0x000000))); // black
    originMaterial->setAlpha(0.6f); // set transparency
    cylinderXMaterial->setDiffuse(QColor(QRgb(0xFF0000))); // red
    cylinderXMaterial->setAlpha(0.8f); // set transparency
    cylinderYMaterial->setDiffuse(QColor(QRgb(0x00FF00))); // green
    cylinderYMaterial->setAlpha(0.8f); // set transparency
    cylinderZMaterial->setDiffuse(QColor(QRgb(0x0000FF))); // blue
    cylinderZMaterial->setAlpha(0.8f); // set transparency
    coneXMaterial->setDiffuse(QColor(QRgb(0xFF0000))); // red
    coneXMaterial->setAlpha(0.8f); // set transparency
    coneYMaterial->setDiffuse(QColor(QRgb(0x00FF00))); // green
    coneYMaterial->setAlpha(0.8f); // set transparency
    coneZMaterial->setDiffuse(QColor(QRgb(0x0000FF))); // blue
    coneZMaterial->setAlpha(0.8f); // set transparency
    

    // Give twin an ambient conrete color
    twinMaterial->setAmbient(QColor(QRgb(0xCCCCCC)));

    // Give fluid material transparecny and blue color
    fluidMaterial->setDiffuse(QColor(QRgb(0x0000FF)));
    fluidMaterial->setAlpha(0.65f);
    fluidMaterial->setAmbient(QColor(QRgb(0x0000FF)));

    // Give piston material a teal color
    pistonMaterial->setDiffuse(QColor(QRgb(0x00FFFF)));

    // hydroMaterial->setDiffuse(QColor(QRgb(0x005FFF)));
    // hydroMaterial->setAmbient(QColor(QRgb(0x005FFF)));

    reservoirMaterial->setDiffuse(QColor(QRgb(0x0000FF)));
    reservoirMaterial->setAlpha(0.6f);
    reservoirMaterial->setAmbient(QColor(QRgb(0x0000FF))); // blue

    harborMaterial->setAmbient(QColor(QRgb(0x8B4513))); // wood
    floorMaterial->setAmbient(QColor(QRgb(0xCCCCCC)));


    auto originEntity = new Qt3DCore::QEntity(rootEntity);
    auto cylinderXEntity = new Qt3DCore::QEntity(rootEntity);
    auto cylinderYEntity = new Qt3DCore::QEntity(rootEntity);
    auto cylinderZEntity = new Qt3DCore::QEntity(rootEntity);
    auto coneXEntity = new Qt3DCore::QEntity(rootEntity);
    auto coneYEntity = new Qt3DCore::QEntity(rootEntity);
    auto coneZEntity = new Qt3DCore::QEntity(rootEntity);
    
    auto floorEntity = new Qt3DCore::QEntity(rootEntity);
    auto harborEntity = new Qt3DCore::QEntity(rootEntity);
    // auto gateEntity = new Qt3DCore::QEntity(rootEntity);

    // Create a cube entity and add the mesh, transform and material components
    auto twinEntity = new Qt3DCore::QEntity(rootEntity);

    QVector < QVector < QVector < Qt3DCore::QEntity* > > > cubeEntity(16,
              QVector < QVector < Qt3DCore::QEntity* > > (16,
                        QVector < Qt3DCore::QEntity* > (16, nullptr)));
    QVector < QVector < QVector < Qt3DCore::QEntity* > > > debrisEntity(16,
              QVector < QVector < Qt3DCore::QEntity* > > (16,
                        QVector < Qt3DCore::QEntity* > (16, nullptr)));    
    QVector < Qt3DCore::QEntity* > sensorEntity(maxSensors, nullptr);
    auto fluidEntity = new Qt3DCore::QEntity(rootEntity);
    auto reservoirEntity = new Qt3DCore::QEntity(rootEntity);
    auto pistonEntity = new Qt3DCore::QEntity(rootEntity);
    // auto hydroEntity = new Qt3DCore::QEntity(rootEntity);


    // Now disable the HydroUQ logo until its cleaned up
    // hydroEntity->setEnabled(false);

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            for (int k = 0; k < 16; k++) {
                cubeEntity[i][j][k] = new Qt3DCore::QEntity(rootEntity);
                cubeEntity[i][j][k]->addComponent(cubeMesh[i][j][k]);
                cubeEntity[i][j][k]->addComponent(cubeMaterial[i][j][k]);
                cubeEntity[i][j][k]->addComponent(cubeTransform[i][j][k]);
                cubeEntity[i][j][k]->setEnabled(false);
                debrisEntity[i][j][k] = new Qt3DCore::QEntity(rootEntity);
                debrisEntity[i][j][k]->addComponent(debrisMesh[i][j][k]);
                debrisEntity[i][j][k]->addComponent(debrisMaterial[i][j][k]);
                debrisEntity[i][j][k]->addComponent(debrisTransform[i][j][k]);
                debrisEntity[i][j][k]->setEnabled(false);
            }
        }
    }
    for (int i = 0; i < maxSensors; i++) {
        sensorEntity[i] = new Qt3DCore::QEntity(rootEntity);
        sensorEntity[i]->addComponent(sensorMesh[i]);
        sensorEntity[i]->addComponent(sensorMaterial[i]);
        sensorEntity[i]->addComponent(sensorTransform[i]);
        sensorEntity[i]->setEnabled(false);
    }

    // Not so sure about needing this...
    cubeEntity[0][0][0]->setEnabled(true);
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            for (int k = 0; k < 16; k++) {
                if (i < 4 && j < 1 && k < 8) {
                    cubeEntity[i][j][k]->setEnabled(true);
                }
            }
        }
    }

    // cubeEntity->addComponent(cubeMesh);
    // cubeEntity->addComponent(cubeMaterial);
    // cubeEntity->addComponent(cubeTransform);
    
    fluidEntity->addComponent(fluidMesh);
    fluidEntity->addComponent(fluidMaterial);
    fluidEntity->addComponent(fluidTransform);

    pistonEntity->addComponent(pistonMesh);
    pistonEntity->addComponent(pistonMaterial);
    pistonEntity->addComponent(pistonTransform);

    twinEntity->addComponent(twinMesh);
    twinEntity->addComponent(twinMaterial);
    twinEntity->addComponent(twinTransform);
 
    originEntity->addComponent(originMesh);
    originEntity->addComponent(originMaterial);
    originEntity->addComponent(originTransform);
    cylinderXEntity->addComponent(cylinderXMesh);
    cylinderXEntity->addComponent(cylinderXMaterial);
    cylinderXEntity->addComponent(cylinderXTransform);
    cylinderYEntity->addComponent(cylinderYMesh);
    cylinderYEntity->addComponent(cylinderYMaterial);
    cylinderYEntity->addComponent(cylinderYTransform);
    cylinderZEntity->addComponent(cylinderZMesh);
    cylinderZEntity->addComponent(cylinderZMaterial);
    cylinderZEntity->addComponent(cylinderZTransform);
    coneXEntity->addComponent(coneXMesh);
    coneXEntity->addComponent(coneXMaterial);
    coneXEntity->addComponent(coneXTransform);
    coneYEntity->addComponent(coneYMesh);
    coneYEntity->addComponent(coneYMaterial);
    coneYEntity->addComponent(coneYTransform);
    coneZEntity->addComponent(coneZMesh);
    coneZEntity->addComponent(coneZMaterial);
    coneZEntity->addComponent(coneZTransform);


    // hydroEntity->addComponent(hydroMesh);
    // hydroEntity->addComponent(hydroMaterial);
    // hydroEntity->addComponent(hydroTransform);
    
    floorEntity->addComponent(floorMesh);
    floorEntity->addComponent(floorMaterial);
    floorEntity->addComponent(floorTransform);

    harborEntity->addComponent(harborMesh);
    harborEntity->addComponent(harborMaterial);
    harborEntity->addComponent(harborTransform);

    reservoirEntity->addComponent(reservoirMesh);
    reservoirEntity->addComponent(reservoirMaterial);
    reservoirEntity->addComponent(reservoirTransform);

    reservoirEntity->setEnabled(false);
    harborEntity->setEnabled(false);
    floorEntity->setEnabled(false);


    // Set the root entity of the 3D window
    view->setRootEntity(rootEntity);


    // Make lambda function to update the position of cuboid design structure
    auto updateFluid = [=]() {
      QJsonObject bodiesObjectJSON; 
      QJsonArray bodiesArrayJSON;
      bodiesObjectJSON["bodies"] = bodiesArrayJSON;
      mpmBodies->outputToJSON(bodiesObjectJSON);
      int fluidBodyID = 0;
      int fluidGeometryID = 0;
      double swl = bodiesObjectJSON["bodies"].toArray()[fluidBodyID].toObject()["geometry"].toArray()[fluidGeometryID].toObject()["standing_water_level"].toDouble();
      double originX = bodiesObjectJSON["bodies"].toArray()[fluidBodyID].toObject()["geometry"].toArray()[fluidGeometryID].toObject()["offset"].toArray()[0].toDouble();
      double originY = bodiesObjectJSON["bodies"].toArray()[fluidBodyID].toObject()["geometry"].toArray()[fluidGeometryID].toObject()["offset"].toArray()[1].toDouble();
      double originZ = bodiesObjectJSON["bodies"].toArray()[fluidBodyID].toObject()["geometry"].toArray()[fluidGeometryID].toObject()["offset"].toArray()[2].toDouble();
      double lengthX = bodiesObjectJSON["bodies"].toArray()[fluidBodyID].toObject()["geometry"].toArray()[fluidGeometryID].toObject()["span"].toArray()[0].toDouble();
      double lengthY = swl;
      double lengthZ = bodiesObjectJSON["bodies"].toArray()[fluidBodyID].toObject()["geometry"].toArray()[fluidGeometryID].toObject()["span"].toArray()[2].toDouble();
      originX = lengthX/2.f + originX;  
      originY = swl/2.f + originY;
      originZ = lengthZ/2.f + originZ;
      fluidMesh->setXExtent(lengthX);
      fluidMesh->setYExtent(lengthY);
      fluidMesh->setZExtent(lengthZ);
      // double wave_maker_neutral = 1.915f;
      fluidTransform->setTranslation(QVector3D(originX, originY, originZ));
    };

    auto updateBoundaryStructureSize = [=]() {
      double lengthX = mpmBoundaries->getDimensionX(mpmBoundaries->getStructureBoundary());
      double lengthY = mpmBoundaries->getDimensionY(mpmBoundaries->getStructureBoundary());
      double lengthZ = mpmBoundaries->getDimensionZ(mpmBoundaries->getStructureBoundary());
      int arrayX = mpmBoundaries->getArrayX(mpmBoundaries->getStructureBoundary());
      int arrayY = mpmBoundaries->getArrayY(mpmBoundaries->getStructureBoundary());
      int arrayZ = mpmBoundaries->getArrayZ(mpmBoundaries->getStructureBoundary());
      arrayX = arrayX > 0 ? (arrayX < 16 ? arrayX : 16) : 1;
      arrayY = arrayY > 0 ? (arrayY < 16 ? arrayY : 16) : 1;
      arrayZ = arrayZ > 0 ? (arrayZ < 16 ? arrayZ : 16) : 1;
      for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
          for (int k = 0; k < 16; k++) {
            if (i < arrayX && j < arrayY && k < arrayZ) {
              cubeMesh[i][j][k]->setXExtent(lengthX);
              cubeMesh[i][j][k]->setYExtent(lengthY);
              cubeMesh[i][j][k]->setZExtent(lengthZ);
              if (cubeEntity[i][j][k]) cubeEntity[i][j][k]->setEnabled(true);
            } else {
              if (cubeEntity[i][j][k]) cubeEntity[i][j][k]->setEnabled(false);
            }
          }
        }
      }

      // cubeMesh->setXExtent(lengthX);
      // cubeMesh->setYExtent(lengthY);
      // cubeMesh->setZExtent(lengthZ);
    };

  // Make lambda function to update the position of debris set
  auto updateDebris = [=]() {
    QJsonObject bodiesObjectJSON; 
    QJsonArray bodiesArrayJSON;
    bodiesObjectJSON["bodies"] = bodiesArrayJSON;
    mpmBodies->outputToJSON(bodiesObjectJSON);
    int debrisBodyID = 1;
    int debrisGeometryID = 0;
    // double swl = bodiesObjectJSON["bodies"].toArray()[debrisBodyID].toObject()["geometry"].toArray()[debrisGeometryID].toObject()["standing_water_level"].toDouble();
    double originX = bodiesObjectJSON["bodies"].toArray()[debrisBodyID].toObject()["geometry"].toArray()[debrisGeometryID].toObject()["offset"].toArray()[0].toDouble();
    double originY = bodiesObjectJSON["bodies"].toArray()[debrisBodyID].toObject()["geometry"].toArray()[debrisGeometryID].toObject()["offset"].toArray()[1].toDouble();
    double originZ = bodiesObjectJSON["bodies"].toArray()[debrisBodyID].toObject()["geometry"].toArray()[debrisGeometryID].toObject()["offset"].toArray()[2].toDouble();
    double lengthX = bodiesObjectJSON["bodies"].toArray()[debrisBodyID].toObject()["geometry"].toArray()[debrisGeometryID].toObject()["span"].toArray()[0].toDouble();
    double lengthY = bodiesObjectJSON["bodies"].toArray()[debrisBodyID].toObject()["geometry"].toArray()[debrisGeometryID].toObject()["span"].toArray()[1].toDouble();
    double lengthZ = bodiesObjectJSON["bodies"].toArray()[debrisBodyID].toObject()["geometry"].toArray()[debrisGeometryID].toObject()["span"].toArray()[2].toDouble();
    int arrayX = bodiesObjectJSON["bodies"].toArray()[debrisBodyID].toObject()["geometry"].toArray()[debrisGeometryID].toObject()["array"].toArray()[0].toInt();
    int arrayY = bodiesObjectJSON["bodies"].toArray()[debrisBodyID].toObject()["geometry"].toArray()[debrisGeometryID].toObject()["array"].toArray()[1].toInt();
    int arrayZ = bodiesObjectJSON["bodies"].toArray()[debrisBodyID].toObject()["geometry"].toArray()[debrisGeometryID].toObject()["array"].toArray()[2].toInt();
    double spacingX = bodiesObjectJSON["bodies"].toArray()[debrisBodyID].toObject()["geometry"].toArray()[debrisGeometryID].toObject()["spacing"].toArray()[0].toDouble();
    double spacingY = bodiesObjectJSON["bodies"].toArray()[debrisBodyID].toObject()["geometry"].toArray()[debrisGeometryID].toObject()["spacing"].toArray()[1].toDouble();
    double spacingZ = bodiesObjectJSON["bodies"].toArray()[debrisBodyID].toObject()["geometry"].toArray()[debrisGeometryID].toObject()["spacing"].toArray()[2].toDouble();
    arrayX = arrayX > 0 ? (arrayX < 16 ? arrayX : 16) : 1;
    arrayY = arrayY > 0 ? (arrayY < 16 ? arrayY : 16) : 1;
    arrayZ = arrayZ > 0 ? (arrayZ < 16 ? arrayZ : 16) : 1;
    originX = lengthX/2.f + originX;  
    originY = lengthY/2.f + originY;
    originZ = lengthZ/2.f + originZ;
    for (int i = 0; i < 16; i++) {
      for (int j = 0; j < 16; j++) {
        for (int k = 0; k < 16; k++) {
          if (i < arrayX && j < arrayY && k < arrayZ) {
            debrisMesh[i][j][k]->setXExtent(lengthX);
            debrisMesh[i][j][k]->setYExtent(lengthY);
            debrisMesh[i][j][k]->setZExtent(lengthZ);
            debrisTransform[i][j][k]->setTranslation(QVector3D(originX + spacingX*i, originY + spacingY * j, originZ + spacingZ * k));
            if (debrisEntity[i][j][k]) debrisEntity[i][j][k]->setEnabled(true);
          } else {
            if (debrisEntity[i][j][k]) debrisEntity[i][j][k]->setEnabled(false);
          }
        }
      }
    }
  };


  // Make lambda function to update the position of sensor set
  auto updateSensors = [=]() {
    QJsonObject sensorsObjectJSON;
    QJsonArray sensorsArrayJSON;
    sensorsObjectJSON["particle-sensors"] = sensorsArrayJSON;
    mpmSensors->outputToJSON(sensorsObjectJSON);
    int sensorID = 0;
    // Number of sensors
    int numParticleSensors = sensorsObjectJSON["particle-sensors"].toArray().size();
    int numGridSensors = sensorsObjectJSON["grid-sensors"].toArray().size();
    int numSensors = numParticleSensors + numGridSensors;
    if (numSensors > maxSensors) {
      numSensors = maxSensors; // Limit to maxSensors that we mem reserved
      if (numParticleSensors > maxSensors) {
        numParticleSensors = maxSensors; // Limit to maxSensors that we mem reserved
      }
      if (numGridSensors > maxSensors) {
        numGridSensors = maxSensors; // Limit to maxSensors that we mem reserved
      }
      if (numParticleSensors + numGridSensors > maxSensors) {
        numParticleSensors = maxSensors - numGridSensors; // Limit to maxSensors that we mem reserved
      }
      if (numGridSensors + numParticleSensors > maxSensors) {
        numGridSensors = maxSensors - numParticleSensors; // Limit to maxSensors that we mem reserved
      }
    }
    // if (numSensors > maxSensors) {
    //   sensorEntity.resize(numSensors);
    //   sensorMesh.resize(numSensors);
    //   sensorTransform.resize(numSensors);
    //   sensorMaterial.resize(numSensors);
    // }
    // sensorEntity.resize(numSensors);
    // Reset all sensors to disabled, re-enable only the ones that are in the JSON object
    for (int i = 0; i < maxSensors; i++) {
        sensorEntity[i]->setEnabled(false);
    }
    // Loop through each sensor and update its position
    int j = 0;
    for (int i = 0; i < numParticleSensors; i++) {
      // Get the sensor position from the JSON object  
      double originX = sensorsObjectJSON["particle-sensors"].toArray()[i].toObject()["domain_start"].toArray()[0].toDouble();
      double originY = sensorsObjectJSON["particle-sensors"].toArray()[i].toObject()["domain_start"].toArray()[1].toDouble();
      double originZ = sensorsObjectJSON["particle-sensors"].toArray()[i].toObject()["domain_start"].toArray()[2].toDouble();
      double lengthX = sensorsObjectJSON["particle-sensors"].toArray()[i].toObject()["domain_end"].toArray()[0].toDouble() - originX;
      double lengthY = sensorsObjectJSON["particle-sensors"].toArray()[i].toObject()["domain_end"].toArray()[1].toDouble() - originY;
      double lengthZ = sensorsObjectJSON["particle-sensors"].toArray()[i].toObject()["domain_end"].toArray()[2].toDouble() - originZ;


      // Update the sensor transform with the new position
      sensorTransform[i]->setTranslation(QVector3D(originX + lengthX/2.f, originY + lengthY/2.f, originZ + lengthZ/2.f));
      sensorTransform[i]->setScale(1.f);
      sensorTransform[i]->setRotation(QQuaternion::fromAxisAndAngle(1.f, 1.f, 1.f, 0.f));
      sensorMesh[i]->setXExtent(lengthX);
      sensorMesh[i]->setYExtent(lengthY);
      sensorMesh[i]->setZExtent(lengthZ);
      sensorEntity[i]->setEnabled(true);
      j = i + 1;
    }
    // Loop through each sensor and update its position
    for (int i = 0; i < numGridSensors; i++) {
      // Get the sensor position from the JSON object  
      double originX = sensorsObjectJSON["grid-sensors"].toArray()[i].toObject()["domain_start"].toArray()[0].toDouble();
      double originY = sensorsObjectJSON["grid-sensors"].toArray()[i].toObject()["domain_start"].toArray()[1].toDouble();
      double originZ = sensorsObjectJSON["grid-sensors"].toArray()[i].toObject()["domain_start"].toArray()[2].toDouble();
      double lengthX = sensorsObjectJSON["grid-sensors"].toArray()[i].toObject()["domain_end"].toArray()[0].toDouble() - originX;
      double lengthY = sensorsObjectJSON["grid-sensors"].toArray()[i].toObject()["domain_end"].toArray()[1].toDouble() - originY;
      double lengthZ = sensorsObjectJSON["grid-sensors"].toArray()[i].toObject()["domain_end"].toArray()[2].toDouble() - originZ;


      // Update the sensor transform with the new position
      sensorTransform[j]->setTranslation(QVector3D(originX + lengthX/2.f, originY + lengthY/2.f, originZ + lengthZ/2.f));
      sensorTransform[j]->setScale(1.f);
      sensorTransform[j]->setRotation(QQuaternion::fromAxisAndAngle(1.f, 1.f, 1.f, 0.f));
      sensorMesh[j]->setXExtent(lengthX);
      sensorMesh[j]->setYExtent(lengthY);
      sensorMesh[j]->setZExtent(lengthZ);
      sensorEntity[j]->setEnabled(true);
      j += 1;
    }
  };

    // cubeMesh->setXExtent(lengthX);
    // cubeMesh->setYExtent(lengthY);
    // cubeMesh->setZExtent(lengthZ);

    // Make lambda function to update the position of cuboid design structure
    auto updateBoundaryStructurePosition = [=]() {
      double originX = mpmBoundaries->getOriginX(mpmBoundaries->getStructureBoundary());
      double originY = mpmBoundaries->getOriginY(mpmBoundaries->getStructureBoundary());
      double originZ = mpmBoundaries->getOriginZ(mpmBoundaries->getStructureBoundary());
      double lengthX = mpmBoundaries->getDimensionX(mpmBoundaries->getStructureBoundary());
      double lengthY = mpmBoundaries->getDimensionY(mpmBoundaries->getStructureBoundary());
      double lengthZ = mpmBoundaries->getDimensionZ(mpmBoundaries->getStructureBoundary());
      originX = lengthX/2.f + originX;  
      originY = lengthY/2.f + originY;
      originZ = lengthZ/2.f + originZ;

      // cubeTransform->setTranslation(QVector3D(originX, originY, originZ));

      int arrayX = mpmBoundaries->getArrayX(mpmBoundaries->getStructureBoundary());
      int arrayY = mpmBoundaries->getArrayY(mpmBoundaries->getStructureBoundary());
      int arrayZ = mpmBoundaries->getArrayZ(mpmBoundaries->getStructureBoundary());
      arrayX = arrayX > 0 ? (arrayX < 16 ? arrayX : 16) : 1;
      arrayY = arrayY > 0 ? (arrayY < 16 ? arrayY : 16) : 1;
      arrayZ = arrayZ > 0 ? (arrayZ < 16 ? arrayZ : 16) : 1;

      double spacingX = mpmBoundaries->getSpacingX(mpmBoundaries->getStructureBoundary());
      double spacingY = mpmBoundaries->getSpacingY(mpmBoundaries->getStructureBoundary());
      double spacingZ = mpmBoundaries->getSpacingZ(mpmBoundaries->getStructureBoundary());
      for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
          for (int k = 0; k < 16; k++) {
            if (i < arrayX && j < arrayY && k < arrayZ) {
              cubeTransform[i][j][k]->setTranslation(QVector3D(originX + spacingX*i, originY + spacingY * j, originZ + spacingZ * k));
              if (cubeEntity[i][j][k]) cubeEntity[i][j][k]->setEnabled(true);
            } else {
              if (cubeEntity[i][j][k]) cubeEntity[i][j][k]->setEnabled(false);
            }
          }
        }
      }


    };

    auto updateBoundaryStructureArray = [=]() {

      double originX = mpmBoundaries->getOriginX(mpmBoundaries->getStructureBoundary());
      double originY = mpmBoundaries->getOriginY(mpmBoundaries->getStructureBoundary());
      double originZ = mpmBoundaries->getOriginZ(mpmBoundaries->getStructureBoundary());
      double lengthX = mpmBoundaries->getDimensionX(mpmBoundaries->getStructureBoundary());
      double lengthY = mpmBoundaries->getDimensionY(mpmBoundaries->getStructureBoundary());
      double lengthZ = mpmBoundaries->getDimensionZ(mpmBoundaries->getStructureBoundary());
      double spacingX = mpmBoundaries->getSpacingX(mpmBoundaries->getStructureBoundary());
      double spacingY = mpmBoundaries->getSpacingY(mpmBoundaries->getStructureBoundary());
      double spacingZ = mpmBoundaries->getSpacingZ(mpmBoundaries->getStructureBoundary());

      originX = lengthX/2.f + originX;
      originY = lengthY/2.f + originY;
      originZ = lengthZ/2.f + originZ;

      int arrayX = mpmBoundaries->getArrayX(mpmBoundaries->getStructureBoundary());
      int arrayY = mpmBoundaries->getArrayY(mpmBoundaries->getStructureBoundary());
      int arrayZ = mpmBoundaries->getArrayZ(mpmBoundaries->getStructureBoundary());
      arrayX = arrayX > 0 ? (arrayX < 16 ? arrayX : 16) : 1;
      arrayY = arrayY > 0 ? (arrayY < 16 ? arrayY : 16) : 1;
      arrayZ = arrayZ > 0 ? (arrayZ < 16 ? arrayZ : 16) : 1;
      // cubeMesh is now a 3d array of cubeMesh
      // Since arrayX, arrayY, and arrayZ updated, we need to update the size of the array
      for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
          for (int k = 0; k < 16; k++) {
            cubeMesh[i][j][k]->setXExtent(lengthX);
            cubeMesh[i][j][k]->setYExtent(lengthY);
            cubeMesh[i][j][k]->setZExtent(lengthZ);
            cubeTransform[i][j][k]->setTranslation(QVector3D(originX + spacingX*i, originY + spacingY * j, originZ + spacingZ * k));
            if (i < arrayX && j < arrayY && k < arrayZ)
            {
              // cubeEntity[i][j][k]->addComponent(cubeMesh[i][j][k]);
              // cubeEntity[i][j][k]->addComponent(cubeMaterial[i][j][k]);
              // cubeEntity[i][j][k]->addComponent(cubeTransform[i][j][k]);
              cubeEntity[i][j][k]->setEnabled(true);
            }
            else 
            {
              cubeEntity[i][j][k]->setEnabled(false);
              // cubeEntity[i][j][k]->removeComponent(cubeMesh[i][j][k]);
              // cubeEntity[i][j][k]->removeComponent(cubeMaterial[i][j][k]);
              // cubeEntity[i][j][k]->removeComponent(cubeTransform[i][j][k]);
            }
          }
        }
      }

    };

    auto updateBoundaryStructureSpacing = [=]() {

      double originX = mpmBoundaries->getOriginX(mpmBoundaries->getStructureBoundary());
      double originY = mpmBoundaries->getOriginY(mpmBoundaries->getStructureBoundary());
      double originZ = mpmBoundaries->getOriginZ(mpmBoundaries->getStructureBoundary());
      double lengthX = mpmBoundaries->getDimensionX(mpmBoundaries->getStructureBoundary());
      double lengthY = mpmBoundaries->getDimensionY(mpmBoundaries->getStructureBoundary());
      double lengthZ = mpmBoundaries->getDimensionZ(mpmBoundaries->getStructureBoundary());
      double spacingX = mpmBoundaries->getSpacingX(mpmBoundaries->getStructureBoundary());
      double spacingY = mpmBoundaries->getSpacingY(mpmBoundaries->getStructureBoundary());
      double spacingZ = mpmBoundaries->getSpacingZ(mpmBoundaries->getStructureBoundary());

      originX = lengthX/2.f + originX;
      originY = lengthY/2.f + originY;
      originZ = lengthZ/2.f + originZ;

      int arrayX = mpmBoundaries->getArrayX(mpmBoundaries->getStructureBoundary());
      int arrayY = mpmBoundaries->getArrayY(mpmBoundaries->getStructureBoundary());
      int arrayZ = mpmBoundaries->getArrayZ(mpmBoundaries->getStructureBoundary());
      // cubeMesh is now a 3d array of cubeMesh
      // Since arrayX, arrayY, and arrayZ updated, we need to update the size of the array
      arrayX = arrayX > 0 ? (arrayX < 16 ? arrayX : 16) : 1;
      arrayY = arrayY > 0 ? (arrayY < 16 ? arrayY : 16) : 1;
      arrayZ = arrayZ > 0 ? (arrayZ < 16 ? arrayZ : 16) : 1;
      
      for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
          for (int k = 0; k < 16; k++) {
            cubeMesh[i][j][k]->setXExtent(lengthX);
            cubeMesh[i][j][k]->setYExtent(lengthY);
            cubeMesh[i][j][k]->setZExtent(lengthZ);
            cubeTransform[i][j][k]->setTranslation(QVector3D(originX + spacingX*i, originY + spacingY * j, originZ + spacingZ * k));
            if (i < arrayX && j < arrayY && k < arrayZ) {
              // cubeEntity[i][j][k]->addComponent(cubeMesh[i][j][k]);
              // cubeEntity[i][j][k]->addComponent(cubeMaterial[i][j][k]);
              // cubeEntity[i][j][k]->addComponent(cubeTransform[i][j][k]);
              cubeEntity[i][j][k]->setEnabled(true);
            } else {
              cubeEntity[i][j][k]->setEnabled(false);
              // cubeEntity[i][j][k]->removeComponent(cubeMesh[i][j][k]);
              // cubeEntity[i][j][k]->removeComponent(cubeMaterial[i][j][k]);
              // cubeEntity[i][j][k]->removeComponent(cubeTransform[i][j][k]);
            }
          }
        }
      }

    };

    auto updateBoundaryPaddleSize = [=]() {
      double lengthX = mpmBoundaries->getDimensionX(mpmBoundaries->getPaddleBoundary());
      double lengthY = mpmBoundaries->getDimensionY(mpmBoundaries->getPaddleBoundary());
      double lengthZ = mpmBoundaries->getDimensionZ(mpmBoundaries->getPaddleBoundary());
      pistonMesh->setXExtent(lengthX);
      pistonMesh->setYExtent(lengthY);
      pistonMesh->setZExtent(lengthZ);
    };

    // Make lambda function to update the position of cuboid design structure
    auto updateBoundaryPaddlePosition = [=]() {
      double originX = mpmBoundaries->getOriginX(mpmBoundaries->getPaddleBoundary());
      double originY = mpmBoundaries->getOriginY(mpmBoundaries->getPaddleBoundary());
      double originZ = mpmBoundaries->getOriginZ(mpmBoundaries->getPaddleBoundary());
      double lengthX = mpmBoundaries->getDimensionX(mpmBoundaries->getPaddleBoundary());
      double lengthY = mpmBoundaries->getDimensionY(mpmBoundaries->getPaddleBoundary());
      double lengthZ = mpmBoundaries->getDimensionZ(mpmBoundaries->getPaddleBoundary());
      originX = lengthX/2.f + originX;  
      originY = lengthY/2.f + originY;
      originZ = lengthZ/2.f + originZ;
      pistonTransform->setTranslation(QVector3D(originX, originY, originZ));
    };


    auto updateDigitalTwin = [=](int index) {
      if (index == 0) {
        twinEntity->setEnabled(true);
        for (int i = 0; i < 16; i++) {
          for (int j = 0; j < 16; j++) {
            for (int k = 0; k < 16; k++) {
              if (i < 16 && j < 16 && k < 16)
              {
                cubeEntity[i][j][k]->setEnabled(false);
                if (i == 0 && j == 0 && k == 0) cubeEntity[i][j][k]->setEnabled(true);

                // debrisEntity[i][j][k]->setEnabled(false);
                // if (i < 4 && j < 1 && k < 4) debrisEntity[i][j][k]->setEnabled(true);
              }
            }
          }
        }
        // cubeEntity[i][j][k]->setEnabled(true);
        fluidEntity->setEnabled(true);
        pistonEntity->setEnabled(true);
        twinTransform->setScale3D(QVector3D(1.f,1.f,1.f));
        // hydroEntity->setEnabled(false);
        reservoirEntity->setEnabled(false);
        harborEntity->setEnabled(false);
        floorEntity->setEnabled(false);
      } else if (index == 1) {
        twinEntity->setEnabled(true);
        for (int i = 0; i < 16; i++) {
          for (int j = 0; j < 16; j++) {
            for (int k = 0; k < 16; k++) {
              if (i < 16-1 && j < 16-1 && k < 16-1)
              {
                cubeEntity[i][j][k]->setEnabled(false);
                if (i == 0 && j == 0 && k < 2) cubeEntity[i][j][k]->setEnabled(true);
                // debrisEntity[i][j][k]->setEnabled(false);
              }
            }
          }
        }
        fluidEntity->setEnabled(true);
        pistonEntity->setEnabled(true);
        twinTransform->setScale3D(QVector3D(0.6f,7.25f,1.f/1.75f));
        // hydroEntity->setEnabled(false);
        reservoirEntity->setEnabled(false);
        harborEntity->setEnabled(false);
        floorEntity->setEnabled(false);
      } else if (index == 2) {
        twinEntity->setEnabled(false);
        for (int i = 0; i < 16; i++) {
          for (int j = 0; j < 16; j++) {
            for (int k = 0; k < 16; k++) {
              if (i < 16 && j < 16 && k < 16)
              {
                cubeEntity[i][j][k]->setEnabled(false);
                if (i == 0 && j == 0 && k == 0) cubeEntity[i][j][k]->setEnabled(true);
                // debrisEntity[i][j][k]->setEnabled(false);
              }
            }
          }
        }
        fluidEntity->setEnabled(true);
        pistonEntity->setEnabled(false);
        // hydroEntity->setEnabled(false);
        reservoirEntity->setEnabled(false);
        harborEntity->setEnabled(false);
        floorEntity->setEnabled(true);
        floorTransform->setTranslation(QVector3D(12.0f/2, -0.125f/2, 1.0f/2)); 
        floorMesh->setXExtent(12.f);
        floorMesh->setYExtent(0.125f);
        floorMesh->setZExtent(1.f);
      } else if (index == 3) {
        twinEntity->setEnabled(false);
        for (int i = 0; i < 16; i++) {
          for (int j = 0; j < 16; j++) {
            for (int k = 0; k < 16; k++) {
              if (i < 16 && j < 16 && k < 16)
              {
                cubeEntity[i][j][k]->setEnabled(false);
                if (i < 2 && j == 0 && k < 5) cubeEntity[i][j][k]->setEnabled(true);
                // debrisEntity[i][j][k]->setEnabled(false);
              }
            }
          }
        }
        // hydroEntity->setEnabled(false);
        floorEntity->setEnabled(true);
        floorTransform->setTranslation(QVector3D(9.0f/2, -0.125f/2, 4.0f/2)); 
        floorMesh->setXExtent(9.f);
        floorMesh->setYExtent(0.125f);
        floorMesh->setZExtent(4.f);
        harborEntity->setEnabled(true);
        fluidEntity->setEnabled(true);
        pistonEntity->setEnabled(true);
        reservoirEntity->setEnabled(true);
      } else if (index == 4) {
        twinEntity->setEnabled(false);
        for (int i = 0; i < 16; i++) {
          for (int j = 0; j < 16; j++) {
            for (int k = 0; k < 16; k++) {
              if (i < 16 && j < 16 && k < 16)
              {
                cubeEntity[i][j][k]->setEnabled(false);
                // debrisEntity[i][j][k]->setEnabled(false);
              }
            }
          }
        }
        fluidEntity->setEnabled(false);
        pistonEntity->setEnabled(true);
        // hydroEntity->setEnabled(false);
        reservoirEntity->setEnabled(false);
        harborEntity->setEnabled(false);
        floorEntity->setEnabled(false);
      }
      updateFluid();
      updateBoundaryStructureSize();
      updateBoundaryStructurePosition();
      updateBoundaryPaddleSize();
      updateBoundaryPaddlePosition();
    };


    // Add check boxes to toggle the visibility of objects
    QCheckBox *twinCheckBox = new QCheckBox("Flume");
    twinCheckBox->setChecked(true);
    connect(twinCheckBox, &QCheckBox::stateChanged, [=](int state){
      if (state == Qt::Checked) {
        twinEntity->setEnabled(true);
      } else {
        twinEntity->setEnabled(false);
      }
    });
    QCheckBox *fluidCheckBox = new QCheckBox("Fluid");
    fluidCheckBox->setChecked(true);
    connect(fluidCheckBox, &QCheckBox::stateChanged, [=](int state){
      if (state == Qt::Checked) {
        updateFluid();
        fluidEntity->setEnabled(true);
      } else {
        fluidEntity->setEnabled(false);
        // if (reservoirEntity->isEnabled()) {
          // reservoirEntity->setEnabled(false);
        // }
      }
    });
    QCheckBox *paddleCheckBox = new QCheckBox("Paddle");  
    paddleCheckBox->setChecked(true);
    connect(paddleCheckBox, &QCheckBox::stateChanged, [=](int state){
      if (state == Qt::Checked) {
        pistonEntity->setEnabled(true);
      } else {
        pistonEntity->setEnabled(false);
      }
    });
    QCheckBox *debrisCheckBox = new QCheckBox("Debris");
    debrisCheckBox->setChecked(true);
    connect(debrisCheckBox, &QCheckBox::stateChanged, [=](int state){
      if (state == Qt::Checked) {
        updateDebris();
      } else {
        for (int i = 0; i < 16; i++) {
          for (int j = 0; j < 16; j++) {
            for (int k = 0; k < 16; k++) {
              debrisEntity[i][j][k]->setEnabled(false);
            }
          }
        }
      }
    });
    QCheckBox *sensorCheckBox = new QCheckBox("Sensors");
    sensorCheckBox->setChecked(true);
    connect(sensorCheckBox, &QCheckBox::stateChanged, [=](int state){
      if (state == Qt::Checked) {
        updateSensors();
      } else {
        for (int i = 0; i < maxSensors; i++) {
          sensorEntity[i]->setEnabled(false);
        }
      }
    });
    QCheckBox *cubeCheckBox = new QCheckBox("Rigid Structure");
    cubeCheckBox->setChecked(true);
    connect(cubeCheckBox, &QCheckBox::stateChanged, [=](int state){
      if (state == Qt::Checked) {
        updateBoundaryStructureArray();
        updateBoundaryStructurePosition();
        updateBoundaryStructureSize();
      } else {
        for (int i = 0; i < 16; i++) {
          for (int j = 0; j < 16; j++) {
            for (int k = 0; k < 16; k++) {
              cubeEntity[i][j][k]->setEnabled(false);
            }
          }
        }
      }
    });

    QCheckBox *originCheckBox = new QCheckBox("Origin");
    originCheckBox->setChecked(true);
    connect(originCheckBox, &QCheckBox::stateChanged, [=](int state){
      if (state == Qt::Checked) {
        originEntity->setEnabled(true);
      } else {
        originEntity->setEnabled(false);
      }
    });
    QCheckBox *axisCheckBox = new QCheckBox("Axis");
    axisCheckBox->setChecked(true);
    connect(axisCheckBox, &QCheckBox::stateChanged, [=](int state){
      if (state == Qt::Checked) {
        cylinderXEntity->setEnabled(true);
        cylinderYEntity->setEnabled(true);
        cylinderZEntity->setEnabled(true);
        coneXEntity->setEnabled(true);
        coneYEntity->setEnabled(true);
        coneZEntity->setEnabled(true);
      } else {
        cylinderXEntity->setEnabled(false);
        cylinderYEntity->setEnabled(false);
        cylinderZEntity->setEnabled(false);
        coneXEntity->setEnabled(false);
        coneYEntity->setEnabled(false);
        coneZEntity->setEnabled(false);
      }
    });

    // QCheckBox *harborCheckBox = new QCheckBox("Harbor Boundary");
    // harborCheckBox->setChecked(true);
    // connect(harborCheckBox, &QCheckBox::stateChanged, [=](int state){
    //   if (state == Qt::Checked) {
    //     harborEntity->setEnabled(true);
    //   } else {
    //     harborEntity->setEnabled(false);
    //   }
    // });
    // QCheckBox *reservoirCheckBox = new QCheckBox("Reservoir Boundary");
    // reservoirCheckBox->setChecked(true);
    // connect(reservoirCheckBox, &QCheckBox::stateChanged, [=](int state){
    //   if (state == Qt::Checked) {
    //     reservoirEntity->setEnabled(true);
    //   } else {
    //     reservoirEntity->setEnabled(false);
    //   }
    // });
    // QCheckBox *floorCheckBox = new QCheckBox("Floor Boundary");
    // floorCheckBox->setChecked(true);
    // connect(floorCheckBox, &QCheckBox::stateChanged, [=](int state){
    //   if (state == Qt::Checked) {
    //     floorEntity->setEnabled(true);
    //   } else {
    //     floorEntity->setEnabled(false);
    //   }
    // });
    
    // Place check boxes in a group box layout with name "Toggle Visibility" in 3 columns

    // QGroupBox *checkBoxLayout = new QGroupBox("Toggle Visibility");
    // QGridLayout *checkBoxLayout = new QGridLayout();
    // checkBoxLayout->addWidget(twinCheckBox,   0, 0);
    // checkBoxLayout->addWidget(fluidCheckBox,  0, 1);
    // checkBoxLayout->addWidget(paddleCheckBox, 0, 2);
    // checkBoxLayout->addWidget(cubeCheckBox,   1, 0);
    // checkBoxLayout->addWidget(debrisCheckBox, 1, 1);
    // checkBoxLayout->addWidget(sensorCheckBox, 1, 2);
    // checkBoxLayout->addWidget(harborCheckBox, 2, 0);
    // checkBoxLayout->addWidget(reservoirCheckBox, 2, 1);
    // checkBoxLayout->addWidget(floorCheckBox, 2, 2);
    // checkBoxLayout->setLayout(checkBoxLayout);

    QGroupBox *checkBoxGroup = new QGroupBox("Visibility Options");
    QGridLayout *checkBoxLayout = new QGridLayout();
    checkBoxGroup->setLayout(checkBoxLayout);
    
    
    
    // Add a push button that will redraw the bodies
    QPushButton *updateBodiesButton = new QPushButton("Redraw Bodies");
    connect(updateBodiesButton, &QPushButton::clicked, [=](void){
      updateDigitalTwin(stackedWidget->currentIndex());
      updateFluid();
      updateDebris();
      updateSensors();
    });

    checkBoxLayout->addWidget(updateBodiesButton, 0, 0, 1, 4);
    checkBoxLayout->addWidget(originCheckBox, 1, 0);
    checkBoxLayout->addWidget(twinCheckBox,   1, 1);
    checkBoxLayout->addWidget(fluidCheckBox,  1, 2);
    checkBoxLayout->addWidget(paddleCheckBox, 1, 3);
    checkBoxLayout->addWidget(axisCheckBox,   2, 0);
    checkBoxLayout->addWidget(cubeCheckBox,   2, 1);
    checkBoxLayout->addWidget(debrisCheckBox, 2, 2);
    checkBoxLayout->addWidget(sensorCheckBox, 2, 3);

    // TODO: Refactor so that we just pass a reference to a container/rootEntity to each of the classes/subclasses. Using widget getters is tedious
    // Could template this to avoid repeating code
    connect(mpmBoundaries->getDimensionXWidget(mpmBoundaries->getStructureBoundary()), &QLineEdit::textChanged, [=](QString text){
      updateBoundaryStructurePosition();
      updateBoundaryStructureSize();
    });
    connect(mpmBoundaries->getDimensionYWidget(mpmBoundaries->getStructureBoundary()), &QLineEdit::textChanged, [=](QString text){
      updateBoundaryStructurePosition();
      updateBoundaryStructureSize();
    });

    connect(mpmBoundaries->getDimensionZWidget(mpmBoundaries->getStructureBoundary()), &QLineEdit::textChanged, [=](QString text){
      updateBoundaryStructurePosition();
      updateBoundaryStructureSize();
    });

    connect(mpmBoundaries->getOriginXWidget(mpmBoundaries->getStructureBoundary()), &QLineEdit::textChanged, [=](QString text){
      updateBoundaryStructurePosition();
      updateBoundaryStructureSize();
    });

    connect(mpmBoundaries->getOriginYWidget(mpmBoundaries->getStructureBoundary()), &QLineEdit::textChanged, [=](QString text){
      updateBoundaryStructurePosition();
      updateBoundaryStructureSize();
    });

    connect(mpmBoundaries->getOriginZWidget(mpmBoundaries->getStructureBoundary()), &QLineEdit::textChanged, [=](QString text){
      updateBoundaryStructurePosition();
      updateBoundaryStructureSize();
    });

    connect(mpmBoundaries->getArrayXWidget(mpmBoundaries->getStructureBoundary()), &QLineEdit::textChanged, [=](QString text){
      updateBoundaryStructureArray(); 
    });

    connect(mpmBoundaries->getArrayYWidget(mpmBoundaries->getStructureBoundary()), &QLineEdit::textChanged, [=](QString text){
      updateBoundaryStructureArray();
    });

    connect(mpmBoundaries->getArrayZWidget(mpmBoundaries->getStructureBoundary()), &QLineEdit::textChanged, [=](QString text){
      updateBoundaryStructureArray();
    });

    connect(mpmBoundaries->getSpacingXWidget(mpmBoundaries->getStructureBoundary()), &QLineEdit::textChanged, [=](QString text){
      updateBoundaryStructureSpacing();
    });

    connect(mpmBoundaries->getSpacingYWidget(mpmBoundaries->getStructureBoundary()), &QLineEdit::textChanged, [=](QString text){
      updateBoundaryStructureSpacing();
    });

    connect(mpmBoundaries->getSpacingZWidget(mpmBoundaries->getStructureBoundary()), &QLineEdit::textChanged, [=](QString text){
      updateBoundaryStructureSpacing();
    });

    // Paddle
    connect(mpmBoundaries->getDimensionXWidget(mpmBoundaries->getPaddleBoundary()), &QLineEdit::textChanged, [=](QString text){
      updateBoundaryPaddlePosition();
      updateBoundaryPaddleSize();
    });
    connect(mpmBoundaries->getDimensionYWidget(mpmBoundaries->getPaddleBoundary()), &QLineEdit::textChanged, [=](QString text){
      updateBoundaryPaddlePosition();
      updateBoundaryPaddleSize();
    });

    connect(mpmBoundaries->getDimensionZWidget(mpmBoundaries->getPaddleBoundary()), &QLineEdit::textChanged, [=](QString text){
      updateBoundaryPaddlePosition();
      updateBoundaryPaddleSize();
    });

    connect(mpmBoundaries->getOriginXWidget(mpmBoundaries->getPaddleBoundary()), &QLineEdit::textChanged, [=](QString text){
      updateBoundaryPaddlePosition();
      updateBoundaryPaddleSize();
    });

    connect(mpmBoundaries->getOriginYWidget(mpmBoundaries->getPaddleBoundary()), &QLineEdit::textChanged, [=](QString text){
      updateBoundaryPaddlePosition();
      updateBoundaryPaddleSize();
    });

    connect(mpmBoundaries->getOriginZWidget(mpmBoundaries->getPaddleBoundary()), &QLineEdit::textChanged, [=](QString text){
      updateBoundaryPaddlePosition();
      updateBoundaryPaddleSize();
    });



    // mainLayout->addWidget(updateBodiesButton, 3, 0);    
    mainLayout->addWidget(checkBoxGroup, 3, 0);

#endif

    mainLayout->addWidget(theTabWidget, 4, 0);
    mainGroup->setLayout(mainLayout);
    mainGroup->setMinimumWidth(windowWidthMin);
    mainGroup->setMaximumWidth(windowWidth);

    
    QScrollArea *theScrollArea = new QScrollArea();
    theScrollArea->setWidget(mainGroup);
    theScrollArea->setWidgetResizable(true);
    theScrollArea->setLineWidth(1);
    theScrollArea->setFrameShape(QFrame::NoFrame);
    theScrollArea->setMinimumWidth(windowWidthMin + 25);
    theScrollArea->setMaximumWidth(windowWidth + 25);


    // Add digital twin + scene builder on left. Add 3D visualizer on right
    QHBoxLayout *horizontalPanelLayout = new QHBoxLayout();
    QWidget *horizontalPanels = new QWidget();
    horizontalPanels->setLayout(horizontalPanelLayout);
    horizontalPanelLayout->addWidget(theScrollArea);

    // horizontalPanelLayout->addWidget(visualizationGroup);
// #ifdef _WIN32
#if ( ( defined(_WIN32) || defined(__linux__) || defined(linux) || defined(WIN32) ) && !defined(__APPLE__) ) && !defined(NO_MPM_QT3D)
    horizontalPanelLayout->addWidget(container);
#endif
    // QVBoxLayout *layout = new QVBoxLayout();
    // mainWindowLayout->addWidget(theScrollArea);
    // mainWindowLayout->addWidget(updateBodiesButton);
    // mainWindowLayout->addWidget(container);
    // mainWindowLayout->addWidget(horizontalPanels);
    // this->setLayout(mainWindowLayout);

    connect(stackedWidget, &SlidingStackedWidget::animationFinished, [=](void) {
      int index = stackedWidget->currentIndex();
      mpmBodies->setDigitalTwin(index);
      mpmBoundaries->setDigitalTwin(index);
// #ifdef _WIN32
#if ( ( defined(_WIN32) || defined(__linux__) || defined(linux) || defined(WIN32) ) && !defined(__APPLE__) ) && !defined(NO_MPM_QT3D)
      updateDigitalTwin(index);
#endif
    });
    

  connect(prev,&QAbstractButton::clicked,[this, stackedWidget, prev, next]{
      if(stackedWidget->slideInPrev()){
          prev->setEnabled(false);
          next->setEnabled(false);
      }
  });
  connect(next,&QAbstractButton::clicked,[this, stackedWidget, prev, next]{
      if(stackedWidget->slideInNext()){
          prev->setEnabled(false);
         next->setEnabled(false);
      }
  });
  connect(stackedWidget,&SlidingStackedWidget::animationFinished,[this, prev, next, &updateFluid, &updateDebris, &updateSensors]{
      prev->setEnabled(true);
      next->setEnabled(true);
#if ( ( defined(_WIN32) || defined(__linux__) || defined(linux) || defined(WIN32) ) && !defined(__APPLE__) ) && !defined(NO_MPM_QT3D)
      // updateDigitalTwin(stackedWidget->currentIndex());
      // updateFluid();
      // updateDebris();
      // updateSensors();
#endif
  });


    // QVBoxLayout *layout = new QVBoxLayout();
    // mainWindowLayout->addWidget(theScrollArea);
    // mainWindowLayout->addWidget(updateBodiesButton);
    // mainWindowLayout->addWidget(container);
    mainWindowLayout->addWidget(horizontalPanels);
    this->setLayout(mainWindowLayout);

    updateDigitalTwin(stackedWidget->currentIndex());
#if ( ( defined(_WIN32) || defined(__linux__) || defined(linux) || defined(WIN32) ) && !defined(__APPLE__) ) && !defined(NO_MPM_QT3D)
    updateFluid();
    updateDebris();
    updateSensors();
#endif
}

MPM::~MPM()
{

}

void MPM::showVisualization(void)
{
#if ( ( defined(_WIN32) || defined(__linux__) || defined(linux) || defined(WIN32) ) && !defined(__APPLE__) ) && !defined(NO_MPM_QT3D)
    // container->show();
    view->show();
#endif
}

void MPM::hideVisualization(void)
{
#if ( ( defined(_WIN32) || defined(__linux__) || defined(linux) || defined(WIN32) ) && !defined(__APPLE__) ) && !defined(NO_MPM_QT3D)
    // container->hide();
    view->hide();
#endif
}

bool MPM::isInitialize()
{
    return caseInitialized;
}

constexpr bool USE_RESULTS_WIDGET = true;
bool MPM::initialize()
{
    const int windowWidth = 850;
    // mainWindowLayout = new QHBoxLayout();

    // ---------------------------------------------------
    hideVisualization();
    // ---------------------------------------------------

    QString currentAppDir = QCoreApplication::applicationDirPath();

    caseDirectoryGroup = new QGroupBox("Case Directory");
    caseDirectoryLayout = new QGridLayout();
    caseDirectoryPathWidget = new QLineEdit();


    // QDir workingDir(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
    // if (!workingDir.exists()) 
    // {
    //   workingDir.mkpath(".");
    // }
    // QString workingDirPath = workingDir.filePath(QCoreApplication::applicationName() + QDir::separator()
    //                                              + "LocalWorkDir" + QDir::separator()
    //                                              + "MPM");

    auto prefs = SimCenterPreferences::getInstance();
    QString remoteWorkDirectoryString = prefs->getRemoteWorkDir();
    QDir remoteWorkDir(remoteWorkDirectoryString);
    if (!remoteWorkDir.exists()) {
        remoteWorkDir.mkpath(".");
    }

    QString tmpDirName = "tmp.SimCenter";
    remoteWorkDir.mkdir(tmpDirName);
    QDir tmpDir = QDir(remoteWorkDir.absoluteFilePath(tmpDirName));
    if (!tmpDir.exists()) {
        tmpDir.mkpath(".");
    }

    QString subDirName = ""; // "tmp.SimCenter"; "templatedir";
    remoteWorkDir.mkdir(subDirName);
    workingDirPath = remoteWorkDir.absoluteFilePath(subDirName);

    QDir workingDir = QDir(workingDirPath);
    if (!workingDir.exists()) {
        workingDir.mkpath(workingDirPath);
    }

    QLabel *casePathLabel = new QLabel("Path: ");
    caseDirectoryPathWidget->setText(workingDirPath);

    QPushButton* browseCaseDirectoryButton  = new QPushButton("Browse");
    caseDirectoryLayout->addWidget(casePathLabel, 0, 0);
    caseDirectoryLayout->addWidget(caseDirectoryPathWidget, 0, 1);
    caseDirectoryLayout->addWidget(browseCaseDirectoryButton, 0, 2);

    // QLabel *citeLabel = new QLabel("This event uses ClaymoreUW Multi-GPU MPM (Bonus 2023). Based on Claymore (Wang et al. 2020)");
    // QFont citeFont("Arial", 8);
    // citeFont.setPointSize(7);
    // citeFont.setItalic(true);
    // citeLabel->setFont(citeFont);

    caseDirectoryGroup->setLayout(caseDirectoryLayout);
    // caseDirectoryGroup->setMaximumWidth(200); // small test
    const int citeRow = 0;
    // mainLayout->addWidget(citeLabel, citeRow, 0);
    mainLayout->addWidget(caseDirectoryGroup, citeRow, 0);
    mainLayout->setRowStretch(0, 5);


    //Populate each tab
    // auto layout = this.layout();
    // layout->addWidget(caseDirectoryGroup);
    // layout->addWidget(citeLabel);
    // layout->addStretch();
    
    // mainWindowLayout->addWidget(caseDirectoryGroup); // Before ?
    connect(browseCaseDirectoryButton, SIGNAL(clicked()), this, SLOT(onBrowseCaseDirectoryButtonClicked()));



    // mainWindowLayout->addWidget(caseDirectoryGroup);
    // mainWindowLayout->addWidget(citeLabel);
    // mainWindowLayout->addStretch();

    // connect(browseCaseDirectoryButton, SIGNAL(clicked()), this, SLOT(onBrowseCaseDirectoryButtonClicked()));
    //=====================================================
    // Setup the case directory
    //=====================================================

    if(!isCaseConfigured())
    {
        setupCase(); // Check if directories for the case files exist, if not create them
    }

    // readCaseData(); // Read the case data from the JSON file

    caseInitialized = true;
    // ==================== Results-View Set-Up ====================
    if constexpr (USE_RESULTS_WIDGET) {
      QWidget* resultsWidget = new QWidget();
      QVBoxLayout* resultsLayout  = new QVBoxLayout();
      resultsWidget->setLayout(resultsLayout);
      mpmResults = new ResultsMPM(this); // this 
      resultsLayout->addWidget(mpmResults);
      resultsLayout->addStretch();
      theTabWidget->addTab(resultsWidget, QIcon(QString(":/icons/flag-black.svg")), "Results");   
    }

    // Update the GI Tab once the data is read
    GeneralInformationWidget *theGI = GeneralInformationWidget::getInstance();
    // theGI->setLengthUnit("m");
    // theGI->setForceUnit("N");
    // theGI->setTemperatureUnit("C");
    // theGI->setNumStoriesAndHeight(numberOfFloors(), buildingHeight());
    // theGI->setBuildingDimensions(buildingWidth(), buildingDepth(), buildingWidth()*buildingDepth());

    this->adjustSize();

    this->showVisualization();

    return true;
}


void MPM::updateJSON()
{
    // Write most recent EVT state to JSON becase it is needed for pre-processing steps / mesh generation before the final simulation is run.
    // In future only one JSON file in tmp.SimCenter directory might be enough
    QString inputFileName = "MPM.json";
    QString inputFilePath = caseDir() + QDir::separator() + inputFileName;
    QString outputFilePath = caseDir() + QDir::separator() + inputFileName;

    QFile jsonFile(inputFilePath);
    if (!jsonFile.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "Cannot find the path: " << inputFilePath;
    }

    QJsonObject jsonObject;
    outputToJSON(jsonObject);

    QJsonDocument jsonDoc = QJsonDocument(jsonObject);
    jsonFile.write(jsonDoc.toJson());
    jsonFile.close();
    return;
}

void MPM::executeBackendScript()
{
    //
    //  Update JSON input file and then pass arguments to a python script. Runs script to prepare case directory.
    //  Python scripts hosted remotely by SimCenterBackendApplications/modules/createEVENT/*
    // 

    updateJSON(); 
    QString jsonFile = caseDir() + QDir::separator() + "MPM.json";
    QString scriptName = "MPM.py"; // "setup_case.py";
    QString scriptPath = pyScriptsPath() + QDir::separator() + scriptName; 
    QString outputFile = caseDir() + QDir::separator() + "EVENT.json";
    /*
    if (QFileInfo(outputFile).exists() == false) {
      // Create the empty EVENT.json file if it doesn't exist
      QFile file(outputFile);
      file.open(QIODevice::WriteOnly);
      file.close();
    }
    */
    if (QFileInfo(scriptPath).exists())
    {
      qDebug() << "Running script: " << scriptPath;
      QString program = SimCenterPreferences::getInstance()->getPython();
      qDebug() << "Program: " << program;
      QStringList arguments; arguments << scriptPath << "--filenameAIM" << jsonFile << "--filenameEVENT" << outputFile;
      qDebug() << "Arguments: " << jsonFile << " " << outputFile;
      qDebug() << "MPM: Skipping running program with arguments for debug purposes.";
      /*
      QProcess *process = new QProcess(this);
      process->start(program, arguments);
      process->waitForFinished(-1);
      process->close();
      // process->deleteLater();
      */
    } 
    else 
    {
      qDebug() << "Cannot find the script path: " << scriptPath;
    }
    return;
}

void MPM::readCaseData()
{
    QString inputFileName = "MPM.json";
    QString inputFilePath = caseDir() + QDir::separator() 
                            + inputFileName;
    QFile jsonFile(inputFilePath);
    if (!jsonFile.open(QFile::ReadOnly | QFile::Text))
    {
      qDebug() << "Cannot find/read input-file path: " << inputFilePath;
      return;
    }

    QString val = jsonFile.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = doc.object();
    this->inputFromJSON(jsonObject);
    jsonFile.close();
    removeOldFiles();
}

void MPM::onBrowseCaseDirectoryButtonClicked(void)
{
    QString fileName = QFileDialog::getExistingDirectory(this, tr("Open Directory"), caseDir(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    QDir newCaseDir(fileName);
    if (!newCaseDir.exists())
    {
       return;
    }
    caseDirectoryPathWidget->setText(fileName);

    if (!isCaseConfigured())
    {
        setupCase();
        return;
    }

    // Need to have scene config file (MPM.json) in the LocalWorkDir/MPM/inputData directory
    readCaseData();
    caseDirectoryPathWidget->setText(fileName);
    return;
}


bool MPM::outputCitation(QJsonObject &jsonObject)
{
    QJsonObject citeClaymore;
    QJsonObject citeClaymoreUW;
    QJsonObject citeValidationCE;
    citeClaymore["citation"] = "Wang, Xinlei and Qiu Yuxing, et al. (2020). “A massively parallel and scalable multi-GPU material point method.” ACM Transactions on Graphics (TOG), Volume 39, Issue 4. https://doi.org/10.1145/3386569.3392442";
    citeClaymore["description"] = "The Multi-GPU Material Point Method software, claymore, which is the predeccesor to ClaymoreUW MPM. It is a highly optimized C++/CUDA code for explicit MLS-MPM simulations on multiple NVIDIA GPUs. It is designed primarily for back-end computer graphics usage.";
    citeClaymoreUW["citation"] = "Bonus, Justin (2023). “Evaluation of Fluid-Driven Debris Impacts in a High-Performance Multi-GPU Material Point Method.” PhD thesis, University of Washington, Seattle, WA.";
    citeClaymoreUW["description"] = "The ClaymoreUW Multi-GPU Material Point Method software developed in this PhD thesis is the engineering refactor of the claymore MPM software. It is a highly optimized C++/CUDA code for explicit MLS-MPM simulations on multiple NVIDIA GPUs. It features higher computational precision, validated accuracy in multiple debris-fluid-structure interaction problems, new algorithms (ASFLIP, F-Bar antilocking), an expanded user-interface, and improved material behavior.";
    citeValidationCE["citation"] = "Justin Bonus, Felix Spröer, Andrew Winter, Pedro Arduino, Clemens Krautwald, Michael Motley, Nils Goseberg. (2024). Tsunami debris motion and loads in a scaled port setting: Comparative analysis of three state-of-the-art numerical methods against experiments. Coastal Engineering. Volume 197. https://doi.org/10.1016/j.coastaleng.2024.104672.";
    citeValidationCE["description"] = "Validates the HydroUQ Material Point Method module for tsunami debris motion and loads in a digital twin's scaled port setting. Compares against stochastic experiments, smoothed particle hydrodynamics (DualSPHysics), and the finite volume method (STAR-CCM+), with MPM proving particularly strong for debris studies.";
    jsonObject["claymore"] = citeClaymore;
    jsonObject["ClaymoreUW"] = citeClaymoreUW;
    jsonObject["Validation"] = citeValidationCE;
    return true;
}

void MPM::clear(void)
{
    this->hideVisualization();

    if (mpmSettings) {
      qDebug() << "MPM::clear: mpmSettings->clear() started";
      mpmSettings->clear();
      qDebug() << "MPM::clear: mpmSettings->clear() finished";
      // qDebug() << "MPM::clear: mpmSettings->clear() returned false";
    }
    if (mpmBodies) {
      qDebug() << "MPM::clear: mpmBodies->clear() started";
      mpmBodies->clear();
      qDebug() << "MPM::clear: mpmBodies->clear() finished";
      // qDebug() << "MPM::clear: mpmBodies->clear() returned false";
    }
    if (mpmBoundaries) {
      qDebug() << "MPM::clear: mpmBoundaries->clear() started";
      mpmBoundaries->clear();
      qDebug() << "MPM::clear: mpmBoundaries->clear() finished";
      // qDebug() << "MPM::clear: mpmBoundaries->clear() returned false";
    }
    if (mpmSensors) {
      qDebug() << "MPM::clear: mpmSensors->clear() started";
      mpmSensors->clear();
      qDebug() << "MPM::clear: mpmSensors->clear() finished";
      // qDebug() << "MPM::clear: mpmSensors->clear() returned false";
    }
    if (mpmOutputs) {
      qDebug() << "MPM::clear: mpmOutputs->clear() started";
      mpmOutputs->clear();
      qDebug() << "MPM::clear: mpmOutputs->clear() finished";
      // qDebug() << "MPM::clear: mpmOutputs->clear() returned false";
    }
}

bool MPM::inputFromJSON(QJsonObject &jsonObject)
{
  // return true;
  // Exiting early to debug

  this->clear();

  /*
  QString newCaseDirectoryPath(jsonObject["caseDirectoryPath"].toString());

  if (newCaseDirectoryPath.isEmpty()) {
    qDebug() << "MPM::inputFromJSON: newCaseDirectoryPath is empty in JSON input.";
    // return false;
  }

  QDir newCaseDir(newCaseDirectoryPath);
  if (!newCaseDir.exists()) {
    qDebug() << "MPM::inputFromJSON: newCaseDir does not exist in folder structure: " << newCaseDirectoryPath;
    // return false;
  }

  if (newCaseDirectoryPath != caseDirectoryPathWidget->text()) {
    caseDirectoryPathWidget->setText(newCaseDirectoryPath);
  }

  caseDirectoryPathWidget->setText(jsonObject["caseDirectoryPath"].toString());
  */

  // Read in the input JSON file
  // If its a worfklow file, ClaymoreUW MPM data will be nested in the "Events" array as an object
  // If its a standalone file, ClaymoreUW MPM data will be the root object
  QJsonArray eventsArray;
  QJsonObject eventObject;
  if (jsonObject.contains("Events")) {
    if (jsonObject["Events"].isArray()) {
      qDebug() << "MPM::inputFromJSON: jsonObject contains 'Events' array";
      if (jsonObject["Events"].toArray().size() > 0) {
        eventsArray = jsonObject["Events"].toArray();
        if (eventsArray[0].isObject()) {
          qDebug() << "MPM::inputFromJSON: use the first object in the 'Events' array as input JSON object";
          eventObject = eventsArray[0].toObject();
        }
      }
    }
  } else {
    qDebug() << "MPM::inputFromJSON: eventObject is the root jsonObject";
    eventObject = jsonObject;
  }

  // if (eventObject["facility"].isString()) {
  //   qDebug() << "MPM::inputFromJSON: eventObject contains 'facility' string";
  //   QString facility = eventObject["facility"].toString();
  //   if (facility == "OSU LWF") {
  //     qDebug() << "MPM::inputFromJSON: eventObject facility is OSU LWF";
  //     // stackedWidget->setCurrentIndex(0);
  //     // mpmBodies->setDigitalTwin(0);
  //     // mpmBoundaries->setDigitalTwin(0);
  //     // mpmBodies->setFluid(0);
  //     // mpmBoundaries->setFluid(0);
  //     // mpmBodies->setFluid(1);
  //     // mpmBoundaries->setFluid(1);

  //   } else if (facility == "OSU DWB") {
  //     qDebug() << "MPM::inputFromJSON: eventObject facility is not OSU DWB";
  //     stackedWidget->setCurrentIndex(1);
  //   } else if (facility == "UW WASIRF") {
  //     qDebug() << "MPM::inputFromJSON: eventObject facility is not UW WASIRF";
  //     stackedWidget->setCurrentIndex(2);
  //   } else if (facility == "WU TWB") {
  //     qDebug() << "MPM::inputFromJSON: eventObject facility is WU TWB";
  //     stackedWidget->setCurrentIndex(3);
  //   } else if (facility == "USGS DFF") {
  //     qDebug() << "MPM::inputFromJSON: eventObject facility is USGS DFF";
  //     stackedWidget->setCurrentIndex(4);
  //   } else {
  //     qDebug() << "MPM::inputFromJSON: eventObject facility is not present, do not change slider.";
  //   }
  // } else {
  //   qDebug() << "MPM::inputFromJSON: eventObject does not contain 'facility' string";
  // }

  if (mpmSettings) {
    qDebug() << "MPM::inputFromJSON: mpmSettings exists";
    if (mpmSettings->inputFromJSON(eventObject) == false) {
      qDebug() << "MPM::inputFromJSON: mpmSettings->inputFromJSON() returned false";
    } else {
      qDebug() << "MPM::inputFromJSON: mpmSettings->inputFromJSON() returned true";
    }
  }
  if (mpmBodies) {
    qDebug() << "MPM::inputFromJSON: mpmBodies exists";
    if (mpmBodies->inputFromJSON(eventObject) == false) {
      qDebug() << "MPM::inputFromJSON: mpmBodies->inputFromJSON() returned false";
    } else {
      qDebug() << "MPM::inputFromJSON: mpmBodies->inputFromJSON() returned true";
    }
  }
  if (mpmBoundaries) {
    qDebug() << "MPM::inputFromJSON: mpmBoundaries exists";
    if (mpmBoundaries->inputFromJSON(eventObject) == false) {
      qDebug() << "MPM::inputFromJSON: mpmBoundaries->inputFromJSON() returned false";
    } else {
      qDebug() << "MPM::inputFromJSON: mpmBoundaries->inputFromJSON() returned true";
    }
  }
  if (mpmSensors) {
    qDebug() << "MPM::inputFromJSON: mpmSensors exists";
    if (mpmSensors->inputFromJSON(eventObject) == false) {
      qDebug() << "MPM::inputFromJSON: mpmSensors->inputFromJSON() returned false";
    } else {
      qDebug() << "MPM::inputFromJSON: mpmSensors->inputFromJSON() returned true";
    }
  }
  if (mpmOutputs) {
    qDebug() << "MPM::inputFromJSON: mpmOutputs exists";
    if (mpmOutputs->inputFromJSON(eventObject) == false) {
      qDebug() << "MPM::inputFromJSON: mpmOutputs->inputFromJSON() returned false";
    } else {
      qDebug() << "MPM::inputFromJSON: mpmOutputs->inputFromJSON() returned true";
    }
  }
  if (mpmResults) {
    // mpmResults->inputFromJSON(jsonObject);
  }
  this->showVisualization();
  return true;
}

bool MPM::outputToJSON(QJsonObject &jsonObject)
{
  jsonObject["EventClassification"] = "Hydro"; // Important for workflow (Earthquake vs Wind vs Hydro, etc.)
  jsonObject["type"] = "MPM";

  jsonObject["Application"] = "MPM"; // For accessing SimCenterBackendApplications/applications/createEVENTS/{Application}/*.py ?
  jsonObject["subtype"] = "MPM";

  // Just so that when read back in inputFromJSON we can set the slider to the correct facility
  // if (stackedWidget->currentIndex() == 0) {
  //   jsonObject["facility"] = "OSU LWF"; // TODO: Add to the settings tab
  // } else if (stackedWidget->currentIndex() == 1) {
  //   jsonObject["facility"] = "OSU DWB"; // TODO: Add to the settings tab
  // } else if (stackedWidget->currentIndex() == 2) {
  //   jsonObject["facility"] = "UW WASIRF"; // TODO: Add to the settings tab
  // } else if (stackedWidget->currentIndex() == 3) {
  //   jsonObject["facility"] = "WU TWB"; // TODO: Add to the settings tab
  // } else if (stackedWidget->currentIndex() == 4) {
  //   jsonObject["facility"] = "USGS DFF"; // TODO: Add to the settings tab
  // } else {
  //   // jsonObject["facility"] = "Unknown Facility"; // TODO: Add to the settings tab
  // } 

  // The JSON object-or-array that defines each main tab (i.e. Settings, Bodies, Boundaries, Sensors, Outputs)
  QJsonObject settingsObject;  
  QJsonArray bodiesArray;
  QJsonArray boundariesArray;
  QJsonArray sensorsArray;
  QJsonObject outputsObject;
  constexpr bool USE_RESULTS_WIDGET_JSONOBJECT = true; // mostly pointless but for consistency
  if constexpr (USE_RESULTS_WIDGET_JSONOBJECT) {
    QJsonObject resultsObject;
  }
  // Pass in the objects or array object wrappers to the outputToJSON functions
  QJsonObject bodiesObjectWrapper;
  QJsonObject boundariesObjectWrapper;
  QJsonObject sensorsObjectWrapper;
  QJsonArray  bodiesArrayWrapper;
  QJsonArray  boundariesArrayWrapper;
  QJsonArray  sensorsArrayWrapper;

  // Some of the outputToJSON functions will add to the arrays in the wrappers
  // We pass in objects wrapping the arrays to avoid two outputToJSON functions per class (could also template)
  bodiesObjectWrapper["bodies"] = bodiesArrayWrapper;  
  boundariesObjectWrapper["boundaries"] = boundariesArrayWrapper;
  sensorsObjectWrapper["sensors"] = sensorsArrayWrapper;

  // Call the outputToJSON functions in the sub-widget classes (i.e. tabs)
  mpmSettings->outputToJSON(settingsObject);
  mpmBodies->outputToJSON(bodiesObjectWrapper);
  mpmBoundaries->outputToJSON(boundariesObjectWrapper);
  mpmSensors->outputToJSON(sensorsObjectWrapper);
  mpmOutputs->outputToJSON(outputsObject);
  // mpmResults->outputToJSON(resultsObject); // For now, just pass the jsonObject to the results tab. Does nothing

  // ==================== Settings ====================
  // Settings (simulation in ClaymoreUW currently)
  if (settingsObject.contains("simulation") && settingsObject["simulation"].isObject()) {
    // Read in the simulation object from the settings object
    jsonObject["simulation"] = settingsObject["simulation"];

    // Move some values from the outputs object to the simulation settings object
    QJsonObject my_sim = jsonObject["simulation"].toObject(); 
    if (outputsObject.contains("save_suffix") && outputsObject["save_suffix"].isString()) {
      if (outputsObject["save_suffix"].toString().isEmpty()) {
        my_sim["save_suffix"] = ".bgeo"; 
      } else {
        // Force lowercase and add a period if it is not the first character
        // If the string is only one character but it is a period, append "bgeo" to it (binary geometry file for Houdinie SideFX)
        if (outputsObject["save_suffix"].toString().at(0) != '.') 
          my_sim["save_suffix"] = "." + outputsObject["save_suffix"].toString(); 

        if (outputsObject["save_suffix"].toString().length() > 1) {
          my_sim["save_suffix"] = my_sim["save_suffix"].toString().left(1) + my_sim["save_suffix"].toString().mid(1).toLower();
        } else {
          my_sim["save_suffix"] = my_sim["save_suffix"].toString().left(1) + "bgeo";
        }
      } 
    }
    if (outputsObject.contains("fps") && outputsObject["fps"].isDouble()) {
      my_sim["fps"] = outputsObject["fps"].toDouble(); // for ClaymoreUW, simulation:fps = outputs:outputBodies_Dt
    }
    if (outputsObject.contains("particles_output_exterior_only") && outputsObject["particles_output_exterior_only"].isBool()) {
      my_sim["particles_output_exterior_only"] = outputsObject["particles_output_exterior_only"].toBool(); // for ClaymoreUW, simulation:particles_output_exterior_only = outputs:bodies_OutputExteriorOnly
    }
    // To be an output option, not a simulation option
    if ((my_sim.contains("duration") && my_sim["duration"].isDouble()) && (my_sim.contains("fps") && my_sim["fps"].isDouble())) {
      my_sim["frames"] = my_sim["duration"].toDouble() * my_sim["fps"].toDouble(); // for ClaymoreUW, simulation:frames = simulation:duration * simulation:fps
    } else {
      my_sim["frames"] = my_sim["fps"]; // Assumes 1 second total simulation as a fallback
    }
    jsonObject["simulation"] = my_sim;
  }
  // Computer, as in hardware and how it is compiled for by application if relevant (e.g. number of GPUs)
  if (settingsObject.contains("computer") && settingsObject["computer"].isObject()) {
    jsonObject["computer"] = settingsObject["computer"];
  }
  // Similitude scaling
  if (settingsObject.contains("scaling") && settingsObject["scaling"].isObject()) {
    jsonObject["scaling"] = settingsObject["scaling"]; 
  }

  // ==================== Bodies ====================
  // Bodies (models in ClaymoreUW currently)
  if (bodiesObjectWrapper.contains("bodies") && bodiesObjectWrapper["bodies"].toArray().size() > 0) {
    bodiesArray = bodiesObjectWrapper["bodies"].toArray();
    int numBodies = bodiesArray.size();
    
    // Assign each body an output_attribs array (array of strings that define what attributes to output each frame per particle)
    QJsonArray outputAttribsArray = outputsObject["outputs"].toObject()["output_attribs"].toArray(); // for ClaymoreUW, outputs:numOutputBodies = bodies:numBodies
    int numOutputAttribs = outputAttribsArray.size(); // Number of output attrib arrays (one per body)
    for (int i = 0; i < numBodies; i++) {
      // If the body ID exceeds rows of outputAttrisbArray (one-per-body), just have body output IDs of particles
      // Else If there are no output attribs for a valid outputAttribsArray row's body, tell the body to output IDs of particles
      if (i < numOutputAttribs) {
        if (outputAttribsArray[i].toArray().size() == 0) 
          outputAttribsArray[i] = QJsonArray::fromStringList(QStringList() << "ID");
      } else if (i >= numOutputAttribs) {
        outputAttribsArray.append(QJsonArray::fromStringList(QStringList() << "ID"));
        numOutputAttribs++;
      } 
      QJsonObject body = bodiesArray[i].toObject();
      QJsonArray bodyAttribsArray = outputAttribsArray[i].toArray();
      body["output_attribs"] = bodyAttribsArray;
      bodiesArray[i] = body;
    }

    // Unravel partition array per body into additional bodies (maybe move this into ClaymoreUW itself)
    for (int i = 0; i < numBodies; i++) {
      QJsonObject body = bodiesArray[i].toObject();
      QJsonArray partitionArray = body["partition"].toArray();
      int numPartitions = partitionArray.size();
      for (int j = 0; j < numPartitions; j++) {
        QJsonObject newBody = body;
        QJsonObject partition = partitionArray[j].toObject();
        newBody["gpu"] = partition["gpu"]; 
        newBody["model"] = partition["model"]; // TODO: Update schema to body maybe
        newBody["partition_start"] = partition["partition_start"]; // TODO: Update schema to body maybe
        newBody["partition_end"] = partition["partition_end"]; // TODO: Update schema to body maybe
        if (j == 0) {
          bodiesArray[i] = newBody;
          continue;
        }
        bodiesArray.append(newBody); // TODO: Insert instead of append
      }

      // Check that "gpu" and "model" are not both identical to another body's partition's "gpu" and "model"
      // If they are, try to increment the "gpu" and "model" of the new body until it is unique, 
      // remaining within "computer" object's "numGPUs" and "modelsPerGPU" values
      // If it is not possible to increment the "gpu" and "model" to a unique value, remove the new body
      // If it is possible to increment the "gpu" and "model" to a unique value, update the new body's "gpu" and "model"
      // for (int j = numBodies; j < bodiesArray.size(); j++) {
      // ---- Debug soon
      // for (int j = 0; j < bodiesArray.size(); j++) {
      //   if (j >= bodiesArray.size()) break;
      //   QJsonObject newBody = bodiesArray[j].toObject();
      //   for (int k = 0; k < j; k++) {
      //     QJsonObject existingBody = bodiesArray[k].toObject();
      //     if (newBody["gpu"].toInt() == existingBody["gpu"].toInt() && newBody["model"].toInt() == existingBody["model"].toInt()) {
      //       int numGPUs = jsonObject["computer"].toObject()["numGPUs"].toInt();
      //       int modelsPerGPU = jsonObject["computer"].toObject()["modelsPerGPU"].toInt();
      //       int newGPU = newBody["gpu"].toInt();
      //       int newModel = newBody["model"].toInt();
      //       bool unique = false;
      //       while (!unique) {
      //         if (j >= bodiesArray.size()) break;

      //         if (newGPU < numGPUs && newModel < modelsPerGPU) {
      //           newModel++;
      //           unique = true;
      //           for (int l = 0; l < j; l++) {
      //             QJsonObject existingBody = bodiesArray[l].toObject();
      //             if (newGPU == existingBody["gpu"].toInt() && newModel == existingBody["model"].toInt()) {
      //               unique = false;
      //               // break;
      //             }
      //           }
      //         } 
              
      //         if (newGPU < numGPUs && newModel < modelsPerGPU) {
      //           newModel++;
      //           unique = true;
      //           for (int l = 0; l < j; l++) {
      //             QJsonObject existingBody = bodiesArray[l].toObject();
      //             if (newGPU == existingBody["gpu"].toInt() && newModel == existingBody["model"].toInt()) {
      //               unique = false;
      //               // break;
      //             }
      //           }
      //         } 
              

      //         // if (newGPU < numGPUs && newModel == modelsPerGPU) {
      //         //   newGPU++;
      //         //   newModel = 0;
      //         //   unique = true;
      //         //   for (int l = 0; l < j; l++) {
      //         //     QJsonObject existingBody = bodiesArray[l].toObject();
      //         //     if (newGPU == existingBody["gpu"].toInt() && newModel == existingBody["model"].toInt()) {
      //         //       unique = false;
      //         //     }
      //         //   }
      //         // }

      //       }
      //       if (!unique) {
      //         // Remove the new body if it is not possible to increment the "gpu" and "model" to a unique value
      //         // Also remove if we exceed the number of GPUs and models per GPU specified in "computer"
      //         // if (!unique) {
      //           bodiesArray.removeAt(j);
      //           // if (j > 0) {
      //           //   j = j - 1;
      //           // }
      //           break;
      //         // }
      //       }
      //       // if (!unique) {}
      //       newBody["gpu"] = newGPU;
      //       newBody["model"] = newModel;
      //       bodiesArray[j] = newBody;
      //     }
      //   }
      // }
      // ---- Debug soon
    }
    jsonObject["bodies"] = bodiesArray; // Add the bodies array to the jsonObject
  }

  // ==================== Boundaries ====================
  // Boundaries (grid-boundaries in ClaymoreUW currently, TODO: Deprecate and change to "boundaries")
  if (boundariesObjectWrapper.contains("boundaries") && boundariesObjectWrapper["boundaries"].isArray()) {
    jsonObject["boundaries"] = boundariesObjectWrapper["boundaries"]; // boundaries is an array of objects, each is an individual boundary
  }

  // ==================== Sensors ====================
  // Sensors (grid-targets, particle-targets in ClaymoreUW currently, TODO: Deprecate and change to "sensors")
  // sensors is an array of objects, each is an individual sensor
  if (sensorsObjectWrapper.contains("particle-sensors") && sensorsObjectWrapper["particle-sensors"].isArray()) 
    jsonObject["particle-sensors"] = sensorsObjectWrapper["particle-sensors"];
  if (sensorsObjectWrapper.contains("grid-sensors") && sensorsObjectWrapper["grid-sensors"].isArray()) 
    jsonObject["grid-sensors"] = sensorsObjectWrapper["grid-sensors"];

  // ==================== Outputs ====================
  // Outputs (not a separate object in ClaymoreUW currently, must move some fields to other objects manually for ClaymoreUW)
  if (outputsObject.contains("outputs") && outputsObject["outputs"].isObject()) {
    jsonObject["outputs"] = outputsObject["outputs"]; // for future schema, not used in ClaymoreUW currently
  }

  return true;
}

bool MPM::outputAppDataToJSON(QJsonObject &jsonObject) {

    //
    // Per API, need to add name of application to be called in Application
    // and all data to be used in ApplicationData
    //

    jsonObject["EventClassification"] = "Hydro";
    jsonObject["Application"] = "MPM";
    // jsonObject["type"] = "MPM"; // Application and type used interchangeably in our openfoam Tapisv3 app

    // Env Variable for ClaymoreUW MPM as a Tool in Tapis V3
    jsonObject["programFile"] = "osu_lwf"; // <- ClaymoreUW MPM executable filename on remote machine. Can be changed depending on compiled optimizations, versions, digital twin, etc.
    jsonObject["maxRunTime"] = "120"; // <- Maximum run time for the simulation, timeout if exceeded
    jsonObject["defaultMaxRunTime"] = "1440";
    jsonObject["publicDirectory"] = "./"; // "../mpm-public-ls6"
    jsonObject["inputFile"] = "scInput.json"; // <- Input file for the simulation
    jsonObject["driverFile"] = "sc_driver"; // <- Python script to run the simulation

    // QJsonArray fileInputsArray;
    // QJsonObject fileInputsObj;
    // fileInputsObj["envKey"] = "dataDirectory"; // <- Environment variable to be set on the remote machine
    // fileInputsObj["sourceUrl"] = "tapis://designsafe.storage.default/bonusj/mpm-public-ls6"; // <- Directory where the input files are located
    // fileInputsObj["targetPath"] = "*"; // <- Copy all files in the sourceUrl to the targetPath
    // fileInputsArray.append(fileInputsObj);
    // jsonObject["fileInputs"] = fileInputsArray;

    QJsonObject dataObj;
    jsonObject["ApplicationData"] = dataObj;
    return true;
}
bool MPM::inputAppDataFromJSON(QJsonObject &jsonObject) {

    Q_UNUSED(jsonObject);
    return true;
}


bool MPM::copyFiles(QString &destDir) {
    qDebug() << "MPM - copying files";
    qDebug() << "MPM - destDir: " << destDir;
    //
    //  Copy the files in the case directory to the destination directory
    //  This is the directory where the simulations will be run / staged
    //  Should pull together any files needed for the simulation, e.g. specified input files
    //

    /*
    executeBackendScript();
    QString caseName = "MPM";
    QString destDirCase = destDir + QDir::separator() + caseName;
    QDir destDirCaseDir(destDirCase);
    if (!destDirCaseDir.exists()) 
    {
        destDirCaseDir.mkpath("."); // Make the directory if it doesn't exist
    }


    bool result = this->copyPath(caseDir(), destDirCase, false); // False means don't copy the directory itself, just the contents
    if (!result) 
    {
        QString errorMessage; errorMessage = "MPM - failed to copy case files in: " + caseDir() + " to: " + destDirCase;
        fatalMessage(errorMessage);
        qDebug() << errorMessage;
        // return false;
    }
    */

    //
    //  Copy files from all the major sub-widgets
    //

    // if (mpmSettings->copyFiles(destDir) == false) 
    // {
    //   qDebug() << "MPM - failed to copy mpmSettings files";
    //   // return false;
    // }
    if (mpmBodies->copyFiles(destDir) == false)
    {
      qDebug() << "MPM - failed to copy mpmBodies files to: " << destDir;
      // return false;
    } else {
      qDebug() << "MPM - copied mpmBodies files to: " << destDir;
    }
    if (mpmBoundaries->copyFiles(destDir) == false)
    {
      qDebug() << "MPM - failed to copy mpmBoundaries files to: " << destDir;
      // return false;
    } else {
      qDebug() << "MPM - copied mpmBoundaries files to: " << destDir;
    }
    // if (mpmSensors->copyFiles(destDir) == false)
    // {
    //   qDebug() << "MPM - failed to copy mpmSensors files";
    //   // return false;
    // }
    // if (mpmOutputs->copyFiles(destDir) == false)
    // {
    //   qDebug() << "MPM - failed to copy mpmOutputs files";
    //   // return false;
    // }
    // if (mpmResults->copyFiles(destDir) == false)
    // {
    //   qDebug() << "MPM - failed to copy mpmResults files";
    //   // return false;
    // }

    return true;
 }


bool MPM::cleanCase()
{
    // 
    //  Remove the primary folders and log file within the case directory recursively
    // 

    // QDir zeroDir(caseDir() + QDir::separator() + "0");
    // QDir constDir(caseDir() + QDir::separator() + "constant");
    // QDir systemDir(caseDir() + QDir::separator() + "system");
    QString templatedirName = QString("templatedir");
    QString templatedirString = caseDir() + QDir::separator() + templatedirName;
    QDir templatedir(templatedirString);
    QDir inputFiles(caseDir() + QDir::separator() + "inputData");
    // zeroDir.removeRecursively();
    // constDir.removeRecursively();
    // systemDir.removeRecursively();
    if (templatedir.exists()) {
      if (SCUtils::isSafeToRemoveRecursivily(templatedir.path())) {
        templatedir.removeRecursively();
      }
    }
    if (inputFiles.exists()) {
      if (SCUtils::isSafeToRemoveRecursivily(inputFiles.path())) {
        inputFiles.removeRecursively();
      }
    }
    // templatedir.removeRecursively();
    // inputFiles.removeRecursively();
    QFile logFile(caseDir() + QDir::separator() + "log.txt");
    if (logFile.exists()) {
      logFile.remove();
    }
    return true;
}

bool MPM::removeOldFiles()
{
    //
    // Remove extra files if they exist in case directory's "0" folder
    //
    
    // auto removeFile = [this](QString filePath) {
    //     QFile file(caseDir() + QDir::separator() + "0" + QDir::separator() + filePath);
    //     if (file.exists()) { 
    //         qDebug() << "Removing old file: " << filePath;
    //         file.remove();
    //     }
    // };
    // removeFile(caseDir() + QDir::separator() + "0" + QDir::separator() + "oldFile");
    return true;
}

bool MPM::setupCase()
{
    cleanCase();
    QDir targetDir(caseDir());
    if (!targetDir.exists())
    {
        targetDir.mkpath(caseDir());
    }

    // targetDir.mkpath("0");
    // targetDir.mkpath("constant");
    // targetDir.mkpath("constant/geometry");
    // targetDir.mkpath("constant/simCenter");
    // targetDir.mkpath("constant/simCenter/output");
    // targetDir.mkpath("constant/simCenter/input");
    // targetDir.mkpath("constant/boundaryData");
    // targetDir.mkpath("constant/boundaryData/inlet");
    // targetDir.mkpath("system");

    targetDir.mkpath("inputData");
    targetDir.mkpath("templatedir");


    // Write setup files using the backend python script
    executeBackendScript();
    return true;
}

// // From WE-UQ EmptyDomainCFD
// QVector<QVector<double>> MPM::readTxtData(QString fileName)
// {
//     int colCount  = 0;
//     QVector<QVector<double>>  data;
//     QFile inputFileTest(fileName);
//     if (inputFileTest.open(QIODevice::ReadOnly))
//     {
//        QTextStream in(&inputFileTest);

//        while (!in.atEnd())
//        {
//             QString line = in.readLine();
//             QStringList  fields = line.split(" ");
//             colCount  = fields.size();
//             break;
//        }
//        inputFileTest.close();
//     }

//     for (int i=0; i < colCount; i++)
//     {
//         QVector<double> row;
//         data.append(row);
//     }

//     int count  = 0;
//     QFile inputFile(fileName);
//     if (inputFile.open(QIODevice::ReadOnly))
//     {
//        QTextStream in(&inputFile);
//        while (!in.atEnd())
//        {
//             QString line = in.readLine();
//             QStringList  fields = line.split(" ");
//             for (int i=0; i < colCount; i++)
//             {
//                 data[i].append(fields[i].toDouble());
//             }
//        }
//        inputFile.close();
//     }

//     return data;
// }

bool MPM::isCaseConfigured()
{
    // QDir tempDir = QDir(caseDir() + QDir::separator() + "templatedir" + QDir::separator() + "simCenter" + QDir::separator() + "input");
    QDir tempDir(caseDir() + QDir::separator() +  "templatedir");
    QDir inputDir(caseDir() + QDir::separator() + "inputData");
    // QDir zeroDir(caseDir() + QDir::separator() + "0");
    // QDir constDir(caseDir() + QDir::separator() + "constant");
    // QDir systemDir(caseDir() + QDir::separator() + "system");
    // QFile contrlDict(caseDir() + QDir::separator() + "system" + QDir::separator() + "controlDict");
    // QFile blockDict(caseDir() + QDir::separator() + "system" +  QDir::separator() + "blockMeshDict");
    // QFile snappyDict(caseDir() + QDir::separator() + "system" + QDir::separator() + "snappyHexMeshDict");

    // //Better if we check other files too, for now these are enougg to run a mesh
    // return zeroDir.exists() && constDir.exists() && systemDir.exists() &&
    //        contrlDict.exists() && blockDict.exists() && snappyDict.exists();
    return tempDir.exists() && inputDir.exists();
}

QString MPM::caseDir()
{
    return caseDirectoryPathWidget->text();
}

QString MPM::pyScriptsPath()
{
    QString backendAppDir = SimCenterPreferences::getInstance()->getAppDir() + QDir::separator()
             + QString("applications") + QDir::separator() + QString("createEVENT") + QDir::separator()
             + QString("MPM");
    return backendAppDir;
}

// // Probably not needed for anything but OpenFOAM
// QString MPM::templateDictDir()
// {
//     QString templateSubFolder = QString("templateOF10Dicts");// "templateMPMDicts";
//     QString templateDictsDir = SimCenterPreferences::getInstance()->getAppDir() + QDir::separator()
//                                 + QString("applications") + QDir::separator() 
//                                 + QString("createEVENT") + QDir::separator()
//                                 + QString("MPM") + QDir::separator() 
//                                 + templateSubFolder;
//     return templateDictsDir;
// }

QString MPM::simulationType()
{
    return QString("MPM");
}

#ifdef USE_MPM_RESULTS_WIDGET_FUNCTIONS
SC_ResultsWidget* MPM::getResultsWidget(QWidget *parent)
{
  // theTabWidget.setCurrentIndex(theTabWidget.indexOf("Results"));
  // Set theTabWidget to show the "Results" tab using its text
  if (mpmResults)
  {
    theTabWidget->setCurrentIndex(theTabWidget->count() - 1);
  }
  else 
  {
    if constexpr (USE_RESULTS_WIDGET) {
      QWidget* resultsWidget = new QWidget();
      QVBoxLayout* resultsLayout  = new QVBoxLayout();
      resultsWidget->setLayout(resultsLayout);
      mpmResults = new ResultsMPM(this); // this
      

      resultsLayout->addWidget(mpmResults);
      resultsLayout->addStretch();
      theTabWidget->addTab(resultsWidget, QIcon(QString(":/icons/flag-black.svg")), "Results");
      theTabWidget->setCurrentIndex(theTabWidget->count() - 1);
    }

  }  

  statusMessage("HydroUQ EVENTS MPM - Get results widget for the EVT to allow us to post-process the downloaded results (or locally saved results) for visualization.");
  return mpmResults;
}
#endif

void MPM::importMainDomainJsonFile(QJsonObject &jsonObject)
{
    // openFoamVersion->setCurrentText(jsonObject["OpenFoamVersion"].toString());
    // geometry->inputFromJSON(jsonObject);
    // snappyHexMesh->inputFromJSON(jsonObject);
    // windCharacteristics->inputFromJSON(jsonObject);
    // boundaryConditions->inputFromJSON(jsonObject);
    // turbulenceModeling->inputFromJSON(jsonObject);
    // numericalSetup->inputFromJSON(jsonObject);
}


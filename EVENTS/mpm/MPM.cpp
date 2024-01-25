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

// Written: fmk

#include "MPM.h"
#include <QScrollArea>
#include <QLineEdit>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QJsonObject>
#include <QJsonArray>
#include <QSvgWidget>
#include <QString>
#include <QIcon>
#include <QPixmap>
#include <QToolButton>
#include <QStackedWidget>
#include "slidingstackedwidget.h"

#include <SettingsMPM.h>
#include <BodiesMPM.h>
#include <BoundariesMPM.h>
#include <SensorsMPM.h>
#include <OutputsMPM.h>

MPM::MPM(QWidget *parent)
    : SimCenterAppWidget(parent)
{
    int windowWidth = 800;
    int windowWidthMin = 250;
    QWidget     *mainGroup = new QWidget();
    QGridLayout *mainLayout = new QGridLayout();



    QLabel *generalDescriptionLabel = new QLabel(" Create waterborne events (EVT) in NHERI SimCenter Digital Twins to streamline your experimental research."
                                                 "\n ");
                                                //  "\n"
                                                //  "\n 1.) Set general simulation Settings, e.g. the total simulation duration."						 
                                                //  "\n 2.) Define Bodies (e.g. fluid, debris, structures, etc) via materials and initial conditions."
                                                //  "\n 3.) Define Boundaries (Digital Twins, Structures, etc) as boundary conditions."
                                                //  "\n 4.) Specify Sensors (e.g. wave-gauges) to measure within simulations."
                                                //  "\n 5.) Select other Output settings (e.g. write simulation checkpoint-resume files).");
                                                //  "\n 6.) If all side-bar pages are complete, click [RUN at DesignSafe] (bottom of the app) to simulate your Event.");
    generalDescriptionLabel->setWordWrap(true);
    generalDescriptionLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(generalDescriptionLabel, 0, 0);

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
                                               "\n "
                                               "\n Generate directional waves with a wide range of wave periods and heights."
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
    connect(stackedWidget,&SlidingStackedWidget::animationFinished,[this, prev, next]{
        prev->setEnabled(true);
        next->setEnabled(true);
    });

    QLabel *aboveTabs = new QLabel("\nSelect a Digital Twin Above To Begin\n");
    aboveTabs->setAlignment(Qt::AlignCenter);
    // aboveTabs->setStyleSheet("QLabel {background-color:  rgb(79, 83, 89); color: #ffffff; border: 0px solid #000000; border-radius: 0px;}"
    //                          "QLabel:disabled {background-color:  rgb(79, 83, 89); color: #ffffff; border: 0px solid #000000; border-radius: 0px;}");
    mainLayout->addWidget(aboveTabs, 2, 0);

    // ==================== Simulation Set-Up ====================
    mpmSettings = new SettingsMPM();
    mpmBodies = new BodiesMPM();
    mpmBoundaries = new BoundariesMPM();
    mpmSensors = new SensorsMPM();
    mpmOutputs = new OutputsMPM();

    QTabWidget *theTabWidget = new QTabWidget();
    theTabWidget->addTab(mpmSettings, QIcon(QString(":/icons/settings-black.svg")), "Settings");
    theTabWidget->addTab(mpmBodies, QIcon(QString(":/icons/deform-black.svg")), "Bodies");
    theTabWidget->addTab(mpmBoundaries, QIcon(QString(":/icons/man-door-black.svg")), "Boundaries");
    theTabWidget->addTab(mpmSensors, QIcon(QString(":/icons/dashboard-black.svg")), "Sensors");
    theTabWidget->addTab(mpmOutputs, QIcon(QString(":/icons/file-settings-black.svg")), "Outputs");    
    int sizePrimaryTabs =20;
    theTabWidget->setIconSize(QSize(sizePrimaryTabs,sizePrimaryTabs));
    // theTabWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

    mainLayout->addWidget(theTabWidget, 3, 0);
    mainGroup->setLayout(mainLayout);
    mainGroup->setMinimumWidth(windowWidthMin);
    mainGroup->setMaximumWidth(windowWidth);
    // mainGroup->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    mainLayout->setRowStretch(0, 4);

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setLineWidth(1);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setWidget(mainGroup);
    scrollArea->setMinimumWidth(windowWidthMin + 25);
    scrollArea->setMaximumWidth(windowWidth + 25);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(scrollArea);
    this->setLayout(layout);


  connect(stackedWidget, &SlidingStackedWidget::animationFinished, [=](void){
    // if(index == 0){
    //   aboveTabs->setText("\nOregon State University's Large Wave Flume - OSU LWF\n");
    // } else if(index == 1){
    //   aboveTabs->setText("\nOregon State University's Directional Wave Basin - OSU DWB\n");
    // } else if(index == 2){
    //   aboveTabs->setText("\nUniversity of Washington's Wind-Air-Sea Interatction Research Facility - UW WASIRF\n");
    // } else if(index == 3){
    //   aboveTabs->setText("\nWaseda University's Tsunami Wave Basin - WU TWB\n");
    // } else if(index == 4){
    //   aboveTabs->setText("\nUnited States Geological Survey's Debris Flow Flume - USGS DFF\n");
    // }
    // mpmBodies->setDigitalTwin(index);
    int index = stackedWidget->currentIndex();
    mpmBodies->setDigitalTwin(index);
    mpmBoundaries->setDigitalTwin(index);
  });


}


MPM::~MPM()
{

}


void MPM::clear(void)
{

}


bool MPM::inputFromJSON(QJsonObject &jsonObject)
{
  this->clear();
  
  mpmSettings->inputFromJSON(jsonObject);
  mpmBodies->inputFromJSON(jsonObject);
  mpmBoundaries->inputFromJSON(jsonObject);
  mpmSensors->inputFromJSON(jsonObject);
  mpmOutputs->inputFromJSON(jsonObject);
  
  return true;
}

bool MPM::outputToJSON(QJsonObject &jsonObject)
{
  jsonObject["EventClassification"]="Hydro";
  jsonObject["Application"] = "MPM";
    
  // The JSON object-or-array that defines each main tab (i.e. Settings, Bodies, Boundaries, Sensors, Outputs)
  QJsonObject settingsObject;  
  QJsonArray bodiesArray;
  QJsonArray boundariesArray;
  QJsonArray sensorsArray;
  QJsonObject outputsObject;

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

  // ==================== Settings ====================
  // Settings (simulation in ClaymoreUW currently)
  if (settingsObject.contains("simulation") && settingsObject["simulation"].isObject()) {
    // Read in the simulation object from the settings object
    jsonObject["simulation"] = settingsObject["simulation"];

    // Move some values from the outputs object to the simulation settings object
    QJsonObject my_sim = jsonObject["simulation"].toObject(); 
    if (outputsObject.contains("save_suffix") && outputsObject["save_suffix"].isString()) {
      my_sim["save_suffix"] = outputsObject["save_suffix"].toString(); // for ClaymoreUW, simulation:save_suffix = outputs:bodies_save_suffix
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
    jsonObject["bodies"] = bodiesArray; // for the future schema
  }

  // ==================== Boundaries ====================
  // Boundaries (grid-boundaries in ClaymoreUW currently, TODO: Deprecate and change to "boundaries")
  if (boundariesObjectWrapper.contains("boundaries") && boundariesObjectWrapper["boundaries"].isArray()) {
    // boundaries is an array of objects, each is an individual boundary
    jsonObject["boundaries"] = boundariesObjectWrapper["boundaries"]; // for the future schema
  }

  // ==================== Sensors ====================
  // Sensors (grid-targets, particle-targets in ClaymoreUW currently, TODO: Deprecate and change to "sensors")
  // sensors is an array of objects, each is an individual sensor
  if (0) {
    if (sensorsObjectWrapper.contains("sensors") && sensorsObjectWrapper["sensors"].isArray()) 
      jsonObject["sensors"] = sensorsObjectWrapper["sensors"];
  } else {
    if (sensorsObjectWrapper.contains("particle-sensors") && sensorsObjectWrapper["particle-sensors"].isArray()) 
      jsonObject["particle-sensors"] = sensorsObjectWrapper["particle-sensors"]; // for the future schema
    if (sensorsObjectWrapper.contains("grid-sensors") && sensorsObjectWrapper["grid-sensors"].isArray()) 
      jsonObject["grid-sensors"] = sensorsObjectWrapper["grid-sensors"]; // for the future schema
  }
  // ==================== Outputs ====================
  // Outputs (not a separate object in ClaymoreUW currently, must move some fields to other objects manually for ClaymoreUW)
  if (outputsObject.contains("outputs") && outputsObject["outputs"].isObject()) {
    jsonObject["outputs"] = outputsObject["outputs"]; // for future schema, not used in ClaymoreUW currently
  }

  
  return true;
}

bool MPM::outputAppDataToJSON(QJsonObject &jsonObject) {

    //
    // per API, need to add name of application to be called in AppLication
    // and all data to be used in ApplicationDate
    //

    jsonObject["EventClassification"]="Hydro";
    jsonObject["Application"] = "MPM";
    QJsonObject dataObj;
    jsonObject["ApplicationData"] = dataObj;

    return true;
}
bool MPM::inputAppDataFromJSON(QJsonObject &jsonObject) {

    Q_UNUSED(jsonObject);
    return true;
}


bool MPM::copyFiles(QString &destDir) {
  
  if (mpmBodies->copyFiles(destDir) == false)
    return false;
  if (mpmBoundaries->copyFiles(destDir) == false)
    return false;
  // if (mpmSensors->copyFiles(destDir) == false)
  //   return false;    

  return true;
 }


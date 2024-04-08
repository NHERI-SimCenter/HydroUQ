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

// Written: JustinBonus

#include "Celeris.h"

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
// #include <QStackedWidget>
// #include "slidingstackedwidget.h"

#include <SC_DoubleLineEdit.h>
#include <SC_IntLineEdit.h>

// #include <Qt3DExtras/QCuboidMesh>
// #include <Qt3DExtras/QPhongMaterial>
// #include <Qt3DExtras/QPhongAlphaMaterial>
// #include <Qt3DExtras/Qt3DWindow>
// #include <Qt3DRender/QMesh>
// #include <Qt3DExtras/QForwardRenderer>
// #include <Qt3DRender/QCamera>
// #include <Qt3DCore/QTransform>
// #include <Qt3DCore/QEntity>
// #include <QQuaternion>
// #include <Qt3DExtras/QOrbitCameraController>
// #include <Qt3DRender/QAttribute>
// #include <Qt3DRender/QBuffer>
// #include <Qt3DRender/QGeometry>
// #include <Qt3DRender/QGeometryRenderer>


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

#include <QWebEngineView>
#include <QUrl> 
// #include <QWebEngineView>
// #include <QWebEnginePage>
// #include <QWebEngineSettings>
// #include <QWebEngineProfile>
// #include <QWebEngineScriptCollection>
// #include <QWebEngineScript>
// #include <QWebEngineScriptCollection>

// Trying out
// #include <SimCenterAppWidget.h>
// #include <WorkflowAppHydroUQ.h>
// #include <MainWindowWorkflowApp.h>
// #include <HydroEventSelection.h>
// #include <LocalApplication.h>
// #include <RemoteApplication.h>
// #include <RemoteJobManager.h>
// #include <RunWidget.h>
// #include <UQ_EngineSelection.h>
// #include <UQ_Results.h>
// #include <SC_ToolDialog.h>
// #include <SC_RemoteAppTool.h>

Celeris::Celeris(QWidget *parent)
    :  SimCenterAppWidget(parent)
{
    int windowWidth = 800;
    int windowWidthMin = 800;
    int windowHeight = 800;
    int windowHeightMin = 800;
    QWidget     *mainGroup = new QWidget();
    mainLayout = new QGridLayout();
    mainWindowLayout = new QHBoxLayout(); 



    // -----------------------------------------------------------------------------------

    // Add QWebView for viewing a Boussinesq wave solver web-page using WebGPU functionality
    m_pWebView = new QWebEngineView(this);
    // Set position and size of instance
    m_pWebView->setGeometry(0, 0, 1920, 1080);
    // Maximize the size of the instance
    m_pWebView->setMinimumSize(800, 400);
    m_pWebView->setMaximumSize(1920, 1080);

    m_pWebView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // m_pWebView->showMaximized();
    
    // Load the initial page
    // m_pWebView->load(QUrl("https://tidesandcurrents.noaa.gov/ports/index.html?port=sf"));
    m_pWebView->load(QUrl("https://plynett.github.io/"));
    // m_pWebView->load(QUrl("https://coast.noaa.gov/ccapatlas/""));
    // m_pWebView->load(QUrl("https://coast.noaa.gov/slr/"));
    // m_pWebView->load(QUrl("https://debristracker.org/data/"));
    // "https://nvs.nanoos.org/TsunamiEvac"
    // Tie the QWebView to the layout
    mainLayout->addWidget(m_pWebView, 0, 0);

    // -----------------------------------------------------------------------------------

    // m_pWebViewExtra = new QWebEngineView(this);
    // Set position and size of instance
    // m_pWebViewExtra->setGeometry(745, 0, 1280, 720);
    // Maximize the size of the instance


    // -----------------------------------------------------------------------------------

    // mainLayout->addWidget(updateBodiesButton, 3, 0);
    // mainLayout->addWidget(theTabWidget, 4, 0);
    mainGroup->setLayout(mainLayout);
    mainGroup->setMinimumWidth(windowWidthMin);
    // mainGroup->setMaximumWidth(windowWidth);
    mainGroup->setMinimumHeight(windowHeightMin);
    // mainGroup->setWidgetResizable(true);
    
    // QScrollArea *scrollArea = new QScrollArea();
    // scrollArea->setWidgetResizable(true);
    // scrollArea->setLineWidth(1);
    // scrollArea->setFrameShape(QFrame::NoFrame);
    // scrollArea->setWidget(mainGroup);
    // scrollArea->setMinimumWidth(windowWidthMin + 25);
    // scrollArea->setMaximumWidth(windowWidth + 25);


    // Add digital twin + scene builder on left. Add 3D visualizer on right
    QHBoxLayout *horizontalPanelLayout = new QHBoxLayout();
    QWidget *horizontalPanels = new QWidget();
    horizontalPanels->setLayout(horizontalPanelLayout);
    // horizontalPanelLayout->addWidget(scrollArea);
    horizontalPanelLayout->addWidget(mainGroup);

    // horizontalPanelLayout->addWidget(visualizationGroup);
    // horizontalPanelLayout->addWidget(container);

    // QVBoxLayout *layout = new QVBoxLayout();
    // mainWindowLayout->addWidget(scrollArea);
    // mainWindowLayout->addWidget(updateBodiesButton);
    // mainWindowLayout->addWidget(container);
    mainWindowLayout->addWidget(horizontalPanels);
    this->setLayout(mainWindowLayout);


}


Celeris::~Celeris()
{

}


bool Celeris::outputToJSON(QJsonObject &jsonObject)
{
    return true;
}

bool Celeris::inputFromJSON(QJsonObject &jsonObject)
{
    return true;
}

bool Celeris::outputAppDataToJSON(QJsonObject &jsonObject)
{
    return true;
}

bool Celeris::inputAppDataFromJSON(QJsonObject &jsonObject)
{
    return true;
}

bool Celeris::copyFiles(QString &dirName)
{
    return true;
}

void Celeris::clear(void)
{
    return;
}


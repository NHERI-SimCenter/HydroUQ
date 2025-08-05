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

#include "DigitalCoast.h"

#include <QVector>
#include <QScrollArea>
#include <QLineEdit>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QJsonObject>
#include <QJsonArray>
// #include <QSvgWidget>
#include <QString>
#include <QIcon>
#include <QPixmap>
#include <QToolButton>

#include <SC_DoubleLineEdit.h>
#include <SC_IntLineEdit.h>

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

DigitalCoast::DigitalCoast(QWidget *parent)
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
    // Add QWebView for viewing page
    m_pWebView = new QWebEngineView(this);

    // Set position and size of instance
    m_pWebView->setGeometry(0, 0, 1920, 1080);

    // Adjust size of the instance
    m_pWebView->setMinimumSize(800, 800);
    m_pWebView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Load the initial page
    m_pWebView->load(QUrl("https://coast.noaa.gov/slr/"));

    // -----------------------------------------------------------------------------------
    QLabel *label = new QLabel();
    QLabel *labelExtra = new QLabel();
    label->setText("Digital Coast - NOAA.");
    labelExtra->setText("Access a variety of intuitive web-applications for coastal management. Port results as intensity measures, etc., to the rest of HydroUQ.");

    // -----------------------------------------------------------------------------------
    mainLayout->addWidget(label, 0, 0, Qt::AlignCenter);
    mainLayout->addWidget(labelExtra, 1, 0, Qt::AlignCenter);
    mainLayout->addWidget(m_pWebView, 2, 0);
    mainGroup->setLayout(mainLayout);
    mainGroup->setMinimumWidth(windowWidthMin);
    mainGroup->setMinimumHeight(windowHeightMin);

    QVBoxLayout *horizontalPanelLayout = new QVBoxLayout();
    QWidget *horizontalPanels = new QWidget();
    horizontalPanels->setLayout(horizontalPanelLayout);
    horizontalPanelLayout->addWidget(mainGroup);
    mainWindowLayout->addWidget(horizontalPanels);
    this->setLayout(mainWindowLayout);
}


DigitalCoast::~DigitalCoast()
{

}


bool DigitalCoast::outputToJSON(QJsonObject &jsonObject)
{
    return true;
}

bool DigitalCoast::inputFromJSON(QJsonObject &jsonObject)
{
    return true;
}

bool DigitalCoast::outputAppDataToJSON(QJsonObject &jsonObject)
{
    return true;
}

bool DigitalCoast::inputAppDataFromJSON(QJsonObject &jsonObject)
{
    return true;
}

bool DigitalCoast::copyFiles(QString &dirName)
{
    return true;
}

void DigitalCoast::clear(void)
{
    return;
}


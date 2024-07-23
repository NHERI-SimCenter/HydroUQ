#ifndef GEOMETRY_AI_H
#define GEOMETRY_AI_H

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

// Written by: JustinBonus

#include <SimCenterWidget.h>

// #include <QList>
class QJsonObject;
class QJsonArray;
class InputWidgetParameters;
class RandomVariablesContainer;
class QComboBox;
class QGridLayout;
class QVBoxLayout;
class QHBoxLayout;
class QSpinBox;
class QCheckBox;
class QLineEdit;
class LineEditRV;
class QTabWidget;
class QTableWidget;
class QGroupBox;
class QPushButton;
class QDoubleSpinBox;
class QLabel;
class QRadioButton;
class QString;
//class QStringList;

class SC_DoubleLineEdit;
class SC_IntLineEdit;
class SC_StringLineEdit;
class SC_ComboBox;
class SC_TableEdit;
class SC_FileEdit;
class SC_CheckBox;

class GeometryAI: public SimCenterWidget
{
    Q_OBJECT

public:
    explicit GeometryAI(QWidget *parent = 0);
    ~GeometryAI(); // override // virtual

    bool inputFromJSON(QJsonObject &jsonObject); // override
    bool outputToJSON(QJsonObject &jsonObject); // override 
    bool executeTextPromptsScripts(QString &dirName);     
    bool executeImagePromptsScripts(QString &dirName);     
    // void clear(void); 
    bool showImage (QString &fileName);
signals:

public slots:
    // void onExecuteScriptClicked(void);
    void onProcessTextPromptsClicked(void);
    void onProcessImagePromptsClicked(void);
    // void onPointCloudToMeshClicked(void);
    // void onSurfaceToVolumeClicked(void);
    // void onPointCloudToSignedDistanceFieldClicked(void);

    bool text2pointcloud();
    bool image2pointcloud();
    // bool pointcloud2mesh();
    // bool text2pointcloud();
    // bool text2mesh();
    // bool image2mesh();
    bool simulationCompleted();    

private:

//     QWidget *container;
    QVBoxLayout         *layout;

    // text2pointcloud
    QGroupBox            *textPromptsGroup;
    QGridLayout          *textPromptsLayout;
    QPushButton          *textPromptsButton;
    QComboBox            *textScriptName;
    QLineEdit            *textPrompt;
    QStringList          *textsList;


    // image2pointcloud
    QGroupBox            *imagePromptsGroup;
    QGridLayout          *imagePromptsLayout;
    QPushButton          *imagePromptsButton;
    QComboBox            *imageScriptName;
    QLineEdit            *imagePrompt;
    QStringList          *imagesList;


    // QStringList         *promptsList;
    // QString             *scriptName;
    // QString             *scriptPath;
    // QString             *promptPath;
    // QString             *outputPath;
    // QDir                *promptsDir;

public:

};

#endif // GEOMETRY_AI_H

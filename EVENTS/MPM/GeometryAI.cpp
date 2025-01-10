
#include "GeometryAI.h"
#include <GeneralInformationWidget.h>
#include <RandomVariablesContainer.h>
#include <LineEditRV.h>
#include <SimCenterPreferences.h>
#include <GeneralInformationWidget.h>
#include <SectionTitle.h>
#include <SC_DoubleLineEdit.h>
#include <SC_IntLineEdit.h>
#include <SC_StringLineEdit.h>
#include <SC_ComboBox.h>
// #include <SC_TableEdit.h>
#include <SC_FileEdit.h>
#include <SC_CheckBox.h>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QGroupBox>
#include <QScrollArea>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>

#include <QVector>
#include <QList>
#include <QIcon>
#include <QMovie>
#include <QPixmap>

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>

#include <QString>
#include <QStringList>
#include <QTextStream>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

// #include <QtMath>
#include <QVector3D>


// #include <QThread>
#include <QProcess>

#include <QUrl>
#include <QWebEngineView>

#include <Qt3DExtras/QCuboidMesh>
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

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <Qt3DCore/QBuffer>
#include <Qt3DCore/QAttribute>
#include <Qt3DCore/QGeometry>
namespace Qt3DGeometry = Qt3DCore;
#else
#include <Qt3DRender/QBuffer>
#include <Qt3DRender/QAttribute>
#include <Qt3DRender/QGeometry>

namespace Qt3DGeometry = Qt3DRender;
#endif

#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DRender/QMaterial>
#include <Qt3DRender/QMesh>
#include <Qt3DRender/QObjectPicker>
#include <Qt3DRender/QParameter>
#include <Qt3DRender/QPointLight>
#include <Qt3DRender/QSceneLoader>
#include <QWebEngineView>


GeometryAI::GeometryAI(QWidget* parent) : SimCenterWidget(parent)
{
    layout = new QVBoxLayout();
    
    textPromptsGroup = new QGroupBox("Text-to-Pointcloud");
    textPromptsLayout = new QGridLayout();
    textPromptsGroup->setLayout(textPromptsLayout);

    imagePromptsGroup = new QGroupBox("Image-to-Pointcloud");
    imagePromptsLayout = new QGridLayout();
    imagePromptsGroup->setLayout(imagePromptsLayout);

    //==================================================================
    //  text2pointcloud - Specify text to process into point clouds
    //==================================================================
    QLabel* textScriptsLabel = new QLabel("Script to Run: ");
    textScriptName = new QComboBox();
    textScriptName->addItem("text2pointcloud.py");
    textScriptName->setToolTip("Name of the post-processing script (typically Python / PyTorch based) which takes a text prompt and returns an AI generated pointcloud.");
    textScriptName->setCurrentIndex(0);

    QLabel* textPromptLabel = new QLabel("Text Prompt: ");
    textPrompt = new QLineEdit();
    textPrompt->setToolTip("Text prompt to process into a point-cloud.");
    textPrompt->setPlaceholderText("Enter text prompt here.");

    textPromptsButton = new QPushButton("GENERATE");
    textPromptsButton->setToolTip("Processes text prompt(s) and executes a backend script to generate point-clouds.");

    textPromptsLayout->addWidget(textScriptsLabel, 0, 0, Qt::AlignRight);
    textPromptsLayout->addWidget(textScriptName, 0, 1);
    textPromptsLayout->addWidget(textPromptLabel, 0, 2, Qt::AlignRight);
    textPromptsLayout->addWidget(textPrompt, 0, 3);
    textPromptsLayout->addWidget(textPromptsButton, 0, 4, 2, 1);

    //==================================================================
    //  image2pointcloud - Specify images to process into point clouds
    //==================================================================
    QLabel* imageScriptsLabel = new QLabel("Script to Run: ");
    imageScriptName = new QComboBox();
    imageScriptName->addItem("image2pointcloud.py");
    imageScriptName->setToolTip("Name of the post-processing script (typically Python / PyTorch based) which takes an image and returns an AI generated pointcloud.");
    imageScriptName->setCurrentIndex(0);

    QLabel* imagePromptLabel = new QLabel("Image Prompt: ");
    imagePrompt = new QLineEdit();
    imagePrompt->setToolTip("Image prompt to process into a point-cloud.");
    imagePrompt->setPlaceholderText("Enter image prompt here.");

    imagePromptsButton = new QPushButton("GENERATE");
    imagePromptsButton->setToolTip("Processes image prompt(s) and executes a backend script to generate point-clouds.");

    imagePromptsLayout->addWidget(imageScriptsLabel, 0, 0, Qt::AlignRight);
    imagePromptsLayout->addWidget(imageScriptName, 0, 1);
    imagePromptsLayout->addWidget(imagePromptLabel, 0, 2, Qt::AlignRight);
    imagePromptsLayout->addWidget(imagePrompt, 0, 3);
    imagePromptsLayout->addWidget(imagePromptsButton, 0, 4, 2, 1);

    //==================================================================
    //              Connect Signals and Slots
    //==================================================================
    connect(textPromptsButton, SIGNAL(clicked()), this, SLOT(onProcessTextPromptsClicked()));
    connect(imagePromptsButton, SIGNAL(clicked()), this, SLOT(onProcessImagePromptsClicked()));

    layout->addWidget(textPromptsGroup);
    layout->addWidget(imagePromptsGroup);



    //==================================================================
    //              3D Point Cloud Viewer
    //==================================================================
    // Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    // // white background
    // view->defaultFrameGraph()->setClearColor(QColor(QRgb(0xffffff)));
    // container = QWidget::createWindowContainer(view);
    // layout->addWidget(container);
    // container->setMinimumSize(QSize(400, 400));
    // container->setMaximumSize(QSize(400, 400));
    // // QWidget *widget = new QWidget;
    // // QHBoxLayout *hLayout = new QHBoxLayout(widget);
    // // hLayout->addWidget(container, 1);
    // // widget->setWindowTitle(QStringLiteral("Generative AI Geometry Viewer"));

    // Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();
    // // view->setRootEntity(rootEntity);

    // // Qt3DInput::QInputAspect *input = new Qt3DInput::QInputAspect;
    // // view->registerAspect(input);

    // // Camera
    // Qt3DRender::QCamera *cameraEntity = view->camera();
    // cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    // cameraEntity->setPosition(QVector3D(0, 0, 40.0f));
    // cameraEntity->setViewCenter(QVector3D(0, 0, 0));
    // // Camera facing a 1x1x1 cube centered at the origin
    // // cameraEntity->setPosition(QVector3D(0, 0, 50.0f));
    // // cameraEntity->setUpVector(QVector3D(0, 1, 0));
    // // cameraEntity->setViewCenter(QVector3D(0, 0, 0));


    // // cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    // // cameraEntity->setPosition(QVector3D(0, 0, 4.0f));
    // // cameraEntity->setViewCenter(QVector3D(0, 0, 0));

    // // Light
    // Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    // Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    // light->setColor("white");
    // light->setIntensity(1);
    // lightEntity->addComponent(light);

    // Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    // lightTransform->setTranslation(cameraEntity->position());
    // lightEntity->addComponent(lightTransform);

    // // Camera Controls
    // Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(rootEntity);
    // camController->setCamera(cameraEntity);
    // // camController->setLinearSpeed( 50.0f );
    // // camController->setLookSpeed( 180.0f );
    // // Show window


    // // Point Cloud
    // QString pointFileName = QDir::cleanPath(QString("/home/justinbonus/SimCenter/point-e/point_e/examples/output") + QDir::separator() + QString("motorcycle_pc") + QString(".obj"));
    // QFile pointFile(pointFileName);
    // if (!pointFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
    //     qDebug() << "ERROR: GeometryAI 3D Viewer - Could not open point-cloud file: " << pointFileName;
    // }
    // QUrl data = QUrl::fromLocalFile(pointFileName);
    // qDebug() << data << data.isValid() << data.toLocalFile() << QFileInfo(data.toLocalFile()).exists() << data.fileName();

    // Qt3DRender::QMesh *pointCloud = new Qt3DRender::QMesh();
    // pointCloud->setMeshName(data.fileName());
    // pointCloud->setSource(data);

    // Qt3DCore::QTransform *pointTransform = new Qt3DCore::QTransform();
    // pointTransform->setScale3D(QVector3D(1.f, 1.f, 1.f));
    // pointTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1.f, 0.f, 0.f), 0.0f));

    // Qt3DExtras::QPhongMaterial *pointMaterial = new Qt3DExtras::QPhongMaterial();
    // pointMaterial->setAmbient(Qt::red);
    // pointMaterial->setDiffuse(Qt::red);
    // pointMaterial->setSpecular(Qt::white);
    // pointMaterial->setShininess(50.0f);

    // Qt3DCore::QEntity *pointCloudEntity = new Qt3DCore::QEntity(rootEntity);
    // pointCloudEntity->addComponent(pointCloud);
    // pointCloudEntity->addComponent(pointTransform);
    // pointCloudEntity->addComponent(pointMaterial);

    // view->setRootEntity(rootEntity);

    // // widget->setEnabled(false);
    // // widget->hide();
    // // widget->show();
    // // widget->resize(800, 800);
    // // ------------------------------------------------------------------

    // Visualize png file
    // QString textDefault = "motorcycle";
    // QString plotsExt = ".png";
    // QString plotsPath = QDir::cleanPath("/home/justinbonus/SimCenter/point-e/point_e/examples/output/motorcycle.png");
    // // QString plotsPath = plotsDirPath + QDir::separator() + textDefault + plotsExt;
    // // QUrl plots = QUrl::fromLocalFile(plotsPath);
    // // qDebug() << plots << plots.isValid() << plots.toLocalFile() << QFileInfo(plots.toLocalFile()).exists() << plots.fileName();
    // // QPixmap plotsPic(plotsPath);
    // QPixmap plotsPic("/home/justinbonus/SimCenter/point-e/point_e/examples/output/motorcycle.png");
    // QLabel *plotsLabel = new QLabel(); 
    // plotsLabel->setPixmap(plotsPic);
    // plotsLabel->setScaledContents(true);
    // plotsLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    // plotsLabel->setMinimumHeight(250);
    // plotsLabel->setMinimumWidth(250);
    // plotsLabel->setMaximumHeight(800);
    // plotsLabel->setMaximumWidth(800);
    // plotsLabel->setAlignment(Qt::AlignCenter);
    // // layout->addWidget(plotsLabel);
    // // plotsLabel->setScaledContents(true);
    // // plotsLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    // // plotsLabel->setMinimumSize(400, 400);
    // // plotsLabel->setMaximumSize(400, 400);
    // // plotsLabel->show();

    // QWidget *plotsPanel = new QWidget();
    // // line->setFrameShape(QFrame::HLine);
    // // line->setFrameShadow(QFrame::Sunken);
    // QHBoxLayout *plotsPanelLayout = new QHBoxLayout();
    // plotsPanel->setLayout(plotsPanelLayout);
    // plotsPanelLayout->addWidget(plotsLabel);
    // layout->addWidget(plotsPanel);


    this->setLayout(layout);

    // connect(textPrompt, SIGNAL(returnPressed()), this, SLOT(onProcessTextPromptsClicked()));
    // connect(imagePrompt, SIGNAL(returnPressed()), this, SLOT(onProcessImagePromptsClicked()));
    // connect(textPrompt, SIGNAL(editingFinished()), this, SLOT(onProcessTextPromptsClicked()));
    // connect(imagePrompt, SIGNAL(editingFinished()), this, SLOT(onProcessImagePromptsClicked()));

    // // lambdas to update the displayed 3d ply file
    // connect(textPromptsButton, &QPushButton::clicked, [=](){
    //     QString pointFileName = QDir::cleanPath("/home/justinbonus/SimCenter/point-e/point_e/examples/output" + QDir::separator() + "motorcycle" + ".ply");
    //     QFile pointFile(pointFileName);
    //     if (!pointFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
    //         qDebug() << "ERROR: GeometryAI 3D Viewer - Could not open point-cloud file: " << pointFileName;
    //     }
    //     QUrl data = QUrl::fromLocalFile(pointFile);
    //     qDebug() << data << data.isValid() << data.toLocalFile() << QFileInfo(data.toLocalFile()).exists() << data.fileName();
    //     pointCloud->setMeshName(data.fileName());
    //     pointCloud->setSource(data);
    // });
}


bool
GeometryAI::showImage(QString &text)
{
    int dialogHeight = 450;
    int dialogWidth  = 450;
    QVBoxLayout *plotLayout = new QVBoxLayout();
    QWebEngineView *plotView = new QWebEngineView();
    plotView->page()->setBackgroundColor(Qt::transparent);
    plotLayout->addWidget(plotView);

    plotView->setMinimumWidth(dialogWidth);
    plotView->setMinimumHeight(dialogHeight);

    // Remove any whitespace from the text prompt, and replace any spaces with nothing.
    text = text.trimmed();
    text = text.replace(" ", "");

    QString ext = ".png";
    QString plotPath = SimCenterPreferences::getInstance()->getLocalWorkDir() + QDir::separator() 
                        + textPrompt->text() 
                        + ext; // Temp hard-code, to be in SimCenterBackendApplications/modules/tools 

    if(QFileInfo::exists(plotPath))
    {
        plotView->load(QUrl::fromLocalFile(plotPath));
        plotView->setWindowFlag(Qt::WindowStaysOnTopHint);
        plotView->show();
        plotView->activateWindow();
        plotView->raise();
        return true;
    }
    return false;
}

GeometryAI::~GeometryAI()
{

}

void GeometryAI::clear(void)
{
    // textPrompt->clear();
    // imagePrompt->clear();
}

bool 
GeometryAI::text2pointcloud()
{
    //
    //  Example Genarative AI Geometry scripts hosted remotely by ../point-e/point_e/examples/ or SimCenterBackendApplications/modules/tools/point-e/point_e/examples/
    // 
    
    QString backendPath = QDir::cleanPath(SimCenterPreferences::getInstance()->getAppDir() + QDir::separator() + "..");
    qDebug() << "GeometryAI::text2pointcloud - backendPath: " << backendPath;

    QString pointePath = QDir::cleanPath(backendPath + QDir::separator() + "point-e"); 
    qDebug() << "GeometryAI::text2pointcloud - pointePath: " << pointePath;
    QString scriptName = "text2pointcloud.py"; // Default script name., in ../point-e/point_e/examples/ or SimCenterBackendApplications/modules/createEVENT/
    if (textScriptName) {
        scriptName = textScriptName->currentText(); // Must be initialized to a valid QString.
    }
    QString scriptPath = QDir::cleanPath(pointePath + QDir::separator() + "point_e" + QDir::separator() + "examples" + QDir::separator() + scriptName);
    QString outputPath = QDir::cleanPath(pointePath + QDir::separator() + "point_e" + QDir::separator() + "examples" + QDir::separator() + "output");
    QString promptPath = QDir::cleanPath(pointePath + QDir::separator() + "point_e" + QDir::separator() + "examples" + QDir::separator() + "input");
    // QString outputPath = mainModel->caseDir() + QDir::separator() + "output" + QDir::separator() ;
    // QString promptPath = mainModel->caseDir() + QDir::separator() + "input" + QDir::separator() ;
    QString text = textPrompt->text(); // The text prompt to process into a point-cloud.

    // Make sure that text is surrounded by quotes, and that any quotes inside the text are escaped.
    // text = "\"" + text.replace("\"", "\\\"") + "\"";

    // QString scriptPath = SimCenterPreferences::getInstance()->getAppDir() + QDir::separator() + "SimCenterBackendApplications" + QDir::separator() + "modules" + QDir::separator() + "tools" + QDir::separator() + "point-e" + QDir::separator() + "point_e" + QDir::separator() + "examples" + QDir::separator() + scriptName;

    // Find all the prompts in the promptPath folder if it exists, make them into one QString that is comma separated.
    qDebug() << "GeometryAI::text2pointcloud - promptPath: " << promptPath;
    qDebug() << "GeometryAI::text2pointcloud - outputPath: " << outputPath;
    qDebug() << "GeometryAI::text2pointcloud - scriptPath: " << scriptPath;
    qDebug() << "GeometryAI::text2pointcloud - scriptName: " << scriptName;

    QString promptsList =  "";
    QDir promptsDir(promptPath);
    // if (promptsDir.exists())
    // {

    //     // Print all the files in the directory (max 64 files for now, to avoid spamming the console)
    //     qDebug() << "Files in the prompts directory: "; 
    //     for (int i = 0; i < promptsDir.count() && i < 64; i++)
    //     {
    //         qDebug() << promptsDir[i];
    //     }

    //     QStringList filters("*.txt"); // This is the file extension of the prompt files, it may change in the future.
    //     // entryList returns a QStringList of all the files in the directory that match the filters.
    //     QStringList promptFiles = promptsDir.entryList(filters); //, QDir::Files, QDir::Name); 
    //     if (promptFiles.size() == 0)
    //     {
    //         qDebug() << "Prompt directory exists, but no text prompt files found in the output directory. Cannot run the text2pointcloud.py script. Dir: " << promptPath;
    //         return false;
    //     }
    //     for (int i = 0; i < promptFiles.size(); i++)
    //     {
    //         promptsList += promptFiles[i]; 
    //         if (i < promptFiles.size() - 1)
    //         {
    //             promptsList += ","; // For QString , is this the correct way to do this? 
    //         }
    //         qDebug() << "Prompt file: " << promptFiles[i];
    //     }
    // } else {
    //     qDebug() << "The prompt directory does not exist: " << promptPath;
    // }
    
    // qDebug() << "GeometryAI::text2pointcloud - promptsList: " << promptsList;

    // if (promptsList.isEmpty())
    // {
    //     qDebug() << "No prompt files found in the output directory. Cannot run the text2pointcloud.py script. Dir: " << promptPath << " promptsList: " << promptsList; 
    //     return false;
    // }


    if (text== "")
    {
        qDebug() << "WARNING: GeometryAI - No text prompt provided! Cannot run the text2pointcloud.py script. Dir: " << promptPath << " text-prompt: " << text; 
        return true; // Return true because the user may not want to run the script, and this is not an error.
    }
    qDebug() << "GeometryAI::text2pointcloud - text-prompt: " << text;

    if (!QDir(outputPath).exists())
    {
        qDebug() << "GeometryAI::text2pointcloud - Creating the output directory: " << outputPath;
        QDir().mkdir(outputPath);
    } 


    if (QFileInfo(scriptPath).exists() && QFileInfo(scriptPath).isFile())
    {
        QString program = SimCenterPreferences::getInstance()->getPython();
        qDebug() << "GeometryAI::text2pointcloud - Python program path: " << program;
        QProcess *process = new QProcess(this);
        QStringList arguments; 
        arguments << scriptPath << text; // arguments << scriptPath << promptPath << outputPath << promptsList;

        // Catch python print statements and errors and display them in through the qDebug() stream.
        QObject::connect(process, &QProcess::readyRead, [process] () {
            QByteArray a = process->readAll();
            qDebug() <<  a;
        });

        // Delete process instance / thread when done (later), and get the exit status to handle errors.
        QObject::connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                        [=](int exitCode, QProcess::ExitStatus /*exitStatus*/){
            qDebug()<< "process exited with code " << exitCode;
            process->deleteLater();
        });
        process->start(program, arguments);
        // wait up to 5 minutes for the process to finish, if it takes longer than this, it is likely stuck in an infinite loop.
        process->waitForStarted(-1);  
        process->waitForReadyRead(-1);
        process->waitForFinished(-1);
        // if (process->state() == QProcess::Running)
        // {
        //     process->kill();
        // }

        if (process->exitStatus() == QProcess::CrashExit)
        {
            qDebug() << "GeometryAI::text2pointcloud - The text2pointcloud.py script has crashed.";
        } 
        else if (process->exitStatus() == QProcess::NormalExit)
        {
            qDebug() << "GeometryAI::text2pointcloud - The text2pointcloud.py script has finished running.";
        }
        else 
        {
            qDebug() << "GeometryAI::text2pointcloud - The text2pointcloud.py script has finished running with an unknown exit status.";
        }
        // Make sure the process completes and closes, or if it fails to do so, kill it.
        // process->close();
        qDebug() << "GeometryAI::text2pointcloud - Finished running the text2pointcloud.py script.";
    } 
    else 
    {
        qDebug() << "ERROR: Cannot find the Generative AI text2pointcloud script path file, consider changing SimCenterBackendApplications path preference under the file drop-down to alter this to be valid: " << scriptPath;
        // return false;
    }
    return true;
}

bool 
GeometryAI::image2pointcloud()
{
    return true; // TODO: Implement this function.
}

bool
GeometryAI::inputFromJSON(QJsonObject &jsonObject)
{
    if (jsonObject.contains("text-prompt")) {
        textPrompt->setText(jsonObject["text-prompt"].toString());
    }
    if (jsonObject.contains("image-prompt")) {
        imagePrompt->setText(jsonObject["image-prompt"].toString());
    }
    return true;
}

bool
GeometryAI::outputToJSON(QJsonObject &jsonObject)
{
    jsonObject["text-prompt"] = textPrompt->text();
    jsonObject["image-prompt"] = imagePrompt->text();
    return true;
}

bool
GeometryAI::executeTextPromptsScripts(QString &dirName)
{
    return text2pointcloud();
}

bool
GeometryAI::executeImagePromptsScripts(QString &dirName)
{
    return image2pointcloud();
}

void 
GeometryAI::onProcessTextPromptsClicked(void)
{
    text2pointcloud();
}

void 
GeometryAI::onProcessImagePromptsClicked(void)
{
    image2pointcloud();
}

bool 
GeometryAI::simulationCompleted()
{
    return true;
}

bool GeometryAI::copyFiles(QString &dirName)
{
    Q_UNUSED(dirName);
    return true;
}


// void GeometryAI::onExecuteScriptClicked(void)
// {
//     return;
// }

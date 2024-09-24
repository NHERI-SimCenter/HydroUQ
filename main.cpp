// Written: fmckenna
// Modified: Ajay B Harish (Feb 2021)
// Modified: Justin Bonus (2024)
// Purpose: the typical Qt main for running a QMainWindow

// Include headers

#include <MainWindowWorkflowApp.h>
#include <QApplication>
#include <QFile>
#include <QThread>
#include <QObject>
#include <TapisV3.h>
#include <WorkflowAppHydroUQ.h>
#include <QCoreApplication>

#include <QString>
#include <QTime>
#include <QTextStream>
#include <QOpenGLWidget>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

#include <GoogleAnalytics.h>

#include <QStatusBar>
#include <QWebEngineView>
// #include <QtWebEngine>
// #include <QWebEngineView>
// #include <QWebEngineSettings>
// #include <QWebEngineProfile>
// #include <QQmlApplicationEngine>

// #include <SimCenterPreferences.h>
// #include <QSurfaceFormat>

#include <QtGlobal>
#include <stdio.h>
#include <stdlib.h>


#ifdef ENDLN
#undef ENDLN
#endif

#if QT_VERSION < QT_VERSION_CHECK(5, 15, 0)
#define ENDLN endl
#else
#define ENDLN Qt::endl
#endif


// Set up logging of output messages for user debugging
static QString logFilePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
      + QDir::separator() + QCoreApplication::applicationName();
constexpr bool logToFileDefault = false;
// static bool logToFile; // To be changed to true if the app is run in Qt Creator, using QTDIR env variable as proxy

 // customMessgaeOutput code taken from web:
 // https://stackoverflow.com/questions/4954140/how-to-redirect-qdebug-qwarning-qcritical-etc-output
void customMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QHash<QtMsgType, QString> msgLevelHash({{QtDebugMsg, "Debug"}, {QtInfoMsg, "Info"}, {QtWarningMsg, "Warning"}, {QtCriticalMsg, "Critical"}, {QtFatalMsg, "Fatal"}});
    QByteArray localMsg = msg.toLocal8Bit();
    QTime time = QTime::currentTime();
    QString formattedTime = time.toString("hh:mm:ss.zzz");
    QByteArray formattedTimeMsg = formattedTime.toLocal8Bit();
    QString logLevelName = msgLevelHash[type];
    QByteArray logLevelMsg = logLevelName.toLocal8Bit();

    // TODO: Better way to check if the app is run in Qt Creator than QTDIR, as its not guaranteed to only belong to Qt Creator
    static bool logToFile; // Compiler should default static bool init to 0. Changes to true if the app is run in Qt Creator, using QTDIR env variable as proxy
    static bool logToStdErr; // If true, output to  stderr
    QByteArray envVar = qgetenv("QTDIR"); // check if the app is run in Qt Creator
    if (envVar.isEmpty()) {
        logToFile = true;
    } else {
        logToFile = false;
    }
    
    if (logToFile) {
        QString txt = QString("%1 %2: %3 (%4)").arg(formattedTime, logLevelName, msg,  context.file);
        QFile outFile(logFilePath);
        outFile.open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream ts(&outFile);
        ts << txt << Qt::endl;
        outFile.close();
    } 
    
    if (logToStdErr || (!logToFile && !logToStdErr)) {
        fprintf(stderr, "%s %s: %s (%s:%u, %s)\n", formattedTimeMsg.constData(), logLevelMsg.constData(), localMsg.constData(), context.file, context.line, context.function);
        fflush(stderr);
    }


    if (type == QtFatalMsg)
         abort();
}


int main(int argc, char *argv[])
{
// #ifdef Q_OS_MACOS
    // QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);

    // code to reset openGL version .. keep around in case need again
    // QSurfaceFormat glFormat;
    // glFormat.setVersion(3, 3);
    // glFormat.setProfile(QSurfaceFormat::CompatibilityProfile);
    // QSurfaceFormat::setDefaultFormat(glFormat);

// #endif
    // QApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    // QGuiApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    // QApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
    // QApplication::setAttribute(Qt::AA_UseOpenGLES);
// #endif

// Extensive documentation on how to set up OpenGL on Windows, macOS, and Linux can be found at:
// https://doc.qt.io/qt-5/windows-requirements.html
#ifdef Q_OS_WIN
    QApplication::setAttribute(Qt::AA_UseOpenGLES); // Use ANGLE on Windows
#else
#ifdef Q_OS_MACOS
    QApplication::setAttribute(Qt::AA_UseDesktopOpenGL); // Use Desktop OpenGL on macOS
#else // Linux
    QApplication::setAttribute(Qt::AA_UseOpenGLES); // Use OpenGLES on Linux
    // QApplication::setAttribute(Qt::AA_ShareOpenGLContexts); 
#endif
#endif


    // QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    //Setting Core Application Name, Organization, and Version
    QCoreApplication::setApplicationName("HydroUQ");
    QCoreApplication::setOrganizationName("SimCenter");
    QCoreApplication::setApplicationVersion("4.0.1");

    //Init resources from static libraries (e.g. SimCenterCommonQt or s3hark)
    Q_INIT_RESOURCE(images);
    Q_INIT_RESOURCE(images1);
    // Q_INIT_RESOURCE(resources);
    // Q_INIT_RESOURCE(Resources);

    //
    // Set up logging of output messages for user debugging
    //

    if (logFilePath.isEmpty()) { 
        qDebug() << QString("Could not find Documents Location: ") << logFilePath;
        logFilePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
                      + QDir::separator() + QCoreApplication::applicationName();
    }
    QDir dirWork(logFilePath);
    if (!dirWork.exists()) {
        if (!dirWork.mkpath(logFilePath)) {
            qDebug() << QString("Could not create Working Dir: ") << logFilePath; 
            qDebug() << QString("May relate to permissions or disk space for the path... rerun with sudo or as an admin...");
        }
    }
    logFilePath = logFilePath + QDir::separator() + QString("debug.log"); 
    QFile debugFile(logFilePath);
    debugFile.remove();


    // Issues with web engine (notably with hardware acceleration) are
    // sometimes resolved by setting various flags.
    // https://github.com/probonopd/linuxdeployqt/issues/554
    // qputenv("QTWEBENGINE_CHROMIUM_FLAGS", "--disable-gpu --no-sandbox");
    // qputenv("QTWEBENGINE_CHROMIUM_FLAGS", "--ignore-gpu-blacklist --ignore-gpu-blocklist  --enable-gpu-rasterization --use-gl=egl");
    // qputenv("QTWEBENGINE_CHROMIUM_FLAGS", "--ignore-gpu-blacklist --ignore-gpu-blocklist  --enable-gpu-rasterization");
    // logToFile = logToFileDefault;
    // if constexpr (false) {
    //     QByteArray envVar = qgetenv("QTDIR"); // check if the app is run in Qt Creator
    //     if (envVar.isEmpty()) {
    //         logToFile = true;
    //     } else {
    //         logToFile = false;
    //     }
    // }

    qInstallMessageHandler(customMessageOutput);
    // qDebug() << "logFile: " << logFilePath;

    /******************  code to reset openGL version .. keep around in case need again
    QSurfaceFormat glFormat;
    glFormat.setVersion(3, 3);
    glFormat.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(glFormat);
    ***********************************************************************************/

    //
    // window scaling
    //

    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling); 
    // QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication a(argc, argv);

    // To have a plugin for web engine, uncomment the following lines
    // https://doc.qt.io/qt-5/qtwebengine-overview.html
    // QtWebEngine::initialize(); // Initialize the QtWebEngine
    // QQmlApplicationEngine engine; // This one only for qt quick applications
    // engine.load(QUrl(QStringLiteral("qrc:/main.qml")));



    // regular Qt startup
    // QApplication a(argc, argv);

    // create a remote interface
    QString tenant("designsafe");
    // QString storage("agave://designsafe.storage.default/"); 
    QString storage("designsafe.storage.default/");        
    QString dirName("HydroUQ"); // this is the default directory for the application
    // AgaveCurl *theRemoteService = new AgaveCurl(tenant, storage, &dirName);
    TapisV3 *theRemoteService = new TapisV3(tenant, storage, &dirName);        


    // create the main window
    WorkflowAppWidget *theInputApp = new WorkflowAppHydroUQ(theRemoteService);
    MainWindowWorkflowApp w(QString("HydroUQ: Water-borne Hazards Engineering with Uncertainty Quantification"), theInputApp, theRemoteService);

    // About the application
    QString aboutTitle = "About the SimCenter HydroUQ Application"; // this is the title displayed in the on About dialog
    QString aboutSource = ":/resources/docs/textAboutHydroUQ.html";  // this is an HTML file stored under resources
    w.setAbout(aboutTitle, aboutSource);

    // Version
    QString version = QString("Version ") + QCoreApplication::applicationVersion();
    w.setVersion(version);

    // Citation
    QString citeText("1) Frank McKenna, Justin Bonus, Ajay B Harish, & Nicolette Lewis. (2024). NHERI-SimCenter/HydroUQ: Version 4.0.0 (v4.0.0). Zenodo. https://doi.org/10.5281/zenodo.10902090 \n\n2) Gregory G. Deierlein, Frank McKenna, Adam Zsarnóczay, Tracy Kijewski-Correa, Ahsan Kareem, Wael Elhaddad, Laura Lowes, Matthew J. Schoettler, and Sanjay Govindjee (2020) A Cloud-Enabled Application Framework for Simulating Regional-Scale Impacts of Natural Hazards on the Built Environment. Frontiers in the Built Environment. 6:558706. doi: 10.3389/fbuil.2020.558706");
    w.setCite(citeText);

    // Link to repository
    QString manualURL("https://nheri-simcenter.github.io/Hydro-Documentation/");
    w.setDocumentationURL(manualURL);

    // Link to message board
    QString messageBoardURL("https://github.com/orgs/NHERI-SimCenter/discussions/categories/hydro-uq");

    w.setFeedbackURL(messageBoardURL);

    //
    // Move remote interface to a thread
    //

    QThread *thread = new QThread(); 
    theRemoteService->moveToThread(thread); 
    // QWidget::connect(thread, SIGNAL(finished()), theRemoteService, SLOT(deleteLater()));
    // QWidget::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    // https://wiki.qt.io/QThreads_general_usage
    // TODO, error handling
    // connect( worker, &TapisV3::error, this, &MyClass::errorString);
    // connect( thread, &QThread::started, theRemoteService, &TapisV3::process);
    // connect( theRemoteService, &TapisV3::finished, thread, &QThread::quit);
    // connect( theRemoteService, &TapisV3::finished, theRemoteService, &TapisV3::deleteLater);
    // connect( thread, &QThread::finished, thread, &QThread::deleteLater);
    // connect( theRemoteService, SLOT(error()), this, SLOT(errorString())); // TODO: make slot for error handling, should it be in the main window?
    QObject::connect(thread, SIGNAL(started()), theRemoteService, SLOT(process()));
    QObject::connect(theRemoteService, SIGNAL(finished()), thread, SLOT(quit())); 
    QObject::connect(theRemoteService, SIGNAL(finished()), theRemoteService, SLOT(deleteLater())); // ? is finished() a signal of theRemoteService?
    // QObject::connect(thread, SIGNAL(finished()), theRemoteService, SLOT(deleteLater())); 
    QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();

    constexpr int startupDelay = 6000; // milliseconds

    //
    // Show the main window, set styles & start the event loop
    //
    
    // https://www.qtcentre.org/threads/62377-Best-place-for-setting-stylesheet
	// Moving this to the place after MainWindow creation fixes unwanted padding,
	// but may produce really weird results on Mac OS X when styling combobox drop-down area.
    // w.show();
    // w.statusBar()->showMessage("Ready", startupDelay);

#ifdef Q_OS_WIN
    QFile file(":/styleCommon/stylesheetWIN.qss");
#else
#ifdef Q_OS_MACOS
    QFile file(":/styleCommon/stylesheetMAC.qss");
#else
#ifdef Q_OS_LINUX
    QFile file(":/styleCommon/stylesheetLinux.qss");
#else
    QFile file(":/styleCommon/stylesheetMAC.qss"); 
#endif 
#endif
#endif

    if (file.open(QFile::ReadOnly)) {
        a.setStyleSheet(file.readAll());
        qDebug() << "Stylesheet loaded: " << file.fileName();
        file.close();
    } else {
        qDebug() << "Could not open stylesheet: " << file.fileName();
    }

    w.show();
    w.statusBar()->showMessage("Ready", startupDelay);


#ifdef _SC_RELEASE

    //Setting Google Analytics Tracking Information
    GoogleAnalytics::SetMeasurementId("G-MC7SGPGWVQ");
    GoogleAnalytics::SetAPISecret("LrEiuSuaSqeh_v1928odog");
    GoogleAnalytics::CreateSessionId();
    GoogleAnalytics::StartSession();

    // Opening a QWebEngineView and using github to get app geographic usage
    QWebEngineView view;
    // view.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    // view.setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    // view.setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::SubWindow);
    // view.setAttribute(Qt::WA_TranslucentBackground);
    // view.setAttribute(Qt::WA_NoSystemBackground);
    // view.setUrl(QUrl("https://github.com/NHERI-SimCenter/HydroUQ/tree/master/GA4.html"));
    view.setUrl(QUrl("https://nheri-simcenter.github.io/HydroUQ/GA4.html"));
    view.resize(1024, 750);
    view.show();
    // view.raise();
    // view.activateWindow();
    // view.close();
    // view.deleteLater();    
    view.hide();

#endif
    
    // Result of execution
    int res = a.exec();

    // On done with event loop, logout & stop the thread
    theRemoteService->logout();

    // Clean up
    theRemoteService = nullptr;
    theInputApp = nullptr; 
    thread = nullptr;
    // thread->deleteLater();


    // Close Google Analytics session
    // GoogleAnalytics::SetClientId("");
    // GoogleAnalytics::SetSessionId("");
    GoogleAnalytics::SetMeasurementId("");
    GoogleAnalytics::SetAPISecret("");
    GoogleAnalytics::EndSession();

    // Complete
    return res;
}

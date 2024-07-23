// Written: fmckenna
// Modified: Ajay B Harish (Feb 2021)
// Purpose: the typical Qt main for running a QMainWindow

// Include headers
#include <GoogleAnalytics.h>
#include <AgaveCurl.h>
#include <MainWindowWorkflowApp.h>
#include <WorkflowAppHydroUQ.h>


#include <QApplication>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QObject>
#include <QFile>
// #include <QOpenGLWidget>
#include <QDebug>
#include <QStandardPaths>
#include <QStatusBar>
#include <QTextStream>
#include <QThread>
#include <QTime>


// #include <QCoreApplication>



#include <QSvgWidget>
#include <QWebEngineView>
#include <QtWebEngine>

//#include <QtGlobal> // for for Q_OS_WIN, etc.
#include <stdlib.h>
//#include <QSurfaceFormat>
#include <SimCenterPreferences.h>

#ifdef ENDLN
#undef ENDLN
#endif

#if QT_VERSION < QT_VERSION_CHECK(5, 15, 0)
#define ENDLN endl
#else
#define ENDLN Qt::endl
#endif


static QString logFilePath;
static bool logToFile = false;


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

    if (logToFile) {
        QString txt = QString("%1 %2: %3 (%4)").arg(formattedTime, logLevelName, msg,  context.file);
        QFile outFile(logFilePath);
        outFile.open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream ts(&outFile);
        ts << txt << Qt::endl;
        outFile.close();
    } else {
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
    QSurfaceFormat glFormat;
    // glFormat.setVersion(3, 3);
    glFormat.setProfile(QSurfaceFormat::CompatibilityProfile);
    QSurfaceFormat::setDefaultFormat(glFormat);

// #endif
    // QApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    QGuiApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    // QApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
    // QApplication::setAttribute(Qt::AA_UseOpenGLES);

    
// #endif

#ifdef Q_OS_WIN
    QApplication::setAttribute(Qt::AA_UseOpenGLES);
    // QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
#endif
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);



    //Setting Core Application Name, Organization, and Version
    QCoreApplication::setApplicationName("HydroUQ");
    QCoreApplication::setOrganizationName("SimCenter");
    QCoreApplication::setApplicationVersion("3.2.0");

    //Init resources from static libraries (e.g. SimCenterCommonQt or s3hark)
    Q_INIT_RESOURCE(images);
    Q_INIT_RESOURCE(images1);
    
    // Q_INIT_RESOURCE(Resources);

    // Set up logging of output messages for user debugging
    logFilePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
      + QDir::separator() + QCoreApplication::applicationName();

    // Make sure tool dir exists in Documentss folder
    QDir dirWork(logFilePath);
    if (!dirWork.exists())
        if (!dirWork.mkpath(logFilePath)) {
            qDebug() << QString("Could not create Working Dir: ") << logFilePath; 
        }

    // full path to debug.log file
    logFilePath = logFilePath + QDir::separator() + QString("debug.log"); 

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


    // remove old log file
    // QFile debugFile(logFilePath); 
    // debugFile.remove(); 

    QApplication a(argc, argv);

    // To have a plugin for web engine, uncomment the following lines
    // https://doc.qt.io/qt-5/qtwebengine-overview.html
    // QtWebEngine::initialize(); // Initialize the QtWebEngine
    // QQmlApplicationEngine engine; // This one only for qt quick applications
    // engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    //  check if the app is run in Qt Creator
    QByteArray envVar = qgetenv("QTDIR"); 

    if (envVar.isEmpty())
        logToFile = true;

    qInstallMessageHandler(customMessageOutput);

    qDebug() << "logFile: " << logFilePath;



    // regular Qt startup
    // QApplication a(argc, argv);

    // create a remote interface
    QString tenant("designsafe"); // this is the default tenant for the design safe community
    QString storage("agave://designsafe.storage.default/"); // this is the default storage system for the design safe community
    QString dirName("HydroUQ"); // this is the default directory for the application
    AgaveCurl *theRemoteService = new AgaveCurl(tenant, storage, &dirName); // this is the remote service used by the application


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
    QString citeText("1) Frank McKenna, Justin Bonus, Ajay B Harish, & Nicolette Lewis. (2024). NHERI-SimCenter/HydroUQ: Version 3.2.0 (v3.2.0). Zenodo. https://doi.org/10.5281/zenodo.10902090 \n\n2) Gregory G. Deierlein, Frank McKenna, Adam Zsarnóczay, Tracy Kijewski-Correa, Ahsan Kareem, Wael Elhaddad, Laura Lowes, Matthew J. Schoettler, and Sanjay Govindjee (2020) A Cloud-Enabled Application Framework for Simulating Regional-Scale Impacts of Natural Hazards on the Built Environment. Frontiers in the Built Environment. 6:558706. doi: 10.3389/fbuil.2020.558706");
    w.setCite(citeText);

    // Link to repository
    QString manualURL("https://nheri-simcenter.github.io/Hydro-Documentation/");
    w.setDocumentationURL(manualURL);

    // Link to message board
    QString messageBoardURL("http://simcenter-messageboard.designsafe-ci.org/smf/index.php?board=17.0");
    w.setFeedbackURL(messageBoardURL);

    // Move remote interface to a thread
    QThread *thread = new QThread(); 
    theRemoteService->moveToThread(thread); 
    QWidget::connect(thread, SIGNAL(finished()), theRemoteService, SLOT(deleteLater()));
    QWidget::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();


    // Show the main window, set styles & start the event loop
    w.show();
    w.statusBar()->showMessage("Ready", 5000);


#ifdef Q_OS_WIN
#define STYLESHEET ":/styleCommon/stylesheetWIN.qss"
    QFile file(":/styleCommon/stylesheetWIN.qss");
#endif

#ifdef Q_OS_MACOS
#define STYLESHEET ":/styleCommon/stylesheetMAC.qss"
    QFile file(":/styleCommon/stylesheetMAC.qss");
#endif

#ifdef Q_OS_LINUX
#define STYLESHEET ":/styleCommon/stylesheetLinux.qss"
    // QFile file(":/styleCommon/stylesheetMAC.qss");
    QFile file(":/styleCommon/stylesheetLinux.qss");
#endif

#ifdef Q_OS_UNIX
#ifndef Q_OS_LINUX
#ifndef Q_OS_MACOS
#define STYLESHEET ":/styleCommon/stylesheetLinux.qss"
    // QFile file(":/styleCommon/stylesheetMAC.qss");
    QFile file(":/styleCommon/stylesheetLinux.qss");
#endif
#endif
#endif

#ifndef STYLESHEET
#define STYLESHEET ":/styleCommon/stylesheetLinux.qss"
    QFile file(":/styleCommon/stylesheetLinux.qss");
#endif


    // Show error message
    if(file.open(QFile::ReadOnly)) {
        a.setStyleSheet(file.readAll());
        file.close();
    } else {
        qDebug() << "could not open stylesheet";
    }

    /* ***************************************************************** 
    //Setting Google Analytics Tracking Information
    GoogleAnalytics::SetMeasurementId("G-MC7SGPGWVQ");
    GoogleAnalytics::SetAPISecret("LrEiuSuaSqeh_v1928odog");
    GoogleAnalytics::CreateSessionId();
    GoogleAnalytics::StartSession();

    // Opening a QWebEngineView and using github to get app geographic usage
    QWebEngineView view;
    view.setUrl(QUrl("https://nheri-simcenter.github.io/HydroUQ/GA4.html"));
    view.resize(1024, 750);
    view.show();
    view.hide();
    ******************************************************************* */
    
    // Result of execution
    int res = a.exec();

    // On done with event loop, logout & stop the thread
    theRemoteService->logout();
    thread->quit();

    // Close Google Analytics session
    GoogleAnalytics::EndSession();

    // Complete
    return res;
}

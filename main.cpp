// Written: fmckenna
// Modified: Ajay B Harish (Feb 2021)
// Purpose: the typical Qt main for running a QMainWindow

// Include headers
#include <MainWindowWorkflowApp.h>
#include <QApplication>
#include <QFile>
#include <QThread>
#include <QObject>

#include <AgaveCurl.h>
#include <WorkflowAppHydroUQ.h>
#include <QCoreApplication>

#include <QApplication>
#include <QFile>
#include <QTime>
#include <QTextStream>
#include <GoogleAnalytics.h>
#include <QOpenGLWidget>
#include <QStandardPaths>
#include <QDir>
#include <QStatusBar>

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

#ifdef Q_OS_WIN
    QApplication::setAttribute(Qt::AA_UseOpenGLES);
#endif

    //Setting Core Application Name, Organization, Version and Google Analytics Tracking Id
    QCoreApplication::setApplicationName("HydroUQ");
    QCoreApplication::setOrganizationName("SimCenter");
    QCoreApplication::setApplicationVersion("1.0.0");

    // GoogleAnalytics::SetTrackingId("UA-178848988-1");
    GoogleAnalytics::StartSession();
    GoogleAnalytics::ReportStart();

    //Init resources from static libraries (e.g. SimCenterCommonQt or s3hark)
    // Q_INIT_RESOURCE(images1);
    Q_INIT_RESOURCE(Resources);

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

    // remove old log file
    QFile debugFile(logFilePath);
    debugFile.remove();

    //  check if the app is run in Qt Creator
    QByteArray envVar = qgetenv("QTDIR");

    if (envVar.isEmpty())
        logToFile = true;

    qInstallMessageHandler(customMessageOutput);

    //
    // window scaling
    //

    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    /******************  code to reset openGL version .. keep around in case need again
    QSurfaceFormat glFormat;
    glFormat.setVersion(3, 3);
    glFormat.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(glFormat);
    ***********************************************************************************/

    // regular Qt startup
    QApplication a(argc, argv);

    // create a remote interface
    QString tenant("designsafe");
    QString storage("agave://designsafe.storage.default/");
    QString dirName("Hydro-UQ");
    AgaveCurl *theRemoteService = new AgaveCurl(tenant, storage, &dirName);


    // create the main window
    WorkflowAppWidget *theInputApp = new WorkflowAppHydroUQ(theRemoteService);
    MainWindowWorkflowApp w(QString("Hydro-UQ: Response during water wave loading"), theInputApp, theRemoteService);

    // About the application
    QString aboutTitle = "About the SimCenter Hydro-UQ Application"; // this is the title displayed in the on About dialog
    QString aboutSource = ":/resources/docs/textAboutHydroUQ.html";  // this is an HTML file stored under resources
    w.setAbout(aboutTitle, aboutSource);

    // Version
    QString version("Version 1.0.0");
    w.setVersion(version);

    // Citation
    QString citeText("Ajay B Harish, & Frank McKenna. (2021, March 31). NHERI-SimCenter/Hydro-UQ: Version 1.0.0 (Version v1.0.0). Zenodo. http://doi.org/to-be-added");
    w.setCite(citeText);

    // Link to repository
    QString manualURL("https://nheri-simcenter.github.io/HydroUQ/");
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
    QFile file(":/styleCommon/stylesheetWIN.qss");
#endif

#ifdef Q_OS_MACOS
    QFile file(":/styleCommon/stylesheetMAC.qss");
#endif

#ifdef Q_OS_LINUX
    QFile file(":/styleCommon/stylesheetMAC.qss");
#endif


    // Show error message
    if(file.open(QFile::ReadOnly)) {
        a.setStyleSheet(file.readAll());
        file.close();
    } else {
        qDebug() << "could not open stylesheet";
    }

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

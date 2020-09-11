#include "mainwindow.h"

#include <QApplication>
#include <QCoreApplication>
#include <QStandardPaths>
#include <QTextStream>
#include <GoogleAnalytics.h>

#include "tapis/AgaveCurl.h"

static QString logFilePath;
static bool logToFile = false;


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
        ts << txt << endl;
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

    QCoreApplication::setApplicationName("HydroUQ");
    QCoreApplication::setOrganizationName("SimCenter");
    QCoreApplication::setApplicationVersion("2.1.0");
    //GoogleAnalytics::SetTrackingId("UA-126303135-1");
    GoogleAnalytics::StartSession();
    GoogleAnalytics::ReportStart();


    //
    // set up logging of output messages for user debugging
    //

    logFilePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
      + QDir::separator() + QCoreApplication::applicationName();

    // make sure tool dir exists in Documentss folder
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

    QByteArray envVar = qgetenv("QTDIR");       //  check if the app is run in Qt Creator

    if (envVar.isEmpty())
        logToFile = true;

    qInstallMessageHandler(customMessageOutput);

    //
    // window scaling
    //

    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    //
    // regular Qt startup
    //    

    QApplication a(argc, argv);


    QString tenant("designsafe");
    QString storage("agave://designsafe.storage.default/");
    QString dirName("HydroUQ");

    AgaveCurl *theRemoteService = new AgaveCurl(tenant, storage, &dirName);

    // Add styles
    #ifdef Q_OS_WIN
        QFile file(":/styles/styles/stylesheetWIN.qss");
    #endif

    #ifdef Q_OS_MACOS
        QFile file(":/styles/styles/stylesheetMAC.qss");
    #endif

    #ifdef Q_OS_LINUX
        QFile file(":/styles/styles/stylesheetMAC.qss");
    #endif
    // QFile file(":/style/styles/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    a.setStyleSheet(styleSheet);

    MainWindow w(theRemoteService);
    w.show();
    return a.exec();

    GoogleAnalytics::EndSession();
    delete theRemoteService;

}

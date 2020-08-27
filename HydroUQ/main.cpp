#include "mainwindow.h"

#include <QApplication>
#include <QCoreApplication>
#include <GoogleAnalytics.h>
#include "tapis/AgaveCurl.h"


int main(int argc, char *argv[])
{

    QCoreApplication::setApplicationName("HydroUQ");
    QCoreApplication::setOrganizationName("SimCenter");
    QCoreApplication::setApplicationVersion("2.1.0");
    //GoogleAnalytics::SetTrackingId("UA-126303135-1");
    GoogleAnalytics::StartSession();
    GoogleAnalytics::ReportStart();


    QApplication a(argc, argv);


    QString tenant("designsafe");
    QString storage("agave://designsafe.storage.default/");
    QString dirName("EE-UQ");

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
}

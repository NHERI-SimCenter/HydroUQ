#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

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

    MainWindow w;
    w.show();
    return a.exec();
}

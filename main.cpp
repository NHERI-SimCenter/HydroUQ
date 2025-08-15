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
#include <QMessageBox>
#include <QString>
#include <QScreen>
#include <QSplashScreen>
#include <QGraphicsDropShadowEffect>
#include <QColor>
#include <QPixmap>
#include <QTimer>
#include <QTime>
#include <QPropertyAnimation>
#include <QGuiApplication>
#include <QCursor>
#include <QFont>
#include <QPainter>
#include <QTextStream>
#include <QOpenGLWidget>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include <QPushButton>

#include <GoogleAnalytics.h>

#include <QStatusBar>
#include <QWebEngineView>
#include <Utils/FileOperations.h>

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
static QString logFilePath;
static bool logToFile = false;

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


static QPixmap withTransparentBorder(const QPixmap& src, int padding)
{
    // Create a larger transparent pixmap and draw the original centered
    QPixmap padded(src.size() + QSize(padding * 2, padding * 2));
    padded.fill(Qt::transparent);
    QPainter p(&padded);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.drawPixmap(padding, padding, src);
    p.end();
    return padded;
}


static QSplashScreen* createSplashWithShadow(const QPixmap& src, int padding = 24)
{
    QPixmap pm = withTransparentBorder(src, padding);

    auto *splash = new QSplashScreen(pm);
    splash->setWindowFlag(Qt::FramelessWindowHint, true);
    splash->setWindowFlag(Qt::WindowStaysOnTopHint, true);
    splash->setAttribute(Qt::WA_TranslucentBackground, true);
    splash->setStyleSheet("QSplashScreen { background: transparent; }");

    // Shadow
    auto *shadow = new QGraphicsDropShadowEffect(splash);
    shadow->setBlurRadius(30); // softness
    shadow->setOffset(8, 8);
    shadow->setColor(QColor(0, 0, 0, 140)); // semi-transparent black
    splash->setGraphicsEffect(shadow);

    // Center on the active screen
    QScreen *screen = QGuiApplication::screenAt(QCursor::pos());
    if (!screen) screen = QGuiApplication::primaryScreen();
    QRect sr = screen->geometry();
    splash->move(sr.center() - splash->rect().center());

    return splash;
}


static void fadeOutSplashAndShowMain(QSplashScreen* splash, QWidget* mainWin) {
    // Keep the splash above everything during the fade
    splash->setWindowFlag(Qt::WindowStaysOnTopHint, true);
    splash->raise();

    // Some platforms (e.g., Wayland) ignore QWidget::setWindowOpacity.
    // Detect support by trying one step; if it doesn't stick, use opacity effect.
    auto supportsWindowOpacity = [&]() -> bool {
        const qreal orig = splash->windowOpacity();
        splash->setWindowOpacity(0.99);
        const bool ok = qFuzzyCompare(splash->windowOpacity(), 0.99);
        splash->setWindowOpacity(orig);
        return ok;
    };

    auto showMainAndCloseSplash = [=]() {
        // Now bring up the main window
        mainWin->show();
        // Close/remove splash AFTER main window is visible
        splash->close();
        splash->deleteLater();
    };

    if (supportsWindowOpacity()) {
        // Fade the actual window
        auto *fade = new QPropertyAnimation(splash, "windowOpacity", splash);
        fade->setDuration(500);
        fade->setStartValue(1.0);
        fade->setEndValue(0.0);
        QObject::connect(fade, &QPropertyAnimation::finished, splash, showMainAndCloseSplash);
        fade->start(QAbstractAnimation::DeleteWhenStopped);
    } else {
        // Fallback: fade the content with a graphics effect (works on Wayland)
        auto *eff = new QGraphicsOpacityEffect(splash);
        splash->setGraphicsEffect(eff);
        auto *fade = new QPropertyAnimation(eff, "opacity", splash);
        fade->setDuration(500);
        fade->setStartValue(1.0);
        fade->setEndValue(0.0);
        QObject::connect(fade, &QPropertyAnimation::finished, splash, showMainAndCloseSplash);
        fade->start(QAbstractAnimation::DeleteWhenStopped);
    }
}


int main(int argc, char *argv[])
{

// Extensive documentation on how to set up OpenGL on Windows, macOS, and Linux can be found at:
// https://doc.qt.io/qt-5/windows-requirements.html
#ifdef Q_OS_WIN
  //QApplication::setAttribute(Qt::AA_UseOpenGLES); // Use ANGLE on Windows
  QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
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
    QCoreApplication::setApplicationVersion("4.1.0");

    //Init resources from static libraries (e.g. SimCenterCommonQt or s3hark)
    Q_INIT_RESOURCE(images);
    Q_INIT_RESOURCE(images1);
    // Q_INIT_RESOURCE(resources);
    // Q_INIT_RESOURCE(Resources);

    //
    // Set up logging of output messages for user debugging
    //

    // full path to debug.log file    
    logFilePath = SCUtils::getAppWorkDir();
    logFilePath = logFilePath + QDir::separator() + QString("debug.log");

    // remove old log file
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

    QByteArray envVar = qgetenv("QTDIR");       //  check if the app is run in Qt Creator

    if (envVar.isEmpty())
        logToFile = true;

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

    // Splash screen to show when opening app (i.e., shows the app logo to look professional)
    QPixmap pixmap(":/icons/NHERI-HydroUQ-Splash.png"); // Replace with your image path
    QSplashScreen *splash = createSplashWithShadow(pixmap, 24); // Create splash with shadow and padding
    
    QFont f = splash->font();
    f.setPointSize(18);  // make it bigger
    f.setBold(true);     // optional
    splash->setFont(f);

    splash->show();
    a.processEvents(); // ensure it paints immediately
    


    // Show first message
    splash->showMessage("Launching HydroUQ...", Qt::AlignLeft | Qt::AlignBottom, Qt::black);

    // Optional: wait cursor during startup
    // QApplication::setOverrideCursor(Qt::WaitCursor);

    // regular Qt startup
    // QApplication a(argc, argv);

    QTimer::singleShot(250, splash, [=]() {
        splash->showMessage("Configuring remote services...", Qt::AlignLeft | Qt::AlignBottom, Qt::black);
    });

    // create a remote interface
    QString tenant("designsafe");
    QString storage("designsafe.storage.default/");        
    QString dirName("HydroUQ"); // this is the default directory for the application
    TapisV3 *theRemoteService = new TapisV3(tenant, storage, &dirName);        

    QTimer::singleShot(250, splash, [=]() {
        splash->showMessage("Initializing application components...", Qt::AlignLeft | Qt::AlignBottom, Qt::black);
    });

    // create the main window
    WorkflowAppWidget *theInputApp = new WorkflowAppHydroUQ(theRemoteService);
    MainWindowWorkflowApp w(QString("HydroUQ: Water-borne Hazards Engineering with Uncertainty Quantification"), theInputApp, theRemoteService);

    QTimer::singleShot(250, splash, [=]() {
        splash->showMessage("Linking components into workflow...", Qt::AlignLeft | Qt::AlignBottom, Qt::black);
    });

    // About the application
    QString aboutTitle = "About the SimCenter HydroUQ Application"; // this is the title displayed in the on About dialog
    QString aboutSource = ":/resources/docs/textAboutHydroUQ.html";  // this is an HTML file stored under resources
    w.setAbout(aboutTitle, aboutSource);

    // Version
    QString version = QString("Version ") + QCoreApplication::applicationVersion();
    w.setVersion(version);

    // Citation
    QString citeText("1) Justin Bonus, Frank McKenna, Nicolette Lewis, Ajay B Harish, & Pedro, Arduino (2025). NHERI-SimCenter/HydroUQ: Version 4.1.0 (v4.1.0). Zenodo. https://doi.org/10.5281/zenodo.15319477  \n\n2) Gregory G. Deierlein, Frank McKenna, Adam Zsarnóczay, Tracy Kijewski-Correa, Ahsan Kareem, Wael Elhaddad, Laura Lowes, Matthew J. Schoettler, and Sanjay Govindjee (2020) A Cloud-Enabled Application Framework for Simulating Regional-Scale Impacts of Natural Hazards on the Built Environment. Frontiers in the Built Environment. 6:558706. doi: 10.3389/fbuil.2020.558706");
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


    QObject::connect(thread, SIGNAL(started()), theRemoteService, SLOT(process()));
    QObject::connect(theRemoteService, SIGNAL(finished()), thread, SLOT(quit())); 
    QObject::connect(theRemoteService, SIGNAL(finished()), theRemoteService, SLOT(deleteLater())); // ? is finished() a signal of theRemoteService?
    // QObject::connect(thread, SIGNAL(finished()), theRemoteService, SLOT(deleteLater())); 
    QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();

    
    //
    // Show the main window, set styles & start the event loop
    //
    
    // https://www.qtcentre.org/threads/62377-Best-place-for-setting-stylesheet
	// Moving this to the place after MainWindow creation fixes unwanted padding,
	// but may produce really weird results on Mac OS X when styling combobox drop-down area.
    // w.show();
    // w.statusBar()->showMessage("Ready", startupDelay);
    
    QTimer::singleShot(250, splash, [=]() {
        splash->showMessage("Setting up user interface...", Qt::AlignLeft | Qt::AlignBottom, Qt::black);
    });
    
#ifdef Q_OS_WIN
    QFile file(":/styleCommon/stylesheetWIN.qss");
#endif

#ifdef Q_OS_MACOS
    QFile file(":/styleCommon/stylesheetMAC.qss");
#endif

#ifdef Q_OS_LINUX
    QFile file(":/styleCommon/stylesheetLinux.qss");
#endif

    if (file.open(QFile::ReadOnly)) {
        a.setStyleSheet(file.readAll());
        qDebug() << "Stylesheet loaded: " << file.fileName();
        file.close();
    } else {
        qDebug() << "Could not open stylesheet: " << file.fileName();
    }

    // QApplication::restoreOverrideCursor();


    auto windowPointer = &w; // Capture the main window pointer for later use
    fadeOutSplashAndShowMain(splash, windowPointer);
    QTimer::singleShot(750, &w, &QWidget::show); // Show main window after x milliseconds
    // w.show();

    constexpr int startupDelay = 5000; // milliseconds
    w.statusBar()->showMessage("Ready", startupDelay);


#ifdef _SC_RELEASE

    //Setting Google Analytics Tracking Information
    qDebug() << "HydroUQ -- running Release Build";
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

#endif


#ifdef _ANALYTICS

    //Setting Google Analytics Tracking Information
    qDebug() << "compiled with: ANALYTICS";    
    GoogleAnalytics::SetMeasurementId("G-MC7SGPGWVQ");
    GoogleAnalytics::SetAPISecret("LrEiuSuaSqeh_v1928odog");
    GoogleAnalytics::CreateSessionId();
    GoogleAnalytics::StartSession();

#endif    
    
    // Result of execution
    int res = a.exec();

#ifdef _GA_AFTER

    // Opening a QWebEngineView and using github to get app geographic usage 
    qDebug() << "compiled with: GA_AFTER";   
    QWebEngineView view;
    view.setUrl(QUrl("https://nheri-simcenter.github.io/HydroUQ/GA4.html"));
    view.resize(1024, 750);
    view.show();
    view.hide();

#endif    
    
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

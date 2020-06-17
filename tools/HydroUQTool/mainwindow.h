#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "dependencies/rapidjson/document.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    std::string gettoolname();

protected:
    //std::string toolname = "H20-UQ";

private:
    Ui::MainWindow *ui;
    std::string toolname = "H20-UQ";


};
#endif // MAINWINDOW_H

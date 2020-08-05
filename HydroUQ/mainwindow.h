#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMap>
#include <QTreeWidget>
#include <QInputDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_SimOptions_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    void clearAllData(void);
    void initialize();
    void refresh_projsettings();

    Ui::MainWindow *ui;
    QMap<int, QMap<QString, QString>*> allData;
    QMap<QString, QString> allData2;

    int oldsimtype,simtype; // Simulation type
    QStringList optiontree; // Tree widget names
};
#endif // MAINWINDOW_H

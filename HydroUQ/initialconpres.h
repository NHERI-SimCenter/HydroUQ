#ifndef INITIALCONPRES_H
#define INITIALCONPRES_H

#include <QFrame>

namespace Ui {
class initialconPres;
}

class initialconPres : public QFrame
{
    Q_OBJECT

public:
    explicit initialconPres(int, QWidget *parent = nullptr);
    ~initialconPres();
    bool getData(QMap<QString, QString>&, int);
    void refreshData(int);

private slots:
    void on_Btn_AddRegion_clicked();
    void on_Btn_RemRegion_clicked();

private:
    void hideshowelems(int);
    Ui::initialconPres *ui;
};

#endif // INITIALCONPRES_H

#ifndef INITIALCONVEL_H
#define INITIALCONVEL_H

#include <QFrame>

namespace Ui {
class initialconVel;
}

class initialconVel : public QFrame
{
    Q_OBJECT

public:
    explicit initialconVel(int, QWidget *parent = nullptr);
    ~initialconVel();
    bool getData(QMap<QString, QString>&, int);

private slots:
    void on_Btn_AddRegion_clicked();
    void on_Btn_RemRegion_clicked();

private:
    void hideshowelems(int);
    Ui::initialconVel *ui;
};

#endif // INITIALCONVEL_H

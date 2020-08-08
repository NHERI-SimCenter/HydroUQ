#ifndef INITIALCONALPHA_H
#define INITIALCONALPHA_H

#include <QFrame>

namespace Ui {
class initialconAlpha;
}

class initialconAlpha : public QFrame
{
    Q_OBJECT

public:
    explicit initialconAlpha(int, QWidget *parent = nullptr);
    ~initialconAlpha();
    bool getData(QMap<QString, QString>&, int);
    void refreshData(int);

private slots:
    void on_Btn_AddRegion_clicked();
    void on_Btn_RemRegion_clicked();

private:
    void hideshowelems(int);
    Ui::initialconAlpha *ui;
};

#endif // INITIALCONALPHA_H

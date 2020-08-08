#ifndef FLOATINGBDS_H
#define FLOATINGBDS_H

#include <QFrame>

namespace Ui {
class floatingbds;
}

class floatingbds : public QFrame
{
    Q_OBJECT

public:
    explicit floatingbds(int, QWidget *parent = nullptr);
    ~floatingbds();
    bool getData(QMap<QString, QString>&,int);
    void refreshData(int);

private:
    void hideshowelems(int);
    Ui::floatingbds *ui;
};

#endif // FLOATINGBDS_H

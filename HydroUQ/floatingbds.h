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
    explicit floatingbds(QWidget *parent = nullptr);
    ~floatingbds();

private:
    Ui::floatingbds *ui;
};

#endif // FLOATINGBDS_H

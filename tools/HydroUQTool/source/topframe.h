#ifndef TOPFRAME_H
#define TOPFRAME_H

#include <QFrame>

namespace Ui {
class TopFrame;
}

class TopFrame : public QFrame
{
    Q_OBJECT

public:
    explicit TopFrame(QWidget *parent = nullptr);
    ~TopFrame();

private:
    Ui::TopFrame *ui;
};

#endif // TOPFRAME_H

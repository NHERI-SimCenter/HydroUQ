#ifndef BOTTOMFRAME_H
#define BOTTOMFRAME_H

#include <QFrame>

namespace Ui {
class BottomFrame;
}

class BottomFrame : public QFrame
{
    Q_OBJECT

public:
    explicit BottomFrame(QWidget *parent = nullptr);
    ~BottomFrame();

private:
    Ui::BottomFrame *ui;
};

#endif // BOTTOMFRAME_H

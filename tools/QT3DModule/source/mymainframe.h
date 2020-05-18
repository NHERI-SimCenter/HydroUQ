#ifndef MYMAINFRAME_H
#define MYMAINFRAME_H

#include <QFrame>

namespace Ui {
class MyMainFrame;
}

class MyMainFrame : public QFrame
{
    Q_OBJECT

public:
    explicit MyMainFrame(QWidget *parent = nullptr);
    ~MyMainFrame();

private:
    Ui::MyMainFrame *ui;
};

#endif // MYMAINFRAME_H

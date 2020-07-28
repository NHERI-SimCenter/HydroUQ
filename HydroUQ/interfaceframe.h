#ifndef INTERFACEFRAME_H
#define INTERFACEFRAME_H

#include <QFrame>

namespace Ui {
class InterfaceFrame;
}

class InterfaceFrame : public QFrame
{
    Q_OBJECT

public:
    explicit InterfaceFrame(const QString, QWidget *parent = nullptr);
    ~InterfaceFrame();

private:
    Ui::InterfaceFrame *ui;
};

#endif // INTERFACEFRAME_H

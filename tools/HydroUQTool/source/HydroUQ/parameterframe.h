#ifndef PARAMETERFRAME_H
#define PARAMETERFRAME_H

#include <QFrame>

namespace Ui {
class ParameterFrame;
}

class ParameterFrame : public QFrame
{
    Q_OBJECT

public:
    explicit ParameterFrame(QWidget *parent = nullptr);
    ~ParameterFrame();

private:
    Ui::ParameterFrame *ui;
};

#endif // PARAMETERFRAME_H

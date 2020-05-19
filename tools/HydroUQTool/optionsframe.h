#ifndef OPTIONSFRAME_H
#define OPTIONSFRAME_H

#include <QFrame>

namespace Ui {
class OptionsFrame;
}

class OptionsFrame : public QFrame
{
    Q_OBJECT

public:
    explicit OptionsFrame(QWidget *parent = nullptr);
    ~OptionsFrame();

private:
    Ui::OptionsFrame *ui;
};

#endif // OPTIONSFRAME_H

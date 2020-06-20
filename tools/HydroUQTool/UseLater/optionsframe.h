#ifndef OPTIONSFRAME_H
#define OPTIONSFRAME_H

#include <QFrame>
#include <QDebug>

namespace Ui {
class OptionsFrame;
}

class OptionsFrame : public QFrame
{
    Q_OBJECT

public:
    explicit OptionsFrame(QWidget *parent = nullptr);
    ~OptionsFrame();

public slots:
    void Listen();

private slots:
    void on_But_GenFiles_clicked();

    void on_But_AA_WDir_clicked();

private:
    Ui::OptionsFrame *ui;
};

#endif // OPTIONSFRAME_H

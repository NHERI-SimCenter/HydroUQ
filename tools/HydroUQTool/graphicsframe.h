#ifndef GRAPHICSFRAME_H
#define GRAPHICSFRAME_H

#include <QFrame>

namespace Ui {
class GraphicsFrame;
}

class GraphicsFrame : public QFrame
{
    Q_OBJECT

public:
    explicit GraphicsFrame(QWidget *parent = nullptr);
    ~GraphicsFrame();

private:
    Ui::GraphicsFrame *ui;
};

#endif // GRAPHICSFRAME_H

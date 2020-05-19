#include "graphicsframe.h"
#include "ui_graphicsframe.h"

GraphicsFrame::GraphicsFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::GraphicsFrame)
{
    ui->setupUi(this);
}

GraphicsFrame::~GraphicsFrame()
{
    delete ui;
}

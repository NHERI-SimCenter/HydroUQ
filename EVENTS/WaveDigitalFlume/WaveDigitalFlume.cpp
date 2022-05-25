#include "WaveDigitalFlume.h"
#include "ui_WaveDigitalFlume.h"

WaveDigitalFlume::WaveDigitalFlume(RandomVariablesContainer *theRV, QWidget *parent)
    : SimCenterAppWidget(parent), theRemoteService(NULL)
    , ui(new Ui::WaveDigitalFlume)
{
    ui->setupUi(this);
}

WaveDigitalFlume::~WaveDigitalFlume()
{
    delete ui;
}

#include "floatingbds.h"
#include "ui_floatingbds.h"

//*********************************************************************************
// Floating body settings
//*********************************************************************************
floatingbds::floatingbds(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::floatingbds)
{
    ui->setupUi(this);
}

//*********************************************************************************
// Delete floating body settings
//*********************************************************************************
floatingbds::~floatingbds()
{
    delete ui;
}

//*********************************************************************************
// Refresh floating body settings
//*********************************************************************************
void floatingbds::refreshData(int type)
{
    // Initialize to show / hide elements
    hideshowelems(type);
}

//*********************************************************************************
// Show - hide elements
//*********************************************************************************
void floatingbds::hideshowelems(int type)
{

}

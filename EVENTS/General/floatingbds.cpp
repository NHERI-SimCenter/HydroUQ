#include "floatingbds.h"
#include "ui_floatingbds.h"

//*********************************************************************************
// Floating body settings
//*********************************************************************************
floatingbds::floatingbds(int type, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::floatingbds)
{
    ui->setupUi(this);

    // Initialize to show / hide elements
    hideshowelems(type);
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
    (void) type;
}


//*********************************************************************************
// Get data from floating bodies
//*********************************************************************************
bool floatingbds::getData(QMap<QString, QString>& map, int type)
{
    bool hasData=false;
    (void) type;
    (void) map;

    // Return the bool
    return hasData;
}

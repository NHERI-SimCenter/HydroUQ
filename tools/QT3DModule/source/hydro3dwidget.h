#ifndef HYDRO3DWIDGET_H
#define HYDRO3DWIDGET_H

#include <QWidget>

class Hydro3DWidget : public QWidget
{
public:
    Hydro3DWidget(QWidget *parent = nullptr);

private:
    void initUI(void);
};

#endif // HYDRO3DWIDGET_H

#ifndef QT3DFRAME_H
#define QT3DFRAME_H

#include <QWidget>

class QT3DFrame : public QWidget
{
    Q_OBJECT
public:
    explicit QT3DFrame(QWidget *parent = nullptr);

private:
    void initUI(void);

};

#endif // QT3DFRAME_H

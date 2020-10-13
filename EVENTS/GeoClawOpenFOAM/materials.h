#ifndef MATERIALS_H
#define MATERIALS_H

#include <QFrame>

namespace Ui {
class materials;
}

class materials : public QFrame
{
    Q_OBJECT

public:
    explicit materials(int, QWidget *parent = nullptr);
    ~materials();
    bool getData(QMap<QString, QString>&,int);
    void refreshData(int);

private:
    void hideshowelems(int);
    Ui::materials *ui;
};

#endif // MATERIALS_H

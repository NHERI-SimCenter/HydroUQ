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
    explicit materials(QWidget *parent = nullptr);
    ~materials();
    bool getData(QMap<QString, QString>&);
    void refreshData(int);

private:
    Ui::materials *ui;
};

#endif // MATERIALS_H

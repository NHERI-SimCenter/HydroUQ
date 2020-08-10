#ifndef BOUNDARYDATA_H
#define BOUNDARYDATA_H

#include <QFrame>

namespace Ui {
class boundaryData;
}

class boundaryData : public QFrame
{
    Q_OBJECT

public:
    explicit boundaryData(const QString, QWidget *parent = nullptr);
    ~boundaryData();

private slots:
    void on_Cmb_UBC_currentIndexChanged(int index);
    void on_Cmb_PresBC_currentIndexChanged(int index);

private:
    void hideshowelems();
    Ui::boundaryData *ui;
};

#endif // BOUNDARYDATA_H

#ifndef POSTPROCESS_H
#define POSTPROCESS_H

#include <QFrame>

namespace Ui {
class postprocess;
}

class postprocess : public QFrame
{
    Q_OBJECT

public:
    explicit postprocess(int, QWidget *parent = nullptr);
    ~postprocess();
    bool getData(QMap<QString, QString>&, int);
    void refreshData(int);

private slots:
    void on_CmB_Probelocation_currentIndexChanged(int index);
    void on_Btn_AddProbe_clicked();
    void on_Btn_RemProbe_clicked();

private:
    Ui::postprocess *ui;
    void hideshowelems(int);
    void hideshowelems2();
};

#endif // POSTPROCESS_H

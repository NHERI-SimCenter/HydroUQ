#ifndef SOLVER_H
#define SOLVER_H

#include <QFrame>

namespace Ui {
class solver;
}

class solver : public QFrame
{
    Q_OBJECT

public:
    explicit solver(QWidget *parent = nullptr);
    ~solver();
    bool getData(QMap<QString, QString>&);

private slots:
    void on_ChB_Restart_stateChanged(int arg1);

private:
    void hideshowelems();
    Ui::solver *ui;
    QStringList restartfilenames;
};

#endif // SOLVER_H

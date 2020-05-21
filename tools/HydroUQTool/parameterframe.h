#ifndef PARAMETERFRAME_H
#define PARAMETERFRAME_H

#include <QFrame>
#include <QTreeWidget>
#include "dependencies/Eigen/Dense"

namespace Ui {
class ParameterFrame;
}

class ParameterFrame : public QFrame
{
    Q_OBJECT

public:
    explicit ParameterFrame(QWidget *parent = nullptr);
    ~ParameterFrame();

private slots:

    // Item clicked on the sim options tree
    void on_SimOptions_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::ParameterFrame *ui;

    // Variables
    Eigen::MatrixXi optionmap;
};

#endif // PARAMETERFRAME_H

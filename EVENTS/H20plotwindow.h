#ifndef H20PLOTWINDOW_H
#define H20PLOTWINDOW_H

#include <QWidget>

namespace Ui {
class H20plotwindow;
}

class H20plotwindow : public QWidget
{
    Q_OBJECT

public:
    explicit H20plotwindow(QWidget *parent = nullptr);
    ~H20plotwindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::H20plotwindow *ui;
};

#endif // H20PLOTWINDOW_H

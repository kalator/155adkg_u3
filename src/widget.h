#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_del_button_clicked();

    void on_clear_button_clicked();

    void on_cont_button_clicked();

    void on_slope_button_clicked();

    void on_load_points_button_clicked();

    void on_aspect_button_clicked();

private:
    Ui::Widget *ui;
    double z_min, z_max;
};

#endif // WIDGET_H

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_clearButton_clicked()
{
    ui->canvas->clearCanvas();
}

void Widget::on_dtButton_clicked()
{
    ui->canvas->setDT();
}

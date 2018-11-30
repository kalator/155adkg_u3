#include "widget.h"
#include "ui_widget.h"

#include <vector>
#include <fstream>
#include <QtGui>


//#include "edge.h"
#include "algorithms.h"
#include "triangle.h"

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

void Widget::on_pushButton_clicked()
{
    std::vector<QPoint3D> points = ui->Canvas->getPoints();
    /*
    std::ofstream f ("test.fxt");
    for(QPoint3D p: points)
    {
        f << p.x() << "  " << p.y() <<'\n';
    }
    f.close();
    */
    std::vector<Edge> dt = Algorithms::DT(points);
    ui->Canvas->setDT(dt);
    repaint();
}

void Widget::on_pushButton_3_clicked()
{
    //Clear and repaint
    ui->Canvas->clearDT();
    repaint();
}

void Widget::on_pushButton_2_clicked()
{
    //Create contour lines
    std::vector<Edge> dt = ui->Canvas->getDT();
    std::vector<Edge> contours = Algorithms::createContours(dt, 0, 100, 5);
    ui->Canvas->setContours(contours);
    repaint();
}

void Widget::on_pushButton_4_clicked()
{
    //Analyze slope and aspect
    std::vector<Edge> dt = ui->Canvas->getDT();
    std::vector<Triangle> dtm = Algorithms::analyzeDTM(dt);
    ui->Canvas->setDTM(dtm);
    repaint();
}

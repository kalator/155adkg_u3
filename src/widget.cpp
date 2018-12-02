#include "widget.h"
#include "ui_widget.h"

#include <vector>
#include <fstream>
#include <QtGui>
#include <cmath>
#include <QPixmap>


//#include "edge.h"
#include "algorithms.h"
#include "triangle.h"
#include "sortpolbyzasc.h"

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

void Widget::on_trg_button_clicked()
{
    std::vector<QPoint3D> points = ui->Canvas->getPoints();
    if(points.size() < 3) return;
    /*
    std::ofstream f ("test.fxt");
    for(QPoint3D p: points)
    {
        f << p.x() << "  " << p.y() <<'\n';
    }
    f.close();
    */
    std::vector<Edge> dt = Algorithms::DT(points);
    std::vector<Triangle> dtm = Algorithms::analyzeDTM(dt);
    ui->Canvas->setDT(dt);
    ui->Canvas->setDTM(dtm);
    repaint();

    //set contour and slope and aspect buttons enabled
    if(!(ui->Canvas->getDT().empty()))
    {
        ui->cont_button->setEnabled(true);
        ui->slope_button->setEnabled(true);
        ui->aspect_button->setEnabled(true);
    }
}

void Widget::on_clear_button_clicked()
{
    //Clear and repaint
    ui->Canvas->clearDT();
    repaint();

    ui->trg_button->setEnabled(false);
    ui->cont_button->setEnabled(false);
    ui->slope_button->setEnabled(false);
    ui->aspect_button->setEnabled(false);
    ui->hyps_button->setEnabled(false);
    ui->pic->clear();
}

void Widget::on_cont_button_clicked()
{
    if(ui->step->text().toDouble() < 1) return;
    //Create contour lines
    std::vector<Edge> dt = ui->Canvas->getDT();
    std::vector<double> contour_heights;
    int step = ui->step->text().toDouble();

    int z_from = this->z_min;
    int z_to = this->z_max;
    z_from = z_from - z_from%step;
    z_to = z_to-z_to%step + step;

    //hypsometry
    std::vector<QPolygonFZ> hyps;

    std::vector<Edge> contours = Algorithms::createContours(dt, z_from, z_to, step, contour_heights, hyps);

    //sort hyps polygons by z
    std::sort(hyps.begin(), hyps.end(), SortPolByZAsc());

    bool draw_main = false;
    if(ui->main_contours->isChecked())
    {
        draw_main = true;
    }
    ui->Canvas->setContours(contours, contour_heights, step, draw_main, hyps);
    repaint();

    ui->hyps_button->setEnabled(true);
}

void Widget::on_slope_button_clicked()
{
    ui->Canvas->setDrawSlope();
    repaint();
}

void Widget::on_load_points_button_clicked()
{
    //get path to directory upper of build
    QDir current_path = QDir::currentPath();
    current_path.cdUp();
    QString path = current_path.path();

    //open file dialog
    QString point_path = QFileDialog::getOpenFileName(
                this,
                tr("Select file"),
                path,
                "Text file (*.txt);;All files (*.*)");

    //convert path from QString to string (change coding to utf8 for ifstream)
    std::string point_path_utf8 = point_path.toUtf8().constData();

    QSizeF canvas_size = ui->Canvas->size();

    ui->Canvas->loadPoints(point_path_utf8, canvas_size, this->z_min, this->z_max); //load
    repaint();

    //enable triangulation button
    if(!(ui->Canvas->getPoints().empty()))
        ui->trg_button->setEnabled(true);

    //disable analysis buttons
    ui->cont_button->setEnabled(false);
    ui->slope_button->setEnabled(false);
    ui->aspect_button->setEnabled(false);
    ui->pic->clear();
}

void Widget::on_aspect_button_clicked()
{
    ui->Canvas->setDrawAspect();


    //get path to directory upper of build
    QDir current_path = QDir::currentPath();
    current_path.cdUp();
    QString path = current_path.path();

    QPixmap pix(path + "/misc/asp_colors.gif");
    ui->pic->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio));

    repaint();
}

void Widget::on_hyps_button_clicked()
{
    ui->Canvas->drawHypsometry();
    repaint();
}

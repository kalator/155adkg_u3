#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "edge.h"
#include "qpoint3d.h"
#include "triangle.h"

class Draw : public QWidget
{
    Q_OBJECT
    private:
        std::vector<QPoint3D> points;     //List of points
        std::vector<Edge> dt;             //List of Delaunay edges
        std::vector<Edge> contours;       //List of contours
        std::vector<double> contour_heights; //List of contour heights
        std::vector<Triangle> dtm;
        bool draw_main;
        int step;

    public:
        explicit Draw(QWidget *parent = nullptr);
        void paintEvent(QPaintEvent *e);
        //void mousePressEvent(QMouseEvent *e);
        void clearPoints() {points.clear();}
        void clearDT();
        std::vector<QPoint3D> & getPoints(){return points;}
        std::vector<Edge> & getDT(){return dt;}
        void setDT(std::vector<Edge> &dt_){dt = dt_; contours.clear();}
        void setContours(std::vector<Edge> &contours_, std::vector<double> &contour_heights_, int step_, bool draw_main_)
        {contours = contours_; contour_heights = contour_heights_; step = step_; draw_main = draw_main_;}
        void setDTM(std::vector<Triangle> &dtm_){dtm = dtm_;}
        void loadPoints(std::string points_path, QSizeF &canvas_size, double &min_z, double &max_z);

    signals:

    public slots:

};

#endif // DRAW_H

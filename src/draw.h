#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "edge.h"
#include "qpoint3d.h"
#include "qpolygonfz.h"
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
        std::vector<QPolygonFZ> hyps; //List of hypsometry polygons
        bool draw_main;
        int step;
        bool draw_slope;
        bool draw_aspect;
        bool draw_hyps;
        std::vector<QColor> ctable; //table of colors for hypsometry

    public:
        explicit Draw(QWidget *parent = nullptr);
        void paintEvent(QPaintEvent *e);
        //void mousePressEvent(QMouseEvent *e);
        void clearPoints() {points.clear();}
        void clearDT();
        std::vector<QPoint3D> & getPoints(){return points;}
        std::vector<Edge> & getDT(){return dt;}
        void setDT(std::vector<Edge> &dt_){dt = dt_; contours.clear();}
        void setContours(std::vector<Edge> &contours_,
                         std::vector<double> &contour_heights_,
                         int step_,
                         bool draw_main_,
                         std::vector<QPolygonFZ> &hyps_);
        void setDTM(std::vector<Triangle> &dtm_){dtm = dtm_;}
        void loadPoints(std::string points_path, QSizeF &canvas_size, double &min_z, double &max_z);
        void setDrawSlope(){this->draw_slope = !this->draw_slope; this->draw_aspect = false; this->draw_hyps = false;}
        void setDrawAspect(){this->draw_aspect = !this->draw_aspect; this->draw_slope = false; this->draw_hyps = false;}
        std::vector<QColor> genAspColors();
        void drawHypsometry();


    signals:

    public slots:

};

#endif // DRAW_H

#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <vector>
#include <QtGui>

#include "edge.h"
#include "algorithms.h"

class Draw : public QWidget
{
    Q_OBJECT
    private:
        std::vector<QPoint> points;     //List of points
        std::vector<Edge> dt;           //List of Delaunay edges

    public:
        explicit Draw(QWidget *parent = nullptr);
        void paintEvent(QPaintEvent *e);
        void mousePressEvent(QMouseEvent *e);
        void clearCanvas() {points.clear(); dt.clear();repaint();}
        std::vector<QPoint> & getPoints(){return points;}
        void setDT(){dt = Algorithms::DT(points); repaint();}

    signals:

    public slots:

};

#endif // DRAW_H

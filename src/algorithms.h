#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <QtGui>
#include <cmath>
#include <vector>
#include <list>

#include "edge.h"
#include "sortbyxasc.h"

//Point and line position
typedef enum{
    LEFT = 0,
    RIGHT,
    ON
} TPosition;

class Algorithms
{
public:
    Algorithms();
    static TPosition getPointLinePosition(QPoint &q, QPoint &a, QPoint &b);
    static double getCircleRadius(QPoint &p1, QPoint &p2, QPoint &p3, QPoint &c);
    static int getNearestPoint(QPoint &p, std::vector<QPoint> &points);
    static double distance(QPoint &p1, QPoint &p2);
    static int getDelaunayPoint(QPoint &s, QPoint &e, std::vector<QPoint> &points);
    static std::vector<Edge> DT(std::vector<QPoint> &points);

};


#endif // ALGORITHMS_H

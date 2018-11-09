#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <QtGui>
#include <cmath>

typedef enum{
    LEFT = 0,
    RIGHT = 1,
    ON = 2
} TPositon; //vyctovy typ

class Algorithms
{
public:
    Algorithms();
    static TPositon getPointLinePosition(QPointF &q, QPointF &a, QPointF &b);
    static double getCircleRadius(QPoint &p1, QPoint &p2, QPoint &p3);
};

#endif // ALGORITHMS_H

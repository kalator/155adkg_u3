#include "algorithms.h"

Algorithms::Algorithms()
{

}

TPositon Algorithms::getPointLinePosition(QPointF &q, QPointF &a, QPointF &b)
{
    double eps = 1.0e-10;

    //get vectors
    double ux = b.x() - a.x();
    double uy = b.y() - a.y();
    double vx = q.x() - a.x();
    double vy = q.y() - a.y();

    //get cross product
    double t = ux*vy - uy*vx;

    //point on the line - return -1
    if(fabs(t) < eps)
        return ON;

    //point in the left halfplane
    else if(t < 0)
        return LEFT;

    //point in the right halfplane
    else
        return RIGHT;
}

double Algorithms::getCircleRadius(QPoint &p1, QPoint &p2, QPoint &p3)
{
    double x1 = p1.x();
    double x2 = p2.x();
    double x3 = p3.x();

    double y1 = p1.y();
    double y2 = p2.y();
    double y3 = p3.y();

    double k1 = x1*x1+y1*y1;
    double k2 = x2*x2+y2*y2;
    double k3 = x3*x3+y3*y3;

    double k4 = y1 - y2;
    double k5 = y1 - y3;
    double k6 = y2 - y3;

    double k7 = x1 - x2;
    double k8 = x1 - x3;
    double k9 = x2 - x3;

    double k10 = x1 * x1;
    double k11 = x2 * x2;
    double k12 = x3 * x3;


    double m = 0.5 *(k12*(-k4)+k11*k5 - (k10+k4*k5)*k6)/(x3*(-k4)+x2*k5+x1*(-k6));

    double n = 0.5*(k1*(-k9)+k2*k8+k3*(-k7))/(y1*(-k9)+y2*k8+y3*(-k7));

    double r = sqrt((x1-m)*(x1-m)+(y1-n)*(y1-n));

    return r;

}

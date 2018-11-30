#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "qpoint3d.h"

class Triangle
{
private:
    QPoint3D p1, p2, p3;
    double slope, aspect;

public:
    Triangle(QPoint3D &p1_, QPoint3D &p2_, QPoint3D &p3_, double slope_, double aspect_):p1(p1_),p2(p2_),p3(p3_),slope(slope_),aspect(aspect_){}
    QPoint3D getP1(){return p1;}
    QPoint3D getP2(){return p2;}
    QPoint3D getP3(){return p3;}
    double getSlope(){return slope;}
    double getAspect(){return aspect;}
};

#endif // TRIANGLE_H

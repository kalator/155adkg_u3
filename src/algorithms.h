#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <QtGui>
#include <vector>
#include "edge.h"
#include "qpoint3d.h"
#include "triangle.h"

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
    static TPosition getPointLinePosition(QPoint3D &q, QPoint3D &a, QPoint3D &b);
    static double getCircleRadius(QPoint3D &p1, QPoint3D &p2, QPoint3D &p3, QPoint3D &c);
    static int getNearestPoint(QPoint3D &p, std::vector<QPoint3D> &points);
    static double distance(QPoint3D &p1, QPoint3D &p2);
    static int getDelaunayPoint(QPoint3D &s, QPoint3D &e, std::vector<QPoint3D> &points);
    static std::vector<Edge> DT(std::vector<QPoint3D> &points);
    static QPoint3D getContourPoint(QPoint3D &p1, QPoint3D &p2, double z);
    static std::vector<Edge> createContours(std::vector<Edge> &dt, double z_min, double z_max, double dz);
    static double getSlope(QPoint3D &p1, QPoint3D &p2, QPoint3D &p3);
    static double getAspect(QPoint3D &p1, QPoint3D &p2, QPoint3D &p3);
    static std::vector<Triangle> analyzeDTM(std::vector<Edge> &dt);

};

#endif // ALGORITHMS_H

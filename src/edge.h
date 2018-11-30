#ifndef EDGE_H
#define EDGE_H

#include "qpoint3d.h"


class Edge
{
private:
    QPoint3D s, e;
public:
    Edge(QPoint3D &start, QPoint3D &end):s(start),e(end){}
    QPoint3D & getS() {return s;}
    QPoint3D & getE() {return e;}
    void switchOr()
    {
        QPoint3D temp = s;
        s = e;
        e = temp;
    }

    bool operator == (const Edge &e_)
    {
        return ((s == e_.s)&&(e == e_.e));
    }

};

#endif // EDGE_H

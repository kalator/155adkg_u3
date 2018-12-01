#ifndef SORTBYXASC_H
#define SORTBYXASC_H

#include<QtGui>
#include "qpoint3d.h"

class SortByXAsc
{
public:
    SortByXAsc();

    bool operator()(QPoint3D &p1, QPoint3D &p2)
    {
        return (p1.x()<p2.x())||((p1.x()==p2.x())&&(p1.y()<p2.y()));
    }
};

#endif // SORTBYXASC_H

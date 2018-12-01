#ifndef SORTBYZASC_H
#define SORTBYZASC_H

#include<QtGui>
#include "qpoint3d.h"

class SortByZAsc
{
public:
    SortByZAsc();

    bool operator()(QPoint3D &p1, QPoint3D &p2)
    {
        if(p1.getZ() < p2.getZ()) return true;
        else if(p1.getZ() > p2.getZ()) return false;
        else if(p1.y() < p2.y()) return true;
        else if(p1.y() > p2.y()) return false;
        else if(p1.x() < p2.x()) return true;
        else if(p1.x() > p2.x()) return false;
        //return (p1.getZ()<p2.getZ())||((p1.getZ()==p2.getZ())&&(p1.y()<p2.y()))&&(p1.x()<p2.x()));
    }
};

#endif // SORTBYZASC_H

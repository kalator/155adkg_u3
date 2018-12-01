#ifndef SORTPOLBYZASC_H
#define SORTPOLBYZASC_H

#include<QtGui>
#include "qpolygonfz.h"

class SortPolByZAsc
{
public:
    SortPolByZAsc();

    bool operator()(QPolygonFZ &p1, QPolygonFZ &p2)
    {
        return (p1.getZ() <= p2.getZ());
    }
};

#endif // SORTPOLBYZASC_H

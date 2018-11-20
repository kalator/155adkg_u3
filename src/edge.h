#ifndef EDGE_H
#define EDGE_H

#include <QPoint>

class Edge
{
private:
    QPoint s, e;
public:
    Edge(QPoint &start, QPoint &end):s(start),e(end){}
    QPoint & getS() {return s;}
    QPoint & getE() {return e;}
    void switchOr()
    {
        QPoint temp = s;
        s = e;
        e = temp;
    }

    bool operator == (const Edge &e_)
    {
        return ((s == e_.s)&&(e == e_.e));
    }

};


#endif // EDGE_H

#ifndef QPOLYGONFZ_H
#define QPOLYGONFZ_H

#include <QtGui>

class QPolygonFZ : public QPolygonF
{
public:
    QPolygonFZ():QPolygonF(), z_mid(0){}
    QPolygonFZ(QPolygonF pol, double z_mid_): QPolygonF(pol), z_mid(z_mid_){}
    double getZ(){return z_mid;}
    void setZ(double z_mid_){z_mid = z_mid_;}

private:
    double z_mid;

};

#endif // QPOLYGONFZ_H

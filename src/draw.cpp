#include "draw.h"

Draw::Draw(QWidget *parent) : QWidget(parent)
{

}


void Draw::paintEvent(QPaintEvent *e)
{
   QPen pen_trg(QColor(255, 0, 0, 127), 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
   QPen pen_point(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
   QPainter painter(this);

   painter.setPen(pen_point);

   //Draw points
   for(unsigned int i = 0; i < points.size(); i++)
   {
       painter.drawPoint(points[i]);
       //painter.drawText(points[i].x() + 10, points[i].y() + 10, QString::number(i));
   }

   painter.setPen(pen_trg);

   //Draw Delaunay edges
   for(unsigned int i = 0; i < dt.size(); i++)
   {
       painter.drawLine(dt[i].getS(), dt[i].getE());
   }

   painter.end();
}

void Draw::mousePressEvent(QMouseEvent *e)
{
    QPoint p(e->x(), e->y());
    points.push_back(p);
    repaint();
}

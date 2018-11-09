#include "draw.h"

Draw::Draw(QWidget *parent) : QWidget(parent)
{

}

void Draw::paintEvent(QPaintEvent *e)
{
    QPen pen_trg(QColor(255, 0, 0, 127), 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_point(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    QPainter painter(this);

    //Draw points
    painter.setPen(pen_point);
    for(unsigned int i = 0; i < points.size(); i++)
    {
        painter.drawPoint(points[i]);
    }

}

void Draw::mousePressEvent(QMouseEvent *e)
{
    QPointF clicked_point(e->x(), e->y());
    points.push_back(clicked_point);
    repaint();
}

void Draw::clearCanvas()
{
    this->points.clear();
    repaint();
}

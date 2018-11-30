#include "draw.h"

#include <QtGui>

Draw::Draw(QWidget *parent) : QWidget(parent)
{
    srand((unsigned)time(0));
}

void Draw::paintEvent(QPaintEvent *e)
{
   QPainter painter(this);
   QPen cont_norm(Qt::black, 1);
   QPen cont_main(Qt::black, 3);
   QPen pen_points(Qt::blue, 3);
   QPen pen_dt(Qt::red, 1);

   //Draw Delaunay edges
   painter.setPen(pen_dt);
   for(int i = 0; i < dt.size(); i++)
   {
       painter.drawLine(dt[i].getS(), dt[i].getE());
   }

   //Draw points
   painter.setPen(pen_points);
   for(int i = 0; i < points.size(); i++)
   {
       painter.drawPoint(points[i].x(), points[i].y());
      // painter.drawText(points[i].x() + 10, points[i].y() + 10, QString::number(points[i].getZ()));
   }

   //Draw contour lines
   if(draw_main)
   {
       for(int i = 0; i < contours.size(); i++)
       {
           int h = contour_heights[i];
           if(!(h%(5*step)))
           {
               painter.setPen(cont_main);
           }
           else
           {
               painter.setPen(cont_norm);
           }

           painter.drawLine(contours[i].getS(), contours[i].getE());
       }
   }
   else
   {
       painter.setPen(cont_norm);
       for(int i = 0; i < contours.size(); i++)
       {
           painter.drawLine(contours[i].getS(), contours[i].getE());
       }
   }


   //Draw slope
   double c = 255.0/180;
   for(int i = 0; i < dtm.size(); i++)
   {
       //Get triangle and its vertices
       Triangle t = dtm[i];
       QPoint3D p1 = t.getP1();
       QPoint3D p2 = t.getP2();
       QPoint3D p3 = t.getP3();

       //Get slope and setthe brush
       int c_slope = c * t.getSlope();
       painter.setBrush(QColor(c_slope,c_slope,c_slope));

       //Create and drawthe  polygon
       QPolygon triangle;
       triangle.append(QPoint(p1.x(), p1.y()));
       triangle.append(QPoint(p2.x(), p2.y()));
       triangle.append(QPoint(p3.x(), p3.y()));

       painter.drawPolygon(triangle);
   }

   painter.end();
}

/*void Draw::mousePressEvent(QMouseEvent *e)
{
    //Add new point
    int z = (rand()%101);
    QPoint3D p(e->x(), e->y(), z);
    points.push_back(p);
    repaint();
}
*/

void Draw::clearDT()
{
    //Clear all
    points.clear();
    dt.clear();
    dtm.clear();
    contours.clear();
}

void Draw::loadPoints(std::string path, QSizeF &canvas_size, double &min_z, double &max_z)
{
    clearDT();
    std::ifstream points_file;
    points_file.open(path);

    //check if points_file is correctly open (or if it exists)
    if(!points_file.is_open())
    {
        return;
    }


    //go through file and load points into poly_pol (storing all polygons)
    double min_x = std::numeric_limits<double>::max();
    double min_y = std::numeric_limits<double>::max();
    min_z = std::numeric_limits<double>::max();
    double max_x = std::numeric_limits<double>::min();
    double max_y = std::numeric_limits<double>::min();
    max_z = std::numeric_limits<double>::min();

    while(points_file.good())
    {
        double x,y,z;
        points_file >> x;
        points_file >> y;
        points_file >> z;
        points.push_back(QPoint3D(x, y, z));
        if(x < min_x) min_x = x;
        if(x > max_x) max_x = x;
        if(y < min_y) min_y = y;
        if(y > max_y) max_y = y;
        if(z < min_z) min_z = z;
        if(z > max_z) max_z = z;
    }

    //scale points to canvas size
    double h = canvas_size.height();
    double w = canvas_size.width();

    double x_coef = w/(max_x-min_x);
    double y_coef = h/(max_y-min_y);

    for(int i = 0; i < points.size(); i++)
    {
        points[i].setX((points[i].x()-min_x)*x_coef);
        points[i].setY((points[i].y()-min_y)*y_coef);
    }
    points_file.close();
}


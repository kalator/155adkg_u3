#include "draw.h"
#include "sortpolbyzasc.h"

#include <QtGui>
#include <ctime>
#include <QDebug>

Draw::Draw(QWidget *parent) : QWidget(parent)
{
    srand((unsigned)time(0));
    this->draw_aspect = false;
    this->draw_slope = false;
    this->draw_hyps = false;

    //create list of colors from file
    //get path to directory upper of build
    QDir current_path = QDir::currentPath();
    current_path.cdUp();
    QString path = current_path.path();
    std::string path_utf8 = path.toUtf8().constData();

    std::ifstream col_file;
    col_file.open(path_utf8+"/misc/hyps.txt");

    //check if points_file is correctly open (or if it exists)
    if(!col_file.is_open())
    {
        return;
    }

    for(int i = 0; i < 256; i++)
    {
        double uid;
        int r,g,b;
        col_file >> uid;
        col_file >> r;
        col_file >> g;
        col_file >> b;
        this->ctable.push_back(QColor(r,g,b));
    }
}

void Draw::setContours(std::vector<Edge> &contours_,
                       std::vector<double> &contour_heights_,
                       int step_,
                       bool draw_main_,
                       std::vector<QPolygonFZ> &hyps_)
{
    contours = contours_;
    contour_heights = contour_heights_;
    step = step_;
    draw_main = draw_main_;
    hyps = hyps_;
}


void Draw::paintEvent(QPaintEvent *e)
{
   QPainter painter(this);
   QPen cont_norm(Qt::black, 1);
   QPen cont_main(Qt::black, 3);
   QPen pen_points(Qt::blue, 3);
   QPen pen_dt(Qt::red, 1);
   QPen pen_slope(Qt::black, 0);

   //Draw Delaunay edges
   painter.setPen(pen_dt);
   for(unsigned int i = 0; i < dt.size(); i++)
   {
       painter.drawLine(dt[i].getS(), dt[i].getE());
   }

   //Draw points
   painter.setPen(pen_points);
   for(unsigned int i = 0; i < points.size(); i++)
   {
       painter.drawPoint(points[i].x(), points[i].y());
      // painter.drawText(points[i].x() + 10, points[i].y() + 10, QString::number(points[i].getZ()));
   }

   //Draw contour lines
   if(draw_main)
   {
       for(unsigned int i = 0; i < contours.size(); i++)
       {
           int h = contour_heights[i];
           if(!(h%(5*step)))
           {
               painter.setPen(cont_main);

               double text_x = (contours[i].getS().x() + contours[i].getE().x())/2;
               double text_y = (contours[i].getS().y() + contours[i].getE().y())/2;
               painter.drawText(text_x, text_y, QString::number(h));
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
       for(unsigned int i = 0; i < contours.size(); i++)
       {
           painter.drawLine(contours[i].getS(), contours[i].getE());
       }
   }


   //Draw slope
   if(this->draw_slope)
   {
       double c = 255.0/180;
       for(unsigned int i = 0; i < dtm.size(); i++)
       {
           //Get triangle and its vertices
           Triangle t = dtm[i];
           QPoint3D p1 = t.getP1();
           QPoint3D p2 = t.getP2();
           QPoint3D p3 = t.getP3();

           //Get slope and set the brush
           int c_slope = c * t.getSlope();
           painter.setBrush(QColor(c_slope,c_slope,c_slope));
           painter.setPen(pen_slope);

           //Create and drawthe  polygon
           QPolygon triangle;
           triangle.append(QPoint(p1.x(), p1.y()));
           triangle.append(QPoint(p2.x(), p2.y()));
           triangle.append(QPoint(p3.x(), p3.y()));

           painter.drawPolygon(triangle);
       }
   }

   //Draw aspect
   if(this->draw_aspect)
   {
       std::vector<QColor> colors = genAspColors();

       double c = 255.0/360;
       for(unsigned int i = 0; i < dtm.size(); i++)
       {
           //Get triangle and its vertices
           Triangle t = dtm[i];
           QPoint3D p1 = t.getP1();
           QPoint3D p2 = t.getP2();
           QPoint3D p3 = t.getP3();

           //Get aspect and set the brush
           int c_aspect = c*t.getAspect();
           painter.setBrush(colors[c_aspect]);
           painter.setPen(pen_slope);

           //Create and drawthe  polygon
           QPolygon triangle;
           triangle.append(QPoint(p1.x(), p1.y()));
           triangle.append(QPoint(p2.x(), p2.y()));
           triangle.append(QPoint(p3.x(), p3.y()));

           painter.drawPolygon(triangle);
       }
   }

   //Draw hypsometry
   if(this->draw_hyps)
   {
       painter.setPen(pen_slope);

       double h_range = hyps[hyps.size()-1].getZ() - hyps[0].getZ();

       double coef = 255.0/h_range;

       for(unsigned int i = 0; i < hyps.size(); i++)
       {
           int brush_index = (hyps[i].getZ() - hyps[0].getZ())*coef;
           painter.setBrush(ctable[brush_index]);
           painter.drawPolygon(hyps[i]);
       }
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
    this->draw_aspect = false;
    this->draw_slope = false;
    this->draw_hyps = false;
    points.clear();
    dt.clear();
    dtm.clear();
    contours.clear();
    hyps.clear();
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
    double h = canvas_size.height() - 40;
    double w = canvas_size.width() - 40;

    double x_coef = w/(max_x-min_x);
    double y_coef = h/(max_y-min_y);

    for(unsigned int i = 0; i < points.size(); i++)
    {
        points[i].setX((points[i].x()-min_x)*x_coef);
        points[i].setY((points[i].y()-min_y)*y_coef);
    }
    points_file.close();
}

std::vector<QColor> Draw::genAspColors()
{
    std::vector<QColor> colors;

    for(int i = 0; i < 256; i++)
    {
        if(i <= (22.5*255/360)) colors.push_back(QColor(255,0,0)); //red
        else if(i > (22.5*255/360) && i <= (67.5*255/360)) colors.push_back(QColor(255,165,0)); //orange
        else if(i > (67.5*255/360) && i <= (112.5*255/360)) colors.push_back(QColor(255,255,0)); //yellow
        else if(i > (112.5*255/360) && i <= (157.5*255/360))colors.push_back(QColor(0,255,0)); //lime
        else if(i > (157.5*255/360) && i <= (202.5*255/360))colors.push_back(QColor(0,255,255)); //cyan
        else if(i > (202.5*255/360) && i <= (247.5*255/360))colors.push_back(QColor(0,191,255)); //deepskyblue
        else if(i > (247.5*255/360) && i <= (292.5*255/360))colors.push_back(QColor(0,0,255)); //blue
        else if(i > (292.5*255/360) && i <= (337.5*255/360))colors.push_back(QColor(255,0,255)); //magenta
        else if(i > (337.5*255/360))colors.push_back(QColor(255,0,0)); //red

    }

    return colors;

}

void Draw::drawHypsometry()
{
    this->draw_hyps = !this->draw_hyps;
    this->draw_aspect = false;
    this->draw_slope = false;
}

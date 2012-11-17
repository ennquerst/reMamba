#include "webpath.h"
#include <iostream>
#include <QRect>
#include <QString>

//class provides some special operations on qpolygon class
//for needed purposes of game
WebPath::WebPath()
{
}

WebPath::~WebPath()
{
}
//append point so that any of lines will be intersected
void WebPath::add(QPoint p)
{

        remove(p);
        positions.append(p);
        //         std::cout
        //                    << QString("pocet prvkov v webpath: %1").arg(positions.size()).toUtf8().constData()
        //                            << std::endl;


}

void WebPath::remove(QPoint p)
{
        int i = pointLine(p) +1;
        int count = positions.size() - i;


        //webpath contains selected point
        //and number of points is more than 1
        if(i > 0){
                //                std::cout
                //                    << QString("mazem od indexu: %1 tolkoto prvkov: %2").arg(i).arg(count).toUtf8().constData()
                //                            << std::endl;

                //want to remove all the next points after
                //the starting point of line that contains point
                //which is beiing removed
                positions.remove(i, count);
        }

}

bool WebPath::containsPoint(QPoint p)
{
        if(pointLine(p) == -1)
                return false;
        return true;
}


//works only for points in horizontal and vertical line
bool WebPath::pointOnLine(QPoint a, QPoint b, QPoint p)
{

        QPoint indicator;
        indicator = b - a;
        bool ret = (
                                (indicator.x() == 0 //vertical
                                 && a.x() == p.x()
                                 && isBetween(a.y(), b.y(), p.y())
                                 ) //point belongs to line
                                ||              //or
                                (indicator.y() == 0 //horizontal
                                 && a.y() == p.y()
                                 && isBetween(a.x(), b.x(), p.x())
                                 ) ) //point belongs to line
                        ;

        //         if(ret)
        //            std::cout
        //                    << "patri na liniu"
        //                            << std::endl;
        //    else
        //            std::cout
        //                    << "nepatri na liniu"
        //                            << std::endl;

        return ret;

}

bool WebPath::pointBetweenPos(int a, int b, int p)
{
        //p.y() belongs between a.y() and b.y()
        bool ret =       ((a <= p && p <= b)
                          ||
                          //p.x() belongs between a.x() and b.x()
                          (a <= p && p <= b));

        //        //p.y() belongs between a.y() and b.y()
        //bool ret =       ((a.y() <= p.y() && p.y() <= b.y())
        //                 || (a.y() >= p.y() && p.y() >= b.y()))
        //            ||
        //        //p.x() belongs between a.x() and b.x()
        //                ((a.x() <= p.x() && p.x() <= b.x())
        //                 || (a.x() >= p.x() && p.x() >= b.x()));

        // if(ret)
        //            std::cout
        //                    << "        patri do stvorca"
        //                            << std::endl;
        //    else
        //            std::cout
        //                    << "        nepatri do stvorca"
        //                            << std::endl;

        return  ret;
}

bool WebPath::isBetween(int a, int b, int p)
{
        return (pointBetweenPos(a, b, p)
                || pointBetweenPos(b, a, p));

}

int WebPath::pointLine(QPoint p)
{

        if(positions.size() == 1){

                //            std::cout
                //                    << " iba jedna polozka"
                //                            << std::endl;
                if(positions[0] == p)
                        return 0;
        }

        //if line is vertical .x()=0
        //if line is horizontal .yi()=0
        QPoint a;
        QPoint b;
        if(!positions.isEmpty()){
                //goes until size -1
                for(int i = 0; i < positions.size()-1; ++i){
                        a = positions[i];
                        b = positions[i+1];

                        if(a == p || b == p){
                                //                                std::cout
                                //                                        << "patri priamo"
                                //                                                << std::endl;
                                return i;
                        }
                        if(pointOnLine(a,b,p))
                                return i;


                }
        }

        //means that point isn't contained in webpath
        return -1;

}

void WebPath::clear()
{

        positions.clear();
}

//returns points where given two positions intersects one of the lines
QPoint WebPath::crossesLinesPoint(QPoint a, QPoint b, QPoint c, QPoint d)
{
        QPoint indicator1;
        QPoint indicator2;
        indicator1 = a - b;
        indicator2 = c - d;
        if((indicator1.x() == 0) //first given line is vertical
                        &&
                        (indicator2.y() == 0) //second given line is horizontal
                        &&
                        isBetween(c.x(), d.x(), a.x())
                        &&
                        isBetween(a.y(), b.y(), c.y())
                        ){
                return QPoint(a.x(), c.y());

        }
        else if(indicator1.y() == 0 //first given line is horizontal
                        &&
                        indicator2.x() == 0 //second given line is horizontal
                        &&
                        isBetween(c.y(), d.y(), a.y())
                        &&
                        isBetween(a.x(), b.x(), c.x())
                        ){

                return QPoint(a.y(), c.x());
        }
        return QPoint(-1,-1);
}

bool WebPath::crossesLines(QPoint a, QPoint b, QPoint c, QPoint d)
{
        QPoint p = crossesLinesPoint(a,b,c,d);
        if(QPoint(-1,-1) == p)
                return false;
        return true;


}

QPoint WebPath::intersectPoint(QPoint c, QPoint d)
{
        QPoint a;
        QPoint b;
        QPoint ret(-1,-1);

        if(!positions.isEmpty()){
                //goes until size -1
                for(int i = 0; i < positions.size(); ++i){
                        a = positions[i];
                        b = positions[(i+1)%positions.size()]; //need to fix last and first point line
                        ret = crossesLinesPoint(a,b,c,d);
                        if(ret != QPoint(-1,-1)){

                                return ret;
                        }

                }
        }

        return ret;
}

#ifndef WEBPATH_H
#define WEBPATH_H

#include <QVector>
#include <QPoint>

class WebPath
{
public:
    WebPath();
    ~WebPath();
    void add(QPoint);
    void remove(QPoint);
    //returns true if point lies on the path from points in qvector
    bool containsPoint(QPoint);
    //returns true if line between given points crosses path
    bool crossesLines(QPoint, QPoint, QPoint, QPoint);
    //returns point where two lines between given points crosses
    QPoint crossesLinesPoint(QPoint, QPoint, QPoint, QPoint);
    //returns point where line crosses webpath
    QPoint intersectPoint(QPoint , QPoint );
    void clear();

//*****inline methods******
   inline QVector<QPoint> getPositions() const
   {

           return positions;

   }

   inline QPoint getLast() const{

           return positions.last();

   }

//temporary for testing
    bool pointOnLine(QPoint, QPoint, QPoint);

    // returns index of starting point of line which contains given point
    int pointLine(QPoint);
    //returns true if p is between a and b
    bool pointBetweenPos(int a, int b, int p);
    //returns true if p is between a and b and also between b and a
    bool isBetween(int a, int b, int p);
private:
    QVector<QPoint> positions;


};

#endif // WEBPATH_H

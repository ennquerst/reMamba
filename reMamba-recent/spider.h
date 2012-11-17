#ifndef SPIDER_H
#define SPIDER_H

#include <QObject>
#include <QPainter>
#include <QPainterPath>
#include <QPoint>
#include <QPixmap>
#include <iostream>
#include "webpath.h"

class Spider : public QObject
{
        Q_OBJECT
public:
        explicit Spider(QObject *parent = 0);

        void move();
        void draw(QPainter*);
        void reset();
        QSize getSize();
        void startWeb(QPoint);
        //QPainterPath stopNgetWeb();//QPoint futurePos);
        QPolygon stopNgetWeb(QPoint);//QPoint futurePos);
        void setDirection(QPoint d);

//**********inline methods*******************
        inline void setPosition(QPoint p){
                position = p;
        }

        inline QPoint getPosition(){
                return position;
        }

        inline QPoint getDirection(){
                return direction;
        }

        inline QPoint getCenter(){
                return center;
        }

        inline void setWeaving(bool b){
                weaving = b ;
        }


private:
       QPoint position;
       QPoint direction;
       QPixmap picture;
       //QPainterPath web;
       WebPath web;
       QPoint center;
        bool weaving;


};

#endif // SPIDER_H

#include "fate.h"
#include "constants.h"
#include <QKeyEvent>
#include <iostream>

Fate::Fate(QWidget *parent) :
        QWidget(parent)
{
        timerId = this->startTimer(INTERVAL);
        spidey = new Spider();
        borders = new QRect(spidey->getCenter(), MAP_CORNER + spidey->getCenter() +QPoint(1,1));
        stopped = false;
        danger = false;

        restart();
        setFocusPolicy(Qt::StrongFocus);
        QPoint res(MAP_CORNER + spidey->getCenter());
        resize(res.x(), res.y());


}

void Fate::paintEvent(QPaintEvent *e)
{
        QPainter painter(this);
        QPen pen(Qt::black, 2, Qt::SolidLine);
        painter.setPen(pen);

        painter.fillRect(*borders, QColor(0, 90, 0));

        painter.setBrush(QColor(200,0,0));
        painter.drawPolygon(QPolygon(dangerZone.getPositions()));
        spidey->draw(&painter);
}

void Fate::timerEvent(QTimerEvent *e)
{
        bound();
        weave();
        spidey->move();
        update();
}

void Fate::keyPressEvent(QKeyEvent *e)
{
        switch (e->key()) {
        case Qt::Key_Up:
                spidey->setDirection(QPoint(0, -1));
                //        std::cout << "up" << std::endl;
                break;
        case Qt::Key_Down:
                spidey->setDirection(QPoint(0, 1));
                break;
        case Qt::Key_Left:
                spidey->setDirection(QPoint(-1, 0));
                break;
        case Qt::Key_Right:
                spidey->setDirection(QPoint(1, 0));
                break;
        case Qt::Key_Space:
                spidey->setDirection(QPoint(0, 0));
                break;
        case 'R':
                restart();
                break;
        default:
                //std::cout << e->key() << std::endl;
                break;
        }


        e->accept();
}

//reset some of the values when new game
void Fate::restart()
{
        lastCross = QPoint(-1,-1);
        spidey->reset();
        //testing
        dangerZone.clear();
        //        dangerZone = QPolygon(QRect(spidey->getCenter()+QPoint(1, 1), MAP_SIZE - QSize(1,1) ), false);
        QPoint centered = spidey->getCenter()+QPoint(49,49);
        QPoint centeredMapCorner(MAP_CORNER + centered - QPoint(100,100));
        dangerZone.add(centered);
        dangerZone.add(QPoint(centeredMapCorner.x(),centered.y()));
        dangerZone.add(centeredMapCorner);
        dangerZone.add(QPoint(centered.x(), centeredMapCorner.y()));

}

//so that spider won't run out of the map
void Fate::bound()
{
        QPoint nowMe = spidey->getPosition() + spidey->getCenter();
        QPoint futureMe =  nowMe + SPIDER_STEP* spidey->getDirection();
        if(!(borders->contains(futureMe))){

                spidey->setDirection(QPoint(0,0));
                //              std::cout
                //                    << QString("now: %1 %2").arg(nowMe.x()).arg(nowMe.y()).toUtf8().constData()
                //                       << std::endl
                //                    << QString("future: %1 %2").arg(futureMe.x()).arg(futureMe.y()).toUtf8().constData()
                //                        << std::endl;
        }
}

//tells the spider to weave a web
void Fate::weave()
{
        QPolygon p(dangerZone.getPositions());
        QPoint nowMe = spidey->getPosition() + spidey->getCenter();
        QPoint futureMe =  nowMe + SPIDER_STEP* spidey->getDirection();
        QPoint nowCross = dangerZone.intersectPoint(nowMe,futureMe);

        //spider enters danger zone i.e the mambas playground
        if(QPoint(-1,-1) != nowCross){
                if(p.containsPoint(futureMe, Qt::OddEvenFill)){
                       spidey->startWeb(nowCross);
                }else{
                        spidey->stopNgetWeb(nowCross);
                }



//                //spider was safe
//                if(!danger){
//                        danger = true;
//                        std::cout << "danger zone entered in next step" << std::endl;
//                        std::cout
//                                << QString("now: %1 %2").arg(nowMe.x()).arg(nowMe.y()).toUtf8().constData()
//                                << std::endl
//                                << QString("future: %1 %2").arg(futureMe.x()).arg(futureMe.y()).toUtf8().constData()
//                        << std::endl;
////                        stopSpider();
//                        spidey->startWeb();
//                }else{ //spider leaves danger zone
//                        danger = false;
//                        std::cout << "one more step to be saved!" << std::endl;
//                        std::cout
//                                << QString("now: %1 %2").arg(nowMe.x()).arg(nowMe.y()).toUtf8().constData()
//                                << std::endl
//                                << QString("future: %1 %2").arg(futureMe.x()).arg(futureMe.y()).toUtf8().constData()
//                        << std::endl;

//        //                spidey->move();
//        //                stopSpider();
////                        dangerZone = dangerZone.subtracted(spidey->stopNgetWeb());
//                        spidey->stopNgetWeb();
//                }
        }
}

void Fate::stopSpider()
{
        if(stopped){
                stopped = false;
                std::cout << "stopped go" << std::endl;
        }else{
                spidey->setDirection(QPoint(0,0));
                stopped = true;
                std::cout << "go stopped" << std::endl;
        }



}

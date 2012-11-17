#include "spider.h"
#include "constants.h"

Spider::Spider(QObject *parent) :
        QObject(parent)
{
        weaving = false;
        picture = QPixmap(":/resources/s.gif");
        center = QPoint(picture.width()/2, picture.height()/2);

        reset();

}

void Spider::setDirection(QPoint d){

        if(weaving){
            if( (direction + d) != QPoint(0,0) && (direction + d) != 2*direction){
////                        std::cout << QString("rozny smer %1,%2 %3,%4").arg(direction.x()).arg(direction.y()).arg(d.x()).arg(d.y()).toUtf8().constData() << std::endl;
////                        std::cout << QString("pridavam bod %1 %2").arg(position.x()).arg(position.y()).toUtf8().constData() << std::endl;

                        //web.lineTo(QPointF(position + center));
                    web.add(QPoint(position + center));
            }
        }
        direction = d;
}

QSize Spider::getSize()
{
        return picture.size();
}

void Spider::draw(QPainter *p)
{
        if(weaving){
                p->setBrush(Qt::NoBrush);
                //p->drawPath(web);
                //p->drawLine(QLineF(web.currentPosition(), QPointF(position + center)));
                web.add(position+center);
                p->drawPolyline(QPolygon(web.getPositions()));
                //p->drawLine(web.getLast(), QPointF(position + center));

          }

        p->drawPixmap(position, picture);

}

void Spider::reset()
{
        web.clear();
        setPosition(QPoint(0,0));
        setDirection(QPoint(0,0));
        //web.~QPainterPath();


}

void Spider::move()
{
//        if(weaving){
//        if(web.isEmpty()){
//                        std::cout << "nova siet"  << std::endl;
//                        web = QPainterPath(position + center);
//                        web.lineTo(position + SPIDER_STEP * direction +center);
//                }

//        }
       position += SPIDER_STEP * direction;

}

void Spider::startWeb(QPoint p)
{
        weaving = true;
        //web = QPainterPath(QPointF(position + center));
        //future position - don't know what is better
        // makes differences
        //QPoint futurePos =  position + SPIDER_STEP * direction;
        //web = QPainterPath(QPointF(futurePos + center));
        web.add(p);
}

QPolygon Spider::stopNgetWeb(QPoint last/*, QPoint mambaPos*/)
{
        weaving = false;
        //web.lineTo(futurePos + center);
        web.add(last);
//        web.add(QPoint(futurePos + center));
        //web2polygon
        //web.~QPainterPath();
        QPolygon ret = web.getPositions();
        web.clear();
//        std::cout << "vraciam siet"  << std::endl;
        return ret;

}

#ifndef FATE_H
#define FATE_H

#include <QWidget>
#include <QPainterPath>
#include "spider.h"
#include "webpath.h"

class Fate : public QWidget
{
    Q_OBJECT
public:
    explicit Fate(QWidget *parent = 0);
    
signals:
    
public slots:

protected:
        void keyPressEvent(QKeyEvent *e);
        void timerEvent(QTimerEvent *e);
        void paintEvent(QPaintEvent *e);

private:
        int timerId;
        //limits spider movements
        QRect*  borders;
        //limits mamba movement - it's danger for spider to be here
        WebPath dangerZone;
        //runs all around the map
        Spider* spidey;
        bool stopped;
        bool danger;
        QPoint lastCross;



        void restart();
        //constraint of spider movement
        void bound();
        void weave();
        void stopSpider();
    
};

#endif // FATE_H

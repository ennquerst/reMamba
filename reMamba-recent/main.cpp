#include <QApplication>
#include "mainwindow.h"
//temporary testing
#include "webpath.h"
#include <QPoint>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    //testing webpath
    WebPath wp;

    QPoint a(10, 20);
    QPoint b(50, 20);
    QPoint c(50, 50);
    QPoint d(30, 30);
    QPoint e(50, 30);
    QPoint f(30, 20);
    QPoint g(50, 100);
    QPoint h(30, 10);

    wp.add(a);
    wp.add(b);
    wp.add(c);

//            std::cout
//                    << QString("index bodu: %1").arg(wp.pointLine(a)).toUtf8().constData()
//                            << std::endl;
    QPoint p = wp.intersectPoint(d,e);
    if(p == QPoint(-1,-1))
            std::cout
                    << "pravda "
                       << "there's no cross point"
                            << std::endl;
    else
            std::cout
                    << "nepravda "
                       << QString("crooss point: %1 %2").arg(p.x()).arg(p.y()).toUtf8().constData()
                            << std::endl;


    return app.exec();
}

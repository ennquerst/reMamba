#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QPoint>

//weave detector doesn't work if it's below 5
//polygon.containsPoint() somehow doesn't recognize point
const int SPIDER_STEP = 5;
const int INTERVAL = 30;
const QPoint MAP_CORNER(600, 400);


#endif // CONSTANTS_H



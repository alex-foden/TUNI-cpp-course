#ifndef SPLASHITEM_HH
#define SPLASHITEM_HH

#include <QGraphicsPixmapItem>

class SplashItem : public QGraphicsPixmapItem
{
public:
    SplashItem(int startX, int startY, int endX, int endY);
};

#endif // SPLASHITEM_HH

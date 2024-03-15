#include "splashitem.hh"

SplashItem::SplashItem(int startX, int startY, int endX, int endY):
    QGraphicsPixmapItem(0)
{
    const int SPLASH_SIZE = 80;

    QPixmap pixmap("images/movingdrop.png");
    setPixmap(pixmap.scaledToHeight(SPLASH_SIZE));

    // Offset the image evenly around its centerpoint.
    setOffset(-SPLASH_SIZE/2, -SPLASH_SIZE/2);

    // Rotate the image according to the travel direction.
    // The original image travels from left to right.
    if (startY < endY) {
        setRotation(90);
    } else if (startX > endX) {
        setRotation(180);
    } else if (startY > endY) {
        setRotation(270);
    }
}

#include "dropitem.hh"
#include "splash.hh"

#include <iostream>
#include <vector>

#include <QPixmap>
#include <QGraphicsSceneMouseEvent>
#include <QPropertyAnimation>


const std::vector<std::string> images = {
    "images/waterdrop1.png",
    "images/waterdrop2.png",
    "images/waterdrop3.png",
    "images/waterdrop4.png"
};

DropItem::DropItem(std::shared_ptr<Drop> drop,
                   unsigned int size,
                   QGraphicsItem* parent):
    QGraphicsPixmapItem(parent),
    size_(size),
    drop_(drop)
{
    updateGraphics();
}

void DropItem::updateGraphics()
{
    int level = drop_->waterLeft();

    // Load the image and scale to correct size.
    QPixmap map(QString::fromStdString(images.at(level-1)));
    setPixmap(map.scaledToHeight(size_));
 }

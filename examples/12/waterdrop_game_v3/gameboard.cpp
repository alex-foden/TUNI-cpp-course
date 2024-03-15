#include "gameboard.hh"
#include "gameengine.hh"
#include "drop.hh"
#include "dropitem.hh"
#include "splash.hh"
#include "splashanimation.hh"

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QCoreApplication>
#include <QTime>

#include <QMessageBox>

#include <iostream>

GameBoard::GameBoard(QObject* parent):
    QGraphicsScene(parent),
    animations_()
{
    // The scene where items can be drawn starts from coordinate 0,0
    // and the width and height are set to SIZE*GRID_SIDE.
    setSceneRect(0, 0, SIZE * GRID_SIDE, SIZE * GRID_SIDE);
}

void GameBoard::addDrop(int column, int row, std::shared_ptr<Drop> drop)
{
    // Create a new graphical item and add it to the scene so it will be drawn.
    DropItem* item = new DropItem(drop, GRID_SIDE, 0);
    addItem(item);

    // Set the correct position within the scene.
    QPointF position = gridToPoint(column, row);
    item->setPos(position);
}

void GameBoard::removeDrop(int column, int row)
{
    QPointF scenePoint = gridToPointCenter(column, row);

    // Find the item at the given point and remove it.
    QGraphicsItem* clickedItem = itemAt(scenePoint, QTransform());

    if (clickedItem != 0) {
        removeItem(clickedItem);
        delete clickedItem;
    }
}

void GameBoard::updateDrop(int column, int row)
{
    QPoint scenePoint = gridToPointCenter(column, row);

    // Find the drop item at the given point and update it.
    DropItem* updatedItem =
            dynamic_cast<DropItem*>(itemAt(scenePoint, QTransform()));

    if (updatedItem) {
        updatedItem->updateGraphics();
    }
}

void GameBoard::addSplash(int startX, int startY, int endX, int endY)
{
    QPoint startPoint = gridToPointCenter(startX, startY);
    QPoint endPoint = gridToPointCenter(endX, endY);

    SplashAnimation* animation =
            new SplashAnimation(this, startPoint, endPoint);
    animations_.addAnimation(animation);
}

void GameBoard::animate()
{
    animations_.start();

    // Animations are executed in the event loop, so process events until
    // the animations are finished.
    while (animations_.state() == QAbstractAnimation::Running) {
         QCoreApplication::processEvents(QEventLoop::AllEvents);
    }

    animations_.clear();
}

void GameBoard::drawBackground(QPainter* painter, QRectF const& /*rect*/)
{
    QColor backGroundColor(225, 225, 225);

    // Draw gridlines for the game area.
    for (int row = 0; row < SIZE; row++) {
        for (int column = 0; column < SIZE; column++) {
            QRectF square(column * GRID_SIDE, row * GRID_SIDE,
                          GRID_SIDE, GRID_SIDE);
            painter->fillRect(square, backGroundColor);
            painter->drawRect(square);
        }
    }
}

void GameBoard::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mousePressEvent(event);

    QPoint clickPosition = event->scenePos().toPoint();

    if (0 <= clickPosition.x() and clickPosition.x() <= GRID_SIDE * SIZE and
        0 <= clickPosition.y() and clickPosition.y() <= GRID_SIDE * SIZE) {
        // Only accept new mouse clicks when animations are not running.
        if (animations_.state() != QAbstractAnimation::Running) {
            emit mouseClick(clickPosition.x() / GRID_SIDE,
                            clickPosition.y() / GRID_SIDE);
        }
    }
}

QPoint GameBoard::gridToPoint(int column, int row) const
{
    return QPoint(GRID_SIDE * column, GRID_SIDE * row);
}

QPoint GameBoard::gridToPointCenter(int column, int row) const
{
    int x = column * GRID_SIDE + GRID_SIDE/2;
    int y = row * GRID_SIDE + GRID_SIDE/2;
    return QPoint(x, y);
}

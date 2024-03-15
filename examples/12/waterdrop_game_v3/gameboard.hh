#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include "drop.hh"
#include <QGraphicsScene>
#include <QParallelAnimationGroup>
#include <QPainter>
#include <memory>

class GameBoard : public QGraphicsScene
{
    Q_OBJECT

public:
    GameBoard(QObject* parent = nullptr);

    // Add a new drop graphics in the given grid coordinates.
    void addDrop(int column, int row, std::shared_ptr<Drop> drop);

    // Remove a drop graphics from the given grid coordinates.
    void removeDrop(int column, int row);

    // Update a drop graphics in the given grid coordinates.
    void updateDrop(int column, int row);

    // Add splash animation from the start grid coordinates to
    // end grid coordinates.
    void addSplash(int startX, int startY, int endX, int endY);

    // Run all splash animations.
    void animate();

signals:
    // Emitted when user clicks a grid square.
    void mouseClick(int x, int y);

protected:   
    // Draws the grid lines.
    virtual void drawBackground(QPainter* painter, QRectF const& rect) override;

    // Handler for mouse click events.
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    // Size of the grid i.e. both width and height.
    const int GRID_SIDE = 50;

    // Converts grid coordinates to scene position.
    QPoint gridToPoint(int column, int row) const;

    // Converts grid coordinates to scene position at the center of the
    // grid square.
    QPoint gridToPointCenter(int column, int row) const;

    // Group (=list) of splash animation to run simultaneously.
    QParallelAnimationGroup animations_;
};

#endif // GAMEBOARD_HH

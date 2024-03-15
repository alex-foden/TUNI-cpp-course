#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gameboard.hh"
#include "gameengine.hh"

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(GameBoard &scene, QWidget* parent = nullptr);

private:
    QGraphicsView view_;
};

#endif // MAINWINDOW_H

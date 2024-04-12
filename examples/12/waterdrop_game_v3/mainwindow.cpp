#include "mainwindow.hh"

#include "dropitem.hh"
#include "gameengine.hh"

MainWindow::MainWindow(GameBoard& scene, QWidget* parent) :
    QMainWindow(parent),
    view_(this)
{
    view_.setScene(&scene);
    setCentralWidget(&view_);
}

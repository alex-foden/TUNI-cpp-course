#include "mainwindow.hh"

#include "gameengine.hh"
#include "gameboard.hh"

#include <QApplication>
#include <QObject>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    GameBoard graphicalGameBoard;
    GameEngine engine(graphicalGameBoard);

    MainWindow w(graphicalGameBoard);

    QObject::connect(&graphicalGameBoard, SIGNAL(mouseClick(int, int)),
                     &engine, SLOT(addWater(int, int)));
    QObject::connect(&engine, SIGNAL(quitGame()), &w, SLOT(close()));

    w.show();

    return a.exec();
}

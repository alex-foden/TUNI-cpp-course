#ifndef GAMEENGINE_HH
#define GAMEENGINE_HH

#include "gameboard.hh"

#include "drop.hh"
#include "splash.hh"
#include <iostream>
#include <vector>
#include <memory>
#include <random>

const int SIZE = 6;

class GameEngine : public QObject
{
    Q_OBJECT

public:
    GameEngine(GameBoard& gameBoard, int seed_value = 0);

    // Initializes new game.
    void initialize();

    // Checks if the game is over, i.e. if the game board is empty of drops.
    bool isEmpty() const;

    // In destruction the drop removes itself from the data content
    // of the game board.
    void removeDrop(int x, int y);

    // Fetches the drop instance from the board at given coordinates,
    // or a nullptr if the coordinates are outside the board.
    std::shared_ptr<Drop> dropAt(int x, int y) const;

signals:
    // Emitted, when the game will be quitted.
    void quitGame();

public slots:
    // Activated, when water is needed to be added to the board
    // at the given position.
    void addWater(int x, int y);

private:
    // Moves each splash on the board one square ahead.
    void moveSplashes(std::vector<std::shared_ptr<Drop> >& removedDrops);

    // Prints the game board to the given stream by animating the flow of
    // splashes (test printing to console)
    void print(std::ostream& stream, std::vector<Splash>& splashes);

    // Utility method for print
    char droplessSquareChar(int x, int y, std::vector<Splash> &splashes) const;

    // Game board used in the game
    std::vector< std::vector< std::shared_ptr<Drop> > > board_;

    // Splashes of the game
    std::vector< Splash > splashes_;

    // Drawing area to show the game status
    GameBoard& graphicalGameBoard_;

    // Available amount of water
    int waterTank_;

    // Random number generator
    std::default_random_engine generator;
};

#endif // GAMEENGINE_HH

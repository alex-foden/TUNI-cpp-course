/* Module: GameBoard / file: gameboard.hh
 * Controls the water drops and splashes on the game board.
 */

#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include "drop.hh"
#include "splash.hh"
#include <iostream>
#include <vector>
#include <memory>

const int SIZE = 12;

class GameBoard
{
public:
    // Constructor initializes the game board with water drops
    // at random locations
    GameBoard();

    // Prints the game board to the given stream by animating the
    // flow of splashes
    void print(std::ostream& stream);

    // Checks if the game board is empty of drops, which means that
    // the game is over
    bool isEmpty() const;

    // Drops a drop of water to a certain location at the game board
    void addWater(int x, int y);

    // In destruction the drop removes itself from the game board
    void removeDrop(int x, int y);

private:
    std::vector< std::vector< std::shared_ptr<Drop> > > board_;
    std::vector< Splash > splashes_;

    // Moves each splash on the board one square ahead
    void moveSplashes();

    // Utility method for print
    char droplessSquareChar(int x, int y) const;
};

#endif // GAMEBOARD_HH

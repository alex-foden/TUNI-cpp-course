/* Module: Drop / file: drop.cpp
 */

#include "drop.hh"
#include "splash.hh"
#include "gameboard.hh"
#include <iostream>

Drop::Drop(int x, int y, int waterAmount, GameBoard* board ):
    x_(x), y_(y), waterAmount_(waterAmount), board_(board)
{}

void Drop::addWater(std::vector<Splash>& createdSplashes) {
    ++waterAmount_;

    if( waterAmount_ > MAX_CAPACITY ) {
        std::cout << x_ + 1 << ',' << y_ + 1 << " pops!\n";
        waterAmount_ = 0;

        // Creating 4 Splashes that go to different directions
        createdSplashes.push_back(Splash(x_, y_, 1, UP));
        createdSplashes.push_back(Splash(x_, y_, 1, DOWN));
        createdSplashes.push_back(Splash(x_, y_, 1, RIGHT));
        createdSplashes.push_back(Splash(x_, y_, 1, LEFT));

        // Drop removes the pointer to itself from the board.
        // Then the reference counter of the dynamically created object
        // becomes zero and the object is destructed automatically.
        // Therefore this call must be the last command of the method.
        board_->removeDrop(x_, y_);
    }
}

void Drop::print( std::ostream& stream ) const {
    // CHARACTERS array contains symbols for each amount of water in the
    // corresponding indices, and thus, we can find the desired symbol easily.
    stream << CHARACTERS[ waterAmount_ ];
}

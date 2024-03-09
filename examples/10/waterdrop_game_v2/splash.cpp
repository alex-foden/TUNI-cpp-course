/* Module: Splash / file: splash.cpp
 */

#include "splash.hh"
#include "gameboard.hh"

Splash::Splash(int x, int y, int waterAmount, Direction type):
    x_(x), y_(y), waterAmount_(waterAmount), type_(type)
{}

char Splash::getChar() const {
    // Member variable type_ is of enum Direction. Its values are
    // UP = 0, DOWN = 1, etc. Here we index array DIRECTIONS by using
    // these values to get the desired character.
    return DIRECTIONS[type_].character;
}

int Splash::getX() const {
    return x_;
}

int Splash::getY() const {
    return y_;
}

bool Splash::move() {
    // Updating the location of the splash with the values of array DIRECTIONS.
    x_ += DIRECTIONS[type_].deltaX;
    y_ += DIRECTIONS[type_].deltaY;

    // Checking, if the splash moved outside the game board,
    // in which case it will be removed
    if(x_ < 0 or x_ >= SIZE or y_ < 0 or y_ >= SIZE) {
        return true;
    }
    return false;
}

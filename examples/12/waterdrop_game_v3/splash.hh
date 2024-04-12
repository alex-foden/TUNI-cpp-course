#ifndef SPLASH_HH
#define SPLASH_HH

#include "drop.hh"

// Because enum is an integer type, the elements of which are enumerated
// from zero on, i.e. UP = 0, DOWN = 1, we can use its values to refer the
// corresponding elements in DIRECTIONS array.
enum Direction {UP, DOWN, RIGHT, LEFT};

struct DirectionInfo {
    int deltaX;
    int deltaY;
    char character;
};

const DirectionInfo DIRECTIONS[] = { {  0, -1, '^' },
                                     {  0,  1, 'v' },
                                     {  1,  0, '>' },
                                     { -1,  0, '<' } };

class Splash
{
public:
    Splash(int x, int y, Direction type);

    // Methods to inspect splashed from outside the class
    int getX() const;
    int getY() const;
    char getChar() const;

    // Moves the splash one step forward in the game board.
    // Returns a boolean value telling, if the splash moved outside the board,
    // in which case it should be removed.
    // (true = removable, false = not removable)
    bool move();

private:
    int x_;  // A splash can be outside the board, and thus, the coordinates
    int y_;  // can also be negative

    Direction type_;
};

#endif // SPLASH_HH

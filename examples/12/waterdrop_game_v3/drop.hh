#ifndef DROP_HH
#define DROP_HH

#include <iostream>
#include <vector>
#include <memory>

class Splash;
class GameEngine;

const int MAX_CAPACITY = 4;
const char CHARACTERS[] = {' ', '.', 'o', 'O', '@'};

class Drop
{
public:
    Drop(int x, int y, int waterAmount, GameEngine* engine);

    // Adds water to the drop.
    // If maximum capacity is exceeded, the drop will pop.
    // Reference parameter exports new Splash objects created in potential pop.
    void addWater(std::vector<Splash>& createdSplashes);

    // Prints the character corresponding to the amount of water of the drop
    // to the given stream.
    void print(std::ostream& stream) const;

    int waterLeft() const;

    int getX() const;

    int getY() const;

private:
    // Location and the amount of water
    int x_;
    int y_;
    int waterAmount_;

    // Pointer to the game engine, at the board of which the drop lies
    GameEngine* engine_;
};

#endif // DROP_HH

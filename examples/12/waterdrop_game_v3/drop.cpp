#include "drop.hh"
#include "splash.hh"
#include "gameengine.hh"
#include <cstdlib>
#include <iostream>

Drop::Drop(int x, int y, int waterAmount, GameEngine* engine ):
    x_(x),
    y_(y),
    waterAmount_(waterAmount),
    engine_(engine)
{}

void Drop::addWater(std::vector<Splash>& createdSplashes)
{
    ++waterAmount_;

    if( waterAmount_ > MAX_CAPACITY ) {
        std::cout << x_+1 << ',' << y_+1 << " pops!" << std::endl;
        waterAmount_ = 0;

        // Creating 4 Splashes that go to different directions
        createdSplashes.push_back(Splash(x_, y_, UP));
        createdSplashes.push_back(Splash(x_, y_, DOWN));
        createdSplashes.push_back(Splash(x_, y_, RIGHT));
        createdSplashes.push_back(Splash(x_, y_, LEFT));

        // Drop removes the pointer to itself from the board.
        // Then the reference counter of the dynamically created object
        // becomes zero and the object is destructed automatically.
        // Therefore this call must be the last command of the method.
        engine_->removeDrop(x_, y_);
    }
}

void Drop::print( std::ostream& stream ) const
{
    // CHARACTERS array contains symbols for each amount of water in the
    // corresponding indices, and thus, we can find the desired symbol easily.
    stream << CHARACTERS[ waterAmount_ ];
}

int Drop::waterLeft() const
{
    return waterAmount_;
}

int Drop::getX() const
{
    return x_;
}

int Drop::getY() const
{
    return y_;
}

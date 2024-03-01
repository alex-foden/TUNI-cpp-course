/* Module: Drop / file drop.hh
 * Includes the data and functionality of a single drop.
 */

#ifndef DROP_HH
#define DROP_HH

#include <iostream>
#include <vector>
#include <memory>

class Splash;
class GameBoard;

const int MAX_CAPACITY = 4;
const char CHARACTERS[] = {' ', '.', 'o', 'O', '@'};

class Drop
{
public:
    Drop(int x, int y, int waterAmount, GameBoard* board);

    // Adds water to the drop.
    // If maximum capacity is exceeded, the drop will pop.
    // Reference parameter exports new Splash objects created in potential pop.
    void addWater(std::vector<Splash>& createdSplashes);

    // Prints the character corresponding to the amount of water of the drop
    // to the given stream.
    void print( std::ostream& ) const;

  private:
    // Location and the amount of water
    int x_;
    int y_;
    int waterAmount_;

    // Pointer to the board, at which the drop lies
    GameBoard* board_;
};

#endif // DROP_HH

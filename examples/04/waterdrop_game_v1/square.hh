#ifndef SQUARE_HH
#define SQUARE_HH

#include <vector>
#include <iostream>


const int MAX_CAPACITY = 4;
const char CHARACTERS[] = {' ', '.', 'o', 'O', '@'};

class Square;
using Board = std::vector< std::vector< Square > >;

class Square {
 public:

   // Location and amount of water as parameters to constructor
   Square( int x, int y, int drops, Board* board);
   ~Square();

   // Adds water to the square, calls pop method if the square overflows
   void addWater();

   // Tells if the square has water, to know if a drop is added to the square
   // or should it pass the square
   bool hasWater() const;

   // Prints the square (its amount of water) to the given stream
   void print( std::ostream& ) const;

 private:

   // Adds water to each direction and disappears
   void pop();

   // Location and the amount of water
   int x_;
   int y_;
   int drops_;

   // Pointer to the board, where the water drop lies
   Board* board_;
};

#endif // SQUARE_HH

#include "square.hh"
#include <cstdlib>
#include <iostream>


Square::Square(int x, int y, int drops, Board* board ):
    x_(x), y_(y), drops_(drops), board_(board) {
   // Square has been initialized with too much water,
   // it pops before game starts :)
   if( drops_ > MAX_CAPACITY ) {
      pop();
   }
}

Square::~Square() {}

void Square::addWater() {
   if( ++drops_ > MAX_CAPACITY ) {
      pop();
   } 
}

bool Square::hasWater() const {
   return drops_;
}

void Square::print( std::ostream& stream ) const {
    stream << CHARACTERS[ drops_ ];
}

void Square::pop() {
   std::cout << x_+1 << ',' << y_+1 << " pops!\n";
   drops_ = 0;

   // Almost the same code copied 4 times. Could you do this more cleverly?
   for( unsigned int x = x_; x < board_->at(y_).size(); ++x ) {
      if( board_->at(y_).at(x).hasWater() ) {
         board_->at(y_).at(x).addWater();
         break;
      }
   }

   for( int x = x_; x >= 0; --x ) {
      if( board_->at(y_).at(x).hasWater() ) {
         board_->at(y_).at(x).addWater();
         break;
      }
   }

   for( unsigned int y = y_; y < board_->size(); ++y ) {
      if( board_->at(y).at(x_).hasWater() ) {
         board_->at(y).at(x_).addWater();
         break;
      }
   }

   for( int y = y_; y >= 0; --y ) {
      if( board_->at(y).at(x_).hasWater() ) {
         board_->at(y).at(x_).addWater();
         break;
      }
   }
}

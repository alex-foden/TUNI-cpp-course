#include "square.hh"
#include <random>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

const int SIZE = 12;

void initBoard( Board& board ) {
    std::default_random_engine rand_gen;

    std::cout << "Enter a seed value or an empty line: ";
    std::string seed_value = "";
    getline(std::cin, seed_value);

    if( seed_value == "" ) {
        // If the user did not give a seed value,
        // use computer time as the seed value.
        rand_gen.seed( time(NULL) );
    } else {
        // If the user gave a seed value, use it.
        rand_gen.seed( stoi(seed_value) );
    }

    // Filling the board with random numbers between 0 and 4
    // These random numbers correspond to the amount of water,
    // i.e. the possible values of CHARACTERS
    std::uniform_int_distribution<int> distribution(0, 4);
    for( int y = 0; y < SIZE; ++y ) {
        std::vector< Square > row;
        for( int x = 0; x < SIZE; ++x ) {
            Square new_square( x, y, distribution(rand_gen), &board);
            row.push_back( new_square );
        }
        board.push_back( row );
    }
}

void printBoard( const Board& board, std::ostream& stream ) {
    // Printing space after each character to make ASCII graphics clearer.

    // Printing numbers of x-axis over the board
    stream << "  ";
    for( int x = 0; x < SIZE; ++x ) {
        // Using modulo 10 to make the output fit, even if the board width
        // was more than 10
        stream << (x + 1) % 10 << ' ';
    }
    stream << std::endl;

    // Printing the board such that each line begins with y-coordinate,
    // and then each square of the line is asked to print itself.
    for( int y = 0; y < SIZE; ++y ) {
        stream << (y+1) % 10 << ' ';
        for( int x = 0; x < SIZE; ++x ) {
            board.at(y).at(x).print( stream );
            stream << " ";
        }
        stream << std::endl;
    }
}

bool isEmpty( const Board& board ) {
    for( int y = 0; y < SIZE; ++y ) {
        for( int x = 0; x < SIZE; ++x ) {
            if( board.at(y).at(x).hasWater() ) {
                return false;
            }
        }
    }
    return true;
}

bool readCommandSuccessfully(int& x, int& y) {
    while(true) {
        std::cout << "x y> ";

        // If input reading fails (by Control-C), program terminates
        if(not(std::cin >> x and std::cin >> y)) {
            return false;
        }

        // If valid coordinates can be read, program execution continues
        if(0 < x and x <= SIZE and 0 < y and y <= SIZE) {
            return true;
        }

        // Otherwise input processing continues
        std::cout << "Error! Coordinates must be 1-" << SIZE << std::endl;
    }
}

int main() {
    Board board;
    initBoard(board);
    printBoard(board, std::cout);

    int x = 0;
    int y = 0;
    int waterTank = 10;

    while(waterTank and not isEmpty(board) and readCommandSuccessfully(x, y)) {
        board.at(y-1).at(x-1).addWater();
        waterTank--;
        printBoard(board, std::cout);
    }

    return EXIT_SUCCESS;
}

/* Module: Main program / file: main.cpp
 * Comprises the user interface, game board object, and the water tank.
 */

#include "gameboard.hh"
#include <cstdlib>
#include <iostream>

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
    GameBoard board;
    board.print(std::cout);

    int x = 0;
    int y = 0;
    int waterTank = 10;

    while(waterTank and not board.isEmpty() and readCommandSuccessfully(x, y)) {
        board.addWater(x-1, y-1);
        waterTank--;
        board.print(std::cout);
    }

    return EXIT_SUCCESS;
}

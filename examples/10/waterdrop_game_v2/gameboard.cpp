/* Module: GameBoard / file: gameboard.cpp
 */

#include "gameboard.hh"
#include <string>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <random>
#include <ctime>

GameBoard::GameBoard(): board_(), splashes_() {
    std::default_random_engine rand_gen;

    // It is possible for the user to give a seed value (for testing purposes)
    std::cout << "Enter a seed value or an empty line: ";
    std::string seed_value = "";
    getline(std::cin, seed_value);

    if(seed_value == "") {
        // If the user did not give a seed value,
        // use computer time as the seed value.
        rand_gen.seed(time(NULL));
    } else {
        // If the user gave a seed value, use it.
        rand_gen.seed(stoi(seed_value));
    }

    std::uniform_int_distribution<int> distribution(0, 4);
    // Initializing the game board in the same way as in waterdrop_game_v1,
    // but ...
    for(int y = 0; y < SIZE; ++y) {
        std::vector< std::shared_ptr<Drop> > line;
        for(int x = 0; x < SIZE; ++x) {
            int size = distribution(rand_gen);
            std::shared_ptr< Drop > newDrop = nullptr;

            // ... Drop instances are created only at squares with water.
            if (size != 0) {
                newDrop = std::make_shared<Drop>(x, y, size, this);
            }
            line.push_back(newDrop);
        }
        board_.push_back(line);
    }
}

void GameBoard::print(std::ostream& stream) {
    // do-while is a loop that will be executed at least once.
    // Condition is at the end of the structure, and it will be evaluated
    // after executing the body.
    do {
        // New splashes are at the square, where the drop popped, so we must
        // move all the splashes one square forward before printing the board.
        moveSplashes();

        // Printing in the same way as in waterdrop_game_v1.
        stream << "\n  ";
        for(int x = 0; x < SIZE; ++x) {
            stream << (x+1) % 10 << ' ';
        }
        stream << std::endl;

        for(int y = 0; y < SIZE; ++y) {
            stream << (y+1) % 10 << ' ';
            for(int x = 0; x < SIZE; ++x) {
                if(board_.at(y).at(x) != 0) {
                    board_.at(y).at(x)->print(stream);
                    stream << " ";
                } else {
                    // If the square has no drops, we must still check, whether
                    // to print an empty square or a square with splashes
                    stream << droplessSquareChar(x, y) << " ";
                }
            }
            stream << std::endl;
        }

        // Waiting for a moment before next printing to make the animation
        // at least a bit better.
        std::this_thread::sleep_for(std::chrono::seconds(1));

    // Printing is iterated as many times as the flow of all splashes has been
    // "animated", i.e. when there are no splashes left.
    } while(splashes_.size() > 0);
}

bool GameBoard::isEmpty() const {
    for( int y = 0; y < SIZE; ++y ) {
        for( int x = 0; x < SIZE; ++x ) {
            if( board_.at(y).at(x) != nullptr ) {
                return false;
            }
        }
    }
    return true;
}

void GameBoard::addWater(int x, int y) {
    if(board_.at(y).at(x) != nullptr) {
        board_.at(y).at(x)->addWater(splashes_);
    } else {
        board_.at(y).at(x) = std::make_shared<Drop>(x, y, 1, this);
    }
}

void GameBoard::removeDrop(int x, int y) {
    board_.at(y).at(x) = nullptr;
}

void GameBoard::moveSplashes() {
    // Container for new splashes that have born due to moving.
    // They cannot be inserted to container splashes_ immediately,
    // because they must wait until the next iteration.
    std::vector<Splash> newSplashes;

    // All the splashes on the board will be gone through by the iterator
    // in the while loop.
    std::vector<Splash>::iterator r = splashes_.begin();
    while (r != splashes_.end()) {

        // Calling move for each splash, which returns true, if the splash
        // moves outside the game board and becomes removable.
        // This return value is saved.
        bool remove = r->move();

        // If the splash is after move at a square with water drop,
        // the drop is added with water and the splash will be removed.
        if(not remove and board_.at(r->getY()).at(r->getX()) != 0) {
            board_.at(r->getY()).at(r->getX())->addWater(newSplashes);
            remove = true;
        }

        // If a splash instance is removed from the vector, erase returns a
        // new iterator that points the vector at the point, where traversal
        // will be continued after removal.
        // Otherwise iterator takes a step forward.
        if(remove) {
            r = splashes_.erase(r);
        } else {
            r++;
        }
    }
    // Finally the new splashes will be inserted to splashes_ of the game board
    // to take them along in animation.
    splashes_.insert(splashes_.end(), newSplashes.begin(), newSplashes.end());
}

char GameBoard::droplessSquareChar(int x, int y) const {
    // Checking if the square has splashes.
    // Saving the printing character of each splash to string characters.
    std::string characters = "";
    for(auto s: splashes_) {
        if(s.getX() == x and s.getY() == y) {
            characters += s.getChar();
        }
    }

    if(characters.length() == 0) { // No splashes in the square
                                   // -> printing empty
        return ' ';
    } else if (characters.length() == 1){  // A single splash
                                           // -> printing its character
        return characters.at(0);
    } else {  // Several splashes in the same square
        for(auto c: characters) {
            if(c != characters.at(0)) {
                // Different kinds of splashes at the same square
                // -> It is not possible to print them all -> printing mess
                return '*';
                // OBS! When a drop pops, it forms 4 splashes to its square,
                // so, in a way, this printing character describes pop, too.
            }
        }
        // Several splashes at the same square, but all of them are similar
        // (with the same printing character) -> printing this common character
        return characters.at(0);
    }
}

#include "gameengine.hh"

#include <QMessageBox>
#include <QCoreApplication>
#include <QTime>

#include <ctime>
#include <thread>

GameEngine::GameEngine(GameBoard& gameBoard, int seed_value):
    QObject(0),
    board_(),
    splashes_(),
    graphicalGameBoard_(gameBoard),
    waterTank_(10)
{
    if(seed_value == 0) {
        // If the user did not give a seed value,
        // use computer time as the seed value.
        generator.seed(time(NULL));
    } else {
        // If the user gave a seed value, use it.
        generator.seed(seed_value);
    }

    initialize();
}

void GameEngine::initialize()
{
    waterTank_ = 10;
    board_.clear();

    // Initializing the data content of the game board in the same way
    // as in waterdrop_game_v2
    for(int y = 0; y < SIZE; ++y) {
        std::vector< std::shared_ptr<Drop> > rowVector;
        for(int x = 0; x < SIZE; ++x) {
            std::uniform_int_distribution<int> distribution(0, 4);
            int size = distribution(generator);

            std::shared_ptr<Drop> newDrop = nullptr;

            if (size != 0) {
                newDrop = std::make_shared<Drop>(x, y, size, this);
            }
            rowVector.push_back(newDrop);
        }
        board_.push_back(rowVector);
    }

    // Initializing the graphical view of the game board
    graphicalGameBoard_.clear();
    for (int row = 0; row < SIZE; row++) {
        for (int column = 0; column < SIZE; column++) {
            std::shared_ptr<Drop> drop = dropAt(column, row);
            if (drop != nullptr) {
                graphicalGameBoard_.addDrop(column, row, drop);
            }
        }
    }
}

bool GameEngine::isEmpty() const
{
    for( int y = 0; y < SIZE; ++y ) {
        for( int x = 0; x < SIZE; ++x ) {
            if( board_.at(y).at(x) != nullptr ) {
                return false;
            }
        }
    }
    return true;
}

void GameEngine::removeDrop(int x, int y)
{
    board_.at(y).at(x) = nullptr;
}

std::shared_ptr<Drop> GameEngine::dropAt(int x, int y) const
{
    if (0 <= x and x < SIZE and 0 <= y and y < SIZE) {
        return board_.at(y).at(x);
    } else {
        return nullptr;
    }
}

void GameEngine::addWater(int x, int y)
{
    // Reducing water from the tank
    waterTank_--;

    // Updating the data content of the game
    if(board_.at(y).at(x) != nullptr) {
        board_.at(y).at(x)->addWater(splashes_);
    } else {
        board_.at(y).at(x) = std::make_shared<Drop>(x, y, 1, this);
    }

    // Fetching pointer to the drop processed just previously
    std::shared_ptr<Drop> drop = dropAt(x, y);

    // Updating the graphical view
    if (drop == nullptr) {
        // If the drop popped, remove its image from the drawing area
        graphicalGameBoard_.removeDrop(x, y);

    } else if (drop->waterLeft() == 1) {
        // In the case of an empty square,
        // add a new drop image to the drawing area
        graphicalGameBoard_.addDrop(x, y, drop);

    } else {
        // Otherwise increasing the drop image
        graphicalGameBoard_.updateDrop(drop->getX(), drop->getY());
    }

    // Updating the graphical view of the game board, moving splashes
    // and adding water from splashes to drops when necessary
    do {
        std::vector<std::shared_ptr<Drop> > growingDrops;

        moveSplashes(growingDrops);
        graphicalGameBoard_.animate();

        // Test printing to console:
        // Put to use by removing comment in the next line
        // print(std::cout, splashes_);

        // Going through all those drops that will added water
        for (auto const& drop : growingDrops) {
            drop->addWater(splashes_);

            // Updating the images of water drops
            if (dropAt(drop->getX(), drop->getY()) == nullptr) {
                // If added water made a drop to pop, the image of the drop
                // will be removed
                graphicalGameBoard_.removeDrop(drop->getX(), drop->getY());
            }
            else {
                // Otherwise changing the image
                graphicalGameBoard_.updateDrop(drop->getX(), drop->getY());
            }
        }

    } while(splashes_.size() > 0);  // Repeated until there are no more splashes

    // Checking if the game is over
    if (waterTank_ <= 0 or isEmpty()) {
        int messageBoxResult = 0;

        if (isEmpty()) {
            messageBoxResult = QMessageBox::question(0,
                                                     "Level completed!",
                                                     "Continue playing?",
                                                     QMessageBox::Yes,
                                                     QMessageBox::No);
        } else {
            messageBoxResult = QMessageBox::question(0,
                                                     "Oops!",
                                                     "No more water. Try again?",
                                                     QMessageBox::Yes,
                                                     QMessageBox::No);
        }

        if (messageBoxResult == QMessageBox::Yes) {
            initialize();
        } else {
            emit quitGame();
        }
    }
}

void GameEngine::moveSplashes(std::vector<std::shared_ptr<Drop> >& grownDrops)
{
    // Container for new splashes that have born due to moving.
    // They cannot be inserted to container splashes_ immediately,
    // because they must wait until the next iteration.
    std::vector<Splash> newSplashes;

    // All the splashes on the board will be gone through by the iterator
    // in the while loop.
    std::vector<Splash>::iterator r = splashes_.begin();
    while (r != splashes_.end()) {

        // Saving the start position of the splash.
        int beginX = r->getX();
        int beginY = r->getY();

        // Calling move for each splash, which returns true, if the splash
        // moves outside the game board and becomes removable.
        // This return value is saved.
        bool remove = r->move();

        // Saving the end position of the splash and adding to animation.
        int endX = r->getX();
        int endY = r->getY();
        graphicalGameBoard_.addSplash(beginX, beginY, endX, endY);

        // If the splash is after move at a square with water drop,
        // the drop is added with water and the splash will be removed.
        std::shared_ptr<Drop> drop = dropAt(endX, endY);

        if(not remove and drop != nullptr) {
            remove = true;
            grownDrops.push_back(drop);
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

void GameEngine::print(std::ostream& stream, std::vector<Splash>& splashes)
{
    stream << "\n  ";
    for(int x = 0; x < SIZE; ++x) {
        stream << (x+1) % 10 << ' ';
    }
    stream << std::endl;

    for(int y = 0; y < SIZE; ++y) {
        stream << (y + 1) % 10 << ' ';
        for(int x = 0; x < SIZE; ++x) {
            if(board_.at(y).at(x) != 0) {
                board_.at(y).at(x)->print(stream);
                stream << " ";
            } else {
                // If the square has no drops, we must still check,
                // whether to print an empty square or a square with splashes
                stream << droplessSquareChar(x, y, splashes) << " ";
            }
        }
        stream << std::endl;
    }
}

char GameEngine::droplessSquareChar(int x,
                                    int y,
                                    std::vector<Splash>& splashes) const
{
    // Checking if the square has splashes.
    // Saving the printing character of each splash to string characters.
    std::string characters = "";
    for(auto r: splashes) {
        if(r.getX() == x and r.getY() == y) {
            characters += r.getChar();
        }
    }

    if(characters.length() == 0) { // No splashes in the square
                                   // -> printing empty
        return ' ';
    } else if (characters.length() == 1){  // A single splash
                                           // -> printing its character
        return characters.at(0);
    } else {  // Several splashes in the same square
        for(auto character: characters){
            if(character != characters.at(0)){
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

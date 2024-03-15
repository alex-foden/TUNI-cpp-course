#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include <vector>
#include <string>

// Pelilaudan alkioiden tyyppi.
// Type of the elements in the gameboa
enum Element_type {ZERO, ONE, EMPTY};

// Vakiot pelilaudan koon määrittelemiseen.
// Constants for the size of the gameboard.
const int NUMBER_OF_SYMBOLS = 3;
const int SIZE = 2 * NUMBER_OF_SYMBOLS;

// Vakio todennäköisyysjakauman ylärajaa varten.
// Nollilla ja ykkösillä on sama todennäköisyys, vaikkapa x, ja tyhjien
// todennäköisyyden voidaan arvioida olevan 6x, jolloin jakaumassa
// on yhteensä kahdeksan pistettä (lukua), joten sopiva väli on esim. [0..7].
//
// Constant for the upper bound of probability distribution.
// Zeros and ones have the same probability, say x, and the estimated
// probability of empties is 6x, whereupon their sum is 8x, and thus,
// the interval must have eigth points, as [0..7].
const int DISTR_UPPER_BOUND = 7;

// Vasemmanpuoleisimman sarakkeen koko, tarvitaan pelilaudan tulostamisessa.
// Width of the left-most column, needed in printing the gameboard.
const unsigned int LEFT_COLUMN_WIDTH = 5;

class GameBoard
{
public:
    // Rakentaja.
    // Constructor. Calls init() to fill the board with EMPTYs.
    GameBoard();

    // Fills the gameboard randomly with three symbols (ZERO, ONE, EMPTY)
    // such that every fourth element is non-empty.
    // Checks the given seed and returns true if it is not one of BAD_SEEDs,
    // otherwise returns false.
    bool fill_randomly(unsigned int seed);

    // Fills the gameboard from the given input.
    // Checks if the input size is correct and if it has only legal symbols.
    // If this holds true, i.e. if filling is possible, returns true,
    // otherwise returns false.
    bool fill_from_input(const std::string& input);

    // Checks if the gameboard has at most two adjacent ZEROs and at most two
    // adjacent ONEs in each row and column.
    // If this is the case, returns true, otherwise returns false.
    // Calls the methods has_permissible_in_rows and has_permissible_in_columns
    // with both ZERO and ONE as a parameter.
    bool ok_adjacent_symbols() const;

    // Checks if each row and column of the gameboard has at most
    // NUMBER_OF_SYMBOLS symbols.
    // If this is the case, returns true, otherwise returns false.
    bool ok_amount_of_symbols() const;

    // Adds the given symbol in the given coordinates of the gameboard.
    // However, this is done only if both has_permissible_adjacent_symbols
    // and has_permissible_amount_of_symbols return true.
    // Returns true, if adding was done, otherwise returns false.
    bool add_symbol(unsigned int x, unsigned int y, char symbol_char);

    // Returns true, if the game is over, i.e. if there are no EMPTYs in the
    // gameboard.
    bool is_game_over() const;

    // Tulostaa pelilaudan.
    // Prints the gameboard.
    void print() const;

private:
    // Inits the gameboard, i.e. fills it with EMPTYs.
    void init();

    // Tulostaa annetun pituisen rivin annettua merkkiä.
    // Prints a line with the given length and the given character.
    void print_line(unsigned int length, char fill_character) const;

    // Goes through all rows in the gameboard and checks if there are
    // at most two adjacent occurrences of the given elem in each row.
    // If this is the case, returns true, otherwise returns false.
    bool ok_adjacent_syms_in_rows(Element_type elem) const;

    // Goes through all columns in the gameboard and checks if there are
    // at most two adjacent occurrences of the given elem in each column.
    // If this is the case, returns true, otherwise returns false.
    bool ok_adjacent_syms_in_columns(Element_type elem) const;

    // Gameboard
    std::vector<std::vector<Element_type>> board_;

    // Ratkaisemattoman pelilaudan tuottavat siemenluvut väliltä [1..50].
    // A list of seed values from [1..50] that produce non-solvable gameboard.
    const std::vector<unsigned int> BAD_SEEDS = { 2, 8, 12, 13, 16, 20, 21, 23,
                                                  26, 29, 31, 32, 34, 41, 42,
                                                  43, 44, 46 };
};

#endif // GAMEBOARD_HH

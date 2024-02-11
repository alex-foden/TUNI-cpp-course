//Ohjelman kirjoittaja
//Nimi: Alex Foden
//Opiskelijanumero: 152492647
//Käyttäjätunnus: cxm844
//E-Mail: alex.foden@tuni.fi


#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

// Pelilaudan alkioiden tyyppi.
enum Element_type {ZERO, ONE, EMPTY};

// Vakiot pelilaudan koon määrittelemiseen.
const int NUMBER_OF_SYMBOLS = 3;
const int SIZE = 2 * NUMBER_OF_SYMBOLS;

// Vakio todennäköisyysjakauman ylärajaa varten.
// Nollilla ja ykkösillä on sama todennäköisyys, vaikkapa x, ja tyhjien
// todennäköisyyden voidaan arvioida olevan 6x, jolloin jakaumassa
// on yhteensä kahdeksan pistettä (lukua), joten sopiva väli on esim. [0..7].
const int DISTR_UPPER_BOUND = 7;

// Vasemmanpuoleisimman sarakkeen koko, tarvitaan pelilaudan tulostamisessa.
const unsigned int LEFT_COLUMN_WIDTH = 5;


class GameBoard
{
public:
    // Rakentaja.
    GameBoard();

    // Tulostaa pelilaudan.
    void print() const;

    // Täyttää pelilaudan satunnaisesti valituilla merkeillä
    void randomize_board(const int seed);

    // Täyttää pelilaudan manuaalisesti valituilla merkeillä
    void set_board(const std::vector<char> input);

    // Tarkistaa että annettu merkki voi lisätä annettuun kohtaan kun 1. Ruutu on tyhjä.
    // 2. Rivillä tai sarakkeella ei ole jo 3 samaa merkkiä.
    // Lopuksi lisää valittuun ruutuun annetun merkin
    // TODO: lisää tarkistus
    // 3. Rivillä tai sarakkeella ei ole yli 2 samaa merkkiä putkeen.
    bool fill_gridspace_with_check(const int x, const int y, const char input);

    // Tarkistaa onko pelilauta täynnä numeroita (peli on silloin ohi).
    bool is_game_over();

    // 6x6 tyhjä pelilauta.
    std::vector<std::vector<char>> board;

    // Ratkaisemattoman pelilaudan tuottavat siemenluvut väliltä [1..50].
    const std::vector<unsigned int> BAD_SEEDS = { 2, 8, 12, 13, 16, 20, 21, 23,
                                                  26, 29, 31, 32, 34, 41, 42,
                                                  43, 44, 46 };

private:
    // Tulostaa annetun pituisen rivin annettua merkkiä.
    void print_line(unsigned int length, char fill_character) const;
};

#endif // GAMEBOARD_HH

//Ohjelman kirjoittaja
//Nimi: Alex Foden
//Opiskelijanumero: 152492647
//Käyttäjätunnus: cxm844
//E-Mail: alex.foden@tuni.fi


#include "gameboard.hh"
#include <string>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

using namespace std;


GameBoard::GameBoard():
    // Tyhjä pelilauta´
    board({
        {' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' '}, }){
}

void GameBoard::print() const
{
    // Tulostetaan yläreuna
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '=');

    // Tulostetaan otsikkorivi
    cout << "|   | ";
    for(unsigned int i = 0; i < SIZE; ++i)
    {
        cout << i + 1 << " ";
    }
    cout << "|" << endl;

    // Tulostetaan viiva otsikkorivin alle
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '-');

    // Tulostetaan pelilaudan varsinainen sisältö
    for(unsigned int row = 0; row < SIZE; ++row)
    {
        cout << "| " << row + 1 << " | ";
        for(unsigned int column = 0; column < SIZE; ++column)
        {
            cout << board[row][column] << " ";
        }
        cout << "|" << endl;
    }

    // Tulostetaan alareuna
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '=');
}

void GameBoard::randomize_board(const int seed)
{
    default_random_engine gen(seed);
    uniform_int_distribution<int> distr(0, DISTR_UPPER_BOUND);

    // Alustaa pelilaudan lisäämällä jokaiseen ruutuun satunnaisesti valittu merkki
    for(unsigned int row = 0; row < SIZE; ++row)
    {
        for(unsigned int column = 0; column < SIZE; ++column)
        {
            int symbol = distr(gen);
            // TODO: käyttä enum Element_Type paremmin
            if(symbol == ZERO)
            {
                board[row][column] = '0';
            }

            if(symbol == ONE)
            {
                board[row][column] = '1';
            }

            // jos distr(gen) == väliltä 2-7: jätä ruutu tyhjäksi.
            // näin ruudulla on 3/4 mahdollisuus olla tyhjä, joka
            // minimizoi mahdottoman aloitustilan tapahtumista.
        }
    }
}

void GameBoard::set_board(const vector<char> input)
{
    int symbol = 0; // merkitsee mitä ruutua luetaan inputista/täytetään pelilautaan

    // Alustaa pelilaudan lisäämällää jokaiseen ruutuun saman kohdan merkki inputista
    for(unsigned int row = 0; row < SIZE; ++row)
    {
        for(unsigned int column = 0; column < SIZE; ++column)
        {
            board[row][column] = input[symbol];
            symbol++;
        }
    }
}

bool GameBoard::fill_gridspace_with_check(int x, int y, const char input)
{
    x -= 1; // Vektorin indeksi alkaa 0:sta
    y -= 1;
    int zeroes_in_row = 0;
    int ones_in_row = 0;
    int zeroes_in_column = 0;
    int ones_in_column = 0;

    vector<char> row;
    vector<char> column;

    // Jos merkin haluttu sijainti ei ole tyhjä, palauta epätosi.
    if(board[y][x] != ' ') {return false;}

    else // Ruutu on tyhjä
    {
        // Lisää merkki ruutuun valmiiksi testausta varten.
        board[y][x] = input;

        for(unsigned int i = 0; i < SIZE; ++i)
        {
            row.push_back(board[y][i]);
            column.push_back(board[i][x]);
        }

        // Lasketaan jokaisen merkin määrä rivillä ja sarakkeella
        zeroes_in_row = count(row.begin(), row.end(), '0');
        ones_in_row = count(row.begin(), row.end(), '1');
        zeroes_in_column = count(column.begin(), column.end(), '0');
        ones_in_column = count(column.begin(), column.end(), '1');

        // Tyhjennä ruutu ja palauta epätosi, jos rivillä tai sarakkeella on yli 3 samaa merkkiä.
        if(zeroes_in_row > 3 or ones_in_row > 3 or zeroes_in_column > 3 or ones_in_column > 3)
        {
            board[y][x] = ' ';
            return false;
        }
        // TODO: tarkista että merkin sijainti noudattaa sääntöjä
    }

    // Tässä vaiheessa merkki on läpäissyt kaikki testit, eli sen sijainti on validi. Palauta tosi.
    return true;
}

bool GameBoard::is_game_over()
{
    // Jos mikään ruutu on tyhjä, peli ei ole ohi.
    for(unsigned int row = 0; row < SIZE; ++row)
    {
        for(unsigned int column = 0; column < SIZE; ++column)
        {
            if(board[row][column] == ' ')
            {
                return false;
            }
        }
    }
    // Muuten jokainen ruutu täytyy olla täytetty eli peli on ohi.
    return true;
}

void GameBoard::print_line(unsigned int length, char fill_character) const
{
    for(unsigned int i = 0; i < length; ++i)
    {
        cout << fill_character;
    }
    cout << endl;
}

//Ohjelman kirjoittaja
//Nimi: Alex Foden
//Opiskelijanumero: 152492647
//Käyttäjätunnus: cxm844
//E-Mail: alex.foden@tuni.fi


#include "gameboard.hh"
#include <iostream>
#include <random>
#include <string>
#include <vector>

GameBoard::GameBoard():
    board({
        {" ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " "},
        {" ", " ", " ", " ", " ", " "} }){
}

void GameBoard::print() const
{
    // Tulostetaan yläreuna
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '=');

    // Tulostetaan otsikkorivi
    std::cout << "|   | ";
    for(unsigned int i = 0; i < SIZE; ++i)
    {
        std::cout << i + 1 << " ";
    }
    std::cout << "|" << std::endl;

    // Tulostetaan viiva otsikkorivin alle
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '-');

    // Tulostetaan pelilaudan varsinainen sisältö
    for(unsigned int row = 0; row < SIZE; ++row)
    {
        std::cout << "| " << row + 1 << " | ";
        for(unsigned int column = 0; column < SIZE; ++column)
        {
            std::cout << board[row][column] << " ";
        }
        std::cout << "|" << std::endl;
    }

    // Tulostetaan alareuna
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '=');
}

void GameBoard::randomize_board(const int seed)
{

    std::default_random_engine gen(seed);
    std::uniform_int_distribution<int> distr(0, DISTR_UPPER_BOUND);

    for(unsigned int row = 0; row < SIZE; ++row)
    {
        for(unsigned int column = 0; column < SIZE; ++column)
        {
            int symbol = distr(gen);

            if(symbol == ZERO)
            {
                board[row][column] = "0";
            }

            if(symbol == ONE)
            {
                board[row][column] = "1";
            }

            // jos distr(gen) == väliltä 2-7: jätä ruutu tyhjäksi.
            // näin ruudulla on 3/4 mahdollisuus olla tyhjä, joka
            // minimizoi mahdottoman aloitustilan tapahtumista.
        }
    }
}

void GameBoard::set_board(const std::vector<char> input)
{
    int symbol = 0; // merkitsee mitä ruutua luetaan inputista/täytetään pelilautaan

    for(unsigned int row = 0; row < SIZE; ++row)
    {
        for(unsigned int column = 0; column < SIZE; ++column)
        {
            board[row][column] = input[symbol];
            symbol++;
        }
    }
}

bool GameBoard::is_game_over()
{
    // Jos mikään ruutu on tyhjä, peli ei ole ohi.
    for(unsigned int row = 0; row < SIZE; ++row)
    {
        for(unsigned int column = 0; column < SIZE; ++column)
        {
            if(board[row][column] == " ")
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
        std::cout << fill_character;
    }
    std::cout << std::endl;
}

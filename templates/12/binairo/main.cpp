#include "gameboard.hh"
#include <iostream>

using namespace std;

// Tulosteet
// Output messages
const string QUIT = "Quitting ...";
const string OUT_OF_BOARD = "Out of board";
const string INVALID_INPUT = "Invalid input";
const string CANT_ADD = "Can't add";
const string WIN = "You won!";

// Muuttaa numeerisen merkkijonon vastaavaksi kokonaisluvuksi
// (kutsumalla stoi-funktiota) ja palauttaa tämän kokonaisluvun.
// Jos annettu merkkijono ei ollut numeerinen, palauttaa nollan.
//
// Converts the given numeric string to the corresponding integer
// (by calling stoi) and returns the integer.
// If the given string is not numeric, returns zero.
unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric)
    {
        return stoi(str);
    }
    else
    {
        return 0;
    }
}

// Poistaa tyhjät merkit (kuten ' ') annetusta merkkijonosta.
// Palauttaa toden, jos annetussa merkkijonossa on täsmälleen yksi ei-tyhjä
// merkki, joka on '0' tai '1', muussa tapauksessa palauttaa epätoden.
//
// Removes empty characters (such as ' ' etc.) from the given string.
// Returns true if the given string has exactly one non-empty character,
// which is either '0' or '1', otherwise returns false.
bool find_fill_symbol(string& str)
{
    string fill_str = "";
    for(unsigned int i = 0; i < str.size(); ++i)
    {
        if(not isspace(str.at(i)))
        {
            fill_str += str.at(i);
        }
    }
    str = fill_str;
    return (fill_str.size() == 1 and
           (fill_str.at(0) == '0' or fill_str.at(0) == '1'));
}

// Mahdollistaa pelin pelaamisen eli kysyy toistuvasti lisättävää merkkiä
// ja sen sijaintia, kunnes peli päättyy.
//
// Enables the user to play the game, i.e. by repeatedly asking an element
// to be added and its position, until the game is over.
void play_game(GameBoard& board)
{
    board.print();
    while(not board.is_game_over())
    {
        string x_str = "";
        string y_str = "";
        string rest_input = "";
        cout << "Enter two coordinates and a fill symbol, or q to quit: ";

        // Luetaan x-koordinaatti merkkijonona ja tarkistetaan, oliko kyseessä
        // lopetuskomento
        //
        // Reading x coordinate as a string and checking if it was quit command
        cin >> x_str;
        if(x_str.at(0) == 'q' or x_str.at(0) == 'Q')
        {
            cout << QUIT << endl;
            return;
        }

        // Luetaan y-koordinaatti
        // Reading y coordinate
        cin >> y_str;

        // Muutetaan koordinaatit merkkijonoista kokonaisluvuiksi ja
        // tarkistetaan, ovatko ne pelilaudan sisällä
        //
        // Changing coordinates from string to int and checking if they are
        // inside the board
        unsigned int x = stoi_with_check(x_str);
        unsigned int y = stoi_with_check(y_str);
        if(not (1 <= x and x <= SIZE and 1 <= y and y <= SIZE))
        {
            cout << OUT_OF_BOARD << endl;
            getline(cin, rest_input);
            continue;
        }

        // Luetaan loppusyöte, joka sisältää täyttömerkin, ja tarkistetaan,
        // koostuuko loppusyöte täsmälleen yhdestä merkistä '0' tai '1'
        //
        // Reading the rest of the input line including fill symbol and
        // checking if the rest input consists exactly of one '0' or '1'
        getline(cin, rest_input);
        if(not find_fill_symbol(rest_input))
        {
            cout << INVALID_INPUT << endl;
            continue;
        }

        // Tässä kohdassa tiedetään, että syöte oli hyväksyttävä, mutta ei
        // ole varmaa, voidaanko annettu merkki lisätä annettuun kohtaan
        //
        // At this point, we know that the input is valid, but we don't know
        // if it is possible to add the given symbol on the given position
        --x;
        --y;
        if(not board.add_symbol(x, y, rest_input.at(0)))
        {
            cout << CANT_ADD << endl;
            continue;
        }

        // Jos annettu merkki voitiin lisätä, tulostetaan muuttunut pelilauta
        // If the given symbol was possible to add, print the changed gameboard
        board.print();
    }
    // Jos peli päättyy täyteen pelilautaan, pelaaja voitti
    // If the game ends up to a totally filled gameboard, the player won
    cout << WIN << endl;
}

// Kysyy käyttäjältä pelilaudan täyttötapaa.
// Palauttaa toden, jos pelilaudan täyttäminen onnistui,
// muuten palauttaa epätoden.
//
// Gives the user a possibility to select a filling way.
// Returns true if filling succeeded, otherwise returns false.
bool select_start(GameBoard& board)
{
    string choice = "";
    cout << "Select start (R for random, I for input): ";
    getline(cin, choice);
    if(choice != "R" and choice != "r" and choice != "I" and choice != "i")
    {
        return false;
    }
    else if(choice == "R" or choice == "r")
    {
        string seed_string = "";
        cout << "Enter a seed value: ";
        getline(cin, seed_string);
        return board.fill_randomly(stoi_with_check(seed_string));
    }
    else // if(choice == "I" or choice == "i")
    {
        string input = "";
        cout << "Input: ";
        getline(cin, input);
        return board.fill_from_input(input);
    }
}

// Lyhyt ja yksinkertainen pääohjelma.
// Short and simple main function.
int main()
{
    GameBoard board;
    while(not select_start(board)); // ei toistettavaa koodia
                                    // no code to be repeated
    play_game(board);
    return 0;
}

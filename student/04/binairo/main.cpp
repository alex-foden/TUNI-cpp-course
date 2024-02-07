/* Binairo
 *
 * Kuvaus:
 *   Ohjelma toteuttaa Binairo-pelin. Pelissä on peliruudukko kooltaan 6 x 6.
 * Kukin ruutu sisältää nollan, ykkösen tai tyhjän. Tarkoituksena on lisätä
 * tyhjiin ruutuihin nollia ja ykkösiä seuraavien sääntöjen mukaisesti:
 * - kullakin vaaka- ja pystyrivillä saa olla korkeintaan kolme samaa lukua
 * - kullakin vaaka- ja pystyrivillä saa olla peräkkäin korkeintaan kaksi
 *   samaa lukua.
 *   Aluksi käyttäjältä kysytään, täytetäänkö peliruudukko satunnaisesti
 * arvottavilla merkeillä vai käyttäjän valitsemilla 36 merkillä.
 * Ensimmäisessä vaihtoehdossa käyttäjältä kysytään satunnaisluku-
 * generaattorin siemenlukua ja jälkimmäisessä häntä pyydetään syöttämään
 * 36 merkkiä, joiden oikeellisuus tarkistetaan.
 *   Joka kierroksella käyttäjältä kysytään lisättävän merkin koordinaatteja
 * sekä lisättävää merkkiä eli kolmea merkkiä. Peli päättyy pelaajan voittoon,
 * jos peliruudukko on saatu täytettyä e.m. sääntöjen mukaisesti. Ohjelma ei
 * salli tehdä lisäyksiä, jotka rikkovat e.m. sääntöjä, mutta on mahdollista
 * päätyä tilanteeseen, jossa mikään lisäys ei ole enää mahdollinen.
 *   Ohjelma tarkistaa annetut syötteet. Lisättävän merkin pitää olla nolla
 * tai ykkönen. Koordinaattien pitää olla peliruudukon sisällä, ja niiden
 * osoittaman ruudun pitää olla tyhjä.
 *
 * Ohjelman kirjoittaja
 * Nimi: Alex Foden
 * Opiskelijanumero: 152492647
 * Käyttäjätunnus: cxm844
 * E-Mail: alex.foden@tuni.fi
 *
 * */


#include "gameboard.hh"
#include <iostream>

using namespace std;


// Tulosteet
const string QUIT = "Quitting ...";
const string OUT_OF_BOARD = "Out of board";
const string INVALID_INPUT = "Invalid input";
const string CANT_ADD = "Can't add";
const string WIN = "You won!";

// Muuttaa numeerisen merkkijonon vastaavaksi kokonaisluvuksi
// (kutsumalla stoi-funktiota) ja palauttaa tämän kokonaisluvun.
// Jos annettu merkkijono ei ollut numeerinen, palauttaa nollan.
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
        cin >> x_str;
        if(x_str.at(0) == 'q' or x_str.at(0) == 'Q')
        {
            cout << QUIT << endl;
            return;
        }

        // Luetaan y-koordinaatti
        cin >> y_str;

        // Muutetaan koordinaatit merkkijonoista kokonaisluvuiksi ja
        // tarkistetaan, ovatko ne pelilaudan sisällä
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
        getline(cin, rest_input);
        if(not find_fill_symbol(rest_input))
        {
            cout << INVALID_INPUT << endl;
            continue;
        }

        // Tässä kohdassa tiedetään, että syöte oli hyväksyttävä, mutta ei
        // ole varmaa, voidaanko annettu merkki lisätä annettuun kohtaan
        // TODO: Lisää tämä tarkistus


        // Jos annettu merkki voitiin lisätä, tulostetaan muuttunut pelilauta
        board.print();
    }
    // Jos peli päättyy täyteen pelilautaan, pelaaja voitti
    cout << WIN << endl;
}

// Kysyy käyttäjältä pelilaudan täyttötapaa.
// Palauttaa toden, jos pelilaudan täyttäminen onnistui,
// muuten palauttaa epätoden.
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

        // TODO: Täytä pelilauta ja palauta tieto täytön onnistumisesta
    }
    else // if(choice == "I" or choice == "i")
    {
        string input = "";
        cout << "Input: ";
        getline(cin, input);

        // (Huomaa, että tässä vaiheessa input sisältää vielä lainausmerkit tms.)
        // TODO: Täytä pelilauta ja palauta tieto täytön onnistumisesta
    }
}

// Lyhyt ja yksinkertainen pääohjelma.
int main()
{
    GameBoard board;
    while(not select_start(board)); // ei toistettavaa koodia

    play_game(board);
    return 0;
}

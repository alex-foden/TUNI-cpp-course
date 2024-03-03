/* Education center
 *
 * Kuvaus:
 * Toteuttaa ohjelman, joka lukee käynnistyessään kurssikeskuksen kursseihin liittyviä tietoja csv-tiedostosta,
 * tallentaa ne sopivaan tietorakenteeseen ja antaa käyttäjän tehdä hakuja kyseiseen tietorakenteeseen.
 *
 * Aluksi käyttäjältä kysytään, mistä csv-tiedostosta luetaan kurssitiedot. Ohjelma tarkistaa, että voiko tiedoston avata
 * ja että onko tiedosto oikeassa muodossa. (csv-tiedoston rivissä on 4 saraketta, jossa lukee: kurssin paikkakunta, teema, nimi sekä osallistujamäärä)
 * Täydessä kurssissa on 50 osallistujaa. Jos tiedosto pystyttiin avaamaan ja se on oikeassa muodossa, ohjelma tallentaa kurssitiedot tietorakenteeseen.
 *
 * Tässä vaiheessa ohjelma pyytää käyttäjältä (haku)komennon. Valideja komentoja on (7):
 *
 * (1) quit - Ohjelman suoritus päätty paluuarvoon EXIT_SUCCESS.
 *
 * (2) locations - Tulostaa aakkosjärjestyksessä allekkain kaikki tunnetut paikkakunnat.
 *
 * (3) themes_in_location <paikkakunta> - Tulostaa aakkosjärjestyksessä allekkain kaikki annetun paikkakunnan teemat.
 *
 * (4) courses <paikkakunta> <teema> - Komento tulostaa kaikki kurssit,
 *     jotka löytyvät kyseiseltä paikkakunnalta ja kyseisestä teemasta sekä niiden osallistujamäärät.
 *
 * (5) available - Komento tulostaa näytölle kaikkien paikkakuntien kaikista kursseista ne,
 *     joille voi vielä ilmoittautua eli jotka eivät ole täynnä. Kursseista tulostetaan paikkakunta, teema ja nimi.
 *
 * (6) courses_in_theme <teema> - Komento tulostaa kaikilta paikkakunnilta annettuun teemaan kuuluvat kurssit aakkosjärjestyksessä.
 *
 * (7) favorite_theme - Komento tulostaa suosituimman teeman. Kuhunkin teemaan kuuluvien kurssien osanottajamäärät lasketaan siis yhteen
 *     ja tulostetaan tämä suurin osanottajamäärä sekä teema (tai teemat), joilla on suurin osanottajamäärä.
 *
 * Kun käyttäjän syöttämä komento on suoritettu, ohjelma pyytää uuden komennon. Tätä jatketaan kunnes käyttäjä syöttää käskyn quit.
 *
 * Ohjelman kirjoittaja
 * Nimi: Alex Foden
 * Opiskelijanumero: 152492647
 * Käyttäjätunnus: cxm844
 * E-Mail: alex.foden@tuni.fi
 */

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>

using namespace std;


// csv-tiedostossa esiintyvät tiedot
enum FIELDS {LOCATION, THEME, COURSE_NAME, ENROLLMENTS, FIELDS_COUNT};
const int MAX_ENROLLMENTS = 50;

// Kurssitiedot
struct Course
{
    string name;
    string theme;
    int enrollments;
};

// Education_center tietorakenteen data-tyyppi ja iteraattorit
using Location_info = map<string, vector<Course>>;
using Location_iterator = Location_info::iterator;
using Theme_iterator = map<string, vector<Course>>::iterator;

// Tulosteet
const string FILE_ERROR = "Error: the input file cannot be opened";
const string EMPTY_FIELD = "Error: empty field";

// Lukee käyttäjän antaman csv-tiedoston ja täyttää kurssin tiedot Education_center tietorakenteeseen
// Ottaa parametrinä tietorakenteen, johon kurssitiedot lisätään
// Palauttaa totuusarvon riippuen siitä, että pystyikö tiedoston avaamaan ja tiedosto on oikeassa muodossa (4 saraketta per rivi)
bool read_input_file(Location_info& Education_center);

// Tarkistaa, että käyttäjän antaman csv-tiedoston rivissä ei ole väärä määrä tai tyhjiä sarakkeita
// Ottaa parametrinä string vektorin, joka vastaa csv-tiedoston riviä
// Palauttaa totuusarvon riippuen siitä, onko csv-tiedoston rivi oikeassa muodossa (4 saraketta)
bool check_empty_field(vector<string>& fields);

// Lisää Education_center tietorakenteeseen kurssin.
// Varmistaa, että millään paikkakunnalla ei ole duplikaatti kurssia (jos kurssi on jo tietorakenteessa, kurssin tiedot päivitetään)
// Ottaa parametrinä kurssin paikkakunnan, teeman, nimen ja jäsenmäärän sekä tietorakenteen, johon kurssitiedot lisätään
void insert_course(Location_info& Education_center, string location,
                   string theme, string course, int enrollments);

// Pyytää käyttäjältä komennon. Palauttaa toden, jos käyttäjä syöttää 'quit'. Muuten palauttaa epätoden.
// Ottaa parametrinä tietorakenteen, josta luetaan ja tulostetaan kurssitiedot käyttäjän hakukommennon mukaisesti
bool select_command(Location_info& Education_center);

// Tulostaa aakkosjärjestyksessä allekkain kaikki tunnetut paikkakunnat. Ottaa parametrinä tietorakenteen,
// josta luetaan ja tulostetaan tunnetut paikkakunnat.
void command_locations(Location_info& Education_center);

// Ottaa parametrinä merkkijonon ja merkin, jonka mukaan merkkijono jaetaan. Jakaa merkkijonon vektoriksi ja palauttaa vektorin
std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result; // Mustaa taikaa. Merkkijono on jaettu vektoriksi.
}

bool read_input_file(Location_info& Education_center)
{
    // Kysytään käyttäjältä luettavaa csv-tiedostoa
    string input_file_name = "";
    cout << "Input file: ";
    getline(cin, input_file_name);

    ifstream input_file(input_file_name);

    // Tarkistetaan, että tiedoston pystyy lukea
    if(not input_file)
    {
        input_file.close();
        cout << FILE_ERROR << endl;
        return false;
    }

    string row; // Läpikäydään csv-tiedoston rivit

    while(getline(input_file, row))
    {
        vector<string> fields = split(row, ';');

        // Tarkistetaan, että csv-tiedoston rivi on oikeassa muodossa
        if(not check_empty_field(fields))
        {
            cout << EMPTY_FIELD << endl;
            return false;
        }

        // Alustetaan kurssitiedot csv-tiedoston rivin tiedoilla
        string location = fields.at(LOCATION);
        string theme = fields.at(THEME);
        string course = fields.at(COURSE_NAME);
        int enrollments;

        if(fields.at(ENROLLMENTS) == "full")
        {
            enrollments = MAX_ENROLLMENTS;
        }

        else
        {
            enrollments = stoi(fields.at(ENROLLMENTS));
        }

        // Lisätään kurssi Education_center tietorakenteeseen
        insert_course(Education_center, location, theme, course, enrollments);
    }

    return true; // Palautetaan tosi, koska tiedosto pystyttiin lukea ja se on oikeassa muodossa
}

bool check_empty_field(vector<string>& fields)
{
    // Tarkistaa, että csv-tiedoston rivissä on (4) saraketta
    if(fields.size() != FIELDS_COUNT)
    {
        return false;
    }

    // Tarkistaa, että mikään csv-tiedoston rivin sarake ei ole tyhjä
    for(const string& field: fields)
    {
        if(field.find_first_not_of(' ') == string::npos)
        {
            return false;
        }
    }

    return true; // csv-tiedoston rivi on oikeassa muodossa
}

void insert_course(Location_info& Education_center, string location,
                   string theme, string course_name, int enrollments)
{
    // Alustetaan kurssi annetuilla tiedoilla
    Course course;
    course.name = course_name;
    course.theme = theme;
    course.enrollments = enrollments;

    // Tarkistetaan, että paikkakunnan kurssi ei ole jo listattu tietorakenteeseen. Jos on, päivitetään kurssin tiedot
    for(Course& existing_course: Education_center[location])
    {
        if(existing_course.name == course_name and
           existing_course.theme == course.theme)
        {
            existing_course.enrollments = course.enrollments;
            return;
        }
    }

    // Muuten lisätään kurssi Education_center tietorakenteseen
    Education_center[location].push_back(course);
}

bool select_command(Location_info& Education_center)
{
    // Tallennetaan käyttäjän antama komento
    string input;
    cout << "> ";
    getline(cin, input);

    // Jaetaan käyttäjän syöte osiin, sillä jotkut komennot ottaa monta syötettä
    vector<string> command = split(input, ' ');

    if(command.at(0) == "quit")
    {
        return true; // Palauttaa toden, koska ohjelma on pysäytetty
    }

    if(command.at(0) == "locations")
    {
        command_locations(Education_center); // Tulostetaan paikkakunnat
    }

    return false; // Palauttaa epätoden, koska ohjelma ei ole pysäytetty
}

void command_locations(Location_info& Education_center)
{
    // Läpikäydään map-tietorakenne ja tulostetaan avaimet (paikkakunnat)
    for(const pair<const string, vector<Course>>& tmp: Education_center)
    {
        string location = tmp.first;

        cout << location << endl;
    }
}

// Lyhyt ja yksinkertain main funktio
int main()
{
    // map-tietorakenne, jonka avain on paikkakunta ja arvo on vektori kursseja
    Location_info Education_center;

    // Lukee käyttäjän antaman csv-tiedoston ja täyttää Education_center tietorakenteen.
    // Palauttaa false jos tiedostoa ei voi avata tai tiedosto on väärän muotoinen
    if (not read_input_file(Education_center))
    {
        return EXIT_FAILURE;
    }

    // Pyydetään käyttäjältä komentoja kunnes käyttäjä pysäyttää ohjelman
    while(not select_command(Education_center));

    return EXIT_SUCCESS;
}

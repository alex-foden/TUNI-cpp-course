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
#include <sstream>
#include <algorithm>

using namespace std;


// csv-tiedostossa esiintyvät tiedot
enum FIELDS {LOCATION, THEME, COURSE_NAME, ENROLLMENTS, FIELDS_COUNT};
const int MAX_ENROLLMENTS = 50; // Täydessä kurssissa on 50 opiskelijaa

// Kurssitiedot
struct Course
{
    string name;
    string theme;
    int enrollments;
};

// Education_center tietorakenteen data-tyyppi ja iteraattorit
using Location_info = map<string, vector<Course>>;

// Tulosteet
const string FILE_ERROR = "Error: the input file cannot be opened";
const string EMPTY_FIELD = "Error: empty field";
const string NO_ENROLLMENTS = "No enrollments";
const string UNKNOWN_LOCATION = "Error: unknown location";
const string UNKNOWN_LOCATION_NAME = "Error: unknown location name";
const string UNKNOWN_THEME = "Error: unknown theme";
const string ERROR_IN_COMMAND = "Error: error in command ";
const string UNKNOWN_COMMAND = "Error: Unknown command: ";

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

// Tulostaa aakkosjärjestyksessä allekkain kaikki annetun paikkakunnan teemat. Ottaa parametrinä tietorakenteen,
// josta luetaan ja tulostetaan tunnetut teemat sekä paikkakunnan, johon haku kohdennetaan.
void command_themes_in_location(Location_info& Education_center, string location);

// Tulostaa kurssin nimen mukaisessa aakkosjärjestyksessä kaikki kyseisen paikkakunnan kurssit,
// jotka löytyvät kyseiseltä paikkakunnalta ja kyseisestä teemasta sekä osallistujamäärät.
// Ottaa parametrina tietorakenteen, josta kurssitiedot luetaan sekä käyttäjän syöttämän paikkakunnan ja teeman, johon haku kohdennetaan.
void command_courses(Location_info& Education_center, string location, string theme);

// Tulostaa näytölle kaikkien paikkakuntien kaikista kursseista ne, joille voi vielä ilmoittautua eli
// jotka eivät ole täynnä. Kursseista tulostetaan aakkosjärjestyksessä paikkakunta, teema ja kurssin nimi
// Ottaa parametrinä tietorakenteen, josta kurssin tiedot luetaan.
void command_available(Location_info& Education_center);

// Tulostaa kaikilta paikkakunnilta annettuun teemaan kuuluvat kurssit aakkosjärjestyksessä.
// Ottaa parametrinä tietorakenteen, josta kurssin tiedot luetaan sekä teeman, johon haku kohdennetaan.
void command_courses_in_theme(Location_info& Education_center, string theme);

// Tulostaa suosituimmat teemat ja niiden osallistujamäärät.
// Ottaa parametrinä tietorakenteen, josta kurssin tiedot luetaan.
void command_favorite_theme(Location_info& Education_center);

// Ottaa parametrinä merkkijonon ja delimiter merkin, jonka mukaan merkkijono jaetaan.
// Jakaa merkkijonon vektoriksi delimiterin mukaan. Teksti lainausmerkkien sisällä ei jaeta.
// Esimerkkitoiminta:
// string input = "courses Vesilahti "Information technology"" -> vector<string> output = {"courses", "Vesilahti", "Information technology"}
std::vector<std::string> split(const std::string& input, const char delimiter)
{
    std::vector<std::string> output;
    bool flag = false;
    output.push_back("");
    for(unsigned int character=0; character<input.size(); ++character)
    {
        if(input[character]=='"')
        {
            flag = flag? false : true;
            continue;
        }

        if(input[character]==delimiter && !flag)
            output.push_back("");
        else
            output[output.size()-1] += input[character];
    }
    return output;
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

        // Alustetaan kurssitiedot nimettyihin muuttujiin csv-tiedoston rivin tiedoilla
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
        if(existing_course.name == course.name and
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
    // Käyttäjän hakukomentojen muoto: "COMMAND (PARAMETER1) (PARAMETER2)"
    enum commands {COMMAND, PARAMETER1, PARAMETER2};

    // Tallennetaan käyttäjän antama komento
    string input_string;
    cout << "> ";
    getline(cin, input_string);

    // Jaetaan käyttäjän syöte osiin, sillä jotkut komennot ottavat monta syötettä (komento + parametrit)
    vector<string> input = split(input_string, ' ');

    // Tallennetaan käyttäjän komento
    string command = input.at(COMMAND);

    if(command == "quit")
    {
        // Tarkistetaan että käyttäjä syötti komennon oikein
        if(input.size() != 1) // (quit ei ota parametreja)
        {
            cout << ERROR_IN_COMMAND << command << endl;
            return false;
        }

        return true; // Palautetaan tosi, koska ohjelma on pysäytetty
    }

    else if(command == "locations")
    {
        // Tarkistetaan että käyttäjä syötti komennon oikein
        if(input.size() != 1) // (location ei ota parametreja)
        {
            cout << ERROR_IN_COMMAND << command << endl;
            return false;
        }

        command_locations(Education_center); // Tulostetaan paikkakunnat
    }

    else if(command == "themes_in_location")
    {
        // Tarkistetaan, että käyttäjä syötti paikkakunnan, josta teemat haetaan
        if(input.size() != 2) // themes_in_location ottaa (1) parametria
        {
            cout << ERROR_IN_COMMAND << command << endl;
            return false;
        }

        string theme = input.at(PARAMETER1); // Tallennetaan 1. parametri (teema)

        // Tulostetaan paikkakunnan teemat
        command_themes_in_location(Education_center, theme);
    }

    else if(command == "courses")
    {
        // Tarkistetaan, että käyttäjä syötti paikkakunnan ja teeman, josta kurssit haetaan
        if(input.size() != 3) // themes_in_location ottaa (2) parametria
        {
            cout << ERROR_IN_COMMAND << command << endl;
            return false;
        }

        string location = input.at(PARAMETER1); // Tallennetaan 1. parametri (paikkakunta)
        string theme = input.at(PARAMETER2); // Tallennetaan 2. parametri (teema)

        // Tulostetaan paikkakuntaan ja teemaan kuuluvat kurssit ja osallistujamäärät
        command_courses(Education_center, location, theme);
    }

    else if(command == "available")
    {
        // Tarkistetaan, että käyttäjä syötti komennon oikein
        if(input.size() != 1) // (available ei ota parametreja)
        {
            cout << ERROR_IN_COMMAND << command << endl;
            return false;
        }

        // Tulostetaan kurssit sekä niiden teemat ja paikkakunnat, jotka eivät ole täynnä
        command_available(Education_center);
    }

    else if(command == "courses_in_theme")
    {
        // Tarkistetaan, että käyttäjä syötti teeman
        if(input.size() != 2) // courses_in_theme ottaa (1) parametria
        {
            cout << ERROR_IN_COMMAND << command << endl;
            return false;
        }

        string theme = input.at(PARAMETER1); // Tallennetaan 1. parametri (teema)

        command_courses_in_theme(Education_center, theme);
    }

    else if(command == "favorite_theme")
    {
        // Tarkistetaan, että käyttäjä syötti komennon oikein
        if(input.size() != 1) // (favorite_theme ei ota parametreja)
        {
            cout << ERROR_IN_COMMAND << command << endl;
            return false;
        }

        command_favorite_theme(Education_center);
    }

    // Jos käyttäjän syöttämä komento ei ole mikään edellisistä, tulostetaan tieto käyttäjälle että ohjelma ei tunnista komentoa
    else
    {
        cout << UNKNOWN_COMMAND << command << endl;
    }

    return false; // Palautetaan epätosi, koska ohjelma ei ole pysäytetty
}

void command_locations(Location_info& Education_center)
{
    // Läpikäydään map-tietorakenne ja tulostetaan avaimet (paikkakunnat)
    for(const pair<const string, vector<Course>>& course: Education_center)
    {
        string location = course.first;

        cout << location << endl;
    }
}

void command_themes_in_location(Location_info& Education_center, string location)
{
    // Tallenetaan kaikki teemat, jotka käyttäjän hakeman paikkakunnan kursseista
    vector<string> themes;

    // Tarkistetaan, että löytyykö paikkakunta tietorakenteesta
    if(Education_center.find(location) == Education_center.end())
    {
        cout << UNKNOWN_LOCATION << endl;
        return;
    }

    // Läpikäydään paikkakunnan kurssit ja varmistetaan, että ei tulosteta samaa teema moneen kertaan
    for(const Course& course: Education_center.at(location))
    {
        string theme = course.theme;

        if(find(themes.begin(), themes.end(), theme) == themes.end())
        {
            themes.push_back(theme);
        }
    }

    // Lajitellaan teemat aakkosjärjestykseen
    sort(themes.begin(), themes.end());

    // Tulostetaan paikkakunnan teemat
    for(const string& theme: themes)
    {
        cout << theme << endl;
    }
}

void command_courses(Location_info& Education_center, string location, string theme)
{
    // Tallennetaan käyttäjän hakemaan paikkakuntaan ja teemaan kuuluvat kurssit (avain) ja niiden osallistujamäärät (arvo
    map<string, int> courses;

    // Tarkistetaan, että paikkakunta löytyy tietorakenteesta
    if(Education_center.find(location) == Education_center.end())
    {
        cout << UNKNOWN_LOCATION_NAME << endl;
        return;
    }

    // Lisätään map-säiliöön ne kurssit ja niiden osallistujamäärät, jotka kuuluvat käyttäjän hakemaan teemaan
    for(const Course& course: Education_center.at(location))
    {
        if(course.theme == theme)
        {
            courses[course.name] = course.enrollments;
        }
    }

    // Tarkistetaan, että löytyykö kursseja, jotka kuuluvat haettuun teemaan
    if(courses.empty())
    {
        cout << UNKNOWN_THEME << endl;
        return;
    }

    // Tulostetaan kurssit ja niiden osallistujamäärät, jotka kuuluvat käyttäjän hakemaan paikkakuntaan ja teemaan
    for(const pair<const string, int>& course: courses)
    {
        string course_name = course.first;
        int enrollments = course.second;

        // Jos kurssi on täynnä, tulostetaan tieto käyttäjän luettavaksi
        if(enrollments == MAX_ENROLLMENTS)
        {
            cout << course_name << " --- " << "full" << endl;
            continue;
        }

        // Muuten tulostetaan osallistujamäärä lukuna
        cout << course_name << " --- " << enrollments << " enrollments" << endl;
    }
}

void command_available(Location_info& Education_center)
{
    // Tallennetaan tulosteet vektoriin jotta ne voidaan lajitella aakkosjärjestykseen
    vector<string> available_courses;

    // Läpikäydään kaikki kurssit ja tallennetaan ne, jotka eivät ole täynnä
    for(const pair<const string, vector<Course>>& tmp: Education_center)
    {
        string location = tmp.first;

        for(const Course& course: tmp.second)
        {
            if(course.enrollments < MAX_ENROLLMENTS)
            {
                // Tuloste näyttää tolta
                available_courses.push_back(location + " : " + course.theme + " : " + course.name);
            }
        }
    }

    // Lajittellaan tulosteet aakkosjärjestykseen
    sort(available_courses.begin(), available_courses.end());

    // Tulostetaan kaikki avoimet kurssit sekä niiden paikkakunnat ja teemat
    for(const string& output: available_courses)
    {
        cout << output << endl;
    }
}

void command_courses_in_theme(Location_info& Education_center, string theme)
{
    // Tallennetaan kaikki kurssit, jotka kuuluvat käyttäjän hakemaan teema
    vector<string> courses;

    // Läpikäydään kaikki kurssit tietorakenteessa
    for(const pair<const string, vector<Course>>& tmp: Education_center)
    {
        for(const Course& course: tmp.second)
        {
            // Tarkistetaan että duplikaatti kursseja ei tallenneta (tulosteta)
            if(find(courses.begin(), courses.end(), course.name) != courses.end())
            {
                continue;
            }

            // Muuten tallennetaan teemaan kuuluva kurssi
            if(course.theme == theme)
            {
                courses.push_back(course.name);
            }
        }
    }

    // Jos ei löytynyt kurssia, joka kuului teemaan (eli teema ei ole olemassa), tulostetaan tieto käyttäjälle
    if(courses.size() == 0)
    {
        cout << UNKNOWN_THEME << endl;
        return;
    }

    // Muuten lajitellaan kurssit aakkosjärjestykseen -
    sort(courses.begin(), courses.end());

    // - ja tulostetaan kaikki kurssit
    for(const string& course_name: courses)
    {
        cout << course_name << endl;
    }
}

void command_favorite_theme(Location_info& Education_center)
{
    // map-säiliö, johon tallennetaan teema (avain) ja teeman kaikkien kurssien osallistujamäärien summa (arvo)
    map<string, int> themes;

    // Tallennetaan suurin osallistujamäärä vertausta varten
    int most_enrollments = 0;

    // Tallennettaan ensin kaikki teemat map-säiliön avaimeksi ja lisätään avaimeen kurssin osallistujamäärä
    for(const pair<const string, vector<Course>>& tmp: Education_center)
    {
        for(const Course& course: tmp.second)
        {
            themes[course.theme] += course.enrollments;

            // Lisäyksen jälkeen teema voi olla suosituin, tarkistetaan ja mahdollisesti tallenetaan osallistujamäärä
            if(themes[course.theme] > most_enrollments) { most_enrollments = themes[course.theme]; }
        }
    }

    // Jos ei löydy yhtäkään teemaa (eli csv-tiedosto on tyhjö), tulostetaan tieto käyttäjälle
    if(themes.empty())
    {
        cout << NO_ENROLLMENTS << endl;
        return;
    }

    // Muuten tulostetaan kaikkien paikkakuntien kaikki teemat, joiden kurssien osallistujamäärien summa on suurin
    cout << most_enrollments << " enrollments in themes" << endl;

    for(const pair<const string, int>& theme: themes)
    {
        if(theme.second == most_enrollments)
        {
            cout << "--- " << theme.first << endl;
        }
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

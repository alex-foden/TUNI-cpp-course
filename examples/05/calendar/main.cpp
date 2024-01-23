#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;


// Let's give our calendar map a second name to save us from
// having to write so much whenever we want to use the type.
using Calendar = map<string, vector<string>>;


void print_calendar(const Calendar& cal);
void add_event(Calendar& cal, const string& date, const string& event);
void delete_days_events(Calendar& cal, const string& date);
string ask_date();
string ask_event();


int main() {
    // first: date string yyyy-mm-dd, second: vector of the day's events
    Calendar calendar_data = {
        { "2017.12.24",  { "Xmas calendar ends", "Santa is coming!" } },
        { "2017.12.06",  { "Independence day" } },
        { "2018.06.01",  { "Summer begins" } },
    };

    // Simple test user interface
    while ( true ) {
        cout << "(p)rint, (a)dd, (d)elete, (q)uit: ";
        string choice = "";
        getline(cin, choice);

        if ( choice == "p" ) {
            print_calendar(calendar_data);

        } else if ( choice == "a" ) {
            string date = ask_date();
            string event = ask_event();

            add_event(calendar_data, date, event);

        } else if ( choice == "d" ) {
            string date = ask_date();

            delete_days_events(calendar_data, date);

        } else if ( choice == "q" ) {
            cout << "This is the end, my only friend, the end..." << endl;
            break;

        } else {

            cout << "Unknown command!" << endl;
        }

        cout << endl;
    }
}


void print_event_vector(const vector<string>& events) {
    vector<string>::const_iterator iter = events.begin();

    while ( iter != events.end() ) {
        cout << "* " << *iter << endl;

        ++iter;
    }

    // An alternative implementation:
    // for ( const auto& event : events ) {
    //     cout << "* " << event << endl;
    // }
}


void print_calendar(const Calendar& cal) {
    Calendar::const_iterator iter = cal.begin();

    while ( iter != cal.end() ) {
        cout << string(10, '=') << endl
             << iter->first << endl
             << string(10, '=') << endl;

        print_event_vector(iter->second);

        ++iter;
    }

    // Or alternatively:
    // for ( const auto& days_data : cal ) {
    //     cout << string(10, '=') << endl
    //          << days_data.first << endl
    //          << string(10, '=') << endl;
    //
    //     print_event_vector(days_data.second);
    // }
}


// Notice, how Calendar& cal has to be a reference parameter. Why?
void add_event(Calendar& cal, const string& date, const string& event) {
    Calendar::iterator iter = cal.find(date);

    // If the date is not as a key in the map, it means there are
    // no events yet on that date.
    if ( iter == cal.end() ) {
        cal.insert( {date, { event }} );

    // Otherwise we'll just add a new event after the existing ones.
    } else {

        cal.at(date).push_back(event);
    }
}


void delete_days_events(Calendar& cal, const string& date) {
    Calendar::iterator iter = cal.find(date);

    if ( iter == cal.end() ) {
        cout << "There are no events on this date, failed to delete!"
             << endl;

    } else {
        // If we have an iterator pointing to an element of any
        // STL-container, it can be deleted with erase-method.
        // Notice, this deletes all the events on the date.

        cal.erase(iter);
    }
}


string ask_date() {
    // Somewhat simple implementation: there are no error checks
    // for the date the user inputs.  It might be a good idea to
    // use the Date class from project-01 instead of a string.

    cout << "Input date: ";
    string date = "";
    getline(cin, date);

    return date;
}


string ask_event() {
    cout << "Input event: ";
    string event = "";
    getline(cin, event);

    return event;
}

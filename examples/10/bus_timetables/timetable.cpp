// Source code file: timetable.cpp
#include "time.hh"
#include "utilities.hh"
#include <iostream>
#include <vector>
#include <map>

using namespace std;

const int HOW_MANY_TO_PRINT = 3;

using Timetable = map<int, vector<Time>>;

void print_next_departures(const Timetable& timetable,
                           const Time& now,
                           int bus);

int main() {
    Timetable timetable = {
        // first: bus number, second: vector of departure times
        { 1,  {{"06.00"}, {"09.00"}, {"12.00"}, {"21.00"}} },
        { 14, {{"10.26"}, {"16.26"}, {"22.26"}} },
        { 17, {{"11.02"}} },
        { 25, {{"8.41"}, {"20.41"}} },
    };

    // Extremely simple user interface:
    // there is no way to quit the program.
    while ( true ) {
        Time time_now;
        while ( not time_now.read_from_keyboard("What time is it: ") ) {
            cout << "Bad time!" << endl;
        }

        int bus_number = 0;
        while ( not read_int("Input bus number: ", bus_number) ) {
            cout << "Bad number!" << endl;
        }

        print_next_departures(timetable, time_now, bus_number);
    }
}

void print_next_departures(const Timetable& timetable,
                           const Time& now,
                           int bus) {
    Timetable::const_iterator iter = timetable.find(bus);
    if ( iter == timetable.end() ) {
        cout << "Unknown bus " << bus << "!" << endl;
        return;
    } else if ( iter->second.size() == 0 ) {
        cout << "Bus " << bus << " has no departures!" << endl;
        return;
    }

    const vector<Time>& timevec = iter->second;  //***
    vector<Time>::size_type i = 0;
    while ( i < timevec.size() ) {
        if ( now.less_or_equal(timevec.at(i)) ) {
            break;
        }
        ++i;
    }

    cout << "Bus " << bus << " next departures:" << endl;
    int print_count = 0;
    while ( print_count < HOW_MANY_TO_PRINT ) {
        if ( i >= timevec.size() ) {
            i = 0;
        }

        timevec.at(i).print();
        ++print_count;
        ++i;
    }
}

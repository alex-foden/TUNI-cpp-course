// Source code file: time.cpp
#include "time.hh"
#include "utilities.hh"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

Time::Time(const string& time) {
    set_value(time);  //***
}

bool Time::set_value(int hour, int minute) {
    if ( hour < 0 or hour > 23 ) {
        return false;
    } else if ( minute < 0 or minute > 59 ) {
        return false;
    } else {
        hour_ = hour;
        minute_ = minute;
        return true;
    }
}

bool Time::set_value(const string& hhmm) {
    string::size_type dotpos = 0;
    dotpos = hhmm.find('.');
    if ( dotpos == string::npos ) {
        return false;
    }

    int hh = 0;  // Temporary variable for hours.
    int mm = 0;  // Temporary variable for minutes.
    if ( not string_to_int(hhmm.substr(0, dotpos), hh) ) {
        return false;
    }

    if ( not string_to_int(hhmm.substr(dotpos + 1), mm) ) {
        return false;
    }

    return set_value(hh, mm);
}

bool Time::read_from_keyboard(const string& prompt) {
    cout << prompt;
    string line = "";
    getline(cin, line);
    return set_value(line);
}

bool Time::less_or_equal(const Time& time2) const {
    if ( hour_ < time2.hour_ ) {
        return true;
    } else if ( hour_ == time2.hour_ and minute_ <= time2.minute_ ) {
        return true;
    } else {
        return false;
    }
}

void Time::print() const {
    cout << setw(2) << right << setfill('0') << hour_<< "."
         << setw(2) << right << setfill('0') << minute_ << endl;
}

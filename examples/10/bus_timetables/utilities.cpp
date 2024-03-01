// Source code file: utilities.cpp
#include <iostream>
#include <string>

using namespace std;

namespace {  //***
bool is_number_string(const string& str) {
    const string DIGITS = "0123456789";

    // Empty string can not be a number.
    if ( str.length() == 0 ) {
        return false;
    }

    string::size_type i = 0;

    // If the string has more than one character
    // the first of the might be minus i.e.
    // negative number: let's skip it.
    if ( str.length() > 1 and str.at(0) == '-' ) {
        ++i;
    }

    // Then we will just loop through the rest of the
    // characters to make sure they are digits.
    while ( i < str.length() ) {
        char current_character = str.at(i);
        if ( DIGITS.find(current_character) == string::npos ) {
            return false;
        }
        ++i;
    }

    return true;
}
}


bool string_to_int(const string& strval, int& result) {
    if ( not is_number_string(strval) ) {
        return false;
    } else {
        result = stoi(strval);
        return true;
    }
}


bool read_int(const string& prompt, int& result) {
    cout << prompt;

    string numstr = "";
    getline(cin, numstr);

    if ( not string_to_int(numstr, result) ) {
        return false;
    } else {
        return true;
    }
}

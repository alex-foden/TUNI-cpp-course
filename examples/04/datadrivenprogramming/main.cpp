#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum PostalAbbreviation {AL, AK, AZ, AR, CA, CO, ERROR_CODE};
                        // Excluded the rest 44 elements

// Version 1: First idea
PostalAbbreviation name_to_abbreviation1(string const& name) {
    if(name == "Alabama"){
        return AL;
    } else if (name == "Alaska"){
        return AK;
    } else if (name == "Arizona"){
        return AZ;
    } else if (name == "Arkansas"){
        return AR;
    } else if (name == "California"){
        return CA;
    } else if (name == "Colorado"){
        return CO;
    } else {   // Excluded 44 "else if" blocks
        return ERROR_CODE;
    }
}

struct StateInfo {
    string name;
    PostalAbbreviation abbreviation;
};

const vector<StateInfo> STATES = {
    { "Alabamaa", AL },
    { "Alaska", AK },
    { "Arizona", AZ },
    { "Arkansas", AR },
    { "California", CA },
    { "Colorado", CO }  // Excluded 44 lines
};

// Version 2: Better solution
PostalAbbreviation name_to_abbreviation2(string const& name) {
    for(auto s : STATES) {
        if(name == s.name) {
            return s.abbreviation;
        }
    }
    return ERROR_CODE;
}

int main() {
    // Tolerable testing
    if(name_to_abbreviation1("California") == CA) {
        cout << "Correct" << endl;
    } else {
        cout << "Error!" << endl;
    }

    if(name_to_abbreviation2("California") == CA) {
        cout << "Correct" << endl;
    } else {
        cout << "Error!" << endl;
    }

    if(name_to_abbreviation1("Not a State") == ERROR_CODE) {
        cout << "Correct" << endl;
    } else {
        cout << "Error!" << endl;
    }

    if(name_to_abbreviation2("Not a State") == ERROR_CODE) {
        cout << "Correct" << endl;
    } else {
        cout << "Error!" << endl;
    }

    return EXIT_SUCCESS;
}

// Task: How to implement function abbreviation_to_name?
// Hint: If you know how enum is implemented in C++,
// you can do the task very easily.

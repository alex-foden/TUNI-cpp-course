#include "cards.hh"
#include <iostream>
#include <cstdlib>
#include <sstream>

using namespace std;

int main() {
    cout << "constructor" << endl;
    Cards deck;

    int n = 0;
    cout << "Enter amount of test cards: ";
    cin >> n;

    cout << endl << "print (deck is empty)" << endl;
    deck.print(cout);

    cout << endl << "add * n" << endl;
    for(int i = 0; i < n; i++) {
        deck.add(i);
    }

    cout << endl << "print" << endl;
    deck.print(cout);

    cout << endl << "reverse" << endl;
    deck.reverse();

    cout << endl << "print" << endl;
    deck.print(cout);

    cout << endl;
    int value = 0;
    while(deck.remove(value)) {
        cout << "remove " << value << endl;
    }

    cout << endl << "destructor" << endl;
    return EXIT_SUCCESS;
}

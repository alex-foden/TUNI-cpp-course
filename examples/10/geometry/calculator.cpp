// Module: calculator / source file: calculator.cpp
// Contains the main program for geometry calculator.
#include "geometry.hh"
#include <iostream>

using namespace std;

int main() {
    double dimension = 0.0;
    cout << "Input the length of the side of a square: ";
    cin >> dimension;
    cout << "Perimeter: "
         << square_perimeter(dimension) << endl
         << "Area: "
         << square_area(dimension) << endl;
    cout << "Input the radius of a circle: ";
    cin >> dimension;
    cout << "Perimeter: "
         << circle_perimeter(dimension) << endl
         << "Area: "
         << circle_area(dimension) << endl;
}

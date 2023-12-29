/*
#############################################################################
# COMP.CS.110 Programming 2: Structures                                     #
# Example: Number series                                                    #
# File: main.cpp                                                            #
# Description: Prints the elements and the of an arithmetic series.         #
# Notes: * Series start point, length, and difference between elements      #
#          are given in the same line, separated by an empty space.         #
#        * for statement can have several expressions in each of its three  #
#          part, in such case these expression are separated by a comma     #
#          (the parts are separated by a semicolon)                         #
#############################################################################
*/

#include <iostream>

using namespace std;

int main()
{
    int start_point = 0;
    int length = 0;
    int difference = 0;

    cout << "Enter series start point, length, and difference: ";
    cin >> start_point;
    cin >> length;
    cin >> difference;

    int sum = 0;

    cout << "Elements of the series: ";
    for(int index = 0, current = start_point;
        index < length;
        ++index, current += difference)
    {
        cout << current << " ";
        sum += current;
    }
    cout << endl;

    cout << "Sum of the series: " << sum << endl;

    return 0;
}

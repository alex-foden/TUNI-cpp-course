/*
#############################################################################
# COMP.CS.110 Programming 2: Structures                                     #
# Example: Triangle                                                         #
# File: main.cpp                                                            #
# Description: Prints an isosceles triangle of the given height             #
# Notes: e.g. the triangle, the height of which is 3, is printed as:        #
#           *                                                               #
#          ***                                                              #
#         *****                                                             #
#############################################################################
*/

#include <iostream>

using namespace std;


// Characters needed in printing
const char FILL_CHARACTER = '*';
const char EMPTY = ' ';

// Prints the given prompt text and reads user input, repeats these actions
// until the user gives an acceptable (positive) value.
int read_input(const string& prompt)
{
    int input = 0;
    while(input <= 0)
    {
        cout << prompt;
        cin >> input;
    }
    return input;
}

// Prints the given amount of the given characters (without a line feed).
void print_chars(unsigned int amount, char print_char)
{
    for(unsigned int i = 0; i < amount; ++i)
    {
        cout << print_char;
    }
}

// Prints an isosceles triangle with the given height.
void print_triangle(unsigned int height)
{
    for(unsigned int i = 0; i < height; ++i)
    {
        print_chars(height - i - 1, EMPTY);
        print_chars(i * 2 + 1, FILL_CHARACTER);
        cout << endl;
    }
}

// Main function.
int main()
{
    int triangle_height = read_input("Enter the height of a triangle: ");
    print_triangle(triangle_height);
    return 0;
}

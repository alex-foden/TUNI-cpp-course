/*
#############################################################################
# COMP.CS.110 Programming 2: Structures                                     #
# Example: Rock paper scissors (kivi, paperi ja sakset)                     #
# File: main.cpp                                                            #
# Description: Enables two players to play the game 'rock paper scissors'   #
#              (RPS) until either player wants to quit.                     #
# Notes: * To avoid large amount of nearly identical if-statements, the     #
#          solution is based on the circular superiority of the picks.      #
#        * We construct a string consisting of two characters, the first    #
#          of which is the pick of player 1 and the second one is that of   #
#          player 2.                                                        #
#        * Player 1 wins if the string is either "SP", "PR", or "RS", and   #
#          thus, we can just check if the string is a substring of "SPRS"   #
#          (or "PRSP", or "RSPR", as well).                                 #
#############################################################################
*/
#include <iostream>

using namespace std;

int main()
{
    // Mutual relations (circular superiority): S > P > R > S,
    // where '>' means 'better than'
    string winning_series = "SPRS"; // could be "PRSP" or "RSPR" as well

    char answer1 = ' ';
    char answer2 = ' ';
    while(answer1 != 'Q' and answer2 != 'Q')
    {
        cout << "Player 1, enter your choice (R/P/S), or Q to quit: ";
        cin >> answer1;
        answer1 = toupper(answer1); // converting the letter to uppercase
                                    // (to make comparison simpler)

        // Player 1 wants to quit
        if(answer1 == 'Q')
        {
            break; // exiting from the while loop
                   // (continue statement would work here as well,
                   // since the while condition would be false)
        }

        cout << "Player 2, enter your choice (R/P/S), or Q to quit: ";
        cin >> answer2;
        answer2 = toupper(answer2); // converting the letter to uppercase
                                    // (to make comparison simpler)

        // If player 2 wants to quit, or if an invalid letter was given
        if(answer2 == 'Q' or
          (answer1 != 'R' and answer1 != 'P' and answer1 != 'S') or
          (answer2 != 'R' and answer2 != 'P' and answer2 != 'S'))
        {
            continue; // skipping the rest of the while loop and
                      // evaluating the while condition again
        }

        if(answer1 == answer2)
        {
            cout << "It's a tie!" << endl;
        }
        else
        {
            // Collecting the answers together and checking if it can be found
            // from the winning series
            string answers_combined = "";
            answers_combined += answer1; // appending a char to a string
            answers_combined += answer2; // appending a char to a string

            // If the answer of player 1 is 'better than' that of player 2,
            // i.e. if the answers of player 1 and player 2 (in this order)
            // can be found in winning_series
            if(winning_series.find(answers_combined) != string::npos)
            {
                cout << "Player 1 won!" << endl;
            }
            else
            {
                cout << "Player 2 won!" << endl;
            }
        }
    }
    return 0;
}

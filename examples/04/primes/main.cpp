/*
#############################################################################
# COMP.CS.110 Programming 2: Structures                                     #
# Example: Number series                                                    #
# File: main.cpp                                                            #
# Description: Lists prime numbers up to SIZE.                              #
# Notes: * The algorithm applies the Sieve of Eratosthenes (Eratostheneen   #
#          seula)                                                           #
#        * Uses a vector of truth values: if the value in index x is true,  #
#          it means that x is a prime.                                      #
#############################################################################
*/

#include <iostream>
#include <vector>

using namespace std;

// The constant up to which primes are listed
// You can try to change the value of SIZE
const unsigned int SIZE = 100;

// The function uses the Sieve of Eratosthenes for counting and printing
// prime numbers up to SIZE.
void eratosthenes_sieve(vector<bool>& numbers)
{
    cout << "Prime numbers less than " << SIZE << ":" << endl;

    // Going through the whole vector
    for(unsigned int i = 0; i < SIZE; ++i)
    {
        // If a prime number was found from the vector
        if(numbers.at(i))
        {
            cout << i << " ";

            // Multiples of a (prime) number cannot be prime
            // (Alku)luvun monikerta ei voi olla alkuluku
            for(unsigned int j = 2 * i; j < SIZE; j += i)
            {
                numbers.at(j) = false;
            }
        }
    }
    cout << endl;
}

int main()
{
    // The vector is first filled with trues
    vector<bool> primes(SIZE, true);

    // Zero and one are not primes
    primes.at(0) = primes.at(1) = false;

    eratosthenes_sieve(primes);
    return 0;
}

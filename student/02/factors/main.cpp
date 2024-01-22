#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a positive number: ";
    int number = 0;
    cin >> number;
    int tekija1 = 0;
    int tekija2 = 0;

    if (number <= 0)
    {
        cout << "Only positive numbers accepted." << endl;
        return EXIT_FAILURE;
    }

    for (int factor1 = 1; factor1 * factor1 <= number; factor1++)
    {
        for (int factor2 = 1; factor1 * factor2 <= number; factor2++)
        {
            if (factor1 * factor2 == number)
            {
                tekija1 = factor1;
                tekija2 = factor2;
            }

        }
    }

    cout << number << " = " << tekija1 << " * " << tekija2 << endl;

    return EXIT_SUCCESS;
}

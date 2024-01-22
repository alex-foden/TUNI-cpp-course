#include <iostream>
#include <cmath>
using namespace std;

unsigned long int calculate_chances(int lottery_balls, int drawn_balls)
{
    unsigned long int n_factorial = 1;
    unsigned long int p_factorial = 1;
    unsigned long int n_min_p_factorial = 1;

    for (int i = 1; i <= lottery_balls; i++)
    {
        n_factorial *= i;
    }

    for (int i = 1; i <= drawn_balls; i++)
    {
        p_factorial *= i;
    }

    for (int i = 1; i <= lottery_balls - drawn_balls; i++)
    {
        n_min_p_factorial *= i;
    }

    unsigned long int chances = n_factorial / (n_min_p_factorial * p_factorial);

    return chances;
}
int main()
{
    cout << "Enter the total number of lottery balls: ";
    int lottery_balls = 0;
    cin >> lottery_balls;

    cout << "Enter the number of drawn balls: ";
    int drawn_balls = 0;
    cin >> drawn_balls;

    if (lottery_balls <= 0 or drawn_balls <= 0)
    {
        cout << "The number of balls must be a positive number." << endl;
        return EXIT_SUCCESS;
    }

    if (drawn_balls > lottery_balls)
    {
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
        return EXIT_SUCCESS;
    }

    unsigned long int chances = calculate_chances(lottery_balls, drawn_balls);

    cout << "The probability of guessing all " << drawn_balls << " balls correctly is 1/" << chances << endl;

    return EXIT_SUCCESS;
}

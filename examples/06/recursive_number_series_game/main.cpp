#include <iostream>

using namespace std;

// Counts the amount of numbers divisible by 3 or 7 or both
unsigned int divisible_by_3_or_7(unsigned int nb)
{
    if(nb == 0)
    {
        return 0;
    }
    else if(nb % 3 == 0 or nb % 7 == 0)
    {
        return nb + divisible_by_3_or_7(nb - 1);
    }
    else
    {
        return divisible_by_3_or_7(nb - 1);
    }
}

// Prints the numbers from lower to upper such that numbers divisible by 3
// are replaced with "zip", numbers divisible by 7 are replaced with "boing",
// and numbers divisible with both 3 and 7 are replaced with "zip boing"
void print_zip_boing(unsigned int lower, unsigned int upper)
{
    if(lower <= upper)
    {
        if(lower % 3 == 0 and lower % 7 == 0)
        {
            cout << "zip boing" << endl;
        }
        else if(lower % 3 == 0)
        {
            cout << "zip" << endl;
        }
        else if(lower % 7 == 0)
        {
            cout << "boing" << endl;
        }
        else
        {
            cout << lower << endl;
        }
        print_zip_boing(lower + 1, upper);
        // What happens if you replace the above call with one
        // of the following:
        // print_zip_boing(lower++, upper);
        // print_zip_boing(++lower, upper);
        // Why?
    }
}

int main()
{
    cout << "How many numbers would you like to have? ";
    unsigned int upper_bound = 0;
    cin >> upper_bound;
    print_zip_boing(1, upper_bound);
    cout << "Sum of non-negative integers between 1 and "
         << upper_bound
         << " and divisible by 3 or 7 is "
         << divisible_by_3_or_7(upper_bound)
         << endl;
    return EXIT_SUCCESS;
}

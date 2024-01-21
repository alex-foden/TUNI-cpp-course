#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    cout << "Enter a number: ";
    int number = 0;
    cin >> number;
    int cube = pow(number, 3);
    int root = cbrt(cube);

    if (root == number)
    {
        cout << "The cube of " << number << " is " << cube << "." << endl;
    }

    else
    {
        cout << "The cube of " << number << " is not " << cube << "." << endl;
    }

    return 0;
}

#include <iostream>

using namespace std;

float fahrenheiter(const int celsius)
{
    float fahrenheit = celsius * 1.8 + 32;
    return fahrenheit;
}

float celsiuser(const int fahrenheit)
{
    float celsius = (fahrenheit - 32) / 1.8;
    return celsius;
}

int main()
{
    cout << "Enter a temperature: ";
    int temperature = 0;
    cin >> temperature;

    cout << temperature << " degress Celsius is "
         << fahrenheiter(temperature) << " degrees Fahrenheit" << endl;

    cout << temperature << " degress Fahrenheit is "
         << celsiuser(temperature) << " degrees Celsius" << endl;



    return EXIT_SUCCESS;
}

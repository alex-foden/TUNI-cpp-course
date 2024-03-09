#include <iostream>
#include <cmath>

using namespace std;

double polynomial(double x);

// Command decltype gives the type of any expression
// (e.g. variable or function).
using Func = decltype(&polynomial);

// Func type above could have been defined without decltype command,
// using type definition syntax of C++ (which in case is a pointer
// to a function that returns a double and receives a double as a parameter):
//
//    using Func = double(*)(double);
//
// decltype is easier to understand, if there is a function that can be used
// a "parameter" to decltype.
// decltype is not a function but a direct command to the compiler, which
// will be solved already in compile-time.


// integrate:
// Calculates an approximate value for the integral of function «f» between
// «left» and «right» by using so called rectangular integration
// (or Midpoint Rule).
// Parameter «number_of_partitions» tells into how many equal-width parts the
// interval to be integrated will be partitioned, i.e. how many rectangles
// constitute the total integral (when calculated as the sum of rectangles).
double integrate(Func f,
                 double left,
                 double right,
                 int number_of_partitions = 500) {
    double length_of_partition = (right - left) / number_of_partitions;
    double sum = 0.0;

    double middle_point = left + length_of_partition / 2;
    while ( middle_point < right ) {
        sum += f(middle_point);  // Same as: sum = sum + f(middle_point);
        middle_point += length_of_partition;
    }

    return sum * length_of_partition;
}


int main() {
    // Note that the first parameters in the calls below are not the return
    // values of sin, cos, sqrt, and polynomial, but these functions
    // themselves.
    // Because of that the function names do not follow "()", which in C++ is
    // an operator that causes function call.
    cout << integrate(sin,        0,  2) << endl;
    cout << integrate(cos,        0,  2) << endl;
    cout << integrate(sqrt,       0,  2) << endl;
    cout << integrate(polynomial, 0,  2) << endl;

    return EXIT_SUCCESS;
}


double polynomial(double x) {
    return 2 * x * x - 3 * x + 1;
}

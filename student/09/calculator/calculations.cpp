// Note that there is no need for "using namespace std",
// since no C++ standard libraries are used.

double addition(double left, double right) {
    return left + right;
}


double subtraction(double left, double right) {
    return left - right;
}


double multiplication(double left, double right) {
    return left * right;
}


double division(double left, double right) {
    return left / right;
}

double exponentiation(double left, double right)
{
    if(right == 0.0)
    {
        return 1.0;
    }

    double result = left;

    for(int times = 1; times < right; times++)
    {
        result *= left;
    }

    return result;
}

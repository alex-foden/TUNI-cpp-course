#ifndef FRACTION_HH
#define FRACTION_HH

#include <iostream>

// Class for describing fractions, i.e. numbers of the form a/b,
// where a and b are integers such that a is a numerator and b is a denominator
class Fraction
{
public:
    // Constructor, creates the fraction, the value of which is zero
    Fraction();

    // Constructor, creates the fraction num/den
    Fraction(int num, int den);

    // Destructor
    ~Fraction();

    // Getter function returning the numerator (needed only in operator<<)
    int getNumerator() const;

    // Getter function returning the denominator (needed only in operator<<)
    int getDenominator() const;

    // Overloaded equality operator
    bool operator==(const Fraction& other) const;

    // Overloaded addition operator
    Fraction operator+(const Fraction& other) const;

    // Overloaded multiplication operator
    Fraction operator*(const Fraction& other) const;

private:
    int numerator_ = 0;
    int denominator_ = 1;

    // Calculates the greatest common divisor between a and b
    int gcd(int a, int b);

    // Transforms the fraction into as reduced shape as possible
    void reduce();
};

// Overloaded output operator (not a member function of Fraction)
// Enables fractions in chained output
std::ostream& operator<<(std::ostream& os, const Fraction& frac);

#endif // FRACTION_HH

#include "fraction.hh"
#include <iostream>

Fraction::Fraction()
{
}

Fraction::Fraction(int num, int den) :
numerator_(num), denominator_(den)
{
    //reduce();
}

Fraction::~Fraction()
{
}

int Fraction::getNumerator() const
{
    return numerator_;
}

int Fraction::getDenominator() const
{
    return denominator_;
}

bool Fraction::operator==(const Fraction& other) const
{
    // Comparison must be done between reduced forms,
    // but the fraction is not wanted to be left in the reduced form
    Fraction reduced_this(numerator_, denominator_);
    reduced_this.reduce();
    Fraction reduced_other(other.numerator_, other.denominator_);
    reduced_other.reduce();
    return reduced_other.numerator_ == reduced_this.numerator_ and
           reduced_other.denominator_ == reduced_this.denominator_;
}

Fraction Fraction::operator+(const Fraction& other) const
{
    Fraction result;
    result.numerator_ = numerator_ * other.denominator_ +
                        denominator_ * other.numerator_;
    result.denominator_ = denominator_ * other.denominator_;
    result.reduce();
    return result;
}

Fraction Fraction::operator*(const Fraction& other) const
{
    Fraction result;
    result.numerator_ = numerator_ * other.numerator_;
    result.denominator_ = denominator_ * other.denominator_;
    result.reduce();
    return result;
}

int Fraction::gcd(int a, int b)
{
    // gcd is counted from absolute values
    if(a < 0) {
        a *= -1;
    }
    if(b < 0) {
        b *= -1;
    }

    // Trivial cases
    if(a == 0) {
        return b;
    }
    if(b == 0) {
        return a;
    }

    if(a == b) {
        return a;
    } else if(a > b) {
        return gcd(a - b, b); // recursive call
    } else {
        return gcd(a, b - a); // recursive call
    }
}

void Fraction::reduce()
{
    int reducing_factor = gcd(numerator_, denominator_);
    if(reducing_factor == 0) {
        std::cout << "0/0 should never be possible" << std::endl;
    } else {
        // Note that both numerator_ and denominator_ are divisible by
        // reducing_factor
        numerator_ /= reducing_factor;
        denominator_ /= reducing_factor;
    }

    // Possible sign is attached to the numerator
    if(denominator_ < 0) {
        denominator_ *= -1;
        numerator_ *= -1;
    }
}

// A non-member function
std::ostream& operator<<(std::ostream& os, const Fraction& frac)
{
    os << frac.getNumerator() << "/" << frac.getDenominator();
    return os;
}

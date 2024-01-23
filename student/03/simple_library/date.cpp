#include "date.hh"
#include <iostream>

// Number of days in months (collected in an array).
// Arrays will be introduced later, but typically their use is not recommended.
// BE ALWAYS CAREFUL IN USING ARRAYS!
unsigned int const MONTH_SIZES[] = { 31, 28, 31, 30, 31, 30,
                                     31, 31, 30, 31, 30, 31 };

Date::Date():
    day_(DEFAULT_VALUE), month_(DEFAULT_VALUE), year_(DEFAULT_VALUE)
{
}

Date::Date(unsigned int day, unsigned int month, unsigned int year):
    day_(day), month_(month), year_(year)
{
    if( month_ > 12 or month_ < 1 )
    {
        month_ = 1;
    }
    if ( day_ > MONTH_SIZES[month_ - 1]
         or ( month_ == 2 and is_leap_year()
             and day > MONTH_SIZES[month - 1] + 1 ) )
    {
        day_ = 1;
    }
}

Date::~Date()
{
}

void Date::advance(unsigned int days)
{
    day_ += days;
    while ( day_ > MONTH_SIZES[month_ - 1] )
    {
        if ( month_ == 2 and day_ == 29 )
        {
            return;
        }
        day_ -= MONTH_SIZES[month_ - 1];
        if ( month_ == 2 and is_leap_year() )
        {
            --day_;
        }
        ++month_;

        if ( month_ > 12 )
        {
            month_ -= 12;
            ++year_;
        }
    }
}

void Date::print() const
{
    if ( day_ < 10 )
    {
        std::cout << "0";
    }
    std::cout << day_ << ".";
    if ( month_ < 10 )
    {
        std::cout << "0";
    }
    std::cout << month_ << ".";
    if ( year_ < 10 )
    {
        std::cout << "0";
    }
    std::cout << year_ << std::endl;
}

bool Date::is_leap_year() const
{
    // A year is a leap year, if it is divisible by 4,
    // but not divisible by 100, unless it is divisible by 400
    return (year_ % 4 == 0) and ((year_ % 100 != 0) or (year_ % 400 == 0));
}

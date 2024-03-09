/* Class Date
 * ----------
 * COMP.CS.110 SPRING 2024
 * ----------
 * Class for describing a date.
 *
 * Note: Students need not change this class, but they can if necessary.
 * */
#ifndef DATE_HH
#define DATE_HH

#include <string>

class Date
{
public:
    /**
      * @brief Date
      * Uses the default value 1 for day, month, and year
      */
    Date();

    /**
      * @brief Date
      * @param day
      * @param month
      * @param year
      * If any of the given parameter is out of sensible limits,
      * default value 1 used instead
      */
    Date(unsigned int day, unsigned int month, unsigned int year);

    /**
      * @brief Date
      * @param string following the format ddmmyyyy
      */
    Date(const std::string& date_as_str);

    /**
      * @brief destructor
      */
    ~Date();

    /**
      * @brief set new values
      * @param day
      * @param month
      * @param year
      */
    void set(unsigned int day, unsigned int month, unsigned int year);

    /**
      * @brief is_default
      * @return true if the date is the default one, otherwise false
      */
    bool is_default() const;

    /**
      * @brief advance
      * @param amount of days
      */
    void advance(unsigned int days);

    /**
      * @brief print the date in the format dd.mm.yyyy
      */
    void print() const;

    /**
      * @brief comparison operators
      */
    bool operator==(const Date& rhs) const;
    bool operator<(const Date& rhs) const;

private:
    unsigned int day_;
    unsigned int month_;
    unsigned int year_;

    /**
      * @brief is_leap_year
      * @return true if the year of the date is a leap year, otherwise false
      */
    bool is_leap_year() const;

    /**
      * @brief str_to_date_int
      * @param date part (day, month, or year)
      * Converts the part from a string to an integer,
      * if the part begins with zero, drops it away
      */
    unsigned int str_to_date_int(const std::string& date_part) const;
};

#endif // DATE_HH

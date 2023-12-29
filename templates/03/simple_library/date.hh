#ifndef DATE_HH
#define DATE_HH

// Default value for day, month, and year
// (0 wouldn't be sensible, since e.g. a day can't be 0).
const unsigned int DEFAULT_VALUE = 1;

class Date
{
public:
    // Default constructor.
    // Uses DEFAULT_VALUE for day, month, and year.
    Date();

    // Constructor.
    // If any of the given parameter is out of sensible limits,
    // uses DEFAULT_VALUE instead.
    Date(unsigned int day, unsigned int month, unsigned int year);

    // Destructor
    ~Date();

    // Advances the date with given amount of days.
    // Can't be anvanced by negative amounts.
    void advance(unsigned int days);

    // Prints the date in the format: dd.mm.yyyy.
    void print() const;

private:
    // Obvious attributes.
    unsigned int day_;
    unsigned int month_;
    unsigned int year_;

    // Returns true if the year of the date is a leap year,
    // otherwise returns false.
    bool is_leap_year() const;
};

#endif // DATE_HH

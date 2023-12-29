#ifndef STUDENT_HH
#define STUDENT_HH

#include "date.hh"
#include <string>


class Student
{
public:
    // Constructor.
    Student(std::string const& name, const Date& birth_day);

    // Destructor.
    ~Student();

    // Sets the given date value for the attribute studies_started_.
    void start_studies(const Date& today);

    // Completes a course with the given credit points, i.e. increases
    // the value of the attribute collected_credits.
    void complete_course(unsigned int credits);

    // Returns true, if the student is older than the other one
    // given as a parameter, otherwise returns false.
    bool older_than(const Student& other_stud) const;

    // Returns true, if the student has studied longer than the other one
    // given as a parameter, otherwise returns false.
    // Compares the whole dates, but perhaps it would be enough to compare
    // years only?
    bool studied_longer_than(const Student& other_stud) const;

    // Prints the values of all attributes.
    void print() const;

private:
    // Obvious attributes
    std::string name_;
    unsigned int collected_credits_;
    Date birth_day_;
    Date studies_started_;
};

#endif // STUDENT_HH

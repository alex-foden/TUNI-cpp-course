#include "student.hh"
#include <iostream>

Student::Student(std::string const& name, const Date& birth_day):
    name_(name), collected_credits_(0), birth_day_(birth_day)
{
}

Student::~Student()
{
}

void Student::start_studies(const Date &today)
{
    studies_started_ = today;
}

void Student::complete_course(unsigned int credits)
{
    collected_credits_ += credits;
}

bool Student::older_than(const Student &other_stud) const
{
    return birth_day_ < other_stud.birth_day_;
}

bool Student::studied_longer_than(const Student &other_stud) const
{
    return studies_started_ < other_stud.studies_started_;
}

void Student::print() const
{
    std::cout << "* Name: " << name_ << std::endl;
    std::cout << "* Birth day: ";
    birth_day_.print();
    std::cout << "* Credits: " << collected_credits_ << std::endl;
    std::cout << "* Studies started: ";
    studies_started_.print();
    std::cout << std::endl;
}

#include "person.hh"
#include <iostream>
#include <map>

Person::Person()
{
}

Person::Person(const std::string &id):
    id_(id)
{
    date_of_birth_ = Date();
}

Person::Person(const std::string& id, const std::string& date_of_birth):
    id_(id), date_of_birth_(date_of_birth)
{
}

Person::~Person()
{
    // Remove the print below before submitting the program in Plussa
    std::cout << "Person " << id_ << " destructed." << std::endl;
}

std::string Person::get_id() const
{
    return id_;
}

std::vector<std::string> Person::get_medicines() const
{
    std::vector<std::string> result;
    for( std::map<std::string, Prescription>::const_iterator
         iter = medicines_.begin();
         iter != medicines_.end();
         ++iter )
    {
        result.push_back(iter->first);
    }
    return result;
}

void Person::add_medicine(const std::string& name,
                          unsigned int strength,
                          unsigned int dosage)
{
    Prescription pre;
    pre.strength_ = strength;
    pre.dosage_ = dosage;
    if( medicines_.find(name) != medicines_.end() )
    {
        medicines_.at(name) = pre;
    }
    else
    {
        medicines_.insert({name, pre});
    }
}

void Person::remove_medicine(const std::string& name)
{
    medicines_.erase(name);
}

void Person::print_id() const
{
    std::cout << id_;
    //date_of_birth_.print();
    //std::cout << std::endl;
}

void Person::print_medicines(const std::string& pre_text) const
{
    if( medicines_.empty() )
    {
        std::cout << " None" << std::endl;
        return;
    }
    std::cout << std::endl;
    for( std::map<std::string, Prescription>::const_iterator
         iter = medicines_.begin();
         iter != medicines_.end();
         ++iter )
    {
        std::cout << pre_text
                  << iter->first << " "
                  << iter->second.strength_ << " mg x "
                  << iter->second.dosage_ << std::endl;
    }
}

bool Person::operator<(const Person &rhs) const
{
    return id_ < rhs.id_;
}


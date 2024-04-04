/*
 * Author:
 * Name: Alex Foden
 * Student number: 152492647
 * Username: cxm844
 * E-Mail: alex.foden@tuni.fi
 * */

#include "careperiod.hh"
#include <iostream>

CarePeriod::CarePeriod(const std::string& start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::CarePeriod(const Date &start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::~CarePeriod()
{
}

void CarePeriod::End_CarePeriod(const Date& today)
{
    end_ = today;
}

Person* CarePeriod::Get_Patient()
{
    return patient_;
}

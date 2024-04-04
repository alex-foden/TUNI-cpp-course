/* Class CarePeriod
 * ----------
 * COMP.CS.110 SPRING 2024
 * ----------
 * Author:
 * Name: Alex Foden
 * Student number: 152492647
 * Username: cxm844
 * E-Mail: alex.foden@tuni.fi
 * Class for describing a patient's care period in hospital.
 *
 * Note: Students need to implement almost all of this class by themselves.
 * */
#ifndef CAREPERIOD_HH
#define CAREPERIOD_HH

#include "person.hh"
#include "date.hh"
#include <string>

class CarePeriod
{
public:
    /**
      * @brief CarePeriod
      * @param start date given as a string (ddmmyyyy)
      * @param patient whose care period will be created
      */
    CarePeriod(const std::string& start, Person* patient);

    /**
      * @brief CarePeriod
      * @param start date given as a Date object
      * @param patient whose care period will be created
      */
    CarePeriod(const Date& start, Person* patient);

    /**
      * @brief destructor
      */
    ~CarePeriod();

    /**
      * @brief End_CarePeriod
      * @param patient whose care period will be created
      * Sets end date for care period
      */
    void End_CarePeriod(const Date& today);

    /**
      * @brief Get_Patient
      * @return patient_
      * Returns pointer to the patient the care period is assigned to
      */
    Person* Get_Patient();

    // add_staff(Person* staff)

    // is_staff(Person* staff)

    // More public methods

private:
    Person* patient_;
    Date start_;
    Date end_;

    std::map<std::string, Person*> staff_;
    // More attributes and methods
};

#endif // CAREPERIOD_HH

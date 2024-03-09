/* Class Hospital
 * ----------
 * COMP.CS.110 SPRING 2024
 * ----------
 * Class for describing a hospital. Only a single object created from this
 * class. Implements all commands in hospital program.
 *
 * Note: Students need change this class to implement commands missing
 * in the template code.
 * */
#ifndef HOSPITAL_HH
#define HOSPITAL_HH

#include "person.hh"
#include "careperiod.hh"
#include "date.hh"
#include <map>

// Error and information outputs
const std::string ALREADY_EXISTS = "Error: Already exists: ";
const std::string NOT_NUMERIC = "Error: Wrong type of parameters.";
const std::string CANT_FIND = "Error: Can't find anything matching: ";
const std::string STAFF_RECRUITED = "A new staff member has been recruited.";
const std::string PATIENT_ENTERED = "A new patient has entered.";
const std::string PATIENT_LEFT = "Patient left hospital, care period closed.";
const std::string MEDICINE_ADDED= "Medicine added for: ";
const std::string MEDICINE_REMOVED= "Medicine removed from: ";
const std::string STAFF_ASSIGNED= "Staff assigned for: ";

using Params = const std::vector<std::string>&;

class Hospital
{
public:
    /**
     * @brief Hospital
     */
    Hospital();

    /**
      * @brief destructor
      */
    ~Hospital();

    //
    // Commands already implemented by course staff
    //

    /**
     * @brief set_date
     * @param params vector containing parameters of the corresponding command
     */
    void set_date(Params params);

    /**
     * @brief advance_date
     * @param params vector containing parameters of the corresponding command
     * Advances the current date with the given number of days.
     */
    void advance_date(Params params);

    /**
     * @brief recruit
     * @param params vector containing parameters of the corresponding command
     * Recruits a new staff member (creates a new Person object)
     */
    void recruit(Params params);

    /**
     * @brief print_all_staff
     */
    void print_all_staff(Params);

    /**
     * @brief add_medicine
     * @param params vector containing parameters of the corresponding command
     * Adds the given medicine (name, strength, dosage) for the given patient.
     * If the given patient already has the medicine,
     * the prescription (strength, dosage) possibly changes.
     * If the given patien already has the medicine with same prescription,
     * nothing happens.
     */
    void add_medicine(Params params);

    /**
     * @brief remove_medicine
     * @param params vector containing parameters of the corresponding command
     * Removes the given medicine from the patient.
     * If the patient does not have the medicine, nothing happens.
     */
    void remove_medicine(Params params);

    //
    // Commands to be implemented by students
    //

    /**
     * @brief enter
     * @param params vector containing parameters of the corresponding command
     * Adds a patient in the hospital and creates a new care period.
     * If the person given as a parameter has never visited hospital earlier,
     * creates a new person object, otherwise just adds an existing person
     * in the newly created care period.
     */
    void enter(Params params);

    /**
     * @brief leave
     * @param params vector containing parameters of the corresponding command
     * Removes the person given as a parameter from the hospital, and closes
     * person's care period. However, the care period still exists.
     */
    void leave(Params params);

    /**
     * @brief assign_staff
     * @param params vector containing parameters of the corresponding command
     * Assigns the given staff member for the given patient.
     * If the patient already has the staff member assigned
     * (in the current care period), nothing happens.
     */
    void assign_staff(Params params);

    /**
     * @brief print_patient_info
     * @param params vector containing parameters of the corresponding command
     * Prints the given patient's all care periods and their current medicines,
     * i.e. those that have been added but not removed.
     */
    void print_patient_info(Params params);

    /**
     * @brief print_care_periods
     * @param params vector containing parameters of the corresponding command
     * Prints the care periods of the given staff member, i.e. those
     * care periods the given staff member has worked in.
     */
    void print_care_periods(Params params);

    /**
     * @brief print_all_medicines
     * Prints all medicines that are used by some patient visited the hospital
     * at some time, i.e. all medicines of current and earlier patients.
     */
    void print_all_medicines(Params);

    /**
     * @brief print_all_patients
     * Prints all patients visited the hospital at some time, i.e. all
     * current and earlier patients.
     * More precisely, prints each patient's id and patient info
     * (in the same format as the method print_patient_info).
     */
    void print_all_patients(Params);

    /**
     * @brief print_current_patients
     * Prints all patients currently in hospital at some time.
     * More precisely, prints each patient's id and patient info
     * (in the same format as the method print_patient_info).
     */
    void print_current_patients(Params);

private:
    std::map<std::string, Person*> current_patients_;
    std::map<std::string, Person*> staff_;

    // More attributes and methods
};

#endif // HOSPITAL_HH

/* Class Person
 * ----------
 * COMP.CS.110 SPRING 2024
 * ----------
 * Class for describing a person that can be a patient or a staff member
 * in hospital.
 *
 * Note: Students can change this class, but most probably they need not.
 * */
#ifndef PERSON_HH
#define PERSON_HH

#include "date.hh"
#include <string>
#include <map>
#include <vector>

class Person
{
public:
    /**
     * @brief Person
     * Gives no values for the attributes
     */
    Person();

    /**
     * @brief Person
     * @param id
     * Initializes the attribute id_
     */
    Person(const std::string& id);

    /**
     * @brief Person
     * @param id
     * @param date_of_birth
     * Initializes the attributes id_ and date_of_birth_ (not in use)
     */
    Person(const std::string& id, const std::string& date_of_birth);

    /**
      * @brief destructor
      */
    ~Person();

    /**
     * @brief get_id
     * @return the value of id_
     */
    std::string get_id() const;

    /**
     * @brief get_medicines
     * @return medicines
     */
    std::vector<std::string> get_medicines() const;

    /**
     * @brief add_medicine
     * @param name
     * @param strength
     * @param dosage
     */
    void add_medicine(const std::string& name,
                      unsigned int strength,
                      unsigned int dosage);

    /**
     * @brief remove_medicine
     * @param name
     * Removes the given medicine from the person.
     */
    void remove_medicine(const std::string& name);

    /**
     * @brief print_id
     */
    void print_id() const;

    /**
     * @brief print_medicines
     * @param pre_text is printed before the medicines
     */
    void print_medicines(const std::string& pre_text) const;

    /**
     * @brief operator <
     * @param rhs
     * @return
     * Comparison operator, enables forming a set of Person objects.
     */
    bool operator<(const Person& rhs) const;

private:
    std::string id_;     // Can be a name or any other identifier
    Date date_of_birth_; // Not actually needed

    struct Prescription
    {
        unsigned int strength_;
        unsigned int dosage_;
    };
    // Medicine names and their prescriptions
    std::map<std::string, Prescription> medicines_;
};

#endif // PERSON_HH

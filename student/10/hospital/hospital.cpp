/*
 * Edited by:
 * Name: Alex Foden
 * Student number: 152492647
 * Username: cxm844
 * E-Mail: alex.foden@tuni.fi
 * */

#include "hospital.hh"
#include "utils.hh"
#include <iostream>
#include <set>
#include <algorithm>

Hospital::Hospital()
{
}

Hospital::~Hospital()
{
    // Deallocating staff
    for( std::map<std::string, Person*>::iterator
         iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        delete iter->second;
        iter->second = nullptr;
    }

    // Deallocating patients
    for( std::map<std::string, Person*>::iterator
         iter = all_patients_.begin();
         iter != all_patients_.end();
         ++iter )
    {
        delete iter->second;
        iter->second = nullptr;
    }

    // Deallocating care periods
    for( std::vector<CarePeriod*>::iterator
         iter = all_care_periods_.begin();
         iter != all_care_periods_.end();
         ++iter)
    {
        delete *iter;
        *iter = nullptr;
    }
}

void Hospital::set_date(Params params)
{
    std::string day = params.at(0);
    std::string month = params.at(1);
    std::string year = params.at(2);
    if( not utils::is_numeric(day, false) or
        not utils::is_numeric(month, false) or
        not utils::is_numeric(year, false) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.set(stoi(day), stoi(month), stoi(year));
    std::cout << "Date has been set to ";
    utils::today.print();
    std::cout << std::endl;
}

void Hospital::advance_date(Params params)
{
    std::string amount = params.at(0);
    if( not utils::is_numeric(amount, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.advance(stoi(amount));
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}

void Hospital::recruit(Params params)
{
    std::string specialist_id = params.at(0);
    if( staff_.find(specialist_id) != staff_.end() )
    {
        std::cout << ALREADY_EXISTS << specialist_id << std::endl;
        return;
    }
    Person* new_specialist = new Person(specialist_id);
    staff_.insert({specialist_id, new_specialist});
    std::cout << STAFF_RECRUITED << std::endl;
}

void Hospital::print_all_staff(Params)
{
    if( staff_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }
    for( std::map<std::string, Person*>::const_iterator iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        std::cout << iter->first << std::endl;
    }
}

void Hospital::add_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string strength = params.at(1);
    std::string dosage = params.at(2);
    std::string patient = params.at(3);
    if( not utils::is_numeric(strength, true) or
        not utils::is_numeric(dosage, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    std::map<std::string, Person*>::const_iterator
            patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->add_medicine(medicine, stoi(strength), stoi(dosage));
    std::cout << MEDICINE_ADDED << patient << std::endl;
}

void Hospital::remove_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string patient = params.at(1);
    std::map<std::string, Person*>::const_iterator
            patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->remove_medicine(medicine);
    std::cout << MEDICINE_REMOVED << patient << std::endl;
}

void Hospital::enter(Params params)
{
    std::string patient_id = params.at(0);

    Person* new_patient;

    // Check if patient is already in a care period
    if(current_patients_.find(patient_id) != current_patients_.end())
    {
        std::cout << ALREADY_EXISTS << patient_id << std::endl;
        return;
    }

    // Check if patient was previously in the hospital. If so, do not create a new patient
    if(all_patients_.find(patient_id) != all_patients_.end())
    {
        new_patient = all_patients_.at(patient_id);
        current_patients_[patient_id] = new_patient;
    }
    // Otherwise create a new patient
    else
    {
        new_patient = new Person(patient_id);
        all_patients_[patient_id] = new_patient;
        current_patients_[patient_id] = new_patient;
    }

    // Add new care period to patient
    CarePeriod* care_period = new CarePeriod(utils::today, new_patient);
    active_care_periods_.push_back(care_period);
    all_care_periods_.push_back(care_period);

    std::cout << PATIENT_ENTERED << std::endl;
}

void Hospital::leave(Params params)
{
    std::string patient_id = params.at(0);

    // Check if patient is in a care period
    if(current_patients_.find(patient_id) == current_patients_.end())
    {
        std::cout << CANT_FIND << patient_id << std::endl;
        return;
    }

    // Find the care period the patient is in and change its status from active to not active
    for(CarePeriod* care_period: active_care_periods_)
    {
        if(care_period->Get_Patient() == current_patients_.at(patient_id))
        {
            care_period->End_CarePeriod(utils::today);
            active_care_periods_.erase(find(active_care_periods_.begin(),
                                            active_care_periods_.end(),
                                            care_period));
            break;
        }
    }

    // Remove patient from the hospital
    current_patients_.erase(patient_id);

    std::cout << PATIENT_LEFT << std::endl;
}

void Hospital::assign_staff(Params params)
{
    std::string staff_id = params.at(0);
    std::string patient_id = params.at(1);

    // Check if staff exists
    if(staff_.find(staff_id) == staff_.end())
    {
        std::cout << CANT_FIND << staff_id << std::endl;
        return;
    }

    // Check if patient is real
    if(current_patients_.find(patient_id) == current_patients_.end())
    {
        std::cout << CANT_FIND << patient_id << std::endl;
        return;
    }

    // Add staff member to patients care period
    Person* staff = staff_.at(staff_id);
    for(CarePeriod* care_period: active_care_periods_)
    {
        if(care_period->Get_Patient() == current_patients_.at(patient_id))
        {
            care_period->Add_Staff(staff);
            break;
        }
    }

    std::cout << STAFF_ASSIGNED << patient_id << std::endl;
}

void Hospital::print_patient_info(Params params)
{
    std::string patient_id = params.at(0);

    // Check if patient has been in the hospital
    if(all_patients_.find(patient_id) == all_patients_.end())
    {
        std::cout << CANT_FIND << patient_id << std::endl;
        return;
    }

    Person* patient = all_patients_.at(patient_id);

    // Find all care periods patient has been in
    std::vector<CarePeriod*> care_periods;
    for(CarePeriod* care_period: all_care_periods_)
    {
        if(care_period->Get_Patient() == all_patients_.at(patient_id))
        {
            care_periods.push_back(care_period);
        }
    }

    // Print the info of all of the care periods patient has been in
    for(CarePeriod* care_period : care_periods)
    {
        Date start_date = care_period->Get_Start_Date();
        Date end_date = care_period->Get_End_Date();
        std::cout << "* Care period: ";
        start_date.print();
        std::cout << " -";
        // Check if patients care period has ended or not
        if(end_date.is_default() == false)
        {
            std::cout << " ";
            end_date.print();
        }
        std::cout << std::endl;

        std::map<std::string, Person*> staff = care_period->Get_Staff();
        std::cout << "  - Staff:";
        // Check if patients care period has/had staff
        if(staff.empty() == true)
        {
            std::cout << " None";
        }
        else
        {
            for(const std::pair<const std::string, Person*>& staff_member : staff)
            {
                std::cout << " " << staff_member.first;
            }
        }
        std::cout << std::endl;
    }
    // Print all the medicine patient has used seperately
    std::cout << "* Medicines:";
    patient->print_medicines("  - ");
}

void Hospital::print_care_periods(Params params)
{
    std::string staff_id = params.at(0);

    bool staff_has_worked = false;

    // Check if staff exists
    if(staff_.find(staff_id) == staff_.end())
    {
        std::cout << CANT_FIND << staff_id << std::endl;
        return;
    }

    // Find all the care periods where the staff in question has worked in
    for(CarePeriod* care_period: all_care_periods_)
    {
        // Each care period can have many staff. Compare and find the staff in question
        for(const std::pair<const std::string, Person*>& staff: care_period->Get_Staff())
        {
            if(staff_id == staff.first)
            {
                staff_has_worked = true;
                Date start_date = care_period->Get_Start_Date();
                Date end_date = care_period->Get_End_Date();
                std::string patient_id = care_period->Get_Patient()->get_id();

                start_date.print();
                std::cout << " -";
                // Check if the care period has ended or not
                if(end_date.is_default() == false)
                {
                    std::cout << " ";
                    end_date.print();
                }
                std::cout << std::endl;

                std::cout << "* Patient: " << patient_id << std::endl;

                break;
            }
        }
    }

    // Check if staff has been recruited but not assigned to patient
    if(staff_has_worked == false)
    {
        std::cout << "None" << std::endl;
    }
}

void Hospital::print_all_medicines(Params)
{
    // Check if hospital has had any patients (no patients = no medicine)
    if(all_patients_.empty() == true)
    {
        std::cout << "None" << std::endl;
        return;
    }

    std::map<std::string, std::vector<std::string>> prescriptions;
    std::vector<std::string> medicines;

    // Find all medicines which have be prescribed.
    for(const std::pair<const std::string, Person*>& patient_pair: all_patients_)
    {
        std::string patient_id = patient_pair.first;
        Person* patient = patient_pair.second;

        medicines = patient->get_medicines();

        for(const std::string& medicine: medicines)
        {
            prescriptions[medicine].push_back(patient_id);
        }
    }

    // Maps are sorted alphabetically by key. Print all medicines and the patients who use them.
    for(const std::pair<const std::string, std::vector<std::string>>& prescription: prescriptions)
    {
        std::string medicine = prescription.first;
        std::vector<std::string> patients = prescription.second;

        std::cout << medicine << " prescribed for" << std::endl;

        for(const std::string& patient: patients)
        {
            std::cout << "* " << patient << std::endl;
        }
    }
}

void Hospital::print_all_patients(Params)
{
    // Check if hosptal has had any patients
    if(all_patients_.empty() == true)
    {
        std::cout << "None" << std::endl;
        return;
    }

    // Call function print_patient_info for all patients
    std::vector<std::string> params;
    for(const std::pair<const std::string, Person*>& patient: all_patients_)
    {
        std::string patient_id = patient.first;
        params.push_back(patient_id);

        std::cout << patient_id << std::endl;

        print_patient_info(params);

        params.pop_back();
    }
}

void Hospital::print_current_patients(Params)
{
    // Check if hosptal has had any patients
    if(current_patients_.empty() == true)
    {
        std::cout << "None" << std::endl;
        return;
    }

    // Call function print_patient_info for all current patients
    std::vector<std::string> params;
    for(const std::pair<const std::string, Person*>& patient: current_patients_)
    {
        std::string patient_id = patient.first;
        params.push_back(patient_id);

        std::cout << patient_id << std::endl;

        print_patient_info(params);

        params.pop_back();
    }
}


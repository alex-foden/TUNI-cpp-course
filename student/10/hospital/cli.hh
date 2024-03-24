/* Class Cli
 * ----------
 * COMP.CS.110 SPRING 2024
 * ----------
 * Class for describing a command line interpreter. Preserves all commands
 * used in hospital program. Implements the exec method that calls an
 * appropriate method based on user-given command through a function pointer.
 *
 * Note: Students shouldn't need to make changes to this class.
 * */
#ifndef CLI_HH
#define CLI_HH

#include "hospital.hh"
#include <string>
#include <iostream>
#include <vector>

// Declares a type of function called.
using MemberFunc = void (Hospital::*)(const std::vector<std::string>& params);

// Struct that 'defines' a function.
struct Cmd
{
    std::vector<std::string> aliases;
    std::string name;
    std::vector<std::string> params;
    MemberFunc func_ptr;
};

// Error strings.
const std::string UNINITIALIZED = "Error: Object uninitialized. Stopping.";
const std::string WRONG_PARAMETERS = "Error: Wrong amount of parameters.";
const std::string UNKNOWN_CMD = "Error: Unknown commands given.";
const std::string FILE_READING_ERROR = "Error: Can't read given file.";
const std::string FILE_READING_OK = "Input read from file: ";

class Cli
{
public:
    /**
     * @brief Cli
     * @param hospital pointer to the hospital obj the functions are called to
     * @param prompt that is printed before taking in user input
     */
    Cli(Hospital* hospital, const std::string& prompt);

    /**
     * @brief exec the cli
     * @return false if execution should end, true if it should continue.
     */
    bool exec();

private:
    /**
     * @brief pop_front
     * @param vec
     * vector utility func that erases the first element of given vector.
     *
     * @note All iterators to the container are invalitaded
     */
    void pop_front(std::vector<std::string>& vec);

    /**
     * @brief find_command
     * @param cmd
     * @return Cmd pointer if one with given alias is found.
     */
    Cmd* find_command(const std::string& cmd);

    /**
     * @brief print_help
     * @param params
     * Generate and print a help, either generic ( no params ) or
     * specific ( func name as param )
     */
    void print_help(const std::vector<std::string>& params);

    /**
     * @brief print_cmd_info
     * @param cmd
     * @param longer
     * Print info of a single cmd.
     * if longer == true, print brief and params.
     */
    void print_cmd_info(Cmd *cmd, bool longer = false) const;

    /**
     * @brief read_from_file
     * @param filename
     * @return false if file could not be read, true otherwise.
     *
     * @note will remove informative output, so even cmds are read, they may
     * not have worked.
     */
    bool read_from_file(const std::string& filename);

    Hospital* hospital_;
    std::string prompt_;
    bool can_start;

    // Vector that stores all cmd info.
    // Exceptionally the lines below may exceed 80 characters,
    // but otherwise the text would be less readable.
    std::vector<Cmd> cmds_ =
    {
        {{"QUIT", "Q"}, "Quit",{},nullptr},
        {{"HELP", "H"},"Help",{"function"},nullptr},
        {{"READ_FROM", "RF"}, "Read", {"filename"},nullptr},
        {{"SET_DATE", "SD"},"Set date",{"day","month","year"},&Hospital::set_date},
        {{"ADVANCE_DATE", "AD"},"Advance date",{"amount"},&Hospital::advance_date},
        {{"RECRUIT", "R"},"Recruit staff",{"staff member id"},&Hospital::recruit},
        {{"PRINT_ALL_STAFF", "PAS"},"Print all staff",{},&Hospital::print_all_staff},
        {{"ADD_MEDICINE", "AM"},"Add medicine for a patient",{"medicine name","strength","dosage","patient id"},&Hospital::add_medicine},
        {{"REMOVE_MEDICINE", "RM"},"Remove medicine from a patient",{"medicine name", "patient id"},&Hospital::remove_medicine},
        {{"ENTER", "E"},"Take patient to hospital",{"patient id"},&Hospital::enter},
        {{"LEAVE", "L"},"Take patient from hospital",{"patient id"},&Hospital::leave},
        {{"ASSIGN_STAFF", "AS"},"Assign staff for a patient", {"staff member id","patient id"},&Hospital::assign_staff},
        {{"PRINT_PATIENT_INFO", "PPI"},"Print patient's info",{"patient id"},&Hospital::print_patient_info},
        {{"PRINT_CARE_PERIODS", "PCPS"},"Print care periods per staff",{"staff member id"},&Hospital::print_care_periods},
        {{"PRINT_ALL_MEDICINES", "PAM"},"Print all used medicines",{},&Hospital::print_all_medicines},
        {{"PRINT_ALL_PATIENTS", "PAP"},"Print all patients",{},&Hospital::print_all_patients},
        {{"PRINT_CURRENT_PATIENTS", "PCP"},"Print current patients",{},&Hospital::print_current_patients},
    };
};

#endif // CLI_HH

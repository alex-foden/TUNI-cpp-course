#ifndef GRADECALCULATOR_HH
#define GRADECALCULATOR_HH

// The constant values below are valid at the beginning of the course.
// At the end of the course, if you use this program to calculate your total
// grade, check the values and update them identical with those in Plussa,
// if needed.
const unsigned int MAX_N_POINTS = 800;
const unsigned int MAX_G_POINTS = 120;
const unsigned int MAX_P_POINTS = 250;

// Calculates the total grade by calling the other functions below.
unsigned int calculate_total_grade(unsigned int n, unsigned int g,
                                   unsigned int p, unsigned int e);

// Calculates score from weekly exercises.
unsigned int score_from_weekly_exercises(unsigned int n, unsigned int g);

// Calculates score from GUI exercises.
unsigned int score_from_gui_exercises(unsigned int g);

// Calculates score from projects.
unsigned int score_from_projects(unsigned int p);

// Compares the mean value calculated based on scores from weekly exercises and
// projects, and possibly also from the exam, with score from GUI exercises.
// If score from GUI exercises is good enough, returns mean as the total grade,
// otherwise returns score from GUI exercises as the total grade.
unsigned int compare_mean_and_gui_score(float mean, unsigned int g);

#endif // GRADECALCULATOR_HH


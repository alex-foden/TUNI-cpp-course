#include "gradecalculator.hh"
#include <iostream>

using namespace std;

// Informs about invalid (too big) N, G, and P points.
// Returns true, if all these three points are valid, otherwise returns false.
bool is_valid_points(unsigned int n,
                     unsigned int g,
                     unsigned int p)
{
    bool is_valid = true;
    if(n > MAX_N_POINTS)
    {
        cout << "Impossible N points" << endl;
        is_valid = false;
    }
    if(g > MAX_G_POINTS)
    {
        cout << "Impossible G points" << endl;
        is_valid = false;
    }
    if(p > MAX_P_POINTS)
    {
        cout << "Impossible P points" << endl;
        is_valid = false;
    }
    return is_valid;
}

// Informs about invalid (too big) exam grade.
// Returns true, if the given exam grade is valid, otherwise returns false.
bool is_valid_exam(unsigned int e)
{
    if(e > 5)
    {
        cout << "Impossible exam grade" << endl;
        return false;
    }
    return true;
}

// Main function.
// Asks first for N, G, and P points, and if all these points are valid,
// prints scores from weekly exercises and projects, and asks for exam grade.
// If also the given exam grade is valid, prints the total grade.
int main()
{
    unsigned int n = 0;
    unsigned int g = 0;
    unsigned int p = 0;
    unsigned int e = 0;
    cout << "Enter N points, G points, P points: ";
    cin >> n;
    cin >> g;
    cin >> p;

    if(is_valid_points(n, g, p))
    {
        cout << "-> W-Score: " << score_from_weekly_exercises(n, g) << endl;
        cout << "-> P-Score: " << score_from_projects(p) << endl;

        cout << "Enter exam grade (if no exam, enter zero): ";
        cin >> e;

        if(is_valid_exam(e))
        {
            cout << "-> Total grade: " << calculate_total_grade(n, g, p, e)
                 << endl;
        }
    }

    return 0;
}

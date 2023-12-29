#include "gradecalculator.hh"
#include <iostream> // needed for max function
#include <cmath>    // needed for ceil function

unsigned int calculate_total_grade(unsigned int n,
                                   unsigned int g,
                                   unsigned int p,
                                   unsigned int e)
{
    float mean = 0.0;
    int score_w = score_from_weekly_exercises(n, g);
    int score_p = score_from_projects(p);

    if(score_w == 0 or score_p == 0)
    {
        return 0;
    }
    if(e == 0)
    {
        mean = ((score_w + score_p) / 2.0) - 2.0;
    }
    else
    {
        mean = (score_w + score_p + e) / 3.0;
    }

    return compare_mean_and_gui_score(mean, score_from_gui_exercises(g));
}

unsigned int score_from_weekly_exercises(unsigned int n, unsigned int g)
{
    float n_only = (n * 100.0) / MAX_N_POINTS;
    float n_and_g = ((n + g) * 100.0)/(MAX_N_POINTS + MAX_G_POINTS);
    float better_score = std::max(n_only, n_and_g);
    if(better_score < 50.0) return 0;
    if(better_score < 60.0) return 1;
    if(better_score < 70.0) return 2;
    if(better_score < 80.0) return 3;
    if(better_score < 90.0) return 4;
    return 5;
}

unsigned int score_from_gui_exercises(unsigned int g)
{
    float score_g = (g * 100.0) / MAX_G_POINTS;
    if(score_g < 30.0) return 2;
    if(score_g < 40.0) return 3;
    if(score_g < 50.0) return 4;
    return 5;
}

unsigned int score_from_projects(unsigned int p)
{
    if(p < 51) return 0;
    if(p < 75) return 1;
    if(p < 125) return 2;
    if(p < 150) return 3;
    if(p < 175) return 4;
    return 5;
}

unsigned int compare_mean_and_gui_score(float mean, unsigned int g)
{
    // Rounding to the nearest integer, exactly half is rounded down
    int rounded_mean = ceil(mean - 0.5);

    if(rounded_mean < 0) return 0;
    if(rounded_mean < 3) return rounded_mean;
    if(rounded_mean < 4 and g >= 3) return rounded_mean;
    if(rounded_mean < 5 and g >= 4) return rounded_mean;
    if(rounded_mean == 5 and g == 5) return rounded_mean;
    return g;
}


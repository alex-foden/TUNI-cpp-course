#ifndef PLAYER_HH
#define PLAYER_HH

#include <string>


class Player
{
public:
    Player(std::string name);
    ~Player();

    std::string get_name();
    void add_points(const int& points);
    int get_points();
    bool has_won();

private:
    std::string name_;
    int points_;
};

#endif // PLAYER_HH

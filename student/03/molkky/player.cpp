#include "player.hh"
#include <iostream>


Player::Player(std::string name):
    name_(name), points_(0)
{

}

Player::~Player()
{

}

std::string Player::get_name()
{
    return name_;
}

void Player::add_points(const int& points)
{
    points_ += points;

    if (points_ > 50)
    {
        points_ = 25;
        std::cout << name_ << " gets penalty points" << std::endl;
    }
}

int Player::get_points()
{
    return points_;
}

bool Player::has_won()
{
    if (points_ == 50)
    {
        return true;
    }

    else
    {
        return false;
    }
}

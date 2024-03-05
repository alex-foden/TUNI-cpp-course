#include "animal.hh"

Animal::Animal(): x_(0), y_(0), moving_noise_("")
{

}

Animal::Animal(const std::string& moving_noise):
    x_(0), y_(0), moving_noise_(moving_noise)
{

}

Animal::~Animal()
{

}
void Animal::move(int x, int y, std::ostream& output)
{
    x_ = x;
    y_ = y;

    output << moving_noise_ << std::endl;
}

void Animal::print_location(std::ostream &output) const
{
    output << "Location: " << x_ << " " << y_ << std::endl;

}

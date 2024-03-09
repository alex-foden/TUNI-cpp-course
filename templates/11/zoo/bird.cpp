#include "bird.hh"


Bird::Bird(): Animal("Flap flap")
{

}

void Bird::print_altitude(std::ostream &output) const
{
    output << "Altitude: " << z_ << std::endl;
}

void Bird::fly(int x, int y, int z, std::ostream& output)
{
    move(x, y, output);
    z_ = z;
}

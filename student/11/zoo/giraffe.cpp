#include "giraffe.hh"

Giraffe::Giraffe():
    Mammal()
{

}

void Giraffe::make_noise(std::ostream &output)
{
    output << "Ori ori ori!" << std::endl;
}

#ifndef MAMMAL_H
#define MAMMAL_H
#include "animal.hh"


class Mammal: public Animal
{
public:
    Mammal();
    void suckle(std::ostream& output);
};

#endif // MAMMAL_H

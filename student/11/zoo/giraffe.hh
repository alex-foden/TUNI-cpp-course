#ifndef GIRAFFE_H
#define GIRAFFE_H
#include "mammal.hh"


class Giraffe: public Mammal
{
public:
    Giraffe();
    void make_noise(std::ostream& output);
};

#endif // GIRAFFE_H

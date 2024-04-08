#include "cockatoo.h"

Cockatoo::Cockatoo():
    Bird()
{

}

void Cockatoo::sing(std::ostream &output)
{
    output << "Kee-ow kee-ow!" << std::endl;
}

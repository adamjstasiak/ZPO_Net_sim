//zawierający definicję klasy Package
#include "types.hpp"

class Package
{
public:
    Package();
    Package(ElementID);
    Package(Package &&);
    Package &operator=(Package &&);
    const ElementID get_id();
    ~Package();
};

// Package::Package(/* args */)
// {
// }

// Package::~Package()
// {
// }

//zawierający definicję klasy Package
#ifndef UNTITLED_PACKAGE_HPP
#define UNTITLED_PACKAGE_HPP


#include "types.hpp"

class Package
{
public:
    Package();
    Package(ElementID);
    Package(Package &&);
    Package &operator=(Package &&);
    const ElementID get_id();
    ~Package() = default;

private:
    int id_ = 0;
};

#endif //UNTITLED_PACKAGE_HPP

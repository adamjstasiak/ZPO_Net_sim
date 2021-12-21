//zawierający definicję klasy Package
#ifndef UNTITLED_PACKAGE_HPP
#define UNTITLED_PACKAGE_HPP

#include <iostream>
#include <set>
#include "types.hpp"


class Package{
public:
    Package() {
        if ( !freed_IDs.empty() ){
            id_ = *freed_IDs.begin();
            freed_IDs.erase(0);               //alternatywnie freed_IDs.erase(freed_IDs.begin());
        }
        else {
            id_ = *assigned_IDs.end()++;
            assigned_IDs.insert(id_);
        }
    };
    Package(ElementID id) { id_ = id; };
    Package(Package &&);
    Package &operator = (Package &&);
    ElementID get_id() const { return id_; };
    ~Package() = default;
    
private:
    static std::set<ElementID> assigned_IDs;  //obecnie przydzielone ID
    static std::set<ElementID> freed_IDs;     //kiedyś używane, obecnie zwolnione
    ElementID id_ = 0;
};

std::set<ElementID> Package::assigned_IDs = {};
std::set<ElementID> Package::freed_IDs = {};

#endif //UNTITLED_PACKAGE_HPP

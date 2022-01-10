#ifndef UNTILTED_NODES_HPP
#define UNTILTED_NODES_HPP 

#include "nodes.hpp"

void ReceiverPreferences::remove_receiver(IPackageReceiver* r){
    auto search = preferences_t.find(r);
    preferences_t.erase(search);
};


#endif //UNTILTED_NODES_HPP
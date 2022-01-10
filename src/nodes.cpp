#ifndef UNTILTED_NODES_HPP
#define UNTILTED_NODES_HPP


#include "nodes.hpp"


void ReceiverPreferences::remove_receiver(IPackageReceiver* r){
    auto search = preferences.find(r);
    preferences.erase(search);
};
void ReceiverPreferences::add_receiver(IPackageReceiver* r){
    double random = (rand() % 10000 + 1) / 10001;
    preferences.insert(std::pair<IPackageReceiver*,double>(r, random));
};

#endif //UNTILTED_NODES_HPP
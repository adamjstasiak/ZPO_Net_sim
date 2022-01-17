#ifndef UNTILTED_NODES_HPP
#define UNTILTED_NODES_HPP


#include "nodes.hpp"


void ReceiverPreferences::remove_receiver(IPackageReceiver* r){
    auto search = preferences.find(r);
    preferences.erase(search);
};
void ReceiverPreferences::add_receiver(IPackageReceiver* r){

    preferences.insert(std::pair<IPackageReceiver*,double>(r, 0.0));
    for (auto& rl : preferences){
        rl.second = 1.0 / (double)preferences.size();
    }
};
void IPackageReceiver::receive_package(Package && p){


};

#endif //UNTILTED_NODES_HPP
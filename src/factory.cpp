// implementacja funkcji factory.hpp
#ifndef UNTILTED_FACTORY_CPP
#define UNTILTED_FACTORY_CPP

#include "factory.hpp"
#include <map>
#include <stdexcept>
#include <string>
#include <istream>
#include <sstream>
#include <vector>

void Factory::do_work(Time time){
    std::for_each(workers_.begin(),workers_.end(), [time](auto& el){ el.do_work(time);});
}

void Factory::do_deliveries(Time time){
    std::for_each(ramps_.begin(),ramps.end(), [time](auto& el){ el.deliver_goods(time); });
}

void Factory::do_package_passing(){
    std::for_each(ramps_.begin(),ramps_.end(), [](auto& el){el.send_package();});
    std::for_each(workers_.begin(),workers_.end(), [](auto& el){el.send_package();});
};

void Factory::remove_receiver(NodeCollection<Node>& collection, Element id){
    for(auto &el: collection) {
        for(auto& i:el.preferences_.get_preferences())
            if(i.first->get_id== id){
                el.preferences_.remove_receiver(i.first);
                break;
            }
    }
}

void Factory::remove_worker(ElementID id){
    remove_receiver(ramps_, id);
    remove_receiver(workers_,id);
    workers_.remove_by_id(id);
}

void Factory::remove_storehouse(ElementID id){
    remove_receiver(workers_,id);
    storehouses_.remove_by_id(id);
}
#endif //UNTILTED_FACTORY_HPP
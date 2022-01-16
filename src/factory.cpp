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

bool Factory::has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*,NodeColor>& node_colors) const{
    if(node_colors[sender]== NodeColor::VERIFIED){
        return true;
    }

    node_colors[sender] = NodeColor::VISITED:
    if(sender->receiver_preferences_.get_preferences().empty()){
        throw std::logic_error("No recipients");
    }
    bool is_reachable = false;
    for(const auto& el: sender->receiver_preferences_.get_preferences()){
        if(el.first->get_receiver_type()== ReceiverType::Storehouse){
            is_reachable = true;
        }
        else if((el.first->get_receiver_type()== ReceiverType::Worker){
            IPackageReceiver* receiver_ptr = el.first;
            auto worker_ptr dynamic_cast<Worker*>(receiver_ptr);
            auto sendrecv_ptr = dynamic_cast<PackageSender*>(worker_ptr);
            if(sendrecv_ptr==sender){
                continue;
            }
            is_reachable = true;
            if(node_colors[sendrecv_ptr]==NodeColor::UNVISITED){
                has_reachable_storehouse(sendrecv_ptr,node_colors);
            }

        }
    }
    node_colors[sender] = NodeColor::VERIFIED;
    if(is_reachable){
        return true;
    }
    else
        throw std::logic_error("No recipients");
}        
bool Factory::is_consistent() const{
    std::map<const PackageSender*, NodeColor> node_colors;
    for(const auto& el: workers_){
        node_colors[(PackageSender *) &el] = NodeColor::UNVISITED; 
    }
    for(const auto& el: ramps_){
        node_colors[(PackageSender *) &el] = NodeColor::UNVISITED; 
    }

    for(const auto& el: ramps_){
        try{
            has_reachable_storehouse(&el, node_colors);
            return true;
        }
        catch(const std::exception& err){
            return false;
        }
    }
    return true;

}


#endif //UNTILTED_FACTORY_CPP
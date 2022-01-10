//definicja szablonu klasy NodeCollection oraz definicja klasy Factory
#ifndef UNTILTED_FACTORY_HPP
#define UNTILTED_FACTORY_HPP


#include "nodes.hpp"
#include "types.hpp"

class Factory{
public:
    void add_ramp(Ramp&&);
    void remove_ramp(ElementID id);
    using const_iterator = std::list<Package>::const_iterator;
    NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id);
    NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id);
    NodeCollection<Ramp>::const_iterator ramp_cbegin();
    NodeCollection<Ramp>::const_iterator ramp_cend();
    NodeCollection<Ramp>::const_iterator ramp_begin();
    NodeCollection<Ramp>::const_iterator ramp_end(); 

    bool is_consistent(void);
    void do_deliveries(Time);
    void do_package_passing(void);
    void do_work(Time);
private:
    void remove_receiver(NodeCollection<Node>& collection, ElementID id);
};

class Ramps{
 
};

class Workers{

};

class NodeCollection{
    void add(Node&& node);
    void remove_by_id(ElementID id);
    using container_t = typename std_container_t<Node>;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;
    
};

#endif //UNTILTED_FACTORY_HPP
//definicja szablonu klasy NodeCollection oraz definicja klasy Factory
#ifndef UNTILTED_FACTORY_HPP
#define UNTILTED_FACTORY_HPP


#include "nodes.hpp"
#include "types.hpp"
#include <list>

enum class NodeColor{
    UNVISITED, VISITED, VERIFIED
}

template<class Node>
class NodeCollection{
public:
    using container_t = typename std::list<Node>;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;

    void add(Node&& node){
        list_of_nodes_.push_back(std::move(node));
    }

    iterator find_by_id(ElementID id){
        for(auto el = list_of_nodes_.begin(); el != list_of_nodes_.end();el++){
            if(el->get_id() == id){
                return el;
            }
        }
        return list_of_nodes_.end();

    }
    const_iterator find_by_id(ElementID id){
        for(auto el = list_of_nodes_.cbegin(); el != list_of_nodes_.cend(); el++){
            if(el->get_id() == id) {
                return el;
            }
        }
        return  list_of_nodes_.cend();
    }

    void remove_by_id(ElementID id) {
        auto el = find_by_id(id);
        if( el != list_of_nodes.end()){
            list_of_nodes_.erase(el);
        }
    }

    container_t get_nodes_list()  const { return list_of_nodes_ ; }
    const_iterator cbegin() const {return list_of_nodes_.cbegin();}
    iterator begin() { return  list_of_nodes_.begin();}
    const_iterator cend() const { return list_of_nodes_.cend();}
    iterator end() { return  list_of_nodes_.end();}
    const_iterator begin() {return  list_of_nodes_.begin();}
    const_iterator end() { return list_of_nodes_.end();}

private:
    container_t list_of_nodes_;

};

class Ramps: public NodeCollection<Ramp>{

};

class Workers: public NodeCollection<Worker>{

};

class Storehouses: public NodeCollection<Storehouse>{

};


class Factory{
public:
    void add_ramp(Ramp&& ramp) {ramps_.add(std::move(ramp));};
    void remove_ramp(ElementID id) {ramps_.remove_by_id(id);};
    NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id) {return ramps_.find_by_id(id);};
    NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id) {return ramps_.find_by_id(id);};
    NodeCollection<Ramp>::const_iterator ramp_cbegin() const{ return ramps_.cbegin();};
    NodeCollection<Ramp>::const_iterator ramp_cend() const{return ramps_.cend();};
    NodeCollection<Ramp>::const_iterator ramp_begin() const{return  ramps_.begin();};
    NodeCollection<Ramp>::const_iterator ramp_end() const{return ramps_.end();};

    void add_worker(Worker&& worker) {workers_.add(std::move(worker));};
    void remove_worker(ElementID id);
    NodeCollection<Worker>::iterator find_worker_by_id(ELementID id) {return workers_.find_by_id(id);}
    NodeCollection<Worker>::const_iterator find_worker_by_id(ElementID id) {return  workers_.find_by_id(id)}
    NodeCollection<Worker>::const_iterator worker_cbegin() const{return workers_.cbegin();};
    NodeCollection<Worker>::const_iterator worker_cend() const { return workers_.cend();}
    NodeCollection<Worker>::const_iterator worker_begin() const {return workers_.begin();};
    NodeCollection<Worker>::const_iterator worker_end() const { return workers_.end();};

    void add_storehouse(Storehouse&& storehouse) {storehouses_.add(std::move(storehouse));};
    void remove_storehouse(ElementID id);
    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElemetID id) {return  storehouses_.find_by_id(id);};
    NodeCollection<Storehouse>::const_iterator storehouse_cbegin() const {return  storehouses_.cbegin();};
    NodeCollection<Storehouse>::const_iterator storehouse_cend() const {return  storehouses_.cend();};
    NodeCollection<Storehouse>::const_iterator storehouse_begin() const {return  storehouses_.begin();};
    NodeCollection<Storehouse>::const_iterator storehouse_end() const {return  storehouses_.end();};

    bool is_consistent(void) const;

    void do_deliveries(Time time);
    void do_package_passing(void);
    void do_work(Time time);

private:
    NodeCollection <Worker> workers_;
    NodeCollection <Storehouse> storehouses_;
    NodeCollection <Ramp> ramps_;
    template<class Node>
    void remove_receiver(NodeCollection<Node>& collection, ElementID id) {collection.remove_by_id(id);};
};

Factory load_factory_structure(std::istream& is);
void save_factory_structure(Factory& factory,std::ostream& os);

#endif //UNTILTED_FACTORY_HPP
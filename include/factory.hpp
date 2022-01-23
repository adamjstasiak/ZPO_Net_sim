//definicja szablonu klasy NodeCollection oraz definicja klasy Factory
#ifndef UNTILTED_FACTORY_HPP
#define UNTILTED_FACTORY_HPP


#include "nodes.hpp"
#include "types.hpp"
#include <list>

enum class NodeColor{
    UNVISITED, VISITED, VERIFIED
};

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
    const_iterator find_by_cid(ElementID id){
        for(auto el = list_of_nodes_.cbegin(); el != list_of_nodes_.cend(); el++){
            if(el->get_id() == id) {
                return el;
            }
        }
        return  list_of_nodes_.cend();
    }

    void remove_by_id(ElementID id) {
        auto el = find_by_id(id);
        if( el != list_of_nodes_.end()){
            list_of_nodes_.erase(el);
        }
    }

    container_t get_nodes_list()  const { return list_of_nodes_ ; }
    const_iterator cbegin() const {return list_of_nodes_.cbegin();}
    iterator begin() { return  list_of_nodes_.begin();}
    const_iterator cend() const { return list_of_nodes_.cend();}
    iterator end() { return  list_of_nodes_.end();}


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
    NodeCollection<Ramp>::const_iterator find_ramp_by_cid(ElementID id) {return ramps_.find_by_id(id);};
    NodeCollection<Ramp>::const_iterator ramp_cbegin() const{ return ramps_.cbegin();};
    NodeCollection<Ramp>::const_iterator ramp_cend() const{return ramps_.cend();};
    NodeCollection<Ramp>::const_iterator ramp_begin() {return  ramps_.begin();};
    NodeCollection<Ramp>::const_iterator ramp_end() {return ramps_.end();};

    void add_worker(Worker&& worker) {workers_.add(std::move(worker));};
    void remove_worker(ElementID id);
    NodeCollection<Worker>::iterator find_worker_by_id(ElementID id) {return workers_.find_by_id(id);}
    NodeCollection<Worker>::const_iterator find_worker_by_cid(ElementID id) {return  workers_.find_by_id(id);}
    NodeCollection<Worker>::const_iterator worker_cbegin() const{return workers_.cbegin();};
    NodeCollection<Worker>::const_iterator worker_cend() const { return workers_.cend();}
    NodeCollection<Worker>::const_iterator worker_begin()  {return workers_.begin();};
    NodeCollection<Worker>::const_iterator worker_end()  { return workers_.end();};

    void add_storehouse(Storehouse&& storehouse) {storehouses_.add(std::move(storehouse));};
    void remove_storehouse(ElementID id);
    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id) {return  storehouses_.find_by_id(id);};
    NodeCollection<Storehouse>::const_iterator storehouse_cbegin() const {return  storehouses_.cbegin();};
    NodeCollection<Storehouse>::const_iterator storehouse_cend() const {return  storehouses_.cend();};
    NodeCollection<Storehouse>::const_iterator storehouse_begin()  {return  storehouses_.begin();};
    NodeCollection<Storehouse>::const_iterator storehouse_end()  {return  storehouses_.end();};

    bool has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors);
    bool is_consistent();

    void do_deliveries(Time time);
    void do_package_passing(void);
    void do_work(Time time);

private:
    NodeCollection <Worker> workers_;
    NodeCollection <Storehouse> storehouses_;
    NodeCollection <Ramp> ramps_;
    template<class Node>
    void remove_receiver(NodeCollection<Node>& collection, ElementID id);
};

template<class Node>

void Factory::remove_receiver(NodeCollection<Node>& collection, ElementID id) {
    Node *node = &(*collection.find_by_id(id));

    std::for_each(ramps_.begin(), ramps_.end(),
                  [&node](auto &ramp) { ramp.receiver_preferences.remove_receiver(node); });
    std::for_each(workers_.begin(), workers_.end(),
                  [&node](auto &worker) { worker.receiver_preferences.remove_receiver(node); });
    collection.remove_by_id(id);
}
enum ElementType{
    RAMP,WORKER,STOREHOUSE,LINK,LOADING_RAMP

};

struct ParsedLineData{
    ElementType element_type;
    std::map<std::string, std::string> parameters; 
};
ParsedLineData parse_line(const std::string & line);
Factory load_factory_structure(std::istream& is);
void save_factory_structure(Factory& factory,std::ostream& os);

#endif //UNTILTED_FACTORY_HPP
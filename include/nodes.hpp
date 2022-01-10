// definicje klas IPackageReceiver, Storehouse, ReceiverPreferences,
// PackageSender, Ramp i Worker oraz typu wyliczeniowego ReceiverType
#ifndef UNTILTED_NODES_HPP
#define UNTILTED_NODES_HPP

#include "package.hpp"
#include "storage_types.hpp"
#include <iostream>
#include <stdexcept>
#include <memory>
#include <optional>
#include <map>
class IPackageReceiver : public Worker, Storehouse{
public:
    virtual void receive_package(Package && p) = 0;
    virtual ElementID get_id(void) const = 0;
};

class PackageSender : public Ramp , Worker {
public:
    PackageSender(PackageSender&&);
    void send_package(void);
    std::optional<Package>& get_sending_buffer(void) const;
    
    ReceiverPreferences receiver_preferences_; 

protected:
    void push_package(Package&&);

};

class Storehouse : public IPackageStockpile{
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d) {};
};

class ReceiverPreferences : public PackageSender{
public:
    ReceiverPreferences(ProbabilityGenerator pg) ;
    void add_receiver(IPackageReceiver* r) ; 
    void remove_receiver(IPackageReceiver* r);
    IPackageReceiver* choose_receiver(void);
    using preferences_t = std::map<IPackageReceiver*,double>;
    using const_iterator = preferences_t::const_iterator;
    preferences_t& get_preferences(void); 
    
};



class Ramp{
public:
    Ramp(ElementID id, TimeOffset di) {};
    void deliver_goods(Time t) ;
    TimeOffset get_delivery_interval(void);
    ElementID get_id(void);
};

class Worker : public IPackageQueue{
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) {};
    void do_work(Time t);
    TimeOffset get_processing_duration(void);
    Time get_package_processing_start_time(void);  
};

enum class ReceiverType{
    WORKER, STOREHOUSE
};

#endif //UNTILTED_NODES_HPP
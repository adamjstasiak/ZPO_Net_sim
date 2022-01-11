// definicje klas IPackageReceiver, Storehouse, ReceiverPreferences,
// PackageSender, Ramp i Worker oraz typu wyliczeniowego ReceiverType


#include "package.hpp"
#include "storage_types.hpp"
#include <iostream>
#include <stdexcept>
#include <memory>
#include <optional>
#include <map>

class Storehouse : public IPackageStockpile{
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d) : id_(id){};
private:
    ElementID id_;//  = Package.get_id();
    std::unique_ptr<IPackageStockpile> d_;
};

class IPackageReceiver : public Storehouse{
public:
    virtual void receive_package(Package && p) = 0;
    virtual ElementID get_id(void) const = 0;
};

class Worker : public IPackageQueue{
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) : id_(id), pd_(pd){};
    void do_work(Time t);
    TimeOffset get_processing_duration(void);
    Time get_package_processing_start_time(void);
private:
    ElementID id_;
    TimeOffset pd_;
    std::unique_ptr<IPackageQueue> q_;

};

class ReceiverPreferences {
public:
    using preferences_t = std::map<IPackageReceiver*,double>;
    using const_iterator = preferences_t::const_iterator;

    ReceiverPreferences(ProbabilityGenerator pg) ;
    void add_receiver(IPackageReceiver* r) ;
    void remove_receiver(IPackageReceiver* r);
    IPackageReceiver* choose_receiver(void);
    preferences_t& get_preferences(void);

    preferences_t preferences;

};

class Ramp{
public:
    Ramp(ElementID id, TimeOffset di) : id_(id), di_(di){};
    void deliver_goods(Time t) ;
    TimeOffset get_delivery_interval(void);
    ElementID get_id(void);
private:
    ElementID id_;
    TimeOffset di_;
};

class PackageSender : public Worker, ReceiverPreferences, Ramp{
public:
    PackageSender(PackageSender&&) = default;
    void send_package(void);
    std::optional<Package>& get_sending_buffer(void) const;
    
    ReceiverPreferences receiver_preferences_; 

protected:
    void push_package(Package&&);

};


enum class ReceiverType{
    WORKER, STOREHOUSE
};


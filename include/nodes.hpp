// definicje klas IPackageReceiver, Storehouse, ReceiverPreferences,
// PackageSender, Ramp i Worker oraz typu wyliczeniowego ReceiverType


#include "package.hpp"
#include "storage_types.hpp"
#include <iostream>
#include <stdexcept>
#include <memory>
#include <optional>
#include <map>
#include "helpers.hpp"
enum class ReceiverType{
    WORKER, STOREHOUSE
};

class IPackageReceiver{
public:
    using const_iterator = std::list<Package>::const_iterator;

    virtual void receive_package(Package && p) = 0;
    virtual ElementID get_id(void) const = 0;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator cend() const = 0;
    virtual const_iterator begin() const = 0;
    virtual const_iterator end() const = 0;
    virtual ReceiverType get_receiver_type() const = 0;
private:

};

class Storehouse : public IPackageReceiver{
public:
    using const_iterator = std::list<Package>::const_iterator;

    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d = std::make_unique<PackageQueue>(PackageQueueType::FIFO)) : id_(id), d_(std::move(d)){};
    ElementID get_id(void) const override {return id_;}
    void receive_package(Package && p) override {d_->push(std::move(p));}
     const_iterator cbegin() const override{ return d_->cbegin(); };
     const_iterator cend() const override {return d_->cend();};
     const_iterator begin() const override{return d_->begin();};
     const_iterator end() const override{return d_->end();};
    ReceiverType get_receiver_type() const override {return ReceiverType::STOREHOUSE;};

private:
    ElementID id_;//  = Package.get_id();
    std::unique_ptr<IPackageStockpile> d_;
};

class ReceiverPreferences {//: public PackageSender{
public:
    using preferences_t = std::map<IPackageReceiver*,double>;
    using const_iterator = preferences_t::const_iterator;

    ReceiverPreferences(ProbabilityGenerator pg = probability_generator) : generator(pg) {};
    void add_receiver(IPackageReceiver* r) ;
    void remove_receiver(IPackageReceiver* r);
    IPackageReceiver* choose_receiver(void);
    preferences_t& get_preferences(void);



    preferences_t preferences;
    ProbabilityGenerator generator ;

};

class PackageSender{
public:
    PackageSender(PackageSender&&) = default;

    PackageSender() {};

    void send_package(void);

    std::optional<Package>& get_sending_buffer(void) const;

    virtual ~PackageSender() = default;


    ReceiverPreferences receiver_preferences_;

protected:
    void push_package(Package&& package);

};


class Worker : public PackageSender, public IPackageReceiver{
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) : id_(id), pd_(pd), q_(std::move(q)){};
    void do_work(Time t);
    TimeOffset get_processing_duration(void);
    Time get_package_processing_start_time(void);
private:
    ElementID id_;
    TimeOffset pd_;
    std::unique_ptr<IPackageQueue> q_;

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






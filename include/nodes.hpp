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
    virtual ~Storehouse() = default;
private:
    ElementID id_;//  = Package.get_id();
    std::unique_ptr<IPackageStockpile> d_;
};

class ReceiverPreferences {//: public PackageSender{
public:
    using preferences_t = std::map<IPackageReceiver*,double>;
    using const_iterator = preferences_t::const_iterator;

    ReceiverPreferences(ProbabilityGenerator pg = probability_generator) : generator(pg) {};
    void add_receiver(IPackageReceiver* r);
    void remove_receiver(IPackageReceiver* r);
    //
    const_iterator preferences_cbegin() const {return preferences.cbegin();};
    const_iterator  preferences_cend() const {return preferences.cend();};
    const_iterator preferences_begin() {return preferences.begin();};
    const_iterator preferences_end() {return preferences.end();};
    IPackageReceiver* choose_receiver(void);

    const preferences_t & get_preferences() const { return preferences;};
    //



    preferences_t preferences;
    ProbabilityGenerator generator ;

};

class PackageSender{
public:
    using Sendingbuffer =   std::optional<Package>;
    PackageSender(PackageSender&&) = default;

    PackageSender() {};

    void send_package(void);

    const std::optional<Package>& get_sending_buffer(void) const {return sending_buffer;};

    virtual ~PackageSender() = default;


    ReceiverPreferences receiver_preferences_;

protected:
    void push_package(Package&& package);
private:
    Sendingbuffer sending_buffer;


};


class Worker : public PackageSender, public IPackageReceiver {
public:
    using preferences_t = std::map<IPackageReceiver*,double>;

    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) : id_(id), pd_(pd), q_(std::move(q)){};
    void do_work(Time t);
    TimeOffset get_processing_duration(void) {return pd_;};
    Time get_package_processing_start_time(void) {return proces;};
    IPackageQueue* get_queue(void);
    std::optional<Package>& get_processing_buffer(void);
    preferences_t preferences;
    
private:
    ElementID id_;
    TimeOffset pd_;
    std::unique_ptr<IPackageQueue> q_;//Może dodanie zmiennej klasy packagequeue /albo odwołanie do metod klasy ipachagequeu przez inteligentny wskaźnik
    ReceiverPreferences receiver_preferences_;
    std::optional<Package> worker_buffer;
    Time proces;
};



class Ramp: public PackageSender{
public:
    using preferences_t = std::map<IPackageReceiver*,double>;

    Ramp(ElementID id, TimeOffset di) : id_(id), di_(di){};
    void deliver_goods(Time t) ;
    TimeOffset get_delivery_interval(void) {return di_;};
    ElementID get_id(void) {return id_;};
    preferences_t preferences;

private:
    ElementID id_;
    TimeOffset di_;
    ReceiverPreferences receiver_preferences_;


};






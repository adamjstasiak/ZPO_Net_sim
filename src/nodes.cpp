#ifndef UNTILTED_NODES_HPP
#define UNTILTED_NODES_HPP


#include "nodes.hpp"


void ReceiverPreferences::remove_receiver(IPackageReceiver* r){
    auto search = preferences.find(r);
    preferences.erase(search);
}
void ReceiverPreferences::add_receiver(IPackageReceiver* r){

    preferences.insert(std::pair<IPackageReceiver*,double>(r, 0.0));
    for (auto& rl : preferences){
        rl.second = 1.0 / (double)preferences.size();
    }
}

IPackageReceiver* ReceiverPreferences::choose_receiver() {
    double p = generator();
    double sum = 0;
    for (auto& rl : preferences){
        sum += rl.second ;
        if(p < sum){
            return rl.first;
        }
    }
    throw std::logic_error("No recipients");
}
void PackageSender::push_package(Package &&package) {
    sending_buffer.emplace(std::move(package));

}
void PackageSender::send_package() {
    IPackageReceiver* p = receiver_preferences_.choose_receiver();
    p->receive_package(std::move(sending_buffer.value()));
    sending_buffer.reset();
}
void Ramp::deliver_goods(Time t){
    if(t % di_ == 1){
        (push_package(Package()));
    }
}
void Worker::do_work(Time t) {

    if((!worker_buffer.has_value()) && (!q_->empty())){
        Package que = q_->pop();
        worker_buffer.emplace(std::move(que));
        proces = t;
    }
    if(t - proces == pd_){
        push_package(std::move(worker_buffer.value()));
        worker_buffer.reset();
        proces = 0;
    }


}


#endif //UNTILTED_NODES_HPP
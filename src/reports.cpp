//
// Created by stasi on 23.01.2022.
//

#include "reports.hpp"
#include "simulation.hpp"

void generate_structure_report(const Factory& factory,std::ostream& os){
    os << "=== [ Turn: " << std::to_string(t) << " ] ===" << '\n';
    os << '\n';
    os << "== WORKERS ==" << '\n';
    for ( auto  it = factory.worker_begin(); it !=factory.worker_end(); it ++ ) {
        os << '\n' << "WORKER #" << std::to_string(it->get_id()) << '\n';
        if (it->get_processing_buffer() != std::nullopt) {
            os << " PBuffer: #" << it->get_processing_time()->get_id() << '\n';
            os << "(pt = " << it->get_precessing_time()<< ")" << '\n';
        }else
            os << " PBuffer: (empty)" << '\n';
        if(!(it->get_queue()->size()==1)) {
            os << " Queue: ";
            for (const auto &el: *it->get_queue()) {
                if (it->get_queue()->size() == 1)
                    os << "#" << el.get_id();
                else
                    os << ", #" << el.get_id();
            }
            os << "\n";
        } else
            os << " Queue: (empty)" << '\n';
        if (it -> is_sending_buffer_empty()){
            os << " SBuffer: (empty)" << '\n';
        }else
            os << " SBuffer: #" << it ->get_sending_buffer_id() << "\n";
    }
    os << '\n' << '\n';

    os << "== STOREHOUSES ==" << '\n';
    for(auto it =factory.storehouse_begin(); it != factory.storehouse_end();it ++) {
        os << '\n' << "STOREHOUSE #" << std::to_string(it->get_id()) << '\n';
        if (!(it->get_queue()->empty())) {
            os << " Stock: ";
            for (const auto &el: *it->get_queue()) {
                if (it->get_queue()->size() == 1)
                    os << "#" << el.get_id() << '\n';
                else
                    os << ", #" << el.get_id() << '\n';
            }
        } else
            os << " Stock: (empty)" << '\n';
    }
    os << '\n';
}
void generate_structure_turn_report(const Factory& factory,std::ostream os, Time t){
    os << '\n';
    os << "== LOADING RAMPS ==" << '\n';
    for ( auto  it = factory.ramp_begin(); it !=factory.ramp_end(); it ++ ){
        os << '\n' << "LOADING RAMP #" << std::to_string(it->get_id());
        os << '\n';
        os << ' ' << ' ' << "Delivery interval: " << std::to_string(it->get_delivery_interval());
        os << '\n';
        os << ' ' << ' ' << "Receivers: ";
        os << '\n';
        std::vector<IPackageReceiver*> receivers;
        ElementID count = 1;
        while(receivers.size() != it->receiver_preferences_.get_preferences().size()){
            for(auto i: it->receivers_preferences_.get_preferences()){
                if(i.first->get_id()== count){
                    receivers.push_back(i.first);
                    count++;
                }
            }
        }
        for(auto i: receivers){
            if(i ->get_receiver_type() == ReceiverType::WORKER)
                os<< ' ' << ' ' << ' ' << ' ' << "worker #" << std::to_string(i->get_id()) << '\n';
            else if(i ->get_receiver_type() == ReceiverType::STOREHOUSE)
                os<< ' ' << ' ' << ' ' << ' ' << "storehouse #" << std::to_string(i->get_id()) << '\n';
        }
    }
    os << '\n' << '\n';

    os << "== WORKERS ==" << '\n';
    for ( auto  it = factory.worker_begin(); it !=factory.worker_end(); it ++ ) {
        os << '\n' << "WORKER #" << std::to_string(it->get_id()) << '\n';
        os << ' ' << ' ' << "Processing time: " << std::to_string(it->get_processing_duration()) << '\n';
        os << ' ' << ' ' << "Queeu type: ";
        if(it-> get_queue()->get_queue_type() == PackageQueueType::FIFO)
            os << "FIFO" << '\n';
        else if (it-> get_queue()->get_queue_type() == PackageQueueType::LIFO)
            os << "LIFO" << '\n';
        os << ' ' << ' ' << "Receivers:";
        os << '\n';
        std::vector<IPackageReceiver*> receivers;
        ElementID count = 1;
        while(receivers.size() != it->receiver_preferences_.get_preferences().size()){
            for(auto i: it->receivers_preferences_.get_preferences()){
                if(i.first->get_id()== count){
                    receivers.push_back(i.first);
                    count++;
                }
            }
        }
        for(auto i: receivers){
            if(i ->get_receiver_type() == ReceiverType::WORKER)
                os<< ' ' << ' ' << ' ' << ' ' << "worker #" << std::to_string(i->get_id()) << '\n';
            else if(i ->get_receiver_type() == ReceiverType::STOREHOUSE)
                os<< ' ' << ' ' << ' ' << ' ' << "storehouse #" << std::to_string(i->get_id()) << '\n';
        }
    }
    os << '\n' << '\n';

    if(factory.storehouse_begin() != factory.storehouse_end()){
        os << "==STOREHOUSES ==" << '\n';
        for ( auto it = factory.storehouse_begin(); it !=factory.storehouse_end(); it ++){
            os << '\n' << "STOREHOUSE #" << std::to_string(iter->get_id());
            os << '\n';
        }
        os << '\n';
    }
}
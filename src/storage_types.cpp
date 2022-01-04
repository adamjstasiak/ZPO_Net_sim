//zawierające definicje funkcjonalności odpowiednich plików nagłówkowych (oraz ewentualne definicje dodatkowych funkcjonalności,
//niezbędnych wyłącznie w ramach danego pliku źródłowego)

#include "storage_types.hpp"
#include <list>
#include <iterator>


Package PackageQueue::pop(){
    switch(type_){
        case PackageQueueType::FIFO:
            auto x = std::move(queue_.front()); 
            queue_.pop_front();
            return x ;
        case PackageQueueType::LIFO:
            auto x = std::move(queue_.back()); 
            queue_.pop_back();
            return x;
    }
}
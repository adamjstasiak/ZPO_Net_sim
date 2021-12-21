//zawierające definicje funkcjonalności odpowiednich plików nagłówkowych (oraz ewentualne definicje dodatkowych funkcjonalności,
//niezbędnych wyłącznie w ramach danego pliku źródłowego)

#include "storage_types.hpp"
#include <list>
size_t IPackageStockpile::size() {
}
Package IPackageQueue::pop(){
    switch(type_){
        case PackageQueueType::FIFO:
            Package x = *queue_.begin(); 
            queue_.pop_front();
        case PackageQueueType::LIFO:
        Package x = *queue_.end(); 
            queue_.pop_back();
    }

}
//zawierający definicje klas IPackageStockpile, IPackageQueue
//i PackageQueue oraz typu wyliczeniowego PackageQueueType
#ifndef UNTILTED_STORAGE_TYPES_HPP
#define UNTILTED_STORAGE_TYPES_HPP

#include <list>
#include "package.hpp"

class IPackageStockpile{
public:
    void push(Package &&);
    bool empty();
    std::size_t size() ;
    ~IPackageStockpile();

    using const_iterator = std::list<Package>::const_iterator;

    const_iterator cbegin() const { return Package_.queue_.cbegin(); }
    const_iterator cend() const { return Package_.queue_.cend(); }
    const_iterator begin() const { return Package_.queue_.begin(); }
    const_iterator end() const { return Package_.queue_.end(); }

private:
    PackageQueue Package_;
};

IPackageStockpile::~IPackageStockpile(){

}


enum class PackageQueueType{
    FIFO,
    LIFO
};

class IPackageQueue : IPackageStockpile{
public:
    Package pop();
    const PackageQueueType get_queue_type(){ return type_;};
private:
    PackageQueue Package_;
    std::list<Package> queue_;
    PackageQueueType type_;
};

class PackageQueue : IPackageQueue{
public:
    PackageQueue(PackageQueueType type, std::list<Package> queue = {}): type_(type) ,queue_(queue) {};
    PackageQueueType type_;
    std::list<Package> queue_;
};

#endif //UNTILTED_STORAGE_TYPES_HPP
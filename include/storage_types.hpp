//zawierający definicje klas IPackageStockpile, IPackageQueue
//i PackageQueue oraz typu wyliczeniowego PackageQueueType
#ifndef UNTILTED_STORAGE_TYPES_HPP
#define UNTILTED_STORAGE_TYPES_HPP

#include <list>
#include "package.hpp"

class IPackageStockpile
{
public:
    void push(Package &&);
    bool empty();
    std::size_t size();
    ~IPackageStockpile();

    using const_iterator = std::list<Package>::const_iterator;
    const_iterator cbegin() const { return Package::id_.cbegin(); }
    const_iterator cend() const { return Package::id_.cend(); }
    const_iterator begin() const { return Package.begin(); }
    const_iterator end() const { return Package.end(); }

private:
    PackageQueue Package_;
};

IPackageStockpile::~IPackageStockpile()
{
}

enum class PackageQueueType
{
    FIFO,
    LIFO
};

class IPackageQueue
{
public:
    Package pop();
    PackageQueueType get_queue_type();
};

class PackageQueue
{
public:
    PackageQueue(PackageQueueType);
};

#endif //UNTILTED_STORAGE_TYPES_HPP
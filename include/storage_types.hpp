//zawierający definicje klas IPackageStockpile, IPackageQueue
//i PackageQueue oraz typu wyliczeniowego PackageQueueType
#include <list>
#include "package.hpp"

class IPackageStockpile
{
public:
    void push(Package &&);
    bool empty();
    std::size_t size();
    ~IPackageStockpile();

    using const_iteraror = std::list<Package>;
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
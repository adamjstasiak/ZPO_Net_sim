//zawierający definicje klas IPackageStockpile, IPackageQueue
//i PackageQueue oraz typu wyliczeniowego PackageQueueType
#ifndef UNTILTED_STORAGE_TYPES_HPP
#define UNTILTED_STORAGE_TYPES_HPP

#include <list>
#include "package.hpp"

class IPackageStockpile{
public:
    using const_iterator = std::list<Package>::const_iterator;
    using size_type = std::size_t;
    virtual void push(Package &&) = 0;
    virtual bool empty() = 0;
    virtual size_type size() = 0;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator cend() const = 0;
    virtual const_iterator begin() const = 0;
    virtual const_iterator end() const = 0;
    virtual ~IPackageStockpile() = default;
};



enum class PackageQueueType{
    FIFO,
    LIFO
};

class IPackageQueue : public IPackageStockpile{
public:
    virtual Package pop() = 0;
    virtual PackageQueueType get_queue_type() const = 0;
};

class PackageQueue : public IPackageQueue{
public:
    explicit PackageQueue(PackageQueueType type): type_(type) {};
    Package pop() override;
    PackageQueueType get_queue_type() const override {return type_;};
    const_iterator cbegin() const {return queue_.cbegin();};
    const_iterator cend() const {return queue_.cend();};
    const_iterator begin() const {return queue_.begin();};
    const_iterator end() const  {return queue_.end();};
    void push(Package && package) {queue_.push_back(std::move(package));};
    bool empty() {return queue_.empty();};
    size_type size() {return queue_.size();};
    
    PackageQueueType type_;
    std::list<Package> queue_;
};

#endif //UNTILTED_STORAGE_TYPES_HPP
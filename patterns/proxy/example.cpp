// virtual proxy

#include <cstddef>
#include <iostream>
#include <memory>
#include <numeric>
#include <vector>
#include <string>

class IIntContainer {
public:
    virtual int& at(std::size_t idx) = 0;
    virtual void add(int x) = 0;
    virtual std::size_t size() const = 0;
    virtual ~IIntContainer() {}
};

class IntContainer : public IIntContainer {
    std::vector<int> container_;

public:
    IntContainer(std::size_t sz, int startVal = 0) :
        container_(sz)
    { std::iota(container_.begin(), container_.end(), startVal); }

public:
    int& at(std::size_t idx) override {
        return container_.at(idx);
    }

    void add(int x) override { 
        container_.push_back(x);
    }

    std::size_t size() const noexcept override {
        return container_.size();
    }
};

class IntContainerProxy : public IIntContainer {
    std::unique_ptr<IntContainer> intContainer_;
    std::size_t sz_;
    int startVal_;

    void createObject_() {
        printStatus_("createObject_()");
        intContainer_.reset(
            new IntContainer(sz_, startVal_));
    }

    void printStatus_(const std::string& op) const {
        std::cout << op << " :";
        if (intContainer_)
            std::cout << "The real object has been created.\n";
        else 
            std::cout << "The actual object has not been created yet\n"; 
    }

public:
    IntContainerProxy(std::size_t sz, int startVal = 0) :
        sz_(sz)
        , startVal_(startVal)
    {}

public:
    int& at(std::size_t idx) override {
        if (!intContainer_) createObject_();
        printStatus_("at()");
        return intContainer_->at(idx);
    }

    void add(int x) override { 
        if (!intContainer_) createObject_();
        printStatus_("add()");
        return intContainer_->add(x);
    }

    std::size_t size() const noexcept override {
        printStatus_("size()");
        if (intContainer_) 
            return intContainer_->size();
        return sz_;
    }
};

int main() {
    std::unique_ptr<IIntContainer> intCont(
        new IntContainerProxy(10, 10));
    
    std::cout << intCont->size() << '\n';
    auto sz = intCont->size();
    for (std::size_t i = 0; i < sz; ++i) {
        std::cout << intCont->at(i) << '\n';
    }

    intCont->add(20);
    std::cout << intCont->size() << '\n';
}  
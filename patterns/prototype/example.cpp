#include <iostream>
#include <memory>
#include <string>

class Prototype {
public:
    virtual std::unique_ptr<Prototype> clone() const = 0;
    virtual void print() const = 0; 
    virtual ~Prototype() {}
};

class ConcretePrototype1 : public Prototype {
    int data_;

public:
    ConcretePrototype1(int data = 0) : data_(data) {}
    std::unique_ptr<Prototype> clone() const override {
        return std::make_unique<ConcretePrototype1>(*this);
    }
    void print() const override {
        std::cout << data_ << '\n';
    }
};

class ConcretePrototype2 : public Prototype {
    std::string data_;
public:
    ConcretePrototype2(const std::string data = "") : data_(std::move(data)) {}
    std::unique_ptr<Prototype> clone() const override {
        return std::make_unique<ConcretePrototype2>(*this);
    }
    void print() const override {
        std::cout << data_ << '\n';
    }
};


class Client {
    std::unique_ptr<Prototype> prototype_;

public:
    Client(std::unique_ptr<Prototype> prototype) :
        prototype_(std::move(prototype))
    {}

    void usePrototype() {
        auto clone = prototype_->clone();
        clone->print();
    }
};


int main() {
    Client c1(std::make_unique<ConcretePrototype1>(5));
    Client c2(std::make_unique<ConcretePrototype2>("ConcretePrototype2"));
    c1.usePrototype();
    c2.usePrototype();
}
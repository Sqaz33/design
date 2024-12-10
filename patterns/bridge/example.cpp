/**
 * @file example.cpp
 * @brief пример паттерна мост.  
 */

#include <iostream>
#include <memory>

class Implementator {
public:
    virtual int implementatorInterface(int) = 0;
    virtual ~Implementator() {}
};

class ConcreteImplementatorA : public Implementator {
public:
    int implementatorInterface(int x) override {
        return x + 1;
    }
};

class ConcreteImplementatorB : public Implementator {
public:
    int implementatorInterface(int x) override {
        return x * x;
    }
};


class ImpFactory {
public:
    virtual ~ImpFactory() {}
    virtual std::unique_ptr<Implementator> createImplementator() = 0;
};

class ImpAFactory : public ImpFactory {
public:
    std::unique_ptr<Implementator> createImplementator() override {
        return std::move(std::make_unique<ConcreteImplementatorA>());
    }
};

class ImpBFactory : public ImpFactory {
public:
    std::unique_ptr<Implementator> createImplementator() override {
        return std::move(std::make_unique<ConcreteImplementatorB>());
    }
};


class Abstraction {
    std::unique_ptr<Implementator> imp_ = nullptr;
public:
    Abstraction(std::shared_ptr<ImpFactory> factory) :
        imp_(factory->createImplementator()) 
    {}

    virtual ~Abstraction() {}

    int abstractionInterface(int x) {
        // do math
        return imp_->implementatorInterface(x);
    }
};

class RefinedAbstraction : public Abstraction {
public:
    RefinedAbstraction(std::shared_ptr<ImpFactory> factory) :
        Abstraction(factory)
    {}  

    int redefinedInterface(int x) {
        return abstractionInterface(x) + 1;
    }
};


int main() { 
    auto factoryA = std::make_shared<ImpAFactory>();
    auto factoryB = std::make_shared<ImpBFactory>();

    Abstraction A(factoryA);
    Abstraction B(factoryB);

    std::cout << A.abstractionInterface(2) << '\n'
              << B.abstractionInterface(2) << '\n';

}
/**
 * @file example.cpp
 * @brief пример паттерна абстрактная фабрика.
 */

#include <iostream>
#include <memory>
#include <string>

class AbstractProductA {
public:
    ~AbstractProductA() { }
    virtual int getVal() = 0;
};

class ConcreteProductA1 : public AbstractProductA {
public:
    int getVal() override {
        return 1;
    }
};

class ConcreteProductA2 : public AbstractProductA {
public:
    int getVal() override {
        return 2;
    }
};

class AbstractProductB {
public:
    ~AbstractProductB() { }
    virtual const char* getStr() = 0;
};

class ConcreteProductB1 : public AbstractProductB {
public:
    const char* getStr() override {
        return "B1";
    }
};

class ConcreteProductB2 : public AbstractProductB {
public:
    const char* getStr() override {
        return "B2";
    }
};


class AbstractFactory {
public:
    ~AbstractFactory() { }
    virtual std::unique_ptr<AbstractProductA> createA() = 0;
    virtual std::unique_ptr<AbstractProductB> createB() = 0;

};

class ConcreteFactoryA : public AbstractFactory {
public:
    std::unique_ptr<AbstractProductA> createA() override {
        return std::move(std::make_unique<ConcreteProductA1>());
    }
    std::unique_ptr<AbstractProductB> createB() override {
        return std::move(std::make_unique<ConcreteProductB1>());
    }
};

class ConcreteFactoryB : public AbstractFactory {
public:
    std::unique_ptr<AbstractProductA> createA() override {
        return std::move(std::make_unique<ConcreteProductA2>());
    }
    std::unique_ptr<AbstractProductB> createB() override {
        return std::move(std::make_unique<ConcreteProductB2>());
    }
};

int main() {
    std::unique_ptr<AbstractFactory> facA = std::make_unique<ConcreteFactoryA>();
    std::unique_ptr<AbstractFactory> facB = std::make_unique<ConcreteFactoryB>();

    auto productA1 = facA->createA();
    auto productA2 = facB->createA();
    std::cout << "val A1: " << productA1->getVal() << '\n'
              << "val A2: " << productA2->getVal() << '\n'; 

    auto productB1 = facA->createB();
    auto productB2 = facB->createB();
    std::cout << "str B1: " << productB1->getStr() << '\n'
              << "str B2: " << productB2->getStr() << '\n'; 
}

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

class ConcreteProductA2 : public AbstractProductA {/**
 * @file example.cpp
 * @brief пример паттерна абстрактная фабричный метод.
 */

#include <iostream>
#include <memory>
#include <string>


class Product {
public:
    virtual ~Product() {}
    virtual void productInterface() = 0;
};

class ConcreteProductA : public Product {
public:
    void productInterface() override {
        std::cout << "cout from A\n"; 
    }
};

class ConcreteProductB : public Product  {
public:
    void productInterface() override {
        std::cout << "cout from B\n"; 
    }
};

class ConcreteProductD : public Product  {
public:
    void productInterface() override {
        std::cout << "cout from B\n"; 
    }
};



class Creator {
public:
    virtual ~Creator() {}
    virtual std::unique_ptr<Product> createProduct() 
#ifndef CONCRETE_CREATOR
    = 0;
#else 
    { return std::move(std::make_unique<ConcreteProductD>()); }
#endif
};

class ConcreteCreatorA : public Creator {
public:
    std::unique_ptr<Product> createProduct() override {
        return std::move(std::make_unique<ConcreteProductA>());
    }
};

class ConcreteCreatorB : public Creator {
public:
    std::unique_ptr<Product> createProduct() override {
        return std::move(std::make_unique<ConcreteProductB>());
    }
};



int main() {
    std::unique_ptr<Creator> creator = std::make_unique<ConcreteCreatorA>();

    std::unique_ptr<Product> product = creator->createProduct(); // product A
    product->productInterface();
    
    
    creator = std::make_unique<ConcreteCreatorB>();

    product = creator->createProduct(); // product B
    product->productInterface();   

#ifdef CONCRETE_CREATOR
    std::unique_ptr<Creator> creator = std::make_unique<Creator>();
    product = creator->createProduct(); // default product
    product->productInterface();   
#endif
}


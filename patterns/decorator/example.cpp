/**
 * @file example.cpp
 * @brief пример паттерна декоратор.
 */

#include <iostream>
#include <memory>
#include <string>

class Component {
public:
    // without state
    virtual int componentInterface(int a, int b) = 0;
    virtual ~Component() {}; 
};


class ConcreteComponent : public Component {
public:
    int componentInterface(int a, int b) override {
        return a + b;
    }
};


class Decorator : public Component {
public:
    Decorator(std::shared_ptr<Component> comp) : comp_(comp) {}
    int componentInterface(int a, int b) override {
        return comp_->componentInterface(a, b);
    }

private:
    std::shared_ptr<Component> comp_;
};


class ConcreteDecoratorA : public Decorator {
public:
    ConcreteDecoratorA(std::shared_ptr<Component> comp) : Decorator(comp) { }

    int componentInterface(int a, int b) override {
        auto res = Decorator::componentInterface(a, b);
        addedBehavior(a, b);
        return res;
    }

private:
    void addedBehavior(int a, int b) {
        std::cout << "added cout: " << a + b << '\n';
    }
};

class ConcreteDecoratorB : public Decorator {
public:
    ConcreteDecoratorB(std::shared_ptr<Component> comp) : Decorator(comp) { }

    int componentInterface(int a, int b) override {
        addedBehavior(a, b);
        auto res = Decorator::componentInterface(a, b);
        return res;
    }

private:
    void addedBehavior(int& a, int& b) { ++a; ++b; }
};


int main() {
    auto compPtr = std::make_shared<ConcreteComponent>();


    ConcreteDecoratorA decoratorA(compPtr);
    auto resA = decoratorA.componentInterface(2, 3);
    std::cout << "res for decorator A: " << resA << '\n';


    std::cout << std::string(30, '-') << '\n';


    ConcreteDecoratorB decoratorB(compPtr);
    auto resB = decoratorB.componentInterface(2, 3);
    std::cout << "res for decorator B: " << resB << '\n';


    std::cout << std::string(30, '-') << '\n';


    //decorator nesting
    auto decB = std::make_shared<ConcreteDecoratorB>(compPtr);
    ConcreteDecoratorA decoratorAnB(decB); 
    auto resAnB = decoratorAnB.componentInterface(2, 3);
    std::cout << "res for decorator A and B: " << resAnB << '\n';
}

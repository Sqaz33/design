/**
 * @file example.cpp
 * @brief пример паттерна стратегия.
 */

#include <iostream>
#include <memory>

class Strategy {
public:
    virtual void algInterface() = 0; 
    virtual ~Strategy() {}
};

class ConcreateStrategyA : public Strategy {
public:
    void algInterface() override {
        std::cout << "alg A\n";
    }
};

class ConcreateStrategyB : public Strategy {
public:
    void algInterface() override {
        std::cout << "alg B\n";
    }
};

class ConcreateStrategyC : public Strategy {
public:
    void algInterface() override {
        std::cout << "alg B\n";
    }
};

class Context {
    // mb state
    std::unique_ptr<Strategy> strat_;

public:
    Context(std::unique_ptr<Strategy> strategy) : strat_(std::move(strategy)) {}
    void contextInteface() { strat_->algInterface(); }
};  

int main() {
    Context c(std::move(std::make_unique<ConcreateStrategyB>()));
    c.contextInteface();
}
/**
 * @file example.cpp
 * @brief пример паттерна мост.  
 */

#include <iostream>
#include <vector>
#include <stdexcept>
#include <memory>

class Float;
class Integer;

class NumberVisitor {
public:
    virtual void visitFloat(const Float& f) = 0;
    virtual void visitInteger(const Integer& i) = 0;
};

class Number {
public:
    virtual void accept(NumberVisitor& visitor) const = 0;
};

class Float final : public Number {
    float val_ = 0.0f;
public:
    Float(float val) : val_(val) {}
    Float(const Float& f) : val_(f.val_) {}
    float val() const { return val_; }
    void accept(NumberVisitor& visitor) const override { 
        visitor.visitFloat(*this); 
    }
};

class Integer final : public Number {
    int val_ = 0;
public:
    Integer(int val) : val_(val) {}
    Integer(const Integer& i) : val_(i.val_) {}
    int val() const { return val_; }
    void accept(NumberVisitor& visitor) const override {
        visitor.visitInteger(*this);
    }
};

class FloatVisitor final : public NumberVisitor {
    float sum_ = 0;

public:
    void visitFloat(const Float& f) override {
        sum_ += f.val(); 
    }
    void visitInteger(const Integer& i) override {/*...*/}
    float sum() const { return sum_; }
}; 

class IntegerVisitor final : public NumberVisitor {
    int sum_ = 0;

public:
    void visitFloat(const Float& f) override { }
    void visitInteger(const Integer& i) override {
        sum_ += i.val();
    }
    int sum() const { return sum_; }
};

class NumberStructure {
    std::vector<std::shared_ptr<Number>> numbers_;

public:
    void push(std::shared_ptr<Number> n) { numbers_.push_back(n); }
    void accept(NumberVisitor& visitor) {
        for (auto n : numbers_) {
            n->accept(visitor);
        }
    }
};

int main() {
    NumberStructure ns;

    auto f1 = std::make_shared<Float>(1.f);
    auto f2 = std::make_shared<Float>(2.f);
    ns.push(f1); 
    ns.push(f2);

    auto i1 = std::make_shared<Integer>(3);
    auto i2 = std::make_shared<Integer>(4);
    ns.push(i1); 
    ns.push(i2);

    FloatVisitor fv;
    ns.accept(fv);

    IntegerVisitor iv;
    ns.accept(iv);

    std::cout << "res for Float: "   << fv.sum() << '\n'
              << "res for Integer: " << iv.sum() << '\n';
}
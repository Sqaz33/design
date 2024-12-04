/**
 * @file example.cpp
 * @brief пример паттерна компоновщик.  
 */

#include <algorithm>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>

using Watt = double;
using Currency = double;

// Component
class Equipment : public std::enable_shared_from_this<Equipment> {
public:
    using iterator = std::vector<std::shared_ptr<Equipment>>::iterator; 
    using const_iterator = std::vector<std::shared_ptr<Equipment>>::const_iterator; 


public:
    const std::string& name() { return name_; }

    virtual Watt power() const = 0;
    virtual Currency netPrice() const = 0;
    virtual Currency discountPrice() const = 0;

    virtual void add(std::shared_ptr<Equipment>);   
    virtual void remove(std::shared_ptr<Equipment>);

    virtual void setMounting(std::weak_ptr<Equipment> mounting) {
        mounting_ = mounting;
    }
    virtual void resetMounting() {
        mounting_.reset();
    }

    auto self() {
        return shared_from_this();
    }

    virtual iterator begin();
    virtual iterator end();
    virtual const_iterator begin() const;
    virtual const_iterator end() const;

    virtual ~Equipment() { } 


protected:
    Equipment(const std::string& name) : 
        name_(name) 
    {}

    std::weak_ptr<Equipment> mounting_;

private:
    std::string name_;
};

Equipment::iterator Equipment::begin() { 
    throw std::logic_error("Call begin() on a non-composite.");
    return Equipment::iterator(); 
}

Equipment::iterator Equipment::end() { 
    throw std::logic_error("Call end() on a non-composite.");
    return Equipment::iterator(); 
}

Equipment::const_iterator Equipment::begin() const { 
    throw std::logic_error("Call cbegin() on a non-composite.");
    return Equipment::iterator(); 
}

Equipment::const_iterator Equipment::end() const { 
    throw std::logic_error("Call cend() on a non-composite.");
    return Equipment::iterator(); 
}


void Equipment::add(std::shared_ptr<Equipment>){
    throw std::logic_error("Call add(....) on a non-composite."); 
}

void Equipment::remove(std::shared_ptr<Equipment>){
    throw std::logic_error("Call remove(....) on a non-composite."); 
}


//Leaf subclass
class FloppyDisk final : public Equipment  {

public:
    FloppyDisk(const std::string& name) : 
        Equipment(name) 
    {}
    
    Watt power() const override { return 1; }
    Currency netPrice() const override { return 2; }
    Currency discountPrice() const override { return 3; }
};


// Composite
class CompositeEquipment : public Equipment {

public:
    void add(std::shared_ptr<Equipment> equip) override {
        equipment_.push_back(equip);
        equip->setMounting(self());
    } 
    void remove(std::shared_ptr<Equipment> equip) override {
        equipment_.erase(
            std::find(begin(), end(), equip)
        );
        equip->resetMounting();
    }

    iterator begin() override {
        return equipment_.begin();
    }

    iterator end() override {
        return equipment_.end();    
    }

    const_iterator begin() const override {
        return equipment_.cbegin();
    }

    const_iterator end() const override {
        return equipment_.cend();    
    }


protected:
    CompositeEquipment(const std::string& name) : 
        Equipment(name) 
    {}

private:
    std::vector<std::shared_ptr<Equipment>> equipment_; 
};


// Composite subclass
class Chassis final : public CompositeEquipment {

public:
    Chassis(const std::string& name) :
        CompositeEquipment(name)
    {}

    Watt power() const override {
        Watt res = 0;
        for (const auto& equip : *this) {
            res += equip->power();
        }
        return res;
    }

    Currency netPrice() const override {
        Currency res = 0;
        for (const auto& equip : *this) {
            res += equip->netPrice();
        }
        return res;
    }

    Currency discountPrice() const override {
        Currency res = 0;
        for (const auto& equip : *this) {
            res += equip->discountPrice();
        }
        return res;
    }
};


int main() {
    auto chassis = std::make_shared<Chassis>("PC Chassis");

    auto disk1 = std::make_shared<FloppyDisk>("PC Disk No 1");
    auto disk2 = std::make_shared<FloppyDisk>("PC Disk No 2");

    chassis->add(disk1);
    chassis->add(disk2);

    std::cout << 
        "Full power: " << chassis->power() << '\n' <<
        "Full net price: " << chassis->netPrice() << '\n' <<
        "Full discount price: " << chassis->discountPrice() << '\n';


    try {
        disk1->begin();
    } catch (const std::exception& e) {
        std::cout << e.what() << '\n';
        return 1;
    }

    return 0;
}
#include <format>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

class Memento;

class Originator {
    int state_ = 0;

public:
    void setState(int s) { state_ = s; }
    int state() const { return state_; } 
    std::unique_ptr<Memento> createMemento();
    void setMemento(std::unique_ptr<Memento> m);
};

class Memento {
    friend class Originator;
    int state_;

private:
    Memento(int state) : state_(state) {}

    int getState() {
        return state_;
    }
};

std::unique_ptr<Memento> Originator::createMemento() {
    return std::unique_ptr<Memento>(new Memento{state_});
}

void Originator::setMemento(std::unique_ptr<Memento> m) {
    state_ = m->getState();
}

// Caretaker
int main() {
    Originator o;

    auto formatState = [] (int state) {
        return std::format(
            "Originator state now: {}\n", state);
    };

    std::cout << formatState(o.state());
    auto m = o.createMemento();
    o.setState(5);
    std::cout << formatState(o.state());
    o.setMemento(std::move(m));
    std::cout << formatState(o.state());
}


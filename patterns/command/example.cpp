/**
 * @file example.cpp
 * @brief пример паттерна команда 
 */

#include <cstddef>
#include <iostream>
#include <memory>
#include <string>

#include "../../utils/print.hpp"
#include "../../utils/sliding_top_stack.hpp"


class Receiver {
    int val_ = 0;

public:
    int inc() { 
        ++val_; 
        std::cout << val_ << '\n'; 
        return val_;
    }

    int dec() { 
        --val_; 
        std::cout << val_ << '\n'; 
        return val_;
    }

    int val() {
        return val_;
    }
};


class Command  {
    std::shared_ptr<Receiver> receiver_;

protected:
    auto receiver() { return receiver_; }

    Command(Command& cmd) : receiver_(cmd.receiver_) {}

    Command(std::shared_ptr<Receiver> receiver) :
        receiver_(receiver)
    {}

public:
    virtual std::shared_ptr<Command> copy() = 0;

    virtual ~Command() {}
    
    virtual void execute() = 0;

    virtual void unexecute() = 0;

};

class ConcreteCommand : public Command, 
                        std::enable_shared_from_this<ConcreteCommand>
{

public:
    ConcreteCommand(std::shared_ptr<Receiver> receiver) :
        Command(receiver)
    {}

    std::shared_ptr<Command> copy() override {
        return std::shared_ptr<Command>(new ConcreteCommand(*this));
    }
 
    void execute() override { 
        std::cout << receiver()->val() <<  "->" 
                  << receiver()->inc() << '\n';
    }

    void unexecute() override {
        int cur = receiver()->val();
        std::cout << receiver()->dec() << "<-"
                  << cur << '\n';
    }
    
};


class Invoker {
    std::shared_ptr<Command> curCmd_;
    sliding_top_stack::SlidingTopStack<std::shared_ptr<Command>> slidingStack_;
public:
    Invoker(std::shared_ptr<Command> cmd) :
        curCmd_(cmd)
    {}

    void action() { 
        int top = slidingStack_.topPos();
        if (top >= 0 && top < slidingStack_.size()) {
            curCmd_ = slidingStack_.top();
        }
        curCmd_->execute();
        slidingStack_.push(curCmd_->copy());
    }

    void redo() {
        if (slidingStack_.onRealTop()) { return; }
        slidingStack_.top()->execute();
        slidingStack_.toRight();
    }

    void undo() {
        if (slidingStack_.topPos() < 0) { return; }
        slidingStack_.top()->unexecute();
        slidingStack_.toLeft(); 
    }
};



int main() {
    auto receiver = std::make_shared<Receiver>();
    std::shared_ptr<Command> cmd = std::make_shared<ConcreteCommand>(receiver);
    Invoker inv(cmd);

    inv.action();
    inv.action();

    std::cout << std::string(50, '-') << '\n';

    inv.undo();
    inv.undo();

    std::cout << std::string(50, '-') << '\n';

    inv.redo();
    inv.redo();

    std::cout << std::string(50, '-') << '\n';

    inv.undo();
    inv.action();
    inv.action();
}

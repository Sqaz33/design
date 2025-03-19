#include <iostream>
#include <memory>
#include <string>

class IMediator {
public:
    virtual bool input(const std::string& in) = 0;
    virtual ~IMediator() {};
};

class Colleague1 final {
    std::shared_ptr<IMediator> mediator_;

public:
    Colleague1(std::shared_ptr<IMediator> mediator) :
        mediator_(mediator)
    {}

    void readInput(std::istream& in) {
        if (in) {
            std::string input;
            in >> input;
            bool acc = false;
            if (input.length())
                acc = mediator_->input(input); 
            if (!acc) 
                std::cout << "But what about saying hello?\n";
        }
    }
};

class Colleague2 final {
public:
    bool handleInput(const std::string& in) {
        if (in == "Hello") {
            std::cout << "Hi\n";
            return true;
        }
        return false;
    } 
};

class ConcreteMediator : public IMediator {
    std::shared_ptr<Colleague2> col2_;
public:
    ConcreteMediator(std::shared_ptr<Colleague2> col2) :
        col2_(col2)
    {}

    bool input(const std::string& in) override {
        return col2_->handleInput(in);
    }
};

int main() {
    auto col2 = std::make_shared<Colleague2>();
    auto mediator = std::make_shared<ConcreteMediator>(col2);
    Colleague1 col1(mediator);
    col1.readInput(std::cin);
}
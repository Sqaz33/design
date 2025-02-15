#include <algorithm>
#include <iostream>
#include <memory>
#include <string>

namespace {

    bool isWord(const std::string& str) {
        return std::all_of(
            str.begin(),
            str.end(),
            [] (char c) { return std::isalpha(c); }
        );
    }
    
    bool isNumber(const std::string& str) {
        return std::all_of(
            str.begin(),
            str.end(),
            [] (char c) { return std::isdigit(c); }
        );
    }
    
} // namespace

class InputHandler {
public:
    InputHandler() = default;
    InputHandler(std::shared_ptr<InputHandler> next) :
        next_(next)
    {}
    
    virtual ~InputHandler() {}

public:
    virtual void handleInput(const std::string& data) {
        if (next_.expired()) return;
        next_.lock()->handleInput(data);
    }

private:
    std::weak_ptr<InputHandler> next_;
};

class IntegerHandler : public InputHandler {
public:
    IntegerHandler() = default;
    IntegerHandler(std::shared_ptr<InputHandler> next) :
        InputHandler(next) 
    {}

public:
    void handleInput(const std::string& data) override {
        if (!isNumber(data)) {
            InputHandler::handleInput(data);
            return;
        }            

        std::cout << "Number: " << data << '\n';
    }
};

class WordHandler : public InputHandler {
public:
    WordHandler() = default;
    WordHandler(std::shared_ptr<InputHandler> next) :
        InputHandler(next) 
    {}

public:
    void handleInput(const std::string& data) override {
        if (!isWord(data)) {
            InputHandler::handleInput(data);
            return;
        }
        std::cout << "Word: " << data << '\n';
    }
};


int main() {
    auto wordHandler = std::make_shared<WordHandler>();
    auto integerHandler = std::make_shared<IntegerHandler>(wordHandler);
    std::string in;
    while (std::cin >> in) 
        integerHandler->handleInput(in);
}
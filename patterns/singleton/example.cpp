#include <memory>
#include <iostream>
#include <string>

class PrintSingleton final {
    PrintSingleton() = default;
    PrintSingleton(PrintSingleton&) = delete;
    PrintSingleton(PrintSingleton&&) = delete;
    PrintSingleton& operator=(PrintSingleton&) = delete; 
    PrintSingleton& operator=(PrintSingleton&&) = delete; 
    
    std::string data_ = "Hello World!";

public:
    static auto& instance() {
        static PrintSingleton instance;
        return instance;
    }

    void print() const {
        std::cout << data_ << std::endl;
    }
}; 

int main() {
    auto&& singleton = PrintSingleton::instance();
    singleton.print();
}

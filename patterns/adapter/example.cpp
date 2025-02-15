#include <iostream>
#include <memory>
#include <string>
#include <cstddef>


class Shape { // Target
public:
    virtual void draw() const = 0;
    virtual std::size_t size() = 0;
    virtual ~Shape() {} 
};


class TextView { // Adatptee
public:
    TextView(std::string txt) : txt_(txt) {}
    void display() const {
        std::cout << txt_ << std::endl;;
    }
    decltype(auto) text() const { return txt_; }
private:
    std::string txt_;
};


// ########################################################################
class TextShape_ClassAdapter : public Shape, private TextView { // Adapter
public:
    TextShape_ClassAdapter(std::string txt) :
        TextView(txt)
    {}

    void draw() const override {
        TextView::display();
    }

    std::size_t size() { 
        return TextView::text().size(); 
    }
};
// ########################################################################

// ########################################################################
class TextShape_ObjectAdapter : public Shape { // Adapter
public:
    TextShape_ObjectAdapter(std::unique_ptr<TextView> textView) :
        textView_(std::move(textView))
    {}

    void draw() const override {
        textView_->display();
    }

    std::size_t size() { 
        return textView_->text().size(); 
    }

private:
    std::unique_ptr<TextView> textView_;
};
// ########################################################################

class Client { // Client
public:
    Client (std::shared_ptr<Shape> shape) :
        shape_(shape)
    {}

    void drawSelf() const {
        shape_->draw();
    }

private:
    std::shared_ptr<Shape> shape_;
};


int main() {
    Client client1(std::make_shared<TextShape_ClassAdapter>("Hi from Class Adapter"));

    auto textView = std::make_unique<TextView>("Hi from Object Adapter");
    Client client2(std::make_shared<TextShape_ObjectAdapter>(std::move(textView)));

    client1.drawSelf();
    client2.drawSelf();
}
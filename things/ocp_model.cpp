#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <initializer_list>

// by Tilir


using Screen = std::ostream;


struct Vector3D {
    int x, y, z;
};

struct Polygon3D {
    std::vector<Vector3D> vs;
    Polygon3D(std::initializer_list<Vector3D> il) : vs(il) {}
};

// просто определить определять функцию для типа, который нужно отрисовать
void draw(Vector3D v, Screen& out, size_t position) {
    out << std::string(position, ' ') << "(" << v.x << ", " << v.y << ", " << v.z 
        << ")\n";
}

void draw(const Polygon3D& p, Screen& out, size_t position) {
    out << std::string(position, ' ') << "</polygon>\n";
    for (auto v : p.vs) 
        ::draw(v, out, position + 2);
    out << std::string(position, ' ') << "</polygon>\n";
}

void draw(int x, Screen& out, size_t position) {
    out << std::string(position, ' ') << "int: " << x << '\n';
}

class Drawable {
    // наследование - часть реализации
    struct IDrawable {
        virtual ~IDrawable() { }
        virtual std::unique_ptr<IDrawable> copy_() const = 0;
        virtual void draw_(Screen&, size_t) const = 0;
    };

    template <class T>
    struct DrawableObject final : IDrawable {
        T data_;
        DrawableObject(T x) : data_(std::move(x)) {}
        std::unique_ptr<IDrawable> copy_() const override {
            return std::make_unique<DrawableObject>(*this);
        }
        void draw_(Screen& out, size_t position) const override;
    };

    std::unique_ptr<IDrawable> self_;

public:
    template <class T>
    Drawable(T x) : 
        self_(std::make_unique<DrawableObject<T>>(std::move(x))) 
    {}        

    // cp ctor, mv ctor and assignment
public:
    Drawable(const Drawable& oth) : 
        self_(oth.self_->copy_())  
    {} 

    Drawable(Drawable&& oth) :
        self_(std::move(oth.self_))
    {}

    Drawable& operator=(const Drawable& rhs) {
        self_ = rhs.self_->copy_();
        return *this;
    }
    
    Drawable& operator=(Drawable&& rhs) {
        self_ = std::move(rhs.self_);
        return *this;
    }

public:
    friend void draw(const Drawable& x, Screen& out, size_t position) {
        x.self_->draw_(out, position);
    }
};

using Model = std::vector<Drawable>;

void draw(const Model& x, Screen& out, size_t position) {
    out << std::string(position, ' ') << "<world>\n";
    for (const auto& d : x) {
        draw(d, out, position + 2);
    }
    out << std::string(position, ' ') << "</world>\n";
} 

template <class T>
void Drawable::DrawableObject<T>::draw_(Screen& out, size_t position) const  {
    ::draw(data_, out, position);
}

int main() {
    Model document;
    document.push_back(0);
    document.push_back(Polygon3D{ {2, 1, 6}, {-3, 7, 4} });
    document.push_back(document);
    document.push_back(Vector3D{1, 2, 3});
    draw(document, std::cout, 0);
}


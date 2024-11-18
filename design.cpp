// полиморфная функция - функция, поведение которой зависит от типа
// аргумента, переданного ей. 
// Перегрузки функции - полиморфная функция.

// Шаблонная функция может не быть полиморфной, если шаблонный тип не является частью сигнатуры. 

// virtual функция всегда полиморвна из-за неявного аргумента this.


//-------------------------------------------
// проектирование - моделирование между типами.





//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------Отношения между классами------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------

//-------------------------------------------
// ассоциация 

// Сущности  каким-то образом связанны.

/* 

    Ассоциация в объектно-ориентированном программировании представляет собой
    связь между двумя классами, когда один класс использует другой, но при этом
    ни один из них не владеет другим. 

*/

class Book;

class Professor {
    ....
    std::vectro<Book*> books;
};

class Book {
    ....

    Author* author;
};


//-------------------------------------------
// генерализация  
// онтношение частное/общее, открытое наследование

// мнемоническое правило - широкий конец к более широкому 
// Derived ----> Base

class IMatrix {
    virtual ~IMatrix() {}
}; 

class Matrix : public IMatrix { .... };

class LazyMatrix : public IMatrix { .... };


//-------------------------------------------
// Композиция
// B является частью A.
// А и B связанны временнем жизни (умирает A - умирает B).

//* стрелка к контейнеру

class File; 

class Folder {
    std::vector<File> content; 
};
// Файл принадлежит только одной папке
// и связан с ней временем жизни.

// Файл тут - Композит.


//-------------------------------------------
// Аггрегация
// Сущность A владеет сущностью B, но у B могут быть еще владельцы. 

class Segment; // Отрезок может быть частью многих треугольников.

class Triangle {
    ....
    stt::vector<Segment*> segments; 
};

Segment s1, s2, s3; // Отрезок может жить дольше, чем какой-то треугольник.
// отрезок тут - Агрегат.

Triangle t1(s1, s2, s3);
Triangle t2(s1, s2, s3);




//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------SOLID-------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------

// хороший проект - легко изменяем.

// SPR - single responcibility principle
// каждый контекст должен иметь одну ответственность.

// OCP - open-close principle
// каждый контекст должнен быть закрыть для изменения и открыт для расширения.

// LSP - Liskov substitution principle
// частный класс должен иметь возможность свободно заменять общий.

// ISP - interface separation principle
// тип не должен зависеть от тех интерфейсов, которые он не использует.

// DIP - dependency inversion principle
// высокоуровневые классы не должны зависеть от низкоуровневых.



//-------------------------------------------
// SRP

class Screen;

class ByteStream;

class Quternion { Vector3D* v_; };

// Класс должен иметь только одну причину для изменений (Robert C. Martin).

class Polygon3D {
    std::vector<Vector3D> vs_; 

public:
    void translate(const Vector3D& t); // если поменяется геометрия, то придестя поменять 
    void rotate(const Quternion& q);   // класс Polygon3D, но это ок.

    void draw(Screen& s);             // если измениться Screen 
    void serialize(ByteStream& bs);   // или ByteStream 
                                      // придется менять Polygon3D - это плохо.
}; // поэтому нужно вынести draw и serialize

//                  |
//                  |
//                  |
//                  |
//                  ↓

class Polygon3D {
    std::vector<Vector3D> vs_; 

public:
    void translate(const Vector3D& t)
    void rotate(const Quternion& q); 

    Iterator begin();    // внешниие функции могут обратится к элементам класса 
    Iterator end();      // но не к его состоянию             
};  // теперь единственная обязанность класса - геометрия


// Модуль - внутри сильно связан, снаружи - слабо связан.


//-------------------------------------------
// OCP


class IFigure {
    virtual Shape shape() = 0; 

    enum class Shape {
        VECTOR, POlYGON, CIRCLE
    };

};

class Vector3D : public IFigure {
    Shape shape() override {
        return IFigure::Shape::VECTOR;
    }   
}

class Polygon3D : public IFigure {
    Shape shape() override {
        return IFigure::Shape::POlYGON;
    }
}

class IScreen {
    virtual void draw(const IFigure& f) = 0;
};

class Screen : IFigure {
    std::vector<IFigure*> figures_;

    void drawVector(const Vector3D& v);
    void drawPolygon(const Polygon3D& p);
    void draw(const IFigure& f) { figures_.push_back(&f); }
    void render() { // нужно модифицировать метод, чтобы напечатать Circle3D
        for (auto f : figures_) {
            switch (f->shape()) {
                case IFigure::Shape::VECTOR:
                    drawPolygon(*static_cast<const Vector3D*>(f));
                    break;
                case IFigure::Shape::POlYGON:
                    drawPolygon(*static_cast<const Polygon3D*>(f));
                    break;
            }
        }
    }

}; 
// класс открыт для модификации, но закрыт для расширения.
// нарушение OPC.
// при расширении класса, не меняется код класса (например наследование).

//                  |
//                  |
//                  |
//                  |
//                  ↓


// решение с соблюдение OPC и SRP смотри в things/ocp_model.cpp



//-------------------------------------------
// LSP - is a

// нарушиние LSP 
bool instersect(Polygon2D& l, Polygon2D& r); // 2D intersection 

class Polygon2D {
    std::vector<double> xcoord, ycoord;
    ....
};

class Polygon3D : public Polygon2D { // Polygon3D is a Polygon2D
    std::vector<double> zcoord;
    ....
}; // 3D полигон можно использовать во всех контекстах, где можно использовать и 2D.
// здесь по факту - это некоректно -> нарушение LSP.



//-------------------------------------------
// ISP 

// нарушение ISP
struct IWorker {
    virtual void work() = 0;
    virtual void eat() = 0;
};

class Robot : public IWorker {
    void work() override { ... }
    void eat() override { 
        // do nothing or abort

        // такая реализация интерфейса сигнализирует о нарушении ISP. 
    }
};

class Manager {
    IWorker* subdue;

public:
    void manage() {
        subdue->work();
    }
}; 
// Менеджер зависит от интерфейса eat, но не использует его.
// В итоге робот должен определить eat.

//                  |
//                  |
//                  |
//                  |
//                  ↓

// решение проблемы 
struct IWorkable {
    virtual void work() = 0;
};

class Robot : public IWorkable {
    void work() override;
};
// Лучше писать небольшие self-contained интерфейсы. 


//-------------------------------------------
// DIP

// Низкоуровневые и высокоуровневые классы должны зависить от абстракций. 
// если нужна зависимость - то она должна быть между абстрактными классами.

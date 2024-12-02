/**
 * @file glyph.hpp
 * @brief 
 * Абстрактный класс Glyph (глиф) определяется для всех объектов, которые
 * могут присутствовать в структуре документа1. Его подклассы определяют как при
 * митивные графические элементы (скажем, символы и изображения), так и струк
 * турные элементы (строки и колонки). 
 */

#ifndef GLYPH_HPP
#define GLYPH_HPP

struct Window;
struct Point;
struct Rect;

namespace glyph {

class Glyph {
public:
    // внешнее представление
    virtual void draw(Window*) = 0; // нарисовать себя на окне.
    virtual void bounds(Rect&) = 0; // вернуть свои размеры.

    // обнаружение точки воздействия 
    virtual bool Intersects(const Point&) = 0; // находится ли точка в пределах глифа.

    // структура
    virtual void insert(Glyph*, int) = 0; // вставить в себя глиф-потомок.
    virtual void remove(Glyph*) = 0; // удалить из себя глиф-потомок. 
    virtual Glyph* child(int) = 0; // вернуть из себя глифа-потомка по его позиции.
    virtual Glyph* parent() = 0; // вернуть своего глифа-родителя.
};

} // namespace glyph

#endif // GLYPH_HPP
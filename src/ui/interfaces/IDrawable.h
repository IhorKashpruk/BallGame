#ifndef TESTC_IDRAWABLE_H
#define TESTC_IDRAWABLE_H

#include "../../utility/primitive_types.h"

class IDrawable {
    typedef int T;
    typedef pt::point<T> Point;
public:
    virtual void draw() = 0;
    virtual void draw(const Point& offset) = 0;
    virtual ~IDrawable() = default;
};

#endif //TESTC_IDRAWABLE_H

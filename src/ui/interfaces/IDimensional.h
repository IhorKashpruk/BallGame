#ifndef TESTC_IDIMENSIONAL_H
#define TESTC_IDIMENSIONAL_H

#include "../../utility/primitive_types.h"

class IDimensional {
    typedef int T;
    typedef pt::point<T> Point;
public:
    virtual bool under(Point&& point) = 0;
    virtual bool under(const Point& point) = 0;
    virtual Point center() const = 0;
    virtual float angle() const = 0;
    virtual ~IDimensional() = default;
};

#endif //TESTC_IDIMENSIONAL_H

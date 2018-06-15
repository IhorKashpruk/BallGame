#ifndef TESTC_IDIMENSIONAL_H
#define TESTC_IDIMENSIONAL_H

#include "../../utility/primitive_types.h"

class IDimensional {
public:
    virtual bool under(pt::point&& p) = 0;
    virtual bool under(const pt::point& p) = 0;
    virtual bool under(const pt::Circle& circle) const = 0;
    virtual bool under(const pt::Rectangle& rectangle) const = 0;
    virtual bool under(const pt::Polygon& polygon) const = 0;
    virtual pt::point center() const = 0;
    virtual float angle() const = 0;
    virtual ~IDimensional() = default;
};

#endif //TESTC_IDIMENSIONAL_H

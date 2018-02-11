#ifndef TESTC_IRESPONSIBLE_H
#define TESTC_IRESPONSIBLE_H

#include "../../utility/primitive_types.h"

class IResponsible {
    typedef pt::point<int> Point;
public:
    virtual void clickLeftButton(const Point& point) = 0;
    virtual void clickRightButton(const Point& point) = 0;
    virtual void enterKey(const char* key) = 0;
    virtual void mouseMove(const Point& point) = 0;
    virtual ~IResponsible() = default;
};

#endif //TESTC_IRESPONSIBLE_H

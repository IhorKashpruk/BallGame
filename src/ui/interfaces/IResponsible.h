#ifndef TESTC_IRESPONSIBLE_H
#define TESTC_IRESPONSIBLE_H

#include "../../utility/primitive_types.h"

class IResponsible {
public:
    virtual void clickLeftButton(const pt::point& p) = 0;
    virtual void clickRightButton(const pt::point& p) = 0;
    virtual void enterKey(const char* key) = 0;
    virtual void mouseMove(const pt::point& p) = 0;
    virtual ~IResponsible() = default;
};

#endif //TESTC_IRESPONSIBLE_H

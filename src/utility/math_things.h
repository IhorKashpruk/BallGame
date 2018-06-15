#ifndef TESTC_MATH_THINGS_H
#define TESTC_MATH_THINGS_H

#include <cmath>


namespace math_things {

#define ONE_RADIAN (57.295779513f)
#define RADIAN_TO_DEGREES(value) ((value) * ONE_RADIAN)
#define DEGREES_TO_RADIAN(value) ((value) / ONE_RADIAN)

    template <class T>
    inline T normalize(T value) {
        return (std::round(value));
    }
}
#endif //TESTC_MATH_THINGS_H

#ifndef TESTC_MATH_THINGS_H
#define TESTC_MATH_THINGS_H

#include <cmath>


namespace math_things {

#define ONE_RADIAN (57.295779513f)
#define RADIAN_TO_DEGREES(value) ((value) * ONE_RADIAN)
#define DEGREES_TO_RADIAN(value) ((value) / ONE_RADIAN)

    template <class T>
    float convert(float);

    template <>
    float convert<float>(float degrees) {
        return (degrees / ONE_RADIAN);
    }

    template <>
    float convert<int>(float radians) {
        return (radians * ONE_RADIAN);
    }

    template <class T>
    inline T normalize(T value) {
        return (std::round(value));
    }

}
#endif //TESTC_MATH_THINGS_H

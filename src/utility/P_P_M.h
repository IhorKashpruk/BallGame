#ifndef TESTC_P_P_M_H
#define TESTC_P_P_M_H

#include <cmath>

template <int p_p_m>
struct P_P_M {
    static int convert(float meters) {
        return (int)(std::round(meters * (float)p_p_m));
    }

    static float convert(int pixels) {
        return ((float)pixels) / (float)p_p_m;
    }
};

typedef P_P_M<50> P_P_M_50;

#endif //TESTC_P_P_M_H

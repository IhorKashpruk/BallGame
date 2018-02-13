#ifndef TESTC_BOX2D_PROPERTIES_H
#define TESTC_BOX2D_PROPERTIES_H

#include <libs/Box2D/Box2D.h>

namespace box2d_properties {
    constexpr float32 gravity_x = 0.0f;
    constexpr float32 gravity_y = -9.8f;

    constexpr float32 time_step =           1.0f/20.0f; //the length of time passed to simulate (seconds)
    constexpr int32 velocity_iterations =   8;          //how strongly to correct velocity
    constexpr int32 position_iterations =   3;          //how strongly to correct position
}

#endif //TESTC_BOX2D_PROPERTIES_H

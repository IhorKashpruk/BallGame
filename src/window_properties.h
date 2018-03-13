#ifndef TESTC_WINDOW_PROPERTIES_H
#define TESTC_WINDOW_PROPERTIES_H

#include <utility/primitive_types.h>

namespace window {
    constexpr static char* title = (char *const) "Game";
    constexpr static pt::size<int> size {600, 600};
    constexpr static int fps = 60;
}

#endif //TESTC_WINDOW_PROPERTIES_H

#ifndef TESTC_COLORSCHEME_H
#define TESTC_COLORSCHEME_H

#include <SDL2/SDL_pixels.h>
#include <tuple>

struct ColorScheme {
    SDL_Color rim;
    SDL_Color background;
    friend bool operator==(const ColorScheme& lhs, const ColorScheme& rhs) {
        return std::tie(lhs.rim.r, lhs.rim.g, lhs.rim.b, lhs.rim.a,
                        lhs.background.r, lhs.background.g, lhs.background.b, lhs.background.a)
               == std::tie(rhs.rim.r, rhs.rim.g, rhs.rim.b, rhs.rim.a,
                           rhs.background.r, rhs.background.g, rhs.background.b, rhs.background.a);
    }
};

#endif //TESTC_COLORSCHEME_H

#ifndef TESTC_THEME_PROPERTIES_H
#define TESTC_THEME_PROPERTIES_H

#include <SDL2/SDL_pixels.h>
#include <ui/ColorScheme.h>

namespace theme {
    namespace base {
        ColorScheme window =        {{255, 255, 255, 255}, {255, 255, 255, 255}};
        struct {
            const ColorScheme sel = {{0, 0, 0, 255},{255, 255, 255, 255}};
            const ColorScheme clk = {{255, 93, 115, 255},{255, 255, 255, 255}};
            const ColorScheme def = {{124, 122, 122, 255},{255, 255, 255, 255}};
        } all;
        SDL_Color text =        {0, 0, 0, 255};
    }
}

#endif //TESTC_THEME_PROPERTIES_H

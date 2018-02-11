#ifndef TESTC_DRAFTSMEN_H
#define TESTC_DRAFTSMEN_H

#include "utility/primitive_types.h"
#include "theme_properties.h"
#include "window_properties.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL2_framerate.h>
#include <utility/other_things.h>

class Draftsman {
NOW_YOU_ARE_SINGELTON(Draftsman)
public:
    bool init() {
        return initSDL() && createWindowAndRenderer();
    }
    void clearAndSetBaseColor() {
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(
                renderer,
                theme::base::window.background.r,
                theme::base::window.background.g,
                theme::base::window.background.b,
                theme::base::window.background.a
        );
    }
    void draw() {
        SDL_SetRenderDrawColor(
                renderer,
                theme::base::window.background.r,
                theme::base::window.background.g,
                theme::base::window.background.b,
                theme::base::window.background.a
        );
        SDL_RenderPresent(renderer);
        SDL_framerateDelay(&fps_manager);
    }

    inline void draw(const pt::Rectangle<int>& rectangle, const ColorScheme& colorScheme) {

        if(rectangle.angle == 0 || rectangle.angle == 360) {
            rectangleRGBA(renderer,
                          rectangle.center.x - rectangle.size_.w,
                          rectangle.center.y - rectangle.size_.h,
                          rectangle.center.x + rectangle.size_.w,
                          rectangle.center.y + rectangle.size_.h,
                          colorScheme.rim.r,
                          colorScheme.rim.g,
                          colorScheme.rim.b,
                          colorScheme.rim.a
            );
        } else {
            if(rectangle.angle == 90 || rectangle.angle == 270) {
                rectangleRGBA(renderer,
                              rectangle.center.x - rectangle.size_.h,
                              rectangle.center.y - rectangle.size_.w,
                              rectangle.center.x + rectangle.size_.h,
                              rectangle.center.y + rectangle.size_.w,
                              colorScheme.rim.r,
                              colorScheme.rim.g,
                              colorScheme.rim.b,
                              colorScheme.rim.a
                );
            } else {
                pt::point<int> p2[4] {
                        {rectangle.size_.w, -rectangle.size_.h},
                        {-rectangle.size_.w, -rectangle.size_.h},
                        {-rectangle.size_.w, rectangle.size_.h},
                        {rectangle.size_.w, rectangle.size_.h}
                };
                pt::point<int> p[4];
                float angle;
                for(int i = 0; i < 4; i++) {
                    angle = other_things::angle(p2[i]);
                    p[i] = other_things::rotatePointInt(angle + DEGREES_TO_RADIAN(rectangle.angle),
                                                        other_things::radius(p2[i]));
//                    p[i].x = (int)math_things::normalize(p2[i].x*std::cos(DEGREES_TO_RADIAN(rectangle.angle))
//                             - p2[i].y*std::sin(DEGREES_TO_RADIAN(rectangle.angle)));
//                    p[i].y = (int)math_things::normalize(p2[i].x*std::sin(DEGREES_TO_RADIAN(rectangle.angle))
//                             + p2[i].y*std::cos(DEGREES_TO_RADIAN(rectangle.angle)));
                }
                for(int i = 0; i < 3; i++) {
                    drawaaLine(p[i], p[i+1], rectangle.center, colorScheme.rim);
                }
                drawaaLine(p[0], p[3], rectangle.center, colorScheme.rim);
            }
        }
    }

    inline void drawaaLine(const pt::point<int>& p1, const pt::point<int>& p2, const pt::point<int>& center, const SDL_Color& color) {
        aalineRGBA(renderer,
                   p1.x + center.x, p1.y + center.y,
                   p2.x + center.x, p2.y + center.y,
                   color.r, color.g, color.b, color.a);
    }

    inline void draw(const pt::Circle<int>& circle, const ColorScheme& colorScheme) {
        aacircleRGBA(renderer,
                     circle.center.x,
                     circle.center.y,
                     circle.radius,
                     colorScheme.rim.r,
                     colorScheme.rim.g,
                     colorScheme.rim.b,
                     colorScheme.rim.a
        );
    }

    inline void draw(const pt::Polygon<int>& polygon, const ColorScheme& colorScheme) {
        pt::point<int> p, p2;
        float base_angle = DEGREES_TO_RADIAN(polygon.angle);
        float radius, angle;
        for(auto it = polygon.points.begin();
            it != --polygon.points.end();) {
            p = other_things::rotatePointInt(other_things::angle(*it) - base_angle, other_things::radius(pt::point<int>{it->x, it->y}));
            ++it;
            p2 = other_things::rotatePointInt(other_things::angle(*it) - base_angle, other_things::radius(pt::point<int>{it->x, it->y}));

            aalineRGBA(renderer,
                     polygon.center.x + p.x,
                     polygon.center.y + p.y,
                     polygon.center.x + p2.x,
                     polygon.center.y + p2.y,
                     colorScheme.rim.r,
                     colorScheme.rim.g,
                     colorScheme.rim.b,
                     colorScheme.rim.a
            );
        }
        p = other_things::rotatePointInt(other_things::angle(polygon.points.at(0)) - base_angle,
                                 other_things::radius(pt::point<int>{polygon.points.at(0).x, polygon.points.at(0).y}));
        p2 = other_things::rotatePointInt(other_things::angle(*polygon.points.rbegin()) - base_angle,
                                  other_things::radius(pt::point<int>{polygon.points.rbegin()->x, polygon.points.rbegin()->y}));
        aalineRGBA(renderer,
                 polygon.center.x + p.x,
                 polygon.center.y + p.y,
                 polygon.center.x + p2.x,
                 polygon.center.y + p2.y,
                 colorScheme.rim.r,
                 colorScheme.rim.g,
                 colorScheme.rim.b,
                 colorScheme.rim.a
        );
    }


    inline void draw(SDL_Texture* texture, SDL_Rect& rec) {
        SDL_RenderCopy(renderer, texture, nullptr, &rec);
    }

    inline void draw(SDL_Texture* texture, SDL_Rect& rec, const float angle) {
        SDL_RenderCopyEx(renderer, texture, nullptr, &rec, angle, nullptr, SDL_FLIP_NONE);
    }

    SDL_Renderer* getRenderer() const { return renderer; }
    TTF_Font* getFont() const { return font; }

private:
    ~Draftsman() {
        if(renderer)
            SDL_DestroyRenderer(renderer);
        if(window)
            SDL_DestroyWindow(window);
        if(font)
            TTF_CloseFont(font);
        IMG_Quit();
        if(TTF_WasInit())
            TTF_Quit();
        SDL_Quit();
    }
    bool createWindowAndRenderer() {
        window = SDL_CreateWindow(
                window::title,
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                window::size.w, window::size.h,
                SDL_WINDOW_SHOWN/*|SDL_WINDOW_RESIZABLE*/
        );

        if(!window) {
            PRINT_ERROR("SDL_CreateWindow", SDL_GetError());
            return false;
        }
        renderer = SDL_CreateRenderer(
                window,
                -1,
                SDL_RENDERER_ACCELERATED /*| SDL_RENDERER_PRESENTVSYNC*/
        );
        if(!renderer) {
            PRINT_ERROR("SDL_CreateRenderer", SDL_GetError());
            return false;
        }
        //SDL_RenderSetLogicalSize(renderer, WindowSize.width, WindowSize.height);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        return true;

    }
    bool initSDL() {
//        if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS) != 0) {
        if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            PRINT_ERROR("SDL_Init",  SDL_GetError());
            return false;
        }
        if(TTF_Init() < 0) {
            PRINT_ERROR("TTF_Init", SDL_GetError());
            return false;
        }

        font = TTF_OpenFont("fonts/Capture_it.ttf", 18);

        if(!font) {
            PRINT_ERROR("TTF_OpenFont", SDL_GetError());
            return false;
        }

        int flags = IMG_INIT_PNG|IMG_INIT_JPG;
        int initted = IMG_Init(flags);
        if((initted & flags) != flags) {
            PRINT_ERROR("IMG_Init", IMG_GetError());
            return false;
        }
        SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
        SDL_initFramerate(&fps_manager);
        SDL_setFramerate(&fps_manager, 30);
        return true;
    }

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    FPSmanager fps_manager{};
    TTF_Font* font = nullptr;
};

#endif //TESTC_DRAFTSMEN_H

#ifndef TESTC_INTERCEPTOR_H
#define TESTC_INTERCEPTOR_H

#include <SDL2/SDL.h>
#include <utility/other_things.h>
#include <thread>
#include <chrono>
#include <future>
#include "ContextManager.h"

class Interceptor {
    NOW_YOU_ARE_SINGELTON(Interceptor)
public:
    inline bool interceptWithAction() {
        static SDL_Event event;
        auto context = ContextManager::getInstance().getCurrentContext().lock();

        if (SDL_PollEvent(&event) == 0)
            return true;
        switch (event.type) {
            case SDL_QUIT:
                return false;
            case SDL_APP_TERMINATING:
                return false;
            case SDL_MOUSEMOTION:
                if(context != nullptr)
                    context->check(EventType::MOUSE_MOVE, {event.button.x, event.button.y});
                break;
            case SDL_KEYDOWN:
                if(context != nullptr)
                    context->check(EventType::KEY_DOWN, SDL_GetKeyName(event.key.keysym.sym));
                break;
            case SDL_KEYUP:
                // context.keyUp(SDL_GetKeyName(event.key.keysym.sym));
                break;
            case SDL_TEXTEDITING:
                //
                break;
            case SDL_TEXTINPUT:
                //
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        if(context != nullptr)
                            context->check(EventType::LEFT_BUTTON_DOWN, {event.button.x, event.button.y});
                        break;
                    case SDL_BUTTON_RIGHT:
                        if(context != nullptr)
                            context->check(EventType::RIGHT_BUTTON_DOWN, {event.button.x, event.button.y});
                        break;
                    default:break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        if(context != nullptr)
                            context->check(EventType::LEFT_BUTTON_UP, {event.button.x, event.button.y});
                        break;
                    case SDL_BUTTON_RIGHT:
                        if(context != nullptr)
                            context->check(EventType::RIGHT_BUTTON_UP, {event.button.x, event.button.y});
                        break;
                    default:break;
                }
                break;
            default:break;
        }
        return true;
    }
    void run(std::atomic<bool>& isGameDone) {
        stop();
        std_thread_ = std::move(std::thread(&Interceptor::runnable, this, std::ref(isGameDone)));
        isDone_ = false;
        std_thread_.detach();
    }

    void stop() {
        if(isDone_ == false) {
            isDone_ = true;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

private:
    void runnable(std::atomic<bool>& isGameDone) {
        while(!isDone_){
            if(!interceptWithAction()) {
                isDone_ = true;
                isGameDone = true;
            }
//            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    std::thread std_thread_;
    std::atomic<bool> isDone_{true};
};


#endif //TESTC_INTERCEPTOR_H

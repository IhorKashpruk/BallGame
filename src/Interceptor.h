#ifndef TESTC_INTERCEPTOR_H
#define TESTC_INTERCEPTOR_H

#include <SDL2/SDL.h>
#include <utility/other_things.h>
#include <thread>
#include <chrono>
#include <future>
#include "ContextManager.h"

class Interceptor {
NOW_YOU_ARE_SINGLETON(Interceptor)
public:
    inline bool interceptWithAction() {
        static SDL_Event event;
//        auto context = ContextManager::getInstance().getCurrentContext().lock();

        if (SDL_PollEvent(&event) == 0)
            return true;
        switch (event.type) {
            case SDL_QUIT:
                return false;
            case SDL_APP_TERMINATING:
                return false;
            case SDL_MOUSEMOTION:
            EventManager::getInstance().add(Event{DEVICE::MOUSE, EVENT::MOUSE_MOVE, {event.button.x, event.button.y}});
//                if(context != nullptr)
//                    context->check(EVENT::MOUSE_MOVE, {event.button.x, event.button.y});
                break;
            case SDL_KEYDOWN:
                EventManager::getInstance().add(Event{DEVICE::KEYBOARD, EVENT::KEY_DOWN, {key: SDL_GetKeyName(event.key.keysym.sym)}});
                EventManager::getInstance().setKeyDown(SDL_GetKeyName(event.key.keysym.sym));
//                if(context != nullptr) {
//                    context->check(EVENT::KEY_DOWN, SDL_GetKeyName(event.key.keysym.sym));
//                }
                break;
            case SDL_KEYUP:
                EventManager::getInstance().setKeyUp(SDL_GetKeyName(event.key.keysym.sym));
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
                        EventManager::getInstance().add(Event{DEVICE::MOUSE, EVENT::LEFT_BUTTON_DOWN, {event.button.x, event.button.y}});
//                        if(context != nullptr)
//                            context->check(EVENT::LEFT_BUTTON_DOWN, {event.button.x, event.button.y});
                        break;
                    case SDL_BUTTON_RIGHT:
                        EventManager::getInstance().add(Event{DEVICE::MOUSE, EVENT::RIGHT_BUTTON_DOWN, {event.button.x, event.button.y}});
//                        if(context != nullptr)
//                            context->check(EVENT::RIGHT_BUTTON_DOWN, {event.button.x, event.button.y});
                        break;
                    default:break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        EventManager::getInstance().add(Event{DEVICE::MOUSE, EVENT::LEFT_BUTTON_UP, {event.button.x, event.button.y}});

//                        if(context != nullptr)
//                            context->check(EVENT::LEFT_BUTTON_UP, {event.button.x, event.button.y});
                        break;
                    case SDL_BUTTON_RIGHT:
                        EventManager::getInstance().add(Event{DEVICE::MOUSE, EVENT::RIGHT_BUTTON_UP, {event.button.x, event.button.y}});

//                        if(context != nullptr)
//                            context->check(EVENT::RIGHT_BUTTON_UP, {event.button.x, event.button.y});
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
        thread_ = std::move(std::thread(&Interceptor::runnable, this, std::ref(isGameDone)));
        isDone_ = false;
        thread_.detach();
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
    std::thread thread_;
    std::atomic<bool> isDone_{true};
};


#endif //TESTC_INTERCEPTOR_H

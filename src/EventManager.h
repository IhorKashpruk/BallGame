#ifndef TESTC_EVENTMANAGER_H
#define TESTC_EVENTMANAGER_H

#include "utility/other_things.h"
#include "utility/primitive_types.h"
#include <vector>
#include <mutex>
#include <map>

enum class EVENT {
    LEFT_BUTTON_DOWN    = 1,
    RIGHT_BUTTON_DOWN   = 2,
    LEFT_BUTTON_UP      = 4,
    RIGHT_BUTTON_UP     = 8,
    MOUSE_MOVE          = 16,
    KEY_DOWN            = 32,
    KEY_UP              = 64,
    NONE                = 128
};

enum class DEVICE {
    MOUSE       = 0,
    KEYBOARD    = 1
};

struct Event {
    DEVICE device;
    EVENT event;
    union {
        const pt::point point;
        const char* key;
    };
};

struct KeyStatus {
    bool down = false;
};

class EventManager {
NOW_YOU_ARE_SINGLETON(EventManager)
public:
    static void add(Event&& event) {
        std::lock_guard<std::mutex> guard(m_);
        events_.push_back(std::move(event));
    }
    static void get(std::vector<Event>& events) {
        std::lock_guard<std::mutex> guard(m_);
        events_.swap(events);
    }
    static bool empty() {
        return events_.empty();
    }
    static KeyStatus getKeyStatus(const char* key) {
        return keys_[key];
    }

    static bool keyIsDown(const char* key) {
        return keys_[key].down;
    }

    static void setKeyDown(const char* key) {
        if(!keys_[key].down)
            keys_[key].down = true;
    }
    static void setKeyUp(const char* key) {
        keys_[key].down = false;
    }
private:
    static std::mutex m_;
    static std::vector<Event> events_;
    static std::map<std::string, KeyStatus> keys_;
};

std::mutex EventManager::m_ = {};
std::vector<Event> EventManager::events_ = {};
std::map<std::string, KeyStatus> EventManager::keys_ = {};

#endif //TESTC_EVENTMANAGER_H

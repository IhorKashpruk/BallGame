#ifndef MYGAME_CHECKER_H
#define MYGAME_CHECKER_H

#include "../utility/primitive_types.h"

enum class SpecEventType {
    CLICK_LEFT_BUTTON   = 0,
    CLICK_RIGHT_BUTTON  = 1,
    ENTER_KEY           = 2,
    MOUSE_MOVE          = 3,
    NONE                = 4
};

enum class EventType {
    LEFT_BUTTON_DOWN    = 0,
    RIGHT_BUTTON_DOWN   = 1,
    LEFT_BUTTON_UP      = 2,
    RIGHT_BUTTON_UP     = 3,
    MOUSE_MOVE          = 4,
    KEY_DOWN            = 5,
    KEY_UP              = 6,
    NONE                = 7
};

struct Event {
    EventType previous_ = EventType::NONE;
    SpecEventType add(const EventType t) {
        if(previous_ == EventType::NONE) {
            previous_ = t;
            return SpecEventType::NONE;
        }
        switch(t) {
            case EventType::LEFT_BUTTON_DOWN:
                break;
            case EventType::RIGHT_BUTTON_DOWN:
                break;
            case EventType::LEFT_BUTTON_UP:
                if(previous_ == EventType::LEFT_BUTTON_DOWN)
                    return SpecEventType::CLICK_LEFT_BUTTON;
                break;
            case EventType::RIGHT_BUTTON_UP:
                if(previous_ == EventType::RIGHT_BUTTON_DOWN)
                    return SpecEventType::CLICK_RIGHT_BUTTON;
                break;
            case EventType::MOUSE_MOVE:
                return SpecEventType ::MOUSE_MOVE;
                break;
            case EventType::KEY_DOWN:
                return SpecEventType::ENTER_KEY;
                break;
            case EventType::KEY_UP:break;
            case EventType::NONE:break;
        }
        previous_ = t;
        return SpecEventType::NONE;
    }
    void clear() {
        previous_ = EventType::NONE;
    }
};


class AChecker {
    typedef int T;
    typedef pt::point<T> Point;
public:
    virtual ~AChecker() = default;

protected:
    virtual void check(const EventType& event, const Point& point) = 0;
    virtual void check(const EventType& event, const char* key) = 0;
    Event& getPreviousEvent() { return previousEvent_; }
private:
    Event previousEvent_;
};


#endif //MYGAME_CHECKER_H

#ifndef MYGAME_CHECKER_H
#define MYGAME_CHECKER_H

#include "../utility/primitive_types.h"
#include "../EventManager.h"

enum class CONTEXT_EVENT_ {
    L_B_D__L_B_U    = 5,
    R_B_D__R_B_U    = 10,
    M_M__M_M        = 16,
    K_D__K_U        = 96,
    K_D__K_D        = 32,
    K_D__M_M        = 48,
    NONE__K_D       = 160,
    NONE            = 128
};

enum class CONTEXT_EVENT {
    CLICK_LEFT_BUTTON   = 5,
    CLICK_RIGHT_BUTTON  = 10,
    MOUSE_MOVE          = 16,
    ENTER_KEY           = 96,
    NONE                = 128
};

struct EventSimplifier {
    EVENT previous_ = EVENT::NONE;
    CONTEXT_EVENT add(const EVENT t) {
//        if(previous_ == EVENT::NONE) {
//            previous_ = t;
//            return CONTEXT_EVENT::NONE;
//        }
        if(t == EVENT::KEY_DOWN) {
            return CONTEXT_EVENT::ENTER_KEY;
        }
        switch((int)previous_ | (int)t) {
            case (int)CONTEXT_EVENT_::L_B_D__L_B_U:
                clear();
                return CONTEXT_EVENT::CLICK_LEFT_BUTTON;
            case (int)CONTEXT_EVENT_::R_B_D__R_B_U:
                clear();
                return CONTEXT_EVENT::CLICK_RIGHT_BUTTON;
            case (int)CONTEXT_EVENT_::M_M__M_M:
                clear();
                return CONTEXT_EVENT::MOUSE_MOVE;
            case (int)CONTEXT_EVENT_::K_D__K_U:
                clear();
                return CONTEXT_EVENT::ENTER_KEY;
            case (int)CONTEXT_EVENT_::K_D__K_D:
                clear();
                return CONTEXT_EVENT::ENTER_KEY;
            case (int)CONTEXT_EVENT_::K_D__M_M:
                clear();
                return CONTEXT_EVENT::ENTER_KEY;
            case (int)CONTEXT_EVENT_::NONE__K_D:
                clear();
                return CONTEXT_EVENT::ENTER_KEY;
            default:
                previous_ = t;
                return CONTEXT_EVENT::NONE;
        }
     }
    void clear() {
        previous_ = EVENT::NONE;
    }
};


class AChecker {
    typedef int T;
    typedef pt::point<T> Point;
public:
    virtual ~AChecker() = default;

protected:
    virtual void check(const EVENT& event, const Point& point) = 0;
    virtual void check(const EVENT& event, const char* key) = 0;
    EventSimplifier& getPreviousEvent() { return previousEvent_; }
private:
    EventSimplifier previousEvent_;
};


#endif //MYGAME_CHECKER_H

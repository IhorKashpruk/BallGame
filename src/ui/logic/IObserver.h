#ifndef TESTC_IOBSERVER_H
#define TESTC_IOBSERVER_H

#include <any>
#include <utility>
#include <string>

enum class STATE {
    LEFT_BUTTON_CLICK,
    RIGHT_BUTTON_CLICK,
    MOUSE_MOVE,
    ENTER_KEY,

    START_GAME,
    END_GAME,
    RESTART_GAME,
    VALUE_CHANGED,
    BALL_OUTSIDE_CAMERA
};

class Signal {
public:
    explicit Signal(std::string uio_id, STATE state, std::any value = nullptr)
            : uio_id_(std::move(uio_id)), state_(state), value_(std::move(value)) {}
    STATE& getState()           { return state_; }
    std::any& getValue()        { return value_; }
    std::string& getUIOID()     { return uio_id_;}
private:
    std::string uio_id_;
    STATE state_;
    std::any value_;
};

class IObserver {
public:
    virtual void update(Signal) = 0;
};

#endif //TESTC_IOBSERVER_H

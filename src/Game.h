#ifndef TESTC_GAME_H
#define TESTC_GAME_H

#include <utility/other_things.h>
#include "Interceptor.h"
#include "Draftsman.h"

class Game {
NOW_YOU_ARE_SINGLETON(Game)
public:
    bool setUp() {
        if(!Draftsman::getInstance().init()) {
            return false;
        }
        isDone_ = false;
        Interceptor::getInstance().run(isDone_);
        return true;
    }

    void loop() {
        while(!isDone_) {
            Draftsman::getInstance().clearAndSetBaseColor();
            if(auto spt = ContextManager::getInstance().getCurrentContext().lock()){
                spt->update();
                spt->draw();
            }
            Draftsman::getInstance().draw();
        }
    }
    void stop() {
        isDone_ = true;
        Interceptor::getInstance().stop();
    }
private:
    std::atomic<bool> isDone_{true};
};


#endif //TESTC_GAME_H

#ifndef TESTC_WORLDLOGIC_H
#define TESTC_WORLDLOGIC_H

#include "ALogic.h"

class WorldLogic : public AContextLogic {
public:
    explicit WorldLogic(Context* context) : AContextLogic(context) {}
public:
    void update(const Signal& signal) override {
        if(signal.getState() == STATE::END_GAME) {
            ContextManager::getInstance().setCurrentContext("menu_context");
        }
    }
};

#endif //TESTC_WORLDLOGIC_H

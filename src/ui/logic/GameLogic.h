#ifndef TESTC_GAMELOGIC_H
#define TESTC_GAMELOGIC_H

#include <iostream>
#include <ContextManager.h>
#include <ui/physics/Ball.h>
#include <ui/physics/WorldUIO.h>
#include "ALogic.h"
#include "WorldLogic.h"

class GameLogic : public AContextLogic {
public:
    explicit GameLogic(Context* context) : AContextLogic(context) {}
public:
    void update(Signal signal) override {
        WorldUIO<WorldLogic, pt::Rectangle>* worldContext =
                dynamic_cast<WorldUIO<WorldLogic, pt::Rectangle> *>(context_->get("world_context"));
        Ball* ball = static_cast<Ball*>(worldContext->get("ball"));
        if(signal.getState() == STATE::ENTER_KEY) {
            const char* key = std::any_cast<const char*>(signal.getValue());
            if(strcmp(key,"Escape") == 0) {
                ContextManager::getInstance().setCurrentContext("menu_context");
            }
        }
    }

private:
};

#endif //TESTC_GAMELOGIC_H

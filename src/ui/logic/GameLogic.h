#ifndef TESTC_GAMELOGIC_H
#define TESTC_GAMELOGIC_H

#include <iostream>
#include <ContextManager.h>
#include <ui/Ball.h>
#include <ui/physics/WorldContext.h>
#include "ALogic.h"
#include "WorldLogic.h"

class GameLogic : public AContextLogic {
public:
    explicit GameLogic(Context* context) : AContextLogic(context) {}
public:
    void update(Signal signal) override {

        if(signal.getState() == STATE::ENTER_KEY) {
            if(strcmp(std::any_cast<const char*>(signal.getValue()),"Escape") == 0) {
                ContextManager::getInstance().setCurrentContext("menu_context");
            }
        }
        if(signal.getState() == STATE::LEFT_BUTTON_CLICK) {
            AUIO* auio = context_->get("world_context");
            if(auio) {
                WorldContext<WorldLogic, pt::Rectangle>* worldContext =
                        dynamic_cast<WorldContext<WorldLogic, pt::Rectangle> *>(auio);
                if (worldContext) {
                    AUIO* ball = worldContext->get("ball");
                    if(ball) {
                        Ball* b = dynamic_cast<Ball *>(ball);
                        b->addVelocity(
                                other_things::calculateForce(
                                        std::any_cast<pt::point<int>>(signal.getValue()),
                                        b->shape(), b->getSpeed())
                        );
                    }
                }
            }
        }
    }
};

#endif //TESTC_GAMELOGIC_H

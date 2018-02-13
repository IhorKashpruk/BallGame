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

        if(signal.getState() == STATE::ENTER_KEY) {
            if(strcmp(std::any_cast<const char*>(signal.getValue()),"Escape") == 0) {
                ContextManager::getInstance().setCurrentContext("menu_context");
            }
        }
        if(signal.getState() == STATE::LEFT_BUTTON_CLICK) {
            AUIO* auio = context_->get("world_context");
            if(auio) {
                WorldUIO<WorldLogic, pt::Rectangle>* worldContext =
                        dynamic_cast<WorldUIO<WorldLogic, pt::Rectangle> *>(auio);
                if (worldContext) {
                    AUIO* ball = worldContext->get("ball");
                    if(ball) {
                        Ball* b = dynamic_cast<Ball *>(ball);
                        pt::point<int> point = std::any_cast<pt::point<int>>(signal.getValue());
                        if(!pt::under(b->shape(), point)) {
                            b2Vec2 force = other_things::calculateForce(
                                    point,
                                    b->shape().center, b->getSpeed());
                            b->addForce(force);
                        }
                    }
                }
            }
        }
    }
};

#endif //TESTC_GAMELOGIC_H

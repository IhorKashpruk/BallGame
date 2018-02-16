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
            const char* key = std::any_cast<const char*>(signal.getValue());
            if(strcmp(key,"Escape") == 0) {
                ContextManager::getInstance().setCurrentContext("menu_context");
            }
            if(isNecessaryKey(key)) {
                AUIO *auio = context_->get("world_context");
                WorldUIO<WorldLogic, pt::Rectangle> *worldContext =
                        dynamic_cast<WorldUIO<WorldLogic, pt::Rectangle> *>(auio);
                AUIO *ball = worldContext->get("ball");
                Ball *b = dynamic_cast<Ball *>(ball);
                b->setDirection(direction(key));
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
                        b2Vec2 point1 = other_things::toPoint(point);
                        if(!pt::under(b->shape(), point)) {
                            b2Vec2 force = other_things::calculateForce(
                                    b->body()->GetPosition(),
                                    point1, b->getSpeed());
                            b->addForce(force);
                        }
                    }
                }
            }
        }
    }

private:
    bool isNecessaryKey(const char* key) {
        return !strcmp(key,"Up")
               || !strcmp(key,"Down")
               || !strcmp(key,"Left")
               || !strcmp(key,"Right")
               || !strcmp(key,"Space");
    }
    typename Ball::DIRECTION direction(const char* key) {
        if(!strcmp(key,"Up")) { return Ball::DIRECTION::UP; }
        if(!strcmp(key,"Down")) { return Ball::DIRECTION::DOWN; }
        if(!strcmp(key,"Left")) { return Ball::DIRECTION::LEFT; }
        if(!strcmp(key,"Right")) { return Ball::DIRECTION::RIGHT; }
        if(!strcmp(key,"Space")) { return Ball::DIRECTION::NONE; }
    }
};

#endif //TESTC_GAMELOGIC_H

#ifndef TESTC_EXITDOOR_H
#define TESTC_EXITDOOR_H

#include "PUIO.h"

class ExitDoor : public PUIO {
public:
    ExitDoor(std::string &&id, box2d::WorldWrapper &world, b2BodyDef &&bodyDef, EntityCategory entityCategory)
            : PUIO(id, world, bodyDef, entityCategory) {}
    ExitDoor(const std::string &id, box2d::WorldWrapper &world, b2BodyDef &bodyDef, EntityCategory entityCategory)
            : PUIO(id, world, bodyDef, entityCategory) {}

    void beginContact(PUIO *puio, const b2Vec2 &point, const b2Fixture &fixture) override {
        if(puio->getEntityCategory() == EntityCategory::PLAYER) {
            notify(Signal{this, STATE::END_GAME, nullptr});
        }
    }

    void endContact(PUIO *puio, const b2Vec2 &point, const b2Fixture &fixture) override {
        PUIO::endContact(puio, point, fixture);
    }
};

#endif //TESTC_EXITDOOR_H

#ifndef TESTC_EXITDOOR_H
#define TESTC_EXITDOOR_H

#include "PUIO.h"

class ExitDoor : public PUIO {
public:
    ExitDoor(std::string &&id, box2d::WorldWrapper &world, b2BodyDef &&bodyDef, EntityCategory entityCategory)
            : PUIO(id, world, bodyDef, entityCategory) {}
    ExitDoor(const std::string &id, box2d::WorldWrapper &world, b2BodyDef &bodyDef, EntityCategory entityCategory)
            : PUIO(id, world, bodyDef, entityCategory) {}

    void beginContact(PUIO *puio) override {
        if(puio->getEntityCategory() == EntityCategory::PLAYER) {
            notify(Signal{this, STATE::END_GAME, nullptr});
        }
    }

    void endContact(PUIO *puio) override {

    }
};

#endif //TESTC_EXITDOOR_H

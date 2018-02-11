#ifndef TESTC_WORLDLOGIC_H
#define TESTC_WORLDLOGIC_H

#include "ALogic.h"

class WorldLogic : public AContextLogic {
public:
    explicit WorldLogic(Context* context) : AContextLogic(context) {}
public:
    void update(Signal signal) override {
    }
};

#endif //TESTC_WORLDLOGIC_H

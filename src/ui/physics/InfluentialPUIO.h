#ifndef TESTC_INFLUENTALPUIO_H
#define TESTC_INFLUENTALPUIO_H

#include "PUIO.h"
#include "Influential.h"

template <class Influential>
class InfluentialPUIO : public PUIO, public Influential {
public:
    explicit InfluentialPUIO(
            std::string &&id,
            box2d::WorldWrapper &world,
            b2BodyDef &&bodyDef,
            typename Influential::properties&& properties,
            EntityCategory entityCategory)
            : PUIO(id, world, bodyDef, entityCategory),
              Influential(properties) {
        Influential* p = static_cast<Influential*>(this);
        setUserData(p);
        Influential::setOwner(this);
    }
    explicit InfluentialPUIO(
            const std::string &id,
            box2d::WorldWrapper &world,
            b2BodyDef &bodyDef,
            const typename Influential::properties& properties,
            EntityCategory entityCategory)
            : PUIO(id, world, bodyDef, entityCategory),
              Influential(properties) {
        Influential* p = static_cast<Influential*>(this);
        setUserData(p);
        Influential::setOwner(this);
    }

    ~InfluentialPUIO() = default;

    void update() override {
        PUIO::update();
        Influential::update();
        Influential::work();
    }
};

#endif //TESTC_INFLUENTALPUIO_H

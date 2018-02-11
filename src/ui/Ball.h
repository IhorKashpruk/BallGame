#ifndef TESTC_BALL_H
#define TESTC_BALL_H

#include <utility/primitive_types.h>
#include "PUIO.h"

class Ball : public PUIO {
public:
    struct properties {
        float speed;
    };
    explicit Ball(std::string&& id,
                  box2d::WorldWrapper& world,
                  b2BodyDef& bodyDef,
                  const properties& prop) :
            PUIO(std::move(id), world, bodyDef),
            properties_(prop){}
    explicit Ball(std::string&& id,
                  box2d::WorldWrapper& world,
                  b2BodyDef&& bodyDef,
                  properties&& prop) :
            PUIO(std::move(id), world, bodyDef),
            properties_(prop) {}
    ~Ball() override = default;

    void addForce(b2Vec2 force) {
        PUIO::body_->ApplyForce(force, PUIO::body_->GetWorldCenter(), true);
    }

    void addLinerImpulse(b2Vec2 impulse) {
        PUIO::body_->ApplyLinearImpulse(impulse, PUIO::body_->GetWorldCenter(), true);
    }

    void addVelocity(b2Vec2 velocity) {
        PUIO::body_->SetLinearVelocity(velocity);
    }

    pt::Circle<int> shape() {
        return other_things::toCircle(
                body_->GetPosition(),
                body_->GetFixtureList()[0].GetShape()->m_radius,
                body_->GetAngle()
        );
    }

    float getSpeed() const {
        return properties_.speed;
    }

    void setSpeed(float speed) {
        properties_.speed = speed;
    }

private:
    properties properties_;
};


#endif //TESTC_BALL_H

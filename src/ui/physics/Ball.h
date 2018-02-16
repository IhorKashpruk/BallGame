#ifndef TESTC_BALL_H
#define TESTC_BALL_H

#include <utility/primitive_types.h>
#include "ui/physics/PUIO.h"
#include <atomic>


class Ball : public PUIO {
public:
    struct properties {
        float speed;
    };
    enum class DIRECTION {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        STOP,
        NONE
    };
    explicit Ball(std::string&& id,
                  box2d::WorldWrapper& world,
                  b2BodyDef& bodyDef,
                  const properties& prop) :
            PUIO(std::move(id), world, bodyDef),
            properties_(prop){ PUIO::setUserData(this); }
    explicit Ball(std::string&& id,
                  box2d::WorldWrapper& world,
                  b2BodyDef&& bodyDef,
                  properties&& prop) :
            PUIO(std::move(id), world, bodyDef),
            properties_(prop) { PUIO::setUserData(this); }
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

    void update() override {
        PUIO::update();
        switch (direction_.load()) {
            case DIRECTION::UP:
                addForce(b2Vec2{0.0f, properties_.speed});
                break;
            case DIRECTION::DOWN:
                addForce(b2Vec2{0.0f, -properties_.speed});
                break;
            case DIRECTION::LEFT:
                addForce(b2Vec2{-properties_.speed, 0.0f});
                break;
            case DIRECTION::RIGHT:
                addForce(b2Vec2{properties_.speed, 0.0f});
                break;
            case DIRECTION::STOP:
                addForce(b2Vec2{0.0f, 0.0f});
                break;
            case DIRECTION::NONE:
                break;
        };
        direction_ = DIRECTION::NONE;
    }

    void setDirection(DIRECTION direction) { direction_ = direction; }
    DIRECTION getDirection() { return direction_; }

private:
    properties properties_;
    std::atomic<DIRECTION> direction_ {DIRECTION::NONE};
};


#endif //TESTC_BALL_H

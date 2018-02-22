#ifndef TESTC_BALL_H
#define TESTC_BALL_H

#include <utility/primitive_types.h>
#include "ui/physics/PUIO.h"
#include <atomic>
#include <map>


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
        LEFT_UP,
        RIGHT_UP,
        STOP,
        NONE
    };
    explicit Ball(std::string&& id,
                  box2d::WorldWrapper& world,
                  b2BodyDef& bodyDef,
                  const properties& prop,
                  EntityCategory entityCategory) :
            PUIO(std::move(id), world, bodyDef, entityCategory),
            properties_(prop){ PUIO::setUserData(this); }
    explicit Ball(std::string&& id,
                  box2d::WorldWrapper& world,
                  b2BodyDef&& bodyDef,
                  properties&& prop,
                  EntityCategory entityCategory) :
            PUIO(std::move(id), world, bodyDef, entityCategory),
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
        if(!onGround_) {
            return;
        }
        switch (direction()) {
            case DIRECTION::UP:
                addVelocity(b2Vec2{0.0f, properties_.speed});
                break;
            case DIRECTION::DOWN:
                addVelocity(b2Vec2{0.0f, -properties_.speed});
                break;
            case DIRECTION::LEFT:
                addVelocity(b2Vec2{-properties_.speed, 0.0f});
                break;
            case DIRECTION::RIGHT:
                addVelocity(b2Vec2{properties_.speed, 0.0f});
                break;
            case DIRECTION::LEFT_UP:
                addVelocity(b2Vec2{-properties_.speed, properties_.speed});
                break;
            case DIRECTION::RIGHT_UP:
                addVelocity(b2Vec2{properties_.speed, properties_.speed});
                break;
            case DIRECTION::STOP:
                addVelocity(b2Vec2{0.0f, 0.0f});
                break;
            case DIRECTION::NONE:
                break;
        };
        direction_ = DIRECTION::NONE;
    }

    void onGround(bool value) { onGround_ = value; }
    bool onGround() const { return onGround_; }

private:
    properties properties_;
    DIRECTION direction_ {DIRECTION::NONE};
    bool onGround_ = false;

    typename Ball::DIRECTION direction() {
#define KEY_DOWN(key) EventManager::getInstance().keyIsDown(key)
        if(KEY_DOWN("Up") && KEY_DOWN("Left"))  { return Ball::DIRECTION::LEFT_UP; }
        if(KEY_DOWN("Up") && KEY_DOWN("Right")) { return Ball::DIRECTION::RIGHT_UP; }
        if(KEY_DOWN("Up"))      { return Ball::DIRECTION::UP; }
        if(KEY_DOWN("Down"))    { return Ball::DIRECTION::DOWN; }
        if(KEY_DOWN("Left"))    { return Ball::DIRECTION::LEFT; }
        if(KEY_DOWN("Right"))   { return Ball::DIRECTION::RIGHT; }
        if(KEY_DOWN("Space"))   { return Ball::DIRECTION::STOP; }
        return Ball::DIRECTION::NONE;
#undef KEY_DOWN
    }
};


#endif //TESTC_BALL_H

#ifndef TESTC_PLAYER_H
#define TESTC_PLAYER_H

#include <utility/primitive_types.h>
#include "ui/physics/PUIO.h"
#include <atomic>
#include <map>
#include <EventManager.h>

class Player : public PUIO {
public:
    struct properties {
        float move_force;
        float jump_force;
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
    explicit Player(std::string&& id,
                  box2d::WorldWrapper& world,
                  b2BodyDef& bodyDef,
                  const properties& prop,
                  EntityCategory entityCategory) :
            PUIO(std::move(id), world, bodyDef, entityCategory),
            properties_(prop){
        setUserData(this);
    }
    explicit Player(std::string&& id,
                  box2d::WorldWrapper& world,
                  b2BodyDef&& bodyDef,
                  properties&& prop,
                  EntityCategory entityCategory) :
            PUIO(std::move(id), world, bodyDef, entityCategory),
            properties_(prop) {
        setUserData(this);
    }
    ~Player() override = default;

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

    void update() override {
        PUIO::update();
        if(!onGround_) {
            return;
        }
        switch (direction()) {
            case DIRECTION::UP:
                addVelocity(b2Vec2{0.0f, properties_.jump_force});
                break;
            case DIRECTION::DOWN:
                addVelocity(b2Vec2{0.0f, -properties_.jump_force});
                break;
            case DIRECTION::LEFT:
                addVelocity(b2Vec2{-properties_.move_force, 0.0f});
                break;
            case DIRECTION::RIGHT:
                addVelocity(b2Vec2{properties_.move_force, 0.0f});
                break;
            case DIRECTION::LEFT_UP:
                addVelocity(b2Vec2{-properties_.jump_force, properties_.jump_force});
                break;
            case DIRECTION::RIGHT_UP:
                addVelocity(b2Vec2{properties_.jump_force, properties_.jump_force});
                break;
            case DIRECTION::STOP:
                addVelocity(b2Vec2{0.0f, 0.0f});
                break;
            case DIRECTION::NONE:
                break;
        };
    }

    void onGround(bool value) { onGround_ = value; }
    bool onGround() const { return onGround_; }

    void beginContact(PUIO *puio) override {
        if(puio->getEntityCategory() == EntityCategory::FLOOR) {
            onGround(true);
        }
        if(puio->getEntityCategory() == EntityCategory::EXIT) {
            notify(Signal{this, STATE::END_GAME, nullptr});
        }
    }

    void endContact(PUIO *puio) override {
        if(puio->getEntityCategory() == EntityCategory::FLOOR) {
            onGround(false);
        }
    }

private:
    properties properties_;
    bool onGround_ = false;

    typename Player::DIRECTION direction() {
#define KEY_DOWN(key) EventManager::getInstance().keyIsDown(key)
        if(KEY_DOWN("Up") && KEY_DOWN("Left"))  { return DIRECTION::LEFT_UP; }
        if(KEY_DOWN("Up") && KEY_DOWN("Right")) { return DIRECTION::RIGHT_UP; }
        if(KEY_DOWN("Up"))      { return DIRECTION::UP; }
        if(KEY_DOWN("Down"))    { return DIRECTION::DOWN; }
        if(KEY_DOWN("Left"))    { return DIRECTION::LEFT; }
        if(KEY_DOWN("Right"))   { return DIRECTION::RIGHT; }
        if(KEY_DOWN("Space"))   { return DIRECTION::STOP; }
        return DIRECTION::NONE;
#undef KEY_DOWN
    }
};


#endif //TESTC_PLAYER_H

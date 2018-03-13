#ifndef TESTC_PLAYER_H
#define TESTC_PLAYER_H

#include <utility/primitive_types.h>
#include "ui/physics/PUIO.h"
#include <algorithm>
#include <vector>
#include <functional>
#include <EventManager.h>
#include <Animation.h>

class Player : public PUIO {
public:
    struct properties {
        float move_force;
        float jump_force;
    };

    struct floor_contact {
        bool onGround() const { return !fixtures.empty(); }
        void add(const b2Fixture& fixture) {
            fixtures.emplace_back(fixture);
        }
        void remove(const b2Fixture& fixture) {
            fixtures.erase(std::remove_if(fixtures.begin(), fixtures.end(),
                                          [&fixture](const b2Fixture& f){
                return &f == &fixture;
            }), fixtures.end());
        }
    private:
        std::vector<std::reference_wrapper<const b2Fixture>> fixtures {};
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
        // Send signal to camera
        notify(Signal(this, STATE::VALUE_CHANGED, other_things::toPoint(body_->GetPosition())));

        if(!floor_contact_.onGround()) {
            switch (direction()) {
                case DIRECTION::LEFT:
                    addForce(b2Vec2{-properties_.move_force-1.5f, 0.0f});
                    break;
                case DIRECTION::RIGHT:
                    addForce(b2Vec2{properties_.move_force-1.5f, 0.0f});
                    break;
                case DIRECTION::LEFT_UP:
                    addForce(b2Vec2{-properties_.move_force-1.5f, 0.0f});
                    break;
                case DIRECTION::RIGHT_UP:
                    addForce(b2Vec2{properties_.move_force-1.5f, 0.0f});
                    break;
                case DIRECTION::STOP:
                    addForce(b2Vec2{0.0f, 0.0f});
                    break;
                case DIRECTION::NONE:
                    break;
                default:
                    return;
            };
            return;
        }
        switch (direction()) {
            case DIRECTION::UP:
                addVelocity(b2Vec2{0.0f, properties_.jump_force});
                break;
            case DIRECTION::DOWN:
                //addVelocity(b2Vec2{0.0f, -properties_.jump_force});
                break;
            case DIRECTION::LEFT:
                addVelocity(b2Vec2{-properties_.move_force, 0.0f});
                break;
            case DIRECTION::RIGHT:
                addVelocity(b2Vec2{properties_.move_force, 0.0f});
                break;
            case DIRECTION::LEFT_UP:
                addVelocity(b2Vec2{-properties_.jump_force/6.0f, properties_.jump_force});
                break;
            case DIRECTION::RIGHT_UP:
                addVelocity(b2Vec2{properties_.jump_force/6.0f, properties_.jump_force});
                break;
            case DIRECTION::STOP:
                addVelocity(b2Vec2{0.0f, 0.0f});
                break;
            case DIRECTION::NONE:
                break;
        };
    }

    void beginContact(PUIO *puio, const b2Vec2& point, const b2Fixture& fixture) override {
        if(puio->getEntityCategory() == EntityCategory::FLOOR
           && (body_->GetPosition().y - 0.25) > point.y) {
            floor_contact_.add(fixture);
        }
        if(puio->getEntityCategory() == EntityCategory::EXIT) {
            notify(Signal{this, STATE::END_GAME, nullptr});
        }
    }

    void endContact(PUIO *puio, const b2Vec2& point, const b2Fixture& fixture) override {
        if(puio->getEntityCategory() == EntityCategory::FLOOR) {
            floor_contact_.remove(fixture);
        }
    }

public:
    void draw() override {
        PUIO::draw();
    }

private:
    properties properties_;
    floor_contact floor_contact_;

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

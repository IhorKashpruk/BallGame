#ifndef TESTC_WORLDWRAPPER_H
#define TESTC_WORLDWRAPPER_H

#include <libs/Box2D/Box2D.h>
#include <memory>
#include "box2d_properties.h"

namespace box2d {
    class WorldWrapper {
        typedef std::unique_ptr<b2World> world_ptr;
    public:
        struct properties {
            float32 time_step           = box2d_properties::time_step;
            int32 velocity_iterations   = box2d_properties::velocity_iterations;
            int32 position_iterations   = box2d_properties::position_iterations;
            b2Vec2 gravity {box2d_properties::gravity_x, box2d_properties::gravity_y};
        };
        explicit WorldWrapper(properties& prop)
                : properties_(std::move(prop)),
                  world_(new b2World{prop.gravity}) {}

        explicit WorldWrapper()
                : properties_(),
                  world_(new b2World{properties_.gravity}) {}

        ~WorldWrapper() = default;

        void setGravity(b2Vec2&& gravity) {
            world_->SetGravity(gravity);
        }

        static b2BodyDef createBodyDef(b2BodyType type, b2Vec2&& position, float32 angle) {
            b2BodyDef bodyDef;
            bodyDef.type = type;
            bodyDef.position = position;
            bodyDef.angle = angle;
            return bodyDef;
        }

        b2Body* createBody(const b2BodyDef& bodyDef) {
            return world_->CreateBody(&bodyDef);
        }

        static b2PolygonShape createPolygonShape(const b2Vec2* vertices, int32 count) {
            b2PolygonShape polygonShape;
            polygonShape.Set(vertices, count);
            return polygonShape;
        }

        static b2PolygonShape createPolygonShape(float32 hx, float32 hy) {
            b2PolygonShape polygonShape;
            polygonShape.SetAsBox(hx, hy);
            return polygonShape;
        }

        static b2CircleShape createCircleShape(b2Vec2&& position, float32 radius) {
            b2CircleShape circleShape;
            circleShape.m_p = position;
            circleShape.m_radius = radius;
            return circleShape;
        }

        static b2FixtureDef createFixtureDef(const b2Shape& shape, float32 density, float32 restitution, float32 friction) {
            b2FixtureDef fixtureDef;
            fixtureDef.shape = &shape;
            fixtureDef.density = density;
            fixtureDef.restitution = restitution;
            fixtureDef.friction = friction;
            return fixtureDef;
        }

        void step() {
            world_->Step(
                    properties_.time_step,
                    properties_.velocity_iterations,
                    properties_.position_iterations
            );
        }
        b2World* getWorld() const { return &*world_;}
    private:
        properties properties_;
        world_ptr world_ ;
    };
}

#endif //TESTC_WORLDWRAPPER_H

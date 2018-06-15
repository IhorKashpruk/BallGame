#ifndef TESTC_WINDMILL_H
#define TESTC_WINDMILL_H

#include "ui/physics/PUIO.h"

class Windmill : public AUIO {
    typedef std::unique_ptr<PUIO> puio_ptr;
public:

    struct properties {

    };

    struct blades_properties {
        b2BodyDef body_def;
        b2FixtureDef fixture_def;
        b2Vec2 size;
    };

    struct holder_properties {
        b2BodyDef body_def;
        b2FixtureDef fixture_def;
        float radius;
    };

    struct motor_properties {
        float max_motor_torque;
        float motor_speed;
    };

    explicit Windmill(std::string id,
                      const properties& prop,
                      box2d::WorldWrapper& world,
                      blades_properties bladesProperties,
                      holder_properties holderProperties,
                      motor_properties motorProperties)
            : AUIO(std::move(id)),
              properties_(prop) {
        createBase(id, prop, world, bladesProperties, holderProperties, motorProperties);
    }

    ~Windmill() override = default;

    b2Body* getBlades() { return blades->body(); }
    b2Body* getHolder() { return holder->body(); }

    void update() override {
        AUIO::update();
        if(blades) {
            blades->update();
        }
        if(holder) {
            holder->update();
        }
    }

    bool under(pt::point&& p) override {
        return false;
    }

    bool under(const pt::point& p) override {
        return false;
    }

    bool under(const pt::Circle& circle) const override {
        return true;
    }

    bool under(const pt::Rectangle &rectangle) const override {
        return true;
    }

    bool under(const pt::Polygon &polygon) const override {
        return true;
    }

    pt::point center() const override {
        return {};
    }

    float angle() const override {
        return 0;
    }

    void draw() override {
        if(blades) {
            blades->draw();
        }
        if(holder) {
            holder->draw();
        }
    }

    void draw(const pt::point &offset) override {
        if(blades) {
            blades->draw(offset);
        }
        if(holder) {
            holder->draw(offset);
        }
    }

    void clickLeftButton(const pt::point& p) override {
        notify(Signal{this, STATE::LEFT_BUTTON_CLICK, p});
    }

    void clickRightButton(const pt::point& p) override {
        notify(Signal{this, STATE::RIGHT_BUTTON_CLICK, p});
    }

    void enterKey(const char* key) override {
        notify(Signal{this, STATE::ENTER_KEY, key});
    }

    void mouseMove(const pt::point& p) override {
        notify(Signal{this, STATE::MOUSE_MOVE, p});
    }

private:
    puio_ptr blades  {nullptr};
    puio_ptr holder  {nullptr};
    properties properties_;

    void createBase(const std::string& id,
                    const properties& prop,
                    box2d::WorldWrapper& world,
                    blades_properties& bladesProperties,
                    holder_properties& holderProperties,
                    const motor_properties& motorProperties) {
        // Create blades
        b2Vec2 ps[4] = {
                {-bladesProperties.size.x, bladesProperties.size.y},
                {bladesProperties.size.x, bladesProperties.size.y},
                {bladesProperties.size.x, -bladesProperties.size.y},
                {-bladesProperties.size.x, -bladesProperties.size.y}
        };
        PUIO* blades_puio = new PUIO(id, world, bladesProperties.body_def, EntityCategory::FLOOR);
        // Add first blade
        b2PolygonShape shape = box2d::WorldWrapper::createPolygonShape(ps, 4);
        bladesProperties.fixture_def.shape = &shape;
        blades_puio->createFixture(bladesProperties.fixture_def);
        // Add second blade
        ps[0] = {bladesProperties.size.y, bladesProperties.size.x};
        ps[1] = {bladesProperties.size.y, -bladesProperties.size.x};
        ps[2] = {-bladesProperties.size.y, bladesProperties.size.x};
        ps[3] = {-bladesProperties.size.y, -bladesProperties.size.x};
        shape = box2d::WorldWrapper::createPolygonShape(ps, 4);
        bladesProperties.fixture_def.shape = &shape;
        blades_puio->createFixture(bladesProperties.fixture_def);
        blades.reset(blades_puio);

        // Create holder
        PUIO* holder_puio = new PUIO(id, world, holderProperties.body_def, EntityCategory::FLOOR);
        b2CircleShape circleShape = box2d::WorldWrapper::createCircleShape({0.0f, 0.0f}, holderProperties.radius);
        holderProperties.fixture_def.shape = &circleShape;
        holder_puio->createFixture(holderProperties.fixture_def);
        holder.reset(holder_puio);

        // Create joint
        b2RevoluteJointDef revoluteJointDef;
        revoluteJointDef.collideConnected = false;
        revoluteJointDef.localAnchorA = {0.0f, 0.0f};
        revoluteJointDef.localAnchorB = {0.0f, 0.0f};
        revoluteJointDef.enableMotor = true;
        revoluteJointDef.maxMotorTorque = motorProperties.max_motor_torque;
        revoluteJointDef.motorSpeed = motorProperties.motor_speed;
        revoluteJointDef.bodyA = blades_puio->body();
        revoluteJointDef.bodyB = holder_puio->body();
        world.getWorld()->CreateJoint(&revoluteJointDef);
    }
};

#endif //TESTC_WINDMILL_H

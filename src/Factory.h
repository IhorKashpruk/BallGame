#ifndef TESTC_FACTORY_H
#define TESTC_FACTORY_H

#include <libs/json.hpp>
#include <utility/primitive_types.h>
#include <ui/physics/PO.h>
#include <ui/physics/WorldUIO.h>
#include <ui/logic/WorldLogic.h>
#include <ui/physics/Windmill.h>
#include <ui/physics/InfluentialPUIO.h>
#include <ui/physics/Influential.h>
#include <ui/physics/Player.h>
#include <ui/physics/ExitDoor.h>

using json = nlohmann::json;

// JSON convertation
namespace pt {

    void to_json(json& j, const point& p) {
        j = json{{"x", p.x}, {"y", p.y}};
    }

    void from_json(const json& j, point& p) {
        p.x = j.at("x").get<int>();
        p.y = j.at("y").get<int>();
    }

    void to_json(json& j, const size& s) {
        j = json{{"w", s.w}, {"h", s.h}};
    }

    void from_json(const json& j, size& s) {
        s.w = j.at("w").get<int>();
        s.h = j.at("h").get<int>();
    }

    void to_json(json& j, const Circle& c) {
        j = json{{"center", c.center}, {"angle", c.angle}, {"radius", c.radius}};
    }

    void from_json(const json& j, Circle& c) {
        c.center = j.at("center").get<point>();
        c.angle = j.at("angle").get<float>();
        c.radius = j.at("radius").get<int>();
    }

    void to_json(json& j, const Rectangle& r) {
        j = json{{"center", r.center}, {"angle", r.angle}, {"size", r.size_}};
    }

    void from_json(const json& j, Rectangle& r) {
        r.center = j.at("center").get<point>();
        r.angle = j.at("angle").get<float>();
        r.size_ = j.at("size").get<size>();
    }

    void to_json(json& j, const Polygon& p) {
        j = json{{"center", p.center}, {"angle", p.angle}, {"points", p.points}};
    }

    void from_json(const json& j, Polygon& p) {
        p.center = j.at("center").get<point>();
        p.angle = j.at("angle").get<float>();
        for(const auto&it: j.at("points")) {
            p.points.push_back({it.at("x").get<int>(), it.at("y").get<int>()});
        }
    }
}

void to_json(json& j, const b2Vec2& vec2) {
    j = json{{"x", vec2.x}, {"y", vec2.y}};
}

void from_json(const json& j, b2Vec2& p) {
    p.x = j.at("x").get<float>();
    p.y = j.at("y").get<float>();
}


void to_json(json& j, const b2BodyDef& bodyDef) {
    j = json{{"type", (int)bodyDef.type}, {"position", bodyDef.position}, {"angle", bodyDef.angle}, {"bullet", bodyDef.bullet}};
}

void from_json(const json& j, b2BodyDef& bodyDef) {
    bodyDef.type = (b2BodyType)j.at("type").get<int>();
    bodyDef.position = j.at("position").get<b2Vec2>();
    bodyDef.angle = j.at("angle").get<float>();
    bodyDef.bullet = j.at("bullet").get<float>();
    bodyDef.fixedRotation = j.at("fixedRotation").get<bool>();
}

void to_json(json& j, const b2CircleShape& circleShape) {
    j = json{{"m_position", circleShape.m_p}, {"m_radius", circleShape.m_radius}};
}

void from_json(const json& j, b2CircleShape& circleShape) {
    circleShape.m_p = j.at("m_position").get<b2Vec2>();
    circleShape.m_radius = j.at("m_radius").get<float>();
}

void to_json(json& j, const b2PolygonShape& polygonShape) {
}

void from_json(const json& j, b2PolygonShape& polygonShape) {
    if(j["points"].size() == 1) {
        for(auto& it: j["points"]) {
            b2Vec2 size = it.get<b2Vec2>();
            b2Vec2 m_center = j["m_center"].get<b2Vec2>();
            polygonShape.SetAsBox(size.x, size.y, m_center, j["angle"]);
        }
    } else {
        std::vector<b2Vec2> tmp;
        for (auto &point: j["points"]) {
            tmp.push_back(point.get<b2Vec2>());
        }
        polygonShape.Set(&tmp[0], (int32)(tmp.size()));
    }
}

void to_json(json& j, const b2FixtureDef& fixtureDef) {
    j = json{{"density", fixtureDef.density}, {"restitution", fixtureDef.restitution}, {"friction", fixtureDef.friction}};
}

void from_json(const json& j, b2FixtureDef& fixtureDef) {
    fixtureDef.density = j.at("density").get<float>();
    fixtureDef.restitution = j.at("restitution").get<float>();
    fixtureDef.friction = j.at("friction").get<float>();
    fixtureDef.filter.categoryBits = j.at("categoryBits").get<uint16>();
    fixtureDef.filter.maskBits = j.at("maskBits").get<uint16>();
    fixtureDef.isSensor = j.at("isSensor").get<bool>();
}

void to_json(json& j, const b2RevoluteJointDef& fixtureDef) {
//    j = json{{"bodyA", ""}, {"bodyB", ""}, {"collideConnected", fixtureDef.collideConnected}, {"localAnchorA", {}}};
}

void from_json(const json& j, b2RevoluteJointDef& revoluteJointDef) {
    revoluteJointDef.collideConnected = j.at("collideConnected").get<bool>();
    revoluteJointDef.localAnchorA = j.at("localAnchorA").get<b2Vec2>();
    revoluteJointDef.localAnchorB = j.at("localAnchorB").get<b2Vec2>();
    revoluteJointDef.enableMotor = j.at("enableMotor").get<bool>();
    revoluteJointDef.maxMotorTorque = j.at("maxMotorTorque").get<float>();
    revoluteJointDef.motorSpeed = j.at("motorSpeed").get<float>();
}


void to_json(json& j, const Player::properties& properties) {
    j = json{{"move_force", properties.move_force}, {"jump_force", properties.jump_force}};
}

void from_json(const json& j, Player::properties& properties) {
    properties.move_force = j.at("move_force").get<float>();
    properties.jump_force = j.at("jump_force").get<float>();
    properties.radius = j.at("radius").get<float>();
}

// Windmill
void to_json(json& j, const Windmill::properties& properties) {
    j = json{};
}

void from_json(const json& j, Windmill::properties& properties) {
}

void to_json(json& j, const Windmill::blades_properties& properties) {
    j = json{};
}

void from_json(const json& j, Windmill::blades_properties& properties) {
    properties.fixture_def = j.at("fixture_def").get<b2FixtureDef>();
    properties.body_def = j.at("body_def").get<b2BodyDef>();
    properties.size = j.at("size").get<b2Vec2>();
}

void to_json(json& j, const Windmill::holder_properties& properties) {
    j = json{};
}

void from_json(const json& j, Windmill::holder_properties& properties) {
    properties.fixture_def = j.at("fixture_def").get<b2FixtureDef>();
    properties.body_def = j.at("body_def").get<b2BodyDef>();
    properties.radius = j.at("radius").get<float>();
}

void to_json(json& j, const Windmill::motor_properties& properties) {
    j = json{};
}

void from_json(const json& j, Windmill::motor_properties& properties) {
    properties.motor_speed = j.at("motorSpeed").get<float>();
    properties.max_motor_torque = j.at("maxMotorTorque").get<float>();
}

// Attractive
void to_json(json& j, const Attractive::properties& properties) {
    j = json{};
}

void from_json(const json& j, Attractive::properties& properties) {
    properties.force = j["force"].get<float>();
}

namespace box2d {
    void to_json(json &j, const WorldWrapper::properties &properties) {
        j = json{};
    }

    void from_json(const json &j, WorldWrapper::properties &properties) {
        properties.gravity = j["gravity"].get<b2Vec2>();
        properties.position_iterations = j["position_iterations"].get<int>();
        properties.velocity_iterations = j["velocity_iterations"].get<int>();
        properties.time_step = j["time_step"].get<float>();
    }
}

namespace factory {

    void addFixture(json& j, PUIO* puio) {
        for (auto& shapes: j) {

            b2FixtureDef fixtureDef = shapes["fixture_def"];

            for (auto& shape : shapes["shapes"]) {
                if(shape["type"] == "circle"){
                    b2CircleShape circleShape = shape.get<b2CircleShape>();
                    fixtureDef.shape = &circleShape;
                    puio->createFixture(fixtureDef);
                }
                if(shape["type"] == "polygon") {
                    b2PolygonShape polygonShape = shape.get<b2PolygonShape>();
                    fixtureDef.shape = &polygonShape;
                    puio->createFixture(fixtureDef);
                }
            }
        }
    }

    template <class Ret>
    Ret* get(json& j, WorldUIO<WorldLogic, pt::Rectangle>& context) {
        return nullptr;
    }

    template <>
    PUIO* get<PUIO>(json& j, WorldUIO<WorldLogic, pt::Rectangle>& context) {
        PUIO* puio = new PUIO(j["id"], *context.getWorld(), j["body_def"], j["category"]);
        addFixture(j["shapes"], puio);
        return puio;
    }

    template <>
    ExitDoor* get<ExitDoor>(json& j, WorldUIO<WorldLogic, pt::Rectangle>& context) {
        ExitDoor* puio = new ExitDoor(j["id"], *context.getWorld(), j["body_def"]);
        addFixture(j["shapes"], puio);
        return puio;
    }

    template <>
    Player* get<Player>(json& j, WorldUIO<WorldLogic, pt::Rectangle>& context) {
        Player* player = new Player(j["id"], *context.getWorld(), j["body_def"], j["fixture_def"], j["properties"]);
        player->attach((IObserver*)context.getCamera());
        context.getCamera()->setCenter(player->shape().center);
        return player;
    }

    template <>
    InfluentialPUIO<Attractive>* get<InfluentialPUIO<Attractive>>(json& j, WorldUIO<WorldLogic, pt::Rectangle>& context) {
        InfluentialPUIO<Attractive>* influentialPUIO = new InfluentialPUIO<Attractive>(j["id"], *context.getWorld(), j["body_def"], j["properties"], j["category"]);
        addFixture(j["shapes"], influentialPUIO);
        return influentialPUIO;
    }

    template <>
    Windmill* get<Windmill>(json& j, WorldUIO<WorldLogic, pt::Rectangle>& context) {
        Windmill* windmill = new Windmill(j["id"], j["properties"], *context.getWorld(), j["blades"], j["holder"], j["motor"]);
        return windmill;
    }

    void buildPUIO(json& j, WorldUIO<WorldLogic, pt::Rectangle>& context) {

        if(j["class"] == "puio") {
            context.add(get<PUIO>(j, context));
            return;
        }
        if(j["class"] == "player") {
            context.add(get<Player>(j, context));
            return;
        }

        if(j["class"] == "windmill") {
            context.add(get<Windmill>(j, context));
            return;
        }
        if(j["class"] == "influentialpuio<attractive>") {
            context.add(get<InfluentialPUIO<Attractive>>(j, context));
        }
        if(j["class"] == "exitdoor") {
            context.add(get<ExitDoor>(j, context));
            return;
        }
    }

    void build(json& j, WorldUIO<WorldLogic, pt::Rectangle>& context) {
        box2d::WorldWrapper::properties properties = j["world_properties"];
        context.resetWorld(new box2d::WorldWrapper(properties));
        for (auto& it: j["puios"]) {
            buildPUIO(it, context);
        }
    }
}

#endif //TESTC_FACTORY_H

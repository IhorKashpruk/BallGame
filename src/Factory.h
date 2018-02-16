#ifndef TESTC_FACTORY_H
#define TESTC_FACTORY_H

#include <libs/json.hpp>
#include <utility/primitive_types.h>
#include <ui/physics/PO.h>
#include <ui/physics/WorldUIO.h>
#include <ui/logic/WorldLogic.h>
#include <ui/physics/Ball.h>
#include <ui/physics/Windmill.h>
#include <ui/physics/InfluentialPUIO.h>
#include <ui/physics/Influential.h>

using json = nlohmann::json;

// JSON convertation
namespace pt {

    template <class T>
    void to_json(json& j, const point<T>& p) {
        j = json{{"x", p.x}, {"y", p.y}};
    }

    template <class T>
    void from_json(const json& j, point<T>& p) {
        p.x = j.at("x").get<T>();
        p.y = j.at("y").get<T>();
    }

    template <class T>
    void to_json(json& j, const size<T>& s) {
        j = json{{"w", s.w}, {"h", s.h}};
    }

    template <class T>
    void from_json(const json& j, size<T>& s) {
        s.w = j.at("w").get<T>();
        s.h = j.at("h").get<T>();
    }

    template <class T>
    void to_json(json& j, const Circle<T>& c) {
        j = json{{"center", c.center}, {"angle", c.angle}, {"radius", c.radius}};
    }

    template <class T>
    void from_json(const json& j, Circle<T>& c) {
        c.center = j.at("center").get<point<T>>();
        c.angle = j.at("angle").get<T>();
        c.radius = j.at("radius").get<T>();
    }

    template <class T>
    void to_json(json& j, const Rectangle<T>& r) {
        j = json{{"center", r.center}, {"angle", r.angle}, {"size", r.size_}};
    }

    template <class T>
    void from_json(const json& j, Rectangle<T>& r) {
        r.center = j.at("center").get<point<T>>();
        r.angle = j.at("angle").get<T>();
        r.size_ = j.at("size").get<size<T>>();
    }


    template <class T>
    void to_json(json& j, const Polygon<T>& p) {
        j = json{{"center", p.center}, {"angle", p.angle}, {"points", p.points}};
    }

    template <class T>
    void from_json(const json& j, Polygon<T>& p) {
        p.center = j.at("center").get<point<T>>();
        p.angle = j.at("angle").get<T>();
        for(const auto&it: j.at("points")) {
            p.points.push_back({it.at("x").get<T>(), it.at("y").get<T>()});
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


void to_json(json& j, const Ball::properties& properties) {
    j = json{{"speed", properties.speed}};
}

void from_json(const json& j, Ball::properties& properties) {
    properties.speed = j.at("speed").get<float>();
}

void to_json(json& j, const Windmill::properties& properties) {
    j = json{};
}

void from_json(const json& j, Windmill::properties& properties) {
}

void to_json(json& j, const Attractive::properties& properties) {
    j = json{};
}

void from_json(const json& j, Attractive::properties& properties) {
    properties.force = j["force"].get<float>();
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
        PUIO* puio = new PUIO(j["id"], *context.getWorld(), j["body_def"]);
        addFixture(j["shapes"], puio);
        return puio;
    }
    template <>
    Ball* get<Ball>(json& j, WorldUIO<WorldLogic, pt::Rectangle>& context) {
        Ball* ball = new Ball(j["id"], *context.getWorld(), j["body_def"], j["properties"]);
        addFixture(j["shapes"], ball);
        return ball;
    }

    template <>
    InfluentialPUIO<Attractive>* get<InfluentialPUIO<Attractive>>(json& j, WorldUIO<WorldLogic, pt::Rectangle>& context) {
        InfluentialPUIO<Attractive>* influentialPUIO = new InfluentialPUIO<Attractive>(j["id"], *context.getWorld(), j["body_def"], j["properties"]);
        addFixture(j["shapes"], influentialPUIO);
        return influentialPUIO;
    }

    template <>
    Windmill* get<Windmill>(json& j, WorldUIO<WorldLogic, pt::Rectangle>& context) {
        Windmill* windmill = new Windmill(j["id"], j["properties"]);

        for (auto& it: j["puios"]) {
            if(it["class"] == "puio") {
                PUIO* puio1 = get<PUIO>(it, context);
                if(puio1->getID() == "blades") {
                    windmill->setBlades(puio1);
                }
                if(puio1->getID() == "holder") {
                    windmill->setHolder(puio1);
                }
            }
        }
        for(auto& it: j["joints"]) {
            if(it["type"] == "revolute") {
                b2RevoluteJointDef revoluteJointDef = it;
                revoluteJointDef.bodyA = windmill->getBlades();
                revoluteJointDef.bodyB = windmill->getHolder();
                context.getWorld()->getWorld()->CreateJoint(&revoluteJointDef);
            }
        }
        return windmill;
    }

    void buildPUIO(json& j, WorldUIO<WorldLogic, pt::Rectangle>& context) {

        if(j["class"] == "puio") {
            context.add(get<PUIO>(j, context));
            return;
        }
        if(j["class"] == "ball") {
            context.add(get<Ball>(j, context));
            return;
        }

        if(j["class"] == "windmill") {
            context.add(get<Windmill>(j, context));
            return;
        }
        if(j["class"] == "influentialpuio<attractive>") {
            context.add(get<InfluentialPUIO<Attractive>>(j, context));
        }
    }

    void build(json& j, WorldUIO<WorldLogic, pt::Rectangle>& context) {
        for (auto& it: j["puios"]) {
            buildPUIO(it, context);
        }
    }
}

#endif //TESTC_FACTORY_H

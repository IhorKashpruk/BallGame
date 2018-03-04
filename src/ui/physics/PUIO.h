#ifndef TESTC_PUIO_H
#define TESTC_PUIO_H

#include <ui/physics/WorldWrapper.h>
#include <ui/physics/PO.h>
#include "ui/UIO.h"
#include "utility/other_things.h"
#include "utility/math_things.h"
#include <ui/interfaces/IContactResponder.h>


enum class EntityCategory {
    PLAYER          = 0x0001,
    FLOOR           = 0x0002,
    PHYSICAL_OBJECT = 0x0003,
    WALL            = 0x0004,
    EXIT            = 0x0009
};

class PUIO : public AUIO, public box2d::PO, public IContactResponder {
    typedef int T;
    typedef pt::point<T> Point;
public:

    explicit PUIO(std::string id,
                   box2d::WorldWrapper& world,
                   b2BodyDef& bodyDef,
                  EntityCategory entityCategory)
            : AUIO(std::move(id)),
              box2d::PO(world, bodyDef),
              IContactResponder(),
              entityCategory_(entityCategory) {
        setUserData((PUIO*)this);
    }
    explicit PUIO(std::string&& id,
                   box2d::WorldWrapper& world,
                   b2BodyDef&& bodyDef,
                  EntityCategory entityCategory)
            : AUIO(std::move(id)),
              box2d::PO(world, bodyDef),
              IContactResponder(),
              entityCategory_(entityCategory) {
        setUserData((PUIO*)this);
    }

    virtual ~PUIO() {
        SDL_Log("Destructor PUIO: %s", id_.c_str());
    };

    void update() override {
        AUIO::update();
    }

    bool under(Point &&point) override {
        return false;
    }

    bool under(const Point &point) override {
        return false;
    }

    Point center() const override {
        return other_things::toPoint(body_->GetPosition());
    }


    float angle() const override {
        return RADIAN_TO_DEGREES(body_->GetAngle());
    }

    void draw() override {
        for(b2Fixture* fixture = body_->GetFixtureList(); fixture; fixture = fixture->GetNext()) {
            b2Shape::Type shapeType = fixture->GetType();
            if (shapeType == b2Shape::e_circle) {

                b2CircleShape* circleShape = (b2CircleShape*)fixture->GetShape();
                b2Vec2 new_center;
                if(circleShape->m_p.x == 0.0f && circleShape->m_p.y == 0.0f) {
                    new_center = body_->GetPosition();
                } else {
                    float angle = other_things::angle(circleShape->m_p);
                    angle += body_->GetAngle();
                    new_center = other_things::rotateb2Vec2(
                            angle,
                            other_things::radius(circleShape->m_p)
                    );
                    new_center.x += body_->GetPosition().x;
                    new_center.y += body_->GetPosition().y;
                }
                pt::Circle<int> circle = other_things::toCircle(
                        {new_center.x,
                         new_center.y},
                        circleShape->m_radius,
                        body_->GetAngle()
                );
                Draftsman::getInstance().draw(circle, colorScheme_);
            }
            else if (shapeType == b2Shape::e_polygon)
            {
                b2PolygonShape* polygonShape = (b2PolygonShape*)fixture->GetShape();
                pt::Polygon<int> polygon;
                if(polygonShape->m_centroid.x == 0.0f && polygonShape->m_centroid.y == 0.0f) {
                    polygon = other_things::toPolygon(
                            body_->GetPosition(),
                            polygonShape->m_vertices,
                            polygonShape->m_count,
                            body_->GetAngle()
                    );
                } else {
                    float angle = other_things::angle(polygonShape->m_centroid) + body_->GetAngle();
                    b2Vec2 new_center = other_things::rotateb2Vec2(
                            angle,
                            other_things::radius(polygonShape->m_centroid)
                    );

                    polygon = other_things::toPolygon(
                            new_center,
                            polygonShape->m_vertices,
                            polygonShape->m_count,
                            body_->GetAngle()
                    );
                }
                Draftsman::getInstance().draw(polygon, colorScheme_);
            }
        }
    }

    void draw(const Point &offset) override {

    }

    void clickLeftButton(const Point& point) override {
        notify(Signal{this, STATE::LEFT_BUTTON_CLICK, point});
    }

    void clickRightButton(const Point& point) override {
        notify(Signal{this, STATE::RIGHT_BUTTON_CLICK, point});
    }

    void enterKey(const char* key) override {
        notify(Signal{this, STATE::ENTER_KEY, key});
    }

    void mouseMove(const Point& point) override {
        notify(Signal{this, STATE::MOUSE_MOVE, point});
    }

    EntityCategory getEntityCategory() const {
        return entityCategory_;
    }

    void beginContact(PUIO* puio, const b2Vec2& point, const b2Fixture& fixture) override {
    }

    void endContact(PUIO* puio, const b2Vec2& point, const b2Fixture& fixture) override {
    }

private:
    EntityCategory entityCategory_;
};

#endif //TESTC_PUIO_H

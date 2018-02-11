#ifndef TESTC_PUIO_H
#define TESTC_PUIO_H

#include <ui/physics/WorldWrapper.h>
#include <ui/physics/PO.h>
#include "UIO.h"
#include "../utility/other_things.h"
#include "../utility/math_things.h"

class PUIO : public AUIO, public box2d::PO {
    typedef int T;
    typedef pt::point<T> Point;
public:

    explicit PUIO(std::string&& id,
                   box2d::WorldWrapper& world,
                   b2BodyDef& bodyDef)
            : AUIO(),
              box2d::PO(world, bodyDef),
              id_(id) {
        setUserData(this);
    }
    explicit PUIO(std::string&& id,
                   box2d::WorldWrapper& world,
                   b2BodyDef&& bodyDef)
            : AUIO(),
              box2d::PO(world, bodyDef),
              id_(id) {
        setUserData(this);
    }

    virtual ~PUIO() {
            SDL_Log("Destructor PUIO: %s", id_.c_str());
    };


    const std::string &id() const override {
        return id_;
    }

    void setColorScheme(const ColorScheme &colorScheme) override {
        colorScheme_ = colorScheme;
    }

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

    void clickLeftButton(const Point &point) override {

    }

    void clickRightButton(const Point &point) override {

    }

    void enterKey(const char *key) override {

    }

    void mouseMove(const Point &point) override {

    }

private:
    std::string id_;
    ColorScheme colorScheme_ = theme::base::all.def;
};

#endif //TESTC_PUIO_H

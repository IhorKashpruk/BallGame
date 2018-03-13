#ifndef TESTC_PUIO_H
#define TESTC_PUIO_H

#include <ui/physics/WorldWrapper.h>
#include <ui/physics/PO.h>
#include "ui/UIO.h"
#include "utility/other_things.h"
#include "utility/math_things.h"
#include <ui/interfaces/IContactResponder.h>
#include <theme_properties.h>


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
        setUserData(this);
    }
    explicit PUIO(std::string&& id,
                   box2d::WorldWrapper& world,
                   b2BodyDef&& bodyDef,
                  EntityCategory entityCategory)
            : AUIO(std::move(id)),
              box2d::PO(world, bodyDef),
              IContactResponder(),
              entityCategory_(entityCategory) {
        setUserData(this);
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

    bool under(const pt::Circle<int> &circle) const override {
        return true;
    }

    bool under(const pt::Rectangle<int> &rectangle) const override {
        return true;
    }

    bool under(const pt::Polygon<int> &polygon) const override {
        return true;
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
                pt::Circle<int> circle = other_things::toCirce(body_, (b2CircleShape*)fixture->GetShape());
                Draftsman::getInstance().draw(circle, colorScheme_);
            }
            else if (shapeType == b2Shape::e_polygon) {
                pt::Polygon<int> polygon = other_things::toPolygon(body_, (b2PolygonShape*)fixture->GetShape());
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
        colorScheme_ = theme::base::all.sel;
    }

    void endContact(PUIO* puio, const b2Vec2& point, const b2Fixture& fixture) override {
        colorScheme_ = theme::base::all.def;
    }

private:
    EntityCategory entityCategory_;
};

#endif //TESTC_PUIO_H

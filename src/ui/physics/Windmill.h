#ifndef TESTC_WINDMILL_H
#define TESTC_WINDMILL_H

#include "ui/physics/PUIO.h"

class Windmill : public AUIO {
    typedef std::unique_ptr<PUIO> puio_ptr;
    typedef int T;
    typedef pt::point<T> Point;
public:

    struct properties {

    };

    explicit Windmill(std::string id, const properties& prop)
            : AUIO(std::move(id)), properties_(prop)  {
    }

    ~Windmill() override = default;

    void setBlades(PUIO* puio) {
        puio->body()->SetUserData(this);
        blades.reset(puio);
    }
    void setHolder(PUIO* puio) {
        holder.reset(puio);
    }

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

    bool under(Point &&point) override {
        return false;
    }

    bool under(const Point &point) override {
        return false;
    }

    Point center() const override {
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

    void draw(const Point &offset) override {

    }

    void clickLeftButton(const Point& point) override {
        notify(Signal{id_, STATE::LEFT_BUTTON_CLICK, point});
    }

    void clickRightButton(const Point& point) override {
        notify(Signal{id_, STATE::RIGHT_BUTTON_CLICK, point});
    }

    void enterKey(const char* key) override {
        notify(Signal{id_, STATE::ENTER_KEY, key});
    }

    void mouseMove(const Point& point) override {
        notify(Signal{id_, STATE::MOUSE_MOVE, point});
    }

private:
    puio_ptr blades  {nullptr};
    puio_ptr holder  {nullptr};
    properties properties_;
};

#endif //TESTC_WINDMILL_H

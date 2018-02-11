#ifndef TESTC_WINDMILL_H
#define TESTC_WINDMILL_H

#include "PUIO.h"

class Windmill : public AUIO {
    typedef std::unique_ptr<PUIO> puio_ptr;
    typedef int T;
    typedef pt::point<T> Point;
public:

    struct properties {

    };

    explicit Windmill(std::string&& id, const properties& prop)
            : AUIO(), id_(std::move(id)), properties_(prop)  {}

    ~Windmill() = default;

    void setBlades(PUIO* puio) {
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

    const std::string &id() const override {
        return id_;
    }

    void setColorScheme(const ColorScheme &colorScheme) override {
        colorScheme_ = colorScheme;
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

    void clickLeftButton(const Point &point) override {

    }

    void clickRightButton(const Point &point) override {

    }

    void enterKey(const char *key) override {

    }

    void mouseMove(const Point &point) override {

    }

private:
    puio_ptr blades  {nullptr};
    puio_ptr holder  {nullptr};
    std::string id_;
    ColorScheme colorScheme_ = theme::base::all.def;
    properties properties_;
};

#endif //TESTC_WINDMILL_H

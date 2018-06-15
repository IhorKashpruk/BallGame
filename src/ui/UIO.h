#ifndef TESTC_UIO_H
#define TESTC_UIO_H

#include <theme_properties.h>
#include <Draftsman.h>
#include <Animation.h>
#include "AUIO.h"
#include "Draftsman.h"


template <class Shape>
class UIO : public AUIO, public LinearAnimation<Shape, 4, false> {
public:
    explicit UIO(std::string id, const Shape& shape)
            : AUIO(std::move(id)),
              LinearAnimation<Shape, 4, false>(100),
              shape_(shape) {}
    explicit UIO(std::string id, Shape&& shape)
            : AUIO(std::move(id)),
              LinearAnimation<Shape, 4, false>(100),
              shape_(shape) {}

    virtual ~UIO() {
        SDL_Log("Destructor UIO: %s", id_.c_str());
    }

    void draw() override {
        Draftsman::getInstance().draw(shape_, colorScheme_);
        if(colorScheme_ == theme::base::all.clk) {
            colorScheme_ = theme::base::all.sel;
        }
        LinearAnimation<Shape, 4, false>::animate();
    }

    void draw(const pt::point& offset) override {

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

    void mouseMove(const pt::point& point) override {
        notify(Signal{this, STATE::MOUSE_MOVE, point});
    }

    bool under(pt::point&& p) override {
        return pt::under(shape_, p);
    }

    bool under(const pt::point& p) override {
        return pt::under(shape_, p);
    }

    bool under(const pt::Circle &circle) const override {
        return true;
    }

    bool under(const pt::Rectangle &rectangle) const override {
        return true;
    }

    bool under(const pt::Polygon &polygon) const override {
        return true;
    }

    pt::point center() const override {
        return shape_.center;
    }

    float angle() const override {
        return shape_.angle;
    }

protected:
    void drawAnimation() override {
        LinearAnimation<Shape, 4, false>::animateShape(shape_, theme::base::all.def);
    }

protected:
    Shape shape_;
};

#endif //TESTC_UIO_H

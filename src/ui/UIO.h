#ifndef TESTC_UIO_H
#define TESTC_UIO_H

#include <theme_properties.h>
#include <Draftsman.h>
#include <Animation.h>
#include "AUIO.h"
#include "Draftsman.h"


template <template <class> class Shape>
class UIO : public AUIO, public LinearAnimation<Shape<int>, 10, false> {
    typedef int T;
    typedef pt::point<T> Point;
public:
    explicit UIO(std::string id, const Shape<T>& shape)
            : AUIO(std::move(id)),
              LinearAnimation<Shape<int>, 10, false>(100),
              shape_(shape) {}
    explicit UIO(std::string id, Shape<T>&& shape)
            : AUIO(std::move(id)),
              LinearAnimation<Shape<int>, 10, false>(100),
              shape_(shape) {}

    virtual ~UIO() {
        SDL_Log("Destructor UIO: %s", id_.c_str());
    }

    void draw() override {
        Draftsman::getInstance().draw(shape_, colorScheme_);
        if(colorScheme_ == theme::base::all.clk) {
            colorScheme_ = theme::base::all.sel;
        }
        LinearAnimation<Shape<int>, 10, false>::animate();
    }

    void draw(const Point& offset) override {

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

    bool under(Point&& point) override {
        return pt::under(shape_, point);
    }

    bool under(const Point& point) override {
        return pt::under(shape_, point);
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
        return shape_.center;
    }

    float angle() const override {
        return shape_.angle;
    }

protected:
    void drawAnimation() override {
        LinearAnimation<Shape<int>, 10, false>::animateShape(shape_, theme::base::all.def);
    }

protected:
    Shape<T> shape_;
};

#endif //TESTC_UIO_H

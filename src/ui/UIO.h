#ifndef TESTC_UIO_H
#define TESTC_UIO_H

#include <theme_properties.h>
#include <Draftsman.h>
#include "AUIO.h"
#include "Draftsman.h"

template <template <class> class Shape>
class UIO : public AUIO {
    typedef int T;
    typedef pt::point<T> Point;
public:
    explicit UIO(std::string id, const Shape<T>& shape)
            : AUIO(std::move(id)),
              shape_(shape) {}
    explicit UIO(std::string id, Shape<T>&& shape)
            : AUIO(std::move(id)),
              shape_(shape) {}

    virtual ~UIO() {
        SDL_Log("Destructor UIO: %s", id_.c_str());
    }

    void draw() override {
        Draftsman::getInstance().draw(shape_, colorScheme_);
        if(colorScheme_ == theme::base::all.clk) {
            colorScheme_ = theme::base::all.sel;
        }
    }

    void draw(const Point& offset) override {

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

    bool under(Point&& point) override {
        return pt::under(shape_, point);
    }

    bool under(const Point& point) override {
        return pt::under(shape_, point);
    }

    Point center() const override {
        return shape_.center;
    }

    float angle() const override {
        return shape_.angle;
    }

protected:
    Shape<T> shape_;
};

#endif //TESTC_UIO_H

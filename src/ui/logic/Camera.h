#ifndef TESTC_CAMERA_H
#define TESTC_CAMERA_H

#include <utility/primitive_types.h>
#include <theme_properties.h>
#include "ALogic.h"

template <class Precision = pt::Rectangle >
class Camera : public ALogic {
public:
    Camera(Precision&& precision, const pt::point& start_position)
            : ALogic(),
              precision_(std::move(precision)),
              start_position_(start_position) {
        precision_.center = start_position_;
    }

    void update(const Signal& signal) override {
        if(signal.getState() == STATE::VALUE_CHANGED) {
            pt::point p = std::any_cast<pt::point>(signal.getValue());
            if(!pt::under(precision_, p)) {
                pt::move(precision_, p);
            }
        }
    }

    pt::point getOffset() const { return (precision_.center - start_position_); }
    void setCenter(const pt::point& p) { precision_.center = p; start_position_ = p; }

private:
    Precision precision_;
    pt::point start_position_;
};

typedef Camera<pt::Rectangle> RectangleCamera;

#endif //TESTC_CAMERA_H

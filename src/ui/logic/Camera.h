#ifndef TESTC_CAMERA_H
#define TESTC_CAMERA_H

#include <utility/primitive_types.h>
#include "ALogic.h"

template <
        template <class> class Shape = pt::Rectangle,
        template <class> class Precision = pt::Rectangle >
class Camera : public ALogic {
    typedef pt::point<int> Point;
public:
    Camera(const Shape<int>& shape, Precision<int>&& precision, const Point& start_position)
            : ALogic(),
              shape_(shape),
              precision_(std::move(precision)),
              start_position_(start_position) {
        shape_.center = start_position_;
        precision_.center = start_position_;
    }

    void update(const Signal& signal) override {
        if(signal.getState() == STATE::VALUE_CHANGED) {
            Point point = std::any_cast<Point>(signal.getValue());
            if(!pt::under(precision_, point)) {
                pt::move(precision_, point);
                shape_.center = precision_.center;
            }
        }
    }

    Shape<int>& getShape() const { return shape_; }
    Point getOffset() const { return (shape_.center - start_position_); }

private:
    Shape<int> shape_;
    Precision<int> precision_;
    const Point start_position_;
};

typedef Camera<pt::Rectangle, pt::Rectangle> RectangleCamera;

#endif //TESTC_CAMERA_H

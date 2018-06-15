#ifndef TESTC_PRIMITIVE_TYPES_H
#define TESTC_PRIMITIVE_TYPES_H

#include <type_traits>
#include <utility>
#include <vector>
#include <algorithm>
#include "math_things.h"

namespace pt {
    struct size {
        int w, h;
        size operator+(const size& l) {
            return size { w + l.w, h + l.h};
        }
    };

    struct point {
        int x, y;
        point operator+(const point& p) const {
            return { x + p.x, y + p.y };
        }
        point operator-(const point& p) const {
            return { x - p.x, y - p.y };
        }
        point operator*(const point& p) const {
            return { x * p.x, y + p.y };
        }
        point operator/(const point& p) const {
            return { x / p.x, y / p.y };
        }
        point& operator+=(const point& p) {
            x += p.x;
            y += p.y;
            return *this;
        }
        point& operator-=(const point& p) {
            x -= p.x;
            y -= p.y;
            return *this;
        }
    };

    struct Shape {
        explicit Shape(point center, float angle)
                : center(std::move(center)), angle(angle) {}
        Shape() = default;
        virtual ~Shape() = default;
        point center;
        float angle;
    };

    struct Circle : public Shape {
        Circle(point center, float angle, int radius)
                : Shape(center, angle),
                  radius(radius) {}
        Circle() = default;
        int radius;
    };

    struct Rectangle : public Shape {
        Rectangle(point center, float angle, size size)
                : Shape(center, angle),
                  size_(size) {}
        Rectangle() = default;
        size size_;
    };

    struct Polygon : public Shape {
        template <class ...P>
        Polygon(point center, float angle, P&&... points)
                : Shape(center, angle), points{std::move(points)...} {}
        template <class ...P>
        Polygon(point center, float angle, P&... points)
                : Shape(center, angle), points{(points)...} {}
        Polygon(point center, float angle, std::vector<point>&& points)
                : Shape(center, angle), points{std::move(points)} {}
        Polygon() = default;
        std::vector<point> points {};
    };

    bool inside(const int target, const int lh, const int rh) {
        return (target >= lh && target <= rh);
    }

    float distance(const point& p1, const point& p2) {
        return std::sqrt((float)(p2.x - p1.x) * (p2.x - p1.x)
                         + (p2.y - p1.y) * (p2.y - p1.y));
    }

    inline int distance(const int& p1, const int& p2) {
        return std::abs(p1 - p2);
    }

    bool under(const Circle& circle, const point& p) {
        return (distance(circle.center, p) <= circle.radius);
    }

    bool under(Circle&& circle, const point& p) {
        return under(circle, p);
    }

    bool under(const Circle& circle, point&& p) {
        return under(circle, p);
    }
    bool under(Circle&& circle, point&& p) {
        return under(circle, p);
    }

    bool under(const Rectangle& rectangle, const point& p) {
        return (inside(p.x, rectangle.center.x - rectangle.size_.w, rectangle.center.x + rectangle.size_.w))
               && (inside(p.y, rectangle.center.y - rectangle.size_.h, rectangle.center.y + rectangle.size_.h));
        point p2 = {rectangle.center.x + rectangle.size_.w, rectangle.center.y + rectangle.size_.h};
        if(!under(Circle{rectangle.center,
                         rectangle.angle,
                         (int)std::round(distance(rectangle.center, p2))}, p)) {
            return false;
        }
        return ((distance(rectangle.center.x, p.x) < rectangle.size_.w)
               && (distance(rectangle.center.y, p.y) < rectangle.size_.h));
    }
    bool under(const Rectangle& rectangle, point&& p) {
        return under(rectangle, p);
    }
    bool under(Rectangle&& rectangle, const point& p) {
        return under(rectangle, p);
    }
    bool under(Rectangle&& rectangle, point&& p) {
        return under(rectangle, p);
    }

    bool under(const Polygon& polygon, const point& p) {
        auto max = [](const std::vector<pt::point>& points) -> int {
            int max_value = 0;
            for(const pt::point& p2: points){
                auto max_tmp1 = std::max(std::abs(p2.x), std::abs(p2.y));
                max_value = std::max(max_value, max_tmp1);
            }
            return max_value;
        };

        if(!under(Circle {polygon.center,
                          polygon.angle,
                          max(polygon.points)}, p)) {
            return false;
        }

        return false;
    }

    bool under(Polygon&& polygon, const point& p) {
        return under(polygon, p);
    }
    bool under(const Polygon& polygon, point&& p) {
        return under(polygon, p);
    }
    bool under(Polygon&& polygon, point&& p) {
        return under(polygon, p);
    }

    void move(Circle& circle, const point& p) {
        point p2 = p;
        p2.y = circle.center.y;
        if(!under(circle, p2)) {
            circle.center.x +=
                    (p.x -
                     ((p.x > circle.center.x)
                      ? (circle.radius + circle.center.x)
                      : (circle.center.x - circle.radius)));
        }
        p2.y = p.y;
        p2.x = circle.center.x;
        if(!under(circle, p2)) {
            circle.center.y +=
                    (p.y -
                            ((p.y > circle.center.y)
                             ? (circle.radius + circle.center.y)
                             : (circle.center.y - circle.radius)));
        }
    }

    void move(Rectangle& rectangle, const point& p) {
        if(!inside(p.x, (rectangle.center.x - rectangle.size_.w), (rectangle.center.x + rectangle.size_.w))) {
            rectangle.center.x +=
                    (p.x -
                            ((p.x > rectangle.center.x)
                             ? (rectangle.size_.w + rectangle.center.x)
                             : (rectangle.center.x - rectangle.size_.w)));
        }
        if(!inside(p.y, (rectangle.center.y - rectangle.size_.h), (rectangle.center.y + rectangle.size_.h))) {
            rectangle.center.y +=
                    (p.y -
                            ((p.y > rectangle.center.y)
                             ? (rectangle.size_.h + rectangle.center.y)
                             : (rectangle.center.y - rectangle.size_.h)));
        }
    }

    bool under(const Rectangle& rec1, const Rectangle& rec2) {
        return !(((rec1.center.x + rec1.size_.w) > (rec2.center.x - rec2.size_.w))
                 || ((rec1.center.x - rec1.size_.w) > (rec2.center.x + rec2.size_.w))
                 || ((rec1.center.y - rec1.size_.h) > (rec2.center.y + rec2.size_.h))
                 || ((rec1.center.y + rec1.size_.h) > (rec2.center.y - rec2.size_.h)));
    }
}

#endif //TESTC_PRIMITIVE_TYPES_H

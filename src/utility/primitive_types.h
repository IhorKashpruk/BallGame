#ifndef TESTC_PRIMITIVE_TYPES_H
#define TESTC_PRIMITIVE_TYPES_H

#include <type_traits>
#include <utility>
#include <vector>
#include <algorithm>
#include "math_things.h"

namespace pt {
    template<typename T = int>
    struct size {
        T w, h;
        size<T> operator+(const size& l) {
            return size<T> { w + l.w, h + l.h};
        }
    };

    template<typename T = int>
    struct point {
        T x, y;
    };

    template<class T>
    struct Shape {
        static_assert(std::is_arithmetic<T>::value,
                      "T must be arithmetic types.\n");
        typedef point<T> Point;
        explicit Shape(Point center, float angle)
                : center(std::move(center)), angle(angle) {}
        Shape() = default;
        virtual ~Shape() = default;
        Point center;
        float angle;
    };

    template<class T>
    struct Circle : public Shape<T> {
        Circle(typename Shape<T>::Point center, float angle, T radius)
                : Shape<T>(center, angle),
                  radius(radius) {}
        Circle() = default;
        T radius;
    };

    template <class T>
    struct Rectangle : public Shape<T> {
        typedef size<T> Size;
        Rectangle(typename Shape<T>::Point center, float angle, Size size)
                : Shape<T>(center, angle),
                  size_(size) {}
        Rectangle() = default;
        Size size_;
    };

    template <class T>
    struct Polygon : public Shape<T> {
        template <template <class> class ...P>
        Polygon(typename Shape<T>::Point center, float angle, P<T>&&... points)
                : Shape<T>(center, angle), points{std::move(points)...} {}
        template <template <class> class ...P>
        Polygon(typename Shape<T>::Point center, float angle, P<T>&... points)
                : Shape<T>(center, angle), points{(points)...} {}
        Polygon(typename Shape<T>::Point center, float angle, std::vector<typename Shape<T>::Point>&& points)
                : Shape<T>(center, angle), points{std::move(points)} {}
        Polygon() = default;
        std::vector<typename Shape<T>::Point> points {};
    };

    template <class T>
    T distance(const pt::point<T> &p1, const pt::point<T> &p2) {
        return std::sqrt((p2.x - p1.x) * (p2.x - p1.x)
                         + (p2.y - p1.y) * (p2.y - p1.y));
    }

    inline int distance(const int& p1, const int& p2) {
        return std::abs(p1 - p2);
    }

    bool under(const Circle<int>& circle, const point<int>& point) {
        return (distance(circle.center, point) <= circle.radius);
    }

    bool under(Circle<int>&& circle, const point<int>& point) {
        return under(circle, point);
    }

    bool under(const Circle<int>& circle, point<int>&& point) {
        return under(circle, point);
    }
    bool under(Circle<int>&& circle, point<int>&& point) {
        return under(circle, point);
    }

    bool under(const Rectangle<int>& rectangle, const point<int>& point) {
        pt::point<int> p = {rectangle.center.x + rectangle.size_.w, rectangle.center.y + rectangle.size_.h};
        if(!under(Circle<int>{rectangle.center,
                              rectangle.angle,
                              distance(rectangle.center, p)}, point)) {
            return false;
        }
        return ((distance(rectangle.center.x, point.x) < rectangle.size_.w)
               && (distance(rectangle.center.y, point.y) < rectangle.size_.h));
    }
    bool under(const Rectangle<int>& rectangle, point<int>&& point) {
        return under(rectangle, point);
    }
    bool under(Rectangle<int>&& rectangle, const point<int>& point) {
        return under(rectangle, point);
    }
    bool under(Rectangle<int>&& rectangle, point<int>&& point) {
        return under(rectangle, point);
    }

    bool under(const Polygon<int>& polygon, const point<int>& point) {
        auto max = [](const std::vector<pt::point<int>>& points) -> int {
            int max_value = 0;
            for(const pt::point<int> p: points){
                auto max_tmp1 = std::max(std::abs(p.x), std::abs(p.y));
                max_value = std::max(max_value, max_tmp1);
            }
            return max_value;
        };

        if(!under(Circle<int>{polygon.center,
                              polygon.angle,
                              max(polygon.points)}, point)) {
            return false;
        }

        return false;
    }

    bool under(Polygon<int>&& polygon, const point<int>& point) {
        return under(polygon, point);
    }
    bool under(const Polygon<int>& polygon, point<int>&& point) {
        return under(polygon, point);
    }
    bool under(Polygon<int>&& polygon, point<int>&& point) {
        return under(polygon, point);
    }

    template <class from, class to>
    point<to> convert(const point<from>& point, to (*conv_f)(from)) {
        return {conv_f(point.x), conv_f(point.y)};
    }

    template <class from, class to>
    size<to> convert(const size<from>& point, to (*conv_f)(from)) {
        return {conv_f(point.w), conv_f(point.h)};
    }

    template <class from, class to>
    std::vector<pt::point<to>> convert(const std::vector<pt::point<from>>& points, to (*conv_f)(from)) {
        std::vector<pt::point<to>> tmp;
        tmp.resize(points.size());
        std::transform(points.begin(), points.end(), tmp.begin(),
                       [&conv_f](const pt::point<from>& it) -> pt::point<to> {
                           return {conv_f(it.x), conv_f(it.y)};
                       }
        );
        return tmp;
    }

    template <class from, class to>
    Circle<to> convert(const Circle<from>& circle, to (*conv_f)(from), float (*conv_f_a)(from)) {
        return {convert(circle.center, conv_f), conv_f_a(circle.angle), conv_f(circle.radius)};
    }

    template <class from, class to>
    Rectangle<to> convert(const Rectangle<from>& rectangle, to (*conv_f)(from), float (*conv_f_a)(from)) {
        return {convert(rectangle.center, conv_f), conv_f_a(rectangle.angle), convert(rectangle.size_, conv_f)};
    }
    template <class from, class to>
    Polygon<to> convert(const Polygon<from>& poligon, to (*conv_f)(from), float (*conv_f_a)(from)) {
        return {convert(poligon.center, conv_f), conv_f_a(poligon.angle), convert(poligon.points, conv_f)};
    }
}

#endif //TESTC_PRIMITIVE_TYPES_H

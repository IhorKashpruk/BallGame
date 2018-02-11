#ifndef TESTC_OTHER_THINGS_H
#define TESTC_OTHER_THINGS_H

#include "primitive_types.h"
#include "P_P_M.h"
#include "math_things.h"
#include <libs/Box2D/Common/b2Math.h>


namespace other_things {

#define DEGREES_TO_RADIANS 0.01745329251
#define MY_PI 3.14159265359
#define SIN_TO_DEGREES(value) (asin(value)*180.0f/MY_PI)
#define MY_PI_DIVIVDE_2 1.5707963268f

#define NOW_YOU_ARE_SINGELTON(className) \
private:\
className() = default;\
className(const className&) = delete;\
className&operator=(const className&) = delete;\
public:\
static className& getInstance() {\
static className instance;\
return instance;}

#define PRINT_ERROR(function_name, error) \
    (SDL_Log("Error in function: '%s': %s.\n", function_name, error))


    template <class from, class to>
    pt::Circle<to> convert(const pt::Circle<from>& circle) {
        return pt::convert(circle, &P_P_M_50::convert, &math_things::convert<to>);
    }

    template <class from, class to>
    pt::Rectangle<to> convert(const pt::Rectangle<from>& rectangle) {
        return pt::convert(rectangle, &P_P_M_50::convert, &math_things::convert<to>);
    }

    template <class from, class to>
    pt::Polygon<to> convert(const pt::Polygon<from>& polygon) {
        return pt::convert(polygon, &P_P_M_50::convert, &math_things::convert<to>);
    }

    template <class from, class to>
    pt::point<to> convert(const pt::point<from>& point) {
        return pt::convert(point, &P_P_M_50::convert);
    }

    template <class from, class to>
    pt::point<to> convert(pt::point<from>&& point) {
        return pt::convert(point, &P_P_M_50::convert);
    }

    pt::point<int> toPoint(const b2Vec2& center, bool m = false) {
        return {P_P_M_50::convert(center.x), P_P_M_50::convert(center.y* (m ? 1.0f : -1.0f))};
    }

    pt::Circle<int> toCircle(const b2Vec2& center, const float& radius, const float& angle) {
        pt::Circle<int> ret;
        ret.center = toPoint(center);
        ret.radius = P_P_M_50::convert(radius);
        ret.angle = RADIAN_TO_DEGREES(angle);
        return ret;
    }

    pt::Circle<int> toCircle(b2Vec2&& center, const float& radius, const float& angle) {
        pt::Circle<int> ret;
        ret.center = toPoint(center);
        ret.radius = P_P_M_50::convert(radius);
        ret.angle = RADIAN_TO_DEGREES(angle);
        return ret;
    }


    b2Vec2 rotateb2Vec2(const float angle, const float radius) {
        b2Vec2 ret;
        ret.x = std::cos(angle) * radius;
        ret.y = std::sin(angle) * radius;
        return ret;
    }
    pt::point<int> rotatePointInt(const float angle, const float radius) {
        pt::point<int> ret;
        ret.x = (int)math_things::normalize(std::cos(angle) * radius);
        ret.y = (int)math_things::normalize(std::sin(angle) * radius);
        return ret;
    }

    template <class T>
    float angle(T&& p) {
        float angle = std::atan2(p.y, p.x);
        angle = (angle < 0) ? angle + 6.2831853072f : angle;
        return angle;
    }

    template <class T>
    float radius(T&& p) {
        return std::sqrt(p.x*p.x + p.y*p.y);
    }


    pt::Polygon<int> toPolygon(const b2Vec2& center, const b2Vec2* vec2, const int count, const float angle) {
        pt::Polygon<int> polygon;
        polygon.center = {P_P_M_50::convert(center.x), P_P_M_50::convert(center.y*-1.0f)};
        polygon.angle = RADIAN_TO_DEGREES(angle);
        for(int i = 0; i < count; i++) {
            polygon.points.push_back(
                    {P_P_M_50::convert(vec2[i].x),
                     P_P_M_50::convert(vec2[i].y)*-1}
            );
        }
        return polygon;
    }


    b2Vec2 calculateForce(const pt::point<int>& point, const pt::Circle<int>& shape, const float& speed) {

        pt::point<int> tmp_p = {point.x-shape.center.x, -(point.y-shape.center.y)};
        pt::point<int> tmp_p_a = {abs(tmp_p.x), abs(tmp_p.y)};

        auto g_s = [](int value) -> float { return value < 0 ? -1.0f : 1.0f; };

        if(under(shape, point)) {
            return {0.0f,0.0f};
        } else {
            float x_speed, y_speed;

            float hypotenuse = sqrt((float)(tmp_p_a.x*tmp_p_a.x + tmp_p_a.y*tmp_p_a.y));
            float sin_a = (float)tmp_p_a.y / hypotenuse;
            float angle = SIN_TO_DEGREES(sin_a);

            y_speed = sin(angle*DEGREES_TO_RADIANS) * speed * g_s(tmp_p.y);
            x_speed = sin((90-angle)*DEGREES_TO_RADIANS) * speed * g_s(tmp_p.x);

            return {x_speed, y_speed};
        }
    }
}
#endif //TESTC_OTHER_THINGS_H

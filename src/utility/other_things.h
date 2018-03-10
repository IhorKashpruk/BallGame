#ifndef TESTC_OTHER_THINGS_H
#define TESTC_OTHER_THINGS_H

#include "primitive_types.h"
#include "P_P_M.h"
#include "math_things.h"
#include <libs/Box2D/Common/b2Math.h>
#include <libs/Box2D/Collision/Shapes/b2Shape.h>
#include <libs/Box2D/Dynamics/b2Body.h>
#include <libs/Box2D/Collision/Shapes/b2CircleShape.h>
#include <libs/Box2D/Collision/Shapes/b2PolygonShape.h>


namespace other_things {

#define NOW_YOU_ARE_SINGLETON(className) \
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

    b2Vec2 toPoint(const pt::point<int>& point) {
        return {P_P_M_50::convert(point.x), P_P_M_50::convert(point.y * -1)};
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

    b2Vec2 calculateForce(const b2Vec2& point1, const b2Vec2& point2, const float& speed) {
        b2Vec2 module{point2.x - point1.x, point2.y - point1.y};
        float full_len = std::sqrt((module.x * module.x) + (module.y * module.y));
        return {(module.x * (speed / full_len)),
                (module.y * (speed / full_len))};
    }

    pt::Circle<int> toCirce(const b2Body* body, const b2CircleShape* circleShape) {
        b2Vec2 new_center;
        if(circleShape->m_p.x == 0.0f && circleShape->m_p.y == 0.0f) {
            new_center = body->GetPosition();
        } else {
            float angle = other_things::angle(circleShape->m_p);
            angle += body->GetAngle();
            new_center = other_things::rotateb2Vec2(
                    angle,
                    other_things::radius(circleShape->m_p)
            );
            new_center += body->GetPosition();
        }
        return other_things::toCircle(
                new_center,
                circleShape->m_radius,
                body->GetAngle()
        );
    }

    pt::Polygon<int> toPolygon(const b2Body* body, const b2PolygonShape* polygonShape) {
        pt::Polygon<int> polygon;
        if(polygonShape->m_centroid.x == 0.0f && polygonShape->m_centroid.y == 0.0f) {
            polygon = other_things::toPolygon(
                    body->GetPosition(),
                    polygonShape->m_vertices,
                    polygonShape->m_count,
                    body->GetAngle()
            );
        } else {
            float angle = other_things::angle(polygonShape->m_centroid) + body->GetAngle();
            b2Vec2 new_center = other_things::rotateb2Vec2(
                    angle,
                    other_things::radius(polygonShape->m_centroid)
            );

            polygon = other_things::toPolygon(
                    new_center,
                    polygonShape->m_vertices,
                    polygonShape->m_count,
                    body->GetAngle()
            );
        }
        return polygon;
    }
}
#endif //TESTC_OTHER_THINGS_H

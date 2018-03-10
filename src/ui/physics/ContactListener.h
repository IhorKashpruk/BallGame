#ifndef TESTC_CONTACTLISTENER_H
#define TESTC_CONTACTLISTENER_H

#include <libs/Box2D/Box2D.h>
#include "Influential.h"
#include "InfluentialPUIO.h"

namespace box2d {
    class ContactListener : public b2ContactListener
    {
        void BeginContact(b2Contact* contact) override {

            void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
            void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
            if(!bodyUserDataA || !bodyUserDataB) {
                return;
            }


            PUIO* puio1 = static_cast<PUIO*>(bodyUserDataA);
            PUIO* puio2 = static_cast<PUIO*>(bodyUserDataB);
            contact->GetWorldManifold(&worldManifold);

            // Find the contact point
            b2Vec2 point = getContactPoint(contact);

            puio1->beginContact(puio2, point, *contact->GetFixtureB());
            puio2->beginContact(puio1, point, *contact->GetFixtureA());
        }

        void EndContact(b2Contact* contact) override {
            void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
            void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
            if(!bodyUserDataA || !bodyUserDataB) {
                return;
            }

            PUIO* puio1 = static_cast<PUIO*>(bodyUserDataA);
            PUIO* puio2 = static_cast<PUIO*>(bodyUserDataB);
            contact->GetWorldManifold(&worldManifold);

            // Find the contact point
            b2Vec2 point = getContactPoint(contact);

            puio1->endContact(puio2, point, *contact->GetFixtureB());
            puio2->endContact(puio1, point, *contact->GetFixtureA());
        }

    private:
        b2WorldManifold worldManifold;

        b2Vec2 calculateContactPoint(const b2Vec2& p1, const b2Vec2& p2) {
            return {(worldManifold.points[0].x + worldManifold.points[1].x)/2.0f,
                    (worldManifold.points[0].y + worldManifold.points[1].y)/2.0f};
        }

        b2Vec2 getContactPoint(b2Contact* contact) {
            b2Vec2 point = worldManifold.points[0];
            if(contact->GetManifold()->pointCount == 2) {
                point = calculateContactPoint(worldManifold.points[0], worldManifold.points[1]);
            }
            return point;
        }
    };
}

#endif //TESTC_CONTACTLISTENER_H

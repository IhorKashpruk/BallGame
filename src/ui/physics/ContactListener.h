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
            puio1->beginContact(puio2, worldManifold.points[0], *contact->GetFixtureB());
            puio2->beginContact(puio1, worldManifold.points[0], *contact->GetFixtureA());
//            if(contact->GetFixtureA()->IsSensor()) {
//                IInfluential *influential = static_cast<IInfluential*>(bodyUserDataA);
//                influential->add(puio2);
//            }
//
//            if(contact->GetFixtureB()->IsSensor()) {
//                AInfluential *influential = static_cast<AInfluential*>(bodyUserDataB);
//                influential->add(puio1);
//            }
//
//            // Check if ball on the ground
//            if(puio1->getEntityCategory() == EntityCategory::PLAYER && puio2->getEntityCategory() == EntityCategory::FLOOR) {
//                Ball* ball = static_cast<Ball*>(puio1);
//                ball->onGround(true);
//            }
//            if(puio2->getEntityCategory() == EntityCategory::PLAYER && puio1->getEntityCategory() == EntityCategory::FLOOR) {
//                Ball* ball = static_cast<Ball*>(puio2);
//                ball->onGround(true);
//            }
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
            puio1->endContact(puio2, worldManifold.points[0], *contact->GetFixtureB());
            puio2->endContact(puio1, worldManifold.points[0], *contact->GetFixtureA());
//
//            if(contact->GetFixtureA()->IsSensor()) {
//                IInfluential *influential = static_cast<IInfluential*>(bodyUserDataA);
//                influential->remove(puio2);
//            }
//
//            if(contact->GetFixtureB()->IsSensor()) {
//                AInfluential *influential = static_cast<AInfluential*>(bodyUserDataB);
//                influential->remove(puio1);
//            }
//
//            // Check if ball on the ground
//            if(puio1->getEntityCategory() == EntityCategory::PLAYER && puio2->getEntityCategory() == EntityCategory::FLOOR) {
//                Ball* ball = static_cast<Ball*>(puio1);
//                ball->onGround(false);
//            }
//            if(puio2->getEntityCategory() == EntityCategory::PLAYER && puio1->getEntityCategory() == EntityCategory::FLOOR) {
//                Ball* ball = static_cast<Ball*>(puio2);
//                ball->onGround(false);
//            }
        }

    private:
        b2WorldManifold worldManifold;
    };
}

#endif //TESTC_CONTACTLISTENER_H

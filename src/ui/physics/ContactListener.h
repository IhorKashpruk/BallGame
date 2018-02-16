#ifndef TESTC_CONTACTLISTENER_H
#define TESTC_CONTACTLISTENER_H

#include <libs/Box2D/Box2D.h>
#include "Influential.h"
#include "InfluentialPUIO.h"

namespace box2d {
    class ContactListener : public b2ContactListener
    {
        void BeginContact(b2Contact* contact) override {

            if(contact->GetFixtureA()->IsSensor()) {
                void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
                void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
                if(bodyUserDataA && bodyUserDataB) {
                    IInfluential *influential = static_cast<IInfluential*>(bodyUserDataA);
                    PUIO *puio = static_cast<PUIO*>(bodyUserDataB);
                    influential->add(puio);
                }
            }

            if(contact->GetFixtureB()->IsSensor()) {
                void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
                void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
                if(bodyUserDataA && bodyUserDataB) {
                    AInfluential *influential = static_cast<AInfluential*>(bodyUserDataB);
                    PUIO *puio = static_cast<PUIO*>(bodyUserDataA);
                    influential->add(puio);
                }
            }
        }

        void EndContact(b2Contact* contact) override {
            if(contact->GetFixtureA()->IsSensor()) {
                void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
                void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
                IInfluential* influential = static_cast<IInfluential*>(bodyUserDataA);
                PUIO* puio = static_cast<PUIO*>(bodyUserDataB);
                influential->remove(puio);
            }

            if(contact->GetFixtureB()->IsSensor()) {
                void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
                void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
                IInfluential* influential = static_cast<IInfluential*>(bodyUserDataB);
                PUIO* puio = static_cast<PUIO*>(bodyUserDataA);
                influential->remove(puio);
            }
        }
    };
}

#endif //TESTC_CONTACTLISTENER_H

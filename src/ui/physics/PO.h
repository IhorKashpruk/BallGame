#ifndef TESTC_PO_H
#define TESTC_PO_H

#include <utility/primitive_types.h>
#include "WorldWrapper.h"

namespace box2d {

    class PO {
    public:
        explicit PO(WorldWrapper& world, b2BodyDef& bodyDef) {
            body_ = world.getWorld()->CreateBody(&bodyDef);
        }
        virtual ~PO() {
            if(body_ && body_->GetWorld()) {
                body_->GetWorld()->DestroyBody(body_);
            }
        };

        void setUserData(void* data) {
            if(body_) {
                SDL_Log("Set user data");
                body_->SetUserData(data);
            }
        }

        void createFixture(const b2FixtureDef& fixtureDef) {
            if(body_) {
                body_->CreateFixture(&fixtureDef);
            }
        }

        b2Body* body() { return body_; }

    protected:
        b2Body* body_;
    };
}
#endif //TESTC_PO_H

#ifndef TESTC_INFLUENTIAL_H
#define TESTC_INFLUENTIAL_H

#include "PUIO.h"

class IInfluential {
public:
    virtual IInfluential() = default;

    virtual void add(PUIO* puio) = 0;
    virtual void remove(PUIO* puio) = 0;
    virtual bool has(PUIO* puio) = 0;
    virtual void update() = 0;
    virtual void work() = 0;
};

class AInfluential : public IInfluential {
public:
    explicit AInfluential() : IInfluential() {}
    virtual ~AInfluential() = default;
    void add(PUIO *puio) override {
        if(puio) { puios_.push_back(puio); }
    }

    void remove(PUIO *puio) override {
        if(puio) { puios_.erase(std::find(puios_.begin(), puios_.end(), puio)); }
    }

    bool has(PUIO *puio) override {
        return (std::find(puios_.begin(), puios_.end(), puio) != puios_.end());
    }

    void setOwner(PUIO* owner) {
        if(owner) { owner_ = owner;}
    }

protected:
    std::vector<PUIO*> puios_ {};
    PUIO* owner_ { nullptr };
};


class Attractive : public AInfluential {
public:
    struct properties {
        float force;
    };
    explicit Attractive(const properties& prop) : AInfluential(),  properties_(prop) {}
    explicit Attractive(properties&& prop) :  AInfluential(), properties_(std::move(prop)) {}

    void update() override {
    }

    void work() override {
        if(!owner_) { return; }
        for(auto& puio: puios_) {
            puio->body()->ApplyForceToCenter(
                    other_things::calculateForce(
                            owner_->body()->GetPosition(),
                            puio->body()->GetPosition(),
                            properties_.force),
                    true);
        }
    }

protected:
    properties properties_;
};

#endif //TESTC_INFLUENTIAL_H

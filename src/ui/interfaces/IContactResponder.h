#ifndef TESTC_ICONTACTRESPONDER_H
#define TESTC_ICONTACTRESPONDER_H

class PUIO;
class IContactResponder {
public:
    virtual ~IContactResponder() {};
    virtual void beginContact(PUIO* puio, const b2Vec2& point, const b2Fixture& fixture) = 0;
    virtual void endContact(PUIO* puio, const b2Vec2& point, const b2Fixture& fixture) = 0;
};

#endif //TESTC_ICONTACTRESPONDER_H

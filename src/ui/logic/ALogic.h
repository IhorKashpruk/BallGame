//
// Created by ihor on 10.01.18.
//

#ifndef MYGAME_LOGIC_H
#define MYGAME_LOGIC_H

#include "IObserver.h"
#include "Subject.h"

class Context;
class AContextLogic : public IObserver, public Subject {
public:
    explicit AContextLogic(Context* context) : context_(context) {}
    virtual ~AContextLogic() = default;
protected:
    Context* context_;
};

class ALogic : public IObserver, public Subject {
public:
    explicit ALogic() = default;
    virtual ~ALogic() = default;
protected:
};

#endif //MYGAME_LOGIC_H

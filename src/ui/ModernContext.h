#ifndef TESTC_MODERNCONTEXT_H
#define TESTC_MODERNCONTEXT_H

#include "Context.h"

template <class Logic>
class ModernContext : public Context {
public:
    explicit ModernContext() : Context() {
        resetLogic(new Logic(this));
    }

    virtual ~ModernContext() = default;
};


template <class Logic>
class ModernIdentityContext : public IdentityContext {
public:
    explicit ModernIdentityContext(std::string id) : IdentityContext(std::move(id)) {
        resetLogic(new Logic(this));
    }

    virtual ~ModernIdentityContext() = default;
};

#endif //TESTC_MODERNCONTEXT_H

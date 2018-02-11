#ifndef TESTC_MODERNCONTEXT_H
#define TESTC_MODERNCONTEXT_H

#include "Context.h"

template <class Logic>
class ModernContext : public Context {
public:
    explicit ModernContext(std::string id) : Context(std::move(id)) {
        resetLogic(new Logic(this));
    }

    ~ModernContext() = default;
};

#endif //TESTC_MODERNCONTEXT_H

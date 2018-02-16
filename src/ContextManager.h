#ifndef TESTC_CONTEXTMANAGER_H
#define TESTC_CONTEXTMANAGER_H

#include "utility/other_things.h"
#include "ui/Context.h"

class ContextManager {
    NOW_YOU_ARE_SINGLETON(ContextManager)
    typedef std::shared_ptr<IdentityContext>    context_ptr;
    typedef std::weak_ptr<IdentityContext>      weak_context_ptr;
    typedef std::vector<context_ptr>            vector_context_ptr;
public:
    ContextManager& add(IdentityContext* context) {
        contexts_.push_back(context_ptr(context));
        return *this;
    }
    weak_context_ptr getCurrentContext() {
        return currentContext_;
    }
    unsigned long size() const { return contexts_.size(); }

    void setCurrentContext(std::string&& id) {
        for(auto& context: contexts_) {
            if(context->getID() == id) {
                currentContext_ = context;
            }
        }
    }

    Context* get(std::string&& id) {
        for(auto& context: contexts_) {
            if(context->getID() == id) {
                return &*context;
            }
        }
        return nullptr;
    }

private:
    vector_context_ptr contexts_{};
    weak_context_ptr currentContext_{};
};


#endif //TESTC_CONTEXTMANAGER_H

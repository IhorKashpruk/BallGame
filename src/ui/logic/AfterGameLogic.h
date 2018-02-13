#ifndef TESTC_AFTERGAMELOGIC_H
#define TESTC_AFTERGAMELOGIC_H

#include <ui/AUIO.h>
#include <ui/Button.h>
#include <ContextManager.h>
#include "ALogic.h"

class AfterGameLogic : public AContextLogic {
public:
    explicit AfterGameLogic(Context* context) : AContextLogic(context) {}
public:
    void update(Signal signal) override {
        if(signal.getUIOID() == "restart_bt" && signal.getState() == STATE::LEFT_BUTTON_CLICK) {
            AUIO* uio = context_->get("restart_bt");
            if(uio) {
//                IText* button = dynamic_cast<IText*>(context_->get("restart_bt"));
                ContextManager::getInstance().setCurrentContext("menu_context");

            }
        }
    }
};


#endif //TESTC_AFTERGAMELOGIC_H

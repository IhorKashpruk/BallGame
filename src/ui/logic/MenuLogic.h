#ifndef TESTC_MENULOGIC_H
#define TESTC_MENULOGIC_H

#include <ui/Button.h>
#include <Game.h>
#include "../../LevelManager.h"
#include "ALogic.h"

class MenuLogic : public AContextLogic {
public:
    explicit MenuLogic(Context* context) : AContextLogic(context) {}
public:
    void update(Signal signal) override {
        if(signal.getUIOID() == "start_bt" && signal.getState() == STATE::LEFT_BUTTON_CLICK) {
            level::LevelManager::getInstance().buildNextLevel();
            ContextManager::getInstance().setCurrentContext("game_context");
            return;
        }
        if(signal.getUIOID() == "exit_bt" && signal.getState() == STATE::LEFT_BUTTON_CLICK) {
            Game::getInstance().stop();
        }
    }
};

#endif //TESTC_MENULOGIC_H

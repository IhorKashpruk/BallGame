#include <ui/logic/AfterGameLogic.h>
#include <ui/ModernContext.h>
#include <ui/logic/GameLogic.h>
#include <ui/logic/WorldLogic.h>
#include <ui/physics/WorldUIO.h>
#include <ui/logic/MenuLogic.h>
#include "Game.h"

using namespace std;

void createBasicContext() {
    // Create after level menu
    auto* afterGameContext = new ModernIdentityContext<AfterGameLogic>("after_menu_context");
    pt::Rectangle<int> button_size {{window::size.w/2, 100}, 0, {50, 15}};
    Button<>* restart_bt = new Button<>("restart_bt", button_size, "Restart");
    button_size.center.y += 50;
    Button<>* menu_bt = new Button<>("menu_bt", button_size, "Menu");
    afterGameContext->add(restart_bt).add(menu_bt);

    // Create game context
    auto* gameContext = new ModernIdentityContext<GameLogic>("game_context");

    // Create world context
    pt::Rectangle<int> rectangle{{window::size.w/2, window::size.h/2}, 0, {window::size.w/2,window::size.h/2}};
    auto* worldContext =
            new WorldUIO<WorldLogic, pt::Rectangle>("world_context", rectangle);
    gameContext->add(worldContext);

    // Create menu context
    auto* menuContext = new ModernIdentityContext<MenuLogic>("menu_context");
    button_size.center.y = 100;
    Button<>* start_bt = new Button<>("start_bt", button_size, "Start");
    button_size.center.y += 50;
    Button<>* settings_bt = new Button<>("settings_bt", button_size, "Settings");
    button_size.center.y += 50;
    Button<>* exit_bt = new Button<>("exit_bt", button_size, "Exit");
    menuContext->add(start_bt).add(settings_bt).add(exit_bt);

    // Add context to ContextManager
    ContextManager::getInstance().add(afterGameContext).add(gameContext).add(menuContext);
    ContextManager::getInstance().setCurrentContext("menu_context");
}

int main() {
    Game::getInstance().setUp();
    createBasicContext();
    Game::getInstance().loop();
    return 0;
}
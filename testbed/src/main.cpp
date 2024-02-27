#include "noctis/events/InputManager.hpp"
#include <noctis/Game.hpp>

int main()
{
//    InputManager inputManager;
    Game game("serious shit", 500, 500);

    while (!game.windowShouldClose) {
        game.pollForEvent();
        game.drawFrame();
    }
    game.end();

    return 0;
}
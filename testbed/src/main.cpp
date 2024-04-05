#include <noctis/Game.hpp>

int main()
{
    Noctis::Game game("serious shit", 500, 500);

    while (!game.windowShouldClose) {
        game.pollEvents();
        game.drawFrame();
    }
    game.end();

    return 0;
}
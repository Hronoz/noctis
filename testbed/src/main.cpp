#include <noctis/EBus.hpp>
#include <noctis/Game.hpp>
#include <noctis/events/MouseMoveEvent.hpp>
#include <noctis/events/MousePressEvent.hpp>
#include <noctis/events/MouseReleaseEvent.hpp>
#include <noctis/logger.hpp>

int main()
{
    Game game("serious shit", 500, 500);

    // Subscribe event handlers
    EBus::Instance().subscribe(EventType::MousePress, onMousePress);
    EBus::Instance().subscribe(EventType::MouseRelease, onMouseRelease);
    EBus::Instance().subscribe(EventType::MouseMove, onMouseMove);

    while (!game.windowShouldClose) {
        game.pollForEvent();
        game.drawFrame();
    }
    game.end();

    return 0;
}
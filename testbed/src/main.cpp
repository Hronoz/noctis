#include <noctis/EBus.hpp>
#include <noctis/Game.hpp>
#include <noctis/events/MousePressEvent.hpp>
#include <noctis/events/MouseReleaseEvent.hpp>
#include <noctis/logger.hpp>
#include <render/Renderer.hpp>
#include <render/vulkan/VulkanBackend.hpp>

int main()
{
    Game game("serious shit", 100, 100);
    Renderer<VulkanBackend> render;

    // Subscribe event handlers
    EBus::Instance().subscribe(EventType::MousePress, onMousePress);
    EBus::Instance().subscribe(EventType::MouseRelease, onMouseRelease);

    while (true) {
        if (game.waitForEvent()) {
            break;
        }
    }

    return 0;
}
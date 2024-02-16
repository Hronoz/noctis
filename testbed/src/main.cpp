#include <core/logger.hpp>
#include <render/Renderer.hpp>
#include <render/vulkan/VulkanBackend.hpp>
#include <core/Game.hpp>

int main()
{
    Game game("serious shit", 100, 100);
    Renderer<VulkanBackend> render;

    INFO("test message");
    test();

    while (true) {
        if (game.waitForEvent()) {
            break;
        }
    }

    return 0;
}
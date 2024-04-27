#include "Game.hpp"

namespace Noctis
{

    Game::Game(const char *windowTitle, i32 width, i32 height) : renderer(windowTitle, width, height) {}

    Game::~Game() {}

    void Game::run()
    {
        while (!glfwWindowShouldClose(renderer.window)) {
            glfwPollEvents();
            renderer.drawFrame();
        }
    }
}  // namespace Noctis

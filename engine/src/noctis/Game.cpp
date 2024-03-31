#include "Game.hpp"

namespace Noctis
{

    Game::Game(const char *windowTitle, i32 width, i32 height)
      : renderer(windowTitle, width, height)
    {
    }

    Game::~Game() {}

    void Game::drawFrame()
    {
        renderer.drawFrame();
    }

    void Game::end()
    {
        renderer.end();
    }

    void Game::pollEvents()
    {
        glfwPollEvents();
        windowShouldClose = glfwWindowShouldClose(renderer.window);
    }
} // namespace Noctis
#include "Game.hpp"

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

void Game::pollForEvent() {
    windowShouldClose = renderer.pollForEvent();
}

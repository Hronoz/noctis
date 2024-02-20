#include "Game.hpp"

#include "noctis/logger.hpp"

Game::Game(const char *windowTitle, i32 width, i32 height, i16 ticks)
  : ticksPerSecond(ticks)
  , isRunning(true)
  , platform(windowTitle, 0, 0, width, height)
{
    INFO("skipTicks == %d", skipTicks);
    ticksPerSecond = 100;
    INFO("skipTicks == %d", skipTicks);
}

bool Game::waitForEvent()
{
    return platform.waitForEvent();
}

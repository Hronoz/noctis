#pragma once

#include "noctis.hpp"
#include "platform/Platform.hpp"

class IGameState;

class Game
{
    Platform platform;
    u16 ticksPerSecond;
    u16 skipTicks = 1000 / ticksPerSecond;
    u16 maxFrameSkip = 10;

  public:
    bool isRunning = false;

    Game(const char *windowTitle, i32 width, i32 height, i16 ticks = 50);

    ~Game() = default;

    void changeState(IGameState &state);

    void pushState(IGameState &state);

    void handleEvents();

    void update();

    void draw();

    bool waitForEvent();
};
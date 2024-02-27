#pragma once

#include "Renderer.hpp"
#include "noctis.hpp"
#include "platform/Platform.hpp"

#include <algorithm>
#include <array>
#include <limits>
#include <optional>
#include <vector>
#include <vulkan/vulkan.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#include <glm/glm.hpp>

class IGameState;

class Game
{
    Renderer renderer;

  public:
    bool windowShouldClose = false;

    Game(const char *windowTitle, i32 width, i32 height);

    ~Game();

    void drawFrame();

    void end();

    void changeState(IGameState &state);

    void pushState(IGameState &state);

    void handleEvents();

    void update();

    void pollForEvent();
};
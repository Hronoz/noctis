#pragma once

#include "Renderer.hpp"
#include "noctis.hpp"

#include <algorithm>
#include <array>
#include <limits>
#include <optional>
#include <vector>
#include <vulkan/vulkan.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#include <glm/glm.hpp>

namespace Noctis
{
    class Game
    {
      public:
        Renderer renderer;

      public:
        bool windowShouldClose = false;

        Game(const char *windowTitle, i32 width, i32 height);

        ~Game();

        void drawFrame();

        void end();

        void pollEvents();
    };
} // namespace Noctis
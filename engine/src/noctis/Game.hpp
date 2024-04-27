#pragma once

#include <vulkan/vulkan.h>

#include "Renderer.hpp"
#include "noctis.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#include <glm/glm.hpp>

namespace Noctis
{
    class Game
    {
       private:
        Renderer renderer;

       public:
        Game(const char *windowTitle, i32 width, i32 height);

        ~Game();

        void run();
    };
}  // namespace Noctis

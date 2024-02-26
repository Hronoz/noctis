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

const int MAX_FRAMES_IN_FLIGHT = 2;

const std::vector<Vertex> vertices = {
    {  { -0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
    {   { 0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
    {    { 0.5f, 0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
    {   { -0.5f, 0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } },

    { { -0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
    {  { 0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
    {   { 0.5f, 0.5f, -0.5f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
    {  { -0.5f, 0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } },

    { { -0.5f, -0.5f, -1.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
    {  { 0.5f, -0.5f, -1.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
    {   { 0.5f, 0.5f, -1.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
    {  { -0.5f, 0.5f, -1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } },
};

const std::vector<uint16_t> indices = { 0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4, 8, 9, 10, 10, 11, 8 };

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
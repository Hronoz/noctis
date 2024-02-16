#pragma once

#include "noctis.hpp"

struct RenderPacket
{
};

template <class T>
class Renderer
{

public:
    Renderer();

    ~Renderer();

    bool drawFrame(RenderPacket packet);
};
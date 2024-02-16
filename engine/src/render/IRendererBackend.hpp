#pragma once

#include "noctis.hpp"
#include "Renderer.hpp"

class IRendererBackend
{
public:
    IRendererBackend()
    = default;

    virtual ~IRendererBackend()
    = default;

    virtual void resized(u16 width, u16 height) = 0;

    virtual bool beginFrame() = 0;

    virtual bool endFrame() = 0;
};

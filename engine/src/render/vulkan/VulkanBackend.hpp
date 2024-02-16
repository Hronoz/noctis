#pragma once

#include "noctis.hpp"
#include "render/IRendererBackend.hpp"

class VulkanBackend : public IRendererBackend
{
public:
    explicit VulkanBackend(const char *appName);

    ~VulkanBackend() override;

    void resized(u16 width, u16 height) override;

    bool beginFrame() override;

    bool endFrame() override;
};
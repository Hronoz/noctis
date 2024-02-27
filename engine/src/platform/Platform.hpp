#pragma once

#include "noctis.hpp"
#include <fstream>
#include <memory>
#include <vector>
#include <vulkan/vulkan.h>

class Platform
{
  private:
    struct Impl; // struct for platform-specific info
    std::unique_ptr<Impl> pimpl;

    i32 _width, _height;

  public:
    Platform(const char *title, i16 x, i16 y, i32 width, i32 height);

    ~Platform();

    const char *windowName;

    void getFramebufferSize(u32 &width, u32 &height);

    void createWindowSurface(VkInstance instance, const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *surface);

    static std::vector<char> readFile(const std::string &filename);

    bool pollForEvent();
};
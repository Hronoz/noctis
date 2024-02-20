#pragma once

#include "noctis.hpp"
#include <memory>

class Platform
{
private:
    struct Impl; // struct for platform-specific info
    std::unique_ptr<Impl> pimpl;
public:
    Platform(const char *title, i16 x, i16 y, i32 width, i32 height);

    ~Platform();

    bool waitForEvent();
};
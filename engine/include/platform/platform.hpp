#pragma once

#include <memory>
#include "engine.hpp"

class Platform
{
private:
    struct Impl; // struct for platfrom-specific info
    std::unique_ptr<Impl> pimpl;
public:
    Platform(const char *title, i16 x, i16 y, i32 width, i32 height);

    virtual ~Platform();

    bool waitForEvent();
};
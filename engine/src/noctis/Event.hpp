#pragma once

#include "noctis.hpp"
// Base event class
struct Event
{
    EventType type;

    virtual i32 getCategoryFlags() const = 0;

    bool isInCategory(EventCategory category) const { return getCategoryFlags() & category; }

    virtual ~Event() {}
};

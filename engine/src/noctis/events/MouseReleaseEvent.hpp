#pragma once

#include "noctis/Event.hpp"

// Example event classes
class MouseReleaseEvent : public Event
{
  public:
    EventType type;
    i32 button, x, y;

    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);

    MouseReleaseEvent(i32 x, i32 y, i32 button)
      : type(EventType::MouseRelease)
      , button(button)
      , x(x)
      , y(y)
    {
    }

    ~MouseReleaseEvent() override = default;
};

void onMouseRelease(const Event *event);

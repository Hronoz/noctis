#pragma once

#include "noctis/Event.hpp"
#include "noctis/logger.hpp"

// Example event classes
class MousePressEvent : public Event
{
  public:
    EventType type;
    i32 button, x, y;

    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);

    MousePressEvent(i32 x, i32 y, i32 button)
      : type(EventType::MousePress)
      , button(button)
      , x(x)
      , y(y)
    {
    }
};

void onMousePress(const Event *event);
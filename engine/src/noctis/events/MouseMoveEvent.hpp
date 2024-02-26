#pragma once

#include "noctis/Event.hpp"

class MouseMoveEvent : public Event
{
  public:
    EventType type;
    i16 x, y;

    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);

    MouseMoveEvent(i16 x, i16 y)
      : type(EventType::MouseMove)
      , x(x)
      , y(y)
    {
    }
};

void onMouseMove(const Event *event);

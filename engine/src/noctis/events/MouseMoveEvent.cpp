#include "MouseMoveEvent.hpp"
#include "noctis/logger.hpp"

void onMouseMove(const Event *event)
{
    const MouseMoveEvent *mousePressEvent;
    mousePressEvent = dynamic_cast<const MouseMoveEvent *>(event);
    DEBUG("Mouse move x: %d", mousePressEvent->x);
    DEBUG("Mouse move y: %d", mousePressEvent->y);
}
#include "MouseReleaseEvent.hpp"
#include "noctis/logger.hpp"
#include <memory>

void onMouseRelease(const Event *event)
{
    const MouseReleaseEvent *mouseReleaseEvent;
    mouseReleaseEvent = dynamic_cast<const MouseReleaseEvent *>(event);
    DEBUG("Mouse %d was released:", mouseReleaseEvent->button);
    DEBUG("x: %d", mouseReleaseEvent->x);
    DEBUG("y: %d", mouseReleaseEvent->y);
}

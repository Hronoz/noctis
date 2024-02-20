#include "MousePressEvent.hpp"
#include "noctis/logger.hpp"
#include <memory>

void onMousePress(const Event *event)
{
    const MousePressEvent *mousePressEvent;
    mousePressEvent = dynamic_cast<const MousePressEvent *>(event);
    DEBUG("Mouse %d was pressed:", mousePressEvent->button);
    DEBUG("x: %d", mousePressEvent->x);
    DEBUG("y: %d", mousePressEvent->y);
}

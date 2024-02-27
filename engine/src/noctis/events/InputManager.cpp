#include "InputManager.hpp"
#include "noctis/EBus.hpp"

bool InputManager::processInput(xcb_generic_event_t *event)
{
    switch (event->response_type & ~0x80) {
        case XCB_MOTION_NOTIFY: {
            auto *motionEvent = (xcb_motion_notify_event_t *)event;
            EBus::Instance().publish(new MouseMoveEvent(motionEvent->event_x, motionEvent->event_y));
            break;
        }
        case XCB_KEY_PRESS: {
            auto *key_event = (xcb_key_press_event_t *)event;
            if (key_event->detail == KeyCode::Escape) {
                return true;
            }
            break;
        }
        case XCB_BUTTON_PRESS: {
            auto *buttonEvent = (xcb_button_press_event_t *)event;
            EBus::Instance().publish(
              new MousePressEvent(buttonEvent->event_x, buttonEvent->event_y, buttonEvent->detail));
            break;
        }
        case XCB_BUTTON_RELEASE: {
            auto *buttonEvent = (xcb_button_release_event_t *)event;
            EBus::Instance().publish(
              new MouseReleaseEvent(buttonEvent->event_x, buttonEvent->event_y, buttonEvent->detail));
            break;
        }
        case XCB_EXPOSE: {
            DEBUG("Expose event");
            break;
        }
        case XCB_CLIENT_MESSAGE: {
            auto *clientEvent = (xcb_client_message_event_t *)event;
            break;
        }
    }
    return false;
}

InputManager &InputManager::Instance()
{
    static InputManager instance;
    return instance;
}
InputManager::InputManager()
{
    EBus::Instance().subscribe(EventType::MouseMove, onMouseMove);
    EBus::Instance().subscribe(EventType::MousePress, onMousePress);
    EBus::Instance().subscribe(EventType::MouseRelease, onMouseRelease);
}

#pragma once

#include "MouseMoveEvent.hpp"
#include "MousePressEvent.hpp"
#include "MouseReleaseEvent.hpp"
#include "keycodes.hpp"
#include "noctis.hpp"
#include <unordered_map>
#include <xcb/xcb.h>

class InputManager
{
  public:
    static InputManager &Instance();

    InputManager(InputManager const &) = delete;

    void operator=(InputManager const &) = delete;

    bool processInput(xcb_generic_event_t *event);

    bool isKeyDown(i32 key) { return keyStates[key]; }

  private:
    InputManager();

    std::unordered_map<i32, bool> keyStates;
};

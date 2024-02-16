#include "platform.hpp" // "platform.hpp" provides "engine.hpp" with needed defines and typedefs

#ifdef PLATFORM_LINUX

#include "core/logger.hpp"

// TODO: xcb docs is absolute garbage, switch to xlib or suffer

// This macro is used to rename struct field in <xcb/xkb.h> named "explicit" which is keyword in C++
// xcb/xkb.h:727:19
// xcb/xkb.h:2005:30
// This solution works but better ways should be researched
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wkeyword-macro"
#endif
#define explicit explicit_
#ifdef __clang__
#pragma clang diagnostic pop
#endif

#include <xcb/xkb.h>

#undef explicit

#include <cstdlib>
#include <cstring>
#include <xcb/xcb.h>
#include <xcb/xcb_ewmh.h>
#include <xkbcommon/xkbcommon.h>

bool processInput(xkb_keysym_t keysym);

struct Platform::Impl
{
    xcb_connection_t *connection;
    xcb_screen_t *screen;
    xcb_window_t window;
    xcb_ewmh_connection_t ewmh;
    xcb_intern_atom_cookie_t *ewmh_cookies;
    xkb_state *key_state;
};

Platform::Platform(const char *title, i16 x, i16 y, i32 width, i32 height)
{
    xcb_connection_t *connection = xcb_connect(nullptr, nullptr);

    if (xcb_connection_has_error(connection)) {
        ERROR("Error opening display.");
        std::exit(1);
    }

    const xcb_setup_t *setup = xcb_get_setup(connection);
    xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);
    xcb_screen_t *screen = iter.data;
    xcb_window_t window = xcb_generate_id(connection);

    DEBUG("roots_len:\t%d", setup->roots_len);
    DEBUG("root:\t\t%d", screen->root);
    DEBUG("width:\t\t%d", screen->width_in_pixels);
    DEBUG("height:\t%d", screen->height_in_pixels);

    u32 mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;

    u32 event_list =
            XCB_BUTTON_PRESS | XCB_BUTTON_RELEASE | XCB_MOTION_NOTIFY | XCB_KEY_PRESS | XCB_KEY_RELEASE | XCB_EXPOSE;
    u32 value_list[] = {screen->black_pixel, event_list};

    xcb_create_window(
            connection,
            screen->root_depth,
            window,
            screen->root,
            x,
            y,
            width,
            height,
            10,
            XCB_WINDOW_CLASS_INPUT_OUTPUT,
            screen->root_visual,
            mask,
            value_list
    );

    xcb_ewmh_connection_t ewmh;
    xcb_intern_atom_cookie_t *ewmh_cookies = xcb_ewmh_init_atoms(connection, &ewmh);

    if (!xcb_ewmh_init_atoms_replies(&ewmh, ewmh_cookies, nullptr)) {
        ERROR("EWMH init atoms failed");
        exit(1);
    }

    xcb_change_property(
            connection, XCB_PROP_MODE_REPLACE, window, XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8, std::strlen(title), title
    );

    xcb_change_property(
            connection,
            XCB_PROP_MODE_REPLACE,
            window,
            ewmh._NET_WM_STATE,
            XCB_ATOM_ATOM,
            32,
            1,
            &(ewmh._NET_WM_STATE_FULLSCREEN));

    xcb_xkb_use_extension(connection, XCB_XKB_MAJOR_VERSION, XCB_XKB_MINOR_VERSION);
    xcb_xkb_per_client_flags(
            connection, XCB_XKB_ID_USE_CORE_KBD, XCB_XKB_PER_CLIENT_FLAG_DETECTABLE_AUTO_REPEAT, 1, 0, 0, 0
    );

    xkb_context *x_context = xkb_context_new(XKB_CONTEXT_NO_FLAGS);
    xkb_keymap *x_keymap = xkb_keymap_new_from_names(x_context, nullptr, XKB_KEYMAP_COMPILE_NO_FLAGS);
    xkb_state *key_state = xkb_state_new(x_keymap);

    pimpl = std::make_unique<Impl>();
    pimpl->connection = connection;
    pimpl->screen = screen;
    pimpl->window = window;
    pimpl->ewmh = ewmh;
    pimpl->ewmh_cookies = ewmh_cookies;
    pimpl->key_state = key_state;

    xcb_map_window(connection, window);
    xcb_flush(connection);
    xcb_delete_property(pimpl->connection, pimpl->window, pimpl->ewmh._NET_WM_STATE);
    xcb_flush(pimpl->connection);
}

// Return true when escaped was pressed
bool Platform::waitForEvent()
{
    xcb_generic_event_t *event;
    bool finish = false;
    xkb_keysym_t keysym;
    char key[32];

    event = xcb_wait_for_event(pimpl->connection);

    switch (event->response_type) {
        case XCB_KEY_PRESS:
            keysym = xkb_state_key_get_one_sym(pimpl->key_state, ((xcb_key_press_event_t *) event)->detail);
            xkb_keysym_get_name(keysym, key, 32);
            DEBUG("Button pressed: \t%s\t%d", key, ((xcb_key_press_event_t *) event)->detail);
            finish = processInput(keysym);
            break;

        case XCB_KEY_RELEASE:
            keysym = xkb_state_key_get_one_sym(pimpl->key_state, ((xcb_key_release_event_t *) event)->detail);
            xkb_keysym_get_name(keysym, key, 32);
            DEBUG("Button released: \t%s", key);
            break;

        case XCB_BUTTON_PRESS:
        DEBUG("Mouse pressed:  \t%u", ((xcb_button_press_event_t *) event)->detail);
            DEBUG("X-coord: \t\t\t%u", ((xcb_button_press_event_t *) event)->event_x);
            DEBUG("Y-coord: \t\t\t%u", ((xcb_button_press_event_t *) event)->event_y);
            break;
        case XCB_BUTTON_RELEASE:
        DEBUG("Mouse released:  \t%u", ((xcb_button_release_event_t *) event)->detail);
            DEBUG("X-coord: \t\t\t%u", ((xcb_button_release_event_t *) event)->event_x);
            DEBUG("Y-coord: \t\t\t%u", ((xcb_button_release_event_t *) event)->event_y);

        default:
            break;
    }
    free(event);

    return finish;
}

Platform::~Platform()
{
    xcb_disconnect(pimpl->connection);
}

bool processInput(xkb_keysym_t keysym)
{
    switch (keysym) {
        case XKB_KEY_Escape:
            return true;
        default:
            return false;
    }
}

#endif
#include "platform/platform.hpp"

#ifdef PLATFORM_LINUX

#include "core/logger.hpp"

#include <xcb/xcb.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>

void Platform::start(const char *title, i16 x, i16 y, i32 width, i32 height)
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

    u32 mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    u32 event_list = XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_EXPOSURE;
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

    xcb_change_property(
            connection,
            XCB_PROP_MODE_REPLACE,
            window,
            XCB_ATOM_WM_NAME,
            XCB_ATOM_STRING,
            8,
            std::strlen(title),
            title
    );

    xcb_map_window(connection, window);
    xcb_flush(connection);
    sleep(1);
    xcb_disconnect(connection);
}

#endif
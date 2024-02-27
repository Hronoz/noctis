#include "Platform.hpp" // "platform.hpp" provides "engine.hpp" with needed defines and typedefs
#include "noctis/events/InputManager.hpp"
#include "noctis/logger.hpp"
#include "render/vulkan/VkTypes.hpp"

#ifdef PLATFORM_LINUX

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
#include <vulkan/vulkan_xcb.h>
#include <xcb/xcb.h>
#include <xcb/xcb_ewmh.h>
#include <xkbcommon/xkbcommon.h>

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
  : windowName(title)
  , _width(width)
  , _height(height)
{
    DEBUG("Linux platform constructor was called");
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
    DEBUG("width:\t\t%d", _width);
    DEBUG("height:\t%d", _height);

    u32 mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;

    u32 event_list = XCB_EVENT_MASK_KEY_RELEASE | XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_BUTTON_PRESS |
                     XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_POINTER_MOTION |
                     XCB_EVENT_MASK_ENTER_WINDOW | XCB_EVENT_MASK_LEAVE_WINDOW | XCB_EVENT_MASK_STRUCTURE_NOTIFY;
    u32 value_list[] = { screen->black_pixel, event_list };

    xcb_create_window(connection,
                      screen->root_depth,
                      window,
                      screen->root,
                      x,
                      y,
                      _width,
                      _height,
                      10,
                      XCB_WINDOW_CLASS_INPUT_OUTPUT,
                      screen->root_visual,
                      mask,
                      value_list);

    xcb_ewmh_connection_t ewmh;
    xcb_intern_atom_cookie_t *ewmh_cookies = xcb_ewmh_init_atoms(connection, &ewmh);

    if (!xcb_ewmh_init_atoms_replies(&ewmh, ewmh_cookies, nullptr)) {
        ERROR("EWMH init atoms failed");
        exit(1);
    }

    xcb_change_property(connection,
                        XCB_PROP_MODE_REPLACE,
                        window,
                        XCB_ATOM_WM_NAME,
                        XCB_ATOM_STRING,
                        8,
                        std::strlen(windowName),
                        windowName);

    xcb_change_property(connection,
                        XCB_PROP_MODE_REPLACE,
                        window,
                        ewmh._NET_WM_STATE,
                        XCB_ATOM_ATOM,
                        32,
                        1,
                        &(ewmh._NET_WM_STATE_FULLSCREEN));

    xcb_xkb_use_extension(connection, XCB_XKB_MAJOR_VERSION, XCB_XKB_MINOR_VERSION);
    xcb_xkb_per_client_flags(
      connection, XCB_XKB_ID_USE_CORE_KBD, XCB_XKB_PER_CLIENT_FLAG_DETECTABLE_AUTO_REPEAT, 1, 0, 0, 0);

    xkb_context *x_context = xkb_context_new(XKB_CONTEXT_NO_FLAGS);
    xkb_keymap *x_keymap = xkb_keymap_new_from_names(x_context, nullptr, XKB_KEYMAP_COMPILE_NO_FLAGS);
    xkb_state *key_state = xkb_state_new(x_keymap);

    xcb_intern_atom_cookie_t cookie = xcb_intern_atom(connection, 1, 12, "WM_PROTOCOLS");
    xcb_intern_atom_reply_t *reply = xcb_intern_atom_reply(connection, cookie, 0);

    xcb_intern_atom_cookie_t cookie2 = xcb_intern_atom(connection, 0, 16, "WM_DELETE_WINDOW");
    xcb_intern_atom_reply_t *reply2 = xcb_intern_atom_reply(connection, cookie2, 0);

    xcb_change_property(connection, XCB_PROP_MODE_REPLACE, width, (*reply).atom, 4, 32, 1, &(*reply2).atom);

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

    DEBUG("Linux platform was successfully initialized");
}

// Return true when escaped was pressed
bool Platform::pollForEvent()
{
    xcb_generic_event_t *event;
    bool finish = false;
    xkb_keysym_t keysym;

    if ((event = xcb_poll_for_event(pimpl->connection)) != nullptr) {
        switch (event->response_type & ~0x80) {
            case XCB_MOTION_NOTIFY:
            case XCB_KEY_PRESS:
            case XCB_BUTTON_PRESS:
            case XCB_BUTTON_RELEASE: {
                finish = InputManager::Instance().processInput(event);
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
    }
    free(event);

    return finish;
}

Platform::~Platform()
{
    xcb_disconnect(pimpl->connection);
}

void Platform::createWindowSurface(VkInstance instance, const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *surface)
{
    VkXcbSurfaceCreateInfoKHR surfaceCreateInfo{};
    surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
    surfaceCreateInfo.pNext = nullptr;
    surfaceCreateInfo.flags = 0;
    surfaceCreateInfo.connection = pimpl->connection;
    surfaceCreateInfo.window = pimpl->window;

    VK_CHECK(vkCreateXcbSurfaceKHR(instance, &surfaceCreateInfo, pAllocator, surface));
}

void Platform::getFramebufferSize(u32 &width, u32 &height)
{
    width = _width;
    height = _height;
}

std::vector<char> Platform::readFile(const std::string &filename)
{
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("failed to open file");
    }

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);
    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();

    return buffer;
}

#endif
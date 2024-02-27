find_package(X11 REQUIRED)
find_package(Vulkan REQUIRED)
find_package(glm REQUIRED)
link_libraries(${X11_xcb_LIB})
link_libraries(${X11_xcb_ewmh_LIB})
link_libraries(${X11_xcb_xkb_LIB})
link_libraries(${X11_xkbcommon_LIB})
include_directories(${PROJECT_SOURCE_DIR}/engine/src)

add_library(engine SHARED src/noctis.cpp
        src/noctis.hpp
        src/noctis/logger.cpp
        src/noctis/logger.hpp
        src/platform/PlatformLinux.cpp
        src/platform/Platform.hpp
        src/noctis/Game.cpp
        src/noctis/Game.hpp
        src/noctis/IGameState.hpp
        src/noctis/TestGameState.cpp
        src/noctis/TestGameState.hpp
        src/noctis/Event.hpp
        src/noctis/events/MousePressEvent.hpp
        src/noctis/EBus.hpp
        src/noctis/events/MousePressEvent.cpp
        src/noctis/events/MouseReleaseEvent.cpp
        src/noctis/events/MouseReleaseEvent.hpp
        src/render/vulkan/VkTypes.hpp
        src/noctis/events/MouseMoveEvent.cpp
        src/noctis/events/MouseMoveEvent.hpp
        src/noctis/Renderer.cpp
        src/noctis/Renderer.hpp
        src/noctis/events/InputManager.cpp
        src/noctis/events/InputManager.hpp
        src/noctis/events/keycodes.hpp
)
target_include_directories(engine PUBLIC ${PROJECT_SOURCE_DIR}/engine)
target_link_libraries(engine Vulkan::Vulkan)
target_link_libraries(engine glm::glm)
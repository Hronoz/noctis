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
        src/core/logger.cpp
        src/core/logger.hpp
        src/platform/platform_linux.cpp
        src/platform/platform.hpp
        src/render/Renderer.cpp
        src/render/Renderer.hpp
        src/render/IRendererBackend.hpp
        src/render/vulkan/VulkanBackend.cpp
        src/render/vulkan/VulkanBackend.hpp
        src/core/Game.cpp
        src/core/Game.hpp
        src/core/IGameState.hpp
        src/core/TestGameState.cpp
        src/core/TestGameState.hpp
)
target_include_directories(engine PUBLIC ${PROJECT_SOURCE_DIR}/engine)
target_link_libraries(engine Vulkan::Vulkan)
target_link_libraries(engine glm::glm)

# install(TARGETS testbed LIBRARY DESTINATION lib ARCHIVE DESTINATION bin)